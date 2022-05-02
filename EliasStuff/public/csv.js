const csv = require('csv-parser');
const fs = require('fs');

fs.createReadStream('EliasStuff/public/Questionaire.csv')
  .pipe(csv())
  .on('data', (row) => {
    console.log(row);
  })
  .on('end', () => {
    console.log('CSV file successfully processed');
  });



const WritingToCsv = require('csv-writer').createObjectCsvWriter;
const csvObject = WritingToCsv({
  path: 'EliasStuff/public/Questionaire.csv',
  header: [
    {id: 'id', title: 'ID'},
    {id: 'question', title: 'Question'},
    {id: 'answer', title: 'Answer'},
  ]
});



const bab = "Icey1";



const data = [
  
  {
    id: 1,
    question: bab,
    answer: 'yes',
  }, {
    id: 2,
    question: 'Question2?',
    answer: 'no',
  }, {
    id: 3,
    question: 'Question3?',
    answer: 'maybe',
  }
];



csvObject
  .writeRecords(data)
  .then(()=> console.log('The CSV file was written successfully', data[0].id));




  /*const WritingToCsv = require('csv-writer').createObjectCsvWriter;
  const csvObject = WritingToCsv({
    path: 'public/Questionaire.csv',
    headers: [ 
      {id: 'idtitle', title:'IDtitle', fields:[{id: 'id', title: 'ID'}, {id: 'question', title: 'Question'}, {id: 'answer', title: 'Answer'}]},
  ]
  });
  
  
  const data = [
    {
    idtitle: "JohnJohn",
    idnumber: 3,
    "fields": [
    {
      id: "1",
      question: "hello",
      answer: "Okay"
    }
  ]
}
  ];
  
const filtered_courses = data.filter(data => data.fields.some(field => csvObject.includes(field.id)));
console.log(filtered_courses);
  
  
  csvObject
    .writeRecords(data)
    .then(()=> console.log('The CSV file was written successfully', data[0].id));
  
*/







module.exports = {fs, csv}

