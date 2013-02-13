// Phong.cpp
// Our first OpenGL program that will just draw a triangle on the screen.

#include <GL/glew.h>
#include <gl/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <iostream>

#include "vbotorus.h"
#include "glslprogram.h"

GLSLProgram prog;
VBOTorus * torus = NULL;

mat4 model;
mat4 view;
mat4 projection;

///////////////////////////////////////////////////////////////////////////////
// Window has changed size, or has just been created. In either case, we need
// to use the window dimensions to set the viewport and the projection matrix.
void ChangeSize(int w, int h)
{
    glViewport(0,0,w,h);
    projection = glm::perspective(70.0f, (float)w/h, 0.3f, 100.0f);
}

///////////////////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering context.
// This is the first opportunity to do any OpenGL related tasks.
void SetupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glEnable(GL_DEPTH_TEST);
    
    prog.compileShaderFromFile("phong.vert", GLSLShader::VERTEX);
    prog.compileShaderFromFile("phong.frag", GLSLShader::FRAGMENT);
    prog.link();
    prog.use();
    

    torus = new VBOTorus(0.7f, 0.3f, 50, 50);
    
    model = mat4(1.0f);
    model *= glm::rotate(-35.0f, vec3(1.0f,0.0f,0.0f));
    model *= glm::rotate(35.0f, vec3(0.0f,1.0f,0.0f));
    view = glm::lookAt(vec3(0.0f,0.0f,2.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
    //projection = mat4(1.0f); we cannot set the projection here
    vec4 worldLight = vec4(5.0f,5.0f,2.0f,1.0f);
    
    prog.setUniform("Material.Kd", 0.9f, 0.5f, 0.3f);
    prog.setUniform("Material.Ka", 0.9f, 0.5f, 0.3f);
    prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Material.Shininess", 100.0f);
    prog.setUniform("Light.Position", view * worldLight );
    prog.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Light.La", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Light.Ls", 1.0f, 1.0f, 1.0f);
}


///////////////////////////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix", mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);
    
    torus->render();
}

void AppMain()
{
    // initialise GLFW
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");
    
    // open a window with GLFW
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    if(!glfwOpenWindow(800, 600, 8, 8, 8, 8, 16, 0, GLFW_WINDOW))
        throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 3.2?");
    
    // initialise GLEW
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if (GLEW_OK != glewInit())
        throw std::runtime_error("glewInit failed");
    
    // make sure OpenGL version 3.2 API is available
    if(!GLEW_VERSION_3_2)
        throw std::runtime_error("OpenGL 3.2 API is not available.");
    
    glfwSetWindowSizeCallback(ChangeSize);
    
    SetupRC();
    
    while(glfwGetWindowParam(GLFW_OPENED) && !glfwGetKey( GLFW_KEY_ESC ))
    {
        RenderScene();
        glfwSwapBuffers();
    }
    
    glfwTerminate();
}


///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLFW based programs
int main( int argc , char * argv [])
{
    try {
        AppMain();
    } catch (const std::exception& e){
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
