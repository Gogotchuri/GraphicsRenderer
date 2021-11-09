#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <memory>
#include <string>
#include <slogger/slogger.h>

class Window {
public:
    virtual ~Window() = default;
    virtual bool isOpen() = 0;
    virtual void close() = 0;
    virtual void onUpdate() = 0;
    virtual void * getBaseWindow() = 0;

    virtual void setVSync(bool) = 0;

    static std::shared_ptr<Window> create(unsigned int width, unsigned int height, const char * name);
};

#endif //_WINDOW_H_