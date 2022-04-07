function studentIDCheck() {
    let hello =  fs.readFileSync("../../../../StudentID.txt", "utf8");
    console.log(hello);
    let test = "Hello world";
    fs.writeFileSync("../../../../StudentID.txt", "\n"+test, {flag: 'a+'});

    hello = fs.readFileSync("../../../../StudentID.txt", "utf8");
    console.log(hello);
}

export { studentIDCheck } 