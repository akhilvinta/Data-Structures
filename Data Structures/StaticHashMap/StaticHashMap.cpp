//
//  map.cpp
//  Map_Part2
//
//  Created by Akhil Vinta on 1/28/20.
//  Copyright © 2020 Akhil Vinta. All rights reserved.
//

#include "Map.h"
#include <iostream>
using namespace std;


Map :: Pair :: Pair(KeyType k, ValueType v){
    this -> k = k;
    this -> v = v;
}

Map :: Pair :: Pair(){}

Map :: Map(){
    list_size = 0;
    head = nullptr;
    tail = nullptr;
}

Map :: ~Map(){
    //if map is empty, just reset it, but don't try to access any of its elements
    if(this -> empty()){
        head = nullptr;
        tail = nullptr;
        return;
    }
    //otherwise, deallocate every node individually, and set head and tail equal to nullptr
    else{
        Node *n = head;
        while(n != nullptr){
            Node *m = n;
            n = n -> next;
            delete m;
        }
        head = nullptr;
        tail = nullptr;
    }
    list_size = 0;
}

Map &Map :: operator=(const Map& old){
   
    this -> ~Map();
    
    Node* n = old.head;
    
    while(n != nullptr){
        this -> insert(n -> value.k, n -> value.v);
        n = n -> next;
    }
    
    return *this;
}
    
Map :: Map(const Map& old){
            
    if(old.empty())
        return;
    
    this -> list_size = 0;
    this -> head = nullptr;
    this -> tail = nullptr;
        
    Node *n = old.head;

    while(n != nullptr){
        this -> insert(n -> value.k, n -> value.v);
        n = n -> next;
    }
    
}

bool Map :: empty() const{
    
    return (list_size == 0 || head == nullptr);
}

int Map :: size() const{
    return list_size;
}

bool Map :: insert(const KeyType& key, const ValueType& value){
    
    //if list is empty, then call separate helper function insertFirstElement, to properly designate first node
    if(this -> empty()){
        this -> insertFirstElement(key, value);
        return true;
    }
    //else, search if the desired key is already in the list
    if(this -> contains(key)){
        return false;
    }
    //else, call helper function addToEnd, which will properly designate the node to the end of the list
    addToEnd(key,value);
    list_size++;
    return true;
    
}

bool Map :: update(const KeyType& key, const ValueType& value){
    if(this -> empty())
        return false;
    
    Node *n = head;
    
    while(n != nullptr){
        if(n -> value.k == key){
            n -> value.v = value;
            return true;
        }
        n = n -> next;
    }
    return false;
}

bool Map :: insertOrUpdate(const KeyType& key, const ValueType& value){
    
    if(this -> empty()){
        insert(key,value);
        return true;
    }
    
    if(this -> contains(key)){
        update(key, value);
        return true;
    }
    
    insert(key,value);
    return true;
}

bool Map :: erase(const KeyType& key){
    //if map is empty return false
    if(this -> empty())
        return false;
    
    list_size--;
    
    //if map has only one element, delete it and set size to 0
    if(head == tail && head -> value.k == key){
        Node *n = head;
        head = tail = nullptr;
        delete n;
        list_size = 0;
        return true;
    }
    //if the tail node contains the desired key, delete the last node and set tail to new last node
    if(tail -> value.k == key){
        Node* n = tail;
        tail = tail -> prev;
        tail -> next = nullptr;
        delete n; return true;
    }
    //if the head node contains the desired key, delete the frist node and set head to new first node
    if(head -> value.k == key){
        Node* n = head;
        head = head -> next;
        head -> prev = nullptr;
        delete n; return true;
    }
    
    //if the desired key is contained in the middle, then find node and delete appropriately
    //n -> next is okay because I know that the desired node will not be the tail node
    Node *n = head; Node *m = new Node;
    while(n -> next!= nullptr){
        if(n -> next -> value.k == key)
            break;
        n = n -> next;
    }
    //if desired key is not found, return false and don't decrement the size of map
    if(n -> next == nullptr){
        list_size++;
        return false;
    }
    //desired key is somewhere in the middle of the map, so adjust appropriately and delete
    m = n -> next; n -> next = n -> next -> next;
    n -> next -> prev = n; delete m;
    
    return true;
}


bool Map :: contains(const KeyType& key) const{
    if(this -> empty())
        return false;
    
    Node *n = head;
    while(n != nullptr){
        if(n -> value.k == key)
            return true;
        n = n -> next;
    }
    return false;
}

bool Map :: get(const KeyType& key, ValueType& value) const {
    if(this -> empty())
        return false;
    
    Node* n = head;
    
    while(n != nullptr){
        if(n -> value.k == key){
            value = n -> value.v;
            return true;
        }
        n = n -> next;
    }
    
    return false;
}

bool Map :: get(int i, KeyType& key, ValueType& value) const {
    if(this -> empty())
        return false;
    
    int count = 0;
    Node* n = head;
    //iterate until list reaches "element" i
    while(n != nullptr){
        if(i == count){
            key = n -> value.k; value = n -> value.v;
            return true;
        }
        count++;
        n = n -> next;
    }

    return false;

}

void Map :: swap(Map& other){
    
    Map temp; int ph;
    
    //swapping head of lists essentially swaps the heads
    temp.head = this -> head;
    this -> head = other.head;
    other.head = temp.head;
    
    ph = this -> size();
    this -> list_size = other.size();
    other.list_size = ph;
}


void Map :: insertFirstElement(const KeyType& key, const ValueType& value){
    //function sets head and tail to the desired node value, and then sets head -> prev and tail -> next to nullptr
    head = new Node;
    head -> value.k = key;
    head -> value.v = value;
    tail = head;
    head -> next = head -> prev = nullptr;
    tail -> next = tail -> prev = nullptr;
    list_size++;
}

void Map :: addToEnd(const KeyType& key, const ValueType& value){
    
    //this function properly designates the desired node to the end of the list, by connecting the current last to desired node, then connecting node -> prev to current last, and then reassigning last to the desired node.
    if(this -> empty()){
        insertFirstElement(key,value); return;}

    Node *n = new Node;
    n -> value.k = key;
    n -> value.v = value;
    n -> prev = tail;
    n -> prev -> next = n;
    tail = n;
    tail -> next = nullptr;
}

bool combine(const Map& m1, const Map& m2, Map& result){
    
    
    if(!result.empty())
        result.~Map();
    
    KeyType k;
    ValueType v;
    bool ret = true;
    //iterate through m1
    for(int i = 0; i < m1.size(); i++){
        m1.get(i, k, v);
        //if this element key in m1 is not shared in m2, then add it to the result map
        if(!m2.contains(k))
            result.insert(k,v);
        //if this element key in m1 is shared in m2, then check if the values of both elements are the same
        if(m2.contains(k)){
            ValueType v2;
            m2.get(k,v2);
            //if both element values are the same, add element to the result map
            if(v2 == v)
                result.insert(k,v);
            //otherwise do nothing, eventually return false;
            else
                ret = false;
        }
    }
    //now iterate through m2, and add any elements that are not shared in m1 to the result map
    for(int i = 0; i < m2.size(); i++){
        m2.get(i,k,v);
        if(!m1.contains(k))
            result.insert(k,v);
    }
    return ret;
}

void reassign(const Map& m, Map& result){
   
    if(!result.empty())
        result.~Map();
    
    KeyType k;
    ValueType v;
    KeyType place_holder;
    
    //if m only contains one element, then place it in result and return
    if(m.size() == 1){
        m.get(0,k,v);
        result.insert(k,v);
        return;
    }
    
    m.get(0,k,v);
    place_holder = k;
    
    //else, iterate through m, attaining all the values, but keep a KeyType place_holder to keep the key one iteration behind the value, so that the values to their appropriate keys are essentially shifted
    for(int i = 1; i < m.size(); i++){
        m.get(i,k,v);
        result.insert(place_holder,v);
       place_holder = k;
    }
    
    m.get(0,k,v);
    result.insert(place_holder,v);
    
}

void Map :: dump() const{
    if(this -> empty())
        return;
    Node *n = head;
    while(n != nullptr){
        cerr << n -> value.k  << " :: " << n -> value.v << endl;
        n = n -> next;
    }

}


