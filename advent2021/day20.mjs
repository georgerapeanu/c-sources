import {stdin} from 'process';
import * as readline from 'node:readline/promises';
import * as assert from "assert";
const rl = await readline.createInterface({input:stdin, output:null});

function get_value(background, opposite, x, y){
    if([x,y] in opposite){
        return 1 - background;
    }
    return background;
}

function get_code(background, opposite, x, y){
    let ans = 0;

    for(let i = x - 1;i <= x + 1;i++){
        for(let j = y - 1;j <= y + 1;j++){
            ans = ans * 2 + get_value(background, opposite, i, j);
        }
    }

    return ans;
}

function apply_enhancement(background, opposite, algorithm){
    let new_background = 0;

    if(background === 0){
        if(algorithm[0] === '.'){
            new_background = 0;
        }else{
            new_background = 1;
        }
    }else{
        if(algorithm[511] === '.'){
            new_background = 0;
        }else{
            new_background = 1;
        }
    }

    let min_x,max_x,min_y,max_y;
    min_x = max_x = min_y = max_y = undefined;

    for(const i in opposite){

        if(min_x === undefined || min_x > opposite[i][0]){
            min_x = opposite[i][0];
        }
        if(max_x === undefined || max_x < opposite[i][0]){
            max_x = opposite[i][0];
        }
        if(min_y === undefined || min_y > opposite[i][1]){
            min_y = opposite[i][1];
        }
        if(max_y === undefined || max_y < opposite[i][1]){
            max_y = opposite[i][1];
        }
    }

    min_x -= 1;
    max_x += 1;
    min_y -= 1;
    max_y += 1;

    let new_opposite = {};

    for(let i = min_x;i <= max_x;i++){
        for(let j = min_y;j <= max_y;j++){
            let tmp = algorithm[get_code(background, opposite, i, j)];
            if(tmp === '.'){
                tmp = 0;
            }else{
                tmp = 1;
            }
            if(tmp !== new_background){
                new_opposite[[i, j]] = [i, j];
            }
        }
    }

    return [new_background, new_opposite];
}

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        if(line.trim().length !== 0){
            input_lines.push(line.trim());
        }
    }).on('close', async () => {
        let algorithm = input_lines[0];

        let background = 0;
        let opposite = {};

        for(let i = 1;i < input_lines.length;i++){
            for(let j = 0;j < input_lines[i].length;j++) {
                if(input_lines[i][j] === '#'){
                    opposite[[i, j]] = [i, j];
                }
            }
        }

        for(let h = 0;h < 50;h++){
            [background, opposite] = apply_enhancement(background, opposite, algorithm);
        }


        console.log(Object.keys(opposite).length);
    });

}

main();
