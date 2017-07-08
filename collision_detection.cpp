#include "src/Ball.h"
#include "src/KDTree.h"
#include "src/Wall.h"

#include <iostream>
#include <time.h>

void changeSize(int w, int h) {
  if (h == 0) {
    h = 1;
  }

  double ratio = 1.0 * w / h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  gluPerspective(45, ratio, 1, 1000); // view angle u y, aspect, near, far
}

static std::vector<Ball> balls;
static std::vector<Wall> walls;

void init() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW); // idemo u perspektivu
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glLoadIdentity(); // resetiranje

  gluLookAt(0.0, 0.0, 50.0,    // camera
            0.0, 0.0, -1.0,    // where
            0.0f, 1.0f, 0.0f); // up vector
}

static float ot, nt, dt;

void drawScene() {
  init();

  glPushMatrix();
  glTranslatef(0, 0, 0);
  for (uint i = 0; i < balls.size(); i++) {
    balls[i].drawSphere();
  }
  KDtreeNode<Ball> ballKdTree;
  KDtreeNode<Wall> wallKdTree;

  wallKdTree.build_tree(walls, 0);
  for (unsigned int i = 0; i < balls.size(); i++)
    wallKdTree.searchCollisions(balls[i]);

  ballKdTree.build_tree(balls, 0);
  for (unsigned int i = 0; i < balls.size(); i++)
    ballKdTree.searchCollisions(balls[i]);

  glPopMatrix();
  glutSwapBuffers();
}

void update(int) {
  nt = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
  dt = nt - ot;
  ot = nt;

  for (uint i = 0; i < balls.size(); i++) {
    balls[i].updatePosition(dt);
  }

  glutPostRedisplay();
  glutTimerFunc(16, update, 0);
}

int main(int argc, char **argv) {
  std::srand(time(NULL));

  // walls.emplace_back(Wall(0, 20, 0, 25, 0, 0, 0, -1, 0, 10000));
  walls.emplace_back(Wall(0, -20, 0, 25000, 0, 0, 0, 1, 0, 10000));
  walls.emplace_back(Wall(25, 0, 0, 0, 25000, 0, -1, 0, 0, 10000));
  walls.emplace_back(Wall(-25, 0, 0, 0, 25000, 0, 1, 0, 0, 10000));

  // unsigned int ballNum = std::rand() % 40 + 2;
  unsigned int ballNum = 10;
  for (uint i = 0; i < ballNum; i++) {
    float x = std::rand() % 40 - 20;
    float y = std::rand() % 20;

    float speedX = std::rand() % 20 - 10;
    float speedY = std::rand() % 10 + 1;
    float mass = std::rand() % 20 + 1000;
    balls.emplace_back(Ball(x, y, 0, 0.5, speedX, speedY, 0.0, mass, i));
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1024, 1080);

  glutCreateWindow("Collision detection");
  glutReshapeFunc(changeSize);
  glutDisplayFunc(drawScene);
  glutTimerFunc(0, update, 0);
  ot = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
  glutMainLoop();

  return 0;
}
