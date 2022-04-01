import {questionfileReader, processFile, questionAppend} from "./QuestionnaireSubmission.js"
import { readFile, writeFile } from 'fs';

// "./yatzy-site-game-control.js" 
const localpath = 'fs-demo\DemoRead.txt'; /**temporary relative path, replace with student answers*/

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