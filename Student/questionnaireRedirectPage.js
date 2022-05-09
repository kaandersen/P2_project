//Global variables
//var _IDIndex = 1;
var _buttonNameIndex = 1;
var _questionaireIndex = 1;





function createQuestionaire() {
    window.location.href="/";
}



//When a questionaire is saved a button is created 
function savingQuestionaireBtns() {
 
  //sets local storage to an variable
  var newArr = JSON.parse(window.localStorage.getItem('WrapperID'));


  
  //loop through local storage items and create button for each item
  for (var i = 0; i < newArr.length; i++) {
      

    btnListContainer = document.getElementById("btn-list-wrapper")
    var createQuestionaireBtn = document.createElement("button");
    createQuestionaireBtn.innerHTML = "Questionaire "+_buttonNameIndex++;
    createQuestionaireBtn.setAttribute("id",""+ newArr[i]);
    createQuestionaireBtn.setAttribute("questionairebtnid",""+ _questionaireIndex++);
    createQuestionaireBtn.setAttribute("class","QuestionaireBtnClass");
    createQuestionaireBtn.name ="renderBtn";
  
    btnListContainer.appendChild(createQuestionaireBtn);

    console.log(createQuestionaireBtn.id);

  }



  //Selects individual button
  btnListContainer.addEventListener('click', (event) => {
    localStorage.btnID = event.target.id;
    localStorage.SelectedBtnID = event.target.getAttribute('questionairebtnid')
    let csv = getCsvData();
    console.log(csv);
    window.location.href="/Selected";
    
  })

}
  
savingQuestionaireBtns();










 


/*window.addEventListener('load', (event) => {
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
    
}*/




