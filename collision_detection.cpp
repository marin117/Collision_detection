#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "src/point.h"
#include "src/AABB_box.h"
#include "src/AABBTreeNode.h"

typedef std::unique_ptr<Node> ptr;


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
    drawSphere(5,0.0,0.0,2.0,100,10);
    drawSphere(2,0.0,0.0,2.0,100,10);
    drawSphere(3,2.0,0.0,2.0,100,10);
    drawSphere(3,-2.0,0.0,2.0,100,10);
    glPopMatrix();
    glutSwapBuffers();

    ptr node1 = std::make_unique<Node>(boxes[0]);
    ptr node2 = std::make_unique<Node>(boxes[1]);
    ptr node3 = std::make_unique<Node>(boxes[2]);
    ptr node4 = std::make_unique<Node>(boxes[3]);


    ptr tree1 = std::make_unique<Node>(node1,node2);
    ptr tree2 = std::make_unique<Node>(node3,node4);
    ptr tree = std::make_unique<Node>(tree1,tree2);

    setIndex(tree,0);
    treeTraverse(tree);
}


int main(int argc, char **argv){

    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize ( 1000, 1000 );

    glutCreateWindow ( "AABB" );
    glutReshapeFunc ( changeSize );
    glutDisplayFunc ( drawScene );
    //glutTimerFunc ( 3, update, 0 );



    glutMainLoop();

	return 0;
}