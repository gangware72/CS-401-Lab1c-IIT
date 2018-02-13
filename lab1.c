#include<stdio.h>
#include<string.h>
#include "header.h"

#define MAXCHARACTER 64

int main(int argc, char *argv[]) {
          int menu_selection;
          struct database d = createDatabase(argv);
          if (d.database_counter==0) {
              menu_selection = 89;
              printf("File not found...");
          } else {
              menu_selection = menuSelection();
          }

                  do
                  {

                    switch (menu_selection)
                    {
                            case 1:
                              printDatabase(d);
                              break;
                            case 2:
                              SearchAndDisplaySingleEmployee(2, d);
                              break;
                            case 3:
                              SearchAndDisplaySingleEmployee(3, d);
                              break;
                            case 4:
                              addEmployee(&d);
                              break;
                    }
                    if (menu_selection ==5 || menu_selection ==89)
                        break;
                    menu_selection = menuSelection();

                  } while (menu_selection != 5);

                  if (menu_selection !=89)
                      writeToFile(openFileWrite(),d);



                  goodbyeMessage();

        }
