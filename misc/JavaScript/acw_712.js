let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let xs = buf.split('\n').map(x => {
        return parseFloat(x);
    });

    let res = 0;
    for (let x of xs) {
        if (x > 0) res++;
    }
    console.log(`${res} positive numbers`);
});