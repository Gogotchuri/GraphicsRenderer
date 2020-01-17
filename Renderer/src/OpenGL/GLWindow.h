#ifndef _OPEN_GL_GL_WINDOW_
#define _OPEN_GL_GL_WINDOW_

#include <Window.h>
#include <slogger/slogger.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GLWindow : public Window {
public:
    GLWindow(unsigned int width, unsigned int height, const char * name);
    virtual ~GLWindow(){};
    virtual bool isOpen();
    virtual void close();
    virtual void swapBuffers();
    virtual void * getBaseWindow();
private:
    GLFWwindow * window;
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height){ glViewport(0, 0, width, height); }

};

#endif //_OPEN_GL_GL_WINDOW_