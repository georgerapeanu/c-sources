import {stdin, stdout} from 'process';
import * as readline from 'node:readline/promises';
const rl = await readline.createInterface({input:stdin, output:null});

async function main(){
    let numbers = [];
    rl.on('line', (input) => {
        numbers.push(parseInt(input));
    }).on('close', async () => {
        let ans = 0;
        for(let i = 3;i < numbers.length;i++){
          //if(numbers[i - 1] < numbers[i]){ //PART1
            if(numbers[i - 3] < numbers[i]){ //PART2
                ans += 1;
            }
        }
        console.log(ans);
    });
}

main();
