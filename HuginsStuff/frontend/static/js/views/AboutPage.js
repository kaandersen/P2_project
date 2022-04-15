import AbstractView from "./AbstractView.js";

export default class extends AbstractView {
    constructor(params) {
        super(params);
        this.setTitle("About");
    }

    async getHtml() {
        return `

        <div class="aboutcontainer">
            <h2>About</h2>
            <div class="descriptionContainer"> 
                <p> This project was completed by group A319 at Aalborg university as a semester project.</p>
            </div>

            <div class="purposeContainer">
                <h3>The Purpose of the project</h3> 

                <p id="longText"> The purpose of this project is (BS incoming) to help allocate students into dorm rooms at universities, with a higher satisfaction rate in mind. 
                    We have therefore created an opimization algorithm that allocates students based on certain traits. 
                    These traits will be extracted based on the student answers that the factulty will be able to customize themseleves. 
                </p>

            </div>
            
            
        </div>
        <div class="contactContainer">
            <h3>Contact</h3>
            <p>Sample@mail.com</p>

        </div>
            

        `;
    }
}