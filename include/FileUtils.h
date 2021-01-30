#ifndef SMARTIN3D_FILEUTILS_H
#define SMARTIN3D_FILEUTILS_H

#include <fstream>
#include <string>

#include "Log.h"

namespace smartin::utils::io {
    static std::string ReadFile(const char *filePath) {
        std::string result;
        std::ifstream fileStream(filePath, std::ios::in);

        if (!fileStream.is_open()) {
            utils::log::E("File", "Failed to read file by path: "); // TODO
            return "";
        }

        std::string line = "";
        while (!fileStream.eof()) {
            std::getline(fileStream, line);
            result.append(line + "\n");
        }

        fileStream.close();

        return result;
    }
}
#endif //SMARTIN3D_FILEUTILS_H