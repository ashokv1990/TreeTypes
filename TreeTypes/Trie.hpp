//
//  Trie.hpp
//  TreeTypes
//
//  Created by Ashok  on 11/29/15.
//  Copyright © 2015 b. All rights reserved.
//

#ifndef Trie_hpp
#define Trie_hpp

#include <stdio.h>
#include <map>
#include <string>
#include <iostream>
class Trie
{
    
public:
    Trie():mmap(),value(0),key('\0'),hasvalue(false)
    {
        mmap.clear();
    }
    
    ~Trie()
    {
        for(std::map<char , Trie*>::iterator it = mmap.begin() ; it != mmap.end() ; it++)
        {
            if(it->second != NULL)
            delete it->second;
        }
    }
    void print();
    void insert(std::string key , int value);
    bool remove(std::string key);
    int searchval(std::string key);
    std::tuple<bool ,int> search(std::string key);
    int getval();
    bool hasval();
    char getkey();
   
private:
    struct deleteres
    {
        bool isthere;
        bool deletechild;
    };
    
    
    std::map<char , Trie*> mmap;
    struct deleteres removeinternal(std::string key);

    bool hasvalue;
    int value;
    char key;
   
    
};

#endif /* Trie_hpp */
