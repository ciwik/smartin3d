#ifndef SMARTIN3D_FILEUTILS_H
#define SMARTIN3D_FILEUTILS_H

#include "precompiled.h"

#include "Log.h"

namespace smartin::utils::io {
    static std::string ReadFile(const std::string& filePath) {
        std::string result;
        std::ifstream fileStream(filePath, std::ios::in);

        if (!fileStream.is_open())
            throw error::FileNotFoundException("Failed to read file by path: " + filePath);

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
