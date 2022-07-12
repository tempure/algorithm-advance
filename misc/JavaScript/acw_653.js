let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let n = parseInt(buf);
    let money = [100, 50, 20, 10, 5, 2, 1];
    console.log(n);
    for (let p of money) {
        let cnt = parseInt(n / p);
        console.log(`${cnt} nota(s) de R$ ${p},00`);
        n %= p;
    }
});