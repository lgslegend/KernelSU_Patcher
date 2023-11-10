#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <cstdio>

const std::string VERSION = "1.0.0";

const std::string MAGISKBOOT = "bin\\magiskboot\\magiskboot.exe";
const std::string SEVEN_ZIP = "bin\\7zip\\7z.exe";

//执行程序
std::string execute(std::string command) {
    std::string result;
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "Failed to execute command.";
    }
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result.append(buffer);
    }
    _pclose(pipe);
    return result;
}
//判断路径是否有效
bool isPathValid(const std::string filePath) {
    try {
        std::filesystem::path fsPath(filePath);
        std::string pathStr = fsPath.generic_string();

        if (std::filesystem::exists(pathStr)) {
            return true;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return false;
}