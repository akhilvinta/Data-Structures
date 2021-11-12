//
//  Queue.cpp
//  DataStructures
//
//  Created by Akhil Vinta on 3/23/20.
//  Copyright © 2020 Akhil Vinta. All rights reserved.
//

#include "Queue.hpp"
#include <iostream>
using namespace std;


Queue :: Queue(){
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

Queue :: ~Queue(){
    Node3* n = head;
    Node3* m;
    while(n != nullptr){
        m = n->next;
        delete n;
        n = m;
    }
}

void Queue :: push(int element){
    if(m_size == 0) {
        head = new Node3();
        head->value = element;
        head->next = nullptr;
        tail = head;
    }
    else if(m_size == 1){
        tail = new Node3();
        tail->value = element;
        head->next = tail;
        tail->next = nullptr;
    }
    else{
        Node3* n = new Node3();
        n->value = element;
        tail -> next = n;
        tail = n;
        tail -> next = nullptr;
    }
    m_size++;
    
}

void Queue :: pop(){
    if(size() == 0){
        cout << "Queue is empty" << endl;
        return;
    }
    
    Node3* m = head->next;
    delete head;
    
    if(m == nullptr) head = nullptr;
    else head = m;
    
    m_size--;
    
}

int Queue :: top(){
    if(head == nullptr)
        cout << "Queue is empty" << endl;
    return head->value;
}


bool Queue :: isEmpty(){
    return m_size == 0;
}

int Queue:: size(){
    return m_size;
}

void Queue :: printStuff(){
    Node3* n = head;
    if(n == nullptr) cout << "queue is empty";
    while(n != nullptr){
        cout << n-> value << " ";
        n = n->next;
    }
    cout << endl;
}


