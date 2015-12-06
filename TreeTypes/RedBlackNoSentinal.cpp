//
//  RedBlackNoSentinal.cpp
//  TreeTypes
//
//  Created by Ashok  on 12/5/15.
//  Copyright © 2015 b. All rights reserved.
//

#include "RedBlackNoSentinal.hpp"




void RedBlackTreeNoSentinal::InsertFix(RedBlackTreeNode* x)
{
    
    while(x != root && dynamic_cast<RedBlackTreeNode*>(x->getparent())->getcolor() == 1)
    {
        bool isleft = x->getparent()->getparent()->getleft() == x->getparent() ? true : false;
        RedBlackTreeNode* uncle ;
        if(isleft)
        {
            uncle = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getparent()->getright());
            bool uncleNull = uncle == NULL ;
            
            
            if(!uncleNull && uncle->getcolor() == 1)
            {
                dynamic_cast<RedBlackTreeNode*>(x->getparent())->setcolor(0);
                uncle->setcolor(0);
                dynamic_cast<RedBlackTreeNode*>(x->getparent()->getparent())->setcolor(1);
                x =  dynamic_cast<RedBlackTreeNode*>(x->getparent()->getparent()); //ROOT MAY BECOME RED SO ENSURE TO COLOR ROOT BLACK
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
                RedBlackTreeNode* temp = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getparent());
                if(temp == root)
                {
                    root =  dynamic_cast<RedBlackTreeNode*>(rightrotate(temp));
                }
                else
                {
                    rightrotate(temp);
                }
                
            }
        }
        else
        {
            uncle = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getparent()->getleft());
            bool uncleNull = uncle == NULL ;
            
            if(!uncleNull && uncle->getcolor() == 1)
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
                RedBlackTreeNode* temp = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getparent());
                if(temp == root)
                {
                    root =  dynamic_cast<RedBlackTreeNode*>(leftrotate(temp));
                }
                else
                {
                    leftrotate(temp);
                }
            }
        }
    }
    root->setcolor(0);
    return;
}

void RedBlackTreeNoSentinal::Insert(int data)
{
    RedBlackTreeNode* newnode = new RedBlackTreeNode();
    newnode->setdata(data);
    newnode->setleft(getNullNode());
    newnode->setright(getNullNode());
    newnode->setparent(getNullNode());
    
    if(root == getNullNode())
    {
        root = newnode;
        newnode->setcolor(0);
        return;
    }
    else
    {
        RedBlackTreeNode* correctroot = root;
        RedBlackTreeNode* parent = NULL;
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
        InsertFix(newnode);
    }
    
   
   
  
}



void RedBlackTreeNoSentinal::deleteFixNull(RedBlackTreeNode *parent , int dir)
{
        RedBlackTreeNode* x = NULL;
        bool isrootparent = root == parent;
        while(x== NULL ||( x->getcolor() == 0 && x != root))
        {
            if(dir == 1)
            {
                RedBlackTreeNode* w = dynamic_cast<RedBlackTreeNode*>(parent->getright());
                if(w->getcolor() == 1)
                {
                    w->setcolor(0);
                    dynamic_cast<RedBlackTreeNode*>(w->getparent())->setcolor(1);
                    if(isrootparent)
                    {
                        root = dynamic_cast<RedBlackTreeNode*>(leftrotate(parent));//CRITICAL :ROTATE CANNOT CHANGE OUR SINGLE SENTINAL NIL,S PARENT AS IT IS USED IN DELETEFIX
                    }
                    else
                    {
                        leftrotate(parent);
                    }
                    
                    w = dynamic_cast<RedBlackTreeNode*>(parent->getright());//EX: USING X->GETPARENT AFTER ROTATION SO NIL,S PARENT CANNOT CHANGE
                    
                }
                RedBlackTreeNode* wl = dynamic_cast<RedBlackTreeNode*>(w->getleft());
                RedBlackTreeNode* wr = dynamic_cast<RedBlackTreeNode*>(w->getright());
                if(wl == NULL && wr == NULL)
                {
                    w->setcolor(1);
                    x = parent;
                }
                else if(wl == NULL || wr == NULL)
                {
                    bool leftuncc = wl == NULL;
                    RedBlackTreeNode* nonnullchild = leftuncc ? wr : wl;
                    if(nonnullchild->getcolor() == 0)
                    {
                        w->setcolor(1);
                        x = parent;
                    }
                    else
                    {
                        if(!leftuncc)
                        {
                            wl->setcolor(0);
                            w->setcolor(1);
                            rightrotate(w);
                            w = dynamic_cast<RedBlackTreeNode*>(parent->getright());
                        }
                        w->setcolor(dynamic_cast<RedBlackTreeNode*>(parent)->getcolor());
                        dynamic_cast<RedBlackTreeNode*>(parent)->setcolor(0);
                        dynamic_cast<RedBlackTreeNode*>(w->getright())->setcolor(0);
                        if(isrootparent)
                        {
                            root = dynamic_cast<RedBlackTreeNode*>(leftrotate(parent));
                        }
                        else
                        {
                            leftrotate(parent);
                        }
                        x = root;
                    }
                }
                else if( wl->getcolor() == 0 &&  wr->getcolor() == 0) //CHECK CAREFULLY NEW UNCLE CANNOT BE A NIL NODE, REVISE ALL PROPERTIES OF RED BLACK TREE
                {
                    w->setcolor(1);
                    x = parent;
                }
                else
                {
                    
                    if(wl->getcolor() == 1) // NULL Considerations here, parent pointer of nil must be consistent
                    {
                        wl->setcolor(0);
                        w->setcolor(1);
                        rightrotate(w);
                        w = dynamic_cast<RedBlackTreeNode*>(parent->getright());
                    }
                    w->setcolor(dynamic_cast<RedBlackTreeNode*>(parent)->getcolor());
                    dynamic_cast<RedBlackTreeNode*>(parent)->setcolor(0);
                    dynamic_cast<RedBlackTreeNode*>(w->getright())->setcolor(0);
                    if(isrootparent)
                    {
                        root = dynamic_cast<RedBlackTreeNode*>(leftrotate(parent));
                    }
                    else
                    {
                        leftrotate(parent);
                    }
                    x = root;
                }
            }
            else if(dir == 0)
            {
                RedBlackTreeNode* w = dynamic_cast<RedBlackTreeNode*>(parent->getright());
                if(w->getcolor() == 1)
                {
                    w->setcolor(0);
                    dynamic_cast<RedBlackTreeNode*>(w->getparent())->setcolor(1);
                    if(isrootparent)
                    {
                        root = dynamic_cast<RedBlackTreeNode*>(rightrotate(parent));//CRITICAL :ROTATE CANNOT CHANGE OUR SINGLE SENTINAL NIL,S PARENT AS IT IS USED IN DELETEFIX
                    }
                    else
                    {
                        rightrotate(parent);
                    }
                    
                    w = dynamic_cast<RedBlackTreeNode*>(parent->getright());//EX: USING X->GETPARENT AFTER ROTATION SO NIL,S PARENT CANNOT CHANGE
                    
                }
                RedBlackTreeNode* wl = dynamic_cast<RedBlackTreeNode*>(w->getleft());
                RedBlackTreeNode* wr = dynamic_cast<RedBlackTreeNode*>(w->getright());
                
                if(wl == NULL && wr == NULL)
                {
                    w->setcolor(1);
                    x = parent;
                }
                else if(wl == NULL || wr == NULL)
                {
                    bool leftuncc = wl == NULL;
                    RedBlackTreeNode* nonnullchild = leftuncc ? wr : wl;
                    if(nonnullchild->getcolor() == 0)
                    {
                        w->setcolor(1);
                        x = parent;
                    }
                    else
                    {
                        if(leftuncc)
                        {
                            wr->setcolor(0);
                            w->setcolor(1);
                            leftrotate(w);
                            w = dynamic_cast<RedBlackTreeNode*>(parent->getleft());
                        }
                        w->setcolor(dynamic_cast<RedBlackTreeNode*>(parent)->getcolor());
                        dynamic_cast<RedBlackTreeNode*>(parent)->setcolor(0);
                        dynamic_cast<RedBlackTreeNode*>(w->getleft())->setcolor(0);
                        if(isrootparent)
                        {
                            root = dynamic_cast<RedBlackTreeNode*>(rightrotate(parent));
                        }
                        else
                        {
                            rightrotate(parent);
                        }
                        x = root;
                    }
                }
                else if(wl->getcolor() == 0 && wr->getcolor() == 0)
                {
                    w->setcolor(1);
                    x = dynamic_cast<RedBlackTreeNode*>(parent);
                }
                else
                {
                    
                    if(wr->getcolor() == 1)
                    {
                        wr->setcolor(0);
                        w->setcolor(1);
                        leftrotate(w);
                        w = dynamic_cast<RedBlackTreeNode*>(parent->getleft());
                    }
                    w->setcolor(dynamic_cast<RedBlackTreeNode*>(parent)->getcolor());
                    dynamic_cast<RedBlackTreeNode*>(parent)->setcolor(0);
                    dynamic_cast<RedBlackTreeNode*>(w->getleft())->setcolor(0);
                    if(isrootparent)
                    {
                        root = dynamic_cast<RedBlackTreeNode*>(rightrotate(parent));
                    }
                    else
                    {
                        rightrotate(parent);
                    }
                    x = root;
                }


            }
        }
        x->setcolor(0);
}

void RedBlackTreeNoSentinal::deleteFix(RedBlackTreeNode *x)
{
    while(x->getcolor() == 0 && x != root)
    {
        bool isleft = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getleft()) == x? true :false;
        bool isrootparent = dynamic_cast<RedBlackTreeNode*>(x->getparent()) == root;
        if(isleft)
        {
            RedBlackTreeNode* w = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getright());
            //UNCLE CANNOT BE NIL BLACK HT VIOLATION
            if(w->getcolor() == 1)
            {
                w->setcolor(0);
                dynamic_cast<RedBlackTreeNode*>(w->getparent())->setcolor(1);
                if(isrootparent)
                {
                      root = dynamic_cast<RedBlackTreeNode*>(leftrotate(x->getparent()));//CRITICAL :ROTATE CANNOT CHANGE OUR SINGLE SENTINAL NIL,S PARENT AS IT IS USED IN DELETEFIX
                }
                else
                {
                    leftrotate(x->getparent());
                }
              
                w = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getright());//EX: USING X->GETPARENT AFTER ROTATION SO NIL,S PARENT CANNOT CHANGE
                
            }
            RedBlackTreeNode* wl = dynamic_cast<RedBlackTreeNode*>(w->getleft());
            RedBlackTreeNode* wr = dynamic_cast<RedBlackTreeNode*>(w->getright());
            
            if(wl == NULL && wr == NULL)
            {
                w->setcolor(1);
                x = dynamic_cast<RedBlackTreeNode*>(x->getparent());
            }
            else if(wl == NULL || wr == NULL)
            {
                bool leftuncc = wl == NULL;
                RedBlackTreeNode* nonnullchild = leftuncc ? wr : wl;
                if(nonnullchild->getcolor() == 0)
                {
                    w->setcolor(1);
                    x = dynamic_cast<RedBlackTreeNode*>(x->getparent());
                }
                else
                {
                    if(!leftuncc)
                    {
                        wl->setcolor(0);
                        w->setcolor(1);
                        rightrotate(w);
                        w = dynamic_cast<RedBlackTreeNode*>(dynamic_cast<RedBlackTreeNode*>(x->getparent())->getright());
                    }
                    w->setcolor(dynamic_cast<RedBlackTreeNode*>(dynamic_cast<RedBlackTreeNode*>(x->getparent()))->getcolor());
                    dynamic_cast<RedBlackTreeNode*>(dynamic_cast<RedBlackTreeNode*>(x->getparent()))->setcolor(0);
                    dynamic_cast<RedBlackTreeNode*>(w->getright())->setcolor(0);
                    if(isrootparent)
                    {
                        root = dynamic_cast<RedBlackTreeNode*>(leftrotate(dynamic_cast<RedBlackTreeNode*>(x->getparent())));
                    }
                    else
                    {
                        leftrotate(x->getparent());
                    }
                    x = root;
                }
            }
            else if(wl->getcolor() == 0 && wr->getcolor() == 0) //CHECK CAREFULLY NEW UNCLE CANNOT BE A NIL NODE, REVISE ALL PROPERTIES OF RED BLACK TREE
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
                if(isrootparent)
                {
                    root = dynamic_cast<RedBlackTreeNode*>(leftrotate(x->getparent()));
                }
                else
                {
                    leftrotate(x->getparent());
                }
                x = root;
            }
        }
        else
        {
            RedBlackTreeNode* w = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getleft());
            if(w->getcolor() == 1)
            {
                w->setcolor(0);
                dynamic_cast<RedBlackTreeNode*>(w->getparent())->setcolor(1);
                if(isrootparent)
                {
                    root = dynamic_cast<RedBlackTreeNode*>(rightrotate(x->getparent()));//CRITICAL :ROTATE CANNOT CHANGE OUR SINGLE SENTINAL NIL,S PARENT AS IT IS USED IN DELETEFIX
                }
                else
                {
                    rightrotate(x->getparent());
                }
                w = dynamic_cast<RedBlackTreeNode*>(x->getparent()->getleft());
            }
            RedBlackTreeNode* wl = dynamic_cast<RedBlackTreeNode*>(w->getleft());
            RedBlackTreeNode* wr = dynamic_cast<RedBlackTreeNode*>(w->getright());
            
            
            if(wl == NULL && wr == NULL)
            {
                w->setcolor(1);
                x =  dynamic_cast<RedBlackTreeNode*>(x->getparent());
            }
            else if(wl == NULL || wr == NULL)
            {
                bool leftuncc = wl == NULL;
                RedBlackTreeNode* nonnullchild = leftuncc ? wr : wl;
                if(nonnullchild->getcolor() == 0)
                {
                    w->setcolor(1);
                    x = dynamic_cast<RedBlackTreeNode*>(x->getparent());
                }
                else
                {
                    if(leftuncc)
                    {
                        wr->setcolor(0);
                        w->setcolor(1);
                        leftrotate(w);
                        w = dynamic_cast<RedBlackTreeNode*>(dynamic_cast<RedBlackTreeNode*>(x->getparent())->getleft());
                    }
                    w->setcolor(dynamic_cast<RedBlackTreeNode*>(dynamic_cast<RedBlackTreeNode*>(x->getparent()))->getcolor());
                    dynamic_cast<RedBlackTreeNode*>(dynamic_cast<RedBlackTreeNode*>(x->getparent()))->setcolor(0);
                    dynamic_cast<RedBlackTreeNode*>(w->getleft())->setcolor(0);
                    if(isrootparent)
                    {
                        root = dynamic_cast<RedBlackTreeNode*>(rightrotate(dynamic_cast<RedBlackTreeNode*>(x->getparent())));
                    }
                    else
                    {
                        rightrotate(x->getparent());
                    }
                    x = root;
                }
            }
            else if(wl->getcolor() == 0 && wr->getcolor() == 0)
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
                if(isrootparent)
                {
                    root = dynamic_cast<RedBlackTreeNode*>(rightrotate(x->getparent()));
                }
                else
                {
                    rightrotate(x->getparent());
                }
                x = root;
            }
        }
    }
    x->setcolor(0);
    return;
    
}


bool RedBlackTreeNoSentinal::deleteNode(int node)
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
        while(z->getleft() != getNullNode())
        {
            z = dynamic_cast<RedBlackTreeNode*>(z->getleft());
        }
    }
    
    bool iszroot = z == root;
    RedBlackTreeNode *x = z->getleft() == getNullNode()? dynamic_cast<RedBlackTreeNode*>(z->getright()): dynamic_cast<RedBlackTreeNode*>(z->getleft());
    bool isXNull = x == NULL;
    RedBlackTreeNode *parent = NULL; //For NULL Case
    int dir ;
    //1 left
    //0 right
    
    
    if(iszroot)
    {
        
        root = x;
        x->setcolor(0);
        delete z;
        return true;
     
    }
    else
    {
        if(!isXNull)
        {
            x->setparent(z->getparent());
           
            
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
        else
        {
            
            bool isleft = dynamic_cast<RedBlackTreeNode*>(z->getparent()->getleft()) == z? true :false;
            if(isleft)
            {
                
                z->getparent()->setleft(NULL);
                dir = 1;
            }
            else
            {
                z->getparent()->setright(NULL);
                dir = 0;
            }
            parent = dynamic_cast<RedBlackTreeNode*>(z->getparent());
        }
    }
    
    
  
  
    
    if(z != w)
    {
       
        
        z->setleft(w->getleft());
        z->setright(w->getright());
        z->setparent(w->getparent());
        w->getleft()->setparent(z);
        w->getright()->setparent(z);
        
        bool newroot = w == root;
        if(newroot)
        {
            root = z;
        }
        else
        {
            bool isleft = dynamic_cast<RedBlackTreeNode*>(w->getparent()->getleft()) == w ? true:false;
            if(isleft)
            {
                w->getparent()->setleft(z);
            }
            else
            {
                w->getparent()->setright(z);
            }
        }
        
       
      
        
        if(z->getcolor() == 0)
        {
            z->setcolor(w->getcolor());
            
            if(isXNull)
            {
                deleteFixNull(parent , dir);
            }
            else
            {
                deleteFix(x);
            }
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
            if(isXNull)
            {
                deleteFixNull(parent , dir);
            }
            else
            {
                deleteFix(x);
            }
        }
        delete z;
    }
    return true;
}

AbstractTreeNode* RedBlackTreeNoSentinal::getNullNode()
{
    return NULL;
}

AbstractTreeNode* RedBlackTreeNoSentinal::getTopNode()
{
    return root;
}

