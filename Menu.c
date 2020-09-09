#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Menu.h"
#include "Animal.h"
#include "Food.h"
#include "Employee.h"
#include "Date.h"
#include "GenericTree.h"

#define MAX 10
#define MAX_NAME 10000

int i; /*variable for general uses in loops and such*/
char c; /*variable for general uses in input checks and such*/
int checker_animal; /*used to check if the tree has been created*/
int checker_employee; /*used to check if the tree has been created*/
int checker_food; /*used to check if the tree has been created*/

TreeNode* head_employee;
TreeNode* head_animal;
TreeNode* head_food;

void printMenu(){  /*main menu, you can go back to this menu from inner sections*/
    for(;;){
        printf("\n****Welcome to The Zoo system****\n");
        printf("\tEmployees (1)\n");
        printf("\tAnimals (2)\n");
        printf("\tFood (3)\n");
        printf("\tEXIT (4)\n");
        printf("Your choice: ");
        inputCheck();
        printf("\n");
        switch (c){
            case '1':
                printEmployeeMenu();
                break;
            case '2':
                printAnimalMenu();
                break;
            case '3':
                printFoodMenu();
                break;
            case '4':
                deleteAllAnimals(head_animal);
                deleteAllEmployees(head_employee);
                deleteAllFood(head_food);
                printf("\nHave a nice day, bye bye.\n");
                return;
            default:
                printf("\n\nIllegal choice!!!\ntry again\n\n");
                break;
        }
    }
 }
/*****************************************************/
void printEmployeeMenu(){  /*prints the employee menu, the available options and takes action according to the choice*/
    if(checker_employee!=1){
        head_employee=createTree();
        checker_employee=1;
    }
    for(;;){
        printf("\n*Employee section*\n");
        printf("\tAdd a new employee (1)\n");
        printf("\tDelete an employee (2)\n");
        printf("\tDelete all employees (3)\n");
        printf("\tPrint all employees (4)\n");
        printf("\tFind employees (5)\n");
        printf("\tPrevious section.. (6)\n");
        printf("your choice:");
        inputCheck();
        switch (c){
            case '1':
                addNewEmployee(&head_employee);
                break;
            case '2':
                if(head_employee==NULL){
                    printf("\nNo employees\n");
                    break;
                }
                deleteEmployee(&head_employee);
                break;
            case '3':
                printf("\nAre you sure? (y/n):\n");
                inputCheck();
                if(c=='y'){
                    deleteAllEmployees(head_employee);
                    checker_employee=0;
                    return;
                }
                else{
                    if(c=='n')
                        break;    
                    else
                    printf("\n\nIllegal choice\n");    
                }
                    break;
            case '4':
                printAll(head_employee);
                break;
            case '5':
                findEmployee(head_employee);
                break;
            case '6':
                return;
            default:
                printf("\n\nIllegal choice!!!\ntry again\n\n");
        }
    }
 }
/*****************************************************/
void printAnimalMenu(){  /*prints the animal menu, the available options and takes action according to the choice*/   
    TreeNode* temp;
    char a[10];
    int year,num;
    double avrg;
    char* color = NULL;
    char* barcode = NULL;
    int animalID = 0;

    if(checker_animal!=1){
        head_animal=createTree();
        checker_animal=1;
    }
    for (;;){
        printf("\n*Animal section*\n");
        printf("\tAdd a new animal (1)\n");
        printf("\tDelete an animal (2)\n");
        printf("\tDelete all animals (3)\n");
        printf("\tNumber of animals With Given Food Kind (4)\n");
        printf("\tNumber of animals With Given Color (5)\n");
        printf("\tPrint all animals that were born in the same year (6)\n");
        printf("\tPrint the average number of all animals' offsprings (7)\n");
        printf("\tPrevious section.. (8)\n");
        printf("Your choice:");
        inputCheck();
        switch (c){
            case '1':
                addNewAnimal(&head_animal);
                break;
            case '2':
                if(head_animal==NULL){
                    printf("\nNo animals\n");
                    break;
                }
                animalID=getAnimalId();
                deleteAnimal(animalID,&head_animal);
                break;
            case '3':
                printf("\nAre you sure? (y/n):\n");
                inputCheck();
                if(c=='y'){
                    deleteAllAnimals(head_animal);
                    head_animal= createTree();
                }
                else{
                    if(c=='n')
                        break;     
                    else
                        printf("\n\nIllegal choice\n");
                    }
                break;
            case '4':
                getFoodBarcode(&barcode);
                if(head_animal==NULL){
                    printf("\nNo Animals yet\n");
                    break;
                 }
                temp=head_animal;
                printf("\nThe number of animals that eat this type of food is: %d\n ", animalNumberWithGivenFoodKind_REC(barcode, temp));
                free(barcode);
                break;
            case '5':
                getAnimalColor(&color);
                if(head_animal==NULL){
                    printf("\nNo Animals yet\n");
                    break;
                 }
                temp=head_animal;
                printf("\nThe number of animals that has this color is: %d\n ", animalNumberWithGivenColor(color,temp));
                free(color);
                break;
            case '6':
                if(head_animal==NULL){
                    printf("\nNo Animals yet\n");
                    break;
                 }
                printf("\nplease enter a Year(yyyy): ");
                for(i=0 ;;i++){ 
                    c=getchar();
                    if(c=='\n'){
                        a[i]='\0';
                        break;
                    }
                    if(isdigit(c))
                        a[i]=c;
                    else{
                        a[0]='\0';
                    }
                }
                year=atoi(a);
                if((year<=1900)||(year>2018)||a[0]=='\0')
                    printf("\nError getting year, try again!!\n");
                else{
                    temp=head_animal;
                    printAnimalsForGivenBirthYear_REC(&year,temp);
                }
                break;
            case '7':
                avrg=average(head_animal, &num);
                printf("The average number of all animals' offsprings is: %g\n", avrg);
            case '8':
                return;
            default:
                printf("\n\nIllegal choice!!!\ntry again..\n\n");
        }
    }
 }
/*****************************************************/
void printFoodMenu(){  /*prints the food menu, the available options and takes action according to the choice*/
    char* temp;
    if(checker_food!=1){
        head_food=createTree();
        checker_food=1;
    }
    for(;;){
        printf("\n*Food section*\n");
        printf("\tAdd a new food (1)\n");
        printf("\tThree most popular food (2)\n");
        printf("\tDelete a food (3)\n");
        printf("\tDelete ALL food (4)\n");
        printf("\tPrevious section (5)\n");
        printf("Your choice:");
        inputCheck();
        switch (c){
            case '1':
                addNewFood(&head_food);
                break;  
            case '2':
                threePopularFoods(head_food,head_animal);
                break;
            case '3':
                if(head_food==NULL){
                    printf("\nNo food objects\n");
                    break;
                }
                getFoodBarcode(&temp);
                deleteFood(temp,&head_food);
                free(temp);
                break;
            case '4':
                printf("\nAre you sure? (y/n):\n");
                inputCheck();
                if(c=='y'){
                    deleteAllFood(head_food);
                    head_food= createTree();
                    return;
                }
                else
                    if(c=='n')
                        break;     
                    else
                        printf("\n\nIllegal choice\n");    
                break;
            case '5':
                return;
            default:
                printf("\n\nIllegal choice!!!\ntry again..\n\n");
        }
    }
 }
/*****************************************************/
void inputCheck(){ /*checks input correction*/
    char choice[20];
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
            return;
        }
        else{
            c=choice[0];
            return;
        }
    }
 }
/*****************************************************/