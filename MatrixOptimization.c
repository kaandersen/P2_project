#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*///////////////////
PROGRAM DESCRIPTION 




//////////////////*/


/* Constant Variables */
#define GROUPS_MAX_SIZE 20

#define GROUPSMAXSIZE 20

/* Structs */


/* Prototypes */


void getStudentAnswers(char* inputFile, int* amountOfStudents, /* Reads from the input file */ 
                    int* amountOfQuestions, int* listOfQuestionTypes, int* listOfOverrulingQuestions,  /* Question related*/
                    int** roomtypes,    /* Get roomtypes in an array */
                    int** listOfStudents);


int** generateGroups(int** listOfStudents, int* listOfOverrulingQuestions);
int* applyOptimization(int** listOfStudents, int** listOfGroups, int* listOfQuestionTypes, int amountOfQuestions);
void createOutput(int* listOfRoommates, char* outputFile);



int getCompatibility(int** listOfStudents, int studentID1, int studentID2);


int main(){
    /* Declaring variables */
    int amountOfGroups, amountOfQuestions, amountOfStudents;
    int** listOfStudents;     /* 2 Dimensional array with all students-ID's followed by their answers */
    int** roomtypes;          /* 2 Dimensional array with amount of rooms with different amount of people capacity */
    int* listOfQuestionTypes; /* List of question types */
    int* listOfOverrulingQuestions;  /* List of questions that are overruling */



    getStudentAnswers("input.txt", &amountOfStudents, /* Reads from the input file */ 
                    &amountOfQuestions, listOfQuestionTypes, listOfOverrulingQuestions,  /* Question related*/
                    roomtypes,  /* Get roomtypes in an array */
                    listOfStudents);

    int** listOfGroups = generateGroups(listOfStudents, listOfOverrulingQuestions);       /*Generates associative array to refer to which student-IDs are in groups */

    int* listOfRoommates = applyOptimization(listOfGroups, listOfStudents, listOfQuestionTypes, amountOfQuestions);   /* The hard part */

    createOutput(listOfRoommates, "output.txt"); /* Prints the results */

    return EXIT_SUCCESS;
}


void getStudentAnswers(char* inputFile, int* amountOfStudents, int* amountOfQuestions, int* listOfQuestionTypes, int* listOfOverrulingQuestions, int** roomtypes, int** listOfStudents){
    
    
}


int** generateGroups(int** listOfStudents, int* listOfOverrulingQuestions){

    int** dummyOutput;
    return dummyOutput;
}


/* From here optimization begins */

int* applyOptimization(int** listOfStudents, int** listOfGroups, int* listOfQuestionTypes, int amountOfQuestions){
    int* dummyOutput;
    return dummyOutput;    
}


int getCompatibility(int** listOfStudents, int studentID1, int studentID2){

    return 1;
}


void createOutput(int* listOfRoommates, char* outputFile){


}