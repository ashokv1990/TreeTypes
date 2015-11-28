//
//  AbstractTree.cpp
//  TreeTypes
//
//  Created by Ashok  on 11/26/15.
//  Copyright © 2015 b. All rights reserved.
//

#include "AbstractTree.h"



void AbstractTree::preOrder(AbstractTreeNode * root)
{
    if(root == getNullNode())
    {
        return;
    }
    
    root->PrintContents();
    preOrder(root->getleft());
    preOrder(root->getright());
};


void AbstractTree::postOrder(AbstractTreeNode * root)
{
    if(root == getNullNode())
    {
        return;
    }
    
    postOrder(root->getleft());
    postOrder(root->getright());
    root->PrintContents();

};

void AbstractTree::inOrder(AbstractTreeNode * root)
{
    if(root == getNullNode())
    {
        return;
    }
    
    inOrder(root->getleft());
    root->PrintContents();
    inOrder(root->getright());
};

AbstractTreeNode* AbstractTree::Search(int data)
{
    AbstractTreeNode* root = getTopNode();
    AbstractTreeNode* res = getNullNode();
    
    while(root != NULL)
    {
        int d = root->getInsertedData();
        if(d == data)
        {
            res = root;
            break;
        }
        else if(d < data)
        {
            root = root->getright();
        }
        else
        {
             root = root->getleft();
        }
    }
    return res;
}

void AbstractTree::LevelOrder()
{
    LevelOrder(getTopNode());
}

void AbstractTree::preOrder()
{
    preOrder(getTopNode());
    std::cout << std::endl;
}

void AbstractTree::postOrder()
{
    postOrder(getTopNode());
    std::cout << std::endl;
}

void AbstractTree::inOrder()
{
    inOrder(getTopNode());
    std::cout << std::endl;
}

AbstractTreeNode* AbstractTree::leftrotate(AbstractTreeNode * root)
{
    AbstractTreeNode* r = root->getright();
    root->setright(r->getleft());
    AbstractTreeNode * p = root->getparent();
    r->setparent(p);
    if( p != getNullNode())
    {
        if(p->getleft() == root)
        {
            p->setleft(r);
        }
        else
        {
            p->setright(r);
        }
    }
    root->setparent(r);
    r->setleft(root);
    return r;
    
}

AbstractTreeNode* AbstractTree::rightrotate(AbstractTreeNode * root)
{
    AbstractTreeNode* r = root->getleft();
    root->setleft(r->getright());
    AbstractTreeNode * p = root->getparent();
    r->setparent(p);
    if( p != getNullNode())
    {
        if(p->getleft() == root)
        {
            p->setleft(r);
        }
        else
        {
            p->setright(r);
        }
    }
    root->setparent(r);
    r->setright(root);
    return r;
}

void AbstractTree::LevelOrder(AbstractTreeNode * root)
{
    if(root == getNullNode())
    {
        return;
    }
    
    std::queue<AbstractTreeNode*> q;
    
    int currentNodes = 0 ;
    int nextNodes = 0;
    
    currentNodes = 1;
    q.push(root);
    
    while(!q.empty())
    {
        AbstractTreeNode* node = q.front();
        q.pop();
        currentNodes--;
        node->PrintContents();
        if(node->getleft() != getNullNode())
        {
            q.push(node->getleft());
            nextNodes++;
        }
        
        if(node->getright() != getNullNode())
        {
            q.push(node->getright());
            nextNodes++;
        }
        
        if(currentNodes == 0)
        {
            std::cout << std::endl;
            currentNodes = nextNodes;
            nextNodes = 0;
        }
        
    }
};