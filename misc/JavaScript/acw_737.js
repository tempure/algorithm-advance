let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let arr = buf.split('\n').map(x => {
        return parseInt(x);
    });

    for (let i = 0; i < 10; i++) {
        if (arr[i] <= 0) arr[i] = 1;
        console.log(`X[${i}] = ${arr[i]}`);
    }
});