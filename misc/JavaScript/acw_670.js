let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let [a, b, c] = buf.split('\n');

    if (a === "vertebrado") {
        if (b === "ave") {
            if (c === "carnivoro") {
                console.log("aguia");
            } else {
                console.log("pomba");
            }
        } else {
            if (c === "onivoro") {
                console.log("homem");
            } else {
                console.log("vaca");
            }
        }
    } else {
        if (b === "inseto") {
            if (c === "hematofago") {
                console.log("pulga");
            } else {
                console.log("lagarta");
            }
        } else {
            if (c === "hematofago") {
                console.log("sanguessuga");
            } else {
                console.log("minhoca");
            }
        }
    }
});