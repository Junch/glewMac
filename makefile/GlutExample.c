#include <stdlib.h> 
#include <GLUT/glut.h> /* Header File For The GLut Library*/ 

#define kWindowWidth      640 
#define kWindowHeight     480 

typedef GLfloat point[3]; 

point v[4] ={{0.0, 0.0, 1.0}, 
             {0.0, 0.942809, -0.333333}, 
             {-0.816497, -0.471405, -0.333333}, 
             {0.816497, -0.471405, -0.333333}};

void triangle( point a, point b, point c) 
{ 
  glBegin(GL_LINE_LOOP);
  glVertex3fv(a); 
  glVertex3fv(b); 
  glVertex3fv(c); 
  glEnd(); 
} 

void tetrahedron(void) 
{ 
  triangle(v[0], v[1], v[2]); 
  triangle(v[3], v[2], v[1]); 
  triangle(v[0], v[2], v[3]); 
} 

void display(void)
{ 
  glClear(GL_COLOR_BUFFER_BIT); 
  glColor3f(1.0,1.0,1.0); 
  glLoadIdentity(); 

  tetrahedron(); 
  glutSwapBuffers();
} 

int main(int argc, char** argv) 
{ 
  glutInit(&argc, argv); 
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
  glutInitWindowSize (kWindowWidth, kWindowHeight); 
  glutInitWindowPosition (100, 100); 
  glutCreateWindow ("simple opengl example");

  glutDisplayFunc(display);

  glutMainLoop();

  return 0;
}
