import {stdin, stdout} from 'process';
import * as readline from 'node:readline/promises';
const rl = await readline.createInterface({input:stdin, output:null});

async function main(){
    let commands = [];
    rl.on('line', (input) => {
        let words = input.split(" ");
        commands.push([words[0], parseInt(words[1])]);
    }).on('close', async () => {
        let depth = 0;
        let position = 0;
        let aim = 0;
        for(const index in commands){
            if(commands[index][0] === "forward"){
                //position += commands[index][1];
                position += commands[index][1];
                depth += aim * commands[index][1];
            }else if(commands[index][0] === "up"){
                //depth -= commands[index][1];
                aim -= commands[index][1];
            }else{
                //depth += commands[index][1];
                aim += commands[index][1];
            }
        }
        console.log(depth * position);
    });
}

main();
