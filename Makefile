all:
	gcc -ansi -pedantic-errors -Wall Zoo.c  GenericTree.c Animal.c Date.c Employee.c Food.c Menu.c -o ZooSystem
compile: