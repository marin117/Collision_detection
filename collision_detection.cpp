#include "src/Ball.h"
#include "src/KDTree.h"
#include "src/Wall.h"
#include <GL/gl.h>
#include <GL/glut.h>
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
  KDtreeNode<Ball> ballKdTree;
  // KDtreeNode<Wall> wallKdTree;

  for (uint i = 0; i < balls.size(); i++) {
    balls[i].drawSphere();
  }
  // wallKdTree.build_tree(walls, 0);
  for (unsigned int i = 0; i < balls.size(); i++) {
    // wallKdTree.searchCollisions(balls[i]);
    for (unsigned int k = 0; k < walls.size(); k++) {
      if (balls[i].collision(walls[k])) {
        balls[i].resolveCollision(walls[k]);
      }
    }
  }

  ballKdTree.build_tree(balls, 0);
  // kdTree.treeTraverse();
  for (unsigned int i = 0; i < balls.size(); i++) {
    ballKdTree.searchCollisions(balls[i]);
  }

  // std::cout << "ball speed: " << balls[0].vecDir.x() << std::endl;

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
  glutTimerFunc(32, update, 0);
}

int main(int argc, char **argv) {
  std::srand(time(NULL));

  walls.emplace_back(Wall(0, 20, 0, 25, 0, 0, 0, -1, 0, 10000));
  walls.emplace_back(Wall(0, -20, 0, 25, 0, 0, 0, 1, 0, 10000));
  walls.emplace_back(Wall(25, 0, 0, 0, 25, 0, -1, 0, 0, 10000));
  walls.emplace_back(Wall(-25, 0, 0, 0, 25, 0, 1, 0, 0, 10000));

  // unsigned int ballNum = std::rand() % 40 + 2;
  unsigned int ballNum = 20;
  for (uint i = 0; i < ballNum; i++) {
    float x = std::rand() % 40 - 20;
    float y = std::rand() % 20;
    // std::cout << i << ": x " << x << " y " << y << " " << std::endl;

    float speedX = std::rand() % 10 + 1;
    float speedY = std::rand() % 10 + 1;
    float mass = std::rand() % 5 + 1;
    balls.emplace_back(Ball(x, y, 0, 0.5, 0, speedY, 0.0, mass));
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
