/* ***************************************************************************************************************
*   Library for reading and writing files
* 
**************************************************************************************************************** */
export {fileReader, processFile, Student}
const path = require("path");
const fs = require("fs");

//pathname of the desired text file
const pathname = 'fs-demo\\DemoRead.txt';

/* Reading a text file */
function fileReader(pathname){
    let data = fs.readFileSync(path.join(__dirname, pathname), 'utf-8', function read(err, data) {
        if (err) {
            /**in case of error */
            throw err; 
        }
    });
    console.log(data); //test
    return data;
}

// let data = fs.readFileSync(path.join(__dirname, pathname), 'utf-8', function read(err, data) {
//     if (err) {
//         /**in case of error */
//         throw err; 
//     }
// });
// console.log(data); //test

processFile(data);

/** Processes the content from the .txt file into an array without the data seperators */
function processFile(data) {
    //https://www.w3schools.com/jsref/jsref_split.asp
    //https://www.w3schools.com/js/js_string_methods.asp
    let numQuestions;

    /**splits the incomming data into an array */
    let dataArray = data.split(/\r\n/g);

    numQuestions = parseInt(dataArray[0]); //test: if the first element indicates how many questions there are
    //console.log(dataArray);//test

    return dataArray;
}

/**
 * The Object constructor; can be used to create a student object
 * that that stores the students id, and answers.
 */
function Student(studentID){
    /* stores the student id */ 
    this.id = studentID;
    this.gender = '';

    /* question storage by question num/id (i.e. string? example: "q1"), stores number of answers as int, stores answer options as an array, stores student answer*/
    this.storeQuestion = function(questionID, studentAnswer){
        this.questionID = questionID;
        this.studentAnswer = studentAnswer;
    }
};


/**
 * Reads the student ID, and the student answers for each question, load into a Student object containing properties
 * studentID: xxx, 
 * answers: []
*/
function studentResponse(/**WIP*/){



    //-----------WIP---------------



}


/**
 * Question Object constructor; stores the questions and their answer options
 */
function Questions(/**WIP*/){
   

    //-----------WIP---------------


 
}


