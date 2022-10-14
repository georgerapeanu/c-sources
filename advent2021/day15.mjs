import {stdin} from 'process';
import * as readline from 'node:readline/promises';
import * as assert from "assert";
const rl = await readline.createInterface({input:stdin, output:null});

const d = [[-1, 0], [0, 1], [1, 0], [0, -1]];

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        input_lines.push(line.trim());
    }).on('close', async () => {
        let dist = [];
        let cost = [];
        for(let i = 0;i < 5 * input_lines.length;i++){
            dist.push(Array(5 * input_lines[i % input_lines.length].length).fill(Math.floor(1e9)));
            cost.push([]);
            for(let j = 0;j < 5 * input_lines[i % input_lines.length].length;j++){
                let base_cost = input_lines[i % input_lines.length].charCodeAt(j % input_lines[i % input_lines.length].length) - '0'.charCodeAt(0);
                let tile_cost = base_cost + Math.floor(j / (input_lines[i % input_lines.length].length)) + Math.floor(i / input_lines.length);
                tile_cost = ((tile_cost - 1) % 9) + 1;
                cost[i].push(tile_cost);
            }
        }
        let q = [];
        for(let i = 0;i < 10;i++){
            q.push([]);
        }
        dist[0][0] = 0;
        q[0].push([0, 0]);

        let cnt_empty = 0;

        for(let i = 0;cnt_empty < 10;i = (i + 1) % 10){
            if(q[i].length === 0){
                cnt_empty += 1;
            }else{
                cnt_empty = 0;
            }
            for(let j = 0;j < q[i].length;j++){
                let x = q[i][j][0];
                let y = q[i][j][1];
                if(dist[x][y] % 10 !== i){
                    continue;
                }
                for(let k = 0;k < d.length;k++){
                    let xx = x + d[k][0];
                    let yy = y + d[k][1];
                    if(xx < 0 || xx >= cost.length || yy < 0 || yy >= cost[xx].length){
                        continue;
                    }
                    if(dist[xx][yy] > dist[x][y] + cost[xx][yy]){
                        dist[xx][yy] = dist[x][y] + cost[xx][yy];
                        q[dist[xx][yy] % 10].push([xx, yy]);
                    }
                }
            }
            q[i] = [];
        }
        console.log(dist[dist.length - 1][dist[dist.length - 1].length - 1]);
    });

}

main();
