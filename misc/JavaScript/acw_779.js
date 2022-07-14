let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

let reverse = (str) => {
    return str.split('').reverse().join('');
}

process.stdin.on("end", function () {
    let lines = buf.split('\n');
    for (let i = 0; i < lines.length;) {
        let n = parseInt(lines[i]); //每组的字符串个数
        if (n === 0) break;
        i++; //跳过 n

        for (let j = 0; j < n; j++) { //翻转，比较前缀更加容易
            lines[i + j] = reverse(lines[i + j]);
        }
        let res = "";
        for (let k = 0; k < lines[i].length; k++) {
            let is_same = true;
            for (let j = 1; j < n; j++) {
                if (lines[i + j][k] != lines[i][k]) {
                    is_same = false;
                    break;
                }
            }
            if (is_same) {
                res += lines[i][k];
            } else {
                break;
            }
        }

        i += n; //跳到下一组样例
        console.log(reverse(res));
    }
});