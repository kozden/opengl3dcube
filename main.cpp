#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include<stdio.h>
#define RADDEG 57.29577951f
#define PI 3.1415926535898

#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))

double dim=3.0;
int secim = 0;
//projeksiyon seçimi
int th = 0;
int ph = 0;
int fov = 55;
int asp = 0;


void project()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (secim) {
//perspektif icin
    gluPerspective(fov,asp,dim/4,4*dim);
  }
  else {
//ortogonal icin
    glOrtho(-dim*asp,+dim*asp, -dim,+dim, -dim,+dim);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void windowKey(unsigned char key,int x,int y)
{
    switch(key){
    case 'p' :secim = 1-secim;
case 'a' : th -= 5; break;
case 's': ph += 5; break;
case 'd': th += 5; break;
case 'w': ph -= 5; break;
    }
th %= 360;
ph %= 360;
project();
glutPostRedisplay();
}

void Kupciz()
{
  /* Cube */
  glBegin(GL_QUADS);
glColor3f(0.0f, 1.0f, 2.0f);
glVertex3f( 1.0f, 1.0f, 1.0f);
glColor3f(1.0f, 2.0f, 3.0f);
glVertex3f(-1.0f, 1.0f, 1.0f);
glColor3f(1.0f, 0.0f, 3.0f);
glVertex3f(-1.0f,-1.0f, 1.0f);
glVertex3f( 1.0f,-1.0f, 1.0f);

glColor3f(0.0f,1.0f,0.0f);
glVertex3f( 1.0f, 1.0f,-1.0f);
glColor3f(1.0f, 2.0f, 3.0f);
glVertex3f(-1.0f, 1.0f,-1.0f);
glVertex3f(-1.0f, 1.0f, 1.0f);
glVertex3f( 1.0f, 1.0f, 1.0f);

glColor3f(0.0f,0.5f,0.0f);
glVertex3f( 1.0f,-1.0f, 1.0f);
glColor3f(0.0f,0.0f,0.0f);
glVertex3f(-1.0f,-1.0f, 1.0f);
glVertex3f(-1.0f,-1.0f,-1.0f);
glVertex3f( 1.0f,-1.0f,-1.0f);

glColor3f(1.0f,1.0f,0.0f);
glVertex3f( 1.0f,-1.0f,-1.0f);
glVertex3f(-1.0f,-1.0f,-1.0f);
glColor3f(0.73f,0.16f,0.96f);
glVertex3f(-1.0f, 1.0f,-1.0f);
glVertex3f( 1.0f, 1.0f,-1.0f);

glColor3f(0.0f,0.0f,1.0f);
glVertex3f(-1.0f, 1.0f, 1.0f);
glVertex3f(-1.0f, 1.0f,-1.0f);
glVertex3f(-1.0f,-1.0f,-1.0f);
glColor3f(0.52f,0.39f,0.39f);
glVertex3f(-1.0f,-1.0f, 1.0f);

glColor3f(5.0f,2.0f,8.0f);
glVertex3f( 1.0f, 1.0f,-1.0f);
glVertex3f( 1.0f, 1.0f, 1.0f);
glColor3f(0.85f,0.85f,0.10f);
glVertex3f( 1.0f,-1.0f, 1.0f);
glVertex3f( 1.0f,-1.0f,-1.0f);

glEnd();
}

void display()
{

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

//onceki sekli siler
  glLoadIdentity();

  if (secim) {
    double Ex = -2*dim*Sin(th)*Cos(ph);
    double Ey = +2*dim        *Sin(ph);
    double Ez = +2*dim*Cos(th)*Cos(ph);
  //9 parametre alýr, ilk 3 u goz pozisyonu
//ikinci üclü hangi noktaya bakýyor
//son üclü de kendi etrafýnda donme
    gluLookAt(Ex,Ey,Ez, 0,0,0 , 0,1,0);
  }
  /*  Orthogonal - set world orientation */
  else {
    glRotatef(ph,1,0,0);
    glRotatef(th,0,1,0);
  }


  Kupciz();


  glFlush();
  glutSwapBuffers();
}

void windowMenu(int value)
{
  windowKey((unsigned char)value, 0, 0);
}

void reshape(int width,int height)
{
    if(height == 0)
    height = 1;

    if(width>height)
        width=height;
    else
        height=width;

 asp =  1.0* width/ height;
  glViewport(0,0, width,height);

   glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (secim) {

    gluPerspective(fov,asp,dim/4,4*dim);
  }
  else {

    glOrtho(-dim*asp,+dim*asp, -dim,+dim, -dim,+dim);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


int main(int argc,char* argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition (255,100);
  glutInitWindowSize(500,450);
  glutCreateWindow("opengl hw2");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(windowKey);
  glutCreateMenu(windowMenu);


  glutMainLoop();
  return 1;
}
