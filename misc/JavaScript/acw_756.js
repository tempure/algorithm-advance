let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let [n, m] = buf.split(' ').map(x => { return parseInt(x) });

    let res = []; //初始全为0
    for (let i = 0; i < n; i++) {
        res[i] = [];
        for (let j = 0; j < n; j++) {
            res[i].push(0);
        }
    }

    let dx = [-1, 0, 1, 0], dy = [0, 1, 0, -1]; //偏移量
    let x = 0, y = 0, d = 1; //初始坐标和偏移量

    for (let i = 1; i <= n * m; i++) {
        res[x][y] = i;
        let a = x + dx[d], b = y + dy[d]; //下一格的坐标
        if (a < 0 || a >= n || b < 0 || b >= m || res[a][b]) { //越界或者碰到已经填的位置就转向
            d = (d + 1) % 4;
            a = x + dx[d], b = y + dy[d];
        }
        x = a, y = b; //下一格的坐标
    }

    for (let i = 0; i < n; i++) {
        let line = "";
        for (let j = 0; j < m; j++)
            line += `${res[i][j]} `;
        console.log(line);
    }
});