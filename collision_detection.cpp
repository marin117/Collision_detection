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
std::vector <float> speeds;
std::vector <float> k;
std::vector <Actor> actors;




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
        actors.emplace_back(Actor(x[i],y[i],0,2,k[i]));
    }
    glPopMatrix();
    glutSwapBuffers();

}

void update(int){

    float calc;

    for(unsigned int i =0; i<actors.size();i++){
        for (unsigned int j=i+1;j<actors.size();j++){
            collision = actors[i].isCollision(actors[j]);
            if (collision){
                calc = (actors[i].center.y - actors[j].center.y)/(actors[i].center.x - actors[j].center.x);
                k[i]=k[j] = calc;
                speeds[i]=-speeds[i];
                speeds[j]=-speeds[j];

            }
        }
    }


    for (uint i = 0;i<x.size();i++){
        x[i]+=speeds[i];
    }


    actors.clear();
    glutPostRedisplay();
    glutTimerFunc (3,update, 0 );

}


int main(int argc, char **argv){

    x.emplace_back(0);
    x.emplace_back(10);

    y.emplace_back(0.0);
    y.emplace_back(3.0);

    k.emplace_back(0.0);
    k.emplace_back(-1.0);

    speeds.emplace_back(0.05);
    speeds.emplace_back(-0.05);



    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize ( 1000, 1000 );

    glutCreateWindow ( "AABB" );
    glutReshapeFunc ( changeSize );
    glutDisplayFunc ( drawScene );
    glutTimerFunc ( 3, update, 0 );

    glutMainLoop();

	return 0;
}
