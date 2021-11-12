//
//  Queue.hpp
//  DataStructures
//
//  Created by Akhil Vinta on 3/23/20.
//  Copyright © 2020 Akhil Vinta. All rights reserved.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>

struct Node3{
    
    int value;
    Node3* next;
};


class Queue{
    
public:
    
    Queue();
    ~Queue();
    void push(int element);
    int size();
    void pop();
    int top();
    bool isEmpty();
    void printStuff();
    
private:
    
    Node3* head;
    Node3* tail;
    int m_size;
};



#endif /* Queue_hpp */
