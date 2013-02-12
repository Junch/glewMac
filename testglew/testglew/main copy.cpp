//
//  main.cpp
//  testglew
//
//  Created by wolf76 on 13-2-10.
//  Copyright (c) 2013年 wolf76. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <glslprogram.h>

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f,1.0f,0.0f);
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f); //画一个绿色的正方形
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    
    glutCreateWindow("绿色");
    glutDisplayFunc(&myDisplay);
    glutMainLoop();
    return 0;
}
