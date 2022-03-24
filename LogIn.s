/* Node.js stuff*/
import {readFileSync} from 'fs';//


function studentLogIn(){
    /* inputValue stores the inputtet value*/
    let inputValue = document.getElementById("studentID").value
    compareID(inputValue, "studentID.txt");
}

function adminLogIn(){
    let inputValue = document.getElementById("adminID").value
    compareID(inputValue, "adminID.txt");
}

function compareID(inputValue, key){
    
    let list;
    list = readFileSync(key, 'utf-8');
    console.log(list);
    /* Open up the correct file, with the key */
    /* Option 1: make a matrix that stores all key ID*/
    /* Option 2: make comparison for each line*/

    
}
