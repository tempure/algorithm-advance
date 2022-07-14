let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

let gcd = (a, b) => {
    return b ? gcd(b, a % b) : a;
}

process.stdin.on("end", function () {
    let [a, b] = buf.split(' ').map(x => { return parseInt(x) });
    console.log(gcd(a, b));
});