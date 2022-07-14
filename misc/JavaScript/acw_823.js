let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

let path = [];
let st = [];


//就这种排列dfs问题，最简单的就是递归树分析最直观。。。

let dfs = (u, n) => { //u 当前dfs的位置
    if (u === n) console.log(path.join(' '));
    else {
        for (let i = 1; i <= n; i++) {
            if (!st[i]) {
                path.push(i);
                st[i] = true;
                dfs(u + 1, n);
                st[i] = false;
                path.pop();
            }
        }
    }
}

process.stdin.on("end", function () {
    let n = parseInt(buf);
    dfs(0, n);
});