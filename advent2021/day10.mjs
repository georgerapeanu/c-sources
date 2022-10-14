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
        let ans = 0;
        let incomplete_line_scores = [];
        let score = {')':3, ']':57, '}':1197, '>':25137};
        let autocomplete_score = {'(':1, '[':2, '{':3, '<':4};
        let pair = {')':'(', ']':'[', '}':'{', '>':'<'};

        for(const h in input_lines){
            const line = input_lines[h];
            let stack = [];
            let ok = true;
            for(const i in line){
                if('([{<'.includes(line[i])){
                    stack.push(line[i]);
                }else if(')]}>'.includes(line[i])){
                    if(stack.length === 0 || stack[stack.length - 1] !== pair[line[i]]){
                        ans += score[line[i]];
                        ok = false;
                        break;
                    }
                    stack.pop();
                }
            }
            if(ok){
                let current_score = 0;
                while(stack.length !== 0){
                    current_score = current_score * 5 + autocomplete_score[stack[stack.length - 1]];
                    stack.pop();
                }
                incomplete_line_scores.push(current_score);
            }
        }

        ans = incomplete_line_scores.sort((a,b) => a - b)[Math.floor(incomplete_line_scores.length / 2)];

        console.log(ans);
    });


}

main();
