//
//  main.cpp
//  linkedlist
//
//  Created by Akhil Vinta on 1/22/20.
//  Copyright © 2020 Akhil Vinta. All rights reserved.
//

#include <iostream>

using KeyType = std::string;
using ValueType = int;
using namespace std;

struct Pair{

    KeyType k;
    ValueType v;
    
    Pair(KeyType k, ValueType v);
    Pair();
};

Pair :: Pair(KeyType k, ValueType v){
    this -> k = k;
    this -> v = v;
}

Pair :: Pair(){
    k = "";
    v = 0;
}

struct Node{
    Pair value;
    Node* next;
    Node* prev;
};


class LinkedList{
   
    public:
        LinkedList();
        void addToStart(Pair element);
        void addToEnd(Pair element);

        void remove(Pair element);
        void addElementAfter(Pair before, Pair element);
        void addElementBefore(Pair after, Pair element);

        void printFront();
        void printBack();
    
    private:
        void addFirstElement(Pair element);
        const bool isEmpty();

        Node * head;
        Node * tail;
};


LinkedList :: LinkedList(){
    head = nullptr;
    tail = nullptr;
}

void LinkedList :: printFront(){
    Node *n = head;
    while(n != nullptr){
        cout << n -> value.k << endl; n = n -> next; }
}

void LinkedList :: printBack(){
    Node *n = tail;
    while(n != nullptr){
        cout << n -> value.k << endl; n = n -> prev;}
}

const bool LinkedList :: isEmpty(){
    return (head == nullptr);
}

void LinkedList :: addFirstElement(Pair element){
    head = new Node;
    head -> value = element;
    tail = head;
    head -> next = head -> prev = nullptr;
    tail -> next = tail -> prev = nullptr;
}

void LinkedList :: addToStart(Pair element){
    if(this -> isEmpty() == true){
        addFirstElement(element);
        return;
    }
    Node *n = new Node;
    n -> value = element;
    n -> next = head;
    n -> next -> prev = n;
    head = n;
    head -> prev = nullptr;
}

void LinkedList :: addToEnd(Pair element){
    if(this -> isEmpty() == true){
        addFirstElement(element); return;}

    Node *n = new Node;
    n -> value = element;
    n -> prev = tail;
    n -> prev -> next = n;
    tail = n;
    tail -> next = nullptr;
}



void LinkedList :: addElementAfter(Pair before, Pair element){

    if(this -> isEmpty())
        return;

    Node* m = head;
    
    if(m != nullptr && m -> value.k == before.k);
    else{
        while(m -> next != nullptr){
            m = m -> next;
            if(m -> value.k == before.k)
                break;
        }
    }

    if(m -> next == nullptr && m -> value.k != before.k) return;
    
    if(m -> next == nullptr){
        addToEnd(element); return;
    }
    
    Node *n = new Node;
    n -> value = element; n -> prev = m; n -> next = m -> next;
    m -> next = n; n -> next -> prev = n;
    
}

void LinkedList :: addElementBefore(Pair after, Pair element){
   
    if(this -> isEmpty())
        return;
    if(head -> value.k == after.k){
        this -> addToStart(element); return;
    }
    Node *n = head;
    
    while(n -> next != nullptr){
        n = n -> next;
        if(n -> value.k == after.k)
            break;
    }
    
    if(n -> next == nullptr && n -> value.k != after.k) return;

    Node *m = new Node;
   
    m -> value = element; m -> next = n; m -> prev = n -> prev;
    n -> prev = m; m -> prev -> next = m;
}



void LinkedList :: remove(Pair element){
    
    if(this -> isEmpty())
        return;
    
    if(head == tail && head -> value.k == element.k){
        Node *n = head;
        head = tail = nullptr;
        delete n;
        return;
    }
    
    if(tail -> value.k == element.k){
        Node* n = tail;
        tail = tail -> prev; tail -> next = nullptr;
        delete n; return;
    }
    
    if(head -> value.k == element.k){
        Node* n = head;
        head = head -> next; head -> prev = nullptr;
        delete n; return;
    }
    
    
    Node *n = head; Node *m = new Node;
    while(n -> next!= nullptr){
        if(n -> next -> value.k == element.k)
            break;
        n = n -> next;
    }
    if(n -> next == nullptr)
        return;
    
    m = n -> next; n -> next = n -> next -> next;
    n -> next -> prev = n; delete m;
    
}


