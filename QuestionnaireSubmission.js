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


/** 
 * lav object
 * 
 * se om jeg kan printe just to check
 * 
 * see if I can add elements to the object 
 * 
 * store the objects to textfiles 
 * 
 */






/* Test writing a text file */
import { readFile, writeFile } from 'fs';
import {Submit} from 'SampleForm.html';

document.getElementById("Submit").addEventListener("submit", submitCall);


/* Test Reading a text file */
readFile('DemoRead.txt', 'utf8', function(err, data){
      
    // Display the file content
    console.log(data);
});

/* Test writing a text file */
const content = "conecting";

writeFile('DemoWrite.txt', content, err => {
    if(err){
        console.err;
        return;
    }    
});



