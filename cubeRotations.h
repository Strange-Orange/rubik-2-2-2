#ifndef CUBEROTATIONS_H
#define CUBEROTATIONS_H
// Define the rotations for the cube, returns the first letter 

#include "globals.h"

#include <unordered_map>
#include <string>
#include <array>

void getCubelet(std::array<std::string, 3>& temps, std::unordered_map<std::string, std::string>& state, int startPoint);

std::string frontClockwise(std::unordered_map<std::string, std::string>& state);
std::string frontAntiClockwise(std::unordered_map<std::string, std::string>& state);
std::string frontDouble(std::unordered_map<std::string, std::string>& state);

std::string upperClockwise(std::unordered_map<std::string, std::string>& state);
std::string upperAntiClockwise(std::unordered_map<std::string, std::string>& state);
std::string upperDouble(std::unordered_map<std::string, std::string>& state);

std::string leftClockwise(std::unordered_map<std::string, std::string>& state);
std::string leftAntiClockwise(std::unordered_map<std::string, std::string>& state);
std::string leftDouble(std::unordered_map<std::string, std::string>& state);

std::string rightClockwise(std::unordered_map<std::string, std::string>& state);
std::string rightAntiClockwise(std::unordered_map<std::string, std::string>& state);
std::string rightDouble(std::unordered_map<std::string, std::string>& state);

std::string bottomClockwise(std::unordered_map<std::string, std::string>& state);
std::string bottomAntiClockwise(std::unordered_map<std::string, std::string>& state);
std::string bottomDouble(std::unordered_map<std::string, std::string>& state);

std::string endClockwise(std::unordered_map<std::string, std::string>& state);
std::string endAntiClockwise(std::unordered_map<std::string, std::string>& state);
std::string endDouble(std::unordered_map<std::string, std::string>& state);

rFunctions rotations(); 

#endif