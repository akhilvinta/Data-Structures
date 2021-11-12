//
//  BinarySearchTree.cpp
//  DataStructures
//
//  Created by Akhil Vinta on 3/23/20.
//  Copyright © 2020 Akhil Vinta. All rights reserved.
//

#include "BinarySearchTree.hpp"
#include <iostream>
#include <vector>
using namespace std;

BinaryTree :: BinaryTree(){
    head = nullptr;
    m_size = 0;
}

bool BinaryTree :: removeValue(int insert){
    
    Node* cur = getValue(insert);
    if(cur == nullptr) return false;
    Node* temp = cur;
    
    if(cur->child_left == nullptr && cur->child_right == nullptr) temp = nullptr;
    else if(cur->child_left == nullptr) temp = cur->child_right;
    else if(cur->child_right == nullptr) temp = cur->child_left;
    
    if(cur->child_left == nullptr || cur->child_right == nullptr){
        if(cur->value < cur->parent->value)
            cur -> parent -> child_left = temp;
        else cur -> parent -> child_right = temp;
        if(!(cur->child_left == nullptr && cur->child_right == nullptr))
            temp -> parent = cur -> parent;
        delete cur; return true;
    }
    
    Node* bottomRight = getBottomRight(cur->child_left);
    cur->value = bottomRight->value;

    if(bottomRight->value < bottomRight->parent->value)
        bottomRight -> parent -> child_left = nullptr;
    else bottomRight -> parent -> child_right = nullptr;
    delete bottomRight;
    
    return true;
}

Node* BinaryTree :: getBottomRight(Node* n){

    if(n->child_right == nullptr && n->child_left == nullptr)
        return n;
    
    if(n->child_right != nullptr)
        n = getBottomRight(n->child_right);
    else if(n->child_left != nullptr)
        n = getBottomRight(n->child_left);
    
    return n;
    
}

Node* BinaryTree :: getValue(int insert){
    
    if(isEmpty()) return nullptr;
    
    Node* cur = head;
    while(cur != nullptr){
        if(cur -> value == insert) return cur;
        cur = (insert > cur->value) ? cur->child_right : cur->child_left;
    }
    return nullptr;
}


void BinaryTree :: addValue(int insert, int num){
    
    if(this -> isEmpty()){
        addFirstValue(insert, num);
        return;
    }
    //in this case, the n
    Node* n = head; Node* m = n; bool greater;
    while(n != nullptr){
        if(insert == n->value) return;
        greater = (insert > n->value) ? true : false;
        m = (greater) ? n->child_right : n->child_left;
        
        if(m == nullptr){
            m = new Node();
            m -> parent = n;
            if(greater) m -> parent -> child_right = m;
            if(!greater) m -> parent -> child_left = m;
            n = m;
            break;
        }
        n = m;
    }
    n->value = insert;
    n -> child_left = nullptr; n -> child_right = nullptr;
    m_size++;
}

void BinaryTree :: addValue(int insert){
    addValue(insert, 0);
}


void BinaryTree:: addFirstValue(int insert, int num){
    head = new Node();
    head -> value = insert;
    head -> child_right = nullptr; head -> child_left = nullptr;
    head -> parent = nullptr;
    m_size++;
}


Node* BinaryTree :: getHead(){
    if(head == nullptr){
        cout << "Tree is Empty" << endl;
        return nullptr;
    }
    return head;
}

int BinaryTree :: size(){ return m_size; }
bool BinaryTree :: isEmpty(){ return size() == 0;}
void BinaryTree :: print(){ printValues(head); }

void BinaryTree :: printValues(Node* n){
   
    static vector<Node*> goat;
    
    if(n == nullptr) return;
    printValues(n->child_left);
    printValues(n->child_right);
    
    goat.push_back(n);
    
    for(int i  =0; i < goat.size(); i++)
        cout << goat[i]->value << endl;

}


int main(){
    
    BinaryTree b;
    
    b.addValue(5);
    b.addValue(7);
    b.addValue(3);
    b.addValue(4);
    b.addValue(16);
    b.addValue(25);
    
    b.print();
    
}

