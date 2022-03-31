//// Import this file in the header of the respective code file to access these finctions when dececting the "SUBMIT" button   ////

/*
*   This Code initializes when the students has filled out the questionnaire and presses the "SUBMIT" button
*   
*   - Find / note down the student's ID and save it together with the student's answers and Questions
*
*   - (A function for checking whether all of the Questionnaire Qs have been filled out, must be dynamic)
*
*   - Ability to store all of the student's answers relative to the questions asked into an object(struct) (along with their ID)
* 
*   - Create the possibility of accessing the data that was filled out, so that the student can edit their answers
*/

/**Empty object that stores all the questions and their answers as an array each*/
let questionObj = {};

/**Read input from txt file (or whatever), into an array of questions, and an array of answer options */
function questionFormatter(/**WIP*/){
    let questionList = [];
    let answerList = [];



    //-----------WIP---------------



    
    questionAppend(questionList, answerList);
}

/**adds an array of question promps and an array of answer possibilities into the questions Object as properties */
function questionAppend(questionList, answerList){
    questionObj.promts = questionList;
    questionObj.answers = answerList;

    /**adds the elements from a list as new properties individually to the questionObj */
    // for(let i in questionList){
    //     questions['question'+i] += questionList[i];
    // }
}

//test run with sample arrays
questionAppend(['How old are you?', 'Where are you from?', 'What is your major?'], [[20,21,21],['aalborg', 'kbh', 'aarhus'],['math', 'arts', 'phsyical']])
console.log(questionObj);


/**Reads the student ID, and the student answers for each question, load into a Student object containing properties
 * studentID: xxx, 
 * answers: []
*/
function studentResponse(/**WIP*/){



    //-----------WIP---------------



}

/**Student object constructor function */
function Student(studentID){
    this.id = studentID;

    this.answers = function(){







        //this should result in an array of the student's answers
    }
}

let sampleStudent = new Student(12345);
sampleStudent.answers();

// data passed to Frederik = student id, answers in chronological order 


/***************************** sample obj constructor ********************************/
// function Circle(radius){
//     this.radius = radius;
//     this.draw = function(){
//         console.log('draw');
//     } 
// }

// const circle = new Circle(5);
// circle.draw();


/*******************************************************************************************************************************************************/

/**
 * The Object constructor function can be used to create a student object
 * that that stores the students id, and answers.
 */
// function Student(studentID){
//     /* stores the student id */ 
//     this.id = studentID;

//     /* question sorage by question num/id (i.e. string? example: "q1"), stores number of answers as int, stores answer options as an array, stores student answer*/
//     this.storeQuestion = function(QuestionID, numAnswers, answerOptions, studentAnswer){
//         this.QuestionID = [numAnswers, answerOptions, studentAnswer]
//     }
// };

// function Student(studentID){
//     this.id = studentID;
//     this.storeQuestion = function(newValue){
//         this.newValue = "grass";
//     }
    
// }

// let student1 = new Student(12345);
// student1.storeQuestion("q1", 3, ["yes", "no", "maybe"], 2);

// console.log(student1);
