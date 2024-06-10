//
// Created by Victor Navarro on 23/04/24.
//

#include "FileHandler.h"
#include <fstream>  
#include <iostream> 

void FileHandler::writeToFile(char *targetFilePath, char *buffer, unsigned int bufferSize) {
    std::ofstream writeStream(targetFilePath, std::ios::binary);
    if (!writeStream) {
        std::cerr << "Error al abrir el archivo para escribir: " << targetFilePath << std::endl;
        return;
    }
    writeStream.write(buffer, bufferSize);
    writeStream.close();
}

char* FileHandler::readFromFile(char *targetFilePath, char* buffer, unsigned int bufferSize) {
    std::ifstream readStream(targetFilePath, std::ios::binary);
    if (!readStream) {
        std::cerr << "Error al abrir el archivo para leer:" << targetFilePath << std::endl;
        throw 1;
    }
    readStream.read(buffer, bufferSize);
    readStream.close();
    return buffer;
}

