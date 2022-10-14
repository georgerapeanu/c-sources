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
        const numbers = input_lines[0].split(",");

        for(const i in numbers){
            numbers[i] = parseInt(numbers[i]);
        }

        numbers.sort((a, b) => a - b);
        let sum = 0;

        for(const i in numbers){
            sum += numbers[i];
        }

        const avg = Math.floor(sum / numbers.length);
        const x = [avg - 1, avg, avg + 1];

        let ans = 1e18;
        for(const i in x) {
            let local_ans = 0;
            for (const j in numbers) {
                const delta = Math.abs(numbers[j] - x[i]);
                local_ans += delta * (delta + 1) / 2;
            }
            ans = Math.min(ans, local_ans);
        }

        console.log(ans);
    });


}

main();
