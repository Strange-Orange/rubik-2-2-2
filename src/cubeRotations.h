#ifndef CUBEROTATIONS_H
#define CUBEROTATIONS_H
// Define the rotations for the cube, returns the first letter 

#include "globals.h"

#include <unordered_map>
#include <string>
#include <array>

void getCubelet(std::array<std::string, 3>& temps, cubeMap& state, int startPoint);

std::string frontClockwise(cubeMap& state);
std::string frontAntiClockwise(cubeMap& state);
std::string frontDouble(cubeMap& state);

std::string upperClockwise(cubeMap& state);
std::string upperAntiClockwise(cubeMap& state);
std::string upperDouble(cubeMap& state);

std::string leftClockwise(cubeMap& state);
std::string leftAntiClockwise(cubeMap& state);
std::string leftDouble(cubeMap& state);

std::string rightClockwise(cubeMap& state);
std::string rightAntiClockwise(cubeMap& state);
std::string rightDouble(cubeMap& state);

std::string bottomClockwise(cubeMap& state);
std::string bottomAntiClockwise(cubeMap& state);
std::string bottomDouble(cubeMap& state);

std::string endClockwise(cubeMap& state);
std::string endAntiClockwise(cubeMap& state);
std::string endDouble(cubeMap& state);

rFunctions rotations(); 

#endif