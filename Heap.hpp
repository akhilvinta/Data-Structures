//
//  Heap.hpp
//  DataStructures
//
//  Created by Akhil Vinta on 3/24/20.
//  Copyright © 2020 Akhil Vinta. All rights reserved.
//

#ifndef Heap_hpp
#define Heap_hpp

#include <stdio.h>
#include <vector>

struct Node4{
    
    int value;
    int num;
    Node4* child_left;
    Node4* child_right;
    
};

class Heap{
    
public:
    Heap();
    int top();
    void insert(int value);
    
    
private:
    int arr[18][262144];
    int level;
    int m_size;
};




#endif /* Heap_hpp */
