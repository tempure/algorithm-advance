let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let x = parseFloat(buf);

    if (x >= 0 && x <= 25)
        console.log("Intervalo [0,25]");
    else if (x > 25 && x <= 50)
        console.log("Intervalo (25,50]");
    else if (x > 50 && x <= 75)
        console.log("Intervalo (50,75]");
    else if (x > 75 && x <= 100)
        console.log("Intervalo (75,100]");
    else
        console.log("Fora de intervalo");
});