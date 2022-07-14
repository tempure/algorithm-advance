let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

let sort = (a, l, r) => {
    for (let i = l; i <= r; i++)
        for (let j = l; j <= r; j++) {
            if (a[i] < a[j]) {
                [a[i], a[j]] = [a[j], a[i]];
            }
        }
}

process.stdin.on("end", function () {
    let lines = buf.split('\n');
    let [n, l, r] = lines[0].split(' ').map(x => { return parseInt(x) });
    let q = lines[1].split(' ').map(x => { return parseInt(x) });
    sort(q, l, r);
    console.log(q.join(' '));
});