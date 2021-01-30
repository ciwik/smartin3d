#include "Log.h"

class Logger {
public:
    Logger(std::ostream& stream) : out(stream.rdbuf()) { }

    void Write(const std::string tag, const std::string message) {
        out << "[" << tag << "]: " << message << "\n";
    }

    ~Logger() {
        out.flush();
    }
private:
    std::ostream out;
};

Logger* logger;

void smartin::utils::log::Init(std::ostream &stream) {
    if (logger != nullptr)
        delete logger;

    logger = new Logger(stream);
}

void smartin::utils::log::I(const std::string tag, const std::string message) { logger->Write(tag, message); }

void smartin::utils::log::W(const std::string tag, const std::string message) { logger->Write(tag, message); }

void smartin::utils::log::E(const std::string tag, const std::string message) { logger->Write(tag, message); }
