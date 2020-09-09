/*header file for Employee.c*/
#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_
#define NAME_S 21
#define ID_ARR 200

#include "Date.h"
#include "GenericTree.h"

#define MAX_L 10000

typedef struct employee{
    char* first_name; /*employee's first name*/
    char* last_name; /*employee's last name*/
    char* ID; /*employee's id*/
    int assigned_animals;  /*amount of animals that are in responsibility of the Employee*/
    int* assigned_animals_id; /*array for each animal's ID*/
    Date work_start;  /*employee's work starting date*/
}Employee;

TreeNode* createEmployeeTree();  /*creates a new employee tree and resets all the structs*/
void addNewEmployee(TreeNode** head_employee);  /*adds a new employee to the tree*/
void deleteEmployee(TreeNode** head_employee);  /*recieves an ID and goes through all the tree to find the employee and delete his struct*/
void deleteAllEmployees(TreeNode* head_employee);  /*zeroes all the employee tree*/
void printAll(TreeNode* p);
void printEmployeeNode(void* p);
void findEmployee(TreeNode* head_employee);
char inputCheckE();
void freeBob(void* temp);
int checkIfIdExistsE(TreeNode* head_employee, char* ID);
int compareEmployee(void *arg1, void *arg2);
int compareEmployeeId(void *ID,void *arg1);
int compareEmployeeAssignedAnimals(void *assigned_animals, void *arg1);

/*******************************************/
void getEmployeeFirstName(char** p);  /*gets first name and checks the input's correction*/
void getEmployeeLastName(char** p);  /*gets last name and checks the input's correction*/
void getEmployeeID(char** p);  /*gets ID and checks the input's correction*/
int getEmployeeAssignedAnimals();  /*gets an input for the amount of the employee's assigned animals and checks the input's correction*/
int getEmployeeAssignedAnimalsID();  /*recieves animal's unique ID for each animal assigned to the employee*/
void getEmployeeWorkStart(Date *p);  /*exact date in which the employee started working at the zoo (dd/mm/yyyy)*/

#endif