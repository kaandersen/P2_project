//Global variables
var _buttonNameIndex = 1;
var _questionaireIndex = 1;
var _questionaireEditIndex = 1;
var questionsArray = [];
var counter = 0;




function createQuestionaire() {
    window.location.href="/";
}



//When a questionaire is saved a button is created 
function savingQuestionaireBtns() {
 
  //sets local storage to an variable
  var newArr = JSON.parse(window.localStorage.getItem('WrapperID'));
  //creates the edit button, that lets the admin edit an questionnaire
  for (var i = 0; i < newArr.length; i++) {
  
    btnEditListContainer = document.getElementById("btn-edit-list-wrapper")
    var editQuestionaireBtn = document.createElement("button");
    editQuestionaireBtn.innerHTML = "Edit";
    editQuestionaireBtn.setAttribute("id",""+ newArr[i]);
    editQuestionaireBtn.setAttribute("questionairebtnid",""+ _questionaireEditIndex++);
    editQuestionaireBtn.setAttribute("class","editBtnClass"); 
    editQuestionaireBtn.name ="editBtns";
  
    btnEditListContainer.appendChild(editQuestionaireBtn);
  }

  //Button that can edit a previously existing questionnaire
  btnEditListContainer.addEventListener('click', (event) => {
    localStorage.btnID = event.target.id;
    localStorage.SelectedBtnID = event.target.getAttribute('questionairebtnid')
    window.location.href="/Edit";
    console.log(event.target.id)
  })

}
  
savingQuestionaireBtns();