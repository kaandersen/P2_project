//Global variable
var _questionaireIndex = 1;


function createQuestionaire() {
    window.location.href="/";
}



//When a questionaire is saved a button is created 
async function savingQuestionaireBtns() {


  //Retrieve questionaire title
  const responseInfo = await fetch("/public/StudentInfoQuestionaire.csv");
  const CSVdataInfo = await responseInfo.text();
  const rowsInfo = CSVdataInfo.split("\n").slice(1);

  var titleColoumnArr = [];

  rowsInfo.forEach((element) => {
      const rowInfo = element.split(",");
      const coloumnTitle = rowInfo[0];
      titleColoumnArr.push(coloumnTitle);
  });
 
  //sets local storage key to an variable
  var newArr = JSON.parse(window.localStorage.getItem('WrapperID'));


  
  //loop through the items and create button for each item
  for (var i = 0; i < newArr.length; i++) {
      

    btnListContainer = document.getElementById("btn-list-wrapper")
    var createQuestionaireBtn = document.createElement("button");
    createQuestionaireBtn.innerHTML = titleColoumnArr[i];
    createQuestionaireBtn.setAttribute("id",""+ newArr[i]);
    createQuestionaireBtn.setAttribute("questionairebtnid",""+ _questionaireIndex++);
    createQuestionaireBtn.setAttribute("class","QuestionaireBtnClass");
    createQuestionaireBtn.name ="renderBtn";
  
    btnListContainer.appendChild(createQuestionaireBtn);
  }



  //Selects individual buttons & change local storage variables according to them
  btnListContainer.addEventListener('click', (event) => {
    localStorage.btnID = event.target.id;
    localStorage.SelectedBtnID = event.target.getAttribute('questionairebtnid')
    window.location.href="/StudentQuestionaireForm";
  })

}
  
savingQuestionaireBtns();










