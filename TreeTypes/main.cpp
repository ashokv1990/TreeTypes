//
//  main.cpp
//  TreeTypes
//
//  Created by Ashok  on 11/26/15.
//  Copyright © 2015 b. All rights reserved.
//

#include <iostream>
#include "AVLTree.hpp"
#include "RedBlackTree.hpp"

void print(AbstractTree * t , int level)
{
    if(level > 0)
    {
    std::cout << "LEVEL ORDER" << std::endl;
    t->LevelOrder();
    }
    if(level > 1)
    {
    std::cout << "IN ORDER" << std::endl;
    t->inOrder();
    }
    if(level > 2)
    {
    std::cout << "PRE ORDER" << std::endl;
    t->preOrder();
    }
    if(level > 3)
    {
    std::cout << "POST ORDER" << std::endl;
    t->postOrder();
    }
}
int main(int argc, const char * argv[]) {
   
    AbstractTree* t = new AVLTree();
    t->Insert(5);
    t->Insert(3);
    print(t , 2);
    t->Insert(2);
    print(t , 2);
    t->Insert(7);
    t->Insert(10);
    std::cout << "test" <<std::endl;
    print(t , 2);
    t->Insert(4);
    print(t,2);
     std::cout << "test2" <<std::endl;
    t->deleteNode(5);
    print(t,2);
    t->deleteNode(10);
    print(t,2);
    std::cout << "RBTREE" << std::endl;
    AbstractTree* r = new RedBlackTree();
    r->Insert(6);
    r->Insert(2);
    r->Insert(1);
    std::cout << "RBTREE" << std::endl;
    r->Insert(4);
    r->Insert(5);
    print(r , 2);
    r->deleteNode(6);
    print(r , 2);
    r->deleteNode(1);
    print(r , 2);
    r->deleteNode(5);
    print(r , 2);
}
