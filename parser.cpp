/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

// Write your code below this line
//  #include<iostream> //please delete this
//  void traverse(ExprTreeNode* root)
//  {
//      if(!root)
//      {
//          return ;
//      }
//      traverse(root->left);
//      cout<<root->id<<" ";
//      traverse(root->right);
//  }
bool isnumber(string s)
{

    bool boo = true;
    if (s[0] == '-' && s.size() > 1)
    {
        for (int i = 1; i < s.size(); i++)
        {
            boo = boo && isdigit(s[i]);
        }
        return boo;
    }
    else
    {
        for (int i = 0; i < s.size(); i++)
        {
            boo = boo && isdigit(s[i]);
        }
        return boo;
    }
}
Parser::Parser()
{
    symtable = new SymbolTable();
    expr_trees = {};
}
void Parser::parse(vector<string> expression)
{
    vector<ExprTreeNode *> stack;
    int n = expression.size();
    for (int i = 0; i < n; i++)
    {

        if (expression[i] != ")")
        {
            if (expression[i] != "(")
            {
                string typ;
                ExprTreeNode *node;

                if (expression[i] == "+")
                {
                    typ = "ADD"; // continue from here
                    node = new ExprTreeNode(typ, -1);
                    node->id = expression[i];
                }
                else if (expression[i] == "*")
                {
                    typ = "MUL";
                    node = new ExprTreeNode(typ, -1);
                    node->id = expression[i];
                }
                else if (expression[i] == "/")
                {
                    typ = "DIV";
                    node = new ExprTreeNode(typ, -1);
                    node->id = expression[i];
                }
                else if (expression[i] == "-")
                {
                    typ = "SUB";
                    node = new ExprTreeNode(typ, -1);
                    node->id = expression[i];
                }
                else if (expression[i] == ":=")
                {
                    typ = "VAR";
                    node = new ExprTreeNode(typ, -1);
                    node->id = expression[i];
                }
                else if (isnumber(expression[i]))
                {

                    typ = "VAL";
                    int v = std::stoi(expression[i]);
                    node = new ExprTreeNode(typ, v);
                    node->id = expression[i];
                }
                else
                {
                    if (expression[i] == "del")
                    {
                        typ = "DEL";
                        node = new ExprTreeNode(typ, -1);
                        node->id = expression[i];
                    }
                    else if (expression[i] == "ret")
                    {
                        typ = "RET";
                        node = new ExprTreeNode(typ, -1);
                        node->id = expression[i];
                    }
                    else
                    {
                        typ = "VAR";
                        node = new ExprTreeNode(typ, -1);
                        node->id = expression[i];
                    }
                }

                stack.push_back(node);
            }
        }

        else
        {
            ExprTreeNode *right = stack.back();
            stack.pop_back();
            ExprTreeNode *op = stack.back();
            stack.pop_back();
            ExprTreeNode *left = stack.back();
            stack.pop_back();
            op->left = left;
            op->right = right;
            stack.push_back(op);
        }
    }

    ExprTreeNode *right = stack.back();
    stack.pop_back();
    ExprTreeNode *op = stack.back();
    stack.pop_back();
    ExprTreeNode *left = stack.back();
    stack.pop_back();
    op->left = left;
    op->right = right;
    expr_trees.push_back(op);
    ExprTreeNode *v = expr_trees.back()->left;
    if (v->type == "VAR")
    {

        symtable->insert(v->id);

        // please see this
    }
    else if (v->type == "DEL")
    {
        last_deleted = symtable->search(expr_trees.back()->right->id);
        // cout<<last_deleted<<endl;
        symtable->remove(v->id);
    }
}

Parser::~Parser()
{
    delete symtable;
    for (int i = 0; i < expr_trees.size(); i++)
    {
        delete expr_trees[i];
    }
}

// int main()
// {
//     Parser p;
//     p.parse({"x",":=","456"});
//     p.parse({"del",":=","x",});
//     p.parse({"x",":=","456"});
//     p.parse({"y",":=","(","x","/","5",")"});
//     for(auto v:p.expr_trees)
//     {
//         traverse(v);cout<<endl;
//     }

// }