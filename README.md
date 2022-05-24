# P2_project
Repository for our P2 project

The program:
How to start and stop the program? 
    Requirements:
        Windows OS
        Node installed

    Start by opening up the terminal in the P2_PROJECT folder 
    This can be done in the two following ways:
        [1] right click the folder and press open in terminal
        [2] navigate your folders in the terminal with "cd [foldername]" to go forward
            or "cd.." to go back.

    When trying to run the program for the first time, node has to be initialized. 
    This is done by typing the folowing lines into the terminal (this can take some time,
    however, it is only neccesary once)
        "npm init -y"
        "npm i express"
        "npm i csv-parser"
        "npm i --save-dev nodemon"

    When node has been set up, the server can be started with "node server.js"
    The server will then provide you with a link to the localhost:4000 page.
    The link can be copied, or clicked on with "ctrl + left_click".

    When you are done with interacting with the server, you must press "ctrl + c" in the terminal
    to stop it

Once you have opened the program, how do you operate the program? 
    The first you will see when clicking the link is the front page
    from here you are free to navigate to any of the sites in the hotbar to the left

    Feel free to use these login ID's 
        Admin: 12345
        Student: 54321
            When loggin in you must press the go button. If you accidently pressed the "enter" button
            you will be greeted with connot GET /adminLogin or /studentLogin. Don't worry, you can just press
            back on your browser, and it will take you back to the login page.

    When on the Admin page or the Student page, you can always navigate back to the front page
    by clicking the arrow in the top left corner.

What do you do on the Admin page?
    When you have logged into the admin page, you will be greeted by the admin front page
    here you have these following options on the page:
        Create new questionnaire
        Continue working on questionnaire
    and these following options on the sidebar:
        Front Page
        Overview Page
        Results
    
    Create new questionnaire:
        Here you will be greeted with the in depth guide on the page,
        on how you can create your own questionnaire
    
        Next you will be redirected to the creation of the questionnaire page
        Here you can add a question by pressing the "plus" button
            When creating a question you can add a question description
            Click on the overruling field to make it overruling 
            The "-" button add the question type "scale, text input or true/false"
            The "x" button deletes the question

        The save button, saves the questionnaire, to be later found in the overview page

        The cancel button cancels the creation of the questionnaire.

    Continue working on questionnaire:
        Here you will be redirected to the overview page. 
        From here, if you have made a questionnaire, you can click the "edit" button
        and be redirected to the edit page

        From the edit page you can:
            Change the type of question by clicking the "-" button
            Change the description of the question
            Make the question overruling .
            Delete the question (While visually removing the question)
                This only removes the content and type of the question.
                And the empty question can be seen again when reloading the page.

    Front page
        Redirects to the front page.

    Overview page:
        From here, if you have made a questionnaire, you can click the "edit" button 
            (look at continue working on questionnaire)
        You can also click the calculate button, which will run the allocation algorithm
            If the amount of students inputted, and the amount of student answers are matching
            the algorithm will run with the student answers.
            If there are insufficient student answers, the algorithm will run
            with random student answers.
            The result from this can bee seen on the results page.

    Results page:
        Here you can see your calculated results

What can you do on the student page:
    When you have logged into the student page, you will be greeted by the student front page
    here you have these following options on the sidebar:
        Front page
        Questionnaires

    Front page:
        Redirects to the front page

    Questionnaires
        If you have made any questionnaires, you will be able to click on them from here

    Answering questionnaires:
        After having answered the questionnaire, you can press the 
        "send" button to save the answers
            after pressing the "send" button you will be redirected to the student front page
        If you don't want to save the answer, you can press the 
        "cancel" button
            after pressing the "cancel" button, you will be redirected to the student front page
        
        The questionnaire currently has no way of checking if all the questions have been answered
        therefore, if you intend to use the algorithm with your own answers, don't leave empty answers



The files:
What files are, generally, located in the "Admin" folder?
    In the admin folder, all files that interact with the admin page can be found


What files are, generally, located in the "AllocationPrograms" folder?
    In the allocationPrograms folder all the different allocation algorithms, that have been tested
    can be found. 
    The only algorithm that has been compiled beforehand is the geneBasic algorithm.
    Gene basic is also the only algorithm that has been made compatible with the csv-files.

What files are, generally, located in the "Frontpage" folder?
    In the frontpage folder, all the files that relate to the program frontpage are located

What files are, generally, located in the "EliasStuff" folder?
    In the EliasStuff folder all files related to the questionnaires are located 

What files are, generally, located in the "Student" folder?
    In the Student folder all files related to the student page are located

What files are locatied in the "node_modules" folder?
    In here all node-modules can be found. 

What files are not in any folder?
    Here you can see: 
        the server
        The compiled allocation algorithm
        the package.json
        the package-lock.json
        the readme.md file