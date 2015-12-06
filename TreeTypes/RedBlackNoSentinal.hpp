//
//  RedBlackNoSentinal.hpp
//  TreeTypes
//
//  Created by Ashok  on 12/5/15.
//  Copyright © 2015 b. All rights reserved.
//

#ifndef RedBlackNoSentinal_hpp
#define RedBlackNoSentinal_hpp

#include <stdio.h>
#include <stdio.h>
#include "AbstractTree.h"
#include "RedBlackTree.hpp"



class RedBlackTreeNoSentinal:public AbstractTree
{
public:
    RedBlackTreeNoSentinal():root(NULL)
    {
       
      
    }
    
    ~RedBlackTreeNoSentinal()
    {
        deleteTree(root);
    };
    
    
    virtual void Insert(int data) ;
    virtual bool deleteNode(int node) ;
    virtual AbstractTreeNode* getNullNode() ;
    virtual AbstractTreeNode* getTopNode() ;
    
    
    
private:
    
    void deleteFix(RedBlackTreeNode *r);
    void deleteFixNull(RedBlackTreeNode *r , int d);
    void InsertFix(RedBlackTreeNode *r);
    void deleteTree(RedBlackTreeNode* node);
    
    RedBlackTreeNode* root;
    
};
#endif /* RedBlackNoSentinal_hpp */
