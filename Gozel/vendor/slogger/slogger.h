#ifndef SLOGGER_H_
#define SLOGGER_H_

#include <string>
#include <iostream>
#include <fstream>

#define SLOGGER_INIT()                  Slogger::init()
#define SLOGGER_INIT_TERMINAL()         Slogger::init(Slogger::LoggerMode::TERMINAL)
#define SLOGGER_INIT_FILE(filename)     Slogger::init(Slogger::LoggerMode::FILE, filename)
#define SLOGGER_INIT_FILE_TERMINAL(f)   Slogger::init(Slogger::LoggerMode::FILE_TERMINAL, f)

#define SLOGGER_CLOSE()                  Slogger::closeFile()

#define SLOGGER_INFO(s)                 Slogger::print(Slogger::MessageStatus::INFO, s)
#define SLOGGER_WARN(s)                 Slogger::print(Slogger::MessageStatus::WARN, s)
#define SLOGGER_ERROR(s)                Slogger::print(Slogger::MessageStatus::ERR, s)

class Slogger {
public:
    enum MessageStatus {
        INFO = 0,
        WARNING,
        ERR
    };

    enum LoggerMode {
        TERMINAL = 0,
        FILE,
        FILE_TERMINAL
    };
public:
    static void init(LoggerMode mode = TERMINAL, const std::string filepath = "");
    static void print(MessageStatus ms, const std::string& message, bool color_suppot = true);
    static void closeFile();
private:
    static LoggerMode mode;
    static std::string filename;
    static std::ofstream out_file;
    static bool is_initialized;
};

#endif //SLOGGER_H_