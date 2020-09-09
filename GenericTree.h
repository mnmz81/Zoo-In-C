#ifndef GENERICTREE_H
#define GENERICTREE_H
#define ALLOC(typ,num) ((typ *) checked_malloc(sizeof(typ)*(num)))
#define SWAP(a,b,t) {t=(a);a=(b);b=(t);}
/*******************************************/
typedef struct treeNode {
  void *data;
  struct treeNode *left;
  struct treeNode *right;
}TreeNode;
/*******************************************/
typedef struct linkedList{
  void *data;
  struct linkedList *next;
}LinkedList;
/*******************************************/
TreeNode* createTree(); /*creates and allocates a new tree*/
TreeNode* addNode(TreeNode *head, void *data, int (*compare) (void*,void*)); /*adds a new node to the tree*/
TreeNode* removeLeaf(TreeNode* head, void* tofind, int (*compare)(void *arg1, void *arg2), void (*freeNode)(void *arg1)); /*removes a node from the tree*/ 
TreeNode * tree_find_max(TreeNode * head, TreeNode **parent); /*finds the object with the highest value*/
TreeNode * tree_find_min(TreeNode * head, TreeNode **parent); /*finds the object with the lowest value*/
TreeNode * tree_find(TreeNode * head, void* tofind, TreeNode **parent, int (*compare) (void *arg1, void *arg2)); /*with given value and head of tree, function returns the exact leaf that contains the object with that value*/
void findNode(TreeNode* headTree, LinkedList** headList, void* tofind, int (*compare) (void *arg1, void *arg2)); /*finds all the objects, that have the same value, and inserts it to a linked list*/
double averageKey(TreeNode* head, int* num, int (*getData)(void* arg)); /*calculates the average value of all the database*/
void treeToArray(TreeNode* head, void* arr, int *i,void (*addToArray)(void* arr, int i, void* data)); /*with given pointer to array, this function converts the tree to an array*/
unsigned int getLeafCount(TreeNode* head); /*returns the amount of leaves in the tree*/
void printTree(TreeNode* head, void (*printData)(void* arg)); /*prints all the tree*/
void freeTree(TreeNode* head,void (*freeData)(void* arg)); /*deletes all the tree using the free function we built*/
void *checked_malloc(unsigned int size); /*used to check if allocation succeeded*/
/*******************************************/
    
#endif