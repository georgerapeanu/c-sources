import {exit, stdin, stdout} from 'process';
import * as readline from 'node:readline/promises';
const rl = await readline.createInterface({input:stdin, output:null});

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        if(line.trim() !== ""){
            input_lines.push(line.trim());
        }
    }).on('close', async () => {
        let lines =[];
        for(const i in input_lines){
            let points = input_lines[i].split("->");
            let line_numbers = [];
            for(const j in points){
                let coords = points[j].split(",");
                for(const k in coords){
                    if(coords[k].trim() !== ""){
                        line_numbers.push(parseInt(coords[k].trim()));
                    }
                }
            }
            lines.push([[line_numbers[0], line_numbers[1]], [line_numbers[2], line_numbers[3]]])
        }
        let points = {};
        for(const i in lines) {
            let fst = lines[i][0];
            let snd = lines[i][1];
            if(fst[0] > snd[0]){
               let tmp = fst;
               fst = snd;
               snd = tmp;
            }else if(fst[0] === snd[0] && fst[1] > snd[1]){
                let tmp = fst;
                fst = snd;
                snd = tmp;
            }
            if (fst[0] === snd[0]) {
                for (let y = fst[1]; y <= snd[1]; y++) {
                    if (!([fst[0], y] in points)) {
                        points[[fst[0], y]] = 0;
                    }
                    points[[fst[0], y]] += 1;
                }
            } else if (fst[1] === snd[1]) {
                for (let x = fst[0];x <= snd[0]; x++) {
                    if (!([x, fst[1]] in points)) {
                        points[[x, fst[1]]] = 0;
                    }
                    points[[x, fst[1]]] += 1;
                }
            } else if(fst[0] - fst[1] === snd[0] - snd[1]){
                for(let i = 0;i <= snd[0] - fst[0];i++){
                    if(!([fst[0] + i, fst[1] + i] in points)){
                        points[[fst[0] + i, fst[1] + i]] = 0;
                    }
                    points[[fst[0] + i, fst[1] + i]] += 1;
                }
            }else if(fst[0] + fst[1] === snd[0] + snd[1]){
                for(let i = 0;i <= snd[0] - fst[0];i++) {
                    if (!([fst[0] + i, fst[1] - i] in points)) {
                        points[[fst[0] + i, fst[1] - i]] = 0;
                    }
                    points[[fst[0] + i, fst[1] - i]] += 1;
                }
            }
        }
        let ans = 0;
        for(const point in points){
            if(points[point] > 1){
                ans += 1;
            }
        }
        console.log(ans);
    });


}

main();
