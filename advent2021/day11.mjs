import {stdin} from 'process';
import * as readline from 'node:readline/promises';
const rl = await readline.createInterface({input:stdin, output:null});
const d = [[-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1]];

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        if(line.trim() !== ""){
            input_lines.push(line.trim());
        }
    }).on('close', async () => {
        let energy = [];
        const STEPS = 100;
        let ans = 0;

        for(const i in input_lines) {
            energy.push([]);
            for (const j in input_lines[i].trim()) {
                energy[energy.length - 1].push(input_lines[i].trim().charCodeAt(j) - '0'.charCodeAt(0));
            }
        }
        while(true){
            let ok = true;
            for(let i = 0;i < energy.length;i++){
                for(let j = 0;j < energy[i].length;j++){
                    if(energy[i][j] !== 0){
                        ok = false;
                    }
                }
            }
            if(ok){
                break;
            }
            let in_queue = {};
            let queue = [];
            for(let i = 0;i < energy.length;i++){
                for(let j = 0;j < energy[i].length;j++){
                    energy[i][j]++;
                    if(energy[i][j] > 9){
                        in_queue[[i, j]] = true;
                        queue.push([i, j]);
                    }
                }
            }
            for(let i = 0;i < queue.length;i++){
                let x = queue[i][0];
                let y = queue[i][1];
                for(let k = 0;k < d.length;k++){
                    let xx = x + d[k][0];
                    let yy = y + d[k][1];
                    if(xx < 0 || xx >= energy.length || yy < 0 || yy >= energy[xx].length){
                        continue;
                    }
                    if(in_queue[[xx, yy]]){
                        continue;
                    }
                    energy[xx][yy]++;
                    if(energy[xx][yy] > 9){
                        in_queue[[xx, yy]] = true;
                        queue.push([xx, yy]);
                    }
                }
            }
            ans += 1;
            for(const i in queue){
                energy[queue[i][0]][queue[i][1]] = 0;
            }
        }
        console.log(ans);
    });

}

main();
