let buf = "";

process.stdin.on("readable", function(){
    let chunk = process.stdin.read();
    if(chunk) buf += chunk.toString();
});

process.stdin.on("end", function(){
    let lines = buf.split("\n"); //先行分割
    let [x1, y1] = lines[0].split(' ').map(x => {return parseFloat(x)});
    let [x2, y2] = lines[1].split(' ').map(x => {return parseFloat(x)});

    let dx = x1 - x2;
    let dy = y1 - y2;

    console.log(Math.sqrt(dx * dx + dy * dy).toFixed(4));
});