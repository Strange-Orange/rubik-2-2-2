#include "cubeRotations.h"
#include "globals.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <array>

void getCubelet(std::array<std::string, 3>& temp, cubeMap& state, int startPoint)
{
    for (size_t i = startPoint, tp = 0; i < (startPoint + temp.size()); i++, tp++)
    {
        temp.at(tp) = state.at(gCUBELETS.at(i));
    }
}

std::string frontClockwise(cubeMap& state)
{
    // front left upper to front right upper
    std::array<std::string, 3> temps;
    getCubelet(temps, state, 3);

    state["fru"] = state["flu"];
    state["urf"] = state["luf"];
    state["rfu"] = state["ufl"];
    // front right upper to front right down
    std::array<std::string, 3> temps2;
    getCubelet(temps2, state, 6);

    state["frd"] = temps[0];
    state["rdf"] = temps[1];
    state["dfr"] = temps[2];
    // front right down to front left down
    getCubelet(temps, state, 9);
    state["fld"] = temps2[0];
    state["dlf"] = temps2[1];
    state["lfd"] = temps2[2];
    // front left down to front left upper
    state["flu"] = temps[0];
    state["luf"] = temps[1];
    state["ufl"] = temps[2];

    return "f";
}

std::string frontAntiClockwise(cubeMap& state)
{
    // Front left upper to front left down
    std::array<std::string, 3> fld;
    getCubelet(fld, state, 9);
    state["fld"] = state["flu"];
    state["dlf"] = state["luf"];
    state["lfd"] = state["ufl"];
    // Front left down to front right down
    std::array<std::string, 3> frd;
    getCubelet(frd, state, 6);
    state["frd"] = fld[0];
    state["rdf"] = fld[1];
    state["dfr"] = fld[2];
    // Front right down to front right upper
    std::array<std::string, 3> fru;
    getCubelet(fru, state, 3);
    state["fru"] = frd[0];
    state["urf"] = frd[1];
    state["rfu"] = frd[2];
    // Front right upper to front left upper
    state["flu"] = fru[0];
    state["luf"] = fru[1];
    state["ufl"] = fru[2];

    return "f`";
}

std::string frontDouble(cubeMap& state)
{
    frontClockwise(state);
    frontClockwise(state);
    return "2f";
}

std::string upperClockwise(cubeMap& state)
{
    // Front left upper to right back upper 
    std::array<std::string, 3> temps;
    getCubelet(temps, state, 12);

    state["lub"] = state["flu"];
    state["blu"] = state["luf"];
    state["ubl"] = state["ufl"];
    // back left upper to right back upper
    std::array<std::string, 3> temps2;
    getCubelet(temps2, state, 15);
    state["rbu"] = temps[0];
    state["bru"] = temps[1]; 
    state["urb"] = temps[2];
    // back right upper to right front upper
    getCubelet(temps, state, 3);
    state["rfu"] = temps2[0];
    state["urf"] = temps2[1];
    state["fru"] = temps2[2];

    // Front upper right to left upper front
    state["luf"] = temps[0];
    state["ufl"] = temps[1];
    state["flu"] = temps[2];

    return "u";
}

std::string upperAntiClockwise(cubeMap& state)
{
    // Front left upper to right front upper
    std::array<std::string, 3> fru;
    getCubelet(fru, state, 3);
    state["fru"] = state["luf"]; 
    state["urf"] = state["ufl"];
    state["rfu"] = state["flu"];

    // front right upper to back right upper
    std::array<std::string, 3> bru;
    getCubelet(bru, state, 15);
    state["bru"] = fru[2];
    state["urb"] = fru[1];
    state["rbu"] = fru[0];

    // back right upper to back left upper
    std::array<std::string, 3> blu;
    getCubelet(blu, state, 12);
    state["blu"] = bru[2];
    state["lub"] = bru[0];
    state["ubl"] = bru[1];

    // back left upper to front left upper
    state["flu"] = blu[1];
    state["luf"] = blu[0];
    state["ufl"] = blu[2];

    return "u`";
}

std::string upperDouble(cubeMap& state)
{
    upperClockwise(state);
    upperClockwise(state);
    return "2u";
}

std::string leftClockwise(cubeMap& state)
{
    // Front left upper to down left front
    std::array<std::string, 3> dlf;
    getCubelet(dlf, state, 9);
    state["fld"] = state["ufl"];
    state["dlf"] = state["flu"];
    state["lfd"] = state["luf"];

    // down left front to back left down
    std::array<std::string, 3> bld;
    getCubelet(bld, state, 21);
    state["bld"] = dlf[1];
    state["dlb"] = dlf[0];
    state["lbd"] = dlf[2];

    // back left down to upper back left
    std::array<std::string, 3> ubl;
    getCubelet(ubl, state, 12);
    state["blu"] = bld[1];
    state["lub"] = bld[2];
    state["ubl"] = bld[0];

    // upper back left to front left upper
    state["flu"] = ubl[2];
    state["luf"] = ubl[1];
    state["ufl"] = ubl[0];

    return "l";
}

std::string leftAntiClockwise(cubeMap& state)
{
    // Front left upper to upper back left
    std::array<std::string, 3> ubl;
    getCubelet(ubl, state, 12);
    state["blu"] = state["ufl"];
    state["lub"] = state["luf"];
    state["ubl"] = state["flu"];

    // upper back left to back left down
    std::array<std::string, 3> lbd;
    getCubelet(lbd, state, 21);
    state["bld"] = ubl[2];
    state["dlb"] = ubl[0];
    state["lbd"] = ubl[1];

    // back left down to down left front
    std::array<std::string, 3> dlf;
    getCubelet(dlf, state, 9);
    state["fld"] = lbd[1];
    state["dlf"] = lbd[0];
    state["lfd"] = lbd[2];

    // down left front to front left upper
    state["flu"] = dlf[1];
    state["luf"] = dlf[2];
    state["ufl"] = dlf[0];

    return "l`";
}

std::string leftDouble(cubeMap& state)
{
    leftClockwise(state);
    leftClockwise(state);
    return "2l";
}

std::string rightClockwise(cubeMap& state)
{
    // Front right upper to upper right back
    std::array<std::string, 3> urb;
    getCubelet(urb, state, 15);
    state["bru"] = state["urf"];
    state["urb"] = state["fru"];
    state["rbu"] = state["rfu"];

    // Upper right back to back right down
    std::array<std::string, 3> brd;
    getCubelet(brd, state, 18);
    state["brd"] = urb[1];
    state["rdb"] = urb[2];
    state["dbr"] = urb[0];

    // back right down to down front right
    std::array<std::string, 3> dfr;
    getCubelet(dfr, state, 6);
    state["frd"] = brd[2];
    state["rdf"] = brd[1];
    state["dfr"] = brd[0];

    // down front right to front right upper 
    state["fru"] = dfr[2];
    state["urf"] = dfr[0];
    state["rfu"] = dfr[1];

    return "r";
}

std::string rightAntiClockwise(cubeMap& state)
{
    // Front right upper to down front right
    std::array<std::string, 3> dfr;
    getCubelet(dfr, state, 6);
    state["frd"] = state["urf"];
    state["rdf"] = state["rfu"];
    state["dfr"] = state["fru"];

    // down front right to back right down 
    std::array<std::string, 3> brd;
    getCubelet(brd, state, 18);
    state["brd"] = dfr[2];
    state["rdb"] = dfr[1];
    state["dbr"] = dfr[0];

    // back right down to upper right back
    std::array<std::string, 3> urb;
    getCubelet(urb, state, 15);
    state["bru"] = brd[2];
    state["urb"] = brd[0];
    state["rbu"] = brd[1];

    // Upper right back to front right upper 
    state["fru"] = urb[1];
    state["urf"] = urb[0];
    state["rfu"] = urb[2];

    return "r`";
}

std::string rightDouble(cubeMap& state)
{
    rightClockwise(state);
    rightClockwise(state);
    return "2r";
}

std::string downClockwise(cubeMap& state)
{
    // Front left down to right down front
    std::array<std::string, 3> rdf;
    getCubelet(rdf, state, 6);
    state["frd"] = state["lfd"];
    state["rdf"] = state["fld"];
    state["dfr"] = state["dlf"];

    // Right down front to back right down 
    std::array<std::string, 3> brd;
    getCubelet(brd, state, 18);
    state["brd"] = rdf[1]; 
    state["rdb"] = rdf[0];
    state["dbr"] = rdf[2];

    // back right down to left back down 
    std::array<std::string, 3> lbd;
    getCubelet(lbd, state, 21);
    state["bld"] = brd[1];
    state["dlb"] = brd[2];
    state["lbd"] = brd[0];

    // left back down to front left down 
    state["fld"] = lbd[2];
    state["dlf"] = lbd[1];
    state["lfd"] = lbd[0];

    return "b";
}

std::string downAntiClockwise(cubeMap& state)
{
    // Front left down to left back down
    std::array<std::string, 3> lbd;
    getCubelet(lbd, state, 21);
    state["bld"] = state["lfd"];
    state["dlb"] = state["dlf"];
    state["lbd"] = state["fld"];

    // Left back down to back right down
    std::array<std::string, 3> brd;
    getCubelet(brd, state, 18);
    state["brd"] = lbd[2];
    state["rdb"] = lbd[0];
    state["dbr"] = lbd[1];

    // back right down to right down front
    std::array<std::string, 3> rdf;
    getCubelet(rdf, state, 6);
    state["frd"] = brd[1];
    state["rdf"] = brd[0];
    state["dfr"] = brd[2];

    // Right down front to front left down
    state["fld"] = rdf[1];
    state["dlf"] = rdf[2];
    state["lfd"] = rdf[0];

    return "b`";
}

std::string downDouble(cubeMap& state)
{
    downClockwise(state);
    downClockwise(state);
    return "2b";
}

std::string backClockwise(cubeMap& state)
{
    // back right upper to back left upper
    std::array<std::string, 3> blu;
    getCubelet(blu, state, 12);
    state["blu"] = state["bru"];
    state["lub"] = state["urb"];
    state["ubl"] = state["rbu"];
    // back left upper to back left down
    std::array<std::string, 3> bld;
    getCubelet(bld, state, 21);
    state["bld"] = blu[0]; 
    state["dlb"] = blu[1];
    state["lbd"] = blu[2];
    // back left down to back right down
    std::array<std::string, 3> brd;
    getCubelet(brd, state, 18);
    state["brd"] = bld[0];
    state["rdb"] = bld[1];
    state["dbr"] = bld[2];
    // back right down to back right upper
    state["bru"] = brd[0];
    state["urb"] = brd[1];
    state["rbu"] = brd[2];

    return "e";
}

std::string backAntiClockwise(cubeMap& state)
{
    // back left upper to back right upper 
    std::array<std::string, 3> bru;
    getCubelet(bru, state, 15);
    state["bru"] = state["blu"];
    state["urb"] = state["lub"];
    state["rbu"] = state["ubl"];
    // back right upper to back right down
    std::array<std::string, 3> brd;
    getCubelet(brd, state, 18);
    state["brd"] = bru[0];
    state["rdb"] = bru[1];
    state["dbr"] = bru[2];
    // back right down to back left down
    std::array<std::string, 3> bld;
    getCubelet(bld, state, 21);
    state["bld"] = brd[0];
    state["dlb"] = brd[1];
    state["lbd"] = brd[2];

    // back left down to back left upper
    state["blu"] = bld[0];
    state["lub"] = bld[1];
    state["ubl"] = bld[2];

    return "e'";
}

std::string backDouble(cubeMap& state)
{
    backClockwise(state);
    backClockwise(state);
    return "2e";
}

rFunctions rotations()
{
    rFunctions r = {
        frontDouble, upperDouble, leftDouble, rightDouble, downDouble, backDouble,
        frontClockwise, frontAntiClockwise, upperClockwise, upperAntiClockwise, leftClockwise, leftAntiClockwise,
        rightClockwise, rightAntiClockwise, downClockwise, downAntiClockwise, backClockwise, backAntiClockwise
    };
    return r;
}