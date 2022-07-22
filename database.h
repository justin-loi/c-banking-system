

/*****************************************************************
//  NAME:        Justin Loi
//
//  HOMEWORK:    Projet 1
// 
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        October 26, 2020 
//
//  FILE:        database.h
//
//  DESCRIPTION:
//   This is the file contains the prototypes of the database
//   functions for the 'Project1' homework.
//
****************************************************************/

int addRecord(struct record **, int, char [ ], char [ ]); /* Creates a new record and uses the parameters for the components */
void printAllRecords(struct record *); /* Prints all the records */
int findRecord(struct record *, int); /* Finds a record by the record number */
int deleteRecord(struct record **, int); /* Deletes a record by the record number */
int readfile(struct record **, char []); /* Populates an array from a file */
int writefile(struct record *, char []); /* Populates a file from an array */
void cleanup(struct record **); /* Releases all of the spaces in the heap */