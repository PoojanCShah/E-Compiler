/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

// Write your code below this line

int get_height1(SymNode *n)
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

void set_height1(SymNode *n)
{
    if (!n)
    {
        return;
    }
    else
    {
        // n->height=1;
        int lh = get_height1(n->left);
        int rh = get_height1(n->right);
        n->height = 1 + max(lh, rh);
        return;
    }
}

int balance_factor(SymNode *n)
{
    if (!n)
    {
        return 0;
    }
    int bal = get_height1(n->right) - get_height1(n->left);
    return bal;
}

bool is_balanced(SymNode *n)
{
    if (!n)
        return true;
    int bal = balance_factor(n);
    return (bal >= -1) && (bal <= 1);
}

SymNode *balance_node(SymNode *n)
{
    int bal = balance_factor(n);
    // cout<<bal<<endl;
    if (bal < -1)
    {
        int left_bal = balance_factor(n->left);
        if (left_bal <= 0)
        {
            return n->RightRightRotation();
        }
        else
        {
            return n->RightLeftRotation();
        }
    }
    else if (bal > 1)
    {
        int right_bal = balance_factor(n->right);
        if (right_bal >= 0)
        {
            return n->LeftLeftRotation();
        }
        else
        {
            return n->LeftRightRotation();
        }
    }
    else
    {
        return n;
    }
}

void fixup(SymNode *n, SymNode *&root)
{
    while (n != NULL)
    {
        // cout<<root->key<<endl;
        if (!is_balanced(n))
        {
            SymNode *z = balance_node(n); // cout<<z->key<<"heere"<<n->key<<endl;
            if (z->par)
            {
                if (z->par->left == n)
                {
                    z->par->left = z;
                }
                else
                {
                    z->par->right = z;
                }
            }
            n = z;
            // set_height(n);
            // cout<<n->key<<" "<<n->par->key<<endl;
        }
        // cout<<n->key<<" "<<n->height<<endl;
        set_height1(n);
        if (n->par == NULL)
        {
            root = n;
        }
        n = n->par; // cout<<n->key<<" "<<n->left->key<<" "<<n->left->height<<endl;
    }
}

SymNode *search_node(SymNode *root, string k)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->key == k)
    {
        return root;
    }
    else if (root->key < k)
    {
        return search_node(root->right, k);
    }
    else
    {
        return search_node(root->left, k);
    }
}

SymbolTable::SymbolTable()
{
    root = NULL;
    size = 0;
}

// void SymbolTable::insert(string k)
// {
// }

void SymbolTable::insert(string k)
{
    SymNode *u = search_node(root, k);
    if (u)
        return;
    SymNode *x = root;
    SymNode *y = NULL;
    SymNode *z = new SymNode(k);
    z->height = 1;
    size++;
    while (x != NULL)
    {
        y = x;
        if (k < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    if (y == NULL)
    {
        root = z;
    }
    else if (k < y->key)
    {
        y->left = z;
        z->par = y;
    }
    else
    {
        y->right = z;
        z->par = y;
    }
    fixup(z, root);
}
SymNode *min(SymNode *root)
{
    if (!root)
    {
        return root;
    }
    SymNode *lol = root;
    while (lol->left)
    {
        lol = lol->left;
    }

    return lol;
}

void SymbolTable::remove(string k)
{
    if (!root)
    {
        return;
    }
    SymNode *z = search_node(root, k);
    if (!z)
    {
        return;
    }
    if (z == root)
    {
        if (!z->left && !z->right)
        {
            delete root;
            root = NULL;
        }
        else if (z->left && !z->right)
        {
            z->left->par = NULL;
            root = z->left;
            delete z;
        }
        else if (!z->left && z->right)
        {
            z->right->par = NULL;
            root = z->right;
            delete z;
        }
        else
        {
            SymNode *y = min(z->right);
            SymNode *parent = y->par;
            int addr = y->address;
            string ke = y->key;
            remove(y->key);
            SymNode *w = search_node(root, k);
            w->key = ke;
            w->address = addr;
            fixup(parent,root);
        }
    }
    else
    {
        SymNode *p = z->par;
        if (!z->left && !z->right)
        {
            if (z == p->left)
            {
                p->left = NULL;
                delete z;
            }
            else
            {
                p->right = NULL;
                delete z;
            }
            fixup(p, root);
        }
        else if (!z->left && z->right)
        {
            if (z == p->left)
            {
                p->left = z->right;
            }
            else
            {
                p->right = z->right;
            }
            z->right->par = p;
            delete z;
            fixup(p, root);
        }
        else if (z->left && !z->right)
        {
            if (z == p->left)
            {
                p->left = z->left;
            }
            else
            {
                p->right = z->left;
            }
            z->left->par = p;
            delete z;
            fixup(p, root);
        }
        else
        {
            SymNode *y = min(z->right);
            SymNode* parent = y->par;
            int addr = y->address;
            string ke = y->key;
            remove(y->key);
            SymNode *w = search_node(root, k);
            w->key = ke;
            w->address = addr;
            fixup(parent,root);
        }
    }
}

// void SymbolTable::remove(string k)
// {

//     if (!search_node(root, k))
//     {
//         return;
//     }
//     size--;
//     SymNode *z = search_node(root, k);
//     SymNode *p = z->par;
//     if (size == 0)
//     {

//         root = NULL;
//         return;
//     }

//     if (!z->left && !z->right)
//     {
//         if (p)
//         {
//             if (z == p->right)
//             {
//                 p->right = NULL;
//             }
//             else
//             {
//                 p->left = NULL;
//             }
//         }
//     }
//     else if (!z->left)
//     {
//         if (p)
//         {
//             if (p->key < z->key)
//             {
//                 p->right = z->right;
//                 z->right->par = p;
//             }
//             else
//             {
//                 p->left = z->right;
//                 z->left->par = p;
//             }
//             z->par = NULL;
//         }
//         else
//         {
//             root = z->right;
//         }
//     }
//     else if (!z->right)
//     {
//         if (p)
//         {
//             if (p->key < z->key)
//             {
//                 p->right = z->left;
//                 z->left->par = p;
//             }
//             else
//             {
//                 p->left = z->left;
//                 z->right->par = p;
//             }
//             z->par = NULL;
//         }
//         else
//         {
//             root = z->left;
//         }
//         if (p != NULL)
//         {
//             fixup(z, root);
//         }
//     }
//     else
//     {
//         SymNode *y = min(z->right);
//         string poojan = y->key;
//         int add = y->address;
//         remove(y->key);
//         z->key = poojan;
//         z->address = add;
//     }
// }

// int SymbolTable::search(string k)
// {
// }
int SymbolTable::search(string k)
{
    SymNode *z = search_node(root, k);
    if (z == NULL)
    {
        return -2;
    }
    else
    {
        return z->address;
    }
}

// void SymbolTable::assign_address(string k, int idx)
// {
// }
void SymbolTable::assign_address(string k, int idx)
{
    SymNode *z = search_node(root, k);
    if (z)
    {
        z->address = idx;
    }
}

int SymbolTable::get_size()
{
    return size;
}

SymNode *SymbolTable::get_root()
{
    return root;
}

void destroy(SymNode* root)
{
    if(!root)
    {
        return;
    }
    destroy(root->left);
    destroy(root->right);
    delete root;
}

SymbolTable::~SymbolTable()
{
    destroy(root);
}