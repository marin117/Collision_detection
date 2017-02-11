#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "src/point.h"
#include "src/AABB_box.h"
#include "src/AABBTreeNode.h"
#include "src/Actor.h"



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
std::vector<AABB_box>boxes;

void drawSphere(float x,float y,float z,float r,float slices,float stacks){


    glPushMatrix();
    glTranslatef(x,y,z);
    boxes.emplace_back(AABB_box(x,y,z,r));
    glutSolidSphere(r,slices,stacks);
    glPopMatrix();
}



float i = 5.;
float j = -5.;
bool collision;


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
    Actor kugla(0,0,0,2,i,0);
    Actor kugla2(5,0,0,2,j,0);
    glPopMatrix();
    glutSwapBuffers();

    boxes.clear();

    collision = kugla.root->treeOverlap(kugla2.root);
}


void update(int){
    i-=0.05;
    j+=0.05;

    if (collision) exit(0);
    glutPostRedisplay();
    glutTimerFunc (3,update, 0 );

}


int main(int argc, char **argv){

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
