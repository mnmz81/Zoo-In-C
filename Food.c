#include "Food.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "GenericTree.h"

void addNewFood(TreeNode** head_food){  /*adds a new food to the tree*/
    Food* new=ALLOC(Food,1);
    Designated_Animals* head_designated=new->designated_animals;
    
    getFoodBarcode(&new->barcode);
    if(checkIfBarcodeExists(*head_food, new->barcode)==1){
        printf("\nFood already exists!\n");
        free(new->barcode);
        free(new);
        return;
    }
    getFoodManufacturer(&new->manufacturer);
    getFoodDesignatedAnimals(head_designated);
    new->stock_quantity=getFoodStockQuantity();
    new->bag_weight=getFoodBagWeight();

    *head_food=addNode(*head_food, new, &compareFood);
    printf("\nFood added\n\n");
 }
/*******************************************/
void threePopularFoods(TreeNode* head_food, TreeNode* head_animal){  /*prints the 3 most popular food consumed by the animals*/
    TreeNode *f=NULL,*s=NULL,*t=NULL;
    if(head_animal==NULL){
        printf("\nNo animals in the zoo!!\n");
        return;
    }
    findMax(head_food,head_animal,&f,&s,&t);
    if(f==NULL){
        printf("\nNo food objects!!\n");
        return;
    }
    if(f!=NULL&& animalNumberWithGivenFoodKind_REC(((Food*)(f->data))->barcode,head_animal)!=0){
        printf("\n#1: %s\n",((Food*)(f->data))->barcode);
    }
    if(s!=NULL&& animalNumberWithGivenFoodKind_REC(((Food*)(s->data))->barcode,head_animal)!=0)
        printf("\n#2: %s\n",((Food*)(s->data))->barcode);
    if(t!=NULL&& animalNumberWithGivenFoodKind_REC(((Food*)(t->data))->barcode,head_animal)!=0)
        printf("\n#3: %s\n",((Food*)(t->data))->barcode);
    if(animalNumberWithGivenFoodKind_REC(((Food*)(f->data))->barcode,head_animal)== 0)
        printf("\nNo popular food\n");
    return;
 }
/*******************************************/
void findMax(TreeNode* head_food, TreeNode* head_animal,TreeNode** f,TreeNode** s,TreeNode** t){ /*finds the 3 most popular food consumed by the animals*/
    int first=0, second=0, third=0,count;
    if(head_food==NULL){
        return;  
    }
    if(*f==NULL){
        *f=head_food;
        findMax(head_food->left,head_animal,f,s,t);
        findMax(head_food->right,head_animal,f,s,t);
        return;
    }
    if(*s==NULL){
        count=animalNumberWithGivenFoodKind_REC(((Food*)(head_food->data))->barcode, head_animal);
        first=animalNumberWithGivenFoodKind_REC(((Food*)((*f)->data))->barcode, head_animal);
        if(count>=first){
            *s=*f;
            *f=head_food;
        }
        else
            *s=head_food;
        findMax(head_food->left,head_animal,f,s,t);
        findMax(head_food->right,head_animal,f,s,t);
        return;
    } 
    if(*t==NULL){
        count=animalNumberWithGivenFoodKind_REC(((Food*)(head_food->data))->barcode, head_animal);
        first=animalNumberWithGivenFoodKind_REC(((Food*)((*f)->data))->barcode, head_animal);
        second=animalNumberWithGivenFoodKind_REC(((Food*)((*s)->data))->barcode, head_animal);
        if(count>=first){
            *t=*s;
            *s=*f;
            *f=head_food;
        }
        else if(count>=second){
                *t=*s;
                *s=head_food;
            }
            else
                *t=head_food;
        findMax(head_food->left,head_animal,f,s,t);
        findMax(head_food->right,head_animal,f,s,t);
        return;
    }

    count=animalNumberWithGivenFoodKind_REC(((Food*)(head_food->data))->barcode, head_animal);
    first=animalNumberWithGivenFoodKind_REC(((Food*)((*f)->data))->barcode, head_animal);
    second=animalNumberWithGivenFoodKind_REC(((Food*)((*s)->data))->barcode, head_animal);
    third=animalNumberWithGivenFoodKind_REC(((Food*)((*t)->data))->barcode, head_animal);
    if(count>=first){
        *t=*s;
        *s=*f;
        *f=head_food;
    }
    else{
        if(count>=second){
            *t=*s;
            *s=head_food;
        }
        else{
            if(count>=third)
                *t=head_food;
        }
    }
    findMax(head_food->left,head_animal,f,s,t);
    findMax(head_food->right,head_animal,f,s,t);
    return;
 }

/*******************************************/
void deleteFood(char* barcode, TreeNode** head_food){  /*recieves a barcode and goes through all the tree to find the food and delete his struct*/
    *head_food=removeLeaf(*head_food, barcode, &compareFoodBarcode, &freeGluten);
    return;
 }
/*******************************************/
void deleteAllFood(TreeNode* head_food){  /*zeroes all the food tree*/
    freeTree(head_food, &freeGluten);
    printf("\nAll food deleted\n");
 }
/*******************************************/
void getFoodBarcode(char** p){  /*gets food's barcode and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L];
    char c;
    for(;;){
        printf("\nPlease enter food's barcode (20 digits):\n");
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
        if(strlen(temp)!=20){
            printf("\nError getting barcode, try again!!\n");
            continue;
        }
        *p=ALLOC(char, i);
        strcpy(*p,&(temp[0]));
        return;
    }
 }
/*******************************************/
void getFoodManufacturer(char** p){  /*gets manufacturer's name and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char temp[MAX_L];
    char c;
    for(;;){
        printf("\nPlease enter food's manufacturer (10 characters):\n");
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
        if(strlen(temp)<2){
            printf("\nError getting name, try again!!\n");
            continue;
        }
        *p=ALLOC(char, i);
        strcpy(*p, &(temp[0]));
        return;
    }
 }
/*******************************************/
int getFoodStockQuantity(){ /*gets food amount in stock(in bags) and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char c, temp[15];
    for(;;){
    printf("\nPlease enter food's stock quantity(0 - 10,000):\n");
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
    if((atoi(temp)<0)||(atoi(temp)>10000)||temp[0]=='\0')
    {
        printf("\nError getting quantity, try again!!\n");
        continue;
    }
    return atoi(temp);
    }
 }
/*******************************************/
double getFoodBagWeight(){  /*gets bag weight(double) and checks the input's correction*/
    int i; /*variable for general uses in loops and such*/
    char temp[15],c;
    for(;;){
        printf("\nPlease enter food's exact bag weight(0.00Kg - 50.00Kg):\n");
        for(i=0 ;;i++){  /*input check*/
            c=getchar();
            if(c=='\n'){
                temp[i]='\0';
                break;
            }
            if(isdigit(c)||c=='.')
                temp[i]=c;
            else{
                temp[0]='\0';
            }
        }
        if((atof(temp)<0.000)||(atof(temp)>50.000)||temp[0]=='\0'){
            printf("\nError getting bag weight, try again!!\n");
            continue;
        }
        return atof(temp);
    }
 }
/*******************************************/
void getFoodDesignatedAnimals(Designated_Animals* head){ /*this function is in charge of filling the sub linked list of designated animals within the main food's linked list*/
    char option[MAX_L], c; /*for switch case*/
    char str[MAX_L];
    int i, j; /*variables for general uses in loops and such*/
    printf("\nFill this list of desiganted animals:\n");
    for(j=1 ; ;){
        printf("\nChoose an option:\nAdd (1)\nFinish (2)\n");
        for(i=0 ;;i++){  /*input check*/
            c=getchar();
            if(c=='\n'){
                option[i]='\0';
                break;
            }
            if(isdigit(c))
                option[i]=c;
            else{
                option[0]='\0';
                i=0;
                continue;
            }
         }
        if(strlen(option)!=1 || option[0]>'2' || option[0]<'1'){
            printf("\nIllegal choice, try again!\n");
            continue;
         }
        switch(option[0]){
            case '1':
                printf("\nAnimal #%d: ",j);
                j++;
                for(i=0 ;;i++){  /*input check*/
                    
                    c=getchar();
                    if(c=='\n'){
                        str[i]='\0';
                        break;
                    }
                    if(isalpha(c) || c==' ')
                        str[i]=c;
                    else
                        str[0]='\0';
                }
                if(strlen(str)<2){
                    j--;
                    printf("\nError getting type, try again!!\n");
                    break;
                }
                head=ALLOC(Designated_Animals, 1);
                head->name=ALLOC(char, strlen(str)+1);
                strcpy(head->name, str);
                head=head->next;
                break;
            case '2':
                break;
        }
        if(option[0]=='2') break;
    }
    return;
 }
/*******************************************/
int checkIfBarcodeExists(TreeNode* head_food, char* barcode){ /*returns 1 if an identical ID already exists and 0 if not*/
    if (head_food == NULL)
        return 0;
    if(strcmp(((Food*)(head_food->data))->barcode, barcode)==0)
        return 1;

    if (strcmp(((Food*)(head_food->data))->barcode, barcode)<0)
       return checkIfBarcodeExists(head_food->right, barcode);
    return checkIfBarcodeExists(head_food->left, barcode);
 }
/*******************************************/
void freeGluten(void* p){ /*freeing function for Employee_Node type*/
    Food* temp=(Food*)p;
    Designated_Animals* head = temp->designated_animals;
    Designated_Animals* current=head;

    free(temp->barcode);
    free(temp->manufacturer);
    while(current!=NULL){
        head=head->next;
        free(current->name);
        free(current);
        current=head;
    }
    free(temp);
 }
/**********************************************/
int compareFood(void *arg1, void *arg2){
    if(strcmp(((Food*)arg1)->barcode, ((Food*)arg2)->barcode)==0) return 0;
    if(strcmp(((Food*)arg1)->barcode, ((Food*)arg2)->barcode)>0) return 1;
    return -1;
 }
/*****************************************************/
int compareFoodBarcode(void *barcode, void *arg1){
    if(strcmp(((Food*)arg1)->barcode,(char*)barcode)==0) return 1;
    return 0;
 }
/*****************************************************/