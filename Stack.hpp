//
//  Stack.hpp
//  DataStructures
//
//  Created by Akhil Vinta on 3/23/20.
//  Copyright © 2020 Akhil Vinta. All rights reserved.
//

#ifndef Stack_hpp
#define Stack_hpp

#include <stdio.h>

struct Node2{
    
    int value;
    Node2* next;
};


class Stack{
    
public:
    
    Stack();
    ~Stack();
    void push(int element);
    int size();
    void pop();
    int top();
    bool isEmpty();
    void printStuff();
    
private:
    
    Node2* head;
    int m_size;
};



#endif /* Stack_hpp */
