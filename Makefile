run :
	g++ -o epp main.cpp eppcompiler.cpp exprtreenode.cpp heapnode.cpp minheap.cpp parser.cpp symnode.cpp symtable.cpp
	./epp $(code)