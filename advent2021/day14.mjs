import {stdin} from 'process';
import * as readline from 'node:readline/promises';
import * as assert from "assert";
const rl = await readline.createInterface({input:stdin, output:null});

async function do_step(polymer, composition){
    let result = {};
    for(const reactants in polymer){
        if(reactants in composition){
            if(!((reactants[0] + composition[reactants]) in result)){
                result[reactants[0] + composition[reactants]] = 0;
            }
            result[reactants[0] + composition[reactants]] += polymer[reactants];
            if(!((composition[reactants] + reactants[1]) in result)){
                result[composition[reactants] + reactants[1]] = 0;
            }
            result[composition[reactants] + reactants[1]] += polymer[reactants];
        }else{
            if(!(reactants in polymer)){
                polymer[reactants] = 0;
            }
            result[reactants] += polymer[reactants];
        }
    }
    return result;
}

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        input_lines.push(line.trim());
    }).on('close', async () => {
        let polymer = {};
        let composition = {};
        for(let i = 0;i + 1 < input_lines[0].length;i++){
            if(!(input_lines[0].slice(i, i + 2) in polymer)) {
                polymer[input_lines[0].slice(i, i + 2)] = 0;
            }
            polymer[input_lines[0].slice(i, i + 2)]++;
        }
        for(let i = 2;i < input_lines.length;i++){
            let reactants = input_lines[i].split("->")[0].trim();
            let product = input_lines[i].split("->")[1].trim();
            composition[reactants] = product;
        }

        for(let i = 0;i < 40;i++) {
            polymer = await do_step(polymer, composition);
        }

        let fr = {};

        for(const reactants in polymer){
            if(!(reactants.charCodeAt(0) in fr)){
                fr[reactants.charCodeAt(0)] = 0;
            }
            fr[reactants.charCodeAt(0)] += polymer[reactants];
            if(!(reactants.charCodeAt(1) in fr)){
                fr[reactants.charCodeAt(1)] = 0;
            }
            fr[reactants.charCodeAt(1)] += polymer[reactants];
        }
        fr[input_lines[0].charCodeAt(0)] += 1;
        fr[input_lines[0].charCodeAt(input_lines[0].length - 1)] += 1;

        for(const it in fr){
            fr[it] = Math.floor(fr[it] / 2);
        }


        let _min = undefined, _max = undefined;

        for(const i in fr){
            if(_min === undefined || fr[i] < _min){
                _min = fr[i];
            }
            if(_max === undefined || fr[i] > _max){
                _max = fr[i];
            }
        }
        console.log(_max - _min);
    });

}

main();
