#include "globals.h"
#include "cubeRotations.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <array>

// rotation functions
const rFunctions g_rotations = rotations();

// The hash function used for an unordered_map needs to be a type. The operator() overload needs to be a const function
struct VertexHash
{
    size_t operator()(const Vertex& v) const
    {
        size_t result = 0;
        const size_t prime = 31;
        for (const std::pair<std::string, std::string>& cl: v.m_lState)
        {
            for (const char& c: cl.second)
            {
                result = c + (result * prime);
            }
        }
        return result;
    }
};

std::string printCubeState(const Vertex& v);
inline void initCube(cubeMap& cubeState);
std::string traceBack(const Vertex& sv, std::unordered_map<Vertex, Vertex, VertexHash>& parent);
void handleInput(int argc, char* args[], cubeMap& cube);
bool checkCompletion(const cubeMap& sCurrentState);
inline bool rotationRepeatOrReverse(const int pMove, const int cMove);
void addToAdj(const Vertex& vStart, std::unordered_map<Vertex, std::vector<Vertex>, VertexHash>& adj);
std::string solveCube(cubeMap& cubeState);

std::string printCubeState(const Vertex& v)
{
    std::string s;
    for (const std::pair<std::string, std::string>& cubelet: v.m_lState)
    {
        s += "Position : " + cubelet.first + " : " + cubelet.second + "\n";
    }
    return s;
}

// Setup a non scrambled cube
inline void initCube(cubeMap& cubeState)
{
    // Each of the 8 cubelets that make up the whole cube, each in all 3 orientations, each face is read as rotation around the 3 faces
    // The whole cube is never rotated, the whole cube is always in the same orientation
    // This is set up with the yellow face facing forward and blue upwords
    const std::vector<std::string> cubeletsOrientations = {
        // Front face
        // upper left
        "ybr", "ryb", "bry",
        // upper right
        "ybo", "boy", "oyb",
        // lower right
        "ygo", "oyg", "goy",
        // lower left
        "ygr", "gry", "ryg",
        // end face (rear)
        // upper left
        "wbr", "rwb", "brw",
        // upper right
        "wbo", "bow", "owb",
        // lower right
        "wgo", "owg", "gow",
        // lower left
        "wgr", "grw", "rwg"
    };

    // cubelets as the key and orientation as the value 
    for (size_t i = 0; i < gCUBELETS.size(); i++)
    {
        cubeState[gCUBELETS[i]] = cubeletsOrientations[i];
    }
}

void handleInput(int argc, char* args[], cubeMap& cube)
{
    // Lazy code
    for (int arg = 1; arg < argc; arg++)
    {
        if (std::strcmp(args[arg], "f") == 0)
            frontClockwise(cube);
        else if (std::strcmp(args[arg], "fa") == 0)
            frontAntiClockwise(cube);
        else if (std::strcmp(args[arg], "u") == 0)
            upperClockwise(cube);
        else if (std::strcmp(args[arg], "ua") == 0)
            upperAntiClockwise(cube);
        else if (std::strcmp(args[arg], "l") == 0)
            leftClockwise(cube);
        else if (std::strcmp(args[arg], "la") == 0)
            leftAntiClockwise(cube);
        else if (std::strcmp(args[arg], "r") == 0)
            rightClockwise(cube);
        else if (std::strcmp(args[arg], "ra") == 0)
            rightAntiClockwise(cube);
        else if (std::strcmp(args[arg], "b") == 0)
            bottomClockwise(cube);
        else if (std::strcmp(args[arg], "ba") == 0)
            bottomAntiClockwise(cube);
        else if (std::strcmp(args[arg], "e") == 0)
            endClockwise(cube);
        else if (std::strcmp(args[arg], "ea") == 0)
            endAntiClockwise(cube);
        else
            continue;
    }
}

// Trace the solution from the solved state back to the start state.
std::string traceBack(const Vertex& sv, std::unordered_map<Vertex, Vertex, VertexHash>& parent)
{
    std::string solution;
    Vertex cv = sv;
    while (cv.m_previousMove.compare("\0") != 0)
    {
        solution = cv.m_previousMove +  " " + solution;
        cv = parent.at(cv);
    }
    return solution;
}

// Check if the cube is solved
bool checkCompletion(const cubeMap& sCurrentState)
{
    for (size_t side = 0; side < gSIDES.size(); side++)
    {
        // Get the first letter of the cublets colour
        // std::string f = gSIDES.at(side).at(0);
        const char colour = sCurrentState.at(gSIDES.at(side).at(0)).at(0);
        for (size_t face = 1; face < gSIDES.at(side).size(); face++)
        {
            std::string facePosition = gSIDES.at(side).at(face);
            if ((sCurrentState.at(gSIDES.at(side).at(face)).at(0)) != colour)
            {
                return false;
            }
        }
    }
    return true;
}

// Check if a rotation will be 2 of the same.( front clockwise front clockwise) Since the frontdouble is performed first
// there no need to calculated it the state has already been found.
// Also check if the opposite rotation will be performed to return to the previous state(front clockwise, front anti clockwise), this state will
// have already been found so there is no need to calculate it. Return true if the cube state has already been found
inline bool rotationRepeatOrReverse(const int pMove, const int cMove)
{
    if (cMove == pMove)
    {
        return true;
    }
    else if (cMove % 2 == 0 && (pMove == cMove + 1))
    {
        return true;
    }
    // current move must be anti-clockwise
    else if (pMove == cMove - 1)
    {
        return true;
    }
    else
    {
        return false;
    } 
}

// Perform all rotations add then rotations to the key vStart in the adjlist 
void addToAdj(const Vertex& vStart, std::unordered_map<Vertex, std::vector<Vertex>, VertexHash>& adj)
{
    // Add vertex if it is not a key in the adjList
    if (adj.find(vStart) == adj.end())
    {
        adj[vStart];
    }

    for (size_t func = 0; func < g_rotations.size(); func++)
    {
        if (!rotationRepeatOrReverse(vStart.m_previousMoveIndex, func))
        {
            std::unordered_map<std::string, std::string> rotated = vStart.m_lState;
            std::string rStr = g_rotations[func](rotated);
            Vertex v(rotated, rStr, func);
            adj.at(vStart).push_back(v);
        }
    }
}

std::string solveCube(cubeMap& cubeState)
{

    Vertex vStartState(cubeState, "\0");

    std::unordered_map<Vertex , int, VertexHash> visited;
    visited[vStartState] = 0;

    std::unordered_map<Vertex, Vertex, VertexHash> parent;

    // Create adjacency list
    std::unordered_map<Vertex, std::vector<Vertex>, VertexHash> adjList;
    addToAdj(vStartState, adjList);

    int level = 1;
    // The frontier is all the vertices reached on the previous level
    std::vector<Vertex> frontier;
    if (!checkCompletion(vStartState.m_lState))
        frontier.push_back(vStartState);

    while(!frontier.empty())
    {
        std::vector<Vertex> next;
        // For each vertex in the frontier create its adjacent vertices
        for (size_t f = 0; f < frontier.size(); f++)
        {
            addToAdj(frontier.at(f), adjList);

            for (size_t av = 0; av < adjList.at(frontier.at(f)).size(); av++)
            {
                Vertex& current = (adjList.at(frontier.at(f)).at(av));
                if (visited.find(current) == visited.end())
                {
                    // The Vertex has not yet been reached
                    visited[current] = level;
                    parent[current] = frontier.at(f);
                    if (checkCompletion(current.m_lState))
                    {
                        return traceBack(current, parent);
                    }
                    next.push_back(current);
                }
            } 
        }
        level++;
        frontier = next;
    }

    return "Cube is solved already";
}

int main(int argc, char* args[])
{
    cubeMap cubeState;
    initCube(cubeState);
    handleInput(argc, args, cubeState);

    std::string sol = solveCube(cubeState);
    std::cout << sol << std::endl;

    return 0;
}