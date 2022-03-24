#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h> /* Remove once actual answers can be gotten */

/*///////////////////
PROGRAM DESCRIPTION 




//////////////////*/


/* Constant Variables */
#define GROUPS_MAX_SIZE 20


/* Structs */


/* Prototypes */

void getQuestionnaireInfoTemp(char* inputFile, int* amountOfStudents, int* amountOfQuestions, int* listOfQuestionTypes, int* listOfOverrulingQuestions,int* maxPersonRoom, int* roomtypes);
void getStudentAnswersTemp(char* inputFile, int** listOfStudents, int amountOfStudents, int amountOfQuestions);

void getQuestionnaireInfo(char* inputFile, int* amountOfStudents, /* Reads from the input file */ 
                    int* amountOfQuestions, int* listOfQuestionTypes, int* listOfOverrulingQuestions,  /* Question related*/
                    int* maxPersonRoom, int* roomtypes    /* Get roomtypes in an array */);
void getStudentAnswers(char* inputFile, int** listOfStudents, int amountOfStudents, int amountOfQuestions);


int** generateGroups(int** listOfStudents, int* listOfOverrulingQuestions);
int* applyOptimization(int** listOfStudents, int** listOfGroups, int* listOfQuestionTypes, int amountOfQuestions);
void createOutput(char* outputFile, int* listOfRoommates);



int getCompatibility(int** listOfStudents, int studentID1, int studentID2, int amountOfQuestion, int* listOfQuestionTypes);


/* Helper functions */
void checkMallocSuccess(void* list);


int main(){
    /* Declaring variables */
    int amountOfGroups, amountOfQuestions, amountOfStudents;
    int** listOfStudents;     /* 2 Dimensional array with all students-ID's followed by their answers */
    int* maxPersonRoom;       /* Max amount of persons in a room */
    int* roomtypes;          /* Array with amount of rooms with different amount of people capacity, spot 0 represents 1 person rooms, 1 represents 2 person rooms etc. */
    int* listOfQuestionTypes; /* List of question types */
    int* listOfOverrulingQuestions;  /* List of questions that are overruling */

    printf("Mark1!");
    getQuestionnaireInfoTemp("input1.txt", &amountOfStudents, /* Reads from the input file */ 
                    &amountOfQuestions, listOfQuestionTypes, listOfOverrulingQuestions,  /* Question related*/
                    maxPersonRoom, roomtypes  /* Get roomtypes in an array */);

    printf("Mark2!");
    srand(time(NULL));  /* For random students answers */
    getStudentAnswersTemp("input2.txt", listOfStudents, amountOfStudents, amountOfQuestions);
    
    //int** listOfGroups = generateGroups(listOfStudents, listOfOverrulingQuestions);       /*Generates associative array to refer to which student-IDs are in groups */

    //int* listOfRoommates = applyOptimization(listOfGroups, listOfStudents, listOfQuestionTypes, amountOfQuestions);   /* The hard part */

    //createOutput("output.txt", listOfRoommates); /* Prints the results */

    return EXIT_SUCCESS;
}


void getQuestionnaireInfoTemp(char* inputFile, int* amountOfStudents, int* amountOfQuestions, int* listOfQuestionTypes, int* listOfOverrulingQuestions,int* maxPersonRoom, int* roomtypes){

    *amountOfStudents = 100;
    *amountOfQuestions = 5;
    printf("Mark3!");
    listOfQuestionTypes = (int*)malloc(*amountOfQuestions*sizeof(int));
    checkMallocSuccess(listOfQuestionTypes);



    listOfOverrulingQuestions = (int*)malloc(*amountOfQuestions*sizeof(int));
    checkMallocSuccess(listOfQuestionTypes);
    int i;      /* Fill up with dummy values */
    for (i=0; i<*amountOfQuestions; i++){
        listOfQuestionTypes[i]=1;
        listOfOverrulingQuestions[i]=1;
    }
    /* Create room list */
    *maxPersonRoom=2;
    roomtypes = (int*)malloc(*maxPersonRoom*sizeof(int));

    roomtypes[1]=*amountOfStudents/2;    /* Only 2-person rooms */
}

void getQuestionnaireInfo(char* inputFile, int* amountOfStudents, int* amountOfQuestions, int* listOfQuestionTypes, int* listOfOverrulingQuestions, int* maxPersonRoom, int* roomtypes){
    int i;
    FILE *fp = fopen(inputFile, "r");   /*Open file in read */

    if (fp != NULL){


        for (i=0;!(feof(fp));i++){       /*Reads file till end of file */
            //match_list = get_match(fp, match_list);
        }

    }

    else {  /*If no file found */
        printf("\n Could not find questionnaire info file.\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp); /*Closes file */
}

void getStudentAnswers(char* inputFile, int** listOfStudents, int amountOfStudents, int amountOfQuestions){
    int i;
    FILE *fp = fopen(inputFile, "r");   /*Open file in read */

    if (fp != NULL){
        for (i=0;!(feof(fp));i++){       /*Reads file till end of file */
            //listOfStudents = get_match(fp, match_list);
        }

    }

    else {  /*If no file found */
        printf("\n Could not find student answers file.\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp); /*Closes file */
}

void getStudentAnswersTemp(char* inputFile, int** listOfStudents, int amountOfStudents, int amountOfQuestions){


    listOfStudents = (int**)malloc(amountOfStudents*sizeof(int*)); /* Malloc for outer list */
    checkMallocSuccess(listOfStudents);

    int i, j;
    for (i=0; i<amountOfStudents;i++){
        listOfStudents[i] = (int*)malloc(amountOfQuestions*sizeof(int)); /* Malloc for inner lists */
        checkMallocSuccess(listOfStudents[i]);
        for (j=0; j<amountOfQuestions;j++){
            listOfStudents[i][j]=(int)rand()%5+1; /* Only with the scale from 1-5 for now */
        }
    }

}


/*  Interpretting data  */


int** generateGroups(int** listOfStudents, int* listOfOverrulingQuestions){

    int** dummyOutput;




    
    return dummyOutput;
}


/* From here optimization begins */

int* applyOptimization(int** listOfStudents, int** listOfGroups, int* listOfQuestionTypes, int amountOfQuestions){
    int* dummyOutput;
    return dummyOutput;    
}


int getCompatibility(int** listOfStudents, int studentID1, int studentID2, int amountOfQuestion, int* listOfQuestionTypes){
    /* There is 1 max 'point' per question. Points measure positive compatibility */
    int compatibility = 0, i;

    for (i=0; i<amountOfQuestion; i++){
        if (listOfQuestionTypes[i]==1){         /* Scale questions*/
            compatibility+= (5-abs(listOfStudents[studentID1][i]-listOfStudents[studentID2][i]))/5;
            /* (Scale length - Difference in student answers)/Scale length */
        }
        else if (listOfQuestionTypes[i]==2){    /* Pick a thingy questions */
            if (listOfStudents[studentID1][i]==listOfStudents[studentID2][i]){
                compatibility++;
            }
        }
        else {
            printf("\n Question %d does not have a valid question type \n", i);
            exit(EXIT_FAILURE);
        }
    }
    compatibility = compatibility/amountOfQuestion;  

    return compatibility;
}


void createOutput(char* outputFile, int* listOfRoommates){


}





/* Helper functions */
void checkMallocSuccess(void* list){
    if (list==NULL){    /*Checks if malloc succeded */
        printf("\n Fail in memory allocation bye.\n");
        exit(EXIT_FAILURE);
    }
} 
