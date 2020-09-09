#include "GenericTree.h"
#include "Animal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TreeNode* createTree(){ /*creates and allocates a new tree*/
    TreeNode* head=ALLOC(TreeNode, 1);
    head=NULL;
    return head;
 }
/*******************************************/
TreeNode* addNode(TreeNode *head, void *data, int(*compare)(void*,void*)) { /*adds a new node to the tree*/
  if(head==NULL) {
    TreeNode *temp;
    temp = ALLOC(TreeNode, 1);
    temp->data =data;
    temp -> left=NULL;
    temp -> right = NULL;
    return temp;
  }
  if(compare(data, head->data) ==-1)
    head->left = addNode(head->left, data, compare);
  else if(compare(data, head->data) == 1)
        head->right = addNode(head->right, data, compare);      
  return head;
 }
/*******************************************/
TreeNode* removeLeaf(TreeNode* head, void* tofind, int (*compare)(void *arg1, void *arg2), void (*freeNode)(void *arg1)){ /*removes a node from the tree*/
    TreeNode *node, *node2, *parent;
    void* temp;
    parent = NULL;
    node = tree_find(head, tofind, &parent, compare);
    if (!node){
        printf("\n Object not found!!\n");
        return head; 
     } 
    if (node->left==NULL && node->right==NULL){
        if (parent) {
            if (parent->left == node) parent->left=NULL;
            else parent->right=NULL;
            freeNode(node->data);
            free(node);
            printf("\nObject deleted\n");
            return head;
        } else {
            freeNode(node->data);
            free(node);
            printf("\nObject deleted\n");
            return NULL;
        }
     } 
    if (node->left) {
        node2 = tree_find_max(node->left, NULL);
        SWAP(node->data, node2->data, temp);
        node->left = removeLeaf(node->left, tofind, compare, freeNode);
    } else {
        node2 = tree_find_min(node->right, NULL);
        SWAP(node->data, node2->data, temp);
        node->right = removeLeaf(node->right, tofind, compare, freeNode);
    }
    return head;
 }
/*******************************************/
TreeNode * tree_find_max(TreeNode * head, TreeNode **parent) { /*finds the object with the highest value*/
    if (!head) return NULL;
    if (head->right) {
        if (parent) *parent = head;
        return tree_find_max(head->right, parent);
    } else {
        return head;
    }
 }
/*******************************************/
TreeNode * tree_find_min(TreeNode * head, TreeNode **parent) { /*finds the object with the lowest value*/
    if (!head) return NULL;
    if (head->left) {
        if (parent) *parent = head;
        return tree_find_min(head->left, parent);
    } else {
        return head;
    }
 }
/*******************************************/
TreeNode * tree_find(TreeNode * head, void* tofind, TreeNode **parent, int (*compare) (void *arg1, void *arg2)) { /*with given value and head of tree, function returns the exact leaf that contains the object with that value*/
    if (!head) return NULL;
    if (compare(tofind, head->data)>0) {
        if (parent) *parent = head;
        return tree_find(head->right, tofind,parent, compare);
    } else if (compare(tofind, head->data)<0) {
        if (parent) *parent = head;
        return tree_find(head->left, tofind,parent, compare);
    } else {
        return head;
    }
 }
/*******************************************/
void findNode(TreeNode* headTree, LinkedList** headList, void* tofind, int (*compare) (void *arg1, void *arg2)){ /*finds all the objects, that have the same value, and inserts it to a linked list*/
    LinkedList* temp;
    if(headTree==NULL)
        return;
    findNode(headTree->right, headList, tofind, compare);
    if(compare(tofind,headTree->data)==1){
        temp=ALLOC(LinkedList, 1);
        temp->data=headTree->data;
        if(*headList==NULL){
            *headList=temp;
            temp->next=NULL;
        }
        else{
            temp->next=*headList;
            *headList=temp;
        }
    }
    findNode(headTree->left, headList, tofind, compare);
 }
/*******************************************/
double averageKey(TreeNode* head, int* num, int (*getData)(void* arg)){	/*calculates the average value of all the database*/
	int num_L,num_R,sum;
    double avg_L,avg_R,avg;
    if(head==NULL){
        *num=0;
        return 0.0;
    }
    avg_L=averageKey(head->left, &num_L,getData);
    avg_R=averageKey(head->right, &num_R,getData);
    *num=(1+num_L+num_R);
    sum=((avg_L*num_L)+(avg_R*num_R)+(getData(head->data)));
    avg=(double)(sum)/(double)(*num);
    return avg;
 } 
/*******************************************/
void treeToArray(TreeNode* head, void* arr, int* i,void (*addToArray)(void* arr, int i, void* data)){ /*with given pointer to array, this function converts the tree to an array*/ 
    if(head == NULL)
        return ;
	treeToArray(head->left, arr, i,addToArray);
    addToArray(arr,*i,head->data);
    ++*i;
    treeToArray(head->right, arr, i, addToArray);
 }
/*******************************************/
unsigned int getLeafCount(TreeNode* head){ /*returns the amount of leaves in the tree*/
	if(head == NULL)       
	return 0;
	if(head->left == NULL && head->right==NULL)      
	return 1;            
	else
	return getLeafCount(head->left)+
			getLeafCount(head->right);      
 }
/*******************************************/
void printTree(TreeNode* head, void (*printData)(void* arg)){ /*prints all the tree*/
    if(head==NULL)
        return;
    printTree(head->left,printData);
    printData(head->data);
    printTree(head->right,printData);
    return;
 }
/*******************************************/
void freeTree(TreeNode* head,void (*freeData)(void* arg)){ /*deletes all the tree using the free function we built*/
      if(head!=NULL) {
        freeTree(head->left,freeData);
        freeTree(head->right,freeData);
        freeData(head->data);
        free(head);
      }
    return;
 }

/*******************************************/
void *checked_malloc(unsigned int size){ /*used to check if allocation succeeded*/
	void * ret;

	ret = malloc(size);
	if (!ret) {
		perror ("Memory allocation error");
		exit (1);
	}
	return ret;
    }

/*******************************************/
