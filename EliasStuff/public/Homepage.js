//Global variables
//var _IDIndex = 1;
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

    btnEditListContainer = document.getElementById("btn-edit-list-wrapper")
    var deleteQuestionaireBtn = document.createElement("button");
    deleteQuestionaireBtn.innerHTML = "Edit";
    deleteQuestionaireBtn.setAttribute("id",""+ newArr[i]);
    deleteQuestionaireBtn.setAttribute("questionairebtnid",""+ _questionaireEditIndex++);
    deleteQuestionaireBtn.setAttribute("class","deleteBtnClass");
    deleteQuestionaireBtn.name ="deleteBtns";
  
    btnEditListContainer.appendChild(deleteQuestionaireBtn);

  }


  //Selects individual button
  btnListContainer.addEventListener('click', (event) => {
    localStorage.btnID = event.target.id;
    localStorage.SelectedBtnID = event.target.getAttribute('questionairebtnid')
    let csv = getCsvData();
    console.log(csv);
    window.location.href="/Selected";
    
  })

  btnEditListContainer.addEventListener('click', (event) => {
    localStorage.btnID = event.target.id;
    localStorage.SelectedBtnID = event.target.getAttribute('questionairebtnid')
    window.location.href="/Edit";
    console.log(event.target.id)
  })

}
  
savingQuestionaireBtns();










 







/*
Object.keys(localStorage).forEach(function(key, index, array){
  console.log(localStorage.getItem(key));
  console.log(index);
});




var newArr = JSON.parse(window.localStorage.getItem('WrapperID'));

for (var i = 0; i < newArr.length; i++) {
  var storedValue = newArr[i] - 1;
  console.log(storedValue);
}*/





/*  var buttonsData = [];
  var button = event.target;
  if (buttonsData[button.id] === undefined)
   {
      // If undefined initialize to an empty array
        buttonsData[button.id] = [];
   }
   
   buttonsData[button.id].push(event.target.id);

   console.log(`${button.id} clicked....`);
   // displayData()
       

   console.log(buttonsData);
*/