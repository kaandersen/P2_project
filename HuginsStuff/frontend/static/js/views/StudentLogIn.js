import AbstractView from "./AbstractView.js";

export default class extends AbstractView {
    constructor(params) {
        super(params);
        this.setTitle("Student LogIn");
    }

    async getHtml() {
        return `
            <h1>Student logIn</h1>
            <label for="studentID">Student ID:</label>
            <input type="text" id="logInID" value="">
            <button type="button" onclick="logIn()">Log in</button>
            <script>
                function logIn() {
                    console.log("This is podracing");
                }
            </script>
        `;
    }
}