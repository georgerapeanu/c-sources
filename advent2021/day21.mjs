import {stdin} from 'process';
import * as readline from 'node:readline/promises';
import * as assert from "assert";
const rl = await readline.createInterface({input:stdin, output:null});

function access(dp, i, j, s1, s2, k){
    if(s1 >= 21){
        return 1 - k;
    }else if(s2 >= 21){
        return k;
    }
    return dp[i][j][s1][s2][k];
}

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        if(line.trim().length !== 0){
            input_lines.push(line.trim());
        }
    }).on('close', async () => {
        let p1 = parseInt(input_lines[0].split(" ")[input_lines[0].split(" ").length - 1]);
        let p2 = parseInt(input_lines[1].split(" ")[input_lines[1].split(" ").length - 1]);
        /*
        let s1 = 0;
        let s2 = 0;
        let rolls = 0;

        while(s1  < 1000 && s2 < 1000){
            if(rolls % 2 === 0){
                p1 += rolls + 1 + rolls + 2 + rolls + 3;
                p1 = (p1 - 1) % 10 + 1;
                s1 += p1;
            }else{
                p2 += rolls + 1 + rolls + 2 + rolls + 3;
                p2 = (p2 - 1) % 10 + 1;
                s2 += p2;
            }
            rolls += 3;
        }
        console.log(rolls, s1, s2, rolls * Math.min(s1, s2));
         */

        let dp = [];

        for(let i = 0;i <= 10;i++){
            let l1 = [];
            for(let j = 0;j <= 10;j++){
                let l2 = [];
                for(let s1 = 0;s1 <= 21;s1++){
                    let l3 = [];
                    for(let s2 = 0;s2 <= 21;s2++){
                        let l4 = [0, 0];
                        l3.push(l4);
                    }
                    l2.push(l3);
                }
                l1.push(l2);
            }
            dp.push(l1);
        }
        for(let sum_scores = 40;sum_scores >= 0;sum_scores--){
            for(let s1 = 0;s1 <= sum_scores && s1 <= 20;s1++){
                let s2 = sum_scores - s1;
                if(s2 > 20){
                    continue;
                }
                for(let i = 1;i <= 10;i++){
                    for(let j = 1;j <= 10;j++){
                        for(let k = 0;k <= 1;k++){
                            for(let roll1 = 1;roll1 <= 3;roll1++){
                                for(let roll2 = 1;roll2 <= 3;roll2++){
                                    for(let roll3 = 1;roll3 <= 3;roll3++){
                                        dp[i][j][s1][s2][k] += access(dp, j, ((i + roll1 + roll2 + roll3 - 1) % 10) + 1, s2, s1 + ((i + roll1 + roll2 + roll3 - 1) % 10) + 1, 1 - k);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        console.log(Math.max(dp[p1][p2][0][0][0], dp[p1][p2][0][0][1]));
    });

}

main();
