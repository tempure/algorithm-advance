let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString(); //不要写为 toString(chunk) 能编译通过但是结果不对
});

process.stdin.on("end", function () {
    let [a, b] = buf.split(' ').map(x => {
        return parseInt(x);
    });
    if (a % b === 0 || b % a === 0) {
        console.log("Sao Multiplos");
    } else {
        console.log("Nao sao Multiplos");
    }
});