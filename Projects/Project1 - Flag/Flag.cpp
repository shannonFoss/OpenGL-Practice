//Shannon Foss
//CECS 449
//Project 1 - draw a flag, display over 10 seconds
//September 20, 2006

#include <Windows.h>//for sleep
#include <GL/glut.h>
#include <math.h> //for sin n cos
  
const float DEG2RAD = 3.14159265/180;
int max = 600;
double maxd = 600.0;
 
void init(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, maxd, 0.0,maxd);
}
void grid(void){//draws a grid to make stuff easier
	glColor3f(1.0,0.0,0.0);
	glLineWidth(1.0);
	for(int i=0;i<max;i++){
		if(i%10 ==0){
			glBegin(GL_LINES);
				glVertex2i(0,i);
				glVertex2i(max,i);
				glVertex2i(i,0);
				glVertex2i(i,max);
			glEnd();		
		}
	}
}
void dot(float radius, int cx, int cy){//lil circles
	glColor3f(0.75,0.75,0.75);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);
		for (int i=0; i < 360; i++){	
			float degInRad = i*DEG2RAD;
			glVertex2f(cos(degInRad)*radius+cx,sin(degInRad)*radius+cy);
		}
	glEnd();
}
void circle(float radius, float thickness){//fixed circle
//x=rcos(t)y=rsin(t) t in rad
//silver = 192,192,192 (.75,.75,.75)
	glColor3f(.75,.75,.75);
	glLineWidth(thickness);
    glBegin(GL_LINE_LOOP); 
		for (int i=0; i < 360; i++){
			float degInRad = i*DEG2RAD;
			if(i!=45&&i!=135&&i!=225&&i!=315){
				glVertex2f(cos(degInRad)*radius+(max/2),sin(degInRad)*radius+(max/2));
			}
			else{
				int x,y;
				if(i==45){
					x=1;
					y=-1;
				}
				else if(i==135){
					x=-1;
					y=-1;
				}
				else if(i==225){
					x=-1;
					y=1;
				}
				else if(i==315){
					x=1;
					y=1;
				}
				for(int j=1; j<=thickness/2+2;j++){
					glVertex2f(cos(degInRad)*radius+(max/2)+x*j,sin(degInRad)*radius+(max/2)+y*j);
				}
			}
		}
    glEnd();
	//original circle
	//glBegin(GL_POINTS);
	//	glPointSize(50.0);
	//	glVertex2f(cos(DEG2RAD*45)*radius+(max/2),sin(DEG2RAD*45)*radius+(max/2));
	//glEnd();

}
void circle2(float radius, float thickness, float are, float gee, float bee){
//circle o' sweetness
//silver = 192,192,192 (.75,.75,.75)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	float scale=radius/100+thickness;
	glColor3f(are,gee,bee);
	glLineWidth(1);
    glBegin(GL_LINE_LOOP); 
		for (int i=0; i < 360*scale; i++){
			float degInRad = i/scale*DEG2RAD;
			glVertex2f(cos(degInRad)*radius+(max/2),sin(degInRad)*radius+(max/2));			
			glVertex2f(cos(degInRad)*(radius+thickness)+(max/2),sin(degInRad)*(radius+thickness)+(max/2));
		}
    glEnd();
}
void star(int cx, int cy, float height){//original star
	glColor3f(0.75,0.75,0.75);
	glLineWidth(1);
	glBegin(GL_LINES);
	//for(float i=0.0;i<3.14/2;i+=.001){
		for(float i=0.0,j=height;i<=height,j>=0;i=i+.5,j=j-.5){
			glVertex2f(cx+i,cy);//1st quad
			glVertex2f(cx,cy+j);			
			glVertex2f(cx-i,cy);//2nd quad
			glVertex2f(cx,cy+j);
			glVertex2f(cx+i,cy);//3rd quad
			glVertex2f(cx,cy-j);
			glVertex2f(cx-i,cy);//4th quad
			glVertex2f(cx,cy-j);
			//glVertex2f(cx+height/pow((1.6-abs(cos(i))),4),cy+height/pow((1.6-abs(sin(i))),4));
		}		
	glEnd();
}
void star1(int cx, int cy, float height){//cooler lookin star
	glColor3f(0.75,0.75,0.75);
	glLineWidth(1);
	glBegin(GL_LINES);
	float a=1.8;
	float i;
	//quad 1
	for(i=0.0;i<height;i+=0.001){
		glVertex2f(cx,cy+height-i);
		glVertex2f(cx+i/a,cy);
	}		
	glEnd();
	glBegin(GL_LINES);
	for(i=0.0;i<height;i+=0.001){
		glVertex2f(cx+height-i,cy);
		glVertex2f(cx,cy+i/a);
	}		
	glEnd();
	//quad 4
	glBegin(GL_LINES);
	for(i=0.0;i<height;i+=0.001){
		glVertex2f(cx,cy-(height-i));
		glVertex2f(cx+i/a,cy);
	}		
	glEnd();
	glBegin(GL_LINES);
	for(i=0.0;i<height;i+=0.001){
		glVertex2f(cx+height-i,cy);
		glVertex2f(cx,cy-i/a);
	}		
	glEnd();
	//quad 3
	glBegin(GL_LINES);
	for(i=0.0;i<height;i+=0.001){
		glVertex2f(cx,cy-(height-i));
		glVertex2f(cx-i/a,cy);
	}		
	glEnd();
	glBegin(GL_LINES);
	for(i=0.0;i<height;i+=0.001){
		glVertex2f(cx-(height-i),cy);
		glVertex2f(cx,cy-i/a);
	}		
	glEnd();
	//quad 2
		glBegin(GL_LINES);
	for(i=0.0;i<height;i+=0.001){
		glVertex2f(cx,cy+(height-i));
		glVertex2f(cx-i/a,cy);
	}		
	glEnd();
	glBegin(GL_LINES);
	for(i=0.0;i<height;i+=0.001){
		glVertex2f(cx-(height-i),cy);
		glVertex2f(cx,cy+i/a);
	}		
	glEnd();
}
void leafBase(int px, int py){
	int mirror = max/2;
	int disp = 2*(px-mirror);
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_POLYGON);
		glVertex2f(px, py);
		glVertex2f(px+15,py+15);
		glVertex2f(px+30,py+20);
		glVertex2f(px+65,py+25);
		glVertex2f(px+90,py+35);
		glVertex2f(px+87,py+25);
		glVertex2f(px+100,py+17);
		glVertex2f(px+30,py+10);
		glVertex2f(px+19,py+5);
		glVertex2f(px+25,py+2);
		glVertex2f(px+50,py);
		glVertex2f(px+40,py-10);
		glVertex2f(px+25,py-10);
	glEnd();
	glBegin(GL_POLYGON);//mirror
		glVertex2f(px-disp, py);
		glVertex2f(px-disp-15,py+15);
		glVertex2f(px-disp-30,py+20);
		glVertex2f(px-disp-65,py+25);
		glVertex2f(px-disp-90,py+35);
		glVertex2f(px-disp-87,py+25);
		glVertex2f(px-disp-100,py+17);
		glVertex2f(px-disp-30,py+10);
		glVertex2f(px-disp-19,py+5);
		glVertex2f(px-disp-25,py+2);
		glVertex2f(px-disp-50,py);
		glVertex2f(px-disp-40,py-10);
		glVertex2f(px-disp-25,py-10);
	glEnd();
}
void leafOne(int px, int py){
	int mirror = max/2;
	int disp = 2*(px-mirror);
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_POLYGON);
		glVertex2f(px-disp,py);
		glVertex2f(px-disp-3, py+10);
		glVertex2f(px-disp-5, py+20);
		glVertex2f(px-disp-8, py+30);
		glVertex2f(px-disp-17, py+41);
		glVertex2f(px-disp-18, py+20);
		glVertex2f(px-disp-20, py+15);
		glVertex2f(px-disp-60, py+16);
		glVertex2f(px-disp-55, py+10);
		glVertex2f(px-disp-50, py+7);
		glVertex2f(px-disp-40, py+2);
		glVertex2f(px-disp-30, py-1);
		glVertex2f(px-disp-20, py-4);
		glVertex2f(px-disp-10, py-5);
		glVertex2f(px-disp-5, py-4);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(px,py);
		glVertex2f(px+3, py+10);
		glVertex2f(px+5, py+20);
		glVertex2f(px+8, py+30);
		glVertex2f(px+17, py+41);
		glVertex2f(px+18, py+20);
		glVertex2f(px+20, py+15);
		glVertex2f(px+60, py+16);
		glVertex2f(px+55, py+10);
		glVertex2f(px+50, py+7);
		glVertex2f(px+40, py+2);
		glVertex2f(px+30, py-1);
		glVertex2f(px+20, py-4);
		glVertex2f(px+10, py-5);
		glVertex2f(px+5, py-4);
	glEnd();
}
void leafTwo(int px, int py){
	int mirror = max/2;
	int disp = 2*(px-mirror);
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_POLYGON);
		glVertex2f(px,py);
		glVertex2f(px-2,py+10);
		glVertex2f(px,py+20);
		glVertex2f(px+3,py+30);
		glVertex2f(px+5,py+40);
		glVertex2f(px+8,py+45);
		glVertex2f(px+9,py+40);
		glVertex2f(px+12,py+30);
		glVertex2f(px+17,py+19);
		glVertex2f(px+30,py+20);
		glVertex2f(px+50,py+23);
		glVertex2f(px+60,py+25);
		glVertex2f(px+50,py+13);
		glVertex2f(px+40,py+8);
		glVertex2f(px+30,py+4);
		glVertex2f(px+20,py+2);
		glVertex2f(px+10,py-2);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(px-disp,py);
		glVertex2f(px-disp+2,py+10);
		glVertex2f(px-disp,py+20);
		glVertex2f(px-disp-3,py+30);
		glVertex2f(px-disp-5,py+40);
		glVertex2f(px-disp-8,py+45);
		glVertex2f(px-disp-9,py+40);
		glVertex2f(px-disp-12,py+30);
		glVertex2f(px-disp-17,py+19);
		glVertex2f(px-disp-30,py+20);
		glVertex2f(px-disp-50,py+23);
		glVertex2f(px-disp-60,py+25);
		glVertex2f(px-disp-50,py+13);
		glVertex2f(px-disp-40,py+8);
		glVertex2f(px-disp-30,py+4);
		glVertex2f(px-disp-20,py+2);
		glVertex2f(px-disp-10,py-2);
	glEnd();
}
void leafThree(int px,int py){
	int mirror = max/2;
	int disp = 2*(px-mirror);
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_POLYGON);
		glVertex2f(px,py);
		glVertex2f(px-1,py+5);
		glVertex2f(px-1,py+25);
		glVertex2f(px,py+40);
		glVertex2f(px+2,py+47);
		glVertex2f(px+6,py+40);
		glVertex2f(px+10,py+30);
		glVertex2f(px+15,py+22);
		glVertex2f(px+20,py+22);
		glVertex2f(px+30,py+25);
		glVertex2f(px+40,py+30);
		glVertex2f(px+50,py+37);
		glVertex2f(px+60,py+45);
		glVertex2f(px+70,py+52);
		glVertex2f(px+65,py+40);
		glVertex2f(px+60,py+30);
		glVertex2f(px+50,py+20);
		glVertex2f(px+40,py+10);
		glVertex2f(px+30,py+7);
		glVertex2f(px+20,py+3);
		glVertex2f(px+10,py+1);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(px-disp,py);
		glVertex2f(px-disp+1,py+5);
		glVertex2f(px-disp+1,py+25);
		glVertex2f(px-disp,py+40);
		glVertex2f(px-disp-2,py+47);
		glVertex2f(px-disp-6,py+40);
		glVertex2f(px-disp-10,py+30);
		glVertex2f(px-disp-15,py+22);
		glVertex2f(px-disp-20,py+22);
		glVertex2f(px-disp-30,py+25);
		glVertex2f(px-disp-40,py+30);
		glVertex2f(px-disp-50,py+37);
		glVertex2f(px-disp-60,py+45);
		glVertex2f(px-disp-70,py+52);
		glVertex2f(px-disp-65,py+40);
		glVertex2f(px-disp-60,py+30);
		glVertex2f(px-disp-50,py+20);
		glVertex2f(px-disp-40,py+10);
		glVertex2f(px-disp-30,py+7);
		glVertex2f(px-disp-20,py+3);
		glVertex2f(px-disp-10,py+1);
	glEnd();
}
void leafFour(int px, int py){
	int mirror = max/2;
	int disp = 2*(px-mirror);
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_POLYGON);
		glVertex2f(px,py);
		glVertex2f(px-5,py+10);
		glVertex2f(px-8,py+20);
		glVertex2f(px-10,py+30);
		glVertex2f(px-11,py+40);
		glVertex2f(px-11,py+43);
		glVertex2f(px-5,py+40);
		glVertex2f(px-3,py+30);
		glVertex2f(px,py+25);
		glVertex2f(px+4,py+21);
		glVertex2f(px+10,py+24);
		glVertex2f(px+20,py+30);
		glVertex2f(px+30,py+40);
		glVertex2f(px+40,py+52);
		glVertex2f(px+50,py+65);
		glVertex2f(px+52,py+68);
		glVertex2f(px+51,py+60);
		glVertex2f(px+50,py+50);
		glVertex2f(px+48,py+40);
		glVertex2f(px+42,py+30);
		glVertex2f(px+33,py+20);
		glVertex2f(px+23,py+10);
		glVertex2f(px+20,py+7);
		glVertex2f(px+10,py+3);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(px-disp,py);
		glVertex2f(px-disp+5,py+10);
		glVertex2f(px-disp+8,py+20);
		glVertex2f(px-disp+10,py+30);
		glVertex2f(px-disp+11,py+40);
		glVertex2f(px-disp+11,py+43);
		glVertex2f(px-disp+5,py+40);
		glVertex2f(px-disp+3,py+30);
		glVertex2f(px-disp,py+25);
		glVertex2f(px-disp-4,py+21);
		glVertex2f(px-disp-10,py+24);
		glVertex2f(px-disp-20,py+30);
		glVertex2f(px-disp-30,py+40);
		glVertex2f(px-disp-40,py+52);
		glVertex2f(px-disp-50,py+65);
		glVertex2f(px-disp-52,py+68);
		glVertex2f(px-disp-51,py+60);
		glVertex2f(px-disp-50,py+50);
		glVertex2f(px-disp-48,py+40);
		glVertex2f(px-disp-42,py+30);
		glVertex2f(px-disp-33,py+20);
		glVertex2f(px-disp-23,py+10);
		glVertex2f(px-disp-20,py+7);
		glVertex2f(px-disp-10,py+3);
	glEnd();
}
void leafFive(int px, int py){
	int mirror = max/2;
	int disp = 2*(px-mirror);
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_POLYGON);
		glVertex2f(px,py);
		glVertex2f(px-9,py+10);
		glVertex2f(px-14,py+20);
		glVertex2f(px-17,py+30);
		glVertex2f(px-19,py+35);
		glVertex2f(px-10,py+30);
		glVertex2f(px,py+22);
		glVertex2f(px+10,py+30);
		glVertex2f(px+16,py+40);
		glVertex2f(px+22,py+50);
		glVertex2f(px+28,py+60);
		glVertex2f(px+33,py+70);
		glVertex2f(px+35,py+60);
		glVertex2f(px+35,py+50);
		glVertex2f(px+32,py+40);
		glVertex2f(px+28,py+30);
		glVertex2f(px+20,py+20);
		glVertex2f(px+13,py+10);
		glVertex2f(px+10,py+6);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(px-disp,py);
		glVertex2f(px-disp+9,py+10);
		glVertex2f(px-disp+14,py+20);
		glVertex2f(px-disp+17,py+30);
		glVertex2f(px-disp+19,py+35);
		glVertex2f(px-disp+10,py+30);
		glVertex2f(px-disp,py+22);
		glVertex2f(px-disp-10,py+30);
		glVertex2f(px-disp-16,py+40);
		glVertex2f(px-disp-22,py+50);
		glVertex2f(px-disp-28,py+60);
		glVertex2f(px-disp-33,py+70);
		glVertex2f(px-disp-35,py+60);
		glVertex2f(px-disp-35,py+50);
		glVertex2f(px-disp-32,py+40);
		glVertex2f(px-disp-28,py+30);
		glVertex2f(px-disp-20,py+20);
		glVertex2f(px-disp-13,py+10);
		glVertex2f(px-disp-10,py+6);
	glEnd();
}
void leafSix(int px, int py){
	int mirror = max/2;
	int disp = 2*(px-mirror);
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_POLYGON);
		glVertex2f(px,py);
		glVertex2f(px-10,py+9);
		glVertex2f(px-17,py+20);
		glVertex2f(px-21,py+30);
		glVertex2f(px-24,py+38);
		glVertex2f(px-12,py+30);
		glVertex2f(px-3,py+27);
		glVertex2f(px,py+30);
		glVertex2f(px+8,py+40);
		glVertex2f(px+11,py+50);
		glVertex2f(px+13,py+60);
		glVertex2f(px+15,py+71);
		glVertex2f(px+20,py+60);
		glVertex2f(px+21,py+50);
		glVertex2f(px+21,py+40);
		glVertex2f(px+17,py+30);
		glVertex2f(px+14,py+20);
		glVertex2f(px+9,py+10);
	glEnd();
	glBegin(GL_POLYGON);		
		glVertex2f(px-disp,py);
		glVertex2f(px-disp+10,py+9);
		glVertex2f(px-disp+17,py+20);
		glVertex2f(px-disp+21,py+30);
		glVertex2f(px-disp+24,py+38);
		glVertex2f(px-disp+12,py+30);
		glVertex2f(px-disp+3,py+27);
		glVertex2f(px-disp,py+30);
		glVertex2f(px-disp-8,py+40);
		glVertex2f(px-disp-11,py+50);
		glVertex2f(px-disp-13,py+60);
		glVertex2f(px-disp-15,py+71);
		glVertex2f(px-disp-20,py+60);
		glVertex2f(px-disp-21,py+50);
		glVertex2f(px-disp-21,py+40);
		glVertex2f(px-disp-17,py+30);
		glVertex2f(px-disp-14,py+20);
		glVertex2f(px-disp-9,py+10);
	glEnd();
}
void leafSeven(int px, int py){
	int mirror = max/2;
	int disp = 2*(px-mirror);
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_POLYGON);
		glVertex2f(px,py);
		glVertex2f(px-10,py+6);
		glVertex2f(px-20,py+16);
		glVertex2f(px-28,py+30);
		glVertex2f(px-20,py+27);
		glVertex2f(px-10,py+24);
		glVertex2f(px-7,py+23);
		glVertex2f(px-6,py+30);
		glVertex2f(px-4,py+40);
		glVertex2f(px-3,py+50);
		glVertex2f(px-3,py+62);
		glVertex2f(px+5,py+55);
		glVertex2f(px+8,py+40);
		glVertex2f(px+9,py+30);
		glVertex2f(px+8,py+20);
		glVertex2f(px+6,py+10);
		glVertex2f(px+3,py+2);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(px-disp,py);
		glVertex2f(px-disp+10,py+6);
		glVertex2f(px-disp+20,py+16);
		glVertex2f(px-disp+28,py+30);
		glVertex2f(px-disp+20,py+27);
		glVertex2f(px-disp+10,py+24);
		glVertex2f(px-disp+7,py+23);
		glVertex2f(px-disp+6,py+30);
		glVertex2f(px-disp+4,py+40);
		glVertex2f(px-disp+3,py+50);
		glVertex2f(px-disp+3,py+62);
		glVertex2f(px-disp-5,py+55);
		glVertex2f(px-disp-8,py+40);
		glVertex2f(px-disp-9,py+30);
		glVertex2f(px-disp-8,py+20);
		glVertex2f(px-disp-6,py+10);
		glVertex2f(px-disp-3,py+2);
	glEnd();
}
void leafEight(int px, int py){
	int mirror = max/2;
	int disp = 2*(px-mirror);
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_POLYGON);
		glVertex2f(px,py);
		glVertex2f(px-10,py+5);
		glVertex2f(px-20,py+13);
		glVertex2f(px-30,py+23);
		glVertex2f(px-35,py+32);
		glVertex2f(px-30,py+29);
		glVertex2f(px-17,py+26);
		glVertex2f(px-17,py+40);
		glVertex2f(px-19,py+53);
		glVertex2f(px-8,py+41);
		glVertex2f(px-3,py+30);
		glVertex2f(px,py+20);
		glVertex2f(px+1,py+10);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(px-disp,py);
		glVertex2f(px-disp+10,py+5);
		glVertex2f(px-disp+20,py+13);
		glVertex2f(px-disp+30,py+23);
		glVertex2f(px-disp+35,py+32);
		glVertex2f(px-disp+30,py+29);
		glVertex2f(px-disp+17,py+26);
		glVertex2f(px-disp+17,py+40);
		glVertex2f(px-disp+19,py+53);
		glVertex2f(px-disp+8,py+41);
		glVertex2f(px-disp+3,py+30);
		glVertex2f(px-disp,py+20);
		glVertex2f(px-disp-1,py+10);
	glEnd();
}
void leafNine(int px, int py){
	int mirror = max/2;
	int disp = 2*(px-mirror);
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_POLYGON);
		glVertex2f(px,py);
		glVertex2f(px-13,py+7);
		glVertex2f(px-20,py+10);
		glVertex2f(px-30,py+17);
		glVertex2f(px-40,py+26);
		glVertex2f(px-51,py+47);
		glVertex2f(px-40,py+41);
		glVertex2f(px-24,py+30);
		glVertex2f(px-25,py+39);
		glVertex2f(px-15,py+33);
		glVertex2f(px-8,py+20);
		glVertex2f(px-4,py+10);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(px-disp,py);
		glVertex2f(px-disp+13,py+7);
		glVertex2f(px-disp+20,py+10);
		glVertex2f(px-disp+30,py+17);
		glVertex2f(px-disp+40,py+26);
		glVertex2f(px-disp+51,py+47);
		glVertex2f(px-disp+40,py+41);
		glVertex2f(px-disp+24,py+30);
		glVertex2f(px-disp+25,py+39);
		glVertex2f(px-disp+15,py+33);
		glVertex2f(px-disp+8,py+20);
		glVertex2f(px-disp+4,py+10);
	glEnd();
}
void you(int cx, int cy){
	glColor3f(0.75,0.75,0.75);
	glLineWidth(10);
	glBegin(GL_LINES);
		glVertex2f(cx,cy);
		glVertex2f(cx,cy+60);

		glVertex2f(cx,cy);
		glVertex2f(cx+40,cy);

		glVertex2f(cx+40,cy);
		glVertex2f(cx+40,cy+60);
	glEnd();
}
void eff(int cx, int cy){
	glColor3f(0.75,0.75,0.75);
	glLineWidth(10);
	glBegin(GL_LINES);
		glVertex2f(cx,cy);
		glVertex2f(cx,cy+60);

		glVertex2f(cx-5,cy+60);
		glVertex2f(cx+40,cy+60);

		glVertex2f(cx,cy+30);
		glVertex2f(cx+25,cy+30);
	glEnd();
}
void pee(int cx, int cy){
	glColor3f(0.75,0.75,0.75);
	glLineWidth(10);
	glBegin(GL_LINES);
		glVertex2f(cx,cy);
		glVertex2f(cx,cy+60);

		glVertex2f(cx-5,cy+60);
		glVertex2f(cx+40,cy+60);

		glVertex2f(cx+40,cy+60);
		glVertex2f(cx+40,cy+30);

		glVertex2f(cx+40,cy+30);
		glVertex2f(cx,cy+30);
	glEnd();
}
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	//grid();
	circle2(150.0, 4.0,0.75,0.75,0.75);
	circle2(159.0, 10.0,0.75,0.75,0.75);
	circle2(147.0, 5.0,0.5,0.5,0.5);
	circle2(1.0, 147.0,0.0,0.0,0.4);
	Sleep(500);//.5
	glFlush();
	leafBase(315,100);
	Sleep(300);//.8
	glFlush();
	leafOne(410, 127);
	Sleep(300);//1.1
	glFlush();
	leafTwo(437,150);
	Sleep(300);//1.4
	glFlush();
	leafThree(460, 180);
	Sleep(300);//1.7
	glFlush();
	leafFour(483,215);
	Sleep(300);//2
	glFlush();
	leafFive(495,252);
	Sleep(300);//2.3
	glFlush();
	leafSix(498,292);
	Sleep(300);//2.6
	glFlush();
	leafSeven(495, 335);
	Sleep(300);//2.9
	glFlush();
	leafEight(485,368);
	Sleep(300);//3.1
	glFlush();
	leafNine(463,405);
	Sleep(300);//3.4
	glFlush();
	star1(252,300,30);
	Sleep(1000);//4.4
	glFlush();
	star1(331, 343, 20);
	Sleep(1000);//5.4
	glFlush();
	star1(346, 265, 20);
	Sleep(1000);//6.4
	glFlush();
	dot(2.0,317,165);
	dot(2.0, 214,191);
	dot(4.0,424,253);
	dot(2.0, 419,288);
	dot(2.0,313,197);
	dot(2.0,304,205);
	dot(2.0,318,221);
	dot(3.0,245,201);
	dot(3.0,404,216);
	dot(4.0,249,426);
	Sleep(200);//6.6
	glFlush();
	dot(3.0,323,424);
	dot(3.0,352,429);
	dot(3.0,292,396);
	dot(4.0,272,379);
	dot(4.0,392,405);
	dot(5.0,206,242);
	dot(5.0,262,228);
	Sleep(200);//6.6
	glFlush();
	dot(5.0,297,244);
	dot(5.0,309,277);
	dot(5.0,351,302);
	dot(3.0,331,276);
	dot(2.0,280,286);
	dot(2.0,353,284);
	Sleep(200);//6.6
	glFlush();
	dot(2.0,244,259);
	dot(2.0,383,383);
	dot(2.0,361,307);
	dot(2.0,324,305);
	dot(3.0,247,378);
	dot(4.0,221,382);
	Sleep(300);//6.9
	glFlush();
	dot(4.0,356,352);
	dot(3.0,302,337);
	dot(4.0,300,319);
	dot(3.0,174,236);
	dot(4.0,170,268);
	dot(4.0,167,285);
	Sleep(200);//7.1
	glFlush();
	dot(4.0,179,323);
	dot(3.0,169,345);
	dot(3.0,200,306);
	dot(3.0,224,293);
	Sleep(200);//7.3
	glFlush();
	dot(3.0,211,275);
	dot(3.0,230,260);
	dot(4.0,227,243);
	dot(3.0,198,213);
	dot(3.0,208,214);
	dot(3.0,220,231);
	dot(3.0,238,238);
	dot(3.0,432,316);
	Sleep(300);//7.6
	glFlush();
	dot(3.0,414,326);
	dot(2.0,418,339);
	dot(3.0,430,353);
	dot(3.0,407,375);
	dot(3.0,328,206);
	dot(3.0,314,231);
	dot(3.0,328,227);
	Sleep(200);//7.8
	glFlush();
	dot(3.0,285,275);
	dot(3.0,298,272);
	dot(3.0,283,255);
	dot(2.0,237,208);
	dot(3.0,244,217);
	Sleep(200);//6.6
	glFlush();
	dot(3.0,255,243);
	dot(3.0,260,270);
	dot(3.0,262,317);
	dot(3.0,331,298);
	dot(3.0,302,287);
	dot(3.0,298,298);
	Sleep(400);//8.2
	glFlush();
	dot(3.0,318,256);
	dot(3.0,370,295);
	dot(3.0,347,331);
	dot(3.0,363,334);
	dot(4.0,365,323);
	dot(4.0,391,367);
	dot(3.0,398,355);
	dot(3.0,386,275);
	Sleep(200);//8.4
	glFlush();
	dot(3.0,378,322);
	dot(3.0,389,320);
	dot(3.0,388,342);
	dot(3.0,376,350);
	dot(3.0,402,345);
	Sleep(1000);//10
	glFlush();
	you(195,495);
	eff(290,490);
	pee(370,490);
	glFlush();
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(max,max);
	glutCreateWindow("Flag");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}