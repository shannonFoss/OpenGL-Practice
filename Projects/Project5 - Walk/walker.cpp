/*
Shannon Foss
CECS 449
Project 5 - walker

keys: use s to rotate left, f to rotate right, e to look up, d to look down, arrow up to move forward,
arrow down to move backward, arrow left to strafe left, arrow right to strafe right. use x to return to
initial position.
note: if you look up or down, and then move forward you will walk in that direction (ie. float above
the ground, or pass through the ground. this is when the x key will come in handy)
*/
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#define PI 3.14159

float angle=0.0,angle2=0.0,ratio=1.0;
float upangle=0.0;
double object[3]={0.0,0.0,1.0};//line of sight
double viewer[3]={50.0,5.0,50.0};//camera pos
GLsizei winHeight = 500, winWidth = 500;

void makeHill(int grid[3][100][100],int ilow, int ihigh,int jlow, int jhigh){
	int i,j,count=1;
	bool breakout=true;
	while(breakout){
		for(i=ilow;i<=ihigh;i++){
			for(j=jlow;j<=jhigh;j++){
				grid[1][i][j]=count;
			}
		}
		if(ihigh-ilow<=0) breakout=false;
		ilow++;
		jlow++;
		ihigh--;
		jhigh--;
		count++;
	}
}
void mesh(){
	int grid[3][100][100];//x,y,z 
	int i,j;

	glColor4f(0.0,1.0,0.3,0.7);
	for(i=0;i<100;i++){
		for(j=0;j<100;j++){
			grid[0][i][j] = i;
			grid[1][i][j] = 0;
			grid[2][i][j] = j;
		}
	}
	makeHill(grid,60,65,50,55);
	makeHill(grid,55,63,70,78);
	makeHill(grid,45,49,23,27);
	makeHill(grid,15,25,72,82);
	makeHill(grid,63,69,63,69);
	makeHill(grid,68,76,68,76);

	for(i=0;i<99;i++){
		for(j=0;j<99;j++){
			glBegin(GL_LINE_LOOP);
				glVertex3i(grid[0][i][j],grid[1][i][j],grid[2][i][j]);
				glVertex3i(grid[0][i+1][j],grid[1][i+1][j],grid[2][i+1][j]);
				glVertex3i(grid[0][i+1][j+1],grid[1][i+1][j+1],grid[2][i+1][j+1]);
				glVertex3i(grid[0][i][j+1],grid[1][i][j+1],grid[2][i][j+1]);
			glEnd();
		}
	}
}
void makePyramid(int x,int z, int size){//size is even amts
	int hsize=size/2;
	glColor4f(0.0,0.0,0.0,1.0);
	glBegin(GL_POLYGON);//bot
		glVertex3i(x,1,z);
		glVertex3i(x+size, 1, z);
		glVertex3i(x+size,1,z+size);
		glVertex3i(x,1,z+size);
	glEnd();
	glColor4f(1.0,0.0,0.5,1.0);
	glBegin(GL_POLYGON);
		glVertex3i(x,1,z);
		glVertex3i(x+size,1,z);
		glVertex3i(x+hsize,size,z+hsize);
	glEnd();
	glColor4f(1.0,0.0,0.0,1.0);
	glBegin(GL_POLYGON);
		glVertex3i(x+size,1,z);
		glVertex3i(x+size,1,z+size);
		glVertex3i(x+hsize,size,z+hsize);
	glEnd();
	glColor4f(1.0,0.0,0.5,1.0);
	glBegin(GL_POLYGON);
		glVertex3i(x+size,1,z+size);
		glVertex3i(x,1,z+size);
		glVertex3i(x+hsize,size,z+hsize);
	glEnd();
	glColor4f(1.0,0.0,0.0,1.0);
	glBegin(GL_POLYGON);
		glVertex3i(x,1,z+size);
		glVertex3i(x,1,z);
		glVertex3i(x+hsize,size,z+hsize);
	glEnd();
}

void makeCube(int x, int z, int size){
	glColor4f(0.0,0.0,0.0,1.0);
	glBegin(GL_POLYGON);//bot
		glVertex3i(x,1,z);
		glVertex3i(x+size, 1, z);
		glVertex3i(x+size,1,z+size);
		glVertex3i(x,1,z+size);
	glEnd();
	glColor4f(0.0,0.0,0.0,1.0);
	glBegin(GL_POLYGON);//top
		glVertex3i(x,size+1,z);
		glVertex3i(x+size, size+1, z);
		glVertex3i(x+size,size+1,z+size);
		glVertex3i(x,size+1,z+size);
	glEnd();	
	glColor4f(1.0,1.0,1.0,1.0);	
	glBegin(GL_POLYGON);//side
		glVertex3i(x,1,z);
		glVertex3i(x+size, 1, z);
		glVertex3i(x+size,size+1,z);
		glVertex3i(x,size+1,z);
	glEnd();	
	glColor4f(0.5,0.5,0.5,1.0);
	glBegin(GL_POLYGON);//side
		glVertex3i(x,1,z);
		glVertex3i(x, size+1, z);
		glVertex3i(x,size+1,z+size);
		glVertex3i(x,1,z+size);
	glEnd();	
	glColor4f(0.5,0.5,0.5,1.0);
	glBegin(GL_POLYGON);
		glVertex3i(x+size,1,z);
		glVertex3i(x+size, size+1, z);
		glVertex3i(x+size,size+1,z+size);
		glVertex3i(x+size,1,z+size);
	glEnd();
	glColor4f(1.0,1.0,1.0,1.0);	
	glBegin(GL_POLYGON);
		glVertex3i(x,1,z+size);
		glVertex3i(x+size, 1, z+size);
		glVertex3i(x+size,size+1,z+size);
		glVertex3i(x,size+1,z+size);
	glEnd();

}
void makeSphere(int x, int z, int radius){
	float c = PI/180.0;
	float theta,thetar,phi,phir,phir20;
	float xx,yy,zz;
	for(phi=-80.0;phi<=80.0;phi+=20.0){
		phir=c*phi;
		phir20=c*(phi+20);
		glBegin(GL_QUAD_STRIP);
		for(theta=-180.0;theta<=180.0;theta+=20.0){
			thetar=c*theta;
			xx=sin(thetar)*cos(phir);
			zz=cos(thetar)*cos(phir);
			yy=sin(phir);
			glVertex3f(xx,yy,zz);
			xx=sin(thetar)*cos(phir20);
			zz=cos(thetar)*cos(phir20);
			yy=sin(phir20);
			glVertex3f(xx,yy,zz);
		}
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
			glVertex3i(x,1,z);
			zz=sin(c*80.0);
			for(theta=-180.0;theta<=180.0;theta+=20.0){
				thetar=c*theta;
				xx=sin(thetar)*cos(c*80.0);
				zz=cos(thetar)*cos(c*80.0);
				glVertex3d(xx,yy,zz);
			}
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
			glVertex3i(x,-1,z);
			zz=sin(c*80.0);
			for(theta=-180.0;theta<=180.0;theta+=20.0){
				thetar=c*theta;
				xx=sin(thetar)*cos(c*80.0);
				zz=cos(thetar)*cos(c*80.0);
				glVertex3d(xx,yy,zz);
			}
		glEnd();
	}
}
void resize(int w, int h){

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0) h = 1;

	ratio = 1.0 * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(45,ratio,1,100);
	glMatrixMode(GL_MODELVIEW);
	winWidth=w;
	winHeight=h;
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewer[0],viewer[1],viewer[2],viewer[0]+object[0],viewer[1]+object[1],viewer[2]+object[2],0.0,1.0,0.0);
	//draw objects
	mesh();
	makeCube(25,25,3);
	makePyramid(75,20,4);
	makePyramid(50,40,6);
	//makeSphere(75,75,3);
	glutSwapBuffers();
}
void keyb(unsigned char key, int x, int y){
	if(key=='s'){//pivot left
		angle += 0.1;
		object[0] = sin(angle);
		object[2] = cos(angle);
		glLoadIdentity();
		gluLookAt(viewer[0],viewer[1],viewer[2],viewer[0]+object[0], viewer[1]+object[1],viewer[2]+object[2],0.0,1.0,0.0);
		glutPostRedisplay();
	}
	if(key=='f'){//pivot right
		angle -= 0.1;
		object[0] = sin(angle);
		object[2] = cos(angle);
		glLoadIdentity();
		gluLookAt(viewer[0],viewer[1],viewer[2], viewer[0]+object[0],viewer[1]+object[1],viewer[2]+object[2],0.0,1.0,0.0);
		glutPostRedisplay();
	}
	if(key=='e'){//pivot upwards
		upangle += 0.1;
		object[1] = sin(upangle);
		glLoadIdentity();
		gluLookAt(viewer[0],viewer[1],viewer[2], viewer[0]+object[0],viewer[1]+object[1],viewer[2]+object[2],0.0,1.0,0.0);
		glutPostRedisplay();
	}
	if(key=='d'){//pivot downward
		upangle -= 0.1;
		object[1] = sin(upangle);
		glLoadIdentity();
		gluLookAt(viewer[0],viewer[1],viewer[2], viewer[0]+object[0],viewer[1]+object[1],viewer[2]+object[2],0.0,1.0,0.0);
		glutPostRedisplay();
	}
	if(key=='x'){//escape key
		angle = 0.0;
		angle2= 0.0;
		upangle=0.0;
		object[0]=0.0;
		object[1]=0.0;
		object[2]=1.0;
		viewer[0]=50.0;
		viewer[1]=5.0;
		viewer[2]=50.0;
		glLoadIdentity();
		gluLookAt(viewer[0],viewer[1],viewer[2], viewer[0]+object[0],viewer[1]+object[1],viewer[2]+object[2],0.0,1.0,0.0);
		glutPostRedisplay();
	}
}
void key(int key, int x, int y) {
	if(key==GLUT_KEY_RIGHT){//strafe right
		angle2 = angle- 1.5;
		viewer[0] += sin(angle2);
		viewer[1] += sin(upangle);
		viewer[2] += cos(angle2);
		glLoadIdentity();
		gluLookAt(viewer[0],viewer[1],viewer[2],object[0],object[1],object[2],0.0,1.0,0.0);
		glutPostRedisplay();
	}
	if(key==GLUT_KEY_LEFT){//strafe left
		angle2 = angle+ 1.5;
		viewer[0] += sin(angle2);
		viewer[1] += sin(upangle);
		viewer[2] += cos(angle2);
		glLoadIdentity();
		gluLookAt(viewer[0],viewer[1],viewer[2],object[0],object[1],object[2],0.0,1.0,0.0);
		glutPostRedisplay();
	}
	if(key==GLUT_KEY_DOWN){//move backward
		viewer[0] -= sin(angle);
		viewer[1] -= sin(upangle);
		viewer[2] -= cos(angle);
		glLoadIdentity();
		gluLookAt(viewer[0],viewer[1],viewer[2],viewer[0]+object[0],viewer[1]+object[1],viewer[2]+object[2],0.0,1.0,0.0);
		glutPostRedisplay();
	}
	if(key==GLUT_KEY_UP){//move forward
		viewer[0] += sin(angle);
		viewer[1] += sin(upangle);
		viewer[2] += cos(angle);
		glLoadIdentity();
		gluLookAt(viewer[0], viewer[1], viewer[2],viewer[0]+object[0],viewer[1]+object[1],viewer[2]+object[2],0.0,1.0,0.0); 
		glutPostRedisplay();
	}
}
void mouse(int btn, int state, int x, int y){

}

int main(int argc, char **argv){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Walker");
	glutReshapeFunc(resize);
    glutDisplayFunc(display);	
	glutKeyboardFunc(keyb);
	glutSpecialFunc(key);
    glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal */
    glutMainLoop();
}
