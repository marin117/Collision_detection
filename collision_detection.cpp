#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>
#include <iostream>
#include "src/Ball.h"
#include "src/KDTree.h"
#include "src/Wall.h"

void changeSize(int w, int h) {
  if (h == 0) {
    h = 1;
  }

  double ratio = 1.0 * w / h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  gluPerspective(45, ratio, 1, 1000);  // view angle u y, aspect, near, far
}

static std::vector<std::shared_ptr<Ball> > balls;
static std::vector<Wall> walls;

void init() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);  // idemo u perspektivu
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glLoadIdentity();  // resetiranje

  gluLookAt(0.0, 0.0, 50.0,     // camera
            0.0, 0.0, -1.0,     // where
            0.0f, 1.0f, 0.0f);  // up vector
}

static float ot, nt, dt;

void drawScene() {
  init();
  KDtreeNode kdTree;

  glPushMatrix();
  glTranslatef(0, 0, 0);
  for (uint i = 0; i < balls.size(); i++) {
    balls[i]->drawSphere();
  }

  kdTree.build_tree(balls, 0);
  kdTree.treeTraverse();

  glPopMatrix();
  glutSwapBuffers();
  exit(0);
}

void update(int) {
  nt = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
  dt = nt - ot;
  ot = nt;

  bool collision;
  for (unsigned int i = 0; i < balls.size(); i++) {
    for (unsigned int k = 0; k < walls.size(); k++) {
      if (balls[i]->isWallCollision(walls[k])) {
        float dot = balls[i]->vecDir * walls[k].vecDir;
        float doubleDot = dot * 2;
        Vector3D newNorm = walls[k].vecDir * doubleDot;
        balls[i]->vecDir = balls[i]->vecDir - newNorm;
      }
    }
  }
  for (unsigned int i = 0; i < balls.size(); i++) {
    for (unsigned int j = i + 1; j < balls.size(); j++) {
      collision = balls[i]->isBallCollision(*balls[j]);

      if (collision) {
        Vector3D v_n(balls[i]->getCenter() - balls[j]->getCenter());
        Vector3D v_un = v_n.normal();
        Vector3D v_ut(-v_un.y(), v_un.x(), v_un.z());

        float v1n = v_un * balls[i]->vecDir;
        float v1t = v_ut * balls[i]->vecDir;

        float v2n = v_un * balls[j]->vecDir;
        float v2t = v_ut * balls[j]->vecDir;

        // količina gibanja formula

        balls[i]->vecDir.setX(v2n * v_un.x() + v1t * v_ut.x());
        balls[i]->vecDir.setY(v2n * v_un.y() + v1t * v_ut.y());

        balls[j]->vecDir.setX(v1n * v_un.x() + v2t * v_ut.x());
        balls[j]->vecDir.setY(v1n * v_un.y() + v2t * v_ut.y());
      }
    }
  }

  for (uint i = 0; i < balls.size(); i++) {
    balls[i]->updatePosition(dt);
  }

  glutPostRedisplay();
  glutTimerFunc(16, update, 0);
}

int main(int argc, char **argv) {
  std::srand(time(NULL));

  walls.emplace_back(Wall(0, 20, 0, 20, 0, 0, 0, -1, 0));
  walls.emplace_back(Wall(0, -20, 0, 20, 0, 0, 0, 1, 0));
  walls.emplace_back(Wall(20, 0, 0, 0, 20, 0, -1, 0, 0));
  walls.emplace_back(Wall(-20, 0, 0, 0, 20, 0, 1, 0, 0));

  // unsigned int ballNum = std::rand() % 40 + 2;
  unsigned int ballNum = 5;
  for (uint i = 0; i < ballNum; i++) {
    float x = std::rand() % 40 - 20;
    float y = std::rand() % 40 - 20;
    std::cout << i << ": x " << x << " y " << y << " ";
    float speedX = std::rand() % 10 + 1;
    float speedY = std::rand() % 10 + 1;
    balls.emplace_back(
        std::make_shared<Ball>(Ball(x, y, 0, 0.2, speedX, speedY, 0.0)));
    std::cout << std::endl;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1024, 1080);

  glutCreateWindow("AABB");
  glutReshapeFunc(changeSize);
  glutDisplayFunc(drawScene);
  glutTimerFunc(0, update, 0);
  ot = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

  glutMainLoop();

  return 0;
}
