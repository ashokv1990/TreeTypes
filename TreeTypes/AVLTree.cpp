//
//  AVLTree.cpp
//  TreeTypes
//
//  Created by Ashok  on 11/26/15.
//  Copyright © 2015 b. All rights reserved.
//

#include "AVLTree.hpp"

AbstractTreeNode* AVLTreeNode::getleft()
{
    return left;
}

AbstractTreeNode* AVLTreeNode::getright()
{
    return right;
}

AbstractTreeNode* AVLTreeNode::getparent()
{
    return parent;
}

void AVLTreeNode::setleft(AbstractTreeNode* r)
{
    left = dynamic_cast<AVLTreeNode*>(r);
}

void AVLTreeNode::setdata(int d)
{
    data = d;
}

void AVLTreeNode::setright(AbstractTreeNode* r)
{
    right =  dynamic_cast<AVLTreeNode*>(r);
}

void AVLTreeNode::setparent(AbstractTreeNode* r )
{
    parent =  dynamic_cast<AVLTreeNode*>(r);
}

int AVLTreeNode::getInsertedData()
{
    return data;
}

int AVLTreeNode::getheight()
{
    return height;
}

void AVLTreeNode::setheight(int h)
{
     height = h;
}

void AVLTreeNode::PrintContents()
{
    std::cout << data << "\t"<<"height:"<<height<<"\t";
}

AbstractTreeNode* AVLTree::getTopNode()
{
    return root;
}

AbstractTreeNode* AVLTree::getNullNode()
{
    return NULL;
}

int AVLTree::getheight(AVLTreeNode *r)
{
    if(r == getNullNode())
    {
        return 0;
    }
    else
    {
        return r->getheight();
    }
}

int AVLTree::getbalance(AVLTreeNode * r)
{
    return getheight(dynamic_cast<AVLTreeNode*>(r->getleft())) - getheight(dynamic_cast<AVLTreeNode*>(r->getright()));
}

AbstractTreeNode* AVLTree::leftrotate(AbstractTreeNode* r) //Must update child,s height then parents height
{
    AbstractTreeNode* root = AbstractTree::leftrotate(r);
    updateheight(r);
    updateheight(root);
    return root;
}

AbstractTreeNode* AVLTree::rightrotate(AbstractTreeNode* r)
{
    AbstractTreeNode* root = AbstractTree::rightrotate(r);
    updateheight(r);
    updateheight(root);
    return root;
    
}

void AVLTree::insertHelper(AVLTreeNode * &node , int data)
{
    if(node == getNullNode())
    {
        node = new AVLTreeNode(data);
        node->setheight(1);
        node->setleft(getNullNode());
        node->setright(getNullNode());
        node->setparent(getNullNode());
        return;
    }
    else if(node->getInsertedData() == data)
    {
        std::cout << "Node Exists" << std::endl;
        return;
    }
    else if(node->getInsertedData() < data)
    {
        AVLTreeNode * right = dynamic_cast<AVLTreeNode*>(node->getright());
        insertHelper( right, data);
        node->setright(right);
        right->setparent(node);
    }
    else
    {
        AVLTreeNode * left = dynamic_cast<AVLTreeNode*>(node->getleft());
        insertHelper( left, data);
        node->setleft(left);
        left->setparent(node);
    }
   
    updateheight(node);
    int balance = getbalance(node);
   
    if(balance == 2)
    {
        AVLTreeNode* currl  = dynamic_cast<AVLTreeNode*>(node->getleft());
        int balancel = getbalance(currl);
        if(balancel == -1)
        {
           leftrotate(currl);
           
          
        
        }
      
        node = dynamic_cast<AVLTreeNode*>(rightrotate(node));
      

    }
    else if(balance == -2)
    {
        AVLTreeNode* currr  = dynamic_cast<AVLTreeNode*>(node->getright());
        int balancer = getbalance(currr);
        if(balancer == 1)
        {
            rightrotate(currr);
            
       
           
        }
        node = dynamic_cast<AVLTreeNode*>(leftrotate(node));
       
       
    }
    
}

void AVLTree::updateheight(AbstractTreeNode *node)
{
   int h = std::max(getheight(dynamic_cast<AVLTreeNode*>(node->getleft())),getheight(dynamic_cast<AVLTreeNode*>(node->getright()))) + 1;
   dynamic_cast<AVLTreeNode*>(node)->setheight(h);
}

AVLTreeNode* AVLTree::deleteHelper(AVLTreeNode * r , int data)
{
  
    if(r->getInsertedData() == data)
    {
        
      if(r->getleft() == getNullNode() && r->getright() == getNullNode())
      {
          delete r;
          return NULL;
      }
      else if(r->getleft() == getNullNode() || r->getright() == getNullNode())
      {
          bool leftchild = r->getleft() != getNullNode() ? true : false;
          AVLTreeNode* child;
          if(leftchild)
          {
              r->getleft()->setparent(r->getparent());
              child = dynamic_cast<AVLTreeNode*>(r->getleft());
            
           
          }
          else
          {
               r->getright()->setparent(r->getparent());
               child = dynamic_cast<AVLTreeNode*>(r->getright());
          }
   
          delete r;
          return child;
          
      }
      else
      {
          AVLTreeNode * succ = dynamic_cast<AVLTreeNode*>(r->getright());
          while(succ->getleft() != getNullNode())
          {
              succ =  dynamic_cast<AVLTreeNode*>(succ->getleft());
          }
         
          r->setdata(succ->getInsertedData());
          r->setright(deleteHelper(dynamic_cast<AVLTreeNode*>(r->getright()) , succ->getInsertedData()));
      }
    }
    else if(r->getInsertedData()  < data)
    {
        r->setright(deleteHelper(dynamic_cast<AVLTreeNode*>(r->getright()) , data));
    }
    else
    {
        r->setleft(deleteHelper(dynamic_cast<AVLTreeNode*>(r->getleft()) , data));
    }
    
    updateheight(r);
    int h = getbalance(r);
    if(h == 2)
    {
         AVLTreeNode* currl  = dynamic_cast<AVLTreeNode*>(r->getleft());
         int bl = getbalance(currl);
         if(bl == -1)
         {
             leftrotate(r->getleft());
         }
         r = dynamic_cast<AVLTreeNode*>(rightrotate(r));
        
    }
    else if(h == -2)
    {
        AVLTreeNode* currr  = dynamic_cast<AVLTreeNode*>(r->getright());
        int br = getbalance(currr);
        if(br == 1)
        {
             rightrotate(r->getright());
        }
        r = dynamic_cast<AVLTreeNode*>(leftrotate(r));
    }
    return r;
}

bool AVLTree::deleteNode(int node)
{
    AbstractTreeNode * w = Search(node);
    if(w == getNullNode())
    {
        std::cout << "Node not in Tree" << std::endl;
        return false;
    }
    
    root = deleteHelper(root , node);
    return true;
    
}

void AVLTree::Insert(int data)
{
    insertHelper(root,data);
}

void AVLTree::deleteTree(AVLTreeNode * root)
{
    if(root == NULL)
    {
        return;
    }
    
    AVLTreeNode* left = dynamic_cast<AVLTreeNode*>(root->getleft());
    AVLTreeNode* right =dynamic_cast<AVLTreeNode*>(root->getright());
    deleteTree(left);
    deleteTree(right);
    delete root;
    
    
}

