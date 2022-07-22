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
//  DATE:        October 28, 2020
//
//  FILE:        database.c
//
//  DESCRIPTION:
//   This file contains the database functions for the menu. 
//
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"record.h"

extern int debugmode;

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   A function that adds a new record.
//
//  Parameters:    record  (struct **) : the address of the address
//                                       that countains record
//                 accnum  (int)       : the account number that will
//                                       be used for the new record
//                 uname    (char[])    : the name that will be used
//                                       for the new record
//                 uaddress (char[])    : the address that will be used
//                                       for the new record
// 
//  Return values:  0 : The function successfully ran.
//
****************************************************************/

int addRecord (struct record ** recordstart, int accnum, char uname[ ], char uaddress[ ])
{
    struct record *temp;
    struct record *cposition;
    struct record *lposition;

    temp = NULL;
    cposition = *recordstart;
    lposition = NULL;

    if (debugmode == 1)
    {
        printf("DEBUG MODE\n");
        printf("----------\n");
        printf("The 'addRecord' function has been called.\n");
        printf("Parameters\n");
        printf("The account number: %d\n", accnum);
        printf("The name of the account: %s\n", uname);
        printf("The address on the account: %s\n", uaddress);
    }
    temp = (struct record *) malloc(sizeof(struct record));
    temp->accountno = accnum;
    strncpy(temp->name, uname, 25);
    strncpy(temp->address, uaddress, 80);

    if (*recordstart == NULL)
    {
        temp->next = NULL;
        *recordstart = temp;
    }
    else
    {
        while((cposition->accountno > accnum) && (cposition->next != NULL))
        {
            lposition = cposition;
            cposition = cposition->next;
        }
        if ((accnum > cposition->accountno) && (cposition == *recordstart))
        {
            temp->next = cposition;
            *recordstart = temp;
        }
        else if ((accnum < cposition->accountno) && (cposition->next == NULL))
        {
            cposition->next = temp;
            temp->next = NULL;
        }
        else if ((accnum == cposition->accountno) && (lposition ==  NULL))
        {
            *recordstart = temp;
            temp->next = cposition;
        }
        else
        {
            lposition->next = temp;
            temp->next = cposition;
        }
    }
    return 0;
}

/*****************************************************************
//
//  Function name: printAllRecord
//
//  DESCRIPTION:   A function that dispays all the records in the database.
//
//  Parameters:    recordstart (struct record *) : contains the address of the record                 
//
//  Return values:  NONE
//
****************************************************************/

void printAllRecords(struct record * recordstart)
{
    int counter;
    int working;
    struct record *cposition;

    cposition = recordstart;
    counter = 0;
    working = 1;

    if (debugmode == 1)
    {
        printf("DEBUG MODE\n");
        printf("----------\n");
        printf("The 'printAllRecords' function has been called.\n");
        printf("Parameters\n");
        printf("NONE\n");
    }

    while (working == 1)
    {
        if (recordstart == NULL)
        {
            working = -1;
        }
        else if (cposition == NULL)
        {
            working = -1;
        }
        else
        {
            printf("Record %d\n", counter + 1);
            printf("--------------------------\n");
            printf("Account Number: %d\n", cposition->accountno);
            printf("Name: %s\n", cposition->name);
            printf("Address: %s\n", cposition->address);
            printf("\n");
            cposition = cposition->next;
            counter++;
        }
    }
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   A function to locate a record by its account number.
//
//  Parameters:    recordstart (struct record *) : contains the address of the record
//                 accnum      (int)             : the account number that will be
//                                                 used to find contents
//                                    
//  Return values:  counter : the number of records with the inputed account number
//
****************************************************************/

int findRecord (struct record * recordstart, int accnum)
{
    int counter;
    int working;
    struct record *cposition;
 
    counter = 0;
    working = 1;
    cposition = recordstart;

    if (debugmode == 1)
    {
        printf("DEBUG MODE\n");
        printf("----------\n");
        printf("The 'findRecord' function has been called.\n");
        printf("Parameters\n");
        printf("The account number: %d\n", accnum);
    }
 
    while (working == 1)
    {
        if (recordstart == NULL)
        {
            working = -1;
        }
        else if (cposition == NULL)
        {
            working = -1;
        }
        else if (accnum == cposition->accountno)
        {
            printf("Record %d with accountno: %d\n", counter + 1, accnum);
            printf("Account Number: %d\n", cposition->accountno);
            printf("Name: %s\n", cposition->name);
            printf("Address: %s\n",cposition->address);
            counter = counter + 1;
            cposition = cposition->next;
        }
        else
        {
            cposition = cposition->next;
        }
    }

    return counter;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   A function to delete a record.
//
//  Parameters:    record (struct **) : contains the address of the address
//                 accnum (int)       : the account number that will be used
//                                      to delete the record                            
//
//  Return values: counter : The number of records that were deleted.
//
****************************************************************/

int deleteRecord(struct record ** startaddress, int accnum)
{
    int counter;
    int working;
    struct record *cposition;
    struct record *lposition;
       
    counter = 0;
    working = 1;
    lposition = *startaddress;
    cposition = *startaddress;

    if (debugmode == 1)
    {
        printf("DEBUG MODE\n");
        printf("----------\n");
        printf("The 'deleteRecord' function has been called.\n");
        printf("Parameters\n");
        printf("The account number: %d\n", accnum);
    }
 
    while (working == 1)
    {
        if (*startaddress == NULL)
        {
            working = -1;
        }
        else if (cposition->accountno == accnum)
        {
            if (cposition == *startaddress)
            {
                *startaddress = cposition->next;
                lposition = *startaddress;
            }
            else if ((cposition->next) == NULL)
            {
                lposition->next = NULL;
            }
            else
            {
                lposition->next = cposition->next;
            }
            free(cposition);
            cposition = lposition;
            counter = counter + 1;
        }
        else if ((accnum != cposition->accountno) && (cposition->next == NULL))
        {
            working = -1;
        }
        else
        {
            lposition = cposition;
            cposition = cposition->next;
        }
    }

    return counter;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   A function that reads data from a file and stores 
//                 it into an array.
//
//  Parameters:    recordstart (struct record **) : contains the address of the address of start      
//                 filename    (char[])           : filename of the file that contains the data           
//
//  Return values: 0 : The function did not successfully run.
//                 1 : The function successfully ran.
//
****************************************************************/

int readfile(struct record ** recordstart, char filename[])
{
    FILE * filein;
    int uaccountno;
    char uname [25];
    char uaddress [80];    
    int cchar;
    int nindex;
    int aindex;
    int running;
    int rest;
    int success;

    filein = fopen(filename, "r");
    nindex = 0;
    aindex = 0;
    running = 1;
    rest = 1;
    success = 2;

    /* If debugmode is on, print the function name and parameters passed */
    if (debugmode == 1)
    {
        printf("\n");
        printf("DEBUG MODE\n");
        printf("----------\n");
        printf("The function passed was the 'readfile'.\n");
        printf("Parameters\n");
        printf("The value of username is %s\n", filename);
        printf("\n");
    }

    if (filein != NULL)
    {
        while (running == 1)
        {
            fscanf(filein, "%d", &uaccountno);

            cchar = fgetc(filein);

            if (cchar == EOF)
            {
                rest = 0;
                running = 0;
            }
            if (rest == 1)
            {
                cchar = fgetc(filein);
            
                while(cchar != '\n' )
                {
                    uname[nindex++] = cchar;
                    cchar = fgetc(filein);
                }
                uname[nindex] = '\0';
            
                nindex = 0;
            
                cchar = fgetc(filein);
                while(cchar != '$')
                {
                    uaddress[aindex++] = cchar;
                    cchar = fgetc(filein);
                }
                uaddress[aindex] = '\0'; 
                aindex = 0;
            
                addRecord(recordstart, uaccountno, uname, uaddress);    
            }
        }

        fclose(filein);
        success = 1;

    }
    else
    {
        success = 0;
    }

    return success;
}

/*****************************************************************
/
//  Function name: writefile
//
//  DESCRIPTION:   A function that reads data from an array and
//                 stores it into a file.
//
//  Parameters:    recordstart (struct record *) : contains the address of the record  
//                 filename    (char[])          : filename of the file that contains the data                 
//
//  Return values: 0 : The function did not successfully run.
//                 1 : The function successfully ran.
//
****************************************************************/

int writefile(struct record * recordstart, char filename[])
{
    FILE * fileout;
    int success;
    struct record *cposition;

    success = -1;
    cposition = recordstart;
    fileout = fopen(filename, "w");

    if (fileout != NULL)
    {
        while(cposition != NULL)        
        {
            fprintf(fileout, "%d\n", cposition->accountno);
            fprintf(fileout, "%s\n", cposition->name);
            fprintf(fileout, "%s$\n", cposition->address);
            cposition = cposition->next;
        }

        fclose(fileout);
        success = 1;

    }
    else
    {
         success = 0;
    }

    return success;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Releases all allocated spaces in the heap memory
//
//  Parameters:    startaddress (struct record **) : contains the address of the address of start           
//
//  Return values:  NONE
//
****************************************************************/

void cleanup(struct record ** startaddress)
{
    struct record *cposition;

    cposition = *startaddress;

    while(*startaddress != NULL)
    {
        while(cposition->next != NULL)
        {
            cposition = cposition->next;
        }

        free(cposition);

        cposition = *startaddress;

        if (cposition == *startaddress)
        {
            *startaddress = NULL;
        }
    }    
}
