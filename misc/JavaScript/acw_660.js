let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let [x, y] = buf.split(' ').map(x => { return parseInt(x) });

    let p;
    if (x === 1) p = 4;
    else if (x === 2) p = 4.5;
    else if (x === 3) p = 5;
    else if (x === 4) p = 2;
    else p = 1.5;

    console.log(`Total: R$ ${(p * y).toFixed(2)}`);
});