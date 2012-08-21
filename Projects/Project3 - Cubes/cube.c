//Shannon Foss
//CECS 449 - Graphics
//proj #3 - spinning cubes
/*
click on button to choose which cube to manipulate with keys
keys: l = left, r = right, u = up, d = down, i = in, o = out, + = enlarge, - = shrink, xyzXYZ for axis to spin around, +/- direction dependant on caps
*/
#include <stdlib.h>
#include <GL/glut.h>

GLfloat vertices[][3] = {{-1.0,-1.0,-1.0}, {-1.0,-1.0,1.0},
{-1.0,1.0,-1.0}, {-1.0,1.0,1.0}, {1.0,-1.0,-1.0},
{1.0,-1.0,1.0}, {1.0,1.0,-1.0}, {1.0,1.0,1.0}};

GLfloat colors[][3] = {{0.0,0.0,0.0},{1.0,0.0,0.0},
{1.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0},
{1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}};

static GLfloat theta1[] = {0.0,0.0,0.0};
static GLfloat theta2[] = {0.0,0.0,0.0};
static GLint axis1 = 2;
static GLint axis2 = 2;
GLsizei wh = 500, ww = 500;
GLfloat orthow=2.0, orthoh=2.0;
GLfloat dx1=1.5,dy1=0,dz1=0;
GLfloat dx2=-1.5,dy2=0,dz2=0;
//GLfloat rx1=1.0,ry1=1.0,rz1=1.0;
//GLfloat rx2=1.0,ry2=1.0,rz2=1.0;
int rotDir1 = 1;//pos
int rotDir2 = 1;
GLfloat scale1=1;
GLfloat scale2=1;
int pickCube =0;

void polygon(int a, int b, int c, int d){
/* draw a polygon via list of vertices */

 glBegin(GL_POLYGON);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
 glEnd();
}
void colorcube(){
/* map vertices to faces */
glColor3fv(colors[1]);
polygon(0,1,3,2);
glColor3fv(colors[3]);
polygon(4,5,7,6);
glColor3fv(colors[4]);
polygon(2,3,7,6);
glColor3fv(colors[2]);
polygon(0,1,5,4);
glColor3fv(colors[5]);
polygon(3,7,5,1);
glColor3fv(colors[7]);
polygon(2,6,4,0);
}
void label(){
 glColor3f(1.0,1.0,1.0);
 if(pickCube==0){
	//display cube1
	glRasterPos3f(-0.19,-1.6,0.1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
    glRasterPos3f(-0.12,-1.6,0.1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'u');
    glRasterPos3f(-0.05,-1.6,0.1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
    glRasterPos3f(0.02,-1.6,0.1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glRasterPos3f(0.07,-1.6,0.1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
    glRasterPos3f(0.12,-1.6,0.1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
 }else{
	//display cube2
	glRasterPos3f(-0.19,-1.6,0.1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
    glRasterPos3f(-0.12,-1.6,0.1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'u');
    glRasterPos3f(-0.05,-1.6,0.1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
    glRasterPos3f(0.02,-1.6,0.1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glRasterPos3f(0.07,-1.6,0.1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
    glRasterPos3f(0.12,-1.6,0.1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '2');
 }
}

void display(){
/* display callback, clear frame buffer and z buffer,
   rotate cube and draw, swap buffers */
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 glLoadIdentity();
 glTranslatef(dx1,dy1,dz1);
 glRotatef(theta1[0], 1.0, 0.0, 0.0);
 glRotatef(theta1[1], 0.0, 1.0, 0.0);
 glRotatef(theta1[2], 0.0, 0.0, 1.0);
 glScalef(scale1,scale1,scale1);
 colorcube();

 glLoadIdentity();
 glTranslatef(dx2,dy2,dz2);
 glRotatef(theta2[0], 1.0, 0.0, 0.0);
 glRotatef(theta2[1], 0.0, 1.0, 0.0);
 glRotatef(theta2[2], 0.0, 0.0, 1.0);
 glScalef(scale2,scale2,scale2);
 colorcube();

 glLoadIdentity();
 //button
 glColor3f(0.6,0.6,0.6);
 glBegin(GL_QUADS);
	glVertex2f(-0.2,-1.5);
	glVertex2f(0.2, -1.5);
	glVertex2f(0.2, -1.67);
	glVertex2f(-0.2, -1.67);
 glEnd();
 label();
 glFlush();
 glutSwapBuffers();
}

void spinCube(){
/* idle callback, spin cube 2 degrees about selected axis */
	//theta1[axis1] += 2.0;
	//if( theta1[axis1] > 360.0 ) theta1[axis1] -= 360.0;
	//theta2[axis2] += 2.0;
	//if( theta2[axis2] > 360.0 ) theta2[axis2] -= 360.0;
	if(rotDir1 ==1){//pos
		theta1[axis1] +=2.0;
		if( theta1[axis1] > 360.0 ) theta1[axis1] -= 360.0;
		if(rotDir2 ==1){
			theta2[axis2] += 2.0;
			if( theta2[axis2] > 360.0 ) theta2[axis2] -= 360.0;
		}else{
			theta2[axis2] -= 2.0;
			if( theta2[axis2] < 0.0 ) theta2[axis2] += 360.0;
		}
	}else{//neg
		theta1[axis1] -=2.0;
		if( theta1[axis1] < 0.0 ) theta1[axis1] += 360.0;
		if(rotDir2 ==1){
			theta2[axis2] += 2.0;
			if( theta2[axis2] > 360.0 ) theta2[axis2] -= 360.0;
		}else{
			theta2[axis2] -= 2.0;
			if( theta2[axis2] < 0.0 ) theta2[axis2] += 360.0;
		}
	}
 /* display(); */
 glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y){
/* mouse callback, selects an axis about which to rotate */
	y=wh-y;
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		int lowx=0,hix=0,lowy=0,hiy=0;
		if(ww<=wh){
			lowx = (ww/2-(0.2/2.0*(ww/2)));
			hix =  (ww/2+(0.2/2.0*(ww/2)));
			lowy = (wh/2-(1.5/orthoh*(wh/2)));
			hiy =  (wh/2-(1.67/orthoh*(wh/2)));
		}else{		
			lowx = (ww/2-(0.2/orthow*(ww/2)));
			hix =  (ww/2+(0.2/orthow*(ww/2)));
			lowy = (wh/2-(1.5/2.0*(wh/2)));
			hiy =  (wh/2-(1.67/2.0*(wh/2)));
		}
		if((x>=lowx && x<=hix)&&(y<=lowy && y>=hiy)){
			if(pickCube==0){
				pickCube=1;
			}else{
				pickCube=0;
			}
		}
	}
}
void key(unsigned char k, int xx, int yy){
	if(pickCube==0){//cube1
		if(k == 'R'||k == 'r'){
			dx1=dx1+ 0.1;
		}
		if(k == 'L'||k=='l'){
			dx1=dx1- 0.1;
		}
		if(k == 'U'||k=='u'){
			dy1=dy1+ 0.1;
		}
		if(k == 'D'||k=='d'){
			dy1=dy1- 0.1;
		}
		if(k == 'I'||k=='i'){
			dz1=dz1+ 0.1;
		}
		if(k == 'O'||k=='o'){
			dz1=dz1- 0.1;
		}
		if(k == '+'){
			scale1 = scale1 * 2;
		}
		if(k == '-'){
			scale1 = scale1 / 2;
		}
		if(k=='X'){
			rotDir1 = 1;
			axis1 = 0;
		}
		if(k=='x'){
			rotDir1 = 0;
			axis1 = 0;
		}
		if(k=='Y'){
			rotDir1 = 1;
			axis1 = 1;
		}
		if(k=='y'){
			rotDir1 = 0;
			axis1 = 1;
		}
		if(k=='Z'){
			rotDir1 = 1;
			axis1 = 2;
		}
		if(k=='z'){
			rotDir1 = 0;
			axis1 = 2;
		}
	}else{
		if(k == 'R'||k == 'r'){
			dx2=dx2+ 0.1;
		}
		if(k == 'L'||k=='l'){
			dx2=dx2- 0.1;
		}
		if(k == 'U'||k=='u'){
			dy2=dy2+ 0.1;
		}
		if(k == 'D'||k=='d'){
			dy2=dy2- 0.1;
		}
		if(k == 'I'||k=='i'){
			dz2=dz2+ 0.1;
		}
		if(k == 'O'||k=='o'){
			dz2=dz2- 0.1;
		}
		if(k == '+'){
			scale2 = scale2 * 2;
		}
		if(k == '-'){
			scale2 = scale2 / 2;
		}
		if(k=='X'){
			rotDir2 = 1;
			axis2 = 0;
		}
		if(k=='x'){
			rotDir2 = 0;
			axis2 = 0;
		}
		if(k=='Y'){
			rotDir2 = 1;
			axis2 = 1;
		}
		if(k=='y'){
			rotDir2 = 0;
			axis2 = 1;
		}
		if(k=='Z'){
			rotDir2 = 1;
			axis2 = 2;
		}
		if(k=='z'){
			rotDir2 = 0;
			axis2 = 2;
		}
	}
}

void myReshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	orthoh= 2.0 * (GLfloat) h / (GLfloat) w;
	orthow= 2.0 * (GLfloat) w / (GLfloat) h;
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,orthoh, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w /(GLfloat) h, orthow, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
	ww=w;
	wh=h;
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
	/* need both double buffering and z buffer */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(ww, wh);
    glutCreateWindow("colorcube");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(spinCube);
	glutKeyboardFunc(key);
    glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal */
    glutMainLoop();
}