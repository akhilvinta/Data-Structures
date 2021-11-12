//
//  BinarySearchTree.hpp
//  DataStructures
//
//  Created by Akhil Vinta on 3/23/20.
//  Copyright © 2020 Akhil Vinta. All rights reserved.
//

#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include <stdio.h>


struct Node{
    
    int value;
    int num;
    Node* parent;
    Node* child_left;
    Node* child_right;
};

class BinaryTree{


public:
    BinaryTree();
    void addValue(int insert); //O(logN)
    void addValue(int insert, int num);
    Node* getValue(int insert); //O(N)
    bool removeValue(int insert); //O(2logN)
    Node* getBottomRight(Node* n); //max, O(N), but in most cases O(logN)
    Node* getHead(); // O(1)
    void print(); //directs to printValue: O(N)
    int size(); //O(1)
    bool isEmpty(); //O(1);


private:
    void printShit(Node* n); // O(N)
    int* printStuff(Node* n);
    void addFirstValue(int insert, int num); // O(1)
    Node* head;
    int m_size;
    
};

#endif /* BinarySearchTree_hpp */
