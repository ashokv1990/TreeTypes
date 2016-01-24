//
//  RedBlackTree.hpp
//  TreeTypes
//
//  Created by Ashok  on 11/27/15.
//  Copyright © 2015 b. All rights reserved.
//

#ifndef RedBlackTree_hpp
#define RedBlackTree_hpp

#include <stdio.h>
#include "AbstractTree.h"

class RedBlackTreeNode:public AbstractTreeNode
{
public:
    RedBlackTreeNode()
    {
        data = 0;
        left = NULL;
        right = NULL;
        parent = NULL;
        color = 1; //1 red 0 black
        
    }
    
    ~RedBlackTreeNode(){
        left = NULL;
        right = NULL;
        parent = NULL;
    };
    
    virtual AbstractTreeNode* getleft() ;
    virtual AbstractTreeNode* getright() ;
    virtual AbstractTreeNode* getparent() ;
    virtual void setleft(AbstractTreeNode*) ;
    virtual void setright(AbstractTreeNode*) ;
    virtual void setparent(AbstractTreeNode*) ;
    virtual void PrintContents() ;
    virtual int getInsertedData() ;
    void setdata(int data);
    int getcolor();
    void setcolor(int h);
    
private:
    int data;
    int color;
    RedBlackTreeNode *left;
    RedBlackTreeNode* right;
    RedBlackTreeNode* parent;
};


class RedBlackTree:public AbstractTree
{
public:
    RedBlackTree():root(NULL)
    {
        root = new RedBlackTreeNode();
        nil = new RedBlackTreeNode();
        nil->setleft(nil);
        nil->setright(nil);
        nil->setparent(nil);
        nil->setcolor(0);
        
        root->setleft(nil);
        root->setright(nil);
        root->setparent(nil);
        root->setcolor(0);
    }
    
    ~RedBlackTree()
    {
        deleteTree(root);
    };
    
    
    virtual void Insert(int data) ;
    virtual bool deleteNode(int node) ;
    virtual AbstractTreeNode* getNullNode() ;
    virtual AbstractTreeNode* getTopNode() ;
   
    
    
private:
    
    virtual AbstractTreeNode* leftrotate(AbstractTreeNode *r);
    virtual AbstractTreeNode* rightrotate(AbstractTreeNode *r);
    void deleteFix(RedBlackTreeNode *r);
    void InsertFix(RedBlackTreeNode *r);
    void deleteTree(RedBlackTreeNode* node);
    
    RedBlackTreeNode* root;
    RedBlackTreeNode* nil;
    
};

#endif /* RedBlackTree_hpp */
