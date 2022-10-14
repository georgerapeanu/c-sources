import {stdin} from 'process';
import * as readline from 'node:readline/promises';
import * as assert from "assert";
const rl = await readline.createInterface({input:stdin, output:null});

///this can also be used to compute the highest y
function compute_final_x(start, steps){
    if(start <= steps){
        return start * (start + 1) / 2;
    }
    return (2 * start - steps + 1) * steps / 2;
}

function compute_final_y(start, steps){
    return (2 * start - steps + 1) * steps / 2;
}

function compute_highest_y(start, steps){
    if(start <= 0){
        return 0;
    }
    if(start >= steps){
        return (2 * start - steps + 1) * steps / 2;
    }
    return (start + 1) * start / 2;
}

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        input_lines.push(line.trim());
    }).on('close', async () => {
        const second_part = input_lines[0].split("x=")[1];
        const x_range = second_part.split(",")[0];
        const y_range = input_lines[0].split("y=")[1];
        let [x_left, x_right] = x_range.split("..");
        let [y_left, y_right] = y_range.split("..");
        [x_left, x_right, y_left, y_right] = [parseInt(x_left), parseInt(x_right), parseInt(y_left), parseInt(y_right)]

        let ans = {};

        for(let steps = 1;steps <= 1e6;steps++){
            let start_x = Math.ceil(x_left / steps);
            while(compute_final_x(start_x, steps) <= x_right){
                if(compute_final_x(start_x, steps) < x_left){
                    start_x++;
                    continue;
                }
                ///(y + (y - steps + 1)) * steps / 2 >= y_left
                ///2 * y - steps + 1 >= y_left * 2 / steps
                ///y >= (y_left * 2 / steps + steps - 1) / 2
                let start_y = Math.ceil((y_left * 2 / steps + steps - 1) / 2);
                while(compute_final_y(start_y, steps) <= y_right){
                    if(compute_final_y(start_y, steps) < y_left){
                        start_y++;
                        continue;
                    }
                    /*
                    if(ans === undefined || ans < compute_highest_y(start_y, steps)){
                        ans = compute_highest_y(start_y, steps);
                    }
                     */
                    ans[[start_x, start_y]] = 1;
                    start_y++;
                }
                start_x++;
            }
        }
        console.log(Object.keys(ans).length);
    });

}

main();
