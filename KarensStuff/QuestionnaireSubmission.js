//// Import this file in the header of the respective code file to access these finctions when dececting the "SUBMIT" button   ////

/*
*   This Code initializes when the students has filled out the questionnaire and pressed the "SUBMIT" button
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
//import { readFile, writeFile } from 'fs';
export {questionfileReader, processFile, questionAppend};
const fs = require('fs');
const path = require("path");

const localpath = 'KarensStuff\\fs-demo\\DemoRead.txt'; /**temporary relative path, replace with student answers*/
questionfileReader(localpath);

//function Question(){};
let questionObj = {};

/**
 * Takes a relative path to a textfile and reads the content
 * Calls the processFile function
 */
 function questionfileReader(filepath){
    fs.readFileSync(path.join(__dirname, filepath), 'utf8', function read(err, data) {
        if (err) {
            throw err;
        }

        // Invoke the Process file function
        processFile(data);   // Or put the next step in a function and invoke it
        //return data;
    });
}

/**Processes the content from the .txt file into an array of questions, and an array of answer options */
//https://www.w3schools.com/jsref/jsref_split.asp
//https://www.w3schools.com/js/js_string_methods.asp
function processFile(data) {
    let questionList = []; let answerList = [];
    let numQuestions; let i; let answerIndex;

    /**splits the incomming data into an array */
    let dataArray = data.split(/\r\n/g);
    //console.log(dataArray);

    numQuestions = parseInt(dataArray[0]);

    /**loads all of the questions into an array, assuming that they're at the beginning of the txt file */
    for(i = 1; i <= numQuestions; i++){
        questionList[i] = dataArray[i];
        //console.log(questionList[i]); //test
    }


    answerIndex = numQuestions+1; //in order to skip the elements loaded into questionlist already

    /**loads all of the answers into an array, assuming that they're at the end of the txt file */
    for(i = 0; answerIndex+i < dataArray.length; i++){
        answerList[i] = dataArray[answerIndex+i];
        //console.log(answerList[i]);// test 
    }
    
    //questionAppend(questionList, answerList); //appends the question and answer arrays to the questionObj
    return dataArray;
}

/**adds an array of question promps and an array of answer possibilities into the questions Object as properties */
function questionAppend(questionList, answerList){
    questionObj.promts = questionList;
    questionObj.answers = answerList;
}


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

// let sampleStudent = new Student(12345);
// sampleStudent.answers();

// data passed to Frederik = student id, answers in chronological order 





/***************************** practice ************************************************************************************************************/

/**adds the elements from a list as new properties individually to the questionObj */
    // for(let i in questionList){
    //     questions['question'+i] += questionList[i];
    // }

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
