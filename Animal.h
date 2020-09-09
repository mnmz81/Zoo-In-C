/*header file for Animal.c*/
#ifndef ANIMAL_H_
#define ANIMAL_H_
#include "Date.h"
#include "GenericTree.h"
#define OFFSPRING 1000
#define MAX_L 10000

typedef struct animal{
    char* type;  /*type of animal*/
    char* color;  /*color of animal*/
    char* name;
    int id;  /*unique number of 5 digits*/
    Date birthdate;  /*dd/mm/yyyy)*/
    char* origin;  /*animal's place of birth*/
    int health;  /*health condition(1-100)*/
    int offspring;  /*number of animal's offsprings*/
    int offspring_id[OFFSPRING]; 
    char* food_type;  /*20 digit number of food's barcode*/
    int mpd;  /*meals per day*/
 }Animal;

/**********************************************/
int compareAnimal(void *arg1, void *arg2);
void addNewAnimal(TreeNode** head_animal);  /*recieves all the needed parameters in order to add a new animal to the tree*/
int animalNumberWithGivenFoodKind_REC(char* bar,TreeNode* p); /*recieves a barcode and recursively returns the amount of animals that consumes that food*/
int animalNumberWithGivenColor(char* color, TreeNode* p);  /*recieves a color and return how many animals have that color*/
void deleteAnimal(int animalId, TreeNode** head_animal);  /*recieves an ID and goes through all the tree to find the animal and delete his struct*/
void deleteAllAnimals(TreeNode* head_animal);  /*zeroes all the animal tree*/
void printAnimalsForGivenBirthYear_REC(int* year, TreeNode* p); /*with given birth year, this function will recursively print all the animals that were born in that year*/
double average(TreeNode* p,int* num); /*calculates the average number of animals' offsprings*/
void printAnimalNode(void* t); /*gets a specific node and prints it's contents*/
int checkIfIdExistsA(TreeNode* head_animal, int ID); /*returns 1 if an identical ID already exists and 0 if not*/
int compareAnimalId(void *id,void *arg1);
int getOffspring(void *arg1);
void freeWilly(void* p);
int compareAnimalFood(void *bar,void *arg1);
int compareAnimalColor(void *color,void *arg1);
int compareAnimalYear(void *year,void *arg1);
/**********************************************/
void getAnimalType(char** p); /*gets animal's type and checks the input's correction*/
void getAnimalColor(char** p); /*gets animal's color and checks the input's correction*/
void getAnimalName(char** p); /*gets animal's name and checks the input's correction*/
void getAnimalOrigin(char** p); /*gets animal's origin and checks the input's correction */
int getAnimalId(); /*gets animal's ID and checks the input's correction*/
void getAnimalBirthday(Date* p); /*gets animal's birth date and checks the input's correction*/
int getAnimalHealth(); /*gets animal's health condition and checks the input's correction*/
int getAnimalOffspring(); /*gets animal's amount of offsprings and checks the input's correction*/
void getAnimalFoodType(char** p);  /*gets animal's suitable food type and checks the input's correction*/
int getAnimalMpd();  /*gets animal's amount of meals per day and checks the input's correction*/
int getAnimalOffspringId(); /*gets animal's offspring ID and checks the input's correction*/
/**********************************************/
#endif