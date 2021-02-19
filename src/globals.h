#ifndef GLOBALS_H
#define GLOBALS_H

#include <unordered_map>
#include <string>
#include <vector>
#include <array>

typedef std::unordered_map<std::string, std::string> cubeMap;
// Array of function pointers
typedef std::array<std::string (*)(std::unordered_map<std::string, std::string>&), 18> rFunctions;

const std::vector<std::vector<std::string>> gSIDES {
    {"flu", "fru", "frd", "fld"},
    {"ufl", "urf", "ubl", "urb"},
    {"luf", "lfd", "lub", "lbd"},
    {"rfu", "rdf", "rbu", "rdb"},
    {"dfr", "dlf", "dbr", "dlb"},
    {"blu", "bru", "brd", "bld"}
};



const std::vector<std::string> gCUBELETS = 
{
    // front left upper, left upper front, upper front left
    "flu", "luf", "ufl",
    // front right upper, upper right front, right front upper
    "fru", "urf", "rfu",
    // front right down, right down front, down front right
    "frd", "rdf", "dfr",
    // front left down, down left front, left front down
    "fld", "dlf", "lfd",
    // back face (rear)
    // back left upper, left upper back, upper back left
    "blu", "lub", "ubl",
    // back right upper, upper right back, right back upper
    "bru", "urb", "rbu",
    // back right down, right down back, down back right
    "brd", "rdb", "dbr",
    // back left down, down left back, left back down
    "bld", "dlb", "lbd"
};

// Vertex in the graph
struct Vertex
{
    cubeMap m_lState;
    // if m_previousMove is "\0" then it has no parents
    std::string m_previousMove;
    // If m_previousMoveIndex is -1 then it is the start state
    int m_previousMoveIndex;

    Vertex()
        : m_lState(), m_previousMove("\0"), m_previousMoveIndex(-1) {};

    Vertex(cubeMap state, std::string move, int moveIndex=-1)
        : m_lState(state), m_previousMove(move), m_previousMoveIndex(moveIndex) {};

    // Compare the m_lState unordered_maps
    bool operator==(const Vertex& rhs) const 
    {
        if (m_lState == rhs.m_lState)
        {
            return true;
        }
        return false;
    }
};

#endif 