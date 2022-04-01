#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h> /* Remove once actual answers can be gotten */
#include <stdbool.h>        /* Bolean values */

/*///////////////////
PROGRAM DESCRIPTION 



//////////////////*/


/* Constant Variables */
#define GROUPS_MAX_SIZE 10


/* Structs */

struct group {       
    int*           groupcode;       /* Digit code of what questions this group represents */
    int     amountOfStudents;
    int*          studentIDs;       /* List of student ID's */
    struct group* nextGroup;
    };
typedef struct group group;

/* Prototypes */

void getQuestionnaireInfoTemp(char* inputFile, int* amountOfStudents, int* amountOfQuestions, int** listOfQuestionTypes, int** listOfOverrulingQuestions,int* maxPersonRoom, int** roomtypes);
void getStudentAnswersTemp(char* inputFile, int*** listOfStudents, int amountOfStudents, int amountOfQuestions);

void getQuestionnaireInfo(char* inputFile, int* amountOfStudents, /* Reads from the input file */ 
                    int* amountOfQuestions, int** listOfQuestionTypes, int** listOfOverrulingQuestions,  /* Question related*/
                    int* maxPersonRoom, int** roomtypes    /* Get roomtypes in an array */);
void getStudentAnswers(char* inputFile, int*** listOfStudents, int amountOfStudents, int amountOfQuestions);



group* generateGroups(int** listOfStudents, int amountOfStudents, int* listOfOverrulingQuestions, int amountOfQuestions, int* listOfQuestionTypes, int* amountOfGroups);

group* getEmptyGroup(int amountOfStudents);
group* getNewGroup(int studentID, int* studentAnswers, int amountOfStudents, int codeLength, int* overruleQuestions);
void addStudent(int studentID, group* groupPointer);
void reduceGroup(group* currentGroup, group** endGroup);



int*** applyOptimization(int** listOfStudents, group* listOfGroups, int* listOfQuestionTypes, int amountOfQuestions, int amountOfGroups);

int getCompatibility(int* studentID1Answers, int* studentID2Answers, int amountOfQuestion, int* listOfQuestionTypes);
void fillCompatibilityArray(int** compatibilityArray,int** listOfAllStudents,int* listOfGroupStudents,int amountOfGroupStudents,int amountOfQuestions,int* listOfQuestionTypes);
void getRoommates(int*** listOfRoommates, int** listOfAllStudents, int* listOfGroupStudents, int amountOfGroupStudents, int amountOfQuestions, int* listOfQuestionTypes);




void createOutput(char* outputFile, int*** listOfRoommates, int* listOfRoomTypes, int maxRooms);






/* Helper functions */
void checkMallocSuccess(void* list);


int main(){
    /* Declaring variables */
    int amountOfGroups, amountOfQuestions, amountOfStudents;
    int** listOfStudents;     /* 2 Dimensional array with all students-ID's followed by their answers */
    int maxPersonRoom;       /* Max amount of persons in a room */
    int* roomtypes;          /* Array with amount of rooms with different amount of people capacity, spot 0 represents 1 person rooms, 1 represents 2 person rooms etc. */
    int* listOfQuestionTypes; /* List of question types */
    int* listOfOverrulingQuestions;  /* List of questions that are overruling */
    getQuestionnaireInfoTemp("input1.txt", &amountOfStudents, /* Reads from the input file */ 
                    &amountOfQuestions, &listOfQuestionTypes, &listOfOverrulingQuestions,  /* Question related*/
                    &maxPersonRoom, &roomtypes  /* Get roomtypes in an array */);
    srand(time(NULL));  /* For random students answers */
    getStudentAnswersTemp("input2.txt", &listOfStudents, amountOfStudents, amountOfQuestions);
    
    group* listOfGroups = generateGroups(listOfStudents, amountOfStudents, listOfOverrulingQuestions, amountOfQuestions, listOfQuestionTypes, &amountOfGroups);      
     /*Generates dynamic associative array to refer to which student-IDs are in groups */

    int*** listOfRoommates = applyOptimization(listOfStudents, listOfGroups, listOfQuestionTypes, amountOfQuestions, amountOfGroups);   /* The hard part */

    //createOutput("outputFile", listOfRoommates, roomTypes, maxPersonRoom) /* Prints the results */

    return EXIT_SUCCESS;
}


void getQuestionnaireInfoTemp(char* inputFile, int* amountOfStudents, int* amountOfQuestions, int** listOfQuestionTypes, int** listOfOverrulingQuestions,int* maxPersonRoom, int** roomtypes){

    *amountOfStudents = 50;
    *amountOfQuestions = 5;

    *listOfQuestionTypes = (int*)malloc(*amountOfQuestions*sizeof(int));
    checkMallocSuccess(*listOfQuestionTypes);


    *listOfOverrulingQuestions = (int*)malloc(*amountOfQuestions*sizeof(int));
    checkMallocSuccess(*listOfQuestionTypes);
    int i;      /* Fill up with dummy values */
    for (i=0; i<*amountOfQuestions; i++){
        (*listOfQuestionTypes)[i]=1;
        (*listOfOverrulingQuestions)[i]=1;
    }
    /* Create room list, just ignore this section for now */ 
    *maxPersonRoom=2;        /* Serves as a constant variable */
    *roomtypes = (int*)malloc(*maxPersonRoom*sizeof(int));
    (*roomtypes)[1]=*amountOfStudents/2;    /* Only 2-person rooms */
}

void getQuestionnaireInfo(char* inputFile, int* amountOfStudents, int* amountOfQuestions, int** listOfQuestionTypes, int** listOfOverrulingQuestions,int* maxPersonRoom, int** roomtypes){
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

void getStudentAnswers(char* inputFile, int*** listOfStudents, int amountOfStudents, int amountOfQuestions){
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

void getStudentAnswersTemp(char* inputFile, int*** listOfStudents, int amountOfStudents, int amountOfQuestions){

    *listOfStudents = (int**)malloc(amountOfStudents*sizeof(int*)); /* Malloc for outer list */
    checkMallocSuccess(*listOfStudents);

    int i, j;
    for (i=0; i<amountOfStudents;i++){
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


group* generateGroups(int** listOfStudents, int amountOfStudents, int* listOfOverrulingQuestions, int amountOfQuestions, int* listOfQuestionTypes, int* amountOfGroups){

    group* output;      /* Functions as start of the array */
    group* pointer;     /* Currently looking to */
    group* previousPointer;     /* Previous pointer, for backtracking dynamic array 1 step */
    group* endPointer;          /* points to end of list, used for reducing group sizes */
    int done, compatible; /*Bolean valuesss*/
    int overruleQuestions[amountOfQuestions];   /* Change this when the format is known */
    int overruleQuestionsLength=0;
    int i, x, j=0;
    
    *amountOfGroups=0; /*Currently there are 0 groups */

    /* Temporary playspace for testing*/

    listOfOverrulingQuestions[3]=2;

    /* -------------------------------- */



    for (i=0; i< amountOfQuestions; i++){    /* Generate list of all overruling questions */
        if (listOfOverrulingQuestions[i]==2){       /* Assuming overruling questions will have datapoint 2, others will have 1 >*/
            overruleQuestions[j]=i;
            overruleQuestionsLength++;
            j++;
        }
    }
    if (overruleQuestionsLength!=0){  /* Assuming there is atleast one overruling question */
        for (i=0; i < amountOfStudents; i++){   /* Inserts all students */
            //printf("\nStudent %d with answer %d", i, listOfStudents[i][3]);
            pointer = output; /* Reset pointer */
            done = false;  
            x = 0;          /* Used to count how far into the dynamic group array we are */
            while (!done){  /* Inserts a single student */
                //printf("Pointer before:   %d, output: %d",pointer,output);
                if (x<*amountOfGroups){
                    compatible = true;      /* Till proven guilty */
                    for (j=0; j<overruleQuestionsLength && compatible==true; j++){
                        if (listOfStudents[i][overruleQuestions[j]]!=pointer->groupcode[j]){    /* If student matches group */
                            compatible=false;
                        }
                    }
                    
                    if (compatible == true){ /*add to current list */
                        addStudent(i,pointer);
                        done = true;
                        //printf(" Already known!  ");
                    }
                    else {                  /* Go next list */
                        previousPointer = pointer;
                        pointer = pointer->nextGroup;
                        x++;
                    }
                }
                else if (pointer == output){     /* first group */
                    //printf(" First group! ");


                    output = getNewGroup(i, listOfStudents[i], amountOfStudents, overruleQuestionsLength, overruleQuestions);
                    (*amountOfGroups)++;
                    done = true;
                    endPointer = output;    /* Update endpointer */
                }
                else {              /* All future groups */
                    //printf(" New group! ");
                    previousPointer->nextGroup=getNewGroup(i, listOfStudents[i], amountOfStudents, overruleQuestionsLength, overruleQuestions);
                    (*amountOfGroups)++;
                    done = true;
                    endPointer = previousPointer->nextGroup;     /* Update endpointer */
                }
            }
        }
    }
    else {  /* In scenario with no overruling auestions */

        output = getEmptyGroup(amountOfStudents);   /* Create empty group with students amount of slots */

        for (i=0;i<amountOfStudents;i++){       /* Fill them in arbetrarily */
            output->studentIDs[i]=i;
        }
        output->amountOfStudents=amountOfStudents;      /* Set amount value*/
        endPointer = output;                            /* Set endpoint value*/
        *amountOfGroups=1;                               /* Set amount of groups */
    }


    /* Check for too large groups */   
    pointer = output;
    for (i=0; i<*amountOfGroups; i++){         /* Checks the current groups */
        if ((pointer->amountOfStudents)>GROUPS_MAX_SIZE){
            /* Oh fuck */
            //printf("\nGroup amount of students: %d", pointer->amountOfStudents);
            reduceGroup(pointer, &endPointer);
        }

        pointer=pointer->nextGroup;
    }

    int count=0;
    pointer = output;
    while (pointer!=NULL)
    {
        count++;
        pointer=pointer->nextGroup;
    }
    *amountOfGroups=count; /* Update amount of groups */



    /* For funsies/testing, delete later */
    pointer = output;
    int woosh = false;
    while (pointer!=NULL && woosh==true)
    {
        printf("\nGroup amount of students: %d", pointer->amountOfStudents);
        pointer=pointer->nextGroup;
    }
    printf("\n\nAmount of groups: %d  \n\n",*amountOfGroups);        
    /* For funsies, delete later */
    
    
    return output;
}

void reduceGroup(group* currentGroup, group** endGroup){                             /* Worried there will be an issue with student amounts just below a multiplication of maxStudentsPerGroup */
    int amountOfNewGroups = ((1+currentGroup->amountOfStudents)/GROUPS_MAX_SIZE);   /*+1 to avoid getting 2 new groups at 40*/
    int studentsPerNewGroup = currentGroup->amountOfStudents/(amountOfNewGroups+1); /* +1 cause there is also the starting group */
    int i, j;
    for (i=0;i<amountOfNewGroups;i++){
        (*endGroup)->nextGroup=getEmptyGroup(studentsPerNewGroup); /* Create new group */
        *endGroup = (*endGroup)->nextGroup;

        for (j=0;j<studentsPerNewGroup;j++){
            (currentGroup->amountOfStudents)--;
            (*endGroup)->studentIDs[j]=currentGroup->studentIDs[currentGroup->amountOfStudents];
        }
    }

}

group* getEmptyGroup(int amountOfStudents){         /* Lesser version of getNewGroup, will only malloc place for students and insert student amount*/
    group* newGroup = (group*)malloc(sizeof(group));


    newGroup->amountOfStudents=amountOfStudents;
    newGroup->studentIDs = (int*)malloc(amountOfStudents*sizeof(int));
    return newGroup;
}

group* getNewGroup(int studentID, int* studentAnswers, int amountOfStudents, int codeLength, int* overruleQuestions){
    group* newGroup = (group*)malloc(sizeof(group));

    newGroup->groupcode = (int*)malloc(codeLength*sizeof(int));
    checkMallocSuccess(newGroup->groupcode);
    int i;
    for (i=0; i<codeLength; i++){
        newGroup->groupcode[i]=studentAnswers[overruleQuestions[i]];
    }
    newGroup->amountOfStudents=1;
    newGroup->studentIDs = (int*)malloc(amountOfStudents*sizeof(int));
    checkMallocSuccess(newGroup->studentIDs);
    newGroup->studentIDs[0]=studentID;


    return newGroup;
}




void addStudent(int studentID, group* groupPointer){
    groupPointer->studentIDs[groupPointer->amountOfStudents]=studentID;     /* Adds student to tbeir slot */
    groupPointer->amountOfStudents++;                                       /* Keeps track of total students in group */
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



int*** applyOptimization(int** listOfStudents, group* listOfGroups, int* listOfQuestionTypes, int amountOfQuestions, int amountOfGroups){

    int i;
    int*** listOfRoommates =  (int***)malloc(amountOfGroups*sizeof(int**));      /* 2 dimensional array per room type */
    checkMallocSuccess(listOfRoommates);

    for (i=0;i<amountOfGroups;i++){     /* Creates roommates from each group, and adds them to listOfRoommates*/
        getRoommates(listOfRoommates, listOfStudents, listOfGroups->studentIDs, listOfGroups->amountOfStudents, amountOfQuestions, listOfQuestionTypes);
        listOfGroups=listOfGroups->nextGroup;
    }



    int*** dummyOutput;
    return dummyOutput;    
}

void getRoommates(int*** listOfRoommates, int** listOfAllStudents, int* listOfGroupStudents, int amountOfGroupStudents, int amountOfQuestions, int* listOfQuestionTypes){
    int i, j;
    int** compatibilityArray = (int**)malloc(amountOfGroupStudents*sizeof(int*));
    checkMallocSuccess(compatibilityArray);
    for (i=0;i<amountOfGroupStudents;i++){
        compatibilityArray[i]=(int*)malloc(amountOfGroupStudents*sizeof(int));  /* Alternatively could only fill in half, find out later */
        checkMallocSuccess(compatibilityArray[i]);  /* Might remove to reduce time, probably only a second extra though */
    }

    fillCompatibilityArray(compatibilityArray, listOfAllStudents, listOfGroupStudents, amountOfGroupStudents, amountOfQuestions, listOfQuestionTypes);

    
    /* prints compatibility array, remove later */

    for (i=0;i<amountOfGroupStudents;i++){
        printf("\n");
        for (j=0;j<amountOfGroupStudents;j++){
            printf(" %2d -",compatibilityArray[i][j]);
        }
    }
    printf("\n\n\n");

    /* Free array */

    for (i=0;i<amountOfGroupStudents;i++){
        free(compatibilityArray[i]);
    }
    free(compatibilityArray);

}

void fillCompatibilityArray(int** compatibilityArray,int** listOfAllStudents,int* listOfGroupStudents,int amountOfGroupStudents,int amountOfQuestions,int* listOfQuestionTypes){
    int i;  /*Vertical */
    int j;  /* Horizontal */

    for (i=0; i<amountOfGroupStudents; i++){
        for (j=0; j<i; j++){

            compatibilityArray[i][j]=getCompatibility(listOfAllStudents[listOfGroupStudents[i]], listOfAllStudents[listOfGroupStudents[j]],amountOfQuestions,listOfQuestionTypes);
            compatibilityArray[j][i]=compatibilityArray[i][j]; /* Since it's mirrored */

        }
        compatibilityArray[i][j]=0; /* Fill diagonal with zeroes */
    }

    /* Fill diagonal with zeroes */

}   


int getCompatibility(int* studentID1Answers, int* studentID2Answers, int amountOfQuestion, int* listOfQuestionTypes){
    /* Currently we are also using overruling questions, which is uneccesary, could be taken out */
    
    /* There is 5 max 'points' per question. Points measure positive compatibility */
    int compatibility = 0, i;

    for (i=0; i<amountOfQuestion; i++){
        if (listOfQuestionTypes[i]==1){         /* Scale questions*/
            compatibility+= 5-abs(studentID1Answers[i]-studentID2Answers[i]);
            /* (Scale length - Difference in student answers)/Scale length */
        }
        else if (listOfQuestionTypes[i]==2){    /* Pick a thingy questions */
            if (studentID1Answers[i]==studentID2Answers[i]){
                compatibility+=5;   
            }
        }

        else if (listOfQuestionTypes[i]!=3) {   /* If not question based question either */
            printf("\n Question %d does not have a valid question type \n", i);
            exit(EXIT_FAILURE);
        }
    }

    return compatibility;
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


void createOutput(char* outputFile, int*** listOfRoommates, int* listOfRoomTypes, int maxRooms){
    int i, j, x=1, y;        /* x counts number of current room, starting from 1 */
    double averageSatisfaction = 0;         /* Sets to zero for now */
    FILE *fp = fopen(outputFile, "w");
    if (fp != NULL){
        for (j=0;j<maxRooms;j++){ 
            for (i = 0; i < listOfRoomTypes[j]; i++){
                fprintf(fp, "Room %d: %d ",x, listOfRoommates[j][i][1]);
                for (y=1;y<(j+1);y++){
                    fprintf(fp, "- %d ", listOfRoommates[j][i][y+1]);
                }
                fprintf(fp, "| Satisfaction: %d \n", listOfRoommates[j][i][0]); /* 0 is reserved for satisfaction value */
                averageSatisfaction += listOfRoommates[j][i][0];
                x++;    /* Counts amount of rooms */
            }
        }
        averageSatisfaction/x;
        fprintf(fp, "\nAverageSatisfaction: %lf \n", averageSatisfaction);
        
    }
    else {
        printf("\n Could not find output file.\n");
        exit(EXIT_FAILURE);
    }
}





/* Helper functions */
void checkMallocSuccess(void* list){
    if (list==NULL){    /*Checks if malloc succeded */
        printf("\n Fail in memory allocation bye.\n");
        exit(EXIT_FAILURE);
    }
} 
