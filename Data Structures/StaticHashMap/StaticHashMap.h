//
//  map.hpp
//  Map_Part2
//
//  Created by Akhil Vinta on 1/28/20.
//  Copyright © 2020 Akhil Vinta. All rights reserved.
//

#ifndef map_h
#define map_h

#include <stdio.h>
#include <string>

using KeyType = std::string;
using ValueType = double;



class Map
{
  public:
    Map(); 
    ~Map();
    Map(const Map& old);
    Map &operator=(const Map& old);
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    void dump() const;

private:
    
    void insertFirstElement(const KeyType& key, const ValueType& value);
    void addToEnd(const KeyType& key, const ValueType& value);
    
    struct Pair{
        KeyType k;
        ValueType v;
        Pair(KeyType k, ValueType v);
        Pair();
    };

    struct Node{
        Pair value;
        Node* next;
        Node* prev;
    };
    
    Node* head;
    Node* tail;
    int list_size;

};

    bool combine(const Map& m1, const Map& m2, Map& result);
    void reassign(const Map& m, Map& result);


#endif /* map_h */
