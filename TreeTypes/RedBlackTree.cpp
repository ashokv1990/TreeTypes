//
//  RedBlackTree.cpp
//  TreeTypes
//
//  Created by Ashok  on 11/27/15.
//  Copyright © 2015 b. All rights reserved.
//

#include "RedBlackTree.hpp"


AbstractTreeNode* RedBlackTreeNode::getleft()
{
    return left;
}

AbstractTreeNode* RedBlackTreeNode::getright()
{
    return right;
}

AbstractTreeNode* RedBlackTreeNode::getparent()
{
    return parent;
}

void RedBlackTreeNode::setleft(AbstractTreeNode* r)
{
    left = dynamic_cast<RedBlackTreeNode*>(r);
}

void RedBlackTreeNode::setright(AbstractTreeNode* r)
{
    right = dynamic_cast<RedBlackTreeNode*>(r);
}

void RedBlackTreeNode::setparent(AbstractTreeNode* r)
{
    parent = dynamic_cast<RedBlackTreeNode*>(r);
}

void RedBlackTreeNode::PrintContents()
{
    std::cout <<data << "Color:" << ((color == 1)?"RED":"BLACK");
}

int RedBlackTreeNode::getInsertedData()
{
    return data;
}

void RedBlackTreeNode::setdata(int d)
{
    data = d;
}

int RedBlackTreeNode::getcolor()
{
    return color;
}

void RedBlackTreeNode::setcolor(int h)
{
    color = h;
}

void RedBlackTree::InsertFix(RedBlackTreeNode* x)
{
    
    while(dynamic_cast<RedBlackTreeNode*>(x->getparent())->getcolor() == 1)
    {
        bool isleft = x->getparent()->getparent()->getleft() == x->getparent() ? true : false;
        RedBlackTreeNode* uncle ;
        if(isleft)
        {
            uncle = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getparent()->getright());
            
        
        
            if(uncle->getcolor() == 1)
            {
                dynamic_cast<RedBlackTreeNode*>(x->getparent())->setcolor(0);
                uncle->setcolor(0);
                dynamic_cast<RedBlackTreeNode*>(x->getparent()->getparent())->setcolor(1);
                x =  dynamic_cast<RedBlackTreeNode*>(x->getparent()->getparent());
            }
            else
            {
                bool amIleft = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getleft()) == x ? true : false;
                if(!amIleft)
                {
                    x = dynamic_cast<RedBlackTreeNode*>(x->getparent());
                    leftrotate(x);
                }
                dynamic_cast<RedBlackTreeNode*>(x->getparent())->setcolor(0);
                dynamic_cast<RedBlackTreeNode*>(x->getparent()->getparent())->setcolor(1);
                rightrotate(x->getparent()->getparent());
            }
        }
        else
        {
            uncle = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getparent()->getleft());
            
            if(uncle->getcolor() == 1)
            {
            
                dynamic_cast<RedBlackTreeNode*>(x->getparent())->setcolor(0);
                uncle->setcolor(0);
                dynamic_cast<RedBlackTreeNode*>(x->getparent()->getparent())->setcolor(1);
                x =  dynamic_cast<RedBlackTreeNode*>(x->getparent()->getparent());
            }
            else
            {
                bool amIleft = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getleft()) == x ? true : false;
                if(amIleft)
                {
                    x = dynamic_cast<RedBlackTreeNode*>(x->getparent());
                    rightrotate(x);
                }
                dynamic_cast<RedBlackTreeNode*>(x->getparent())->setcolor(0);
                dynamic_cast<RedBlackTreeNode*>(x->getparent()->getparent())->setcolor(1);
                leftrotate(x->getparent()->getparent());
            }
        }
  }
    dynamic_cast<RedBlackTreeNode*>(root->getleft())->setcolor(0);
    
    return;
}

void RedBlackTree::Insert(int data)
{
    RedBlackTreeNode* newnode = new RedBlackTreeNode();
    newnode->setdata(data);
    newnode->setleft(getNullNode());
    newnode->setright(getNullNode());
    newnode->setparent(getNullNode());
    
    RedBlackTreeNode* correctroot = dynamic_cast<RedBlackTreeNode*>(root->getleft());
    
    RedBlackTreeNode* parent = root;
    
    while(correctroot != getNullNode())
    {
        if(correctroot->getInsertedData() < data)
        {
            parent = correctroot;
            correctroot  = dynamic_cast<RedBlackTreeNode*>(correctroot->getright());
        }
        else if(correctroot->getInsertedData() > data)
        {
            parent = correctroot;
            correctroot  = dynamic_cast<RedBlackTreeNode*>(correctroot->getleft());
        }
        else
        {
            std::cout << "Node Exists in the Tree" <<std::endl;
            return;
        }
    }
    
    if(parent == root)
    {
        root->setleft(newnode);
        root->getleft()->setparent(root);
    }
    else
    {
        int d = parent->getInsertedData();
        if(d > data)
        {
            parent->setleft(newnode);
        }
        else
        {
            parent->setright(newnode);
        }
        newnode->setparent(parent);
    }
    
    InsertFix(newnode);
    return;
}

void RedBlackTree::deleteFix(RedBlackTreeNode *x) //THIS CODE CAN HAVE A NIL COMING INTO IT, BUT THIS NIL SHOULD HAVE AN ARBITRARY AND CORRECT PARENT FROM DELETE PROCEDURE
{
    RedBlackTreeNode* rleft = dynamic_cast<RedBlackTreeNode*>(root->getleft());
    while(x->getcolor() == 0 && x != rleft)
    {
        bool isleft = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getleft()) == x? true :false;
        if(isleft)
        {
            RedBlackTreeNode* w = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getright());
            if(w->getcolor() == 1)
            {
                w->setcolor(0);
                dynamic_cast<RedBlackTreeNode*>(w->getparent())->setcolor(1);
                leftrotate(x->getparent());//CRITICAL :ROTATE CANNOT CHANGE OUR SINGLE SENTINAL NIL,S PARENT AS IT IS USED IN DELETEFIX
                w = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getright());//EX: USING X->GETPARENT AFTER ROTATION SO NIL,S PARENT CANNOT CHANGE
                
            }
            RedBlackTreeNode* wl = dynamic_cast<RedBlackTreeNode*>(w->getleft());
            RedBlackTreeNode* wr = dynamic_cast<RedBlackTreeNode*>(w->getright());
            if(wl->getcolor() == 0 && wr->getcolor() == 0) //CHECK CAREFULLY NEW UNCLE CANNOT BE A NIL NODE, REVISE ALL PROPERTIES OF RED BLACK TREE
            {
                w->setcolor(1);
                x = dynamic_cast<RedBlackTreeNode*>(x->getparent());
            }
            else
            {
                
                if(wl->getcolor() == 1) // NULL Considerations here, parent pointer of nil must be consistent
                {
                    wl->setcolor(0);
                    w->setcolor(1);
                    rightrotate(w);
                    w = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getright());
                }
                w->setcolor(dynamic_cast<RedBlackTreeNode*>(x->getparent())->getcolor());
                dynamic_cast<RedBlackTreeNode*>(x->getparent())->setcolor(0);
                dynamic_cast<RedBlackTreeNode*>(w->getright())->setcolor(0);
                leftrotate(x->getparent());
                x = rleft;
            }
        }
        else
        {
             RedBlackTreeNode* w = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getleft());
             if(w->getcolor() == 1)
             {
                 w->setcolor(0);
                 dynamic_cast<RedBlackTreeNode*>(w->getparent())->setcolor(1);
                 rightrotate(x->getparent());
                 w = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getleft());
             }
             RedBlackTreeNode* wl = dynamic_cast<RedBlackTreeNode*>(w->getleft());
             RedBlackTreeNode* wr = dynamic_cast<RedBlackTreeNode*>(w->getright());
             if(wl->getcolor() == 0 && wr->getcolor() == 0)
             {
                w->setcolor(1);
                x = dynamic_cast<RedBlackTreeNode*>(x->getparent());
             }
             else
             {
                
                 if(wr->getcolor() == 1)
                 {
                     wr->setcolor(0);
                     w->setcolor(1);
                     leftrotate(w);
                     w = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getleft());
                 }
                 w->setcolor(dynamic_cast<RedBlackTreeNode*>(x->getparent())->getcolor());
                 dynamic_cast<RedBlackTreeNode*>(x->getparent())->setcolor(0);
                 dynamic_cast<RedBlackTreeNode*>(w->getleft())->setcolor(0);
                 rightrotate(x->getparent());
                 x = rleft;
             }
        }
    }
    x->setcolor(0);
    return;
    
}

AbstractTreeNode* RedBlackTree::leftrotate(AbstractTreeNode *r1)
{
    AbstractTreeNode* r = r1->getright();
    AbstractTreeNode* leftchildofright = r->getleft();
    r1->setright(leftchildofright);
    AbstractTreeNode * p = r1->getparent();
    r->setparent(p);
    if( p != getNullNode())
    {
        if(p->getleft() == r1)
        {
            p->setleft(r);
        }
        else
        {
            p->setright(r);
        }
    }
    r1->setparent(r);
    r->setleft(r1);
    
    if(leftchildofright != nil)
    {
        leftchildofright->setparent(r1);
    }
    return r;
}

AbstractTreeNode* RedBlackTree::rightrotate(AbstractTreeNode *r1)
{
    AbstractTreeNode* r = r1->getleft();
    AbstractTreeNode* rightchildofleft = r->getright();
    r1->setleft(rightchildofleft);
    AbstractTreeNode * p = r1->getparent();
    r->setparent(p);
    if( p != getNullNode())
    {
        if(p->getleft() == r1)
        {
            p->setleft(r);
        }
        else
        {
            p->setright(r);
        }
    }
    r1->setparent(r);
    r->setright(r1);
    
    if(rightchildofleft != nil)
    {
        rightchildofleft->setparent(r1);
    }
    return r;
    
}

bool RedBlackTree::deleteNode(int node)
{
    RedBlackTreeNode * w = dynamic_cast<RedBlackTreeNode*>(Search(node));
    if(w == getNullNode())
    {
        std::cout << "Node not in Tree" << std::endl;
        return false;
    }
    
    RedBlackTreeNode *z = w;
    if(w->getleft() != getNullNode() && w->getright() != getNullNode())
    {
        z = dynamic_cast<RedBlackTreeNode*>(z->getright());
        while(z != getNullNode())
        {
            z = dynamic_cast<RedBlackTreeNode*>(z->getleft());
        }
    }
    RedBlackTreeNode *x = z->getleft() == getNullNode()? dynamic_cast<RedBlackTreeNode*>(z->getright()): dynamic_cast<RedBlackTreeNode*>(z->getleft());

    x->setparent(z->getparent()); //X COULD BE NIL , NIL,S PARENT IS NOW A NON NIL NODE
    if(x->getparent() == root)
    {
        root->setleft(x);
    }
    else
    {
        bool isleft = dynamic_cast<RedBlackTreeNode*>(z->getparent()->getleft()) == z? true :false;
        if(isleft)
        {
            z->getparent()->setleft(x);
        }
        else
        {
            z->getparent()->setright(x);
        }
    }
    
    if(z != w)
    {
        z->setleft(w->getleft());
        z->setright(w->getright());
        z->setparent(w->getparent());
        w->getleft()->setparent(z);
        w->getright()->setparent(z);
        
        bool isleft = dynamic_cast<RedBlackTreeNode*>(w->getparent()->getleft()) == w ? true:false;
        if(isleft)
        {
            w->getparent()->setleft(z);
        }
        else
        {
            w->getparent()->setright(z);
        }
        
        if(z->getcolor() == 0)
        {
            z->setcolor(w->getcolor());
            deleteFix(x);
        }
        else
        {
            z->setcolor(w->getcolor());
        }
        delete w;
        
    }
    else
    {
        if(z->getcolor() == 0)
        {
            deleteFix(x);
        }
        delete z;
    }
    return true ;
}

AbstractTreeNode* RedBlackTree::getNullNode()
{
    return nil;
}

AbstractTreeNode* RedBlackTree::getTopNode()
{
    return root->getleft();
}

