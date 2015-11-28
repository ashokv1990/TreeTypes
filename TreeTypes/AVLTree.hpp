//
//  AVLTree.hpp
//  TreeTypes
//
//  Created by Ashok  on 11/26/15.
//  Copyright © 2015 b. All rights reserved.
//

#ifndef AVLTree_hpp
#define AVLTree_hpp
#include "AbstractTree.h"
#include <stdio.h>

class AVLTreeNode:public AbstractTreeNode
{
public:
    AVLTreeNode(int d):data(d)
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        height = 0;
    }
    
    ~AVLTreeNode(){
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
    int getheight();
    void setheight(int h);
    
private:
    int data;
    int height;
    AVLTreeNode *left;
    AVLTreeNode* right;
    AVLTreeNode* parent;
};


class AVLTree:public AbstractTree
{
public:
    AVLTree():root(NULL)
    {
        
    }
    
    ~AVLTree()
    {
        deleteTree(root);
    };
    
   
    virtual void Insert(int data) ;
    virtual bool deleteNode(int node) ;
    virtual AbstractTreeNode* getNullNode() ;
    virtual AbstractTreeNode* getTopNode() ;
    virtual AbstractTreeNode* leftrotate(AbstractTreeNode *root);
    virtual AbstractTreeNode* rightrotate(AbstractTreeNode *right);
    
   
private:
    AVLTreeNode* deleteHelper(AVLTreeNode * node , int data);
    void insertHelper(AVLTreeNode *&node , int data);
    void deleteTree(AVLTreeNode* node);
    int getheight(AVLTreeNode * r);
    int getbalance(AVLTreeNode * r);
    void updateheight(AbstractTreeNode *r);
    AVLTreeNode* root;
    
    
};
#endif /* AVLTree_hpp */
