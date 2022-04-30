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
#define GROUP_REDUCTION_ON 0 /* 1 for true, 0 for false */

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
void getQuestionnaireInfoTemp(char* inputFile, int* amountOfStudents, int* amountOfQuestions, int** listOfQuestionTypes, int** listOfOverrulingQuestions,int* maxPersonRoom, int** roomtypes);
void getStudentAnswersTemp(char* inputFile, int*** listOfStudents, int amountOfStudents, int amountOfQuestions);

void getQuestionnaireInfo(char* inputFile, int* amountOfStudents, /* Reads from the input file */ 
                    int* amountOfQuestions, int** listOfQuestionTypes, int** listOfOverrulingQuestions,  /* Question related*/
                    int* maxPersonRoom, int** roomtypes    /* Get roomtypes in an array */);
void getStudentAnswers(char* inputFile, int*** listOfStudents, int amountOfStudents, int amountOfQuestions);


/* Make groups */
group* generateGroups(int** listOfStudents, int amountOfStudents, int* listOfOverrulingQuestions, int amountOfQuestions, int* listOfQuestionTypes, int* amountOfGroups);

group* getEmptyGroup(int amountOfStudents);
group* getNewGroup(int studentID, int* studentAnswers, int amountOfStudents, int codeLength, int* overruleQuestions);
void addStudent(int studentID, group* groupPointer);
void reduceGroup(group* currentGroup, group** endGroup);


/* Allocate students */
int*** applyOptimization(int** listOfStudents, group* listOfGroups, int amountOfGrups, int* listOfQuestionTypes, int amountOfQuestions, int maxPersonRoom, int* roomTypes, int** inUseRooms);


int getCompatibility(int* studentID1Answers, int* studentID2Answers, int amountOfQuestion, int* listOfQuestionTypes);
void getRoommates(int*** listOfRoommates, int** listOfAllStudents, int* listOfGroupStudents, int amountOfGroupStudents, int amountOfQuestions, int* listOfQuestionTypes, int* roomTypes, int maxPersonRoom, int* inUseRooms);
int getRoomSize(int amountOfGroupstudents, int* roomTypes, int maxPersonRoom);

int getGroupCompatibility(int* roomArray, int sizeOfRoom,int** compatibilityArray,int amountOfQuestions);
void fillCompatibilityArray(int** compatibilityArray,int** listOfAllStudents,int* listOfGroupStudents,int amountOfGroupStudents,int amountOfQuestions,int* listOfQuestionTypes);
int getRoomCompatibility(int*** listOfRoommates,int** listOfAllStudents, int* groupRoom, int amountOfQuestion, int* listOfQuestionTypes);

int findRooms(int** groupRooms, int*** listOfRoommates, int* listOfGroupStudents, int amountOfGroupStudents, int* roomTypes, int maxPersonRoom, int* inUseRooms, int* roomsCounter);


int optimize(int* ListOfStudentsInArray,int amountOfStudents, int amountOfRooms, int** bestConfig, int** compatibilityArray);


/* Create output */
void createOutput(char* outputFile, char* outputDataFile,int*** listOfRoommates, int* listOfRoomTypes, int maxRooms, int amountOfQuestions);
void storeSatisfaction(int* scoreTracker, int maxScore, int satisfaction);





/* Helper functions */
void checkMallocSuccess(void* list);
void freeValues(int** listOfStudents,int* roomTypes,int* listOfQuestionTypes,int* listOfOverrulingQuestions,int amountOfStudents);

int main(){
    /* Declaring variables */
    int amountOfGroups, amountOfQuestions, amountOfStudents;
    int** listOfStudents;     /* 2 Dimensional array with all students-ID's followed by their answers */
    int maxPersonRoom;       /* Max amount of persons in a room */
    int* roomTypes;          /* Array with amount of rooms with different amount of people capacity, spot 0 represents 1 person rooms, 1 represents 2 person rooms etc. */
    int* listOfQuestionTypes; /* List of question types */
    int* listOfOverrulingQuestions;  /* List of questions that are overruling */
    int* inUseRooms;                /* List over how many of each rooms are being used */
   
    /* Get question data */
    getQuestionnaireInfoTemp("input1.txt", &amountOfStudents, /* Reads from the input file */ 
                    &amountOfQuestions, &listOfQuestionTypes, &listOfOverrulingQuestions,  /* Question related*/
                    &maxPersonRoom, &roomTypes  /* Get roomtypes in an array */);
    srand(time(NULL));  /* For random students answers */

    /* Get data */
    getStudentAnswersTemp("input2.txt", &listOfStudents, amountOfStudents, amountOfQuestions);

    printf("Got data");
    
    group* listOfGroups = generateGroups(listOfStudents, amountOfStudents, listOfOverrulingQuestions, amountOfQuestions, listOfQuestionTypes, &amountOfGroups);      
     /*Generates dynamic associative array to refer to which student-IDs are in groups */

    int*** listOfRoommates = applyOptimization(listOfStudents, listOfGroups, amountOfGroups, listOfQuestionTypes, amountOfQuestions, maxPersonRoom, roomTypes, &inUseRooms);   /* The hard part */

    printf("\n\nSuccessfully created roommate list!!!!");

    /* free values */
    freeValues(listOfStudents, roomTypes, listOfQuestionTypes, listOfOverrulingQuestions, amountOfStudents);

    /* Print output */
    createOutput("AllocationPrograms/output.txt", "AllocationPrograms/outputData.txt", listOfRoommates, inUseRooms, maxPersonRoom, amountOfQuestions); /* Prints the results */


    printf("Successfully finished program");

    return EXIT_SUCCESS;
}   
/* Frees all the lists */
void freeValues(int** listOfStudents,int* roomTypes,int* listOfQuestionTypes,int* listOfOverrulingQuestions,int amountOfStudents){
    int i;
    free(roomTypes);
    free(listOfQuestionTypes);
    free(listOfOverrulingQuestions);

    for (i=0;i<amountOfStudents;i++){
        //free(listOfStudents[i]);
    }
    free(listOfStudents);
}

void getQuestionnaireInfoTemp(char* inputFile, int* amountOfStudents, int* amountOfQuestions, int** listOfQuestionTypes, int** listOfOverrulingQuestions,int* maxPersonRoom, int** roomtypes){

    *amountOfStudents = 20;
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
    for (i=0; i<*maxPersonRoom;i++){
        (*roomtypes)[i]=0;                /* Sets a base value for testing */
    }
    (*roomtypes)[1]=80;    /* Only 2-person rooms */


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
    printf("\n\nAmount of groups: %d  \n\n",*amountOfGroups);        
    /* For funsies, delete later */ 
    
    
    return output;
}

/* Works by figuring out how many new groups we need, and how many students we need to put in them each 
Then procedes to 'steal' that amount of students from the original group, for each new group created */

void reduceGroup(group* currentGroup, group** endGroup){                             /* Worried there will be an issue with student amounts just below a multiplication of maxStudentsPerGroup */
    int amountOfNewGroups = ((currentGroup->amountOfStudents)/GROUPS_MAX_SIZE)-1;   /*-1 cause there is also the starting group*/
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

int*** applyOptimization(int** listOfStudents, group* listOfGroups, int amountOfGrups, int* listOfQuestionTypes, int amountOfQuestions, int maxPersonRoom, int* roomTypes, int** inUseRooms){

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
        getRoommates(listOfRoommates, listOfStudents, listOfGroups->studentIDs, listOfGroups->amountOfStudents, amountOfQuestions, listOfQuestionTypes, roomTypes, maxPersonRoom, *inUseRooms);
    

        /* Free all values */
        printf("GetRoommate Success");
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
void getRoommates(int*** listOfRoommates, int** listOfAllStudents, int* listOfGroupStudents, int amountOfGroupStudents, int amountOfQuestions, int* listOfQuestionTypes, int* roomTypes, int maxPersonRoom, int* inUseRooms){
    int i, j;
    int roomsCounter=0; /* Used to keep track of how many rooms are allocated to this group */

    int roomSize;
    int* tempPointer1; /* List containing all students being considered for rooms, an updated version of listOfGroupStudents that also contains fillers */
    int* tempPointer2; /* List containing all students being considered for rooms, an updated version of listOfGroupStudents that also contains fillers */
    /* Firstly find the rooms needed, additionally also checks for filler students */
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


    /* Finds needed rooms */
    int extraFillers = findRooms(groupRooms, listOfRoommates, listOfGroupStudents, amountOfGroupStudents, roomTypes, maxPersonRoom, inUseRooms, &roomsCounter);

    /* Handle adding fillers, this means changing listOfGroupStudents */
    printf("Check for  filler  %d", extraFillers);
    if (extraFillers>0){

        printf("Generating filler ");

        tempPointer1 = (int*)malloc((amountOfGroupStudents+extraFillers)*sizeof(int));

        for (i=0;i<amountOfGroupStudents;i++){
            tempPointer1[i]=listOfGroupStudents[i];
        }
        for (i; i<amountOfGroupStudents+extraFillers; i++){
            tempPointer1[i]=-1;
        }
        amountOfGroupStudents += extraFillers;

        tempPointer2=listOfGroupStudents;
        listOfGroupStudents=tempPointer1;
        free(tempPointer2);                 /* Fillers have been added to list of group students */

    }
    /* If no need for fillers, just carry on using the akready labaled students */




    /* Create compaptibility array */

    int compatibilityArraySize = amountOfGroupStudents;

    int** compatibilityArray = (int**)malloc(amountOfGroupStudents*sizeof(int*));
    checkMallocSuccess(compatibilityArray);


    /* Creates space for compatibility array */
    for (i=0;i<amountOfGroupStudents;i++){
        compatibilityArray[i]=(int*)malloc(amountOfGroupStudents*sizeof(int));  
        checkMallocSuccess(compatibilityArray[i]);  /* Might remove to reduce time, probably only a second extra though */
    }
    /* Fills in compatibility array */
    fillCompatibilityArray(compatibilityArray, listOfAllStudents, listOfGroupStudents, amountOfGroupStudents, amountOfQuestions, listOfQuestionTypes);
    
    
    /* prints compatibility array, remove later */

    for (i=0;i<amountOfGroupStudents;i++){
        printf("\n");
        for (j=0;j<amountOfGroupStudents;j++){
            printf(" %2d -",compatibilityArray[i][j]);
        }
    }
    printf("\n\n\n");
    /* Remove  later */



    /* Next we need to find ideal solution */

    /* We wanna cycle through all choices, storing the current computation, we will be doing this recursively */
    


    /* It has several values
    ListOfStudentsInArray = Keeps track of students and moves them around between recursive calls, used to specfically track their place in the compatibilityArray 
    amountOfStudents = AmountOfStudents left that are still being considered in the current recursive call
    amountOfRooms = How many rooms are left till we reach bottom level, 1 room left would be amountOfRooms 0
    bestConfig = 2 dimensional array that keeps track of the best combination of people at different recursive levels of the call
    bestValue = 1 dimensional array that keeps track of best value at differing points of the array

    Compatibility array is a dimensional array of already calculated compatibility between students 

    We need to now create some of these values

    */ 
    int* listOfStudentsInArray = (int*)malloc(compatibilityArraySize*sizeof(int));  /* Create array referencing position in array */
    for (i=0;i<compatibilityArraySize;i++){
       listOfStudentsInArray[i]=i;
    }
    int** bestConfig = (int**)malloc(roomsCounter*sizeof(int*));    /* Create array that can keep track of best configurations at differing levels */
    for (i=roomsCounter;i>0;i--){
        bestConfig[i-1]=(int*)malloc(i*2*sizeof(int));
    }


    /* We will be calling this recursively*/
    // printf("\nStarting recurisve Calls!!!");


    optimize(listOfStudentsInArray, amountOfGroupStudents, roomsCounter-1, bestConfig, compatibilityArray);


    // printf("\nFinished recurisve Calls!!!\n ");

    // for (i=0;i<amountOfGroupStudents;i++){      /* Printing best config */
    //     printf(" %d |", bestConfig[roomsCounter-1][i]);
    // }

    /* Next we need to translate these results, and put people in rooms */

    for (i=0;i<roomsCounter;i++){
        for (j=0;j<groupRooms[i][0]+1;j++){
            // printf("\nAdding %d", listOfGroupStudents[bestConfig[roomsCounter-1][amountOfGroupStudents-1]]);
            listOfRoommates[groupRooms[i][0]][groupRooms[i][1]][j+1]=listOfGroupStudents[bestConfig[roomsCounter-1][amountOfGroupStudents-1]]; /* Assigns students to room */
            amountOfGroupStudents-=1;
        }
        getRoomCompatibility(listOfRoommates, listOfAllStudents, groupRooms[i], amountOfQuestions, listOfQuestionTypes);  /* Gets compatibility */
    }



    /* Free compatibility array */

    for (i=0;i<compatibilityArraySize;i++){
        free(compatibilityArray[i]);
    }
    free(compatibilityArray);

    
    /* Free rooms list */

    for (i=0;i<amountOfGroupStudents;i++){      /* Remember that amount of students has been changed in above;
        //free(groupRooms[i]);                  /* Find out why issues with 'free' command */
    }

    free(groupRooms);


    
    /* Free optimized array */

    for (i=0;i<roomsCounter;i++){
       // free(bestConfig[i]);
    }
    free(listOfStudentsInArray);
    free(bestConfig);

    printf("\nPast free hell !!!");
}

int optimize(int* ListOfStudentsInArray,int amountOfStudents, int amountOfRooms, int** bestConfig, int** compatibilityArray){
    
    if (amountOfStudents==2){   /* If only one option / at bottom layer */
        bestConfig[amountOfRooms][amountOfStudents-1]=ListOfStudentsInArray[amountOfStudents-1]; /* Sets config for best config at bottom layer to this */
        bestConfig[amountOfRooms][amountOfStudents-2]=ListOfStudentsInArray[amountOfStudents-2]; /* Sets config for best config at bottom layer to this */

        return compatibilityArray[ListOfStudentsInArray[amountOfStudents-1]][ListOfStudentsInArray[amountOfStudents-2]];  /* Returns compatibility for the two students */
    }

    else {  /* If not at bottom layer */
        int i, j;

        bestConfig[amountOfRooms][amountOfStudents-1]=ListOfStudentsInArray[amountOfStudents-1];   /* Set the first person in the array */

        int tempHolder=ListOfStudentsInArray[amountOfStudents-2];  /* Hold the second last student in the array */

  
        int currentValue;
        int bestValue=-1; /* Resets best value for level */

        // printf("\nStarting main loop with %d students!!", amountOfStudents);

        for (i=0; i<amountOfStudents-2; i++){ /* Cycling through all students left */
            ListOfStudentsInArray[amountOfStudents-2]=ListOfStudentsInArray[i];         /* Set current student to outside remaining considered students */
            ListOfStudentsInArray[i]=tempHolder;      /* Switching around student considered and student previously outside array */


            currentValue = compatibilityArray[ListOfStudentsInArray[amountOfStudents-1]][ListOfStudentsInArray[amountOfStudents-2]] +   /* Sets value to config for room, + ideal version of future rooms */
                           optimize(ListOfStudentsInArray, (amountOfStudents-2), (amountOfRooms-1), bestConfig, compatibilityArray);


            if (currentValue>bestValue){ /* If best config at this level */
                bestValue=currentValue;  /* Update optimal value */
                /* Add optimal list from last level */
                for (j=0;j<amountOfStudents-2; j++){
                    bestConfig[amountOfRooms][j]=bestConfig[amountOfRooms-1][j];
                }
                bestConfig[amountOfRooms][amountOfStudents-2]=ListOfStudentsInArray[amountOfStudents-2];  /* Add the student being considered from the above ForLoop */
            }
            ListOfStudentsInArray[i]=ListOfStudentsInArray[amountOfStudents-2]; /* Revert changes made */
            ListOfStudentsInArray[amountOfStudents-2]=tempHolder;

        }

        // printf("\n Found values at level %d  \n", amountOfRooms);
        // for (i=0;i<amountOfStudents;i++){
        //     printf(" %d |", bestConfig[amountOfRooms][i]);
        // }

        return bestValue;

    }

}



/* Used for rooms where we do not have enough students to fill them up, therefore add fillers

In this scenario it is the last group, and we need to find all remaining students, 
we don't need to find optimal pairings, as there is only 1 option


1st We find all remaining students
2nd Add them to listOfRommmates
3rd Get compatibility
4th Add compatibility
5th Free lists used in function

*/

int findRooms(int** groupRooms, int*** listOfRoommates, int* listOfGroupStudents, int amountOfGroupStudents, int* roomTypes, int maxPersonRoom, int* inUseRooms, int* roomsCounter){

    int amountOfGroupStudentsTracker = amountOfGroupStudents;
    
    /* Till all students have been allocated */
    while (amountOfGroupStudentsTracker>0){
        /* Finds roomSize */
        int roomSize = getRoomSize(amountOfGroupStudentsTracker, roomTypes, maxPersonRoom);
        
        amountOfGroupStudentsTracker -= roomSize+1;

        groupRooms[*roomsCounter][0]=roomSize;
        groupRooms[*roomsCounter][1]=inUseRooms[roomSize];  /* Already counted up in fillRoom so need reduce by 1 here */
        inUseRooms[roomSize] += 1; /* Counts an additional room being used */

        (*roomsCounter) += 1;
    }

    return(amountOfGroupStudentsTracker*-1); /* Returns amount of additional students */
}


void fillUpGroup(int* roomArray,int** compatibilityArray,int sizeOfCompatibilityArray, int amountOfGroupStudents, int roomSize, int amountOfQuestions, int* listOfGroupStudents){
    
    int i;
    int* endPair = (int*)malloc((amountOfGroupStudents)*sizeof(int));    /* Keeps track of end pair position in compatibility array NOT THEIR ID */
   
    int count=0;

    /* Find all remaining students */
    for (i=0; i<sizeOfCompatibilityArray; i++){
        if (compatibilityArray[i][i]!=-1){
            endPair[count]=i;
            count++;
        }
    }
    /* Add to actual room array with student IDs */
    for (i=0; i<amountOfGroupStudents; i++){
        roomArray[i+1]=listOfGroupStudents[endPair[i]];
    }
    /* Compatibility */
    roomArray[0]=getGroupCompatibility(endPair, (count-1), compatibilityArray, amountOfQuestions);


    /* Add filler students */
    for (i; i<roomSize+1; i++){
        roomArray[i+1]= -1; /* Adds filler */
    }

    free(endPair);
}

/* Used for rooms where we have enough students to fill up rooms

In this scenario we want to find the highest possible combination with an algoirthm, and then add them to our data


1st We find the best pairing
2nd Add them to listOfRommmates
3rd Get compatibility
4th Add compatibility
5th Free lists used in function

*/

/* Finds compatibility for group */
int getGroupCompatibility(int* roomArray, int sizeOfRoom,int** compatibilityArray,int amountOfQuestions){
    int i, j;
    int compatibility=0; /* Used to keep track of amased compatibility */
    if (sizeOfRoom==0){ /* If single person room */
        return (amountOfQuestions*4);   /* Return max score */
    }

    for (j=0;j<sizeOfRoom+1;j++){
        for (i=j+1;i<=sizeOfRoom;i++){ 
            compatibility += compatibilityArray[roomArray[i]][roomArray[j]];  /* Add compatibilities together */
        }
    }
    compatibility = compatibility/((sizeOfRoom)*(sizeOfRoom+1)/2);    /* Reduce by amount of compatibility scores */

    roomArray[0]=compatibility;

    return compatibility;
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
        /* Usually returns a minus value, however this is handled by counting the amount of extra students this procedure will take */

        return (lowestAvailableRoom);
        
    }

    else {  /* No rooms left */
        printf("\nProgram error, no more rooms avaliable. Bye!");
        exit(EXIT_FAILURE);
    }
    return i; /* Filler */
}


/* Fills compatibility array */
void fillCompatibilityArray(int** compatibilityArray,int** listOfAllStudents,int* listOfGroupStudents,int amountOfGroupStudents,int amountOfQuestions,int* listOfQuestionTypes){
    int i;  /*Vertical */
    int j;  /* Horizontal */

    for (i=0; i<amountOfGroupStudents; i++){
        for (j=0; j<i; j++){

            if (listOfGroupStudents[i] ==-1 || listOfGroupStudents[j]==-1){
                compatibilityArray[i][j]= amountOfQuestions* 4; /* Max value! */
                compatibilityArray[j][i]=compatibilityArray[i][j]; /* Since it's mirrored */
            }
            else {
                compatibilityArray[i][j]=getCompatibility(listOfAllStudents[listOfGroupStudents[i]], listOfAllStudents[listOfGroupStudents[j]],amountOfQuestions,listOfQuestionTypes);
                compatibilityArray[j][i]=compatibilityArray[i][j]; /* Since it's mirrored */
            }
        }
        compatibilityArray[i][j]=0; /* Fill diagonal with zeroes */
    }


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
            printf("\n Question %d does not have a valid question type \n", i);
            exit(EXIT_FAILURE);
        }
    }

    return compatibility;
}

int getRoomCompatibility(int*** listOfRoommates,int** listOfAllStudents, int* groupRoom, int amountOfQuestion, int* listOfQuestionTypes){

    int i, j, amountOfCompatibilities=0;

    listOfRoommates[groupRoom[0]][groupRoom[1]][0] = 0; /* Sets grouproom compatibility to zero */
    for (i=0; i<groupRoom[0]+1;i++){    /* Cycle through all students in room */
        if (listOfRoommates[groupRoom[0]][groupRoom[1]][i+1]!=-1){ /* If i not a filler student */
            for (j=i+1; j<groupRoom[0]+1;j++){  /* Cycle through all students in room */
                
                if (listOfRoommates[groupRoom[0]][groupRoom[1]][j+1]!=-1){  /* If j not filler student */


                    printf("Student 1:  %d    Student 2: %d \n", listOfRoommates[groupRoom[0]][groupRoom[1]][i+1], listOfRoommates[groupRoom[0]][groupRoom[1]][j+1]);

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
    printf("Compatibility: %d \n", listOfRoommates[groupRoom[0]][groupRoom[1]][0]);
    return listOfRoommates[groupRoom[0]][groupRoom[1]][0];
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

void createOutput(char* outputFile, char* outputDataFile, int*** listOfRoommates, int* inUseRooms, int maxRooms, int amountOfQuestions){
    int i, j, x=1, y;        /* x counts number of current room, starting from 1 */
    double averageSatisfaction = 0;         /* Sets to zero for now */

    int* scoreTracker = (int*)malloc(10*sizeof(int));   /* Used to track how many rooms have different scores */
    checkMallocSuccess(scoreTracker);

    for (i=0;i<10;i++){
        scoreTracker[i]=0;  /* Sets score to 0 */
    }

    int maxScore = amountOfQuestions * 4;   /* Finds max amount of points */

    FILE *fp = fopen(outputFile, "w");
    if (fp != NULL){
        for (j=0;j<maxRooms;j++){   /* Goes through all room sizes */
            for (i = 0; i < inUseRooms[j]; i++){    /* Goes through all rooms of size j */
                fprintf(fp, "Room %3d: %3d ",x, listOfRoommates[j][i][1]);  /* Prints first person in room */
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

    printf("\n\nSuccessfully created greedy list!!!!");

    averageSatisfaction = averageSatisfaction/(x-1);    /* reduces total satisfaction by amount of rooms */

    /* Writes data output */

    fp = fopen(outputDataFile, "w");
    if (fp != NULL){
        
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
