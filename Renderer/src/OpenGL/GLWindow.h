#ifndef _OPEN_GL_GL_WINDOW_
#define _OPEN_GL_GL_WINDOW_

#include <Window.h>
#include <slogger/slogger.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GLWindow : public Window {
public:
    GLWindow(unsigned int width, unsigned int height, const char * name);
    virtual ~GLWindow() override;
    virtual bool isOpen() override;
    virtual void close() override;
    virtual void onUpdate() override;
    virtual void * getBaseWindow() override;

    virtual void setVSync(bool) override;
private:
    GLFWwindow * window;
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height){ glViewport(0, 0, width, height); }
    
};

#endif //_OPEN_GL_GL_WINDOW_