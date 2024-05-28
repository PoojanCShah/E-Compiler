/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

HeapNode::HeapNode(){
    val = -1;
    left = NULL;
    right = NULL;
    par = NULL;

}

HeapNode::HeapNode(int _val){
    val = _val;
    left = NULL;
    right = NULL;
    par = NULL;
}

HeapNode::~HeapNode(){
    if(this!=NULL)
    {
        if(left) delete left;
        if(right) delete right;
    }
    
  
}