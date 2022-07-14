let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let lines = buf.split('\n');
    let c = lines[0];

    let d = [];
    for (let i = 0; i < 12; i++)
        d.push(lines[i + 1].split(' ').map(x => { return parseFloat(x) }));

    let sum = 0, cnt = 0;
    for (let i = 0; i < 12; i++)
        for (let j = 0; j <= 10 - i; j++) { //找规律
            sum += d[i][j];
            cnt++;
        }

    if (c === 'M') sum /= cnt;

    console.log(`${sum.toFixed(1)}`);
});