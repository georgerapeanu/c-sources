import {stdin} from 'process';
import * as readline from 'node:readline/promises';
const rl = await readline.createInterface({input:stdin, output:null});
const d = [[-1, 0], [0, 1], [1, 0], [0, -1]];

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        if(line.trim() !== ""){
            input_lines.push(line.trim());
        }
    }).on('close', async () => {
        let matrix = JSON.parse(JSON.stringify(input_lines));
        let cnt = Array(matrix.length).fill(Array(matrix[0].length).fill(0));
        cnt = JSON.parse(JSON.stringify(cnt));
        for(const i in matrix){
            for(const j in matrix[i]){
                for(const k in d){
                    let x =  parseInt(i) + d[k][0];
                    let y = parseInt(j) + d[k][1];
                    if(0 <= x && x < matrix.length && 0 <= y && y < matrix[i].length){
                        if(matrix[x][y] <= matrix[i][j]){
                            cnt[parseInt(i)][parseInt(j)]++;
                        }
                    }
                }
            }
        }
        let initial_cnt = JSON.parse(JSON.stringify(cnt));
        let basins = [];
        for(const i in matrix){
            for(const j in matrix[i]){
                if(initial_cnt[i][j] === 0){
                    let queue = [];
                    cnt = JSON.parse(JSON.stringify(initial_cnt));
                    queue.push([parseInt(i), parseInt(j)]);
                    for(let h = 0; h < queue.length;h++){
                        let x = queue[h][0];
                        let y = queue[h][1];
                        for(const k in d){
                            let xx = x + d[k][0];
                            let yy = y + d[k][1];
                            if(0 <= xx && xx < matrix.length && 0 <= yy && yy < matrix[0].length && matrix[x][y] < matrix[xx][yy]){
                                if(cnt[xx][yy] !== -1 && matrix[xx].charCodeAt(yy) !== '9'.charCodeAt(0)){
                                    cnt[xx][yy] = -1;
                                    queue.push([xx, yy]);
                                }
                            }
                        }
                    }
                    basins.push(queue.length);
                }
            }
        }
        basins.sort((a, b) => b - a);
        let ans = 1;
        for(let i = 0;i < 3;i++){
            ans *= basins[i];
        }
        console.log(ans);
    });


}

main();
