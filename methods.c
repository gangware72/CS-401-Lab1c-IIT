#include "header.h"
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>


/*--------------READS--------------------------------------READS---------------------------------------------*/
/*--------------READS--------------------------------------READS---------------------------------------------*/
/*--------------READS--------------------------------------READS---------------------------------------------*/


int readInt() /*reads in ints*/
{
    int userInteger;
    int counter = 0;

    char c;
    while (1)
    {
        int result = scanf("%d", &userInteger);
        if ( result == 1) {

            return userInteger;
          }

        c = getchar();
        if (counter == 0)
            printf("I said enter an integer...\n");
        counter++;
    }




}

char* readString() /*Must be 99 chars or less*/
{
    static char userString[99];
    scanf("%s", userString);

    return userString;
}

float readFloat()
{
    float userFloat;
    scanf("%f", userFloat );
    return userFloat;

}

int menuSelection() /*displays Menu and reads in an int, checks if it si correct*/
{

    displayMenu();
    int selection = readInt();
    if (selection >= 6 && selection < 1)
        printf("\nThe integer needs to be between 1 and 5 please...\n");

    return selection;
}

FILE* openFileRead(char *a[])
{
    FILE *file_pointer = fopen(a[1], "r"); /*fopen("name of file", w==write, r==read, a== append)*/
    if (file_pointer)
        return file_pointer;
    return 0;

}

FILE* openFileWrite()
{
    FILE *file_pointer = fopen("small.txt", "w");
    return file_pointer;
}

void readFileToDatabase(FILE* file_pointer, struct database* d)
{
    if (file_pointer == NULL)
        return;
    int sixDigitId, salary;
    char firstName[100], lastName[100];

    while(fscanf(file_pointer,"%d %s %s %d", &sixDigitId, firstName, lastName, &salary)>1)
    {
        struct employee e;
        e.ID = sixDigitId;
        strcpy(e.first_name, firstName);
        strcpy(e.last_name, lastName);
        e.salary = salary;

        d->E[d->database_counter] = e;
        d->database_counter = d->database_counter + 1;

    }
    fclose(file_pointer);
}

/*--------------CREATION & MODIFICATION-------------------------------CREATION & MODIFICATION-----------------------------------*/
/*--------------CREATION & MODIFICATION-------------------------------CREATION & MODIFICATION-----------------------------------*/
/*--------------CREATION & MODIFICATION-------------------------------CREATION & MODIFICATION-----------------------------------*/

struct employee createEmployee()
{
        char check;
        struct employee e;
        do {
            check = 't';
            printf("Please enter the employee ID:\n");
            e.ID = readInt();
            printf("Please enter the employee LAST NAME:\n");
            strcpy(e.last_name, readString());
            printf("Please enter the employee FIRST NAME:\n");
            strcpy(e.first_name, readString());
            printf("Please enter the employee SALARY\n");
            e.salary = readInt();

        } while (check == 'f');


        return e;
}

void addEmployee(struct database* d)
{
        d->E[d->database_counter] = createEmployee();
        d-> database_counter = d->database_counter + 1;
        printf("%d\n", d->database_counter);
}

struct database createDatabase(char *a[])
{
        struct database d;
        d.database_counter = 0;
        readFileToDatabase(openFileRead(a), &d);

        return d;

}

int writeToFile(FILE *fp, struct database d)
{
    int i;
    for (i = 0; i < d.database_counter; i++)
    {
        fprintf(fp,"%d",d.E[i].ID);
        fputs(" ", fp);
        fputs(d.E[i].first_name, fp);
        fputs(" ", fp);
        fputs(d.E[i].last_name, fp);
        fputs(" ", fp);
        fprintf(fp, "%d\n",d.E[i].salary);

    }

    return 1;



}

/*---------------SORTING--------------------------------SORTING------------------------SORTING------------------*/
/*---------------SORTING--------------------------------SORTING------------------------SORTING------------------*/
/*---------------SORTING--------------------------------SORTING------------------------SORTING------------------*/

void swap(struct employee *one, struct employee *another)
{
    struct employee temp = *one;
    *one = *another;
    *another = temp;
}

void sortByID(struct database* d)
{
    int i, j;
    int array_size = d->database_counter;
    for (i =0; i < array_size; i++)
        for (j=0; j < array_size-1-i; j++)
            if (d->E[j].ID > d->E[j+1].ID)
                swap(&d->E[j], &d->E[j+1]);
}

void sortByLastName(struct database* d)
{
    int i, j;
    int array_size = d->database_counter;
    for (i=0; i<array_size; i++)
        for (int j=0; j <array_size-1-i; j++)
        {
            int comparison_results = strcmp(d->E[j].last_name, d->E[j+1].last_name);
            if (comparison_results > 0)
                swap(&d->E[j], &d->E[j+1]);
        }
}


/*-----------------SEARCHING----------------------------SEARCHING------------------------SEARCHING-----------------*/
/*-----------------SEARCHING----------------------------SEARCHING------------------------SEARCHING-----------------*/
/*-----------------SEARCHING----------------------------SEARCHING------------------------SEARCHING-----------------*/


/*This method is used with searchByID. If you are searching by ID int is 1, if you are searching by name int is 2,*/
void SearchAndDisplaySingleEmployee(int choice, struct database d)
{
    struct employee e;

    if (choice == 2)
        e = searchByID(d);
    if (choice == 3)
        e = searchByLastName(d);
    if (e.ID != -1)
    {
        printf("\n\n\nSUCCESS!!!!!\n\n\n");
        printf("\n%s   %s    %d    %d\n", e.first_name, e.last_name, e.salary, e.ID);
    }
    else
    {
        printf("\nThe employee you are looking for is not in the database. Sorry...but its really not my fault you know.\n");
    }
}

struct employee searchByID(struct database d) {
    sortByID(&d);
    printf("Please enter an employee ID:  ");
    int employeeID = readInt();
    int low = 0;
    int high = d.database_counter;
    int half = (d.database_counter)/2;
    int comparison_results;

    do
    {
        comparison_results = d.E[half].ID - employeeID;

        if (comparison_results == 0)
        {
            return d.E[half];
        }

        else if (comparison_results > 0)
        {
            high = half-1;

        }

        else
        {
            low = half+1;
        }

        half = (low+high)/2;

    } while (low <= high);

    return createNullEmployee();
}

struct employee searchByLastName(struct database d)
{
    sortByLastName(&d);
    char employeeLastName[100];
    printf("Please enter an employee LAST NAME: \n");
    strcpy(employeeLastName, readString());

    int low = 0;
    int high = d.database_counter;
    int half = (d.database_counter)/2;
    int comparison_results;

    do
    {
        comparison_results = strcmp(d.E[half].last_name ,employeeLastName);

        if (comparison_results == 0)
        {
            return d.E[half];
        }

        else if (comparison_results > 0)
        {
            high = half-1;
        }

        else
        {
            low = half+1;
        }

        half = (low + high)/2;

    } while (low <= high);

    return createNullEmployee();
}

struct employee createNullEmployee()
{
    struct employee e;
    char REMOVED[8] = "REMOVED";
    e.ID = -1;
    strcpy(e.last_name, REMOVED);
    strcpy(e.first_name, REMOVED);
    e.salary = -1;
    return e;
}




/*---------------PRINTS-------------------------------PRINTS---------------------------PRINTS------------------*/
/*---------------PRINTS-------------------------------PRINTS---------------------------PRINTS------------------*/
/*---------------PRINTS-------------------------------PRINTS---------------------------PRINTS------------------*/
/*---------------PRINTS-------------------------------PRINTS---------------------------PRINTS------------------*/

void printDatabase(struct database d)
{
    printTableHeaderData();
    printDatabaseLine();
    printEmployeeData(d);
    printDatabaseLine();
    printf("Number of Employees (%d)\n\n", d.database_counter);
}

void printTableHeaderData()
{
    char name[] = "NAME";
    char salary[] = "SALARY";
    char id[] = "ID"; /*All three variables are assigned to allow formatting*/
    printf("\n%20s %36s %18s\n", name, salary, id);
}

void printEmployeeData(struct database d)
{
    int counter; //specifies the current array position to print
    for (counter = 0; counter < d.database_counter; counter++)
        printf("%20s %15s %20d %20d\n", d.E[counter].first_name, d.E[counter].last_name,
               d.E[counter].salary, d.E[counter].ID);
}

void printDatabaseLine()
{
    printf("_______________________________________________________________________________________________________________________\n");
}

void goodbyeMessage()
{
    printf("\nThanks for using me. If you were on the fence; this program is definitely A work.\n And not, like, middle of the road 95 percent A work. More like 97 to 100.\n Just sayyyyyyyyyyyyin....\n\n\n\n");
}

void displayMenu()
{
    printf("\nEmployee DB Menu:\n");
    printf("--------------------------------------\n");
    printf("(1) Print the Database\n");
    printf("(2) Lookup by ID\n");
    printf("(3) Lookup by Last Name\n");
    printf("(4) Add an Employee\n");
    printf("(5) Quit\n");
    printf("--------------------------------------\n");
    printf("\nEnter your choice:  ");
}
