#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Employee.h"
#include "GenericTree.h"
#define M 100


/**********************************************/
void addNewEmployee(TreeNode** head_employee) { /*adds a new employee to the tree*/
    int j; /*variable for general uses in loops and such*/
    Employee* new=ALLOC(Employee,1);
    getEmployeeID(&new->ID);

    if(checkIfIdExistsE(*head_employee, new->ID)==1){
        printf("\nEmployee already exists!\n");
        free(new->ID);
        free(new);
        return;
    }

    getEmployeeFirstName(&new->first_name);
    getEmployeeLastName(&new->last_name);
    new->assigned_animals=getEmployeeAssignedAnimals();
    new->assigned_animals_id=ALLOC(int,new->assigned_animals);
    if(new->assigned_animals>0){
        printf("\nFill this list of assigned animals' ID:\n");
        for(j=0 ; j<new->assigned_animals ;){
            printf("\nAnimal ID #%d: ",j+1);
            new->assigned_animals_id[j]=getEmployeeAssignedAnimalsID();
            j++;
        }
    }
    getEmployeeWorkStart(&(new->work_start)); /*function in date c file. copies all the struct data to the destination struct*/
    *head_employee=addNode(*head_employee, new, &compareEmployee);
    printf("\nEmployee added\n");
 }
/*******************************************/
void deleteEmployee(TreeNode** head_employee){  /*recieves an ID and goes through all the tree to find the employee and delete his struct*/
    char* ID;
    getEmployeeID(&ID);
    *head_employee=removeLeaf(*head_employee, ID, &compareEmployeeId, &freeBob);
    free(ID);
    return;
 }
/*******************************************/
void deleteAllEmployees(TreeNode* head_employee){  /*zeroes all the employee tree*/
    freeTree(head_employee, &freeBob);
    printf("\nAll employees deleted\n");
 }
/*******************************************/
void printEmployeeNode(void* temp){ /*gets a specific node and prints it's contents*/
    int j; /*variable for general uses in loops and such*/
    Employee* p=(Employee*)temp;
    printf("\nFirst name: %s\n", p->first_name);
    printf("Last name: %s\n", p->last_name);
    printf("ID: %s\n", p->ID);
    printf("Amount of assigned animals: %d\n", p->assigned_animals);
    printf("Assigned animals ID's: ");
    for(j=0 ; j<p->assigned_animals ; j++)
        printf("%d, ", p->assigned_animals_id[j]);
    printf("\n");
    printf("Work starting date: %d/%d/%d\n", p->work_start.day, p->work_start.month, p->work_start.year);
    printf("\n");
 }
/**********************************************/
void printAll(TreeNode* p){ /*prints all the tree*/
    printTree(p, &printEmployeeNode);
 }
/*******************************************/
void findEmployee(TreeNode* head_employee){ /*this function uses 2 external functions, depends on what option the user chooses, to find an employee*/
    char c, *ID;
    int animals;
    LinkedList* headList=NULL;
    LinkedList* temp;
    printf("\nFind employees by:\n");
    printf("ID (1)\n");
    printf("Number of assigned animals (2)\n");
    c=inputCheckE();  

    switch(c){
        case '1':  
            getEmployeeID(&ID);
            findNode(head_employee, &headList, ID, &compareEmployeeId);
            free(ID);
            break;
        case '2':
            animals=getEmployeeAssignedAnimals();
            findNode(head_employee, &headList, &animals, &compareEmployeeAssignedAnimals);
            break;
        default:
            printf("\nIllegal choice!\n");
            return;
    }
    if(headList==NULL){
       printf("\nEmployee not found\n");
       return;
    } 
    while(headList!=NULL){
        printEmployeeNode(headList->data);
        temp=headList;
        headList=headList->next;
        free(temp);
    }
 }
/*******************************************/

/*******************************************/
void getEmployeeFirstName(char** p){  /*gets first name and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L];
    char c;
    for(;;){
        printf("\nPlease enter employee's first name:\n");
        for(i=0 ;;i++){  /*input check*/
            c=getchar();
            if(c=='\n'){
                temp[i]='\0';
                break;
            }
            if(isalpha(c) || c==' ')
                temp[i]=c;
            else
                temp[0]='\0';
        }
        if(strlen(temp)<2)
        {
            printf("\nError getting first name, try again!!\n");
            continue;
        }
        *p=ALLOC(char,i);
        strcpy(*p,&(temp[0]));
        return;
    }
 } 
/**********************************************/
void getEmployeeLastName(char** p){  /*gets last name and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L];
    char c;
    for(;;){
        printf("\nPlease enter employee's last name:\n");
        for(i=0 ;;i++){  /*input check*/
            c=getchar();
            if(c=='\n'){
                temp[i]='\0';
                break;
            }
            if(isalpha(c) || c==' ')
                temp[i]=c;
            else
                temp[0]='\0';
        }
        if(strlen(temp)<2)
        {
            printf("\nError getting last name, try again!!\n");
            continue;
        }
        *p=ALLOC(char,i);
        strcpy(*p,&(temp[0]));
        return;
    }
 } 
/**********************************************/
void getEmployeeID(char** p){  /*gets ID and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L];
    char c;
    for(;;){
        printf("\nPlease enter employee's ID(9 digits):\n");
        for(i=0 ;;i++){  /*input check*/
            c=getchar();
            if(c=='\n'){
                temp[i]='\0';
                break;
            }
            if(isdigit(c))
                temp[i]=c;
            else
                temp[0]='\0';
        }
        if(strlen(temp)!=9)
        {
            printf("\nError getting ID, try again!!\n");
            continue;
        }
        *p=ALLOC(char,9);
        strcpy(*p, &(temp[0]));
        return;
    }
 }
/**********************************************/
int getEmployeeAssignedAnimals(){  /*gets an input for the amount of the employee's assigned animals and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L],c;
    for(;;){
    printf("\nPlease enter the amount of employee's assigned animals(200 MAX):\n");
    for(i=0 ;;i++){  /*input check*/
        c=getchar();
        if(c=='\n'){
            temp[i]='\0';
            break;
        }
        if(isdigit(c))
            temp[i]=c;
        else{
            temp[0]='\0';
        }
    }
    if((atoi(temp)<0)||(atoi(temp)>200)||temp[0]=='\0')
    {
        printf("\nError getting number, try again!!\n");
        continue;
    }
    return atoi(temp);
    }
 }
/**********************************************/
int getEmployeeAssignedAnimalsID(){ /*recieves animal's unique ID for each animal assigned to the employee*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L];
    char c;
    for(;;){
        for(i=0 ;;i++){  /*input check*/
            c=getchar();
            if(c=='\n'){
                temp[i]='\0';
                break;
            }
            if(isdigit(c))
                temp[i]=c;
            else{
                temp[0]='\0';
            }
        }
        if(strlen(temp)!=5 || temp[0]=='\0'){
            printf("\nError getting ID, try again!!\n");
            return -1;
        }
        else
            return atoi(temp);
    }
 }
/**********************************************/
void getEmployeeWorkStart(Date *p){  /*exact date in which the employee started working at the zoo (dd/mm/yyyy)*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L],c;
    for(;;) {
        printf("\nPlease enter employee's job starting date\n");
        for(;;){
            printf("Day(dd): ");
            for(i=0 ;;i++){  /*input check*/
                c=getchar();
                if(c=='\n'){
                    temp[i]='\0';
                    break;
                }
                if(isdigit(c))
                    temp[i]=c;
                else{
                    temp[0]='\0';
                }
            }
            i=atoi(temp);
            if((i<=0)||(i>31)||temp[0]=='\0')
                printf("Error getting day, try again!!\n");
            else{
                p->day=i;
                break;
            }
         }
        for(;;){
            printf("Month(mm): ");
            for(i=0 ;;i++){  /*input check*/
                c=getchar();
                if(c=='\n'){
                    temp[i]='\0';
                    break;
                }
                if(isdigit(c))
                    temp[i]=c;
                else{
                    temp[0]='\0';
                }
            }
            i=atoi(temp);
            if((i<=0)||(i>12)||temp[0]=='\0')
                printf("Error getting month, try again!!\n");
            else{
                p->month=i;
                break;    
            }
        }
        for(;;){
            printf("Year(yyyy): ");
            for(i=0 ;;i++){  /*input check*/
                c=getchar();
                if(c=='\n'){
                    temp[i]='\0';
                    break;
                }
                if(isdigit(c))
                    temp[i]=c;
                else{
                    temp[0]='\0';
                }
            }
            i=atoi(temp);
            if((i<=1900)||(i>2018)||temp[0]=='\0')
                printf("Error getting year, try again!!\n");
            else{
                p->year=i;
                break;  
            }
        }
        return;
    }
 }
/**********************************************/
char inputCheckE(){ /*checks input correction*/
    int i;
    char choice[20];
    char c;
    for(;;){
        for(i=0 ;;i++){  /*input check*/
            c=getchar();
            if(c=='\n'){
                choice[i]='\0';
                break;
            }
            choice[i]=c;
        }
        if(strlen(choice)!=1){
            return 0;
        }
        else{
            c=choice[0];
            return c;
        }
    }
 }
/*****************************************************/
void freeBob(void* p){ /*freeing function for TreeNode type*/
    Employee* temp=(Employee*)p;
    free(temp->first_name);
    free(temp->last_name);
    free(temp->ID);
    free(temp->assigned_animals_id);
    free(temp);
    return;
 }
/*****************************************************/
int checkIfIdExistsE(TreeNode* head_employee, char* ID){ /*returns 1 if an identical ID already exists and 0 if not*/
    if (head_employee == NULL)
        return 0;
    if(strcmp(((Employee*)(head_employee->data))->ID, ID)==0)
        return 1;

    if (strcmp(((Employee*)(head_employee->data))->ID, ID)<0)
       return checkIfIdExistsE(head_employee->right, ID);
    return checkIfIdExistsE(head_employee->left, ID);
 }
/*****************************************************/
int compareEmployee(void *arg1, void *arg2){
    if(strcmp(((Employee*)arg1)->ID, ((Employee*)arg2)->ID)==0) return 0;
    if(strcmp(((Employee*)arg1)->ID, ((Employee*)arg2)->ID)>0) return 1;
    return -1;
 }
/*****************************************************/
int compareEmployeeId(void *ID,void *arg1){
    if(strcmp(((Employee*)arg1)->ID,(char*)ID)==0) return 1;
    return 0;
 }
/**********************************************/
int compareEmployeeAssignedAnimals(void *assigned_animals, void *arg1){
    if(((Employee*)arg1)->assigned_animals ==*((int*)assigned_animals)) return 1;
    return 0;
 }
/*****************************************************/