/*****************************************************************
//
//  NAME:        Justin Loi
//
//  HOMEWORK:    Project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        October 30, 2020
//
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   This file serves as the userinterface for the banking program.
//
****************************************************************/

/* Importing Function Prototypes from other files */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "record.h"
#include "database.h"

/* Function Prototypes in 'user_interface.c'*/
int menu();
void getaddress (char [], int);
void getname(char [], int);

/* Global Variables*/
int debugmode;

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   A userinterface function
//                 This function utilizes the functions, menu, get address
//                 and getname. Also, it uses database.c, to make an interactive
//                 banking system.
//
//  Parameters:    argc    (int)  : contains the number of arguments
//                                  passed into the program
//                 *argv[] (char) : the listing of all arguments
//
//  Return values: 0 : The program has successfully run. 
//
****************************************************************/

int main(int argc, char *argv[])
{
    /* Variables */
    struct record * start = NULL; /* Required */
    char project [] = "./project";
    char debug [] = "debug";  
    int debugcheckerhw3;
    int debugcheckerdebug;
    int optionchoice;
    int running;
    char userinput [12] = {'0', '0', '0','0','0','0','0','0','0','0','0','0'};
    int wrongcounter;
    int counter;
    int valid;
    int reuserinput;
    int charchecker;
    int useraccnum;
    char username [25];
    char useraddress [80];
    char trash [256];
    int results;

    /* Assigning variables a placeholder value */
    useraccnum = 0;
    debugmode = 0;
    optionchoice = 0;
    running = 0;
    wrongcounter = 0;
    counter = 0;
    results = 0;

    /* Case 1: argc = 1 && argv[0] = "./homework" */       
    if (argc == 1)
    {
        debugmode = 0;
        running = 1;
        printf("DEBUG MODE IS OFF\n");
    }
    /* Case 2: argc = 2 && argv[0] = "./homework3" && argv[1] = debug */ 
    else if (argc == 2 && strlen(argv[1]) == 5)
    {
        debugcheckerhw3 = strncmp(project, argv[0], strlen(argv[0])); /* Checks if argv[0] = "./homework3" */
        debugcheckerdebug = strncmp(debug, argv[1], strlen(argv[1])); /* Checks if argv[1] = "debug" */
        
        /* If the two debugcheckers are good, represented by 0 */
        if (debugcheckerhw3 == 0 && debugcheckerdebug == 0) 
        {
            debugmode = 1;
            running = 1;
            printf("DEBUG MODE IS ON\n");
        }
        else
        {
            printf("ERROR: INVALID INPUT\n");
        }   

    }
    /* Everything else: Prints an error message  */ 
    else
    {
        printf("ERROR: INVALID INPUT\n");
    }   

    results = readfile(&start, "Saved");
    if (results == 1)
    {
        printf("The file 'Saved' has successfully been read.\n");
    }
    else
    {
        printf("There is not a file to receive.\n");
    }
    /* Displaying a menu, choosing an option, getting additional info, and displaying results */
    while (running == 1)
    {  
        /* Displaying the menu and getting the option choice */
        optionchoice = menu();

        /* If the option is add */
        if (optionchoice == 1) 
        {
            /* Obtaining the additional information */
            while (valid != 1)
            {
                printf("Enter a record number\n");
                printf("NOTE: It must be a positive number and only numbers will be accepted\n");
                scanf("%s", userinput);
                for (counter = 0; counter < 12 ;counter++)
                {
                    charchecker = isalpha(userinput[counter]);
                    if (charchecker != 0)
                    {
                        wrongcounter++;
                    }
                }

                if (wrongcounter == 0)
                {
                    reuserinput = atoi(userinput);               
                    if (reuserinput > 0)
                    {
                        useraccnum = reuserinput;
                        valid = 1;
                    }
                }
                else
                {
                    wrongcounter = 0;
                    printf("You have inputed a invalid account number, try again\n");
                }
            }

            fgets(trash, 30, stdin);

            printf("Enter a name for the record\n");
            printf("This will automatically close out when you reach 25 characters or you may press 'Enter'\n");
            printf("NOTE: Tab and Endline will be treated as a space character'\n");            
            getname(username, 25);            

            printf("Enter a multiline record address\n");
            printf("This will automatically close out when you reach 79 characters\n");
            printf("You may close out early by entering '$' then 'Enter'\n");
            getaddress(useraddress, 80);

            /* Clears any extra characters if stdin goes beyond 80 characters*/
            fgets(trash, 60, stdin);

            /* Running the 'addRecord' function with the inputed parameters*/
            addRecord (&start, useraccnum, username, useraddress);
            valid = 0;
        }
        /* If the option is printall */
        else if (optionchoice == 2)
        {
            /* Prints all of the stored records */
            printAllRecords(start);   
            if (start == NULL)
            {
                printf("This list is empty.\n");
            }
        }
        /* If the option is find */
        else if (optionchoice == 3)
        {
            /* Obtaining the additional information */
            while (valid != 1)
            {
                printf("Enter a record number\n");
                printf("NOTE: It must be a positive number and only numbers will be accepted\n");
                scanf("%s", userinput);
                for (counter = 0; counter < 12 ;counter++)
                {
                    charchecker = isalpha(userinput[counter]);
                    if (charchecker != 0)
                    {
                        wrongcounter++;
                    }
                }

                if (wrongcounter == 0)
                {
                    reuserinput = atoi(userinput);               
                    if (reuserinput > 0)
                    {
                        useraccnum = reuserinput;
                        valid = 1;
                    }
                }
                else
                {
                    printf("You have inputed a invalid account number, try again\n");
                    wrongcounter = 0;
                }
            }

            /* Running the 'findRecord' function with the inputed parameters*/
            results = findRecord (start, useraccnum);
            if (results > 0)
            {
                printf("The following %d record(s) with the inputed account number has been found.\n", results);
            }
            else
            {
                printf("No record with the inputed account number is found.\n");
            }
            valid = 0;
        }
        /* If the option is delete*/
        else if (optionchoice == 4)
        {
            /* Obtaining the additional information */
            while (valid != 1)
            {   
                printf("Enter a record number\n");
                printf("NOTE: It must be a positive number and only numbers will be accepted\n");
                scanf("%s", userinput);
                for (counter = 0; counter < 12 ;counter++)
                {   
                    charchecker = isalpha(userinput[counter]);
                    if (charchecker != 0)
                    {   
                        wrongcounter++;
                    }
                }
                
                if (wrongcounter == 0)
                {   
                    reuserinput = atoi(userinput);
                    if (reuserinput > 0)
                    {   
                        useraccnum = reuserinput;
                        valid = 1;
                    }
                }
                else
                {   
                    wrongcounter = 0;
                    printf("You have inputed a invalid account number, try again.\n");
                }
            }

            /* Running the 'deleteRecord' function with the inputed parameters*/
            results = deleteRecord(&start, useraccnum);
            if (results > 0)
            {
                printf("%d record(s) has been deleted.\n", results); 
            }
            else
            { 
                printf("No record with the inputed account number is found.\n");
            }
            valid = 0;
        }
        /* If the option is quit */
        else 
        {
            /* Writefile and Cleanup */
            results = writefile(start, "Saved");
            if (results == 1)
            {
                printf("The file 'Saved' with the data has successfully been created.\n");
            }
            else
            {
                printf("The file 'Saved' has not been created.\n");
            }
            cleanup(&start);
            if (start == NULL)
            {
                printf("All of the records have been cleared from the heap.\n");
            }
            else
            {
                printf("Cleanup failed\n");
            }
            /* Breaks the while look, ending the program */
            running = 0;
        }        

    }

    return 0;

}

/*****************************************************************
//
//  Function name: menu
//
//  DESCRIPTION:   A userinterface function
//                 This function prints out a menu, which the user
//                 inputs an option. This function returns a 
//                 corresponding number to represent the option choice.
//
//  Parameters:    NONE
//
//  Return values:  optionchoice : the number that corresponds
//                                 with each option
//
****************************************************************/

int menu()
{
    char * strcomp;
    char optioninput [30];
    int optionnumber;
    int valid;
    char foptions [5] = {'a', 'p', 'f', 'd', 'q'};    

    optionnumber = 0;
    valid = 0;

    /* If debugmode is on, print the function name and parameters passed */
    if (debugmode == 1)
    {
        printf("\n");
        printf("DEBUG MODE\n");
        printf("----------\n");
        printf("The function passed was the 'menu'.\n");
        printf("Parameters\n");
        printf("NONE\n");
        printf("\n");
    }
 
    /* Introductory Message */
    printf("Welcome to the Bank Database.\n"); 
    printf("\n");
    
    /* Instructions for the user to choose a menu option */
    printf("Instructions\n");
    printf("Enter the option that you would like to use and hit the 'Enter' button\n");
    printf("NOTE: You may type either a partial or the full option name (no more than that) to choose an option\n"); 
    printf("Examples that work: de,   de, de     , delete  \n");
    printf("Examples that do not work: deletebob, dddd, errweq, addddd \n");
    printf("\n");

    /* Do-while loop to get an option */
    do
    {
        /* Displaying menu choices */
        printf("MENU\n");
        printf("<Add>      : Adds a new record in the database \n");
        printf("<Printall> : Prints all the records currently stored in the database\n");
        printf("<Find>     : Find record(s) by a specified account #\n");
        printf("<Delete>   : Delete existing record(s) from the database using the account number as the key\n");
        printf("<Quit>     : Quits the program \n");
        printf("\n");

        /* Userinput choice */
        scanf("%s", optioninput);

        /* Checks if the first character of optioninput is 'a' */
        if (optioninput[0] == foptions[0])
        {
             /* Compares optioninput as a substring of 'add' */
            strcomp = strstr("add", optioninput);

            /* If the rest of the characters is a substring of add, corresponding option is passed and while-loop ends*/
            if (strcomp)
            {
                valid = 1;
                optionnumber = 1;
            }
             /* The rest of the characters do not match add, error message displayed */
             else
             {
                  printf("ERROR: INVALID OPTION NAME\n");
                  printf("Enter a valid option\n");
             }
        }
        /* Checks if the first character of optioninput is 'p' */
        else if (optioninput[0] == foptions[1])
        {
             /* Compares optioninput as a substring of 'printall' */
             strcomp = strstr("printall", optioninput);
             
             /* If the rest of the characters is a substring of printall, corresponding option is passed and while-loop ends*/             
             if (strcomp)
             {
                 valid = 1;
                 optionnumber = 2;
             }
             /* The rest of the characters do not match printall, error message displayed */
             else
             {
                  printf("ERROR: INVALID OPTION NAME\n");
                  printf("Enter a valid option\n");
             }
        }
        /* Checks if the first character of optioninput is 'f' */
        else if (optioninput[0] == foptions[2])
        {
             /* Compares optioninput as a substring of 'find' */
             strcomp = strstr("find", optioninput);

             /* If the rest of the characters is a substring of find, corresponding option is passed and while-loop ends*/             
             if (strcomp)
             {
                 valid = 1;
                 optionnumber = 3;
             }
             /* The rest of the characters do not match find, error message displayed */
             else
             {
                  printf("ERROR: INVALID OPTION NAME\n");
                  printf("Enter a valid option\n");
             }
        }
        /* Checks if the first character of optioninput is 'd' */
        else if (optioninput[0] == foptions[3])
        {
             /* Compares optioninput as a substring of 'delete' */
             strcomp = strstr("delete", optioninput);
             
             /* If the rest of the characters is a substring of delete, corresponding option is passed and while-loop ends*/
             if (strcomp)
             {
                 valid = 1;
                 optionnumber = 4;
             }
             /* The rest of the characters do not match delete, error message displayed */
             else 
             {
                  printf("ERROR: INVALID OPTION NAME\n");
                  printf("Enter a valid option\n");
             }
        }
        /* Checks if the first character of optioninput is 'q' */
        else if (optioninput[0] == foptions[4])
        {
             /* Compares optioninput as a substring of 'quit' */
             strcomp = strstr("quit", optioninput);
             
             /* If the rest of the characters is a substring of quit, corresponding option is passed and while-loop ends*/
             if (strcomp)
             {
                 valid = 1;
                 optionnumber = 5;
             }
             /* The rest of the characters do not match quit, error message displayed */
             else 
             {
                  printf("ERROR: INVALID OPTION NAME\n");
                  printf("Enter a valid option\n");
             }
        }
        /* If the first character of the option is invalid, error message displayed */
        else
        {
             printf("ERROR: INVALID OPTION NAME\n");
             printf("Enter a valid option\n");
        }

    } while (valid != 1);     

    /* Returns the optionnumber corresponding to each menu choice*/
    return optionnumber;
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   A userinterface function
//                 This function gets a multiline input and stores
//                 it into a char array.
//
//  Parameters:    addressname (char[]) : contains the user's multiline input
//                 count       (int)    : the maximum space in the char array
//
//  Return values: NONE
//
****************************************************************/
 
void getaddress(char addressname[], int count)
{
   char currentchar;
   int index = 0;
 
    /* If debugmode is on, print the function name and parameters passed */
    if (debugmode == 1)
    {
        printf("\n");
        printf("DEBUG MODE\n");
        printf("----------\n");
        printf("The function passed was the 'getaddress'.\n");
        printf("Parameters\n");
        printf("The value of addressname is %s\n", addressname);
        printf("The value of count is %d\n", count);
        printf("\n");
    }

   /* Loops through the input and puts c in the chararray until count - 1 */ 
   while(((currentchar = getchar()) != '$') && index <= (count - 1) )
   {
       addressname[index++] = currentchar;
   }

   /* Puts '\0' at the last position */
   addressname[index] = '\0';

}

/*****************************************************************
//
//  Function name: getname
//
//  DESCRIPTION:   A userinterface function
//                 This function gets an input and stores
//                 it into a char array. It does not take tab or 
//                 end line characters.
//
//  Parameters:    username (char[]) : contains the user's input
//                 count    (int)    : the maximum space in the char array
//
//  Return values: NONE
//
****************************************************************/

void getname(char username[], int count)
{
   char currentchar;
   int index = 0;

    /* If debugmode is on, print the function name and parameters passed */
    if (debugmode == 1)
    {
        printf("\n");
        printf("DEBUG MODE\n");
        printf("----------\n");
        printf("The function passed was the 'getname'.\n");
        printf("Parameters\n");
        printf("The value of username is %s\n", username);
        printf("The value of count is %d\n", count);
        printf("\n");
    }

   /* Loops through the input and puts c in the chararray until count - 1 */
   while(((currentchar = getchar()) != '\n') && index <= (count - 1) )
   {
       if (currentchar == '\t' || currentchar == '\n')
       {
           username[index++] = ' ';
       }
       else
       {
           username[index++] = currentchar;
       }
   }

   /* Puts '\0' at the last position */
   username[index] = '\0';

}
