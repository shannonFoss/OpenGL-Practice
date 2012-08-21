/* 
Shannon Foss
CECS 449 
Project #2 - paint prog
keys: b = blue, r = red, g = green, c = cyan, m = magenta, y = yellow, w = white, l = black, f = toggles fill.
mouse: right click = exit or clear screen, left click = point choices, 2 points for circle, 3 for triangle, 2 for square...
simple painting program with text, lines, triangles,
rectangles, and points */
/*
1. fix rectangle on toolbar
2. pixel color
3. circle shape and add to toolbar
4. continuous line, click makes new point, double click ends
5. draw control points when making shapes
6. add keyboard shortcuts for colors
7. make toolbar better, make the selected shape stand out
8. selected shape should show color that will be drawn
*/

#define NULL 0
#define LINE 1
#define RECTANGLE 2
#define TRIANGLE 3
#define POINTS 4
#define TEXT 5
#define CIRCLE 6
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h> //for sin n cos
  
void mouse(int, int, int, int);
void key(unsigned char, int, int);
void display();
void drawSquare(int, int);
void myReshape(GLsizei, GLsizei);
void circle(float,int,int);
void myinit();
void labels();
void screen_box(int, int, int);
void right_menu(int);
void middle_menu(int);
void color_menu(int);
void pixel_menu(int);
void fill_menu(int);
int pick(int, int);

/* globals */

GLsizei wh = 500, ww = 500; /* initial window size */
GLfloat size = 3.0;   /* half side length of square */
int draw_mode = 0; /* drawing mode */
int rx, ry; /*raster position*/
const float DEG2RAD = 3.14159265/180;
GLfloat r = 1.0, g = 1.0, b = 1.0; /* drawing color */
int fill = 0; /* fill flag */

void drawSquare(int x, int y){
    y=wh-y;
    glBegin(GL_POLYGON);
            glVertex2f(x+size, y+size);
            glVertex2f(x-size, y+size);
            glVertex2f(x-size, y-size);
            glVertex2f(x+size, y-size);
    glEnd();
}

void circle(float radius, int cx, int cy){
	int i;
	glLineWidth(1.0);
	glBegin(GL_POLYGON);
		for(i=0; i<360; i++){	
			float degInRad = i*DEG2RAD;
			glVertex2f(cos(degInRad)*radius+cx,sin(degInRad)*radius+cy);
		}
	glEnd();
}

/* reshaping routine called whenever window is resized or moved */
void myReshape(GLsizei w, GLsizei h){
/* adjust clipping box */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

/* adjust viewport and clear */
    glViewport(0,0,w,h);
    glClearColor (0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    display();
    glFlush();

/* set global size for use by drawing routine */
    ww = w;
    wh = h;
}

void myinit(){
	glViewport(0,0,ww,wh);

/* Pick 2D clipping window to match size of X window. This choice
avoids having to scale object coordinates each time window is
resized. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble) ww , 0.0, (GLdouble) wh , -1.0, 1.0);

/* set clear color to black and clear window */
    glClearColor (0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void mouse(int btn, int state, int x, int y){
    static int count;
    int where;
    static int xp[2],yp[2];
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
       glPushAttrib(GL_ALL_ATTRIB_BITS);
       where = pick(x,y);
       glColor3f(r, g, b);
       if(where != 0)
       {
          count = 0;
          draw_mode = where;
       }
       else switch(draw_mode)
       {
         case(LINE):
          if(count==0){
			  glBegin(GL_POINTS);
				glVertex2i(x,wh-y);
			  glEnd();
              count++;
              xp[0] = x;
              yp[0] = y;
          }
          else{
			  if(xp[0]==x && yp[0]==y){
				  draw_mode=0;
				  count=0;
				  glColor3f(0.0,0.0,0.0);
				  labels();
			  }else{
				glBegin(GL_LINES);
                 glVertex2i(x,wh-y);
                 glVertex2i(xp[0],wh-yp[0]);
				glEnd();
				xp[0]=x;
				yp[0]=y;
			  }
          }
          break;
		 case(RECTANGLE):
			if(count == 0){
			  glBegin(GL_POINTS);
				glVertex2i(x,wh-y);
			  glEnd();
              count++;
              xp[0] = x;
              yp[0] = y;
            }
            else{
              if(fill) glBegin(GL_POLYGON);
			  else glBegin(GL_LINE_LOOP);
                    glVertex2i(x,wh-y);
					glVertex2i(x,wh-yp[0]);
					glVertex2i(xp[0],wh-yp[0]);
					glVertex2i(xp[0],wh-y);
			 	   glEnd();
				   glColor3f(0.0,0.0,0.0);
				   labels();
				   draw_mode=0;
                   count=0;
			}
          break;
         case (TRIANGLE):
           switch(count){
            case(0):
			  glBegin(GL_POINTS);
				glVertex2i(x,wh-y);
			  glEnd();
              count++;
              xp[0] = x;
              yp[0] = y;
              break;
            case(1):
			  glBegin(GL_POINTS);
				glVertex2i(x,wh-y);
			  glEnd();
              count++;
              xp[1] = x;
              yp[1] = y;
              break;
            case(2):
              if(fill) glBegin(GL_POLYGON);
              else glBegin(GL_LINE_LOOP);
                 glVertex2i(xp[0],wh-yp[0]);
                 glVertex2i(xp[1],wh-yp[1]);
                 glVertex2i(x,wh-y);
                glEnd();
				glColor3f(0.0,0.0,0.0);
				labels();
                draw_mode=0;
                count=0;
           }
           break;
        case(POINTS):
          {
             drawSquare(x,y);
             count++;
          }
	      break;
		case(TEXT):
		{
			rx=x;
			ry=wh-y;
			glRasterPos2i(rx,ry);
			count=0;
		}
		case(CIRCLE):
			if(count == 0){
			  glBegin(GL_POINTS);
				glVertex2i(x,wh-y);
			  glEnd();
              count++;
              xp[0] = x;
              yp[0] = y;
            }
            else{
			  int i;
			  float radius;
			  radius = sqrt((x-xp[0])*(x-xp[0])+(y-yp[0])*(y-yp[0]));
              if(fill) glBegin(GL_POLYGON);
			  else glBegin(GL_LINE_LOOP);
				for(i=0; i<360; i++){	
					float degInRad = i*DEG2RAD;
					glVertex2f(cos(degInRad)*radius+xp[0],sin(degInRad)*radius+(wh-yp[0]));
				}
			 	glEnd();
				glColor3f(0.0,0.0,0.0);
				labels();
				draw_mode=0;
                count=0;
			}
          break;
       }
       glPopAttrib();
       glFlush();
     }
}

int pick(int x, int y)
{
    y = wh - y;
    if(y < wh-ww/10) return 0;
	else if(x < ww/10){
		glColor3f(0.6,0.6,0.6);
		labels();
		glColor3f(r,g,b);
		glBegin(GL_LINES);//line label
			glVertex2i(wh/40,wh-ww/20);
			glVertex2i(wh/40+ww/20,wh-ww/20);
		glEnd();
		return LINE;
	}
	else if(x < ww/5){ 
		glColor3f(0.6,0.6,0.6);
		labels();
		glColor3f(r,g,b);
		glBegin(GL_QUADS);//square label
			glVertex2i(2*ww/20+ww/40, wh-ww/20-ww/40);
			glVertex2i((2*ww/20+ww/40)+ww/20, wh-ww/20-ww/40);
			glVertex2i((2*ww/20+ww/40)+ww/20, (wh-ww/20-ww/40)+ww/20);
			glVertex2i(2*ww/20+ww/40, (wh-ww/20-ww/40)+ww/20);
		glEnd();
		return RECTANGLE;
	}
	else if(x < 3*ww/10){
		glColor3f(0.6,0.6,0.6);
		labels();
		glColor3f(r,g,b);    
		glBegin(GL_TRIANGLES);//triangle label
			glVertex2i(ww/5+ww/40,wh-ww/10+ww/40);
			glVertex2i(ww/5+ww/20,wh-ww/40);
			glVertex2i(ww/5+3*ww/40,wh-ww/10+ww/40);
		glEnd();
		return TRIANGLE;
	}
	else if(x < 2*ww/5){ 
		glColor3f(0.6,0.6,0.6);
		labels();
		glColor3f(r,g,b);
		glPointSize(3.0);
		glBegin(GL_POINTS);//point label
			glVertex2i(3*ww/10+ww/20, wh-ww/20);
		glEnd();
		return POINTS;
	}
	else if(x < ww/2){ 
		int shift=0;
		glColor3f(0.6,0.6,0.6);
		labels();
		glColor3f(r,g,b);
		glRasterPos2i(2*ww/5,wh-ww/20);//char label
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
		shift=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'A');
		glRasterPos2i(2*ww/5+shift,wh-ww/20);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'B');
		shift+=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'B');
		glRasterPos2i(2*ww/5+shift,wh-ww/20);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
		return TEXT;
		
	}
	else if(x < 3*ww/5){ 
		glColor3f(0.6,0.6,0.6);
		labels();
		glColor3f(r,g,b);
		circle(ww/40, 11*ww/20, wh-ww/20);//circle label
		return CIRCLE;
	}
    else return 0;
}

void screen_box(int x, int y, int s){
	glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_QUADS);
      glVertex2i(x, y);
      glVertex2i(x+s, y);
      glVertex2i(x+s, y+s);
      glVertex2i(x, y+s);
    glEnd();
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINES);
		glVertex2i(x,y);
		glVertex2i(x,y+s);
		glVertex2i(x,y);
		glVertex2i(x+s,y);
	glEnd();	
}
void labels(){
	int shift=0;
    glBegin(GL_LINES);//line label
       glVertex2i(wh/40,wh-ww/20);
       glVertex2i(wh/40+ww/20,wh-ww/20);
    glEnd();
	glBegin(GL_QUADS);//square label
      glVertex2i(2*ww/20+ww/40, wh-ww/20-ww/40);
      glVertex2i((2*ww/20+ww/40)+ww/20, wh-ww/20-ww/40);
      glVertex2i((2*ww/20+ww/40)+ww/20, (wh-ww/20-ww/40)+ww/20);
      glVertex2i(2*ww/20+ww/40, (wh-ww/20-ww/40)+ww/20);
    glEnd();
    glBegin(GL_TRIANGLES);//triangle label
       glVertex2i(ww/5+ww/40,wh-ww/10+ww/40);
       glVertex2i(ww/5+ww/20,wh-ww/40);
       glVertex2i(ww/5+3*ww/40,wh-ww/10+ww/40);
    glEnd();
    glPointSize(3.0);
    glBegin(GL_POINTS);//point label
       glVertex2i(3*ww/10+ww/20, wh-ww/20);
    glEnd();
    glRasterPos2i(2*ww/5,wh-ww/20);//char label
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
    shift=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'A');
    glRasterPos2i(2*ww/5+shift,wh-ww/20);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'B');
    shift+=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'B');
    glRasterPos2i(2*ww/5+shift,wh-ww/20);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	circle(ww/40, 11*ww/20, wh-ww/20);//circle label
    glFlush();
}
void right_menu(int id){
   if(id == 1) exit(0);
   else display();
}

void middle_menu(int id){

}

void color_menu(int id){
   if(id == 1) {r = 1.0; g = 0.0; b = 0.0;}
   else if(id == 2) {r = 0.0; g = 1.0; b = 0.0;}
   else if(id == 3) {r = 0.0; g = 0.0; b = 1.0;}
   else if(id == 4) {r = 0.0; g = 1.0; b = 1.0;}
   else if(id == 5) {r = 1.0; g = 0.0; b = 1.0;}
   else if(id == 6) {r = 1.0; g = 1.0; b = 0.0;}
   else if(id == 7) {r = 1.0; g = 1.0; b = 1.0;}
   else if(id == 8) {r = 0.0; g = 0.0; b = 0.0;}
}

void pixel_menu(int id){
   if (id == 1) size = 2 * size;
   else if (size > 1) size = size/2;
}

void fill_menu(int id){
   if (id == 1) fill = 1;
   else fill = 0;
}

void key(unsigned char k, int xx, int yy){
	if(draw_mode!=TEXT){
		if(k=='B' || k=='b'){//blue
			r=0.0;
			g=0.0;
			b=1.0;
		}else if(k=='R'||k=='r'){//red
			r=1.0;
			g=0.0;
			b=0.0;
		}else if(k=='G'||k=='g'){//green
			r=0.0;
			g=1.0;
			b=0.0;
		}else if(k=='C'||k=='c'){//cyan
			r=0.0;
			g=1.0;
			b=1.0;
		}else if(k=='M'||k=='m'){//magenta
			r=1.0;
			g=0.0;
			b=1.0;
		}else if(k=='Y'||k=='y'){//Yellow
			r=1.0;
			g=1.0;
			b=0.0;
		}else if(k=='W'||k=='w'){//white
			r=1.0;
			g=1.0;
			b=1.0;
		}else if(k=='L'||k=='l'){//black
			r=0.0;
			g=0.0;
			b=0.0;
		}else if(k=='F'||k=='f'){//fill
			if(fill==0){
				fill=1;
			}else{
				fill=0;
			}
		}
		return;
	}
   glColor3f(r,g,b);
   glRasterPos2i(rx,ry);
   glutBitmapCharacter(GLUT_BITMAP_9_BY_15, k);
 /*glutStrokeCharacter(GLUT_STROKE_ROMAN,i); */
   rx+=glutBitmapWidth(GLUT_BITMAP_9_BY_15,k);
}

void display(){
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glClearColor (0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    screen_box(0,wh-ww/10,ww/10);//line
    screen_box(ww/10,wh-ww/10,ww/10);//square
    screen_box(ww/5,wh-ww/10,ww/10);//triangle
    screen_box(3*ww/10,wh-ww/10,ww/10);//point
    screen_box(2*ww/5,wh-ww/10,ww/10);//char
	screen_box(5*ww/10,wh-ww/10,ww/10);//circle
    glColor3f(0.0, 0.0, 0.0);
    labels();
    glFlush();
    glPopAttrib();
}

int main(int argc, char** argv){
    int c_menu, p_menu, f_menu;
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Paint");
    glutDisplayFunc(display);
    c_menu = glutCreateMenu(color_menu);
    glutAddMenuEntry("Red",1);
    glutAddMenuEntry("Green",2);
    glutAddMenuEntry("Blue",3);
    glutAddMenuEntry("Cyan",4);
    glutAddMenuEntry("Magenta",5);
    glutAddMenuEntry("Yellow",6);
    glutAddMenuEntry("White",7);
    glutAddMenuEntry("Black",8);
    p_menu = glutCreateMenu(pixel_menu);
    glutAddMenuEntry("increase pixel size", 1);
    glutAddMenuEntry("decrease pixel size", 2);
    f_menu = glutCreateMenu(fill_menu);
    glutAddMenuEntry("fill on", 1);
    glutAddMenuEntry("fill off", 2);
    glutCreateMenu(right_menu);
    glutAddMenuEntry("quit",1);
    glutAddMenuEntry("clear",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutCreateMenu(middle_menu);
    glutAddSubMenu("Colors", c_menu);
    glutAddSubMenu("Pixel Size", p_menu);
    glutAddSubMenu("Fill", f_menu);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
    myinit ();
    glutReshapeFunc (myReshape);
    glutKeyboardFunc(key);
    glutMouseFunc (mouse);
    glutMainLoop();
}
