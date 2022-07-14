let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let [str, a, b] = buf.split('\n');
    let words = str.split(' ');

    let res = "";
    for (let w of words) {
        if (w === a) res += b + ' ';
        else res += w + ' ';
    }

    console.log(res);
});