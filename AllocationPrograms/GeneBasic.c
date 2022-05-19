/* Library header inclusions */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>        /* Bolean values */



/*///////////////////
PROGRAM DESCRIPTION 

This program reads 4 csv files as an input and enters a 3 step process.

Firstly it divides students into groups based on overruling questionsd and group-reduction.

Secondly it takes each of the generated groups, and starts filling them into available rooms. Then it applies the gene algorithm.
The gene algorithm makes mutations and picks the best mutation over many iterations, slowly improving the results. 



//////////////////*/


/* Constant Variables */
#define GROUPS_MAX_SIZE 50
#define GROUP_REDUCTION_ON 0 /* 1 for true, 0 for false */
#define FILL_IN_STUDENTS 1   /* 1 for true, 0 for false */

/* Buffer numbers */
#define MAX_ROOMS_SIZE 50        /* The highest possible roomsize */

/* Exclusive to gene algorithm */
#define AMOUNT_OF_ITERATIONS 1000    /* How many times the algorithm should run */
#define AMOUNT_OF_MUTATIONS 250   /* How many new options should be made every time */
#define PRINT_GENE 0            /* If should print gene progress, ONLY IF NO OVERRULING QUESTIONS */


/* Structs */

struct group {       
    int*           groupcode;       /* Digit code of what questions this group represents */
    int     amountOfStudents;
    int*          studentIDs;       /* List of student ID's */
    struct group* nextGroup;        /* Pointer to next group */
    };
typedef struct group group;

/* Prototypes */
/* Get data functions*/
void getQuestionnaireInfoTemp(int* questionnaireID, int* amountOfStudents, /* Reads from the input file */ 
                    int* amountOfQuestions, int** listOfQuestionTypes, int** listOfOverrulingQuestions,  /* Question related*/
                    int* maxPersonRoom, int** roomtypes    /* Get roomtypes in an array */);

void getStudentAnswersTemp(int*** listOfStudents, int amountOfStudents, int amountOfQuestions, int questionnaireID, int* listOfQuestionTypes);

void getQuestionnaireInfo(int* questionnaireID, int* amountOfStudents, /* Reads from the input file */ 
                    int* amountOfQuestions, int** listOfQuestionTypes, int** listOfOverrulingQuestions,  /* Question related*/
                    int* maxPersonRoom, int** roomtypes    /* Get roomtypes in an array */);

void getStudentAnswers(int*** listOfStudents, int amountOfStudents, int amountOfQuestions, int questionnaireID, int* listOfQuestionTypes);

char* getfield(char* line, int num);
int stringToInt(char* string);



/* Make groups functions*/
group* generateGroups(int** listOfStudents, int amountOfStudents, int* listOfOverrulingQuestions, int amountOfQuestions, int* listOfQuestionTypes, int* amountOfGroups);

group* getEmptyGroup(int amountOfStudents);
group* getNewGroup(int studentID, int* studentAnswers, int amountOfStudents, int codeLength, int* overruleQuestions);
void addStudent(int studentID, group* groupPointer);
void reduceGroup(group* currentGroup, group** endGroup);


/* Allocate students functions*/
int*** applyOptimization(int** listOfStudents, group* listOfGroups, int amountOfGrups, int* listOfQuestionTypes, int amountOfQuestions, int maxPersonRoom, int* roomTypes, int** inUseRooms, int* beginningTotalValue, int* listOfIterationValues);


int getCompatibility(int* studentID1Answers, int* studentID2Answers, int amountOfQuestion, int* listOfQuestionTypes);
int getRoomSize(int amountOfGroupstudents, int* roomTypes, int maxPersonRoom);
void fillRoom(int* roomSize, int*** listOfRoommates, int* inUseRooms, int maxPersonRoom, int* amountOfGroupStudentsTracker,  int* listOfGroupStudents);
void findRooms(int** groupRooms, int*** listOfRoommates, int* listOfGroupStudents, int amountOfGroupStudents, int* roomTypes, int maxPersonRoom, int* inUseRooms, int* roomsCounter);
int getRoomCompatibility(int*** listOfRoommates,int** listOfAllStudents, int* groupRoom, int amountOfQuestion, int* listOfQuestionTypes);
void getMutation(int* newValue,int** newMutation, int roomsCounter, int** groupRooms ,int*** listOfRoommates,int** listOfAllStudents, int amountOfQuestion, int* listOfQuestionTypes);
void geneAlgorithm(int roomsCounter, int** groupRooms, int*** listOfRoommates,int** listOfAllStudents, int amountOfQuestion, int* listOfQuestionTypes, int* listOfIterationValues, int counter);
void getRoommates(int*** listOfRoommates, int** listOfAllStudents, int* listOfGroupStudents, int amountOfGroupStudents, int amountOfQuestions, int* listOfQuestionTypes, int* roomTypes, int maxPersonRoom, int* inUseRooms, int* beginningValue, int* listOfIterationValues);

/* Create output */
void createOutput(char* outputFile, char* outputDataFile, char* outputFileGene,int*** listOfRoommates, int* listOfRoomTypes, int maxRooms, int amountOfQuestions,int beginningTotalValue, int* listOfIterationValues);
void storeSatisfaction(int* scoreTracker, int maxScore, int satisfaction);





/* Helper functions */
void checkMallocSuccess(void* list);
void freeValues(int** listOfStudents,int* roomTypes,int* listOfQuestionTypes,int* listOfOverrulingQuestions,int amountOfStudents);

int main(){
    int amountOfGroups, amountOfQuestions, amountOfStudents, questionnaireID;
    int** listOfStudents;     /* 2 Dimensional array with all students-ID's followed by their answers */
    int maxPersonRoom;       /* Max amount of persons in a room */
    int* roomTypes;          /* Array with amount of rooms with different amount of people capacity, spot 0 represents 1 person rooms, 1 represents 2 person rooms etc. */
    int* listOfQuestionTypes; /* List of question types */
    int* listOfOverrulingQuestions;  /* List of questions that are overruling */
    int* inUseRooms;                /* List over how many of each rooms are being used */

    /* Values keeping track of gene algorithm */
    int listOfIterationValues[AMOUNT_OF_ITERATIONS]; /* Used to print results from gene algorithm over time, keeps track of change in overall score, this only works for no overruling questions */
    int beginningTotalValue=0;


   
    /* Get question data */
    getQuestionnaireInfo(&questionnaireID, &amountOfStudents, /* Reads from the input file */ 
                    &amountOfQuestions, &listOfQuestionTypes, &listOfOverrulingQuestions,  /* Question related*/
                    &maxPersonRoom, &roomTypes  /* Get roomtypes in an array */);
    srand(time(NULL));  /* For random students answers */

    /* Get data */
    getStudentAnswers(&listOfStudents, amountOfStudents, amountOfQuestions, questionnaireID, listOfQuestionTypes);
    printf("\nGot answers \n");

    group* listOfGroups = generateGroups(listOfStudents, amountOfStudents, listOfOverrulingQuestions, amountOfQuestions, listOfQuestionTypes, &amountOfGroups);      
     /*Generates dynamic associative array to refer to which student-IDs are in groups */

    printf("\nGot Groups \n");

    int*** listOfRoommates = applyOptimization(listOfStudents, listOfGroups, amountOfGroups, listOfQuestionTypes, amountOfQuestions, maxPersonRoom, roomTypes, &inUseRooms, &beginningTotalValue, listOfIterationValues);   /* The hard part */

    printf("\nSuccessfully created roommate list!!!!\n");

    /* free values       This caused memory issues so removed it */
    //freeValues(listOfStudents, roomTypes, listOfQuestionTypes, listOfOverrulingQuestions, amountOfStudents);
    printf("\n\nSuccessfully Freed values"); 

    /* Print output */  
    createOutput("Admin/output.txt", "Admin/outputData.txt", "AllocationPrograms/outputGene.txt", listOfRoommates, inUseRooms, maxPersonRoom, amountOfQuestions, beginningTotalValue, listOfIterationValues); /* Prints the results */


    printf("\nSuccessfully Finished Program\n");

    return EXIT_SUCCESS;
}   

/* Frees all the lists  This function caused problems so was not included in the final version */
/* It is meant to free values */
void freeValues(int** listOfStudents,int* roomTypes,int* listOfQuestionTypes,int* listOfOverrulingQuestions,int amountOfStudents){
    int i;

    free(roomTypes);
    free(listOfQuestionTypes);        /* Touching this apparently breaks stuff, for somer reason? */
    free(listOfOverrulingQuestions);



    for (i=0;i<amountOfStudents;i++){
        free(listOfStudents[i]);
    }
    free(listOfStudents);
}


/* Temporary version of get questionnaire info, that allows the user to define values in C, rather than reading them from a file 
This function takes inputs from with empty values, and updates them during the function */

/* Inputs meaning: 
questionnaireID: Pointer to an integer finding the ID number of the questionnaire
amountOfStudents: Pointer to an integer with amount of students. Meant to update it from this function
amountOfQuestions: Pointer to an integer with amount of students. Meant to update it from this function

listOfQuestionTypes: Pointer to an array with 'amountOfQuestions' elements. Each element is an integer representing the question type value
listOfOverrulingQuestions: Pointer to an array with 'amountOfQuestions' elements. Each element is a bolean integer showing whether a question is overruling

maxPersonRoom: Pointer to an integer keeping track of what the largest size room is

roomtypes: Pointer to an array with 'MAX_ROOM_SIZE' spots, elements is how many rooms of that roomsize+1. So Roomtypes[0]=1-person rooms. Roomtypes[1]=2-person rooms

*/
void getQuestionnaireInfoTemp(int* questionnaireID, int* amountOfStudents, int* amountOfQuestions, int** listOfQuestionTypes, int** listOfOverrulingQuestions,int* maxPersonRoom, int** roomtypes){
 
    *amountOfStudents = 100;    
    *amountOfQuestions = 5;

    *listOfQuestionTypes = (int*)malloc(*amountOfQuestions*sizeof(int));    /* Make array for question types, 1 means scale, 2 means yes/no, 3 means text*/
    checkMallocSuccess(*listOfQuestionTypes);   /* Check for malloc success, if not end program cause memory issue */


    *listOfOverrulingQuestions = (int*)malloc(*amountOfQuestions*sizeof(int));  /* Make bolean array for overruling question list, 1 means false, 2 means true */
    checkMallocSuccess(*listOfQuestionTypes);
    int i;      /* Fill up with dummy values */
    for (i=0; i<*amountOfQuestions; i++){
        (*listOfQuestionTypes)[i]=1;    /* Set all questions to scale */
        (*listOfOverrulingQuestions)[i]=1;  /* Set no overruling questions */
    }

    /* This deals with amount of rooms*/ 
    *maxPersonRoom=5;        /* Sets largest roomsize*/
    *roomtypes = (int*)malloc(*maxPersonRoom*sizeof(int));
    for (i=0; i<*maxPersonRoom;i++){
        (*roomtypes)[i]=0;                /* Sets a base value for all variables that end up not getting defined */
    }
    (*roomtypes)[1]=30;    /* 30 2-person rooms */
    (*roomtypes)[2]=10;    /* 10 3-person rooms */
    (*roomtypes)[4]=2;    /* 2 5-person rooms */


}


/* This function takes inputs from with empty values, and updates them during the function 
It does this by reading the correct values from CSV files*/

/* Inputs meaning: 
questionnaireID: Pointer to an integer finding the ID number of the questionnaire
amountOfStudents: Pointer to an integer with amount of students. Meant to update it from this function
amountOfQuestions: Pointer to an integer with amount of students. Meant to update it from this function

listOfQuestionTypes: Pointer to an array with 'amountOfQuestions' elements. Each element is an integer representing the question type value
listOfOverrulingQuestions: Pointer to an array with 'amountOfQuestions' elements. Each element is a bolean integer showing whether a question is overruling

maxPersonRoom: Pointer to an integer keeping track of what the largest size room is

roomtypes: Pointer to an array with 'MAX_ROOM_SIZE' spots, elements is how many rooms of that roomsize+1. So Roomtypes[0]=1-person rooms. Roomtypes[1]=2-person rooms

*/
void getQuestionnaireInfo(int* questionnaireID, int* amountOfStudents, int* amountOfQuestions, int** listOfQuestionTypes, int** listOfOverrulingQuestions,int* maxPersonRoom, int** roomtypes){
    int i, j;
    
    char* textBuffer1 = (char*)malloc(50*sizeof(char)); /* Sets a buffer for a string which will be used to store values */


    char* line = (char*)malloc(1024*sizeof(char));  /* Buffer for a line of the CSV file which will be read and stored, one line at a time*/
    /* File questionnaire ID */

    FILE* fp = fopen("EliasStuff/public/QuestionaireData.csv", "r");    /* Opens questionnaireID and amountOfQuestions */

    if (fp!=NULL){  /* Till no more lines in file */
        i=0;
        while (fgets(line, 1024, fp))   /* Get next line from file */
        {
            char* tmp1 = strdup(line);  /*gets a variable ready to intepret csv file */
            char* tmp2 = strdup(line);


            if (i==1){    /* Have to find second iteration cause need get rid of first line which has text, not the values we want */
                *questionnaireID = stringToInt(getfield(tmp1, 1));  /* Finds nr 1 element in csv file (Couting from 1->2->3->4, NOT 0), and converts to int */
                *amountOfQuestions = stringToInt(getfield(tmp2, 2)); /* Finds element nr 2, amount of questions */
            }

            free(tmp1);
            free(tmp2);
            i++;    /* Keeps track of iterations */
        }
    }
    else {  /*If no file found */
        printf("\n Could not find questionnaire directions file.\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp); /*Closes file */


    printf("\nQuestions: %d,  Id: %d  \n", *amountOfQuestions, *questionnaireID);   /* Print progress */

    /* Make space for lists */
    *listOfOverrulingQuestions = (int*)malloc(*amountOfQuestions*sizeof(int));
    *listOfQuestionTypes = (int*)malloc(*amountOfQuestions*sizeof(int));


    /* 
    //////////////////////////////
    //////////////////////////////          QUESTION INFO
    //////////////////////////////
    */

    fp = fopen("EliasStuff/public/Questionaire.csv", "r");  /* Open file with question data */

    if (fp!=NULL){
        i=0;        /* Have to find second iteration cause need get rid of top */
        j=0; /* Counts amount of questions */
        while (fgets(line, 1024, fp))
        {
            char* tmp1 = strdup(line); /*gets a variable ready to intepret csv file */
            char* tmp2 = strdup(line);
            char* tmp3 = strdup(line);



            if (i>0){ /* If not first line */
                if (stringToInt(getfield(tmp1, 1))==*questionnaireID){  /* If correct questionnaire, if questionnaire ID matches the one we're looking for */

                    textBuffer1 = getfield(tmp2,4); /* Gets the 4th element and stores it as a string */
                    if (strcmp(textBuffer1, "SCALE")==0){  /* If string matches, it is a scale question */
                        (*listOfQuestionTypes)[j]=1;
                    }
                    else if (strcmp(textBuffer1, "YES/NO")==0){ /* If string matches, it is a Yes/No question */
                        (*listOfQuestionTypes)[j]=2;
                    }
                    else if (strcmp(textBuffer1, "TEXT")==0){ /* If string matches, it is a Text question */
                        (*listOfQuestionTypes)[j]=3;
                    }
                    else {
                        printf("\nInvalid question type.\n"); /* If string is not recognized  */
                        exit(EXIT_FAILURE);
                    }

                    /* Look for overrlung questions */

                    if (getfield(tmp3, 5)!=NULL){   /* If an input is given we know that it is overruling, since if it is not, it will be blank */
                        (*listOfOverrulingQuestions)[j]=2; /* 2 means overruling */
                    }
                    else{
                        (*listOfOverrulingQuestions)[j]=1;  /* 1 means not overruling */
                    }
                    j++; /* Counts amount of questions so it gets put correctly into arrays */
                }
            }
            free(tmp1);
            free(tmp2);
            free(tmp3);
            i++;
        }
    }
    else {  /*If no file found */
        printf("\n Could not find question info file.\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp); /*Closes file */


    if (j!=*amountOfQuestions){
        printf("\nFail in finding all questions.\n");
        exit(EXIT_FAILURE);
    }


    for (i=0; i<*amountOfQuestions; i++){   /* Prints findings */
        printf("Type: %d    Overruling: %d \n", (*listOfQuestionTypes)[i], (*listOfOverrulingQuestions)[i]);
    }


    /* 
    //////////////////////////////
    //////////////////////////////          ROOM INFO
    //////////////////////////////
    */

    *roomtypes = (int*)malloc(MAX_ROOMS_SIZE*sizeof(int));      /* Max rooms of size 50 */
    
    fp = fopen("EliasStuff/public/StudentInfoQuestionaire.csv", "r"); /* File having room data */

    if (fp!=NULL){
        i=0;        /* Counts till iteration with room we want */
        j=0;        /* Counts amount of rooms */
        while (fgets(line, 1024, fp))
        {
            char* tmp1 = strdup(line); /*gets a variable ready to intepret csv file */
            char* tmp2 = strdup(line);


            if (i==(*questionnaireID)){ /* If time that matches questionnaire, since this file is structured for questionnaire ID to match line */
                *amountOfStudents = stringToInt(getfield(tmp1, 2)); /* Reads amount of students */

                textBuffer1 = getfield(tmp2, 4);    /* Gets amount of rooms as a string, the string looks like >-5-2< for 0 1-person rooms, 5 2-person rooms, and 2 3-person rooms*/
                
                
                printf("\n >%s< \n", textBuffer1);
                if (textBuffer1[0]== '-'){    /* If next character is -, it means there are 0 rooms of that size*/
                    (*roomtypes)[j]=0;     /* Sets amount of rooms at that size to 0 */
                }
                else{
                    sscanf(textBuffer1, " %d - ", &(*roomtypes)[j]);    /* If not empty, it can be read as an integer */

                    /* Then a character is removed till the number is gone, and there is either a '-' or the end of the string '\0' is found */
                    while (textBuffer1[0]!= '-' && textBuffer1[0]!= '\0')
                    {   
                        strcpy(textBuffer1, textBuffer1+1); /* Remove one character*/
                    }

                }

                j++;
                while (textBuffer1[0]== '-')    /* Keeps going while there are more amounts of rooms, which can be seen with '-' */
                {   
                    strcpy(textBuffer1, textBuffer1+1); /* Remove the '-' character*/
                    if (textBuffer1[0]== '-'){    /* If empty set to 0*/
                        (*roomtypes)[j]=0; 
                    }
                    else{
                        sscanf(textBuffer1, " %d - ", &(*roomtypes)[j]); /* If not empty it can read as an integer */
                    
                    /* Then a character is removed till the number is gone, and there is either a '-' or the end of the string '\0' */
                        while (textBuffer1[0]!= '-' && textBuffer1[0]!= '\0')
                        {
                            strcpy(textBuffer1, textBuffer1+1); /* Remove one character*/
                        }
                        }

                    j++;
                }
                *maxPersonRoom=j;   /* The max person room is set to the amount of counted roomk types */
            }
            free(tmp1);
            free(tmp2);
            i++;
        }
    }
    else {  /*If no file found */
        printf("\n Could not find roomsize info file.\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp); /*Closes file */


    printf("MaxSize: %d , students: %d \n", *maxPersonRoom, *amountOfStudents); /* Prints results */
    for (i=0; i<*maxPersonRoom; i++){
        printf("Amount at size %d: %d  \n", i, (*roomtypes)[i]);
    }

    free(textBuffer1);
    free(line);
}


/* This function finds student answers as an empty 2 dimensional list, and updates it during the function 
It does this by reading through the CSV file, and takes all answers that fit the questionnaire*/

/* Inputs meaning: 
listsOfStudents: A pointer to a 2-dimensional array. The first dimension is the individual students, and the second array is their answers.
First array is used with their student ID, second array is their answers as integers. 

amountOfStudents: Integer with amount of students 
amountOfQuestions: Integer with amount of questions
questionnaireID: Integer with questionnaire id

listOfQuestionTypes: List of what type each question is, used to know how to interpret answers

*/
void getStudentAnswers(int*** listOfStudents, int amountOfStudents, int amountOfQuestions, int questionnaireID, int* listOfQuestionTypes){
    int i, j, x;
    
    char* textBuffer1 = (char*)malloc(50*sizeof(char)); /* Text buffer */
    checkMallocSuccess(textBuffer1);
    char* line = (char*)malloc(1024*sizeof(char)); /*Line buffer for reading line from csv file */
    checkMallocSuccess(line);


    (*listOfStudents) = (int**)malloc(amountOfStudents*sizeof(int*));   /* Create 2 dimensional arary with size 'amountOfStudents' X 'amountOfQuestons' */
    checkMallocSuccess((*listOfStudents));
    for (i=0; i<amountOfStudents; i++){
        (*listOfStudents)[i]=(int*)malloc(amountOfQuestions*sizeof(int));
        checkMallocSuccess((*listOfStudents)[i]);
    }


    FILE* fp = fopen("EliasStuff/public/StudentQuestionaire.csv", "r"); /* Opens student answer file */

    if (fp!=NULL){ /* Till end of file */
        i=0;        /* Counts till over first room */
        j=0;        /* Counts amount of students */
        x=0;      /* Counts amount of questions */
        while (fgets(line, 1024, fp))
        {
            char* tmp1 = strdup(line); /*gets a variable ready to intepret csv file */
            char* tmp2 = strdup(line);


            if (i>0){ /* If over first run */

                if (stringToInt(getfield(tmp1, 1))==questionnaireID){   /* If questionnaire in answer, matches questionnaire we are searching for */
                    
                    if (listOfQuestionTypes[x]==1){ /* If scale questions */
                        (*listOfStudents)[j][x]=stringToInt(getfield(tmp2, 2));
                    }

                    else if (listOfQuestionTypes[x]==2){ /* If Yes/No questions */
                        textBuffer1 = getfield(tmp2, 2);
                        if (strcmp(textBuffer1,"True")==0){ /* If string matches 'True', set answer to 1 */
                            (*listOfStudents)[j][x]=1;
                        }
                        else if (strcmp(textBuffer1,"False")==0){/* If string matches 'False', set answer to 0 */
                            (*listOfStudents)[j][x]=0;
                        }

                    }

                    else {  /* Only remainng version is text, which we set to 0, cause we don't interpret it */
                        (*listOfStudents)[j][x]=0; /* If text set to zero */
                    }


                    x++;    /* Go next question */
                    if (x==amountOfQuestions){  /* If all questions for a student has been filled out, go to next student */
                        x=0;    /* Reset question */
                        j++;    /* Go next student */
                    }

                }

            }
            free(tmp1);
            free(tmp2);
            i++;
        }
    }

    /* Randomly fill in remaining student answers */
    if (FILL_IN_STUDENTS==1){
        while (j<amountOfStudents){
            while (x<amountOfQuestions){
                if (listOfQuestionTypes[x]==1){ /* If Scale question question */
                    (*listOfStudents)[j][x]=(int)rand()%5+1; /* Scale from 1-5 */
                }
                else if (listOfQuestionTypes[x]==2){ /* If Yes/No question */
                    (*listOfStudents)[j][x]=(int)rand()%2; /* Only with the scale from 0-1 for yes or no */
                }
                else {  /* If text question , set answer to 0*/
                    (*listOfStudents)[j][x]=0;
                }
                x++; /* Go next question */
            }
            x=0; /* Once through all questions reset amount of questions, and go next student */
            j++;
        }
    }

    


    else {  /*If no file found */
        printf("\n Could not find student answers file.\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp); /*Closes file */


    // for (i=0; i<amountOfStudents; i++){
    //     printf("Student %d \n", i);
    //     for (j=0; j<amountOfQuestions; j++){
    //         printf("Answer %d = %d\n", j, (*listOfStudents)[i][j]);
    //     }
    // }


    /* Free buffer space */
    free(textBuffer1);
    free(line);

}

/* taken from https://stackoverflow.com/questions/12911299/read-csv-file-in-c */
char* getfield(char* line, int num)
{
    char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

int stringToInt(char* string){
    int output;
    sscanf(string, " %d ", &output);
    return output;  /* Convert string to integer*/
}


/* This function allows for manual input of student answers / it will randomize them*/

/* Inputs meaning: 
listsOfStudents: A pointer to a 2-dimensional array. The first dimension is the individual students, and the second array is their answers.
First array is used with their student ID, second array is their answers as integers. 

amountOfStudents: Integer with amount of students 
amountOfQuestions: Integer with amount of questions
questionnaireID: Integer with questionnaire id

listOfQuestionTypes: List of what type each question is, used to know how to interpret answers

*/
void getStudentAnswersTemp(int*** listOfStudents, int amountOfStudents, int amountOfQuestions, int questionnaireID, int* listOfQuestionTypes){
 
    *listOfStudents = (int**)malloc(amountOfStudents*sizeof(int*)); /* Malloc for outer list */
    checkMallocSuccess(*listOfStudents);    /* Array with students amount of spots */

    int i, j;
    for (i=0; i<amountOfStudents;i++){  /* each spot in the student array has a sub-array with length size of amount of questions */
        (*listOfStudents)[i] = (int*)malloc(amountOfQuestions*sizeof(int)); /* Malloc for inner lists */
        checkMallocSuccess((*listOfStudents)[i]);
        for (j=0; j<amountOfQuestions;j++){
            (*listOfStudents)[i][j]=(int)rand()%5+1; /* Only with the scale from 1-5 for now */
        }
    }
}


/* -------------------------
----------------------------
----------------------------
----------------------------

- From here groupings begin -

----------------------------
----------------------------
----------------------------
----------------------------*/

/* This function takes all students there are, and puts them into groups depending on their answers to overruling questions
The output is a group struct, which contains a list of the students in that group */

/* Inputs meaning: 
listsOfStudents: A 2-dimensional array. The first dimension is the individual students, and the second array is their answers.
First array is used with their student ID, second array is their answers as integers. 

amountOfStudents: Integer with amount of students 

listOfOverrulingQuestions: An array with 'amountOfQuestions' elements. Each element is a bolean integer, 2 meaning overruling, 1 meaning not overruling.

amountOfQuestions: Integer with amount of questions

listOfQuestionTypes: An array with 'amountOfQuestions' elements. Each element is an integer that shows what question type a given question is. 1->Scale, 2->Yes/NO, 3->Text

amountOfGroups: Pointer to an integer, that tells how many groups there are
*/

group* generateGroups(int** listOfStudents, int amountOfStudents, int* listOfOverrulingQuestions, int amountOfQuestions, int* listOfQuestionTypes, int* amountOfGroups){

    group* output;      /* Functions as start of the array */
    group* pointer;     /* Currently looking to this group*/
    group* previousPointer;     /* Previous pointer, for backtracking dynamic array 1 step */
    group* endPointer;          /* points to end of list, used for reducing group sizes */
    int done, compatible; /*Bolean valuesss*/
    int overruleQuestions[amountOfQuestions];   /* a list of which questions are overruling questions, meaning an associative array*/
    int overruleQuestionsLength=0;  /* Amount of overruling questions in overruleQuestions list*/
    int i, x, j=0;  /* Random counters */
    
    *amountOfGroups=0; /*Currently there are 0 groups */


    /* ---------------  ALGORITHM BEGINS    ----------------- */

    for (i=0; i< amountOfQuestions; i++){    /* Generate list of all overruling questions */
        if (listOfOverrulingQuestions[i]==2){       /* Overruling questions will have datapoint 2, others will have 1 >*/
            overruleQuestions[j]=i;
            overruleQuestionsLength++;  /* We make this list so we only go through overruling questions, not all questions */
            j++;
        }
    }

    /* This procedure works by checking if a students 'code' matches with a certain group.
    If the student matches they are added to that group
    If the student does not match, the next group is checked
    If the student does not match any current groups, a new group is created with the students 'code'.

    A student's code is determined by their answers to overruling questions */

    if (overruleQuestionsLength!=0){  /* If there is atleast one overruling question */
        for (i=0; i < amountOfStudents; i++){   /* For each student, till no students remain */
            pointer = output; /* Reset pointer */
            done = false;  /* Set done to false */
            x = 0;          /* Used to count how far into the dynamic group array we are */

            while (!done){  /* Inserts a single student process */
                if (x<*amountOfGroups){ /* If there are avaliable groups */
                    compatible = true;      /* The student is assumed to be compatible, till it can be seen they are not */

                    for (j=0; j<overruleQuestionsLength && compatible==true; j++){  /* Check if the student's 'code' matches the group 'code' */
                        if (listOfStudents[i][overruleQuestions[j]]!=pointer->groupcode[j]){    /* If student does not match group */
                            compatible=false;   /* Set student to not compatible */
                        }
                    }
                    
                    if (compatible == true){ /*If compatible, add to current group */
                        addStudent(i,pointer);  /* Adds student */
                        done = true;    /* Successfully found group, go next student */
                    }
                    else {                  /* If not compatible, go next group */
                        previousPointer = pointer;      /* Update previouspointer */
                        pointer = pointer->nextGroup;   /* Goes next group */
                        x++;
                    }
                }
                /* If no more available groups, and student code matches no current groups */
                else if (pointer == output){     /* If no groups have been created before, create first group */
                    /* Gets new group with code matching first student */
                    output = getNewGroup(i, listOfStudents[i], amountOfStudents, overruleQuestionsLength, overruleQuestions);
                    (*amountOfGroups)++;    /* Notes there is 1 more group */
                    done = true;    /* Successfully found group for student */
                    endPointer = output;    /* Update endpointer */
                }
                else {              /* Creating All future groups */
                    /* Gets new group with code matching student */
                    previousPointer->nextGroup=getNewGroup(i, listOfStudents[i], amountOfStudents, overruleQuestionsLength, overruleQuestions);
                    (*amountOfGroups)++;/* Notes there is 1 more group */
                    done = true;/* Successfully found group for student */
                    endPointer = previousPointer->nextGroup;     /* Update endpointer */
                }
            }
        }
    }
    else {  /* In scenario with no overruling auestions */


        output = getEmptyGroup(amountOfStudents);   /* Create empty group with students amount of slots */

        for (i=0;i<amountOfStudents;i++){       /* Fill them in arbetrarily with all student*/
            output->studentIDs[i]=i;
        }
        output->amountOfStudents=amountOfStudents;      /* Set amount value*/
        endPointer = output;                            /* Set endpoint value*/
        *amountOfGroups=1;                               /* Set amount of groups */
        output->nextGroup = NULL;                       /* next_group is set to null */
    }


    /* Check for too large groups IF GROUP REDUCTION ON */   
    if (GROUP_REDUCTION_ON==1){
        pointer = output;
        for (i=0; i<*amountOfGroups; i++){         /* Checks the current groups */
            if ((pointer->amountOfStudents)>GROUPS_MAX_SIZE){   /* If looked at group is above GROUP_MAX_SIZE */

                reduceGroup(pointer, &endPointer);  /* Reduce group into smaller groups */
            }

            pointer=pointer->nextGroup; /* Go next group*/
        }
    }
    int count=0;    /* Counts amount of groups */
    pointer = output;
    while (pointer!=NULL)   /* Counts amount of groups, after group reduction */
    {   
        count++;
        pointer=pointer->nextGroup;
    }
    *amountOfGroups=count; /* Update amount of groups */

    /* For looking at how many students in each group, delete last */
    pointer = output;
    int woosh = true;
    while (pointer!=NULL && woosh==true)
    {
        printf("\nGroup amount of students: %d", pointer->amountOfStudents);
        pointer=pointer->nextGroup;
    }     
    /* delete later */ 
    
    
    return output; /* Returns the first group, which contains a pointer (next_group) to all subsequent groups */
}



/* Works by figuring out how many new groups we need, and how many students we need to put in them each 
Then procedes to 'steal' that amount of students from the original group, for each new group created */

/* Inputs:
Currentgroup: Is a pointer to the group that needs to be reduced to smaller groups
endGroup: Is the last group, meaning that its Next_group, leads to NULL(nothing). All future groupings must be latched onto that one 

*/

void reduceGroup(group* currentGroup, group** endGroup){  
    /* Find amount of new groups needed */
    int amountOfNewGroups = ((currentGroup->amountOfStudents-1)/GROUPS_MAX_SIZE);   /* -1 to avoid trouble generating too many groups */
    /* Find amount of students per new group */
    int studentsPerNewGroup = currentGroup->amountOfStudents/(amountOfNewGroups+1); /* +1 cause there is also the starting group */
    int i, j;
    for (i=0;i<amountOfNewGroups;i++){  /* For each new group created, create new group */
        (*endGroup)->nextGroup=getEmptyGroup(studentsPerNewGroup); /* Create new group */
        *endGroup = (*endGroup)->nextGroup; /* Update the last group, to be the group just created */

        for (j=0;j<studentsPerNewGroup;j++){    /* Transfer students */
            (currentGroup->amountOfStudents)--;
            (*endGroup)->studentIDs[j]=currentGroup->studentIDs[currentGroup->amountOfStudents];
        }
    }

}

/* Used in cases with no overruling questions or with reduce group, here we create a group struct
Only space for student IDs + amount of students, no group code. */
/* Inputs:
Amount of students: Amount of students meant to be in the empty group
*/

group* getEmptyGroup(int amountOfStudents){         /* Lesser version of getNewGroup, will only malloc place for students and insert student amount*/
    group* newGroup = (group*)malloc(sizeof(group));    /* Make space for new group */
    checkMallocSuccess(newGroup);

    newGroup->amountOfStudents=amountOfStudents;    /* Set group amount of students */
    newGroup->studentIDs = (int*)malloc(amountOfStudents*sizeof(int));  /* Allocate space for students in group */
    checkMallocSuccess(newGroup->studentIDs);
    return newGroup;    /* Return pointer to generated group */
}

/* Used to create a newgroup, will create new unique group code, and malloc space for lists */

/* Inputs:
studentID: The first student in the group's ID. Person 'starting the group'

studentAnswers: This is a list of the student 'starting the group''s answers.

Amount of students: Amount of students in total (meaning all students)
codeLength: Amount of integers in the codelength

overruleQuestions: List over which questions are overruling
*/

group* getNewGroup(int studentID, int* studentAnswers, int amountOfStudents, int codeLength, int* overruleQuestions){
    group* newGroup = (group*)malloc(sizeof(group)); /* make space for new group */
    checkMallocSuccess(newGroup);
    newGroup->groupcode = (int*)malloc(codeLength*sizeof(int)); /* Make space for a groupcode */
    checkMallocSuccess(newGroup->groupcode);
    int i;
    for (i=0; i<codeLength; i++){   /* Create the new groupcode to match the student's groupcode */
        newGroup->groupcode[i]=studentAnswers[overruleQuestions[i]];
    }
    newGroup->amountOfStudents=1;   /* Sets amount of students to 0 */
    newGroup->studentIDs = (int*)malloc(amountOfStudents*sizeof(int));  /* Makes space for list of students, up to all students, in case all students have the same code*/
    checkMallocSuccess(newGroup->studentIDs);
    newGroup->studentIDs[0]=studentID;  /* Add student that created the group, to the list of students, in group */
    newGroup->nextGroup = NULL; /* There is no next_group */


    return newGroup;
}


/* Adds a student to a group */
/* Inputs:
StudentID: The student being added's ID
groupPointer: Pointer to the group the student is being added to */


void addStudent(int studentID, group* groupPointer){
    groupPointer->studentIDs[groupPointer->amountOfStudents]=studentID;     /* Adds student to tbeir slot */
    groupPointer->amountOfStudents++;                                       /* Keeps track of total students in group, incrementing with 1 */
}

/* -------------------------
----------------------------
----------------------------
----------------------------

- From here optimization begins -

----------------------------
----------------------------
----------------------------
----------------------------*/

/* This process takes students from the groupings list, and puts them into the list of roommates 
List of roommates has 3 levels

Upper level: An array with room sizes, each of these slots contains a pointer to another list with rooms of that size
Mid level: An array with rooms, these 'room' arrays contain a pointer to students
Low level: An array representing the individual room, space 0 is reserved for compatibility score, rest contain the student IDs, in that room


Optimization works by going through each group, and adding their students to the list of roommates. Then freeing the group list.


*/
/*inputs:
listOfStudents: 2 dime
ListOfGroups: Pointer to first group with students, future groups can be reached through listOfGroups->Next_Group

amountOfGroups: Integer with amount of groups

listOfQuestionTypes: Array with 'amountOfQuestions' elements. Each element is an integer telling of a question type 1->Scale, 2->Yes/No, 3->Text

amountOfQuestions: Integer with amount of questions
maxPersonRoom: Integer with maximum sized room

roomTypes: Array with 'maxPersonRoom' elements. Each element is an integer detailing how many rooms there are available of that size. 
Roomtypes[0]->1-person rooms, roomtypes[1]-> 2-person rooms etc. 

inUseRooms: Pointer to an array with 'maxPersonRoom' elements. Counts rooms in use at different room sizes

beginningTotalValue: Pointer to integer used to keep track of total compatibility before first iteration of geneAlgorithm

listOfIterationValues: List of totalcompatibility added value at each iteration
*/

int*** applyOptimization(int** listOfStudents, group* listOfGroups, int amountOfGrups, int* listOfQuestionTypes, int amountOfQuestions, int maxPersonRoom, int* roomTypes, int** inUseRooms, int* beginningTotalValue,int* listOfIterationValues){

    int i, j;
    int*** listOfRoommates =  (int***)malloc(maxPersonRoom*sizeof(int**));      /* 2 dimensional array per room type */
    *inUseRooms = (int*)malloc(maxPersonRoom*sizeof(int)); /* Used to keep track of how many rooms are currently in use */
    group* pointer; /* Points to current group */

    checkMallocSuccess(listOfRoommates);
    checkMallocSuccess(inUseRooms);


    for (i=0;i<maxPersonRoom;i++){                                              /* Makes space for rooms */
        listOfRoommates[i]=(int**)malloc(roomTypes[i]*sizeof(int*));
        checkMallocSuccess(listOfRoommates[i]);

        for (j=0; j<roomTypes[i]; j++){                                         /* Makes space for students in rooms */
            listOfRoommates[i][j]=(int*)malloc((i+1)*sizeof(int));  /* Space 0 is reserved for compatibility score */
            checkMallocSuccess(listOfRoommates[i][j]);
        }  
    }

    for (i=0;i<maxPersonRoom;i++){
        (*inUseRooms)[i]=0;                /* Set to default zero in used rooms, as none have been used yet */
    }

        /* ---------- actual algorithm ----------- */


    for (i=0;i<amountOfGrups;i++){     /* Creates roommates from each group, and adds them to listOfRoommates*/

        getRoommates(listOfRoommates, listOfStudents, listOfGroups->studentIDs, listOfGroups->amountOfStudents, amountOfQuestions, listOfQuestionTypes, roomTypes, maxPersonRoom, *inUseRooms, beginningTotalValue, listOfIterationValues);


        /* Free all values , this causes issues so commented out*/
        //free(listOfGroups->studentIDs);
 

        pointer = listOfGroups; /* This is here to free the pointer later on, which we don't do anymore cause it messes with the program */

        /* Go next group*/
        listOfGroups=listOfGroups->nextGroup;

        //free(pointer);
    }

    
    return listOfRoommates;    
}


/* Puts all students from a group into rooms
Firstly creates compatibility array, which keeps track of all compatibilities in group.

Afterwards picks appropriate room size for students, going high -> low

Then fills in group randomly

Then starts gene basic algorithm

*/

/*inputs:
listOfRoommates: Explained on line 860

listsOfStudents: A 2-dimensional array. The first dimension is the individual students, and the second array is their answers.

ListOfGroupStudents: Array with all student IDs beloning to the group

amountOfGroupStudents: Amount of students in group

amountOfQuestions: Integer with amount of questions
listOfQuestionTypes: Array with 'amountOfQuestions' elements. Each element is an integer telling of a question type 1->Scale, 2->Yes/No, 3->Text

roomTypes: Array with 'maxPersonRoom' elements. Each element is an integer detailing how many rooms there are available of that size. 

maxPersonRoom: Integer with maximum sized room

inUseRooms: Pointer to an array with 'maxPersonRoom' elements. Counts rooms in use at different room sizes

beginningTotalValue: Pointer to integer used to keep track of total compatibility before first iteration of geneAlgorithm

listOfIterationValues: List of totalcompatibility added value at each iteration
*/


void getRoommates(int*** listOfRoommates, int** listOfAllStudents, int* listOfGroupStudents, int amountOfGroupStudents, int amountOfQuestions, int* listOfQuestionTypes, int* roomTypes, int maxPersonRoom, int* inUseRooms, int* beginningTotalValue,int* listOfIterationValues){
    int i, j;
    int roomsCounter=0;  /* Will keep track of size of groupRooms Array */

    int roomSize;


    int** groupRooms=(int**)malloc(amountOfGroupStudents*sizeof(int*)); /* List over which rooms are attached to this room */
    checkMallocSuccess(groupRooms);
    for (i=0; i<amountOfGroupStudents;i++){
        groupRooms[i]=(int*)malloc(2*sizeof(int));
        checkMallocSuccess(groupRooms[i]);
    }    
    /* Make a list that keeps track group rooms size and numbers
    Needs to be able to find roomsize, and specific rooms
    Therefore the array will lead to a secondary array containing room size and room number, 
    position 0 in is room size, 1 is room number

    Will be used as associative array for getRoommates

    Example: Room 5 group is using
    groupRooms[5][0]=Group room 5 roomSize
    groupRooms[5][1]=Group room 5 roomNumber

    Then to find 2 students in a room you would do
    listOfRoommates[groupRooms[5][0]]  [groupRooms[5][1]]  [1]  -For finding the first student
    listOfRoommates[groupRooms[5][0]]  [groupRooms[5][1]]  [2]  -For finding the second student
    */ 


    /* Finds rooms and fills them up randomly */
    findRooms(groupRooms, listOfRoommates, listOfGroupStudents, amountOfGroupStudents, roomTypes, maxPersonRoom, inUseRooms, &roomsCounter);
    /* Find compatibility for all current rooms */

    for (i=0; i<roomsCounter; i++){ /* Counts total amount of compatibility there currently is */
        *beginningTotalValue += getRoomCompatibility(listOfRoommates, listOfAllStudents, groupRooms[i], amountOfQuestions, listOfQuestionTypes);
    }


    int x;  /* Potential for printing out the 'gene' which is room allocation */
    /* Print gene */
    // for (j=0;j<roomsCounter; j++){
    //     printf("\nRoom %d:   ", j);
    //     for (x=0; x<groupRooms[j][0]+1;x++){
    //         printf("%d - ", listOfRoommates[groupRooms[j][0]][groupRooms[j][1]][x+1]);
    //     }
    // }

    if (roomsCounter>1){    /* Only gonna do algorithm if there is more than 1 room */

        /* The actual gene algorithm, made with AMOUNT_OF_ITERATIONS iterations */

        for (i=0;i<AMOUNT_OF_ITERATIONS; i++){
            geneAlgorithm(roomsCounter, groupRooms, listOfRoommates, listOfAllStudents, amountOfQuestions, listOfQuestionTypes, listOfIterationValues, i);

            
            /* Potential for printing out the 'gene' which is room allocation */
            // for (j=0;j<roomsCounter; j++){
            //     printf("\nRoom %d:   ", j);
            //     for (x=0; x<groupRooms[j][0]+1;x++){
            //         printf("%d - ", listOfRoommates[groupRooms[j][0]][groupRooms[j][1]][x+1]);
            //     }
            // }
            // printf("\n %d \n\n", i);
        }
    }

    /* Need find compativviltiy score for every room afterwards, this is to calculate room compatibility at the end */
    for (i=0; i<roomsCounter; i++){ /* For each room */
        getRoomCompatibility(listOfRoommates, listOfAllStudents, groupRooms[i], amountOfQuestions, listOfQuestionTypes);
    }


    /* Free array, but issues with free command so no */

    for (i=0;i<amountOfGroupStudents;i++){
        //free(groupRooms[i]);                 
    }

    //free(groupRooms);

}

/* GeneAlgorithm takes a current allcoation, and makes an amount of mutations, then picks the best mutation to set as the new base model */

/*inputs:

roomsCounter: Integer with amount of rooms in group

groupRooms: 2 dimensional array with group rooms. Explained on line 990

listOfRoommates: Explained on line 860

listsOfAllStudents: A 2-dimensional array. The first dimension is the individual students, and the second array is their answers.

amountOfQuestions: Integer with amount of questions
listOfQuestionTypes: Array with 'amountOfQuestions' elements. Each element is an integer telling of a question type 1->Scale, 2->Yes/No, 3->Text

listOfIterationValues: List of totalcompatibility added value at each iteration

counter: Integer with iteration the algorithm is currently on
*/


void geneAlgorithm(int roomsCounter, int** groupRooms, int*** listOfRoommates,int** listOfAllStudents, int amountOfQuestion, int* listOfQuestionTypes, int* listOfIterationValues, int counter){
/* Current version switches around 2 students at a time */
    int i, j, newValue, bestValue=-10000;  /* Best value is set to something where SURELY, atleast one new mutation value should be higher */
    int valueHolder;
    int** newMutation=(int**)malloc(2*sizeof(int*)); /* Pointer to student ID's in listOfRoommates,  */
    /* Switches position 0 and 1, refering to student ID position */
    checkMallocSuccess(newMutation);
    int** bestMutation=(int**)malloc(2*sizeof(int*)); /* Copy of the best newMutation */
    checkMallocSuccess(bestMutation);

    /* Get mutations process */

    for(i=0; i<AMOUNT_OF_MUTATIONS; i++){   /* For amount of mutations, get a new mutation */

        getMutation(&newValue, newMutation, roomsCounter, groupRooms , listOfRoommates, listOfAllStudents, amountOfQuestion, listOfQuestionTypes);

        if (newValue>bestValue){    /* If new mutation has better value than previous best value */
            bestValue=newValue;          /* Set new best value */
            for (j=0; j<2;j++){
                bestMutation[j]=newMutation[j]; /* Copy mutation to become new best mutation*/
            }
        }
    }
    listOfIterationValues[counter]=bestValue; /* Notes down added value */

    /* perform best mutation */
    valueHolder = (*(bestMutation[0])); /* Holds id of student 1 */
    *(bestMutation[0]) = *(bestMutation[1]);    /* Replaces student 1 with student 2 */
    *(bestMutation[1])= valueHolder;    /* Puts student 1 in student 2's previous place */


    //free(newMutation);  /* Free values works, which is weird */
    //free(bestMutation);
}



/* Mutation finds 2 rooms, and a student from each, and tries switching them around and tests the gained vaue*/

/* 
/*inputs:

newValue: Pointer to integer keeping track of value gained from mutation

newMutation: Array with a pointer to student IDS in listOfRoommates. newMutation[0] is student 1, newMutation[1] is student 2

roomsCounter: Integer with amount of rooms in group

groupRooms: 2 dimensional array with group rooms. Explained on line 990

listOfRoommates: Explained on line 860

listsOfAllStudents: A 2-dimensional array. The first dimension is the individual students, and the second array is their answers.

amountOfQuestions: Integer with amount of questions
listOfQuestionTypes: Array with 'amountOfQuestions' elements. Each element is an integer telling of a question type 1->Scale, 2->Yes/No, 3->Text

*/

void getMutation(int* newValue,int** newMutation, int roomsCounter, int** groupRooms ,int*** listOfRoommates,int** listOfAllStudents, int amountOfQuestion, int* listOfQuestionTypes){
    int i, j;   
    int oldValue=0; /* Holds old value for rooms */
    int tempValue=0; /* Value found in rooms after mutation */
    int valueHolder;

    /* Finds two random rooms*/
    int room1 = (int)rand()%roomsCounter;  
    int room2 = (int)rand()%roomsCounter;

    while (room1==room2){
        room2 = (int)rand()%roomsCounter;        /* Makes sure its different rooms */
    }
    int student1 =(int)rand()%(groupRooms[room1][0]+1)+1; /* Gets random student from found room */
    int student2 =(int)rand()%(groupRooms[room2][0]+1)+1; /* Gets random student from found room */


    /* Store new mutation */
    newMutation[0]=&(listOfRoommates[groupRooms[room1][0]][groupRooms[room1][1]][student1]);  /* Gets pointers to student 1 ID value */
    newMutation[1]=&(listOfRoommates[groupRooms[room2][0]][groupRooms[room2][1]][student2]);  /* Gets pointer to student 2 ID value */


    /* Get satisfaction from the two rooms, before applying mutation */

    oldValue += getRoomCompatibility(listOfRoommates, listOfAllStudents, groupRooms[room1], amountOfQuestion, listOfQuestionTypes);
    oldValue += getRoomCompatibility(listOfRoommates, listOfAllStudents, groupRooms[room2], amountOfQuestion, listOfQuestionTypes);


    /* Perform mutation, switching students */
    valueHolder = *(newMutation[0]); /* Holds id of student 1 */
    *(newMutation[0]) = *(newMutation[1]);    /* Replaces student 1 with student 2 */
    *(newMutation[1])= valueHolder; 

    /* Get new value */
    tempValue += getRoomCompatibility(listOfRoommates, listOfAllStudents, groupRooms[room1], amountOfQuestion, listOfQuestionTypes);
    tempValue += getRoomCompatibility(listOfRoommates, listOfAllStudents, groupRooms[room2], amountOfQuestion, listOfQuestionTypes);


    /* Perform mutation, switching students again back to original*/
    valueHolder = *(newMutation[0]); /* Holds id of student 1 */
    *(newMutation[0]) = *(newMutation[1]);    /* Replaces student 1 with student 2 */
    *(newMutation[1])= valueHolder; 

    /* Finds new value by finding the difference between after mutation and before mutation */
    *newValue = tempValue - oldValue;

    // printf("\nNewvalue: %d \n", *newValue);
}
    
/* GetRoomCompatibility gets a groupRoom, and finds the compatibility within the room, returning that value */

/*inputs:

roomsCounter: Integer with amount of rooms in group


listOfRoommates: Explained on line 860

listsOfAllStudents: A 2-dimensional array. The first dimension is the individual students, and the second array is their answers.

groupRoom: 1 dimensional array taken from groupRooms, to the groupRoom in question. GroupRooms explained on line 990


amountOfQuestions: Integer with amount of questions
listOfQuestionTypes: Array with 'amountOfQuestions' elements. Each element is an integer telling of a question type 1->Scale, 2->Yes/No, 3->Text

*/
int getRoomCompatibility(int*** listOfRoommates,int** listOfAllStudents, int* groupRoom, int amountOfQuestion, int* listOfQuestionTypes){

    int i, j, amountOfCompatibilities=0;

    listOfRoommates[groupRoom[0]][groupRoom[1]][0] = 0; /* Sets grouproom compatibility to zero */

    for (i=0; i<groupRoom[0]+1;i++){    /* Cycle through all students in room and set them as i */
        if (listOfRoommates[groupRoom[0]][groupRoom[1]][i+1]!=-1){ /* If student i not a filler student */
            for (j=i+1; j<groupRoom[0]+1;j++){  /* Cycle through all other students in room  and set them as j*/
                
                if (listOfRoommates[groupRoom[0]][groupRoom[1]][j+1]!=-1){  /* If student j not filler student */

                    listOfRoommates[groupRoom[0]][groupRoom[1]][0] +=   /* Adds all student compatibilities together */
                    /* Gets compatibility between the two students */
                    getCompatibility(listOfAllStudents[listOfRoommates[groupRoom[0]][groupRoom[1]][i+1]], 
                    listOfAllStudents[listOfRoommates[groupRoom[0]][groupRoom[1]][j+1]],
                    amountOfQuestion, listOfQuestionTypes);

                    amountOfCompatibilities++;  /*Counts amount of compatibilities together */
                }

            }
        }
    }


    if (amountOfCompatibilities==0){    /* If only one person */
        listOfRoommates[groupRoom[0]][groupRoom[1]][0] = amountOfQuestion*4; /* Set to max compatibility */
    }
    else {      /* Divide accumulated compatibility by amount of compatibilities */
        listOfRoommates[groupRoom[0]][groupRoom[1]][0] = listOfRoommates[groupRoom[0]][groupRoom[1]][0] / amountOfCompatibilities;
    }
    // printf("Compatibility: %d \n", listOfRoommates[groupRoom[0]][groupRoom[1]][0]);
    return listOfRoommates[groupRoom[0]][groupRoom[1]][0];  /* Returns the compatibility */
}



/* Finds rooms needed to accomdate for amount of students in group. Always trying to fill out larger rooms first */

/* 
/*inputs:

groupRooms: 2 dimensional array with group rooms. Explained on line 990

listOfRoommates: Explained on line 860

listsOfGroupStudents: An array with all student ID's in the group

amountOfGroupStudents: Amount of students in group

roomTypes: Array with 'maxPersonRoom' elements. Each element is amount of avaliable rooms at that roomsize.

maxPersonRoom: Max sized room

inUseRooms: Array with 'maxPersonRoom' elements. Each element is amount of used rooms at that roomsize.

roomsCounter: A poiner to an integer with how many rooms are used by the group.
*/
void findRooms(int** groupRooms, int*** listOfRoommates, int* listOfGroupStudents, int amountOfGroupStudents, int* roomTypes, int maxPersonRoom, int* inUseRooms, int* roomsCounter){

    int amountOfGroupStudentsTracker = amountOfGroupStudents;   /* Keeps track of how many students are remaining */
    
    /* Runs till all students have been allocated */
    while (amountOfGroupStudentsTracker>0){
        /* Finds largest roomsize where all spots can be used */
        int roomSize = getRoomSize(amountOfGroupStudentsTracker, roomTypes, maxPersonRoom);
        
        /* Fills out room with students from listOfGroupStudents*/
        fillRoom(&roomSize, listOfRoommates, inUseRooms, maxPersonRoom, &amountOfGroupStudentsTracker, listOfGroupStudents); 

        /*Adds room to list of GroupRooms */
        groupRooms[*roomsCounter][0]=roomSize;
        groupRooms[*roomsCounter][1]=inUseRooms[roomSize]-1;  /* Already counted up in fillRoom so need reduce by 1 here */


        (*roomsCounter) += 1;   /* Counts one more room */
    }

}


/* Fills room up with as mant students as it can, potentially adds filler if needed */

/*inputs:

roomSize: pointer to an integer with the size of the room. 
If the integer is negative, it means that there are not enough students to fill the room out, and it needs fillers

listOfRoommates: Explained on line 860

inUseRooms: Array with 'maxPersonRoom' elements. Each element is amount of used rooms at that roomsize.

maxPersonRoom: Max sized room

amountOfGroupStudentsTracker: Amount of students in group remaining

listsOfGroupStudents: An array with all student ID's in the group

*/
void fillRoom(int* roomSize, int*** listOfRoommates, int* inUseRooms, int maxPersonRoom, int* amountOfGroupStudentsTracker, int* listOfGroupStudents){
    int i;
    if (*roomSize>=0){ /* If no need for filler students, signaled by a psotive number*/

        for (i=0; i<(*roomSize)+1; i++){    /* Fills in 'roomsize+1' amounts of students from listOfGroupStudents */
            listOfRoommates[*roomSize][inUseRooms[*roomSize]][i+1]=listOfGroupStudents[(*amountOfGroupStudentsTracker) - 1];
            (*amountOfGroupStudentsTracker) -= 1;   /*Reduces amount of students by 1 */
        }
    }

    else {      /* If need to fill up with 'fake' students, signaled by a negative number */
        *roomSize = (*roomSize) * -1;   /* Revert the number to positive */

        for (i=0; i<(*amountOfGroupStudentsTracker); i++){ /*Fill in last remaining students */
            listOfRoommates[*roomSize][inUseRooms[*roomSize]][i+1]=listOfGroupStudents[(*amountOfGroupStudentsTracker) - 1];
        }
        /* Fill in remaining */
        for (i; i<(*roomSize)+1;i++){   /* When out of students, fill in rest as blanks signalled by -1 */
            listOfRoommates[*roomSize][inUseRooms[*roomSize]][i+1]=-1;
        }
        *amountOfGroupStudentsTracker =0;   /* Set amount of remaining students to zero */

    }

    inUseRooms[*roomSize] += 1; /* Adds an extra room in use of this size */
}



/* Finds appropriate room size, picking the largest possible or the one that can be filled out the most */
/*inputs:

amountOfGroupStudents: Amount of students in group remaining

roomTypes: Array with 'maxPersonRoom' elements. Each element is amount of avaliable rooms at that roomsize.

maxPersonRoom: Max sized room

*/

int getRoomSize(int amountOfGroupstudents, int* roomTypes, int maxPersonRoom){
    int i;  /* Indicates current roomsize looked at */
    int lowestAvailableRoom = maxPersonRoom; /* Variable meant to keep track of lowest available room, we start from 1 above max, to see if any rooms remain */

    for (i=maxPersonRoom-1;i>=0;i--){   /* Counting down to size 0 rooms */
        
        if (roomTypes[i]>0){ /* If any rooms of this size avaliable */

            if (amountOfGroupstudents>=(i+1)){  /* If enough students to fill out room */
                roomTypes[i] -= 1; /* We use this roomsize, and update amount of rooms of this size */
                return(i);
            }
            else {  /* Else mark down as lowest available room */
                lowestAvailableRoom=i;        
            }
        }

    }

    /* In cases where i runs out of room options, meaning no room can be filled out fully
    We wish to use the smallest size room possible */

    if (lowestAvailableRoom!=maxPersonRoom){    /* this checks if lowestavaliable has been updated, since it was originally defined
    If there is an available room left we pick the lowest avaliable*/


        roomTypes[lowestAvailableRoom] -= 1; /* Update amount of rooms */

        /* Returns a minus value to symbol we need to fill up remaining */


        return (lowestAvailableRoom * -1);
        
    }

    else {  /* No rooms left, but students still remain */
        printf("\nProgram error, no more rooms avaliable. Bye!");
        exit(EXIT_FAILURE);
    }
    return i; /* Filler */
}





/* Calculates compatibility between two students 

This is done by comparing their answers to differnet questions 


Type 1: Scale questions with range 1-5. Points are awarded depending on how far from eachother answers are
Type 2: Multiple choice questions, only points if they match
Type 3: Text based? Maybe, if gets implemented, no function handling it yet
*/
/*inputs:

studentID1Answers: Array with answers from the first student
studentID2Answers: Array with answers from the second student

amountOfQuestions: integer with amount of questions


listOfQuestionTypes: Array with 'amountOfQuestions' elements. Each element is an integer telling of a question type 1->Scale, 2->Yes/No, 3->Text


*/

int getCompatibility(int* studentID1Answers, int* studentID2Answers, int amountOfQuestion, int* listOfQuestionTypes){
    /* Currently we are also using overruling questions, which is uneccesary, could be taken out */
    
    /* There is 4 max 'points' per question. Points measure positive compatibility */

    int compatibility = 0, i;   /* Compatibility keeps track of the pairs compatibility */

    for (i=0; i<amountOfQuestion; i++){ /* Goes through all questions */

        if (listOfQuestionTypes[i]==1){         /* Scale questions*/
            compatibility+= 4-abs(studentID1Answers[i]-studentID2Answers[i]);  
            /* (Scale length - Difference in student answers)/Scale length */
        }
        else if (listOfQuestionTypes[i]==2){    /* yes/no questions */
            if (studentID1Answers[i]==studentID2Answers[i]){
                compatibility+=4;   
            }
        }

        else if (listOfQuestionTypes[i]!=3) {   /* If not text based question either */
            exit(EXIT_FAILURE);
        }
    }


    return compatibility;   /* Returns compatibility */
}



/* -------------------------
----------------------------
----------------------------
----------------------------

- From here Output begins -

----------------------------
----------------------------
----------------------------
----------------------------*/

/* creates output, by reading through list of roommates, and printing to 3 output txt documents
Firstly roommate pairings along with their satisfaction score
Secondly a scoretracker over how many rooms are in different ranges
Thirdly a tracker over the gene progress across all iterations */

/*inputs:

outputFile: String name of the txt document that recieves student pairings
outputDataFile: String name of txt document that gets scoretracker of how many rooms in different ranges
outputFileGene: String name of txt document that gets gene score at different iterations

listOfRoommates: Explained on line 860, has list of all created roommate pairings

inUseRooms: Array with 'maxPersonRoom' elements. Each element is amount of used rooms at that roomsize.

maxPersonRoom: Max sized room

amountOfQuestions: integer with amount of questions

beginningTotalValue: Pointer to integer used to keep track of total compatibility before first iteration of geneAlgorithm

listOfIterationValues: List of totalcompatibility added value at each iteration

*/


void createOutput(char* outputFile, char* outputDataFile, char* outputFileGene, int*** listOfRoommates, int* inUseRooms, int maxRooms, int amountOfQuestions, int beginningValue, int* listOfIterationValue){
    int i, j, x=1, y;        /* x counts number of current room, starting from 1 */
    double averageSatisfaction = 0;         /* Sets to zero for now */

    int amountOfRooms=0;

    int* scoreTracker = (int*)malloc(10*sizeof(int));   /* Used to track how many rooms have different scores within satisfaction levels:
    0-10, 10-20, 20-30, ..., 90-100 */
    checkMallocSuccess(scoreTracker);

    for (i=0;i<10;i++){
        scoreTracker[i]=0;  /* Sets amount of rooms at different scores to 0 */
    }


    int maxScore = amountOfQuestions * 4;   /* Finds max amount of points */

    printf("\nPrinting Pairings\n");

    FILE *fp = fopen(outputFile, "w");  /* Open file */
    if (fp != NULL){
        for (j=0;j<maxRooms;j++){   /* Goes through all room sizes */
            for (i = 0; i < inUseRooms[j]; i++){    /* Goes through all rooms of size j */
                fprintf(fp, "Room %3d: %3d ",x, listOfRoommates[j][i][1]);  /* Prints first person in room */
                amountOfRooms++;
                for (y=1;y<(j+1);y++){  /* If there are more than one more person in the room, print renmaining */
                    if (listOfRoommates[j][i][y+1]!=-1){    /* If person isn't filler person(Signalled by >-1<, add remaining people */
                        fprintf(fp, "- %3d ", listOfRoommates[j][i][y+1]);
                    }
                }
                /* Print satisfaction level in room */
                fprintf(fp, "| Satisfaction: %4d%%. \n", (listOfRoommates[j][i][0]*100)/maxScore); /* Spot in listOfRoommates is reserved for satisfaction value */
                averageSatisfaction += (listOfRoommates[j][i][0]*100)/maxScore; /* Adds to accumulated satisfaction */
                x++;    /* Counts amount of rooms */
                storeSatisfaction(scoreTracker, maxScore, listOfRoommates[j][i][0]);    /* Adds to list of how many people with each satisfaction level */
            }
        }

    }
    else {
        printf("\n Could not find pairings output file.\n");
        exit(EXIT_FAILURE);
    }
    
    fclose(fp); /*Closes file */


    averageSatisfaction = averageSatisfaction/(x-1);    /* Reduces accumulated satisfaction by amount of rooms */

    /* Writes data output */

    printf("\nPrinting Scores\n");

    fp = fopen(outputDataFile, "w");    /* Open outputscore file */
    if (fp != NULL){
        

        fprintf(fp, "\nAverageSatisfaction: %lf%% \n", averageSatisfaction);    /* Print average satisfaction */

        for (i=0;i<10;i++){ /* Prints satisfaction rates */

            fprintf(fp, "\nRooms with satisfaction: %3d%% - %3d%% | %3d \n", i*10, (i+1)*10, scoreTracker[i]);  
            /* Prints amount of rooms at different satisfaction levels */

        }

    }
    else {
        printf("\n Could not find scores output file.\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp); /*Closes file */

    printf("\nPrinting Gene\n");

    if (PRINT_GENE==1){     /* If pint_Gene is on */
        fp = fopen(outputFileGene, "w");    /* Open file */
        if (fp != NULL){
            
            fprintf(fp, "\nStart value: %d \n", beginningValue);    /* Prints original value */
            int maxValue = maxScore*amountOfRooms;  /* Finds maximum possible value */
            for (i=0;i<AMOUNT_OF_ITERATIONS;i++){ /* Prints satisfaction rates */

                beginningValue += listOfIterationValue[i];  /* Updates current value */
                /* Prints interation number, current value, change since last iteration, and percent of max possible option */
                fprintf(fp, "\n Time %d: %3d - %3d | %3lf%% \n", i, beginningValue, listOfIterationValue[i], 100*(double)beginningValue/maxValue);

            }

        }
        else {
            printf("\n Could not find gene output file.\n");
            exit(EXIT_FAILURE);
        }
        fclose(fp); /*Closes file */

    }



    free(scoreTracker);
}

/* Keeps track of how many rooms of different satisfaction levels there are */
/*inputs:

Scoretracker: Array with 10 elements, 0-10, 10-20, 20-30, ... 90-100. It counts amount of rooms within those satisfaction pairs

maxScore: Max possible dcore within a room (4*amountOfQuestions)

Satisfaction: Satisfaction within the given room

*/
void storeSatisfaction(int* scoreTracker, int maxScore, int satisfaction){

    int percentSatisfaction = ceil((double)satisfaction*10/maxScore);    /* finds amounts from 1-10 */

    if (percentSatisfaction==0){    /* Fixer for if student compatibility = 0 */
        percentSatisfaction++;
    }

    scoreTracker[percentSatisfaction-1] += 1;     /* Counter for amount of rooms within that satisfaction range */

}



/* Helper functions */
void checkMallocSuccess(void* list){    /* Checks if malloc succeded*/
    if (list==NULL){    /*Checks if malloc succeded */
        printf("\n Fail in memory allocation bye.\n");
        exit(EXIT_FAILURE);
    }
} 
