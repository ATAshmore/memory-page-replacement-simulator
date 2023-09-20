//  makes the dataStructures accessible to all the policies
#ifndef DATA_STRUCTURES_HPP
#define DATA_STRUCTURES_HPP

struct memaccess {
    unsigned addr;
    char rw;
};

struct Node {
    memaccess data;
    Node* next;
    Node* prev;
};



#endif // DATA_STRUCTURES_HPP