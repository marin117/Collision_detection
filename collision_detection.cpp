#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
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

std::vector <Actor> actors;


void init(){

    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode ( GL_MODELVIEW ); // idemo u perspektivu
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glLoadIdentity(); // resetiranje

    gluLookAt ( 0.0,0.0,50.0, // camera
                0.0,0.0,-1.0, // where
                0.0f,1.0f,0.0f ); // up vector

}


float ot, nt,dt;

void drawScene()
{
    init();

    glPushMatrix();
    glTranslatef(0,0,0);
    for (uint i = 0;i<actors.size();i++){
        actors[i].drawSphere();
    }

    glPopMatrix();

    glutSwapBuffers();

}

void update(int){

    nt = glutGet(GLUT_ELAPSED_TIME)/1000.0f;
    dt = nt - ot;
    ot = nt;

    for(unsigned int i =0; i<actors.size();i++){
        for (unsigned int j=i+1;j<actors.size();j++){

            collision = actors[i].isCollision(actors[j]);

            if (collision){

                Vector3D v_n(actors[i].center - actors[j].center);
                Vector3D v_un = v_n.normal();
                Vector3D v_ut(-v_un.y(),v_un.x(),v_un.z());

                float v1n = v_un * actors[i].velocity;
                float v1t = v_ut * actors[i].velocity;

                float v2n = v_un * actors[j].velocity;
                float v2t = v_ut * actors[j].velocity;

                //količina gibanja formula

                actors[i].velocity.setX(v2n * v_un.x() + v1t * v_ut.x());
                actors[i].velocity.setY(v2n * v_un.y() + v1t * v_ut.y());

                actors[j].velocity.setX(v1n * v_un.x() + v2t * v_ut.x());
                actors[j].velocity.setY(v1n * v_un.y() + v2t * v_ut.y());

            }
        }
    }

    for (uint i=0; i<actors.size();i++){
        actors[i].updatePosition(dt);
    }

    glutPostRedisplay();
    glutTimerFunc (25,update, 0 );

}


int main(int argc, char **argv){

    std::vector <float> x;
    std::vector<float> y;
    std::vector <float> speedX, speedY;



    x.emplace_back(10);
    x.emplace_back(-10);

    y.emplace_back(2.0);
    y.emplace_back(0.0);

    speedY.emplace_back(0);
    speedY.emplace_back(0);

    speedX.emplace_back(-5);
    speedX.emplace_back(5);


    for (uint i = 0;i<x.size();i++){
        actors.emplace_back(Actor(x[i],y[i],0,2,speedX[i],speedY[i],0.0));
    }

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
