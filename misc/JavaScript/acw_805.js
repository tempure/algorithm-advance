let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

let max = (x, y) => {
    return x > y ? x : y;
}

process.stdin.on("end", function () {
    let [x, y] = buf.split(' ').map(x => { return parseInt(x) });
    console.log(max(x, y));
});