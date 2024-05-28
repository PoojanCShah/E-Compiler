/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
// #include <iostream>
//Write your code below this line

// void print2DUtil(HeapNode* root, int space)
// {
    
//     // Base case
//     if (root == NULL)
//         return;
 
//     // Increase distance between levels
//     space += 10;
 
//     // Process right child first
//     print2DUtil(root->right, space);
 
//     // Print current node after space
//     // count
//     cout << endl;
//     for (int i = 10; i < space; i++)
//         cout << " ";
//     cout << root->val<< "\n";
 
//     // Process left child
//     print2DUtil(root->left, space);
// }
 
// // Wrapper over print2DUtil()
// void print2D(HeapNode* root)
// {
//     // Pass initial space count as 0
//     print2DUtil(root,0);
// }
std::string tobin(int n) {
    if (n == 0) {
        return "0"; 
    }

    std::string binary = ""; 

    while (n > 0) {
        int bit = n % 2;         
        binary = std::to_string(bit) + binary; 
        n /= 2;           
    }

    return binary;
}

HeapNode* getnode(int n, HeapNode* root)
{
    HeapNode* curr = root;
    if(n==1)
    {
        return root;
    }
    string path = tobin(n);
    for(int j = 1; j < path.size();j++)
    {
        if(path[j] == '0')
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    return curr;
}
void HeapifyUp(HeapNode* root)
{
    if(!root) return;
    if(!root->par) return;
    if(root->val < root->par->val)
    {
        int temp = root->val;
        root->val = root->par->val;
        root->par->val = temp;
        HeapifyUp(root->par);
    }
}

void HeapifyDown(HeapNode* root)
{
    if(!root->left && !root->right)
    {
        return ;
    } 
    else if(root->left && !root->right)
    {
        if(root->val > root->left->val)
        {
            std::swap(root->val,root->left->val);
            HeapifyDown(root->left);
        }
    }
    else if(!root->left && root->right)
    {
        if(root->val > root->right->val)
        {
            std::swap(root->val,root->right->val);
            HeapifyDown(root->right);
        }
    }
    else
    {
        int mini = root->val;
        if(mini > root->left->val) mini = root->left->val;
        if(mini > root->right->val) mini = root->right->val;
        if(mini == root->right->val)
        {
            std::swap(root->val,root->right->val);
            HeapifyDown(root->right);
        }
        else if(mini == root->left->val)
        {
            std::swap(root->val,root->left->val);
            HeapifyDown(root->left);
        }
    }
}

MinHeap::MinHeap(){

}

void MinHeap::push_heap(int num){
    if(size==0)
    {
        size++;
        root = new HeapNode(num);
        return;
    }
    size++;
    int n = (size)/2;
    HeapNode* parent = getnode(n,root);
    HeapNode* newnode = new HeapNode(num);
    if(parent->left == NULL)
    {
        parent->left = newnode;
    }
    else
    {
        parent->right = newnode;
    }
    newnode->par = parent;
    HeapifyUp(newnode);
}

int MinHeap::get_min(){
    return root->val;

}

void MinHeap::pop(){
    HeapNode* last = getnode(size,root);
    if(last == root)
    {
        delete root;
        root = NULL;
        size--;
        return ;
    }
    std::swap(root->val,last->val);
    if(last->par->left==last)
    {
        last->par->left = NULL;
        delete last;
    }
    else
    {
        last->par->right = NULL;
        delete last;
    }
    HeapifyDown(root);
    size--;
}

MinHeap::~MinHeap(){
    delete root;

}

// int main()
// {
//     MinHeap hp;
//    for(int i = 100; i >=0 ; i--)
//    {
//     hp.push_heap(i);
//    }
//    for(int i = 100; i >=0 ;i--)
//    {
//     cout<<hp.get_min()<<endl;
//     hp.pop();
//    }
// }
