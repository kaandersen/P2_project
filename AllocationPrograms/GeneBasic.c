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
#define GROUPS_MAX_SIZE 50
#define GROUP_REDUCTION_ON 0 /* 1 for true, 0 for false */

/* Exclusive to gene algorithm */
#define AMOUNT_OF_ITERATIONS 1000    /* How many times the algorithm should run */
#define AMOUNT_OF_MUTATIONS 250   /* How many new options should be made every time */
#define PRINT_GENE 1            /* If should print gene progress, ONLY IF NO OVERRULING QUESTIONS */


/* Structs */

struct group {       
    int*           groupcode;       /* Digit code of what questions this group represents */
    int     amountOfStudents;
    int*          studentIDs;       /* List of student ID's */
    struct group* nextGroup;        /* Pointer to next group */
    };
typedef struct group group;

/* Prototypes */
/* Get data */
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

/* Make groups */
group* generateGroups(int** listOfStudents, int amountOfStudents, int* listOfOverrulingQuestions, int amountOfQuestions, int* listOfQuestionTypes, int* amountOfGroups);

group* getEmptyGroup(int amountOfStudents);
group* getNewGroup(int studentID, int* studentAnswers, int amountOfStudents, int codeLength, int* overruleQuestions);
void addStudent(int studentID, group* groupPointer);
void reduceGroup(group* currentGroup, group** endGroup);


/* Allocate students */
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
    /* Declaring variables */
    // printf("Test");
    // return(0);
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
    printf("Got answers \n");

    group* listOfGroups = generateGroups(listOfStudents, amountOfStudents, listOfOverrulingQuestions, amountOfQuestions, listOfQuestionTypes, &amountOfGroups);      
     /*Generates dynamic associative array to refer to which student-IDs are in groups */

    printf("Got Groups \n");

    int*** listOfRoommates = applyOptimization(listOfStudents, listOfGroups, amountOfGroups, listOfQuestionTypes, amountOfQuestions, maxPersonRoom, roomTypes, &inUseRooms, &beginningTotalValue, listOfIterationValues);   /* The hard part */

    printf("\n\nSuccessfully created roommate list!!!!");

    /* free values */
    freeValues(listOfStudents, roomTypes, listOfQuestionTypes, listOfOverrulingQuestions, amountOfStudents);

    printf("\n\nSuccessfully Freed values");

    /* Print output */  
    createOutput("Admin/output.txt", "Admin/outputData.txt", "AllocationPrograms/outputGene.txt", listOfRoommates, inUseRooms, maxPersonRoom, amountOfQuestions, beginningTotalValue, listOfIterationValues); /* Prints the results */


    printf("Successfully Finished Program");

    return EXIT_SUCCESS;
}   
/* Frees all the lists */
void freeValues(int** listOfStudents,int* roomTypes,int* listOfQuestionTypes,int* listOfOverrulingQuestions,int amountOfStudents){
    int i;

    free(roomTypes);
 //   free(listOfQuestionTypes);        /* Touching this apparently breaks stuff, for somer reason? */
    free(listOfOverrulingQuestions);



    for (i=0;i<amountOfStudents;i++){
        free(listOfStudents[i]);
    }
    free(listOfStudents);
}

void getQuestionnaireInfoTemp(int* questionnaireID, int* amountOfStudents, int* amountOfQuestions, int** listOfQuestionTypes, int** listOfOverrulingQuestions,int* maxPersonRoom, int** roomtypes){
 
    *amountOfStudents = 100;
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
    *maxPersonRoom=5;        /* Serves as a constant variable */
    *roomtypes = (int*)malloc(*maxPersonRoom*sizeof(int));
    for (i=0; i<*maxPersonRoom;i++){
        (*roomtypes)[i]=0;                /* Sets a base value for testing */
    }
    (*roomtypes)[1]=30;    /* Only 2-person rooms */
    (*roomtypes)[2]=10;    /* Only 2-person rooms */
    (*roomtypes)[4]=2;    /* Only 2-person rooms */


}

void getQuestionnaireInfo(int* questionnaireID, int* amountOfStudents, int* amountOfQuestions, int** listOfQuestionTypes, int** listOfOverrulingQuestions,int* maxPersonRoom, int** roomtypes){
    int i, j;
    
    char* textBuffer1 = (char*)malloc(50*sizeof(char));

    char* line = (char*)malloc(1024*sizeof(char));;
    /* File questionnaire ID */

    FILE* fp = fopen("EliasStuff/public/QuestionaireData.csv", "r");

    if (fp!=NULL){
        i=0;        /* Have to find second iteration cause need get rid of top */
        while (fgets(line, 1024, fp))
        {
            char* tmp1 = strdup(line);
            char* tmp2 = strdup(line);
            //printf("Field 3 would be %s\n", getfield(tmp1, 1));
            // NOTE strtok clobbers tmp


            if (i==1){
                *questionnaireID = stringToInt(getfield(tmp1, 1));
                *amountOfQuestions = stringToInt(getfield(tmp2, 2));
            }

            free(tmp1);
            free(tmp2);
            i++;
        }
    }
    else {  /*If no file found */
        printf("\n Could not find questionnaire directions file.\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp); /*Closes file */


    printf("\nQuestions: %d,  Id: %d  \n", *amountOfQuestions, *questionnaireID);

    /* Make space for lists */
    *listOfOverrulingQuestions = (int*)malloc(*amountOfQuestions*sizeof(int));
    *listOfQuestionTypes = (int*)malloc(*amountOfQuestions*sizeof(int));


    /* 
    //////////////////////////////
    //////////////////////////////          QUESTION INFO
    //////////////////////////////
    */

    fp = fopen("EliasStuff/public/Questionaire.csv", "r");

    if (fp!=NULL){
        i=0;        /* Have to find second iteration cause need get rid of top */
        j=0; /* Counts amount of questions */
        while (fgets(line, 1024, fp))
        {
            char* tmp1 = strdup(line);
            char* tmp2 = strdup(line);
            char* tmp3 = strdup(line);
            //printf("Field 3 would be %s\n", getfield(tmp1, 1));
            // NOTE strtok clobbers tmp


            if (i>0){ /* If not first line */
                if (stringToInt(getfield(tmp1, 1))==*questionnaireID){  /* If correct questionnaire */
                    if (strcmp(getfield(tmp2, 4), "SCALE")==0){
                        (*listOfQuestionTypes)[j]=1;
                    }
                    else if (strcmp(tmp2, "YES/NO")==0){
                        (*listOfQuestionTypes)[j]=2;
                    }
                    else if (strcmp(tmp2, "TEXT")==0){
                        (*listOfQuestionTypes)[j]=3;
                    }
                    else {
                        printf("\nInvalid question type.\n");
                        exit(EXIT_FAILURE);
                    }

                    if (getfield(tmp3, 5)!=NULL){
                        (*listOfOverrulingQuestions)[j]=1;
                    }
                    else{
                        (*listOfOverrulingQuestions)[j]=0;
                    }
                    j++;
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


    for (i=0; i<*amountOfQuestions; i++){
        printf("Type: %d    Overruling: %d \n", (*listOfQuestionTypes)[i], (*listOfOverrulingQuestions)[i]);
    }


    /* 
    //////////////////////////////
    //////////////////////////////          ROOM INFO
    //////////////////////////////
    */

    *roomtypes = (int*)malloc(50*sizeof(int));
    
    fp = fopen("EliasStuff/public/StudentInfoQuestionaire.csv", "r");

    if (fp!=NULL){
        i=0;        /* Counts till iteration with room we want */
        j=0;        /* Counts amount of rooms */
        while (fgets(line, 1024, fp))
        {
            char* tmp1 = strdup(line);
            char* tmp2 = strdup(line);
            //printf("Field 3 would be %s\n", getfield(tmp1, 1));
            // NOTE strtok clobbers tmp


            if (i==(*questionnaireID)-1){ /* If time that matches questionnaire */
                *amountOfStudents = stringToInt(getfield(tmp1, 2));

                textBuffer1 = getfield(tmp2, 3);

                sscanf(textBuffer1, " %d - ", &(*roomtypes)[j]);
                j++;
                
                while (textBuffer1[1]== '-')
                {
                    strcpy(textBuffer1, textBuffer1+2); /* Remove two characters*/
                    sscanf(textBuffer1, " %d ", &(*roomtypes)[j]);

                    j++;
                }
                *maxPersonRoom=j;
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


    printf("MaxSize: %d , students: %d \n", *maxPersonRoom, *amountOfStudents);
    for (i=0; i<*maxPersonRoom; i++){
        printf("Amount at size %d: %d  \n", i, (*roomtypes)[i]);
    }

    free(textBuffer1);
    free(line);
}

void getStudentAnswers(int*** listOfStudents, int amountOfStudents, int amountOfQuestions, int questionnaireID, int* listOfQuestionTypes){
    int i, j, x;
    
    char* textBuffer1 = (char*)malloc(50*sizeof(char));

    char* line = (char*)malloc(1024*sizeof(char));;



    (*listOfStudents) = (int**)malloc(amountOfStudents*sizeof(int*));
    for (i=0; i<amountOfStudents;i++ ){
        (*listOfStudents)[i]=(int*)malloc(amountOfQuestions*sizeof(int));
    }


    FILE* fp = fopen("EliasStuff/public/StudentQuestionaire.csv", "r");

    if (fp!=NULL){
        i=0;        /* Counts till over first room */
        j=0;        /* Counts amount of students */
        x=0;      /* Counts amount of questions */
        while (fgets(line, 1024, fp))
        {
            char* tmp1 = strdup(line);
            char* tmp2 = strdup(line);
            //printf("Field 3 would be %s\n", getfield(tmp1, 1));
            // NOTE strtok clobbers tmp


            if (i>0){ /* If over first run */

                if (stringToInt(getfield(tmp1, 1))==questionnaireID){   /* If right questionnaire */

                    if (listOfQuestionTypes[x]!=3){ /* If not text*/
                        (*listOfStudents)[j][x]=stringToInt(getfield(tmp2, 2));
                    }
                    else {
                        (*listOfStudents)[j][x]=0; /* If text set to zero */
                    }
                    x++;
                    if (x==amountOfQuestions){
                        x=0;
                        j++;
                    }

                }

            }
            free(tmp1);
            free(tmp2);
            i++;
        }
    }
    else {  /*If no file found */
        printf("\n Could not find student answers file.\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp); /*Closes file */


    for (i=0; i<amountOfStudents; i++){
        printf("Student %d \n", i);
        for (j=0; j<amountOfQuestions; j++){
            printf("Answer %d = %d\n", j, (*listOfStudents)[i][j]);
        }
    }


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
    sscanf(string, "%d", &output);
    return output;  /* Convert string to integer*/
}



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

/* This puts students in the right groups */

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

    //listOfOverrulingQuestions[3]=2;     /* Question number 4 is set to overruling, FOR TESTING */

    /* -------------------------------- */

    for (i=0; i< amountOfQuestions; i++){    /* Generate list of all overruling questions */
        if (listOfOverrulingQuestions[i]==2){       /* Assuming overruling questions will have datapoint 2, others will have 1 >*/
            overruleQuestions[j]=i;
            overruleQuestionsLength++;  /* We make this list so we only go through overruling questions */
            j++;
        }
    }

    /* This procedure works by checking if a students 'code' matches with a certain group.
    If the student matches they are added to that group
    If the student does not match, the next group is checked
    If the student does not match any current groups, a new group is created with the students 'code'.

    A student's code is determined by their answers to overruling questions */

    if (overruleQuestionsLength!=0){  /* Assuming there is atleast one overruling question */
        for (i=0; i < amountOfStudents; i++){   /* Inserts all students */
            pointer = output; /* Reset pointer */
            done = false;  
            x = 0;          /* Used to count how far into the dynamic group array we are */
            while (!done){  /* Inserts a single student */
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
                    }
                    else {                  /* Go next list */
                        previousPointer = pointer;
                        pointer = pointer->nextGroup;
                        x++;
                    }
                }
                else if (pointer == output){     /* Create first group */

                    output = getNewGroup(i, listOfStudents[i], amountOfStudents, overruleQuestionsLength, overruleQuestions);
                    (*amountOfGroups)++;
                    done = true;
                    endPointer = output;    /* Update endpointer */
                }
                else {              /* Create All future groups */
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
        output->nextGroup = NULL;
    }


    /* Check for too large groups IF GROUP REDUCTION ON */   
    if (GROUP_REDUCTION_ON==1){
        pointer = output;
        for (i=0; i<*amountOfGroups; i++){         /* Checks the current groups */
            if ((pointer->amountOfStudents)>GROUPS_MAX_SIZE){   /* If looked at group is above limit */
                /* Oh fuck */
                reduceGroup(pointer, &endPointer);  /* The magic touch */
            }

            pointer=pointer->nextGroup; /* Go next */
        }
    }

    int count=0;
    pointer = output;
    while (pointer!=NULL)   /* Counts amount of groups, after group reduction */
    {   
        count++;
        pointer=pointer->nextGroup;
    }
    *amountOfGroups=count; /* Update amount of groups */


    /* For funsies/testing, delete later */
    pointer = output;
    int woosh = true;
    while (pointer!=NULL && woosh==true)
    {
        printf("\nGroup amount of students: %d", pointer->amountOfStudents);
        pointer=pointer->nextGroup;
    }     
    /* For funsies, delete later */ 
    
    
    return output;
}

/* Works by figuring out how many new groups we need, and how many students we need to put in them each 
Then procedes to 'steal' that amount of students from the original group, for each new group created */

void reduceGroup(group* currentGroup, group** endGroup){                             /* Worried there will be an issue with student amounts just below a multiplication of maxStudentsPerGroup */
    int amountOfNewGroups = ((currentGroup->amountOfStudents-1)/GROUPS_MAX_SIZE);   /* -1 to avoid trouble generating too many groups */
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

/* Used in case with no overruling questions and reduce group, here we create a group struct
Only space for student IDs + amount of students, no group code. */

group* getEmptyGroup(int amountOfStudents){         /* Lesser version of getNewGroup, will only malloc place for students and insert student amount*/
    group* newGroup = (group*)malloc(sizeof(group));


    newGroup->amountOfStudents=amountOfStudents;
    newGroup->studentIDs = (int*)malloc(amountOfStudents*sizeof(int));
    return newGroup;
}

/* Used to create a newgroup, will create new unique group code, and malloc space for lists */

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


/* Adds a student to a group */

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

/* This process takes students from the groupings list, and puts them into the list of roommates 
List of roommates has 3 levels

Upper level: An array with room sizes, each of these slots contains a pointer to another list with rooms of that size
Mid level: An array with rooms, these 'room' arrays contain a pointer to students
Low level: An array representing the individual room, space 0 is reserved for compatibility score, rest contain the student IDs, in that room


Optimization works by going through each group, and adding their students to the list of roommates. Then freeing the group list.

*/

int*** applyOptimization(int** listOfStudents, group* listOfGroups, int amountOfGrups, int* listOfQuestionTypes, int amountOfQuestions, int maxPersonRoom, int* roomTypes, int** inUseRooms, int* beginningTotalValue,int* listOfIterationValues){

    int i, j;
    int*** listOfRoommates =  (int***)malloc(maxPersonRoom*sizeof(int**));      /* 2 dimensional array per room type */
    *inUseRooms = (int*)malloc(maxPersonRoom*sizeof(int)); /* Used to keep track of how many rooms are currently in use */
    group* pointer;

    checkMallocSuccess(listOfRoommates);


    for (i=0;i<maxPersonRoom;i++){                                              /* Makes space for rooms */
        listOfRoommates[i]=(int**)malloc(roomTypes[i]*sizeof(int*));
        checkMallocSuccess(listOfRoommates[i]);

        for (j=0; j<roomTypes[i]; j++){                                         /* Makes space for students in rooms */
            listOfRoommates[i][j]=(int*)malloc((i+1)*sizeof(int));  /* Space 0 is reserved for compatibility score */
            checkMallocSuccess(listOfRoommates[i][j]);
        }   /* Should call malloc success but would take a whileee */
    }

    for (i=0;i<maxPersonRoom;i++){
        (*inUseRooms)[i]=0;                /* Set to default zero in use */
    }

        /* ---------- actual algorithm ----------- */


    for (i=0;i<amountOfGrups;i++){     /* Creates roommates from each group, and adds them to listOfRoommates*/

  
        getRoommates(listOfRoommates, listOfStudents, listOfGroups->studentIDs, listOfGroups->amountOfStudents, amountOfQuestions, listOfQuestionTypes, roomTypes, maxPersonRoom, *inUseRooms, beginningTotalValue, listOfIterationValues);
    

        /* Free all values */
        free(listOfGroups->studentIDs);
        /* free code should also be used but does not work for reduced groups where it will crash the program, so kinda iffyyy */
        pointer = listOfGroups; /* Used to get rid of actual group holding thingy */

        /* Go next group*/
        listOfGroups=listOfGroups->nextGroup;

        free(pointer);
    }

    
    return listOfRoommates;    
}


/* Puts all students from a group into rooms
Firstly creates compatibility array, which keeps track of all compatibilities in group.

Afterwards picks appropriate room size for students, going high -> low

Then finds best pairings for that amount of students

Afterwards frees the group

*/
void getRoommates(int*** listOfRoommates, int** listOfAllStudents, int* listOfGroupStudents, int amountOfGroupStudents, int amountOfQuestions, int* listOfQuestionTypes, int* roomTypes, int maxPersonRoom, int* inUseRooms, int* beginningTotalValue,int* listOfIterationValues){
    int i, j;
    int roomsCounter=0;  /* Will keep track of size of groupRooms Array */

    int roomSize;


    int** groupRooms=(int**)malloc(amountOfGroupStudents*sizeof(int*));
    checkMallocSuccess(groupRooms);
    for (i=0; i<amountOfGroupStudents;i++){
        groupRooms[i]=(int*)malloc(2*sizeof(int));
        checkMallocSuccess(groupRooms[i]);
    }    
    /* Make a list that keeps track group rooms size and numbers
    Needs to be able to find roomsize, and specific rooms
    Therefore the array will lead to a secondary array containing room size and room number, position 0 is room size, 1 is room number
    Will be used as associative array for getRoommates
    */ 


    /* Finds rooms and fills them up randomly */
    findRooms(groupRooms, listOfRoommates, listOfGroupStudents, amountOfGroupStudents, roomTypes, maxPersonRoom, inUseRooms, &roomsCounter);
    /* Find compatibility for all current rooms */
    for (i=0; i<roomsCounter; i++){
        *beginningTotalValue += getRoomCompatibility(listOfRoommates, listOfAllStudents, groupRooms[i], amountOfQuestions, listOfQuestionTypes);
    }



    int x;
    /* Print gene */
    // for (j=0;j<roomsCounter; j++){
    //     printf("\nRoom %d:   ", j);
    //     for (x=0; x<groupRooms[j][0]+1;x++){
    //         printf("%d - ", listOfRoommates[groupRooms[j][0]][groupRooms[j][1]][x+1]);
    //     }
    // }

    if (roomsCounter>1){    /* Only gonna do algorithm if there is more than 1 room */

        /* The actual gene algorithm, made with 500 iterations currently*/

        for (i=0;i<AMOUNT_OF_ITERATIONS; i++){
            geneAlgorithm(roomsCounter, groupRooms, listOfRoommates, listOfAllStudents, amountOfQuestions, listOfQuestionTypes, listOfIterationValues, i);

            
            // /* Print gene */
            // for (j=0;j<roomsCounter; j++){
            //     printf("\nRoom %d:   ", j);
            //     for (x=0; x<groupRooms[j][0]+1;x++){
            //         printf("%d - ", listOfRoommates[groupRooms[j][0]][groupRooms[j][1]][x+1]);
            //     }
            // }
        }
    }

    /* Need find compativviltiy score arfterwards */
    for (i=0; i<roomsCounter; i++){
        getRoomCompatibility(listOfRoommates, listOfAllStudents, groupRooms[i], amountOfQuestions, listOfQuestionTypes);
    }


    /* Free array */

    for (i=0;i<amountOfGroupStudents;i++){
        //free(groupRooms[i]);                  /* Find out why issues with 'free' command */
    }

    free(groupRooms);

}

void geneAlgorithm(int roomsCounter, int** groupRooms, int*** listOfRoommates,int** listOfAllStudents, int amountOfQuestion, int* listOfQuestionTypes, int* listOfIterationValues, int counter){
/* Current version switches around 2 students at a time */
    int i, j, newValue, bestValue=-10000;  /* Best value is set to something where SURELY, atleast one new mutation value should be higher */
    int valueHolder;
    int** newMutation=(int**)malloc(2*sizeof(int*)); /* Pointer to student ID's in listOfRoommates,  */
    /* Switches position 0 and 1, refering to student ID position */

    int** bestMutation=(int**)malloc(2*sizeof(int*)); /* Copy of the best newMutation */
    
    
    /* Need to make 4 new options, these 4 new options need to have their benefit factor noted down */

    for(i=0; i<AMOUNT_OF_MUTATIONS; i++){

        getMutation(&newValue, newMutation, roomsCounter, groupRooms , listOfRoommates, listOfAllStudents, amountOfQuestion, listOfQuestionTypes);

        if (newValue>bestValue){    /* If new best value */
            bestValue=newValue;          /* Set new best value */
            for (j=0; j<2;j++){
                bestMutation[j]=newMutation[j]; /* Copy mutation */
            }
        }
    }
    listOfIterationValues[counter]=bestValue;

    /* Best option */
    // printf("Best options:  %d - %d ", *(bestMutation[0]), *(bestMutation[1]));

    /* perform best mutation */
    valueHolder = (*(bestMutation[0])); /* Holds id of student 1 */
    *(bestMutation[0]) = *(bestMutation[1]);    /* Replaces student 1 with student 2 */
    *(bestMutation[1])= valueHolder; 


    free(newMutation);
    free(bestMutation);
}

/* Mutation needs to find a room, and student, and keep track of them, which means just a pointer to an integer will do? */
void getMutation(int* newValue,int** newMutation, int roomsCounter, int** groupRooms ,int*** listOfRoommates,int** listOfAllStudents, int amountOfQuestion, int* listOfQuestionTypes){
    int i, j;
    int oldValue=0;
    int tempValue=0;
    int valueHolder;

    /* We need to first find the rooms and students we will be switching */
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


    /* Get satisfaction from the two rooms*/

    /* Can be optimized further, only calculating those values relevant to the student */
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


    *newValue = tempValue - oldValue;

    // printf("\nNewvalue: %d \n", *newValue);
}
    




int getRoomCompatibility(int*** listOfRoommates,int** listOfAllStudents, int* groupRoom, int amountOfQuestion, int* listOfQuestionTypes){

    int i, j, amountOfCompatibilities=0;

    listOfRoommates[groupRoom[0]][groupRoom[1]][0] = 0; /* Sets grouproom compatibility to zero */
    for (i=0; i<groupRoom[0]+1;i++){    /* Cycle through all students in room */
        if (listOfRoommates[groupRoom[0]][groupRoom[1]][i+1]!=-1){ /* If i not a filler student */
            for (j=i+1; j<groupRoom[0]+1;j++){  /* Cycle through all students in room */
                
                if (listOfRoommates[groupRoom[0]][groupRoom[1]][j+1]!=-1){  /* If j not filler student */


                    // printf("Student 1:  %d    Student 2: %d \n", listOfRoommates[groupRoom[0]][groupRoom[1]][i+1], listOfRoommates[groupRoom[0]][groupRoom[1]][j+1]);

                    listOfRoommates[groupRoom[0]][groupRoom[1]][0] +=   /* Adds all student compatibilities together */
                    getCompatibility(listOfAllStudents[listOfRoommates[groupRoom[0]][groupRoom[1]][i+1]], 
                    listOfAllStudents[listOfRoommates[groupRoom[0]][groupRoom[1]][j+1]],
                    amountOfQuestion, listOfQuestionTypes);

                    amountOfCompatibilities++;
                }

            }
        }
    }


    if (amountOfCompatibilities==0){    /* If only one person */
        listOfRoommates[groupRoom[0]][groupRoom[1]][0] = amountOfQuestion*4; /* Set to max compatibility */
    }
    else {      /* Divide accumulated compatibility by amount of roommates */
        listOfRoommates[groupRoom[0]][groupRoom[1]][0] = listOfRoommates[groupRoom[0]][groupRoom[1]][0] / amountOfCompatibilities;
    }
    // printf("Compatibility: %d \n", listOfRoommates[groupRoom[0]][groupRoom[1]][0]);
    return listOfRoommates[groupRoom[0]][groupRoom[1]][0];
}



void findRooms(int** groupRooms, int*** listOfRoommates, int* listOfGroupStudents, int amountOfGroupStudents, int* roomTypes, int maxPersonRoom, int* inUseRooms, int* roomsCounter){

    int amountOfGroupStudentsTracker = amountOfGroupStudents;
    
    /* Till all students have been allocated */
    while (amountOfGroupStudentsTracker>0){
        /* Finds roomSize */
        int roomSize = getRoomSize(amountOfGroupStudentsTracker, roomTypes, maxPersonRoom);
        
        fillRoom(&roomSize, listOfRoommates, inUseRooms, maxPersonRoom, &amountOfGroupStudentsTracker, listOfGroupStudents); 


        groupRooms[*roomsCounter][0]=roomSize;
        groupRooms[*roomsCounter][1]=inUseRooms[roomSize]-1;  /* Already counted up in fillRoom so need reduce by 1 here */


        (*roomsCounter) += 1;
    }

}

void fillRoom(int* roomSize, int*** listOfRoommates, int* inUseRooms, int maxPersonRoom, int* amountOfGroupStudentsTracker, int* listOfGroupStudents){
    int i;
    if (*roomSize>=0){ /* If no need for filler students */

        for (i=0; i<(*roomSize)+1; i++){
            listOfRoommates[*roomSize][inUseRooms[*roomSize]][i+1]=listOfGroupStudents[(*amountOfGroupStudentsTracker) - 1];
            (*amountOfGroupStudentsTracker) -= 1;
        }
    }

    else {      /* If need to fill up with 'fake' students */
        *roomSize = (*roomSize) * -1;

        for (i=0; i<(*amountOfGroupStudentsTracker); i++){
            listOfRoommates[*roomSize][inUseRooms[*roomSize]][i+1]=listOfGroupStudents[(*amountOfGroupStudentsTracker) - 1];
        }
        /* Fill in remaining */
        for (i; i<(*roomSize)+1;i++){
            listOfRoommates[*roomSize][inUseRooms[*roomSize]][i+1]=-1;
        }
        *amountOfGroupStudentsTracker =0;   /* Set remaining students to zero */

    }

    inUseRooms[*roomSize] += 1;
}





/* Finds appropriate room size */
int getRoomSize(int amountOfGroupstudents, int* roomTypes, int maxPersonRoom){
    int i;
    int lowestAvailableRoom = maxPersonRoom; /* Variable meant to keep track of lowest available room */

    for (i=maxPersonRoom-1;i>=0;i--){   /* Counting down to size 0 rooms */
        
        if (roomTypes[i]>0){ /* If any rooms of this size avaliable */

            if (amountOfGroupstudents>=(i+1)){  /* If enough students to fill out room */
                roomTypes[i] -= 1; /* Update amount of rooms */
                return(i);
            }
            else {  /* Else mark down as lowest available room */
                lowestAvailableRoom=i;        
            }
        }

    }

    /* In cases where i runs out of room options */

    if (lowestAvailableRoom!=maxPersonRoom){    /* If there is an available room left */


        roomTypes[lowestAvailableRoom] -= 1; /* Update amount of rooms */

        /* Need a way to get all remaining students into a single group and fill out this group */
        /* Returns a minus value to symbol we need to fill up remaining */


        return (lowestAvailableRoom * -1);
        
    }

    else {  /* No rooms left */
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
int getCompatibility(int* studentID1Answers, int* studentID2Answers, int amountOfQuestion, int* listOfQuestionTypes){
    /* Currently we are also using overruling questions, which is uneccesary, could be taken out */
    
    /* There is 5 max 'points' per question. Points measure positive compatibility */

    int compatibility = 0, i;
    for (i=0; i<amountOfQuestion; i++){

        if (listOfQuestionTypes[i]==1){         /* Scale questions*/
            compatibility+= 4-abs(studentID1Answers[i]-studentID2Answers[i]);
            /* (Scale length - Difference in student answers)/Scale length */
        }
        else if (listOfQuestionTypes[i]==2){    /* Pick a thingy questions */
            if (studentID1Answers[i]==studentID2Answers[i]){
                compatibility+=4;   
            }
        }

        else if (listOfQuestionTypes[i]!=3) {   /* If not question based question either */
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

/* creates output, by reading through list of roommates, and printing to file */

void createOutput(char* outputFile, char* outputDataFile, char* outputFileGene, int*** listOfRoommates, int* inUseRooms, int maxRooms, int amountOfQuestions, int beginningValue, int* listOfIterationValue){
    int i, j, x=1, y;        /* x counts number of current room, starting from 1 */
    double averageSatisfaction = 0;         /* Sets to zero for now */

    int amountOfRooms=0;

    int* scoreTracker = (int*)malloc(10*sizeof(int));   /* Used to track how many rooms have different scores */
    checkMallocSuccess(scoreTracker);

    for (i=0;i<10;i++){
        scoreTracker[i]=0;  /* Sets score to 0 */
    }

    int maxScore = amountOfQuestions * 4;   /* Finds max amount of points */

    printf("Printing Output");

    FILE *fp = fopen(outputFile, "w");
    if (fp != NULL){
        for (j=0;j<maxRooms;j++){   /* Goes through all room sizes */
            for (i = 0; i < inUseRooms[j]; i++){    /* Goes through all rooms of size j */
                fprintf(fp, "Room %3d: %3d ",x, listOfRoommates[j][i][1]);  /* Prints first person in room */
                amountOfRooms++;
                for (y=1;y<(j+1);y++){
                    if (listOfRoommates[j][i][y+1]!=-1){    /* Prints additional people in room, if person isn't filler person */
                        fprintf(fp, "- %3d ", listOfRoommates[j][i][y+1]);
                    }
                }
                fprintf(fp, "| Satisfaction: %4d%%. \n", (listOfRoommates[j][i][0]*100)/maxScore); /* 0 is reserved for satisfaction value */
                averageSatisfaction += (listOfRoommates[j][i][0]*100)/maxScore; /* Adds to accumulated satisfaction */
                x++;    /* Counts amount of rooms */
                storeSatisfaction(scoreTracker, maxScore, listOfRoommates[j][i][0]);    /* Adds to list of how many people with each satisfaction level */
            }
        }

    }
    else {
        printf("\n Could not find output file.\n");
        exit(EXIT_FAILURE);
    }
    
    fclose(fp); /*Closes file */


    averageSatisfaction = averageSatisfaction/(x-1);    /* reduces total satisfaction by amount of rooms */

    /* Writes data output */

    printf("Printing Stats");

    fp = fopen(outputDataFile, "w");
    if (fp != NULL){
        
        printf("Printing Stats");

        fprintf(fp, "\nAverageSatisfaction: %lf%% \n", averageSatisfaction);

        for (i=0;i<10;i++){ /* Prints satisfaction rates */


            fprintf(fp, "\nRooms with satisfaction: %3d%% - %3d%% | %3d \n", i*10, (i+1)*10, scoreTracker[i]);

        }

    }
    else {
        printf("\n Could not find output file.\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp); /*Closes file */

    printf("Printing Gene");

    if (PRINT_GENE==1){    
        fp = fopen(outputFileGene, "w");
        if (fp != NULL){
            
            fprintf(fp, "\nStart value: %d \n", beginningValue);
            int maxValue = maxScore*amountOfRooms;
            for (i=0;i<AMOUNT_OF_ITERATIONS;i++){ /* Prints satisfaction rates */

                beginningValue += listOfIterationValue[i];
                fprintf(fp, "\n Time %d: %3d - %3d | %3lf%% \n", i, beginningValue, listOfIterationValue[i], 100*(double)beginningValue/maxValue);

            }

        }
        else {
            printf("\n Could not find output file.\n");
            exit(EXIT_FAILURE);
        }
        fclose(fp); /*Closes file */

    }



    free(scoreTracker);
}

/* Keeps track of how satisfied rooms are */
void storeSatisfaction(int* scoreTracker, int maxScore, int satisfaction){

    int percentSatisfaction = ceil((double)satisfaction*10/maxScore);    /* finds amounts from 1-10 */

    if (percentSatisfaction==0){    /* Should very very rarely happen, but if they literally are direct opposites */
        percentSatisfaction++;
    }

    scoreTracker[percentSatisfaction-1] += 1;     /* Counter for amount of rooms within that range */

}



/* Helper functions */
void checkMallocSuccess(void* list){
    if (list==NULL){    /*Checks if malloc succeded */
        printf("\n Fail in memory allocation bye.\n");
        exit(EXIT_FAILURE);
    }
} 
