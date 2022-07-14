let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let str = buf.split('\n')[0].split(' ');
    let res = "";
    str.reverse();
    for (let w of str) {
        res += w + ' ';
    }
    console.log(res);
});