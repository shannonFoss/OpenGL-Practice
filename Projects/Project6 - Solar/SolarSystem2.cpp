/****************************************************
 *File: SolarSystem.cpp                             *
 *Desc: Program that displays a mini solar system.  *
 *      -sun = cube with texture maps on each side. *
 *      -earth = shaded sphere w/specular highlight *
 *      -moon = object with multiple sides, w/diff  *
 *      materials on each side.                     *
 *      -each rotates on an axis and moon revolves  *
 *      around the earth, and earth around the sun  *
 *      -use perspective view.                      *
 *                                                  *
 *Auth: Shannon Foss                                *
 *	    CECS 449                                    *
 *      Project #6 - solar system                   *
 ****************************************************
 note: need to change picture file locations to match (lines 255-260)
 */
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#define PI 3.14159

GLfloat SunTheta[3] = {0.0,0.0,0.0};
GLfloat PlanetTheta[3] = {0.0,0.0,0.0};
GLfloat MoonTheta[3] = {0.0,0.0,0.0};
int imageSize = 256;
int row,col;
GLuint *image1,*image2,*image3,*image4,*image5,*image6;

GLfloat light_ambient[]= {0.3f, 0.3f, 0.3f, 1.0f };
GLfloat light_diffuse[]= { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat light_specular[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_position[]= {0.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat_ambient[]= { 0.5, 0.5f, 0.5f, 1.0f };
GLfloat mat_diffuse[]= { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular[]= {0.6f, 0.6f, 0.6f, 0.9f };
GLfloat mat_shininess[]= { 0.7f };
GLfloat mat_ambient1[]= { 0.0, 0.0f, 0.5f, 1.0f };
GLfloat mat_diffuse1[]= { 0.0f, 0.0f, 0.8f, 1.0f };
GLfloat mat_specular1[]= {0.0f, 0.0f, 0.6f, 0.9f };
GLfloat mat_shininess1[]= { 0.7f };
GLfloat mat_ambient2[]= { 0.0, 0.5f, 0.0f, 1.0f };
GLfloat mat_diffuse2[]= { 0.0f, 0.8f, 0.0f, 1.0f };
GLfloat mat_specular2[]= {0.0f, 0.6f, 0.0f, 0.9f };
GLfloat mat_shininess2[]= { 0.7f };
GLfloat mat_ambient3[]= { 0.5, 0.0f, 0.0f, 1.0f };
GLfloat mat_diffuse3[]= { 0.8f, 0.0f, 0.0f, 1.0f };
GLfloat mat_specular3[]= {0.6f, 0.0f, 0.0f, 0.9f };
GLfloat mat_shininess3[]= { 0.7f };
GLfloat mat_ambient4[]= { 0.0, 0.5f, 0.5f, 1.0f };
GLfloat mat_diffuse4[]= { 0.0f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular4[]= {0.0f, 0.6f, 0.6f, 0.9f };
GLfloat mat_shininess4[]= { 0.7f };


void moon(){
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0,0.0,1.0);
		glNormal3f(1,0,-0.5);
		glVertex3f(-0.5,-0.5,0.0);
		glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient1);
		glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse1);
		glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular1);
		glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess1);
		glNormal3f(0,-1,-0.5);
		glVertex3f(0.5,-0.5,0.0);	
		glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient2);
		glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse2);
		glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular2);
		glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess2);
		glNormal3f(-1,0,-0.5);
		glVertex3f(0.5,0.5,0.0);	
		glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient3);
		glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse3);
		glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular3);
		glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess3);
		glNormal3f(0.0,1.0,-0.5);
		glVertex3f(-0.5,0.5,0.0);
	glEnd();
	glBegin(GL_QUADS);
		glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient4);
		glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse4);
		glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular4);
		glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess4);
		glNormal3f(0.0,0.0,-1.0);
		glVertex3f(-0.5,-0.5,0.0);
		glVertex3f(0.5,-0.5,0.0);
		glVertex3f(0.5,0.5,0.0);
		glVertex3f(-0.5,0.5,0.0);
	glEnd();

	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);
}
void planet(double r, int latitude, int longitude){
	for(int i=0; i <=latitude; i++) {
		float lati = PI * (-0.5 + (float)(i - 1)/ latitude);
		float z0  =sin(lati);
		float zr0 =cos(lati);

		float latj = PI * (-0.5 + (float)i/ latitude);
		float z1 =sin(latj);
		float zr1 =cos(latj);

		glBegin(GL_QUAD_STRIP);
		for(int j=0; j <=longitude; j++){
			float longi = 2 * PI * (float)(j - 1)/ longitude;
			float x =cos(longi);
			float y =sin(longi);

			glNormal3f(x*zr0, y*zr0, z0);
			glVertex3f(x*zr0, y*zr0, z0);
			glNormal3f(x*zr1, y*zr1, z1);
			glVertex3f(x*zr1, y*zr1, z1);
		}
		glEnd();
	}
}
void cube(){

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imageSize,imageSize,0,GL_RGB,GL_UNSIGNED_INT, image1);
	glBegin(GL_QUADS);//Bottom//good
		glTexCoord2f(0.0,0.0);
		glVertex3f(-1.0,1.0,1.0);
		glTexCoord2f(1.0,0.0);
		glVertex3f(-1.0,-1.0,1.0);
		glTexCoord2f(1.0,1.0);
		glVertex3f(-1.0,-1.0,-1.0);
		glTexCoord2f(0.0,1.0);
		glVertex3f(-1.0,1.0,-1.0);
	glEnd();
	
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imageSize,imageSize,0,GL_RGB,GL_UNSIGNED_INT, image2);
	glBegin(GL_QUADS);//Front
		glTexCoord2f(0.0,0.0);
		glVertex3f(1.0,1.0,1.0);
		glTexCoord2f(1.0,0.0);
		glVertex3f(1.0,-1.0,1.0);
		glTexCoord2f(1.0,1.0);
		glVertex3f(-1.0,-1.0,1.0);
		glTexCoord2f(0.0,1.0);
		glVertex3f(-1.0,1.0,1.0);
	glEnd();


	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imageSize,imageSize,0,GL_RGB,GL_UNSIGNED_INT, image3);
	glBegin(GL_QUADS);//right//good
		glTexCoord2f(0.0,0.0);
		glVertex3f(1.0,-1.0,1.0);
		glTexCoord2f(1.0,0.0);
		glVertex3f(1.0,-1.0,-1.0);
		glTexCoord2f(1.0,1.0);
		glVertex3f(-1.0,-1.0,-1.0);
		glTexCoord2f(0.0,1.0);
		glVertex3f(-1.0,-1.0,1.0);
	glEnd();
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imageSize,imageSize,0,GL_RGB,GL_UNSIGNED_INT, image4);
	glBegin(GL_QUADS);//Back
		glTexCoord2f(0.0,0.0);
		glVertex3f(1.0,-1.0,-1.0);
		glTexCoord2f(1.0,0.0);
		glVertex3f(1.0,1.0,-1.0);
		glTexCoord2f(1.0,1.0);
		glVertex3f(-1.0,1.0,-1.0);
		glTexCoord2f(0.0,1.0);
		glVertex3f(-1.0,-1.0,-1.0);
	glEnd();
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imageSize,imageSize,0,GL_RGB,GL_UNSIGNED_INT, image5);
	glBegin(GL_QUADS);//left//good
		glTexCoord2f(0.0,0.0);
		glVertex3f(1.0,1.0,-1.0);
		glTexCoord2f(1.0,0.0);
		glVertex3f(1.0,1.0,1.0);
		glTexCoord2f(1.0,1.0);
		glVertex3f(-1.0,1.0,1.0);
		glTexCoord2f(0.0,1.0);
		glVertex3f(-1.0,1.0,-1.0);
	glEnd();
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imageSize,imageSize,0,GL_RGB,GL_UNSIGNED_INT, image6);
	glBegin(GL_QUADS);//Top
		glTexCoord2f(0.0,0.0);
		glVertex3f(1.0,1.0,-1.0);
		glTexCoord2f(1.0,0.0);
		glVertex3f(1.0,-1.0,-1.0);
		glTexCoord2f(1.0,1.0);
		glVertex3f(1.0,-1.0,1.0);
		glTexCoord2f(0.0,1.0);
		glVertex3f(1.0,1.0,1.0);
	glEnd();
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(SunTheta[0],1.0,0.0,0.0);//rotates sun
	glScalef(2.0,2.0,2.0);
	cube();
	glShadeModel(GL_SMOOTH);
	glTranslatef(0.0,8.0,0.0);
	glRotatef(PlanetTheta[0],1.0,0.0,0.0);//rotates planet
	planet(1.0, 20,20);
	glRotatef(MoonTheta[0],1.0,0.0,0.0);//rotation around planet
	glTranslatef(0.0,3.0,0.0);
	glRotatef(MoonTheta[0],0.0,0.0,1.0);//rotates moon
	moon();

	glFlush();
	glutSwapBuffers();
}
void init(){
	glClearColor(0,0,0,1);
	glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv (GL_LIGHT1, GL_POSITION, light_position);
	glEnable (GL_LIGHT1);
	glEnable (GL_LIGHTING);
	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,1000,1000);
	gluPerspective(45,1,1,100);
	gluLookAt(30,30,40,0,0,0,1,0,0);
	glMatrixMode(GL_MODELVIEW);
}
void idle(){
	for(int i=0;i<3;i++){
		SunTheta[i] += 1.0;
		if( SunTheta[i] > 360.0 ) SunTheta[i] -= 360.0;	
		PlanetTheta[i] +=0.5;
		if(PlanetTheta[i]>360.0) PlanetTheta[i] -=360;
		MoonTheta[i] +=3.0;
		if(MoonTheta[i]>360.0) MoonTheta[i] -=360;
	}
	Sleep(25);
	glutPostRedisplay();
}
int main(int argc, char **argv){
	FILE *f1,*f2,*f3,*f4,*f5,*f6;
	int i,j,k;
	char b[100];
	float s;
	int red, green, blue;
	int rowOffset(0),colOffset(0);
	f1 = fopen("C:\\Documents and Settings\\Shannon Foss\\Desktop\\sunPics\\kitten1.ppm", "r");
	f2 = fopen("C:\\Documents and Settings\\Shannon Foss\\Desktop\\sunPics\\kitten2.ppm", "r");
	f3 = fopen("C:\\Documents and Settings\\Shannon Foss\\Desktop\\sunPics\\kitten3.ppm", "r");
	f4 = fopen("C:\\Documents and Settings\\Shannon Foss\\Desktop\\sunPics\\kitten4.ppm", "r");
	f5 = fopen("C:\\Documents and Settings\\Shannon Foss\\Desktop\\sunPics\\kitten5.ppm", "r");
	f6 = fopen("C:\\Documents and Settings\\Shannon Foss\\Desktop\\sunPics\\kitten6.ppm", "r");
	fscanf(f1,"%s",b);
	fscanf(f1,"%d %d", &col, &row);
	fscanf(f1,"%d", &k);	
	fscanf(f2,"%s",b);
	fscanf(f2,"%d %d", &col, &row);
	fscanf(f2,"%d", &k);	
	fscanf(f3,"%s",b);
	fscanf(f3,"%d %d", &col, &row);
	fscanf(f3,"%d", &k);
	fscanf(f4,"%s",b);
	fscanf(f4,"%d %d", &col, &row);
	fscanf(f4,"%d", &k);
	fscanf(f5,"%s",b);
	fscanf(f5,"%d %d", &col, &row);
	fscanf(f5,"%d", &k);
	fscanf(f6,"%s",b);
	fscanf(f6,"%d %d", &col, &row);
	fscanf(f6,"%d", &k);
	printf("File: %s %d cols %d rows %d maxv\n",b,col,row,k);
	image1=(GLuint *)malloc(3*sizeof(GLuint)*imageSize*imageSize);
	image2=(GLuint *)malloc(3*sizeof(GLuint)*imageSize*imageSize);
	image3=(GLuint *)malloc(3*sizeof(GLuint)*imageSize*imageSize);
	image4=(GLuint *)malloc(3*sizeof(GLuint)*imageSize*imageSize);
	image5=(GLuint *)malloc(3*sizeof(GLuint)*imageSize*imageSize);
	image6=(GLuint *)malloc(3*sizeof(GLuint)*imageSize*imageSize);
	s=255.0/k;
	rowOffset = (imageSize -row)/2;
	colOffset = (imageSize - col)/2;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			fscanf(f1, "%d %d %d",&red,&green,&blue);
			image1[imageSize*3*(i+rowOffset)+3*(j+colOffset)+0]=red;
			image1[imageSize*3*(i+rowOffset)+3*(j+colOffset)+1]=green;
			image1[imageSize*3*(i+rowOffset)+3*(j+colOffset)+2]=blue;
			fscanf(f2, "%d %d %d",&red,&green,&blue);
			image2[imageSize*3*(i+rowOffset)+3*(j+colOffset)+0]=red;
			image2[imageSize*3*(i+rowOffset)+3*(j+colOffset)+1]=green;
			image2[imageSize*3*(i+rowOffset)+3*(j+colOffset)+2]=blue;
			fscanf(f3, "%d %d %d",&red,&green,&blue);
			image3[imageSize*3*(i+rowOffset)+3*(j+colOffset)+0]=red;
			image3[imageSize*3*(i+rowOffset)+3*(j+colOffset)+1]=green;
			image3[imageSize*3*(i+rowOffset)+3*(j+colOffset)+2]=blue;
			fscanf(f4, "%d %d %d",&red,&green,&blue);
			image4[imageSize*3*(i+rowOffset)+3*(j+colOffset)+0]=red;
			image4[imageSize*3*(i+rowOffset)+3*(j+colOffset)+1]=green;
			image4[imageSize*3*(i+rowOffset)+3*(j+colOffset)+2]=blue;
			fscanf(f5, "%d %d %d",&red,&green,&blue);
			image5[imageSize*3*(i+rowOffset)+3*(j+colOffset)+0]=red;
			image5[imageSize*3*(i+rowOffset)+3*(j+colOffset)+1]=green;
			image5[imageSize*3*(i+rowOffset)+3*(j+colOffset)+2]=blue;
			fscanf(f6, "%d %d %d",&red,&green,&blue);
			image6[imageSize*3*(i+rowOffset)+3*(j+colOffset)+0]=red;
			image6[imageSize*3*(i+rowOffset)+3*(j+colOffset)+1]=green;
			image6[imageSize*3*(i+rowOffset)+3*(j+colOffset)+2]=blue;
		}
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000,1000);
	glutCreateWindow("Solar System");
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glPixelStorei(GL_UNPACK_SWAP_BYTES,GL_TRUE);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	init();
	glutMainLoop();
}