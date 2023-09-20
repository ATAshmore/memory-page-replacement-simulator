//  main interface of the simulator, it takes user input in two forms
//  g++ for cpp. gcc for c

//  each trace is a series of lines, each listing a hexadecimal memory address followed by a R or W for read or write
//  can scan in one memory by using fscanf():
//  unsigned addr; char
//      rw;
//      ...
//      fscanf(file,"%x %c", &addr, &rw);
/*
    use a single level page
    keep track of what pages are loaded into memory
    chcek to see if the corresponding page is loaded as it process each memory event fro mthe trace
    if not, it should choose a page to remove from memory
    if page replaced is dirty (previous accesses is a Write access), should be saved to disk.
    new page is loaded into memory from disk, and page table is updated
    assume all page and page frames are 4KB(4096 bytes)
    dont need to read and write data from disk, just keep track fo disk reads and writes

    implement FIFO, LRU, Segmented FIFO/vms(no more)

*/
//g++ -o memsim memsim.cpp policies.hpp lru.cpp fifo.cpp dataStructures.hpp dataStructures.cpp -std=c++11

#include "dataStructures.hpp"
#include "policies.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <list>

//added for nullptr error
//#include <cstddef>




using namespace std;

//  keep here
int main(int argc, char *argv[]){
    //  check if input is valid number of arguments. if hit, not valid
    if(argc != 5 && argc != 6){
        cout << "USAGE: ./memsim tracefile nFrames policy [percentage] quiet/debug" << endl;
        return 0;
    }

    //  command example: ./memsim <tracefile> <nFrames> <policy> [percentage] <quiet/debug>
    //  seperate command line arguements
    string traceFile = argv[1];     //  tracefile name: sixpack.trace or bzip.trace
    int nFrames = stoi(argv[2]);    //  # of frames
    string policy = argv[3];        //  policy name: fifo, lru


    if(policy == "fifo") {
        fifo(argv[1], nFrames, argv[4]);
        return 0;
    }
    if(policy == "lru"){
        lru(argv[1], nFrames, argv[4]);
        return 0;
    }

    printf("failed");

    return 0;

}// end main

