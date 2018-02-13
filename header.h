#include <stdio.h>
#include <math.h>
#include<string.h>


#define MAXCHARACTER 64

/*-------------------------STRUCTS---------------------------------*/

struct employee {
  int ID;
  char first_name[MAXCHARACTER];
  char last_name[MAXCHARACTER];
  int salary;
};

struct database {
  struct employee E[1024];
  int database_counter;
  int *location_pointer;
};

/*-------------------------READS---------------------------------*/


int readInt(); /*Asks the user for an integer and reads it in*/
char * readString(); /*Asks the user for a string and reads it in*/
float readFloat();
int menuSelection();
FILE* openFileRead(char *a[]);
FILE* openFileWrite();
void readFileToDatabase(FILE* file_pointer, struct database* dgc);


/*-------------------------CREATION & MODIFICATION---------------------------------*/


struct employee createEmployee(); /*creates an employee */
void addEmployee(struct database* d); /* Adds an employee by reading input from user and prompting output. Returns 1 if success.*/
struct database createDatabase(char *a[]);
int writeToFile(FILE *fp, struct database d);

/*-------------------------SORTING---------------------------------*/

void swap(struct employee *one, struct employee *another);
void sortByID(struct database* d);
void sortByLastName(struct database* d);


/*-------------------------SEARCHING---------------------------------*/

void SearchAndDisplaySingleEmployee(int choice, struct database d);
struct employee searchByID(struct database d);
struct employee searchByLastName(struct database d);
struct employee createNullEmployee();

/*-------------------------PRINTS---------------------------------*/
void printDatabase(struct database d);
void printTableHeaderData();
void printEmployeeData(struct database d);
void printDatabaseLine();
void goodbyeMessage();
void displayMenu();
