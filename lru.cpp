//  file that implements least recently used policy
#include "dataStructures.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <list>

using namespace std;

//  linked list lru
void lru(char* tracefile, int nframes, char* type) {

    //  initialize list
    list<memaccess> lru;
    //  initialize counts
    int events = 0; //  total memory access
    int reads = 0;  //  total reads
    int writes = 0; //  total dirty page writes

    // Set mode to debug if argv[4] is debug, not quiet
    bool debug = (strcmp(type,"debug") == 0);


    
    //  open the trace file
    FILE* file;
    file = fopen(tracefile,"r");
    if(file == NULL) {
        cout << "cant open or file not found!\n";
    }
    
    memaccess tempMem;

    //  read the tracefile
    while(fscanf(file,"%x %c",&tempMem.addr,&tempMem.rw) !=EOF) {
        // Make adderess into pagenumber by diving by pagesize
        tempMem.addr /= 4096;
        // Each run, increment event
        events++;
        
        //  if debug print
        if(debug) {
            cout << "Memory access #" << events << " is " << tempMem.addr << tempMem.rw << ". " << endl;
        }

        bool next = false;
        //  search for page in list and update if found
        for(auto itsHim = lru.begin(); itsHim != lru.end(); ++itsHim) {
            //  page already in memory so move to back of list
            if(itsHim->addr == tempMem.addr) {
                next = true; //  skip to the next mem access
                //  make copy of the mem access
                memaccess tempMem2 = *itsHim;
                //If read operation is a write, then update it upon placing it to the back.
                //  if memaccess was read then ne won e is write, update to write
                if(itsHim->rw == 'R' && tempMem.rw == 'W') {
                    tempMem2.rw='W';
                }
                lru.erase(itsHim);  //  remove old mem access from list
                lru.push_back(tempMem2);   //  add updated mem access to back of list
                break;  //  leave for loop
            }
        }

        //  if tthe page is already in memory skip to next mem access
        if(next)
            continue;
        else {
            //  if space in memory, add page to the back of the list
            if(lru.size() < (unsigned)nframes) {
                lru.push_back(tempMem);
                reads++;    //  increment page faults
            }
            //  if full, remove lru page(front of list). add new page to back of list
            else {
                //  if removed page dirty, increment dirty page writes
                if(lru.front().rw == 'W') {
                    writes++;
                } 
                lru.pop_front();
                lru.push_back(tempMem);
                reads++;    //  increment number of page faults
            }
        }

    }
    
    //  close file
    fclose(file);
    //  print performance
    cout << "total memory frames: " << nframes << endl;
    cout << "events in trace: " << events << endl;
    cout << "total disk reads: " << reads << endl;
    cout << "total disk writes: " << writes << endl;



}// end LRU