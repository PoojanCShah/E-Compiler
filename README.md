# E++Compiler

We implement a compiler using the following datastructures :

1. AVL trees for maintaining a symbol table
2. Binary Heap for memory management
3. Stack Machine as target architecture
4. Parse trees

## How to run this project ?
After cloning the repo, use
`make run code=<filename>` where `<filename>` has the source code. A file `targ.txt` will be generated which will contain the compiled code

### Source Language
This language is an imperative language for doing arithmetic. It has the following syntax : 
$$e \in Exp ::= n | x | e1 + e2 | e1 - e2 | e1 * e2 | e1 / e2 $$
$$c \in  Com ::= x := e | ret := x | del := x$$

### Target Language 
| Command         | Description                                                                                                                                               | Example                                                                                               |
|-----------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------|
| `PUSH x`        | Pushes an integer `x` onto the stack.                                                                                                                      | `PUSH 5` results in the stack `[5]`.                                                                  |
| `PUSH mem[i]`   | Pushes the value stored in the memory location `i` onto the stack.                                                                                         | If `mem[0] = 10`, then `PUSH mem[0]` results in the stack `[10]`.                                     |
| `mem[i] = POP`  | Pops the value at the top of the stack and stores it in the memory location `i`.                                                                           | If the stack is `[20, 30]`, executing `mem[0] = POP` results in `mem[0] = 30` and the stack `[20]`.   |
| `DEL = mem[i]`  | Deletes the value stored at memory location `i` and frees it for future use.                                                                               | If `mem[1] = 15`, executing `DEL = mem[1]` results in `mem[1]` being cleared.                         |
| `ADD`           | Pops the top two elements from the stack, adds them, and pushes the result back onto the stack.                                                            | If the stack is `[3, 4]`, executing `ADD` results in the stack `[7]`.                                 |
| `SUB`           | Pops the top two elements from the stack, subtracts the top element from the second top element, and pushes the result back onto the stack.               | If the stack is `[10, 3]`, executing `SUB` results in the stack `[7]` (`10 - 3 = 7`).                 |
| `MUL`           | Pops the top two elements from the stack, multiplies them, and pushes the result back onto the stack.                                                      | If the stack is `[4, 5]`, executing `MUL` results in the stack `[20]`.                                |
| `DIV`           | Pops the top two elements from the stack, divides the second top element by the top element, and pushes the floor of the result back onto the stack.       | If the stack is `[10, 2]`, executing `DIV` results in the stack `[5]` (`10 / 2 = 5`).                 |
|                 | If division by zero is attempted, the result is set to NULL.                                                                                               | If the stack is `[10, 0]`, executing `DIV` results in the stack `[NULL]`.                             |
| `RET = POP`     | Pops the value at the top of the stack and stores it in a special memory location named `ret`. The execution of the program ends after this operation.     | If the stack is `[8]`, executing `RET = POP` results in `ret = 8` and the end of program execution.   |


### Example

```
x := 3
y := ( 2 * ( x + 1 ) )
z := ( 3 * ( y - 1 ) )
del := y
del := x
ret := z
```

```
PUSH 3
mem[0] = POP
PUSH 1
PUSH mem[0]
ADD
PUSH 2
MUL
mem[1] = POP
PUSH 1
PUSH mem[1]
SUB
PUSH 3
MUL
mem[2] = POP
DEL = mem[1]
DEL = mem[0]
PUSH mem[2]
RET = POP

```