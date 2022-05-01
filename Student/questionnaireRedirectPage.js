window.addEventListener('load', (event) => {
    console.log('page is fully loaded');
    checkForQuestionnaire();
});

const AFFIRMATIVE = "Get started by clicking the \"Go to questionnaire\" button. Please remember to fill out the best of your ability. Remember to save when finished.";
const DISSENT = "*Crickets*... It seems that there are currently no available questionnaire available";

function checkForQuestionnaire() {
    let status = true;
    let textAffirm = document.createTextNode(AFFIRMATIVE);
    let textDissent = document.createTextNode(DISSENT);

    let p = document.createElement("p");
    p.className = "text-content";

    let button = document.createElement("a");
    let linkText = document.createTextNode("Start Questionnaire");
    button.appendChild(linkText);
    button.className = "redirection-to-quest-editor";
    button.title = "Start Questionnaire";
    
    button.href = "./temptQeustionnaireEditor.html"; //insert the link to Elias's page where the student can answer the questionnaire

    let contentDiv = document.getElementById("content");

    if(status){ //if the questionnaire has been published
        p.appendChild(textAffirm);
        contentDiv.appendChild(p); 
        contentDiv.appendChild(button);

    } else { //if there is no questionnaire published
        p.appendChild(textDissent);
        contentDiv.appendChild(p); 
    }
    
}




