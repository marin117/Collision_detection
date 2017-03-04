#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "src/point.h"
#include "src/AABB_box.h"
#include "src/AABBTreeNode.h"
#include "src/Actor.h"

typedef unsigned int uint;

void changeSize ( int w, int h )
{
    if ( h == 0 )
    {
        h = 1;
    }

    float ratio = 1.0* w / h;

    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();
    glViewport ( 0, 0, w, h );
    gluPerspective ( 45,ratio,1,1000 ); // view angle u y, aspect, near, far
}



bool collision;
std::vector <float> x;
std::vector<float> y;
std::vector <float> speedX, speedY;
std::vector <Actor> actors;


float ot, nt,dt;

void drawScene()
{


    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode ( GL_MODELVIEW ); // idemo u perspektivu
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glLoadIdentity(); // resetiranje

    gluLookAt ( 0.0,0.0,50.0, // camera
                0.0,0.0,-1.0, // where
                0.0f,1.0f,0.0f ); // up vector

    glPushMatrix();
    glTranslatef(0,0,0);
    for (uint i = 0;i<x.size();i++){
        actors.emplace_back(Actor(x[i],y[i],0,2));
    }


    glPopMatrix();
    glutSwapBuffers();

}

void update(int){

    nt = glutGet(GLUT_ELAPSED_TIME)/1000.0f;
    dt = nt - ot;
    ot = nt;

    for(unsigned int i =0; i<1/*actors.size()*/;i++){
        for (unsigned int j=i+1;j<actors.size();j++){
            collision = actors[i].isCollision(actors[j]);

            if (collision){
                float x_n = actors[i].center.x - actors[j].center.x;
                float y_n = actors[i].center.y - actors[j].center.y;
                float mag = std::sqrt(std::pow(x_n,2) + std::pow(y_n,2));

                float x_un = x_n/mag;
                float y_un = y_n/mag;

                float x_ut = -y_un;
                float y_ut = x_un;

                float speed1N = x_un * speedX[i] + y_un * speedY[i];
                float speed1T = x_ut * speedX[i] + y_ut * speedY[i];

                float speed2N = x_un * speedX[j] + y_un * speedY[j];
                float speed2T = x_ut * speedX[j] + y_ut * speedY[j];

                // ovdje treba postojat formula za količinu gibanja

                speedX[i] = speed2N * x_un + speed1T*x_ut;
                speedY[i] = speed2N*y_un + speed1T*y_ut;

                speedX[j] = speed1N * x_un + speed2T * x_ut;
                speedY[j] = speed1N * y_un + speed2T * y_ut;

            }
        }
    }

    for (uint i = 0;i<x.size();i++){

        x[i]+=speedX[i]*dt;
        y[i]+=speedY[i]*dt;

    }


    actors.clear();

    glutPostRedisplay();
    glutTimerFunc (16,update, 0 );

}


int main(int argc, char **argv){

    x.emplace_back(-10);
    x.emplace_back(10);

    y.emplace_back(5.0);
    y.emplace_back(0.0);

    speedY.emplace_back(-3);
    speedY.emplace_back(0);

    speedX.emplace_back(5);
    speedX.emplace_back(-5);



    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize ( 1000, 1000 );

    glutCreateWindow ( "AABB" );
    glutReshapeFunc ( changeSize );
    glutDisplayFunc ( drawScene );
    glutTimerFunc ( 0, update, 0 );
    ot = glutGet(GLUT_ELAPSED_TIME)/1000.0f;

    glutMainLoop();

	return 0;
}
