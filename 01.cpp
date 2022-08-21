#include"AVL_Tree.h"

int main()
{
	avl_tree t;

	t = NULL;
	t = insert(4, t);
	t = insert(1, t); 
	t = insert(2, t); 
	t = insert(3, t);   
	t = insert(5, t); 
	t = insert(7, t);
	t = insert(6, t);
	t = insert(16, t);
	t = insert(15, t);
	print_tree(1,9,t); 
	printf("\n\n\n");

	make_empty(t);
	return 0;
}
