let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let n = parseInt(buf);
    for (let i = 1; i <= n; i++) {
        if (n % i === 0)
            console.log(i);
    }
});