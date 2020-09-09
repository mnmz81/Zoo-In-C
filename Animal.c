#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Date.h"
#include "Animal.h"
#include "GenericTree.h"

/*******************************************/
void addNewAnimal(TreeNode** head_animal){  /*recieves all the needed parameters in order to add a new animal to the tree*/
    int j; /*variable for general uses in loops and such*/
    Animal* new=ALLOC(Animal,1);
    new->id=getAnimalId();

    if(checkIfIdExistsA(*head_animal, new->id)==1){
        printf("\nAnimal already exists!\n");
        free(new);
        return;
    }
    getAnimalType(&new->type);
    getAnimalColor(&new->color);
    getAnimalName(&new->name);
    getAnimalBirthday(&(new->birthdate));
    getAnimalOrigin(&new->origin);
    new->health=getAnimalHealth();
    new->offspring=getAnimalOffspring();
    for(j=0;j<new->offspring;j++)
            new->offspring_id[j]=getAnimalOffspringId();
    getAnimalFoodType(&new->food_type);
    new->mpd=getAnimalMpd();
    *head_animal=addNode(*head_animal, new, &compareAnimal);
    printf("\nAnimal added\n");
 }
/*******************************************/
int animalNumberWithGivenFoodKind_REC(char* bar, TreeNode* p){ /*recieves a barcode and recursively returns the amount of animals that consumes that food*/
   int i=0;
   LinkedList* headList=NULL;
   LinkedList* temp;
   findNode(p, &headList, bar,&compareAnimalFood);
   while(headList!=NULL){
       i++;
       temp=headList;
       headList=headList->next;
       free(temp);
   }
   return i;
 }
/*******************************************/
int animalNumberWithGivenColor(char* color, TreeNode* p){  /*recieves a color and return how many animals have that color*/
    int i=0;
    LinkedList* headList=NULL;
    LinkedList* temp;
    findNode(p, &headList, color,&compareAnimalColor);
    while(headList!=NULL){
        i++;
        temp=headList;
        headList=headList->next;
        free(temp);
    }
    return i;
 }
/*******************************************/
void deleteAnimal(int animalId, TreeNode** head_animal){  /*recieves an ID and goes through all the tree to find the animal and delete his struct*/
    *head_animal=removeLeaf(*head_animal, &animalId, &compareAnimalId, &freeWilly);
    return ;
 }
/*******************************************/
void deleteAllAnimals(TreeNode* head_animal){  /*zeroes all the animal tree*/
    freeTree(head_animal,&freeWilly);
    printf("\nAll animals deleted\n");
 }
/*******************************************/
void printAnimalsForGivenBirthYear_REC(int* year, TreeNode* p){ /*with given birth year, this function will recursively print all the animals that were born in that year*/
    LinkedList* headList=NULL;
    LinkedList* temp;
    findNode(p, &headList, year,&compareAnimalYear);
    if(headList==NULL){
       printf("\nNo animals found that match this year\n");
       return;
    } 
    while(headList!=NULL){
        printAnimalNode(headList->data);
        temp=headList;
        headList=headList->next;
        free(temp);
    }
 }
/*******************************************/
double average(TreeNode* p,int* num){ /*calculates the average number of animals' offsprings*/
    return averageKey(p , num ,&getOffspring);
 }

/**********************************************/

/**********************************************/
int getAnimalId(){  /*gets animal's ID and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L];
    char c;
    for(;;){
        printf("\nPlease enter animal's ID(5 digits):\n");
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
        if(strlen(temp)!=5 || temp[0]=='\0' || atoi(temp)<10000)
            printf("\nError getting ID, try again!!\n");
        else
            return atoi(temp);
    }
 }
/**********************************************/
void getAnimalType(char **p){ /*gets animal's type and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L];
    char c;
    for(;;){
        printf("\nPlease enter animal's type:\n");
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
            printf("\nError getting type, try again!!\n");
        else
        {
            *p=ALLOC(char,i);
            strcpy(*p,&(temp[0]));
            return;
        }
    }
 } 
/**********************************************/
void getAnimalColor(char **p){  /*gets animal's color and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L];
    char c;
    for(;;){
        printf("\nPlease enter animal's color:\n");
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
        if(strlen(temp)<3)
                printf("\nError getting color, try again!!\n");
        else{
            *p=ALLOC(char,i);
            strcpy(*p,&(temp[0]));
            return ;
        }
    }
 }
/**********************************************/
void getAnimalName(char** p){  /*gets animal's name and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L];
    char c;
    for(;;){
        printf("\nPlease enter animal's name:\n");
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
        if((strlen(temp)==0))
            printf("\nError getting name, try again!!\n");
        else{
                *p=ALLOC(char,i);
                strcpy(*p,&(temp[0]));
            return ;
        }
    }
 }
/**********************************************/
void getAnimalOrigin(char** p){  /*gets animal's origin and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L];
    char c;
    for(;;){
        printf("\nPlease enter animal's origin:\n");
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
        if((strlen(temp)<2))
            printf("\nError getting origin, try again!!\n");
        else{
            *p=ALLOC(char,i);
            strcpy(*p,&(temp[0]));
            return;
        }
    }
 }
/**********************************************/
void getAnimalBirthday(Date* p){  /*gets animal's birth date and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char c,temp[MAX_L];
    for(;;) {   
        printf("\nPlease enter animal's birthdate\n");
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
                printf("\nError getting Day, try again!!\n");
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
                printf("\nError getting Month, try again!!\n");
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
                printf("\nError getting year, try again!!\n");
            else{
                p->year=i;
                break;  
            }
        }
        return;
    }
 }
/**********************************************/
int getAnimalOffspringId(){  /*gets animal's offspring ID and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L];
    char c;
    for(;;){
        printf("\nPlease enter animal's offspring ID(5 digits):\n");
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
        if(strlen(temp)!=5 || temp[0]=='\0')
            printf("\nError getting ID, try again!!\n");
        else
            return atoi(temp);
    }
 }
/**********************************************/
int getAnimalHealth(){  /*gets animal's health condition and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char c,temp[MAX_L];
    for(;;){
        printf("\nPlease enter animal's health condition(1-100):\n");
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
        if((atoi(temp)<=0)||(atoi(temp)>100)||temp[0]=='\0')
        {
            printf("\nError getting health condition, try again!!\n");
            continue;
        }
        return atoi(temp);
    }
 }
/**********************************************/
int getAnimalOffspring(){  /*gets animal's amount of offsprings and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char c,temp[MAX_L];
    for(;;){
        printf("\nPlease enter animal's amount of offsprings:\n");
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
        if((atoi(temp)<0)||(atoi(temp)>1000)||temp[0]=='\0')
            printf("\nError getting amount of offsprings, try again!!\n");
        else
            return atoi(temp);
    }
 }
/**********************************************/
void getAnimalFoodType(char** p){  /*gets animal's suitable food type and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L];
    char c;
    for(;;){
        printf("\nPlease enter designated food's barcode(20 digits):\n");
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
        if((strlen(temp)!=20))
            printf("\nError getting barcode, try again!!\n");
        else{
            *p=ALLOC(char,i);
            strcpy(*p,&(temp[0]));
            return;
        }
    }
 }
/**********************************************/
int getAnimalMpd(){  /*gets animal's amount of meals per day and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char c,temp[MAX_L];
    for(;;){
        printf("\nPlease enter animal's number of meals per day (0-10):\n");
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
        if((atoi(temp)<0)||(atoi(temp)>10)||temp[0]=='\0')
            printf("\nError getting number, try again!!\n");
        else
            return atoi(temp);
    } 
 }
/**********************************************/
void printAnimalNode(void* t){ /*gets a specific node and prints it's contents*/
    int i; /*variable for general uses in loops and such*/
    printf("Type: %s\n",((Animal*)t)->type);
    printf("Name: %s\n", ((Animal*)t)->name);
    printf("Color: %s\n",((Animal*)t)->color);
    printf("ID: %d\n",((Animal*)t)->id);
    printf("Origin: %s\n",((Animal*)t)->origin);
    printf("Food type: %s\n",((Animal*)t)->food_type);
    printf("Amount of offsprings: %d\n",((Animal*)t)->offspring);
    printf("Offsprings' ID's:  ");
    for(i=0 ; i<((Animal*)t)->offspring ; i++)
        printf("#%d: %d,  ", i+1,((Animal*)t)->offspring_id[i]);
    printf("\n");
    printf("Birthdate: %d/%d/%d\n",((Animal*)t)->birthdate.day, ((Animal*)t)->birthdate.month,((Animal*)t)->birthdate.year);
    printf("Amount of meals per day: %d\n",((Animal*)t)->mpd);
    printf("\n");
 }
/**********************************************/
void freeWilly(void* p){ /*freeing function for Animal_Node type*/
    Animal* temp=p;
    free(temp->type);
    free(temp->color);
    free(temp->name);
    free(temp->origin);
    free(temp->food_type);
    free(temp);
    return;
 }

/**********************************************/
int checkIfIdExistsA(TreeNode* head_animal, int ID){ /*returns 1 if an identical ID already exists and 0 if not*/
    if (head_animal == NULL)
        return 0;
    if(((Animal*)(head_animal->data))->id == ID)
        return 1;

    if (((Animal*)(head_animal->data))->id < ID)
       return checkIfIdExistsA(head_animal->right, ID);
    return checkIfIdExistsA(head_animal->left, ID);
 }
/**********************************************/
int compareAnimal(void *arg1, void *arg2){
    if(((Animal*)arg1)->id==((Animal*)arg2)->id) return 0;
    if(((Animal*)arg1)->id >((Animal*)arg2)->id) return 1;
    return -1;
 }
/**********************************************/
int compareAnimalId(void *id,void *arg1){
    if(((Animal*)arg1)->id==*((int*)id)) return 0;
    if(((Animal*)arg1)->id >*((int*)id)) return 1;
    return -1;
 }
/**********************************************/
int compareAnimalFood(void *bar,void *arg1){
    if(strcmp(((Animal*)arg1)->food_type,(char*)bar)==0) return 1;
    return 0;
 }
/**********************************************/
int compareAnimalColor(void *color,void *arg1){
    if(strcmp(((Animal*)arg1)->color,(char*)color)==0) return 1;
    return 0;
 }
/**********************************************/
int compareAnimalYear(void *year,void *arg1){
    if(((Animal*)arg1)->birthdate.year ==*((int*)year)) return 1;
    return 0;
 }
/**********************************************/
int getOffspring(void *arg1){
    return ((Animal*)arg1)->offspring;
 }
/**********************************************/
