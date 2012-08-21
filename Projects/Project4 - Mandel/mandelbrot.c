/*
Shannon Foss
CECS 449
Proj #4 - mandelbrot set

notes: when run, you must input how many iterations you wish to run to calculate the mandelbrot set.
you must also choose whether you would like to see inside or outside the set.  colors will appear inside
the set if you choose a 1, or outside if you choose 0.   you must input these each time you zoom in on a 
part of the set (i think outside the set turns out prettier, orange colors tend to glow nicely against the
blue background.  inside the set will tend to have liquid metallic areas, especially when singling out blue).  

the display time increases as the number of iterations you input gets higher, a good display that is quick is 
100 iterations (maybe 5 seconds at most),1000 iterations will look better but sometimes can take up to 30 seconds.

the program is somewhat odd when it comes to window focus,  it does not switch to the input screen when 
it prompts for input. 

mouse: left click and drag a square, then release to zoom in on area bounded by square, right click to zoom back out.
keys:  use r,g,b to toggle those colors (usually messes up background).
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
/* default data*/
/* can enter other values via command line arguments */

#define CENTERX -0.5
#define CENTERY 0.0
#define HEIGHT 2
#define WIDTH 2
#define MAX_ITER 100
#define PI 3.14159265

/* N x M array to be generated */

#define N 500//horizontal
#define M 500//vertical

struct Dimention {
	double height;
	double width;
	double cx;
	double cy;
	GLubyte image[N][M];
};
//double height = HEIGHT; /* size of window in complex plane */
//double width = WIDTH;
//double cx = CENTERX; /* center of window in complex plane */
//double cy = CENTERY;
int max = MAX_ITER; /* number of interations per point */
int n=N;
int m=M;
int ytemp1,ytemp2;
int xtemp1,xtemp2;
int boxCount;
int dimIter=0;
int redTog=1;
int greenTog=1;
int blueTog=1;
/* use unsigned bytes for image */

//GLubyte image[N][M];

/* complex data type and complex add, mult, and magnitude functions
   probably not worth overhead */

typedef double complex[2];
struct Dimention dimention[25];
float redmap[256], greenmap[256],bluemap[256];

void add(complex a, complex b, complex p)
{
    p[0]=a[0]+b[0];
    p[1]=a[1]+b[1];
}

void mult(complex a, complex b, complex p)
{
    p[0]=a[0]*b[0]-a[1]*b[1];
    p[1]=a[0]*b[1]+a[1]*b[0];
}

double mag2(complex a)
{
    return(a[0]*a[0]+a[1]*a[1]);
}

void form(double a, double b, complex p)
{
    p[0]=a;
    p[1]=b;
}
void makeImage(){
	int i, j, k;
    double x, y, v;
    complex c0, c, d;
	int choice;
/* uncomment to define your own parameters */
	printf("Input number of iterations: ");
	scanf("%d",&max); /* maximum iterations */
	printf("Input 1 for inside set, 0 for outside set: ");
	scanf("%i",&choice);
/*    scanf("%f", &cx); /* center x */
/*    scanf("%f", &cy); /* center y */
/*    scanf("%f", &width); /* rectangle width */
/*    height=width; /* rectangle height */

    for (i=0; i<n; i++) for(j=0; j<m; j++){
/* starting point */
		x= i *(dimention[dimIter].width/(n-1)) + dimention[dimIter].cx -dimention[dimIter].width/2;
		y= j *(dimention[dimIter].height/(m-1)) + dimention[dimIter].cy -dimention[dimIter].height/2;
		form(0,0,c);
		form(x,y,c0);

/* complex iteration */

		for(k=0; k<max; k++){
			mult(c,c,d);
			add(d,c0,c);
			v=mag2(c);
			if(v>4.0) break; /* assume not in set if mag > 4 */
		}

	/* assign gray level to point based on its magnitude */
			if(v>1.0) v=1.0; /* clamp if > 1 */
			if(choice==0){
                dimention[dimIter].image[j][i]=k*1.0*255/max;
			}else{
				dimention[dimIter].image[j][i] = 255*v;
			}
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(n,m,GL_COLOR_INDEX, GL_UNSIGNED_BYTE, dimention[dimIter].image);
	glFlush();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
    gluOrtho2D(0.0, (GLdouble) n, (GLdouble) n, (GLdouble) m* (GLdouble) h /(GLdouble) w);
    else
    gluOrtho2D(0.0, (GLdouble) n, (GLdouble) n * (GLdouble) w / (GLdouble) h,(GLdouble) m);
    glMatrixMode(GL_MODELVIEW);
}

void myinit()
{
    int i;
    glClearColor (0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0.0, (GLdouble) n, 0.0, (GLdouble) m);//(left, right,bottom,top)

// define pseudocolor maps, ramps for red blue green

    for(i=0;i<255;i++){
		//redmap[i]=(sin (PI/(i+1))+1)/2;//rings, not a large range of color,
		//redmap[i] = 1-i/255.0; //bright center dark top/bot
		//redmap[i] = i/255.0;//edges faint
		redmap[i] = 0.7*((i<128)?i/128.0: 1-(i-128)/128.0);//edges faint
		bluemap[i]=(i<128)?1-i/128.0: (i-128)/128.0;//filled center bright edges (red)
		greenmap[i]=(i<64)?1-(i+64)/128.0:((i<172)?(i-64)/128.0:1-(i-172)/128.0);//edges center 
		//redmap[i] = (i*i/ pow(1.1,i))/60;//rings and edges
		//redmap[i] = (0.0003259469*i*i-0.000001278223*i*i*i)/3.2;//edges and top/bot
		//redmap[i] = 0.0;
		//greenmap[i] = 0.0;
		//bluemap[i] = 0.0;
    }
    glPixelMapfv(GL_PIXEL_MAP_I_TO_B, 256, bluemap);
    glPixelMapfv(GL_PIXEL_MAP_I_TO_R, 256, redmap);
    glPixelMapfv(GL_PIXEL_MAP_I_TO_G, 256, greenmap);
}
void mouse(int btn, int state, int x, int y){
	y=m-y;
	if( btn==GLUT_LEFT_BUTTON){
		if(state==GLUT_DOWN){
			//zoom in
			xtemp1=x;
			xtemp2=x;
			ytemp1=y;
			boxCount=0;
		}else if(state == GLUT_UP && xtemp1!=xtemp2){
			double xptSize = dimention[dimIter].width/n;
			double yptSize = dimention[dimIter].height/m;
			double x1pos = (xtemp1 - 250.0)*xptSize+dimention[dimIter].cx;
			double y1pos = (ytemp1 - 250.0)*yptSize+dimention[dimIter].cy;
			double x2pos = (xtemp2 - 250.0)*xptSize+dimention[dimIter].cx;
			double y2pos = (ytemp2 - 250.0)*yptSize+dimention[dimIter].cy;

			dimention[dimIter+1].cx = (((xtemp2+xtemp1)/2)-250)*xptSize+dimention[dimIter].cx;
			dimention[dimIter+1].cy = (((ytemp2+ytemp1)/2)-250)*yptSize+dimention[dimIter].cy;

			dimention[dimIter+1].height= y2pos-y1pos;
			if(dimention[dimIter+1].height<0){
				dimention[dimIter+1].height = dimention[dimIter+1].height*-1.0;
			}
			dimention[dimIter+1].width = x2pos-x1pos;
			if(dimention[dimIter+1].width<0){
				dimention[dimIter+1].width= dimention[dimIter+1].width*-1.0;
			}
			dimIter++;
			makeImage();
			glDrawPixels(n,m,GL_COLOR_INDEX, GL_UNSIGNED_BYTE, dimention[dimIter].image);
			glFlush();
		}
	}
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		//zoom out
		if(dimIter-1>=0){
			//dimention[dimIter].height = dimention[dimIter-1].height;
			//dimention[dimIter].width = dimention[dimIter-1].width;
			//dimention[dimIter].cx = dimention[dimIter-1].cx;
			//dimention[dimIter].cy = dimention[dimIter-1].cy;
			dimIter--;
			//makeImage();
			glDrawPixels(n,m,GL_COLOR_INDEX, GL_UNSIGNED_BYTE, dimention[dimIter].image);
			glFlush();
		}
	}
}

void activeMouse(int x, int y){
	y =m-y;//rubba band
	if(x>xtemp1){
		if(y>ytemp1){
			if(x-xtemp1>y-ytemp1){
				y=ytemp1+(x-xtemp1);
			}else{
				x=xtemp1+(y-ytemp1);
			}
		}else{//y<ytemp1
			if(x-xtemp1>ytemp1-y){
				y=ytemp1-(x-xtemp1);
			}else{
				x=xtemp1+(ytemp1-y);
			}
		}
	}else{//x<xtemp1
		if(y>ytemp1){
			if(xtemp1-x>y-ytemp1){
				y=ytemp1+(xtemp1-x);
			}else{
				x=xtemp1-(y-ytemp1);
			}
		}else{//y<ytemp1
			if(xtemp1-x>ytemp1-y){
				y=ytemp1-(xtemp1-x);
			}else{
				x=xtemp1-(ytemp1-y);
			}
		}
	}
	if(boxCount==0){
		glEnable(GL_COLOR_LOGIC_OP);
		glLogicOp(GL_XOR);
		glColor4f(0.5,0.5,0.5,0.5);
		glBegin(GL_LINE_LOOP);
			glVertex2i(xtemp1,ytemp1);
			glVertex2i(xtemp1,y);
			glVertex2i(x,y);
			glVertex2i(x,ytemp1);
		glEnd();
		glFlush();
		glDisable(GL_COLOR_LOGIC_OP);
		xtemp2=x;
		ytemp2=y;
		boxCount++;
	}else{//erase old
		glEnable(GL_COLOR_LOGIC_OP);
		glLogicOp(GL_XOR);
		glColor4f(0.5,0.5,0.5,0.5);
		glBegin(GL_LINE_LOOP);
			glVertex2i(xtemp1,ytemp1);
			glVertex2i(xtemp1,ytemp2);
			glVertex2i(xtemp2,ytemp2);
			glVertex2i(xtemp2,ytemp1);
		glEnd();
		glFlush();
		glDisable(GL_COLOR_LOGIC_OP);
		//draw new
		glEnable(GL_COLOR_LOGIC_OP);
		glLogicOp(GL_XOR);
		glColor4f(0.5,0.5,0.5,0.5);
		glBegin(GL_LINE_LOOP);
			glVertex2i(xtemp1,ytemp1);
			glVertex2i(xtemp1,y);
			glVertex2i(x,y);
			glVertex2i(x,ytemp1);
		glEnd();
		glFlush();
		glDisable(GL_COLOR_LOGIC_OP);
		xtemp2=x;
		ytemp2=y;
	}
}
void key(unsigned char k, int xx, int yy){
	int i;
	if(k=='r'){
		if(redTog==1){
			for(i=0;i<256;i++){
				redmap[i] = 0.0;
			}
			redTog=0;
		}else{
			for(i=0;i<256;i++){
				redmap[i] = (i<128)?1-i/128.0: (i-128)/128.0;
			}
			redTog=1;
		}
	}
	if(k=='b'){
		if(blueTog==1){
			for(i=0;i<256;i++){
				bluemap[i] = 0.0;
			}
			blueTog=0;
		}else{
			for(i=0;i<256;i++){
				bluemap[i] = i/255.0;
			}
			blueTog=1;
		}
	}
	if(k=='g'){
		if(greenTog==1){
			for(i=0;i<256;i++){
				greenmap[i] = 0.0;
			}
			greenTog=0;
		}else{
			for(i=0;i<256;i++){
				greenmap[i] = (i<64)?1-(i+64)/128.0:((i<172)?(i-64)/128.0:1-(i-172)/128.0);
			}
			greenTog=1;
		}
	}
	glPixelMapfv(GL_PIXEL_MAP_I_TO_B, 256, bluemap);
    glPixelMapfv(GL_PIXEL_MAP_I_TO_R, 256, redmap);
    glPixelMapfv(GL_PIXEL_MAP_I_TO_G, 256, greenmap);
	glDrawPixels(n,m,GL_COLOR_INDEX, GL_UNSIGNED_BYTE, dimention[dimIter].image);
	glFlush();
}

main(int argc, char *argv[])
{
	dimention[dimIter].height = HEIGHT;
	dimention[dimIter].width = WIDTH;
	dimention[dimIter].cx = CENTERX;
	dimention[dimIter].cy = CENTERY;
	makeImage();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(N, M);
    glutCreateWindow("mandlebrot");
    myinit();
	glutMouseFunc(mouse);
	glutMotionFunc(activeMouse);
	glutKeyboardFunc(key);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);

    glutMainLoop();


}
