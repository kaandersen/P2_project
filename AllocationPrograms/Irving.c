#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h> /* Remove once actual answers can be gotten */
#include <stdbool.h>        /* Bolean values */

/*///////////////////
PROGRAM DESCRIPTION 

ONLY FOR 2 PERSON ROOMS

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

void fillCompatibilityArray(int** compatibilityArray,int** listOfAllStudents,int* listOfGroupStudents,int amountOfGroupStudents,int amountOfQuestions,int* listOfQuestionTypes);



void assignRooms(int* listOfGroupStudents,int* listOfAccept,int amountOfGroupStudents,int* inUseRooms,int* roomTypes, int*** listOfRoommates, int** compatibilityArray);


void checkForDone(int** priorityArray,int amountOfGroupStudents, int* listOfAccept, int studentNumber);
void reducePriority(int** priorityArray,int amountOfGroupStudents, int studentNumber,int secondPerson);
int findLastPerson(int** priorityArray,int amountOfGroupStudents, int studentNumber);
void deleteLeftovers(int** priorityArray,int amountOfGroupStudents, int* listOfAccept, int studentNumber);

void propose(int** priorityArray,int amountOfGroupStudents, int* listOfAccept, int studentNumber);
void proposeCross(int** priorityArray,int student1, int student2, int proposedToStudent, int* listOfAccept, int amountOfGroupStudents);

void fillPriorityArray(int** compatibilityArray,int** priorityArray,int  amountOfGroupStudents);
void bubbleSort(int arr[], int arr2[], int n);
void swap(int* xp, int* yp);
int findArrayPos(int arr[], int arraySize, int element);

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
    
    printf("\n\nGot Data!!!");
    
    group* listOfGroups = generateGroups(listOfStudents, amountOfStudents, listOfOverrulingQuestions, amountOfQuestions, listOfQuestionTypes, &amountOfGroups);      
     /*Generates dynamic associative array to refer to which student-IDs are in groups */

    printf("\n\nGot groups!!!!");

    int*** listOfRoommates = applyOptimization(listOfStudents, listOfGroups, amountOfGroups, listOfQuestionTypes, amountOfQuestions, maxPersonRoom, roomTypes, &inUseRooms);   /* The hard part */

    printf("\n\nSuccessfully created roommate list!!!!");

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
    (*roomtypes)[1]=500;    /* Only 2-person rooms */


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
    int i, j, x;

    int roomSize;
    int compatibilityArraySize = amountOfGroupStudents;

    int** compatibilityArray = (int**)malloc(amountOfGroupStudents*sizeof(int*));
    int** priorityArray = (int**)malloc(amountOfGroupStudents*sizeof(int*));    /* Keeps track of priority list, -1 means rejected */
    int* listOfAccept = (int*)malloc(amountOfGroupStudents*sizeof(int));    /* Keeps track of who each person has accepted */
    checkMallocSuccess(compatibilityArray);

    /* Creates space for compatibility array */
    for (i=0;i<amountOfGroupStudents;i++){
        compatibilityArray[i]=(int*)malloc(amountOfGroupStudents*sizeof(int));  
        checkMallocSuccess(compatibilityArray[i]);  /* Might remove to reduce time, probably only a second extra though */
    }
    /* Fills in compatibility array */
    fillCompatibilityArray(compatibilityArray, listOfAllStudents, listOfGroupStudents, amountOfGroupStudents, amountOfQuestions, listOfQuestionTypes);
    
    if (amountOfGroupStudents%2!=0){    /* Check if uneven amount of students */
        printf("\nUneven Amount of Students, Bye\n");
        exit(EXIT_FAILURE);
    }

    for (i=0; i<amountOfGroupStudents; i++){
        listOfAccept[i] = -1;                  /* Sets all students to having accepted nobody at beginning */
    }


    /* Creates space for priority array */
    for (i=0;i<amountOfGroupStudents;i++){
        priorityArray[i]=(int*)malloc(amountOfGroupStudents*sizeof(int));  
        checkMallocSuccess(priorityArray[i]);  /* Might remove to reduce time, probably only a second extra though */
    }
    /* Fills in priority array */
    fillPriorityArray(compatibilityArray, priorityArray, amountOfGroupStudents);


    /* Print priority array */
    // for (i=0; i<amountOfGroupStudents;i++){
    //     printf("\nStudent :%2d ", i);
    //     for (j=0;j<amountOfGroupStudents;j++){
    //         printf(" %2d -", priorityArray[i][j]);
    //     }
    // }
    // printf("\n\n\n");


  

    /* ALGORITHM BEGINS */



    /* Phase 1 */
    for (i=0; i<amountOfGroupStudents;i++){
        propose(priorityArray, amountOfGroupStudents, listOfAccept, i);
    }

    printf("\n Propose Phase Successfull \n");


    /* Phase Delete */
    for (i=0; i<amountOfGroupStudents;i++){
        deleteLeftovers(priorityArray, amountOfGroupStudents, listOfAccept, i);
    }

    printf("\n Delete Phase Successfull \n");

    /* Phase 2 */

    for (i=0; i<amountOfGroupStudents;i++){
        checkForDone(priorityArray, amountOfGroupStudents, listOfAccept, i);
    }

    printf("\n Only one person per room \n");

    /* Assign to rooms, a person's preffered person is in listOfAccept, also gets compatibility */

    assignRooms(listOfGroupStudents, listOfAccept, amountOfGroupStudents, inUseRooms, roomTypes, listOfRoommates, compatibilityArray);







    /* Free array */

    for (i=0;i<compatibilityArraySize;i++){
        free(compatibilityArray[i]);
    }
    free(compatibilityArray);
    for (i=0;i<compatibilityArraySize;i++){
        free(priorityArray[i]);
    }
    free(priorityArray);
    free(listOfAccept);

}

void assignRooms(int* listOfGroupStudents,int* listOfAccept,int amountOfGroupStudents,int* inUseRooms,int* roomTypes, int*** listOfRoommates, int** compatibilityArray){
    int i, roomSize=1; /* We only use roomsize 2 for this algorithm */


    for (i=0; i<amountOfGroupStudents;i++){
        if (listOfAccept[i]!=-1){    /* If not marked as already used */
            if (roomTypes[roomSize]>0){ /* If more rooms avaliable */


                listOfRoommates[roomSize][inUseRooms[roomSize]][1]=listOfGroupStudents[i];    /* Assigns students to room */
                listOfRoommates[roomSize][inUseRooms[roomSize]][2]=listOfGroupStudents[listOfAccept[i]];

                listOfRoommates[roomSize][inUseRooms[roomSize]][0]=compatibilityArray[i][listOfAccept[i]]; /* Finds compatibility */

                inUseRooms[roomSize]+=1;        /* Updates amount of rooms in use and remaining */
                roomTypes[roomSize]-=1;



                listOfAccept[listOfAccept[i]]=-1;   /* Sets other list of accept to be blank, so no duplicate rooms */



            }
            else{
                printf("\n No more two person rooms avaliable. Bye. \n");
                exit(EXIT_FAILURE);
            }
        }
    }



}



void checkForDone(int** priorityArray,int amountOfGroupStudents, int* listOfAccept, int studentNumber){
    int i, count=0;

    for (i=0;i<amountOfGroupStudents;i++){
        if (priorityArray[studentNumber][i]!=-1){   /*  Counts all not rejected */
            count++;
            listOfAccept[studentNumber]=priorityArray[studentNumber][i]; /* Stores who the person found is */

            if (count>1){   /* If more than one rejected */

                printf("\n\n STARTING REDUCTION THINGY \n\n");

                reducePriority(priorityArray, amountOfGroupStudents, studentNumber, listOfAccept[studentNumber]);
                count=0;
                i=0;
            }
        }
    }
}

void reducePriority(int** priorityArray,int amountOfGroupStudents, int studentNumber,int secondPerson){
    int j, i=1;
    int* list = (int*)malloc(amountOfGroupStudents*sizeof(int));
    /* Create list */
    list[0]=studentNumber;  
    list[1]=secondPerson;
    while (list[i]!=studentNumber)
    {
        i++;
        list[i]=findLastPerson(priorityArray, amountOfGroupStudents, list[i-1]);   
        
    }

    /* Delete from list */
    for (j=2; j<i+1; j+=2){
        priorityArray[list[j-1]][list[j]]=-1;
        priorityArray[list[j]][list[j-1]]=-1;
    }

    free(list);
}

int findLastPerson(int** priorityArray,int amountOfGroupStudents, int studentNumber){
    int i;

    for (i=studentNumber-1; i>=0; i--){
        if (priorityArray[studentNumber][i]!=-1){
            return(priorityArray[studentNumber][i]);
        }
    }

    printf("\n Deleted entire priority array \n");
    exit(EXIT_FAILURE);
}

void deleteLeftovers(int** priorityArray,int amountOfGroupStudents, int* listOfAccept, int studentNumber){
    int i, studentPos;
    int deleteAll = false;

    for (i=0;i<amountOfGroupStudents;i++){
        if (priorityArray[studentNumber][i]==studentNumber){        /* If reached self */
            priorityArray[studentNumber][i]=-1; /* Set number to denied */
        }

        else if (deleteAll==true && priorityArray[studentNumber][i]!=-1){ /* If deltee on and not already rejected */
            studentPos = findArrayPos(priorityArray[priorityArray[studentNumber][i]], amountOfGroupStudents, studentNumber);    /* Find pos in to be rejected array */
            
            priorityArray[priorityArray[studentNumber][i]][studentPos]=-1; 
            priorityArray[studentNumber][i]=-1; /* Set number to denied */


        }
        else if (listOfAccept[studentNumber]==priorityArray[studentNumber][i]){   /* Once accepted proposal person is reached, delete all afterwards */
            deleteAll=true;
        }
    }
}



void propose(int** priorityArray,int amountOfGroupStudents, int* listOfAccept, int studentNumber){
    int i;
    int done=false;

    for (i=0; i<amountOfGroupStudents-1 && done==false; i++){

        if (priorityArray[studentNumber][i]!=-1){   /* If not rejected */
            if (listOfAccept[priorityArray[studentNumber][i]]==-1){ /* If not already proposed to */
                listOfAccept[priorityArray[studentNumber][i]]=studentNumber;
                done=true;
            }
            else {          /* If not already proposed to */
                proposeCross(priorityArray, studentNumber, listOfAccept[priorityArray[studentNumber][i]], priorityArray[studentNumber][i], listOfAccept, amountOfGroupStudents);
                done=true;
            }
        }

    }

    /* If been rejected by everyone */
    if (done==false){
        printf("\n Student ran out of people to propose to. Bye \n");
        exit(EXIT_FAILURE);
    }
}

void proposeCross(int** priorityArray,int student1, int student2, int proposedToStudent, int* listOfAccept, int amountOfGroupStudents){
    int i;
    for (i=0; i<amountOfGroupStudents;i++){
        if (priorityArray[proposedToStudent][i]==student1){ /* If first person is student 1, */
            
            listOfAccept[proposedToStudent]=student1;
            
            /* rejection part */
           

            int student2Pos=findArrayPos(priorityArray[proposedToStudent], amountOfGroupStudents, student2); /* Finds rejected persons pos */


            priorityArray[proposedToStudent][student2Pos]=-1;

            int proposedToStudentPos=findArrayPos(priorityArray[student2], amountOfGroupStudents, proposedToStudent);  /* Finds pos in rejected person's array */


            priorityArray[student2][proposedToStudentPos]=-1;

            propose(priorityArray, amountOfGroupStudents, listOfAccept, student2);  /* Student must propose to someone new */


            /* End loop */
            i = amountOfGroupStudents;
        }
        else if (priorityArray[proposedToStudent][i]==student2){ /* If first person is student 2,  */
            
            listOfAccept[proposedToStudent]=student2;
            
            /* rejection part */

            int student1Pos=findArrayPos(priorityArray[proposedToStudent], amountOfGroupStudents, student1); /* Finds rejected persons pos */


            priorityArray[proposedToStudent][student1Pos]=-1;
            
            int proposedToStudentPos=findArrayPos(priorityArray[student1], amountOfGroupStudents, proposedToStudent); /* Finds pos in rejected person's array */


            priorityArray[student1][proposedToStudentPos]=-1;

            propose(priorityArray, amountOfGroupStudents, listOfAccept, student1);  /* Student must propose to someone new */



            /* End loop */
            i = amountOfGroupStudents;
        }
    }
}



void fillPriorityArray(int** compatibilityArray,int** priorityArray,int  amountOfGroupStudents){

    int i, j, counter=0;
    
    /* Need copy of compatibility array */
    int* compatibilityArray2 = (int*)malloc(amountOfGroupStudents*sizeof(int));
    checkMallocSuccess(compatibilityArray2);



    for (i=0; i<amountOfGroupStudents; i++){    /* Generate student compatibility list */
        for (j=0; j<amountOfGroupStudents; j++){    /* Take each other student */
            priorityArray[i][j]=j;  /* Set value to  */
            compatibilityArray2[j]=compatibilityArray[i][j];
        }
        bubbleSort(compatibilityArray2, priorityArray[i], amountOfGroupStudents);
    }

    free(compatibilityArray2);

}
/* Stolen from https://www.geeksforgeeks.org/bubble-sort/ */
void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
/* Stolen from https://www.geeksforgeeks.org/bubble-sort/ */
void bubbleSort(int arr[], int arr2[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++){
 
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++){
            if (arr[j] < arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
                swap(&arr2[j],&arr2[j + 1]);
            }
        }
    }
}

int findArrayPos(int arr[], int arraySize, int element){
    int i;
    for (i=0;i<arraySize;i++){
        if (arr[i]==element){
            return(i);
        }
    }
    printf("Could not find element %d. Bye.", element);
    exit(EXIT_FAILURE);
    return(-1);
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
