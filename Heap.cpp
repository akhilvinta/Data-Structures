//
//  Heap.cpp
//  DataStructures
//
//  Created by Akhil Vinta on 3/24/20.
//  Copyright © 2020 Akhil Vinta. All rights reserved.
//

#include "Heap.hpp"
#include <cmath>
#include <iostream>
using namespace std;

Heap :: Heap(){
    level = 0;
    m_size = 0;
}

int Heap :: top(){
    if(m_size == 0) cout << "Heap is empty" << endl;
    return arr[1][0];
}

void Heap :: insert(int value){
    level = (m_size == 0) ? 1 : (int)log2(m_size) + 1;
    if(m_size == 0){
        arr[level][m_size] = value;
    }
}

