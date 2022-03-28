/* ***************************************************************************************************************
*   Example of reading and writing local .txt files
* 
**************************************************************************************************************** */

/* Test writing a text file */
import { readFile, writeFile } from 'fs';

/* Test Reading a text file */
readFile('fs-demo\\DemoRead.txt', 'utf8', function(err, data){
      
    // Display the file content
    console.log(data);
});

/* Test writing a text file */
const content = "banan";

writeFile('fs-demo\\DemoWrite.txt', content, err => {
    if(err){
        console.err;
        return;
    }    
});
