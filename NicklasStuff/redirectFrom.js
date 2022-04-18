window.addEventListener("load", checkForQuestionnaire);

/*Checks whether there already exists a questionnaire, 
if there does, a link will appear which will lead you to the dit / finish pages. 
If none exists you will have the ability to create a new questionnaire.*/
function checkForQuestionnaire() {
    //Temporary code for deciding the existance of a questionnaire.
    let existance = true;
    localStorage.existance = JSON.stringify(existance);
    let exists = JSON.parse(localStorage.existance);

    //Creates a link to continue working based on the existance of a questionnaire. 
    let a = document.createElement('a');
    let linkText;
    if (exists===true) {
        linkText = document.createTextNode("Continue working on questionnaire");
        a.appendChild(linkText);
        a.title = "Continue";
        a.href = "./P2HTML_continue.html";
        document.body.appendChild(a);
    } else {
        //Creates a link to create a new questionnaire based on the existance of a questionnaire. 
        linkText = document.createTextNode("Create new questionnaire");
        a.appendChild(linkText);
        a.title = "Create new";
        a.href = "./new.html";
        document.body.appendChild(a);
    }
}
