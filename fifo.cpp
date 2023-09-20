//  file that implements first-in first-out replacement policy
#include "dataStructures.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <list>




using namespace std;


void fifo(char* tracefile, int nframes, char* type) {

    // Initialize counters
    int events = 0; // count events
    int reads = 0;  // count reads
    int writes = 0; // count writes

    // Set mode to debug if argv[4] is debug, not quiet
    bool debug = (strcmp(type, "debug") == 0);

    // Open file
    ifstream file(tracefile);
    // Check if file opened, return error and die if not
    if (!file.is_open()) {
        cout << "File can't be read or found?\n";
        return;
    }

    // Initialize head and tail pointers of linked list
    Node* head = nullptr;
    Node* tail = nullptr;

    // Read each memory access from tracefile
    memaccess tempMem;
    while (file >> hex >> tempMem.addr >> tempMem.rw) {
        // Make adderess into pagenumber by diving by pagesize
        tempMem.addr /= 4096;
        // Each run, increment event
        events++;

        // If debug print
        if (debug) {
            cout << "Memory access #" << events << " is " << tempMem.addr << tempMem.rw << ". " << endl;
        }

        // Flag if current mem access is already in page table
        bool next = false;

        // Check each node in linked list if it matches the current memory access
        for (Node* current = head; current != nullptr; current = current->next) {
            // Memory access already exists in page table, set flag true
            if (current->data.addr == tempMem.addr) {
                next = true;
                // If entry in page table was read and current access is write then update page table entry with write
                if (current->data.rw == 'R' && tempMem.rw == 'W') {
                    current->data.rw = 'W';
                }
                break;
            }
        }

        // If memory access is in the page table go the the next access
        if (next) {
            continue;
        } else {
            // If there is space in page table add the memory access to the next open slot
            if (reads < nframes) {
                // Create new node and add to tail of linked list
                Node* newNode = new Node{tempMem, nullptr};
                if (tail == nullptr) {
                    head = tail = newNode;
                } else {
                    tail->next = newNode;
                    tail = newNode;
                }
                reads++;
            }
            // If page table is full, remove oldest entry which is the first entry in the linked list
            else {
                // If removed entry was write, increment write count
                if (head->data.rw == 'W') {
                    writes++;
                }
                // Remove first node from linked list
                Node* temp = head;
                head = head->next;
                delete temp;

                //  Make new node and add to tail
                Node* newNode = new Node{tempMem, nullptr};
                if (tail == nullptr) {
                    head = tail = newNode;
                } else {
                    tail->next = newNode;
                    tail = newNode;
                }

                // Increment read
                reads++;
            }
        }
    }

    // Close file
    file.close();

    // Delete all nodes in the linked list
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    //  quiet mode output: mem frames, events in trace, disk reads, disk writes.
    cout << "Total memory frames: \t" << nframes << endl;
    cout << "Events in trace: \t" << events << endl;
    cout << "Total disk reads: \t" << reads << endl;
    cout << "Total disk writes: \t" << writes << endl;

}// end FIFO