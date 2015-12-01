//
//  Trie.cpp
//  TreeTypes
//
//  Created by Ashok  on 11/29/15.
//  Copyright © 2015 b. All rights reserved.
//

#include "Trie.hpp"
#include <queue>




int Trie::getval()
{
    return value;
}

bool Trie::hasval()
{
    return hasvalue;
}

char Trie::getkey()
{
    return key;
}


void Trie::insert(std::string key , int value)
{
   
    if(key.size() == 1)
    {
        char first = key[0];
        auto it = mmap.find(first);
        
        if(it == mmap.end())
        { mmap.insert(std::make_pair(first , new Trie()));
          it = mmap.find(first);
          it->second->key = first;
        }
        
        
     
        it->second->hasvalue = true;
        it->second->value = value;
        return;
    }
    
    char first = key[0];
    
    auto it = mmap.find(first);
    
    if(it == mmap.end())
    {
        mmap.insert(std::make_pair(first , new Trie()));
        it = mmap.find(first);
        it->second->key = first;
        it->second->hasvalue = false;
        it->second->value = 0;
     
    }
    
    it->second->insert(key.substr(1 , std::string::npos) , value);
    
    
}


bool Trie::remove(std::string key)
{
    Trie::deleteres d = removeinternal(key);
    if(d.isthere)
    {
        return true;
    }
    return false;
}

struct Trie::deleteres Trie::removeinternal(std::string key)
{
    char first = key[0];
    
    auto it = mmap.find(first);
    
    if(key.size() == 1)
    {
        struct Trie::deleteres res;
        
        
        if(it != mmap.end() && it->second->hasvalue)
        {
            res.isthere = true;
            if(it->second->mmap.empty())
            {
                mmap.erase(first);
                res.deletechild = mmap.empty();
             
                
            }
            else
            {
                it->second->hasvalue = false;
                it->second->value = 0;
            }
        }
        else
        {
            res.isthere = false;
            res.deletechild = false;
        }
        
        return res;
    }

    
    if(it == mmap.end())
    {
        struct Trie::deleteres res;
        res.isthere = false;
        res.deletechild = false;
        return res;
    }
    
    struct Trie::deleteres d =  it->second->removeinternal(key.substr(1 , std::string::npos) );
    if(d.deletechild)
    {
        mmap.erase(first);
        d.deletechild = mmap.empty();
    }
    
    return d;
}




int Trie::searchval(std::string key)
{
    std::tuple<bool , int> val = search(key);
    if(std::get<0>(val))
    {
        return std::get<1>(val);
    }
    else
    {
        std::cout << "key not found in trie" << std::endl;
        return 0;
    }
}

void Trie::print()
{
    
    
    std::queue<Trie*> q;
    
    int currentNodes = 0 ;
    int nextNodes = 0;
    
    
    for(auto it = mmap.begin() ; it != mmap.end() ; it++)
    {
        Trie* node = it->second;
        
        q.push(node);
        currentNodes++;
    }
    
    
    
    while(!q.empty())
    {
        Trie* n = q.front();
        q.pop();
        currentNodes--;
      
        std::cout << n->key << ":" << n->hasvalue <<":" << n->value  << "\t" ;
        
        for(auto it = n->mmap.begin() ; it != n->mmap.end() ; it++)
        {
            Trie* node = it->second;
         
       
            

           
            q.push(node);
            nextNodes++;
        }
       
        
        if(currentNodes == 0)
        {
            std::cout << std::endl;
            currentNodes = nextNodes;
            nextNodes = 0;
        }
        
    }
}

std::tuple<bool,int> Trie::search(std::string key)
{
    
    if(key.size() == 1)
    {
        char first = key[0];
        auto it = mmap.find(first);
        if(it->second->hasvalue)
        {
            return std::make_pair(true,it->second->value);
        }
        else
        {
            return std::make_pair(false,0);
        }
    }
    
    char first = key[0];
    
    auto it = mmap.find(first);
    
    if(it == mmap.end())
    {
        return std::make_pair(false,0);
    }
    
    return it->second->search(key.substr(1 , std::string::npos));
    
    
}