import AbstractView from "./AbstractView.js";

export default class extends AbstractView {
    constructor(params) {
        super(params);
        this.setTitle("Front Page");
    }

    async getHtml() {
        return `
        <div class="aboutcontainer">
            <h1>Questionnaire based Student allocation</h1>
            <p>
                Welcome to our questionnaire based student allocation program.
                <br>
                <br>
                [insert description of how to use the program?]
                <br>
                <br>
                For exaple: 
                <br>
                This program helps efficiently allocate students into dorm rooms...
                
            </p>

        </div>
        
            
        `;
    }
}