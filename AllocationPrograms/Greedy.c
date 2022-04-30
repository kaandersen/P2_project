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
void fillUpGroup(int* roomArray,int** compatibilityArray,int sizeOfCompatibilityArray, int amountOfGroupStudents, int roomSize, int amountOfQuestions, int* listOfGroupStudents);
void clearRow(int clearValue, int** compatibilityArray,int compatibilityArraySize);
void getPairings(int** listOfRooms,int sizeOfRoom,int** compatibilityArray, int sizeOfCompatibilityArray, int* inUseRooms, int amountOfQuestions,int* listOfGroupStudents);



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
    
    group* listOfGroups = generateGroups(listOfStudents, amountOfStudents, listOfOverrulingQuestions, amountOfQuestions, listOfQuestionTypes, &amountOfGroups);      
     /*Generates dynamic associative array to refer to which student-IDs are in groups */

    int*** listOfRoommates = applyOptimization(listOfStudents, listOfGroups, amountOfGroups, listOfQuestionTypes, amountOfQuestions, maxPersonRoom, roomTypes, &inUseRooms);   /* The hard part */

    printf("\n\nSuccessfully created greedy list!!!!");

    /* free values */
    freeValues(listOfStudents, roomTypes, listOfQuestionTypes, listOfOverrulingQuestions, amountOfStudents);

    /* Print output */
    createOutput("AllocationPrograms/output.txt", "AllocationPrograms/outputData.txt", listOfRoommates, inUseRooms, maxPersonRoom, amountOfQuestions); /* Prints the results */


    printf("Program Finished Successfully");

    return EXIT_SUCCESS;
}   
/* Frees all the lists */
void freeValues(int** listOfStudents,int* roomTypes,int* listOfQuestionTypes,int* listOfOverrulingQuestions,int amountOfStudents){
    int i;
    free(roomTypes);
    free(listOfQuestionTypes);
    free(listOfOverrulingQuestions);

    for (i=0;i<amountOfStudents;i++){
        free(listOfStudents[i]);
    }
    free(listOfStudents);
}

void getQuestionnaireInfoTemp(char* inputFile, int* amountOfStudents, int* amountOfQuestions, int** listOfQuestionTypes, int** listOfOverrulingQuestions,int* maxPersonRoom, int** roomtypes){

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
    *maxPersonRoom=2;        /* Serves as a constant variable */
    *roomtypes = (int*)malloc(*maxPersonRoom*sizeof(int));
    for (i=0; i<*maxPersonRoom;i++){
        (*roomtypes)[i]=0;                /* Sets a base value for testing */
    }
    (*roomtypes)[1]=1200;    /* Only 2-person rooms */


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
        // printf("GetRoommate Success");
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

    int roomSize;
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

    // for (i=0;i<amountOfGroupStudents;i++){
    //     printf("\n");
    //     for (j=0;j<amountOfGroupStudents;j++){
    //         printf(" %2d -",compatibilityArray[i][j]);
    //     }
    // }
    // printf("\n\n\n");
    /* Remove  later */

    /* Starts allocating group */
    while (amountOfGroupStudents>0){
           /* Find appropriate room size */
        roomSize = getRoomSize(amountOfGroupStudents, roomTypes, maxPersonRoom);

            /* Find optimal pair for room size */

        if (roomSize>=0){
            getPairings(listOfRoommates[roomSize],roomSize,compatibilityArray,compatibilityArraySize, inUseRooms, amountOfQuestions, listOfGroupStudents);
            amountOfGroupStudents -= roomSize+1;
            inUseRooms[roomSize] += 1;
        }
        else {  /* If need to fill up group with artificial people, this is the last group */
                /* We figure this out by this value being negative, we can just reverse it to find the desired room type though */

            /* Find remaining students */
            roomSize = roomSize * -1; /* Reverts roomsize from minus */
            fillUpGroup(listOfRoommates[roomSize][inUseRooms[roomSize]],compatibilityArray, compatibilityArraySize, amountOfGroupStudents, roomSize, amountOfQuestions, listOfGroupStudents);
          

            amountOfGroupStudents = 0;
            inUseRooms[roomSize] += 1;


        }   
        /* Remove later */
        /* Remove later */
        /* Remove later */
        /* Remove later */
        /* Remove later */
        /* Remove later */
        /* Remove later */
        /* Remove later */
        /* Remove later */
        /* Remove later */

        // for (i=0;i<compatibilityArraySize;i++){
        //     printf("\n");
        //     for (j=0;j<compatibilityArraySize;j++){
        //         if (compatibilityArray[i][j]!=-1){
        //             printf(" %2d -",compatibilityArray[i][j]);
        //         }
        //         else{
        //             printf("    -");
        //         }
        //     }
        // }
        // printf("\n\n\n");
        /* Remove later */
        /* Remove later */
        /* Remove later */
        /* Remove later */
        /* Remove later */
        /* Remove later */
        /* Remove later */

    }




    /* Free array */

    for (i=0;i<compatibilityArraySize;i++){
        free(compatibilityArray[i]);
    }
    free(compatibilityArray);

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

void getPairings(int** listOfRooms,int sizeOfRoom,int** compatibilityArray, int sizeOfCompatibilityArray, int* inUseRooms, int amountOfQuestions,int* listOfGroupStudents){
    int highestChoiceValue=-1;
    int currentPickValue;
    int amountOfCurrentPicks;


    int* endPair = (int*)malloc((sizeOfRoom+1)*sizeof(int));    /* Keeps track of end pair position in compatibility array NOT THEIR ID */
    checkMallocSuccess(endPair);
    int i, j, done;

    if (sizeOfRoom==0){/* If only 1 person-room, in this scenario there are only 1 person rooms left */
        /* Find any avaliable person */
        done = 0;
        for (i=1; i<sizeOfCompatibilityArray && done==0;i++){
            if (compatibilityArray[i][i]!=-1){  /* Checks if person is already picked, picked people have -1 */
                done=1;
                endPair[0]=i;
            }
        }

    }

    /* Find first pairings */  
    else {
        for (i=0; i<sizeOfCompatibilityArray;i++){
            for (j=0; j<i;j++){
                if (compatibilityArray[i][j]>highestChoiceValue){    /* Check through all options */
                    highestChoiceValue=compatibilityArray[i][j];     /* If above previous highest value set to new max */
                    endPair[0]=i;
                    endPair[1]=j;
                }
            }
        }


        /* Find additional pairings for rooms sized 3 and higher*/
        if (sizeOfRoom>1){
            highestChoiceValue=0;

            for (amountOfCurrentPicks=2; amountOfCurrentPicks<sizeOfRoom+1;amountOfCurrentPicks++){
                for (i=0;i<sizeOfCompatibilityArray;i++){   /* Goes through all students in list */
                    currentPickValue=0;
                    
                    for (j=0;j<amountOfCurrentPicks;j++){   /* Look through compatibility with all memebers currently in group */
                        if (i==endPair[j]){  /* If already in group we go to next student */
                            currentPickValue=-1; /* Makes it impossible to be assigned */
                            j=amountOfCurrentPicks; /* Stops loop */
                        }
                        else {
                            currentPickValue += compatibilityArray[i][endPair[j]];
                        }
                    }
                    if (currentPickValue>highestChoiceValue){  /* If new highest combination */
                        highestChoiceValue=currentPickValue;
                        endPair[amountOfCurrentPicks]=i;    
                    }
                }
            }
            
        }
    }
    /* Assign pairings to actual roommate array HERE WE APPLY STUDENT ID*/
    for (i=0; i<sizeOfRoom+1; i++){
        listOfRooms[inUseRooms[sizeOfRoom]][i+1]=listOfGroupStudents[endPair[i]];
    }   
    /* Get compatibility */
    listOfRooms[inUseRooms[sizeOfRoom]][0]=getGroupCompatibility(endPair,sizeOfRoom, compatibilityArray,amountOfQuestions);


    /* Clear values in compatibility array, which means setting their values to -1 
    This is so they do not get picked in the future */
    for (i=0; i<sizeOfRoom+1; i++){
        clearRow(endPair[i],compatibilityArray, sizeOfCompatibilityArray);
    }

    /* free values */
    free(endPair);
}

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

    return compatibility;
}
/* Sets all values for a given row to -1, symbolling this person has been picked */
void clearRow(int clearValue, int** compatibilityArray,int compatibilityArraySize){
    int i;

    for (i=0;i<compatibilityArraySize;i++){
        compatibilityArray[clearValue][i]=-1;
        compatibilityArray[i][clearValue]=-1;
    }
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


/* Fills compatibility array */
void fillCompatibilityArray(int** compatibilityArray,int** listOfAllStudents,int* listOfGroupStudents,int amountOfGroupStudents,int amountOfQuestions,int* listOfQuestionTypes){
    int i;  /*Vertical */
    int j;  /* Horizontal */

    for (i=0; i<amountOfGroupStudents; i++){
        for (j=0; j<i; j++){

            compatibilityArray[i][j]=getCompatibility(listOfAllStudents[listOfGroupStudents[i]], listOfAllStudents[listOfGroupStudents[j]],amountOfQuestions,listOfQuestionTypes);
            compatibilityArray[j][i]=compatibilityArray[i][j]; /* Since it's mirrored */

        }
        compatibilityArray[i][j]=-2; /* Fill diagonal with zeroes */
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


    averageSatisfaction = averageSatisfaction/(x-1);    /* reduces total satisfaction by amount of rooms */

    /* Writes data output */

    fp = fopen(outputDataFile, "w");
    if (fp != NULL){
        
        fprintf(fp, "\nAverageSatisfaction: %lf \n", averageSatisfaction);

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
