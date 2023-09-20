//  declares policies to be used by the simulator
#ifndef POLICIES_HPP
#define POLICIES_HPP

#include "dataStructures.hpp"

void fifo(char* tracefile, int nFrames, char* type);

void lru(char* tracefile, int nframes, char* type);

#endif//POLICIES_HPP