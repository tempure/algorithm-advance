let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let [a, b] = buf.split(' ').map(x => { return parseInt(x) });

    let res;
    if (a < b) res = b - a;
    else res = 24 - a + b;

    console.log(`O JOGO DUROU ${res} HORA(S)`);
});