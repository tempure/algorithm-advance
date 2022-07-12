let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let n = parseInt(buf);
    let m = parseInt(n / 2);
    for (let i = 0; i < n; i++) {
        let line = "";
        for (let j = 0; j < n; j++) {
            if (Math.abs(i - m) + Math.abs(j - m) <= m) //曼哈顿距离 <= n/2 就是边界内的点
                line += '*';
            else line += ' ';
        }
        console.log(line);
    }
});
