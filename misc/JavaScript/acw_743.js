let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let lines = buf.split('\n');
    let L = parseInt(lines[0]);
    let c = lines[1];

    let d = [];

    for (let i = 0; i < 12; i++) {
        d.push(lines[i + 2].split(' ').map(x => { return parseFloat(x) }));
    }

    let sum = 0;
    for (let i = 0; i < 12; i++) {
        sum += d[L][i];
    }
    if (c === 'M') sum /= 12;
    console.log(sum.toFixed(1));
});