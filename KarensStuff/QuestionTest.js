import {questionfileReader, processFile, questionAppend} from "./QuestionnaireSubmission.js"

const path = require("path");
const fs = require('fs');

const localpath = 'KarensStuff\fs-demo\DemoRead.txt'; /**temporary relative path, replace with student answers*/

Question(localpath);

function Question(path){
    let data = [];
    data = questionfileReader(path);

    console.log(data);

    // let testList =  processFile(data);

    // for(let i in testList){
    //     console.log(i);
    // }
    
}