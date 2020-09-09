/*Header file for Food.c*/
#ifndef FOOD_H_
#define FOOD_H_

#define MAX_L 10000
#include "Animal.h"
#include "GenericTree.h"


typedef struct designated_animals{ /*struct used as a sub linked list within the food tree*/
    char* name;
    struct designated_animals* next;
}Designated_Animals;

typedef struct food{
    char* barcode; /*food's barcode*/
    char* manufacturer; /*food's manufacturer*/
    Designated_Animals* designated_animals;  /*list of animals that can eat that type of food*/
    int stock_quantity;  /*how many bags of that food are in stock*/
    double bag_weight;  /*weight of the bag in KG*/
}Food;

TreeNode* createFoodTree();  /*creates a new food tree and resets all the structs*/
void addNewFood(TreeNode** head_food);  /*adds a new food to the tree*/
void threePopularFoods(TreeNode* head_food, TreeNode* head_animal);  /*prints the 3 most popular food consumed by the animals*/
void deleteFood(char* barcode, TreeNode** head_food);  /*recieves a barcode and goes through all the tree to find the food and delete his struct*/
void deleteAllFood(TreeNode* head_food);  /*zeroes all the food tree*/
void findMax(TreeNode* head_food, TreeNode* head_animal,TreeNode** f,TreeNode** s,TreeNode** t); /*finds the 3 most popular food consumed by the animals*/
int checkIfBarcodeExists(TreeNode* head_food, char* barcode); /*returns 1 if an identical ID already exists and 0 if not*/
void freeGluten(void* p);
int compareFood(void *arg1, void *arg2);
int compareFoodBarcode(void *barcode, void *arg1);
/*******************************************/
void getFoodBarcode(char** p);  /*gets food barcode and checks the input's correction*/
void getFoodManufacturer(char** p);  /*gets name of food's manufacturer and checks the input's correction*/
void getFoodDesignatedAnimals(Designated_Animals* head); /*this function is in charge of filling the sub linked list of designated animals within the main food's linked list*/
int getFoodStockQuantity();  /*gets an input for the amount of food's bags in stock and checks the input's correction*/
double getFoodBagWeight();  /*gets food's bag weight and checks the input's correction*/
/*******************************************/



#endif