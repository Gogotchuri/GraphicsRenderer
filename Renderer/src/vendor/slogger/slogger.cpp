#include "slogger.h"
#include <ctime>
/* COLOR KEYS */
#define DEFAULT_KEY "\x1B[0m"
#define RED_KEY     "\x1B[31m"
#define YELLOW_KEY  "\x1B[33m"
#define GREEN_KEY   "\x1B[32m"
#define BOLD_KEY    "\x1B[1m"

//TODO Log timing!

static std::string getLocalTime(){
    auto now_t = std::time(0);
    auto now = std::localtime(&now_t);
    char buffer[32];
    //Some time formatting
    sprintf(buffer, "[%d/%d%d/%d%d %d%d:%d%d:%d%d]",
        now->tm_year+1900, now->tm_mon/10, now->tm_mon%10,
        now->tm_mday/10, now->tm_mday%10,
        now->tm_hour/10, now->tm_hour%10, now->tm_min/10, now->tm_min%10,
        now->tm_sec/10, now->tm_sec%10
    );
    return std::string(buffer);
}

static void print_info(const std::string& message, bool color_support = false){
    std::cout << getLocalTime() << " ";
    if(color_support)
        std::cout << GREEN_KEY << "INFO: " << message << DEFAULT_KEY << std::endl;
    else
        std::cout << "INFO: " << message << std::endl;
}

static void print_warning(const std::string& message, bool color_support = false){
    std::cout << getLocalTime() << " ";
    if(color_support)
        std::cout << YELLOW_KEY << "WARNING: " << message << DEFAULT_KEY << std::endl;
    else
        std::cout << "WARNING: " << message << std::endl;
}

static void print_error(const std::string& message, bool color_support = false){
    std::cout << getLocalTime() << " ";
    if(color_support)
        std::cout << RED_KEY << "ERROR: " << message << DEFAULT_KEY << std::endl;
    else
        std::cout << "ERROR: " << message << std::endl;
}

///+++++++++++++++++++++++++++++ Slogger +++++++++++++++++++++++++++++++
bool Slogger::is_initialized = false;
std::string Slogger::filename = "";
Slogger::LoggerMode Slogger::mode = TERMINAL;
std::ofstream Slogger::out_file = std::ofstream();

void Slogger::init(LoggerMode m, const std::string filepath) {
    if(out_file.is_open()) out_file.close();
    is_initialized = true;
    filename = filepath;
    mode = m;
    if(mode != TERMINAL) out_file = std::ofstream(filepath);
}

void Slogger::print(MessageStatus ms, const std::string& message, bool color_suppot) {
    if(mode != FILE) {
        // Print to terminal
        switch (ms)
        {
            case INFO:
                print_info(message, color_suppot);
                break;
            case WARNING:
                print_warning(message, color_suppot);
                break;
            case ERR:
                print_error(message, color_suppot);
                break;
        }
    }

    if(mode != TERMINAL){
        out_file << getLocalTime() << " ";
        switch (ms)
        {
            case INFO:
                out_file << "INFO: " << message << std::endl;
                break;
            case WARNING:
                out_file << "WARNING: " << message << std::endl;
                break;
            case ERR:
                out_file << "ERROR: " << message << std::endl;
                break;
        }
    }
}

void Slogger::closeFile() {
    if(mode != TERMINAL && out_file.is_open()) out_file.close();
}

