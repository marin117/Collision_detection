#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>
#include <iostream>
#include <memory>
#include "src/Ball.h"
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

static std::vector<Ball> actors;
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

  glPushMatrix();
  glTranslatef(0, 0, 0);
  for (uint i = 0; i < actors.size(); i++) {
    actors[i].drawSphere();
  }

  glPopMatrix();
  glutSwapBuffers();
}

void update(int) {
  nt = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
  dt = nt - ot;
  ot = nt;

  bool collision;
  for (unsigned int i = 0; i < actors.size(); i++) {
    for (unsigned int k = 0; k < walls.size(); k++) {
      if (actors[i].isWallCollision(walls[k])) {
        float dot = actors[i].vecDir * walls[k].vecDir;
        float doubleDot = dot * 2;
        Vector3D newNorm = walls[k].vecDir * doubleDot;
        actors[i].vecDir = actors[i].vecDir - newNorm;
      }
    }
  }
  for (unsigned int i = 0; i < actors.size(); i++) {
    for (unsigned int j = i + 1; j < actors.size(); j++) {
      collision = actors[i].isBallCollision(actors[j]);

      if (collision) {
        Vector3D v_n(actors[i].getCenter() - actors[j].getCenter());
        Vector3D v_un = v_n.normal();
        Vector3D v_ut(-v_un.y(), v_un.x(), v_un.z());

        float v1n = v_un * actors[i].vecDir;
        float v1t = v_ut * actors[i].vecDir;

        float v2n = v_un * actors[j].vecDir;
        float v2t = v_ut * actors[j].vecDir;

        // količina gibanja formula

        actors[i].vecDir.setX(v2n * v_un.x() + v1t * v_ut.x());
        actors[i].vecDir.setY(v2n * v_un.y() + v1t * v_ut.y());

        actors[j].vecDir.setX(v1n * v_un.x() + v2t * v_ut.x());
        actors[j].vecDir.setY(v1n * v_un.y() + v2t * v_ut.y());
      }
    }
  }

  for (uint i = 0; i < actors.size(); i++) {
    actors[i].updatePosition(dt);
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

  int ballNum = std::rand() % 40 + 2;

  for (int i = 0; i < ballNum; i++) {
    float x = std::rand() % 40 - 20;
    float y = std::rand() % 40 - 20;
    float speedX = std::rand() % 10 + 1;
    float speedY = std::rand() % 10 + 1;
    actors.emplace_back(Ball(x, y, 0, 0.2, speedX, speedY, 0.0));
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
