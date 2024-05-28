/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

// Write your code below this line
// #include <iostream> //please delete this
// using namespace std;//plsdelete
EPPCompiler::EPPCompiler()
{
    Parser *targp = new Parser();
    targ = *targp;
    memory_size = 0;
    output_file = "";
    mem_loc = {};
    MinHeap *least_mem_locp = new MinHeap();
    least_mem_loc = *least_mem_locp;
}

EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
    Parser *targp = new Parser();
    targ = *targp;
    memory_size = mem_limit;
    output_file = out_file;
    // vector<int> temp(mem_limit);
    // for (int i = 0; i < mem_limit; i++)
    // {
    //     temp[i] = mem_limit - i - 1;
    // }
    // mem_loc = temp;
    for(int i = 0; i < mem_limit; i++)
    {
        least_mem_loc.push_heap(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code)
{
    vector<string> program = {};
    for (int i = 0; i < code.size(); i++)
    {
        targ.parse(code[i]);
        ExprTreeNode *v = targ.expr_trees.back()->left;
        if (v->type == "DEL")
        {
            int free_add = targ.last_deleted;
            // mem_loc.push_back(free_add);
            least_mem_loc.push_heap(free_add);
        }
        else if (v->type == "VAR")
        {
            if(targ.symtable->search(v->id) == -1)
            {
               
                // int free_add = mem_loc.back();
                // mem_loc.pop_back();
                int free_add = least_mem_loc.get_min();
                least_mem_loc.pop();
                targ.symtable->assign_address(v->id, free_add);
                // cout<<targ.symtable->search(v->id)<<endl;
            }
                
            
        }
        vector<string> low_lvl = generate_targ_commands();
        for(auto s : low_lvl)
        {
            program.push_back(s);
        }
    }
    write_to_file(program);
}

vector<string> converthitolo(ExprTreeNode *root, SymbolTable *symtable, int last)
{
    vector<string> curr = {};
    if (root->type == "VAL")
    {
        string s = "PUSH " + std::to_string(root->num);
        curr.push_back(s);
        return curr;
    }
    else if (root->type == "VAR" && root->id != ":=" && (symtable->search(root->id)!=-2))
    {
        string mem = std::to_string(symtable->search(root->id));
        string s = "";
        s = s + "PUSH ";
        s = s + "mem[";
        s = s + mem;
        s = s + "]";
        curr.push_back(s);
        return curr;
    }
    else if (root->type == "ADD")
    {
        vector<string> right = converthitolo(root->right, symtable, last);
        vector<string> left = converthitolo(root->left, symtable,last);
        for (int i = 0; i < right.size(); i++)
        {
            curr.push_back(right[i]);
        }
        for (int i = 0; i < left.size(); i++)
        {
            curr.push_back(left[i]);
        }
        curr.push_back("ADD");
        return curr;
    }
    else if (root->type == "MUL")
    {
        vector<string> right = converthitolo(root->right, symtable,last);
        vector<string> left = converthitolo(root->left, symtable,last);
        for (int i = 0; i < right.size(); i++)
        {
            curr.push_back(right[i]);
        }
        for (int i = 0; i < left.size(); i++)
        {
            curr.push_back(left[i]);
        }
        curr.push_back("MUL");
        return curr;
    }
    else if (root->type == "DIV")
    {
        vector<string> right = converthitolo(root->right, symtable,last);
        vector<string> left = converthitolo(root->left, symtable,last);
        for (int i = 0; i < right.size(); i++)
        {
            curr.push_back(right[i]);
        }
        for (int i = 0; i < left.size(); i++)
        {
            curr.push_back(left[i]);
        }
        curr.push_back("DIV");
        return curr;
    }
    else if (root->type == "SUB")
    {
        vector<string> right = converthitolo(root->right, symtable,last);
        vector<string> left = converthitolo(root->left, symtable,last);
        for (int i = 0; i < right.size(); i++)
        {
            curr.push_back(right[i]);
        }
        for (int i = 0; i < left.size(); i++)
        {
            curr.push_back(left[i]);
        }
        curr.push_back("SUB");
        return curr;
    }
    else if (root->id == ":=")
    {
        if (root->left->type == "DEL")
        {
            // vector<string> right = converthitolo(root->right, symtable,last);
            // for (int i = 0; i < right.size(); i++)
            // {
            //     curr.push_back(right[i]);
            // }
            string mem = std::to_string(last);
            string s = "";
            s = s + "DEL = ";
            s = s + "mem[";
            s = s + mem;
            s = s + "]";
            curr.push_back(s);
            return curr;
        }
        else if(root->left->type == "RET")
        {
            vector<string> right = converthitolo(root->right, symtable,last);
            for (int i = 0; i < right.size(); i++)
            {
                curr.push_back(right[i]);
            }
            curr.push_back("RET = POP");
            return curr;
        }
        else
        {
            vector<string> right = converthitolo(root->right, symtable,last);
            for (int i = 0; i < right.size(); i++)
            {
                curr.push_back(right[i]);
            }
            string mem = std::to_string(symtable->search(root->left->id));
            string s = "";
            s = s + "mem[";
            s = s + mem;
            s = s + "] = POP";
            curr.push_back(s);
            return curr;
        }
    }
}
vector<string> EPPCompiler::generate_targ_commands()
{
    return converthitolo(targ.expr_trees.back(),targ.symtable,targ.last_deleted);
}

void EPPCompiler::write_to_file(vector<string> commands)
{ // clear the file here
    std::fstream outputfile(output_file,std::ios::out);
    for (const std::string& str : commands) {
        outputfile << str << std::endl;
        // cout<<str<<endl;
    }
    outputfile.close();
}

EPPCompiler::~EPPCompiler()
{
    // targ.~Parser();
    // least_mem_loc.~MinHeap();
}

// int main()
// {
//     EPPCompiler e("out.txt",5);
//     // vector<vector<string>> code = {{"x",":=","(","5","+","8",")"},{"y",":=","(","x","*","7",")"},{"del",":=","x"}};
//     // vector<vector<string>> code  = {{"x",":=","3"},{"y",":=","1"},{"z",":=","(","x","/","y",")"},{"del",":=","y"},{"ret",":=","(","z","+","z",")"}};
//     // vector<vector<string>> code = {{"x",":=","5"},{"y",":=","(","x","-","90",")"},{"z",":=","(","y","*","y",")"},{"del",":=","x"},{"w",":=","67"},{"ret",":=","z"}};
//     vector<vector<string>> code = {{"x",":=","-3"},{"y",":=","5"},{"z",":=","7"},{"del",":=","x"},{"del",":=","y"},{"w",":=","(","5","+","(","z","/","2",")",")"},{"ret",":=","w"}};
//      e.compile(code);

// }