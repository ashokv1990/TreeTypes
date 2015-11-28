//
//  AbstractTree.h
//  TreeTypes
//
//  Created by Ashok  on 11/26/15.
//  Copyright © 2015 b. All rights reserved.
//

#ifndef AbstractTree_h
#define AbstractTree_h

#include <iostream>
#include <queue>

class AbstractTreeNode
{
public:
    virtual AbstractTreeNode* getleft() = 0;
    virtual AbstractTreeNode* getright() = 0;
    virtual AbstractTreeNode* getparent() = 0;
    virtual void setleft(AbstractTreeNode*) = 0;
    virtual void setright(AbstractTreeNode*) = 0;
    virtual void setparent(AbstractTreeNode*) = 0;
    virtual void PrintContents() = 0;
    virtual int getInsertedData() = 0;
    
};

class AbstractTree
{

public:
    virtual void Insert(int data) = 0;
    virtual bool deleteNode(int node) = 0;
    virtual AbstractTreeNode* getNullNode() = 0;
    virtual AbstractTreeNode* getTopNode() = 0;
    
   
    
    AbstractTreeNode* Search(int data);
    
    void LevelOrder();
    void postOrder();
    void inOrder();
    void preOrder();
    void LevelOrder(AbstractTreeNode * root);
    void postOrder(AbstractTreeNode * root);
    void inOrder(AbstractTreeNode *root);
    void preOrder(AbstractTreeNode *root);
    virtual AbstractTreeNode* leftrotate(AbstractTreeNode *root);
    virtual AbstractTreeNode* rightrotate(AbstractTreeNode *right);
    
    
};

#endif /* AbstractTree_h */
