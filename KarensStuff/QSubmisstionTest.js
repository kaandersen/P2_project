import {fileReader, processFile, Student, Questions} from "./QuestionnaireSubmission2.js"

const pathname = 'fs-demo\\DemoRead.txt';/**temporary relative path, replace with student answers*/

const data = fileReader(pathname); //stores the data from the txt file

processFile(data); // processes the data into an array

let student1 = new Student(12345); // creates a Student obj

student1.storeQuestion(1, 3); //appends a student answer to the student obj
