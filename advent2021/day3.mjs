import {stdin, stdout} from 'process';
import * as readline from 'node:readline/promises';
const rl = await readline.createInterface({input:stdin, output:null});

function oxygen_criteria(cnt_0,cnt_1){
    if(cnt_1 >= cnt_0){
        return '1';
    }else{
        return '0';
    }
}

function co_criteria(cnt_0,cnt_1){
    if(cnt_1 >= cnt_0){
        return '0';
    }else{
        return '1';
    }
}

function get_count_1(lines, col){
    let answer = 0;
    for(const lin in lines){
        if(lines[lin][col] === "1"){
            answer += 1;
        }
    }
    return answer;
}

function get_by_criteria(numbers, criteria){
    for(const j in numbers[0]){
        if(numbers.length === 1){
            return parseInt(numbers[0], 2);
        }
        let cnt_1 = get_count_1(numbers, j);
        let cnt_0 = numbers.length - cnt_1;
        numbers = numbers.filter(number => number[j] === criteria(cnt_0, cnt_1));
    }
    return parseInt(numbers[0], 2);
}

async function main(){
    let lines = [];
    rl.on('line', (line) => {
        if(line.trim() !== ""){
            lines.push(line.trim());
        }
    }).on('close', async () => {
        let gamma = 0;
        let epsilon = 0;
        for(const j in lines[0]){
            if(2 * get_count_1(lines, j) > lines.length){
                gamma += 1 << (lines[0].length - j - 1);
            }else{
                epsilon += 1 << (lines[0].length - j - 1);
            }
        }
        let oxygen = get_by_criteria(Array.from(lines), oxygen_criteria);
        let co = get_by_criteria(Array.from(lines), co_criteria);

        console.log(oxygen * co);
    });
}

main();
