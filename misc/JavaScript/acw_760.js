let buf = "";

process.stdin.on("readable", function () {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

process.stdin.on("end", function () {
    let str = buf.split('\n')[0]; //处理行末回车如果有回车的话
    console.log(str.length);
});