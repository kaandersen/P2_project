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
                Welcome to the Questionnaire Based Student Allocation Program of 2022.<br>
                
                
                
                
            </p>

        </div>
        
            
        `;
    }
}