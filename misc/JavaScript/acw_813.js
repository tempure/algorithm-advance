let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

let print = (a, row) => {
    for (let i = 0; i < row; i++) {
        console.log(a[i].join(' '));
    }
}

process.stdin.on("end", function () {
    let lines = buf.split('\n');
    let [n, m] = lines[0].split(' ').map(x => { return parseInt(x) });
    let a = [];
    for (let i = 0; i < n; i++) {
        a.push(lines[i + 1].split(' ').map(x => { return parseInt(x) }));
    }
    print(a, n);
});