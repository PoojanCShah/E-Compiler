/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    id = "";
    type = "VAR";
    num = -1;
    left = NULL;
    right = NULL;

}

ExprTreeNode::ExprTreeNode(string t,int v){
    id = "";
    type = t;
    num = v;
    left = NULL;
    right = NULL;
  
}

ExprTreeNode::~ExprTreeNode(){

}

