let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});


process.stdin.on("end", function () {
    let ns = buf.split('\n').map(x => parseInt(x));

    for (let n of ns) {
        if (n === 0) break;
        for (let i = 0; i < n; i++) {
            let line = "";
            for (let j = 0; j < n; j++) {
                line += `${Math.min(i + 1, n - i, j + 1, n - j)} `; //上下左右边界距离的最小值
            }
            console.log(line);
        }
        console.log();
    }
});