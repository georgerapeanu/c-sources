import {stdin} from 'process';
import * as readline from 'node:readline/promises';
import * as assert from "assert";
const rl = await readline.createInterface({input:stdin, output:null});
const d = [[-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1]];

async function debug(from_conf, from_nod, to_conf, to_nod, ways){
    if(ways === 0){
        return;
    }
    console.log(from_conf, from_nod, to_conf, to_nod, ways);
}

async function apply_fold(points, fold) {
    let answer = {};
    for(const point in points){
        let x = parseInt(point.split(",")[0].trim());
        let y = parseInt(point.split(",")[1].trim());
        if(fold[0] === "x"){
            if(x > fold[1]){
                x = 2 * fold[1] - x;
            }
        }else{
            if(y > fold[1]){
                y = 2 * fold[1] - y;
            }
        }
        answer[[x,y]]++;
    }
    return answer;
}

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        input_lines.push(line.trim());
    }).on('close', async () => {
        let folds = [];
        let end_points = false;
        let points = {};
        for(const i in input_lines){
            if(input_lines[i].trim() === ""){
                end_points = true;
            }else if(end_points){
                if(input_lines[i].includes("x=")){
                    let coord = parseInt(input_lines[i].split("x=")[1].trim());
                    folds.push(["x", coord]);
                }else{
                    let coord = parseInt(input_lines[i].split("y=")[1].trim());
                    folds.push(["y", coord]);
                }
            }else{
                let x = parseInt(input_lines[i].split(",")[0].trim());
                let y = parseInt(input_lines[i].split(",")[1].trim());
                points[[x, y]] = 1;
            }
        }

        for(let i = 0;i < folds.length;i++){
            points = await apply_fold(points, folds[i]);
        }
        let min_x, min_y, max_x, max_y;
        min_x = min_y = max_x = max_y = undefined;

        for(const point in points){
            let x = parseInt(point.split(",")[0].trim());
            let y = parseInt(point.split(",")[1].trim());
            if(min_x === undefined || min_x > x){
                min_x = x;
            }
            if(max_x === undefined || max_x < x){
                max_x = x
            }
            if(min_y === undefined || min_y > y){
                min_y = y;
            }
            if(max_y === undefined || max_y < y){
                max_y = y;
            }
        }
        for(let i = min_y;i <= max_y;i++){
            let line = "";
            for(let j = min_x;j < max_x;j++){
                if([j,i] in points){
                    line += "\x1b[40m ";
                }else{
                    line += "\x1b[47m ";
                }
            }
            line += "\x1b[0m";
            console.log(line);
        }
    });

}

main();
