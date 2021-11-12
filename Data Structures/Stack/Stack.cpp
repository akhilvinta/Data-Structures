//
//  Stack.cpp
//  DataStructures
//
//  Created by Akhil Vinta on 3/23/20.
//  Copyright © 2020 Akhil Vinta. All rights reserved.
//

#include "Stack.hpp"
#include <iostream>
using namespace std;


Stack :: Stack(){
    head = nullptr;
    m_size = 0;
}

Stack :: ~Stack(){
    
    Node2* n = head;
    Node2* m;
    while(n != nullptr){
        m = n->next;
        delete n;
        n = m;
    }
    
}

void Stack :: push(int element){
    if(m_size == 0) {
        head = new Node2();
        head->value = element;
        head->next = nullptr;
    }
    else{
        Node2* n = new Node2();
        n->value = element;
        n->next = head;
        Node2* m = n;
        n = head;
        head = m;
    }
    m_size++;
    
}

void Stack :: pop(){
    if(size() == 0){
        cout << "Stack is empty" << endl;
        return;
    }
    
    Node2* m = head->next;
    delete head;
    
    if(m == nullptr) head = nullptr;
    else head = m;
    
    m_size--;
    
}

int Stack :: top(){
    if(head == nullptr)
        cout << "Stack is empty" << endl;
    return head->value;
}


bool Stack :: isEmpty(){
    return m_size == 0;
}

int Stack:: size(){
    return m_size;
}

void Stack :: printStuff(){
    Node2* n = head;
    while(n != nullptr){
        cout << n-> value << " ";
        n = n->next;
    }
    cout << endl;
}

