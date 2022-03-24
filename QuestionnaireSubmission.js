//// Import this file in the header of the respective code file to access these finctions when dececting the "SUBMIT" button   ////

/*
*   This Code initializes when the students has filled out the questionnaire and presses the "SUBMIT" button
*   
*   - Attatch the student's ID to the answer's they have submitted
*
*   - A function for checking whether all of the Questionnaire Qs have been filled out, must be dynamic
*
*   - Ability to store all of the student's answers relative to the questions asked into an object(struct)
* 
*   - Create the possibility of accessing the data that was filled out, so that the student can edit their answers
*/

// the fs.readFile() method
// Include fs module
import { readFile, writeFile } from 'fs';

/* Test Reading a text file */
readFile('DemoRead.txt', 'utf8', function(err, data){
      
    // Display the file content
    console.log(data);
});

console.log('readFile called'); //Affirmation


/* Test writing a text file */
const content = "ayaya";

writeFile('DemoWrite.txt', content, err => {
    if(err){
        console.err;
        return;
    }    
});

