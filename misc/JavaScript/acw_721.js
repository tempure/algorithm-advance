let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let xs = buf.split('\n').map(x => {
        return parseInt(x);
    });

    for (let x of xs) {
        if (x === 0) break;
        let line = "";
        for (let i = 1; i <= x; i++) {
            line += `${i} `;
        }
        console.log(line);
    }
});