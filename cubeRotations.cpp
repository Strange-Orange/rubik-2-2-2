#include "cubeRotations.h"
#include "globals.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <array>

void getCubelet(std::array<std::string, 3>& temp, std::unordered_map<std::string, std::string>& state, int startPoint)
{
    for (size_t i = startPoint, tp = 0; i < (startPoint + temp.size()); i++, tp++)
    {
        temp.at(tp) = state.at(gCUBELETS.at(i));
    }
}

std::string frontClockwise(std::unordered_map<std::string, std::string>& state)
{
    // front left upper to front right upper
    std::array<std::string, 3> temps;
    getCubelet(temps, state, 3);

    state["fru"] = state["flu"];
    state["urf"] = state["luf"];
    state["rfu"] = state["ufl"];
    // front right upper to front right bottom
    std::array<std::string, 3> temps2;
    getCubelet(temps2, state, 6);

    state["frb"] = temps[0];
    state["rbf"] = temps[1];
    state["bfr"] = temps[2];
    // front right bottom to front left bottom
    getCubelet(temps, state, 9);
    state["flb"] = temps2[0];
    state["blf"] = temps2[1];
    state["lfb"] = temps2[2];
    // front left bottom to front left upper
    state["flu"] = temps[0];
    state["luf"] = temps[1];
    state["ufl"] = temps[2];

    return "fc";
}

std::string frontAntiClockwise(std::unordered_map<std::string, std::string>& state)
{
    // Front left upper to front left bottom
    std::array<std::string, 3> temps;
    getCubelet(temps, state, 9);

    state["flb"] = state["fru"];
    state["blf"] = state["luf"];
    state["lfb"] = state["ufl"];
    // Front left bottom to front right bottom
    std::array<std::string, 3> temps2;
    getCubelet(temps2, state, 6);
    state["frb"] = temps[0];
    state["rbf"] = temps[1];
    state["bfr"] = temps[2];
    // Front right bottom to front right upper
    getCubelet(temps, state, 3);
    state["fru"] = temps2[0];
    state["urf"] = temps2[1];
    state["rfu"] = temps2[2];
    // Front right upper to front left upper
    state["flu"] = temps[0];
    state["luf"] = temps[1];
    state["ufl"] = temps[2];

    return "f`";
}

std::string frontDouble(std::unordered_map<std::string, std::string>& state)
{
    frontClockwise(state);
    frontClockwise(state);
    return "2f";
}

std::string upperClockwise(std::unordered_map<std::string, std::string>& state)
{
    // Front left upper to right end upper 
    std::array<std::string, 3> temps;
    getCubelet(temps, state, 12);

    state["lue"] = state["flu"];
    state["elu"] = state["luf"];
    state["uel"] = state["ufl"];
    // End left upper to right end upper
    std::array<std::string, 3> temps2;
    getCubelet(temps2, state, 15);
    state["reu"] = temps[0];
    state["eru"] = temps[1]; 
    state["ure"] = temps[2];
    // End right upper to right front upper
    getCubelet(temps, state, 3);
    state["rfu"] = temps2[0];
    state["urf"] = temps2[1];
    state["fru"] = temps2[2];

    // Front upper right to left upper front
    state["luf"] = temps[0];
    state["ufl"] = temps[1];
    state["flu"] = temps[2];

    return "uc";
}

std::string upperAntiClockwise(std::unordered_map<std::string, std::string>& state)
{
    // Front left upper to right front upper
    std::array<std::string, 3> fru;
    getCubelet(fru, state, 3);
    state["fru"] = state["luf"]; 
    state["urf"] = state["ufl"];
    state["rfu"] = state["flu"];

    // front right upper to end right upper
    std::array<std::string, 3> eru;
    getCubelet(eru, state, 15);
    state["eru"] = fru[2];
    state["ure"] = fru[1];
    state["reu"] = fru[0];

    // end right upper to end left upper
    std::array<std::string, 3> elu;
    getCubelet(elu, state, 12);
    state["elu"] = eru[2];
    state["lue"] = eru[0];
    state["uel"] = eru[1];

    // End left upper to front left upper
    state["flu"] = elu[1];
    state["luf"] = elu[0];
    state["ufl"] = elu[2];

    return "u`";
}

std::string upperDouble(std::unordered_map<std::string, std::string>& state)
{
    upperClockwise(state);
    upperClockwise(state);
    return "2u";
}

std::string leftClockwise(std::unordered_map<std::string, std::string>& state)
{
    // Front left upper to bottom left front
    std::array<std::string, 3> blf;
    getCubelet(blf, state, 9);
    state["flb"] = state["ufl"];
    state["blf"] = state["flu"];
    state["lfb"] = state["luf"];

    // Bottom left front to end left bottom
    std::array<std::string, 3> elb;
    getCubelet(elb, state, 21);
    state["elb"] = blf[1];
    state["ble"] = blf[0];
    state["leb"] = blf[2];

    // end left bottom to upper end left
    std::array<std::string, 3> uel;
    getCubelet(uel, state, 12);
    state["elu"] = elb[1];
    state["lue"] = elb[2];
    state["uel"] = elb[0];

    // upper end left to front left upper
    state["flu"] = uel[2];
    state["luf"] = uel[1];
    state["ufl"] = uel[0];

    return "lc";
}

std::string leftAntiClockwise(std::unordered_map<std::string, std::string>& state)
{
    // Front left upper to upper end left
    std::array<std::string, 3> uel;
    getCubelet(uel, state, 12);
    state["elu"] = state["ufl"];
    state["lue"] = state["luf"];
    state["uel"] = state["flu"];

    // upper end left to end left bottom
    std::array<std::string, 3> leb;
    getCubelet(leb, state, 21);
    state["elb"] = uel[2];
    state["ble"] = uel[0];
    state["leb"] = uel[1];

    // end left bottom to bottom left front
    std::array<std::string, 3> blf;
    getCubelet(blf, state, 9);
    state["flb"] = leb[1];
    state["blf"] = leb[0];
    state["lfb"] = leb[2];

    // bottom left front to front left upper
    state["flu"] = blf[1];
    state["luf"] = blf[2];
    state["ufl"] = blf[0];

    return "l`";
}

std::string leftDouble(std::unordered_map<std::string, std::string>& state)
{
    leftClockwise(state);
    leftClockwise(state);
    return "2l";
}

std::string rightClockwise(std::unordered_map<std::string, std::string>& state)
{
    // Front right upper to upper right end
    std::array<std::string, 3> ure;
    getCubelet(ure, state, 15);
    state["eru"] = state["urf"];
    state["ure"] = state["fru"];
    state["reu"] = state["rfu"];

    // Upper right end to end right bottom
    std::array<std::string, 3> erb;
    getCubelet(erb, state, 18);
    state["erb"] = ure[1];
    state["rbe"] = ure[2];
    state["ber"] = ure[0];

    // End right bottom to bottom front right
    std::array<std::string, 3> bfr;
    getCubelet(bfr, state, 6);
    state["frb"] = erb[2];
    state["rbf"] = erb[1];
    state["bfr"] = erb[0];

    // Bottom front right to front right upper 
    state["fru"] = bfr[2];
    state["urf"] = bfr[0];
    state["rfu"] = bfr[1];

    return "rc";
}

std::string rightAntiClockwise(std::unordered_map<std::string, std::string>& state)
{
    // Front right upper to bottom front right
    std::array<std::string, 3> bfr;
    getCubelet(bfr, state, 6);
    state["frb"] = state["urf"];
    state["rbf"] = state["rfu"];
    state["bfr"] = state["fru"];

    // Bottom front right to end right bottom 
    std::array<std::string, 3> erb;
    getCubelet(erb, state, 18);
    state["erb"] = bfr[2];
    state["rbe"] = bfr[1];
    state["ber"] = bfr[0];

    // End right bottom to upper right end
    std::array<std::string, 3> ure;
    getCubelet(ure, state, 15);
    state["eru"] = erb[2];
    state["ure"] = erb[0];
    state["reu"] = erb[1];

    // Upper right end to front right upper 
    state["fru"] = ure[1];
    state["urf"] = ure[0];
    state["rfu"] = ure[2];

    return "r`";
}

std::string rightDouble(std::unordered_map<std::string, std::string>& state)
{
    rightClockwise(state);
    rightClockwise(state);
    return "2r";
}

std::string bottomClockwise(std::unordered_map<std::string, std::string>& state)
{
    // Front left bottom to right bottom front
    std::array<std::string, 3> rbf;
    getCubelet(rbf, state, 6);
    state["frb"] = state["lfb"];
    state["rbf"] = state["flb"];
    state["bfr"] = state["blf"];

    // Right bottom front to end right bottom 
    std::array<std::string, 3> erb;
    getCubelet(erb, state, 18);
    state["erb"] = rbf[1]; 
    state["rbe"] = rbf[0];
    state["ber"] = rbf[2];

    // End right bottom to left end bottom 
    std::array<std::string, 3> leb;
    getCubelet(leb, state, 21);
    state["elb"] = erb[1];
    state["ble"] = erb[2];
    state["leb"] = erb[0];

    // left end bottom to front left bottom 
    state["flb"] = leb[2];
    state["blf"] = leb[1];
    state["lfb"] = leb[0];

    return "bc";
}

std::string bottomAntiClockwise(std::unordered_map<std::string, std::string>& state)
{
    // Front left bottom to left end bottom
    std::array<std::string, 3> leb;
    getCubelet(leb, state, 21);
    state["elb"] = state["lfb"];
    state["ble"] = state["blf"];
    state["leb"] = state["flb"];

    // Left end bottom to end right bottom
    std::array<std::string, 3> erb;
    getCubelet(erb, state, 18);
    state["erb"] = leb[2];
    state["rbe"] = leb[0];
    state["ber"] = leb[1];

    // End right bottom to right bottom front
    std::array<std::string, 3> rbf;
    getCubelet(rbf, state, 6);
    state["frb"] = erb[1];
    state["rbf"] = erb[0];
    state["bfr"] = erb[2];

    // Right bottom front to front left bottom
    state["flb"] = rbf[1];
    state["blf"] = rbf[2];
    state["lfb"] = rbf[0];

    return "b`";
}

std::string bottomDouble(std::unordered_map<std::string, std::string>& state)
{
    bottomClockwise(state);
    bottomClockwise(state);
    return "2b";
}

std::string endClockwise(std::unordered_map<std::string, std::string>& state)
{
    // End right upper to end left upper
    std::array<std::string, 3> elu;
    getCubelet(elu, state, 12);
    state["elu"] = state["eru"];
    state["lue"] = state["ure"];
    state["uel"] = state["reu"];
    // End left upper to end left bottom
    std::array<std::string, 3> elb;
    getCubelet(elb, state, 21);
    state["elb"] = elu[0];
    state["ble"] = elu[1];
    state["leb"] = elu[2];
    // End left bottom to end right bottom
    std::array<std::string, 3> erb;
    getCubelet(erb, state, 18);
    state["erb"] = elb[0];
    state["rbe"] = elb[1];
    state["ber"] = elb[2];
    // End right bottom to end right upper
    state["eru"] = erb[0];
    state["ure"] = erb[1];
    state["reu"] = erb[2];

    return "e";
}

std::string endAntiClockwise(std::unordered_map<std::string, std::string>& state)
{
    // End left upper to end right upper 
    std::array<std::string, 3> eru;
    getCubelet(eru, state, 15);
    state["eru"] = state["elu"];
    state["ure"] = state["lue"];
    state["reu"] = state["uel"];
    // End right upper to end right bottom
    std::array<std::string, 3> erb;
    getCubelet(erb, state, 18);
    state["erb"] = eru[0];
    state["rbe"] = eru[1];
    state["ber"] = eru[2];
    // End right bottom to end left bottom
    std::array<std::string, 3> elb;
    getCubelet(elb, state, 21);
    state["elb"] = erb[0];
    state["ble"] = erb[1];
    state["leb"] = erb[2];

    // End left bottom to end left upper
    state["elu"] = elb[0];
    state["lue"] = elb[1];
    state["uel"] = elb[2];

    return "e'";
}

std::string endDouble(std::unordered_map<std::string, std::string>& state)
{
    endClockwise(state);
    endClockwise(state);
    return "2e";
}

rFunctions rotations()
{
    rFunctions r = {
        frontDouble, upperDouble, leftDouble, rightDouble, bottomDouble, endDouble,
        frontClockwise, frontAntiClockwise, upperClockwise, upperAntiClockwise, leftClockwise, leftAntiClockwise,
        rightClockwise, rightAntiClockwise, bottomClockwise, bottomAntiClockwise, endClockwise, endAntiClockwise
    };
    return r;
}