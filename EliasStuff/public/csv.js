app.post("/writetostudentcsv", (req, res) => {
   
  let temp_data=[]

fs.createReadStream('EliasStuff/public/StudentQuestionaire.csv').
on('error',(err)=>{

 const data = req.body.questionsArray;

const WritingToCsv = require("csv-writer").createObjectCsvWriter;
const csvObject = WritingToCsv({
path: "EliasStuff/public/Questionaire.csv",
header: [
  { id: "id", title: "ID" },
  { id: "answer", title: "Answer" },
],

});
csvObject
.writeRecords(data)
.then(() =>
  console.log("The CSV file was written successfully")
);


return ;


})
.pipe(csv())
.on('data', (row) => {
 console.log("I am Running");
    temp_data.unshift(row)

})
.on('end', () => {

 const final_data=[...temp_data,...req.body.questionsArray]
 
 

 for(let i=0;i<final_data.length; i++){
           final_data[i].id=i;

      
 }

 const WritingToCsv = require("csv-writer").createObjectCsvWriter;
 const csvObject = WritingToCsv({
   path: "EliasStuff/public/StudentQuestionaire.csv",
   header: [
    { id: "id", title: "ID" },
    { id: "answer", title: "Answer" },
]
 
 });
 csvObject
   .writeRecords(final_data)
   .then(() =>
     console.log("The CSV file was written successfully")
   );
}); 

res.status(200).json({
 message: "Successfully wrote to csv",
});

});


