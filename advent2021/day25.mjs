import {stdin} from 'process';
import * as readline from 'node:readline/promises';
import * as assert from "assert";
const rl = await readline.createInterface({input:stdin, output:null});

function do_step(matrix){
    let ans = [];
    for(let i = 0;i < matrix.length;i++){
        let row = [];
        for(let j = 0;j < matrix[i].length;j++){
            row.push(".");
        }
        ans.push(row);
    }

    for(let i = 0;i < matrix.length;i++){
        for(let j = 0;j < matrix[i].length;j++){
            if(matrix[i][j] !== '>'){
                continue;
            }
            if(matrix[i][(j + 1) % matrix[i].length] === '.'){
                ans[i][(j + 1) % matrix[i].length] = '>';
            }else{
                ans[i][j] = '>';
            }
        }
    }

    for(let i = 0;i < matrix.length;i++){
        for(let j = 0;j < matrix[i].length;j++){
            if(matrix[i][j] !== 'v'){
                continue;
            }
            if(ans[(i + 1) % matrix.length][j] === '.' && matrix[(i + 1) % matrix.length][j] !== 'v'){
                ans[(i + 1) % matrix.length][j] = 'v';
            }else{
                ans[i][j] = 'v';
            }
        }
    }

    return ans;
}

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        if(line.trim().length !== 0){
            input_lines.push(line);
        }
    }).on('close', async () => {
        let matrix = [];
        for(let i = 0;i < input_lines.length;i++){
            let row = [];
            for(let j = 0;j < input_lines[i].length;j++){
                row.push(input_lines[i][j]);
            }
            matrix.push(row);
        }
        /*
        matrix = do_step(matrix);
        matrix = do_step(matrix);
        matrix = do_step(matrix);
        matrix = do_step(matrix);
        for(let i = 0;i < matrix.length;i++){
            console.log(matrix[i].join(""));
        }
        return ;

         */

        let cnt = 0;
        while(true){
            let nxt = do_step(matrix);
            cnt++;
            if(JSON.stringify(matrix) === JSON.stringify(nxt)){
                break;
            }
            matrix = nxt;
        }
        console.log(cnt);
    });

}

main();
