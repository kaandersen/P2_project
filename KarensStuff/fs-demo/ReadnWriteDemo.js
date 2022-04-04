/* ***************************************************************************************************************
*   Example of reading and writing local .txt files
* 
**************************************************************************************************************** */

/* Test writing a text file */
//import { readFile, writeFile } from 'fs';
const path = require("path");
const fs = require("fs");
/* Test Reading a text file */
data = fs.readFileSync(path.join(__dirname, 'DemoRead.txt'), 'utf-8');
console.log(data);

const content = "banan";

// fs.writeFile('fs-demo\\DemoWrite.txt', content, err => {
//     if(err){
//         console.err;
//         return;
//     }    
// });
