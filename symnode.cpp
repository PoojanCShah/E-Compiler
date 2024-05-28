/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line
int get_height(SymNode *n)
{
    if (!n)
    {
        return 0;
    }
    else
    {
        return n->height;
    }
}

void set_height(SymNode *n)
{
    if (!n)
    {
        return;
    }
    else
    {
        //n->height=1;
        int lh = get_height(n->left);
        int rh = get_height(n->right);
        n->height = 1 + max(lh,rh);
        return;
    }
}
SymNode::SymNode(){
    key = "";
    height = 0;
    par = NULL;
    left = NULL;
    right = NULL;

}

SymNode::SymNode(string k){
    key = k;
    height = 0;
    par = NULL;
    left = NULL;
    right = NULL;
}

// SymNode* SymNode::LeftLeftRotation(){
//       return NULL;
// }
SymNode *SymNode::LeftLeftRotation()
{
    SymNode *y = right;
    SymNode *t1 = y->left;
    right = t1;
    if (t1)
    {
        t1->par = this;
    }
    y->left = this;
    y->par = par;
    par = y;
    set_height(this);
    set_height(y);
    return y;
}
// SymNode* SymNode::RightRightRotation(){
//     return NULL;

// }
SymNode *SymNode::RightRightRotation()
{
    SymNode *y = left;
    SymNode *t1 = y->right;
    left = t1;
    if (t1)
    {
        t1->par = this;
    }
    y->right = this;
    y->par = par;
    par = y;
    set_height(this);
    set_height(y);
    // cout<<y->key<<" "<<y->height<<" "<<y->left->key<<" "<<y->right->key<<endl;
    // cout<<y->left->height<<" "<<y->right->height<<endl;
    return y;
}

// SymNode* SymNode::LeftRightRotation(){
//   return NULL;
// }

SymNode *SymNode::LeftRightRotation()
{
    SymNode *y = right;
    SymNode *z = y->left;
    SymNode *t1 = z->left;
    SymNode *t2 = z->right;
    y->left = t2;
    if (t2)
    {
        t2->par = y;
    }
    z->right = y;
    y->par = z;
    right = t1;
    if (t1)
    {
        t1->par = this;
    }
    z->left = this;
    z->par = par;
    par = z;
    set_height(this);
    set_height(y);
    set_height(z);
    return z;
}

// SymNode* SymNode::RightLeftRotation(){
//   return NULL;
// }

SymNode *SymNode::RightLeftRotation()
{
    SymNode *y = left;
    SymNode *z = y->right;
    SymNode *t1 = z->left;
    SymNode *t2 = z->right;
    y->right = t1;
    if (t1)
    {
        t1->par = y;
    }
    z->left = y;
    y->par = z;
    left = t2;
    if (t2)
    {
        t2->par = this;
    }
    z->right = this;
    z->par = par;
    par = z;
    set_height(this);
    set_height(y);
    set_height(z);
    return z;
}

SymNode::~SymNode(){
    

}