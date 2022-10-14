import {stdin} from 'process';
import * as readline from 'node:readline/promises';
const rl = await readline.createInterface({input:stdin, output:null});

/*
    C2: 1
    C3: 7
    C4: 4
    C5: 2, 3, 5
    C6: 0, 6, 9
    C7: 8

    a:8
    b:6
    c:8
    d:7
    e:4
    f:9
    g:7
    a = C3/C2
    g is always with an a
*/

async function get_mapping(inputs){
    let fr = new Array(7).fill(0);
    let mapping = new Array(7).fill(-1);
    inputs = inputs.sort((a, b) => a.length - b.length);
    for(const i in inputs){
        for(const j in inputs[i]){
            fr[inputs[i][j].charCodeAt(0) - 'a'.charCodeAt(0)]++;
        }
    }
    for(const i in fr){
        if(fr[i] === 4){
            mapping[i] = 'e'.charCodeAt(0) - 'a'.charCodeAt(0);
        }else if(fr[i] === 6){
            mapping[i] = 'b'.charCodeAt(0) - 'a'.charCodeAt(0);
        }else if(fr[i] === 9){
            mapping[i] = 'f'.charCodeAt(0) - 'a'.charCodeAt(0);
        }
    }
    let a_value = 0;
    for(const i in inputs[0]){
        a_value ^= inputs[0][i].charCodeAt(0) - 'a'.charCodeAt(0);
    }
    for(const i in inputs[1]){
        a_value ^= inputs[1][i].charCodeAt(0) - 'a'.charCodeAt(0);
    }
    mapping[a_value] = 'a'.charCodeAt(0) - 'a'.charCodeAt(0);
    let c_value = a_value;
    for(const i in fr){
        if(fr[i] === fr[a_value]){
            c_value ^= parseInt(i);
        }
    }
    mapping[c_value] = 'c'.charCodeAt(0) - 'a'.charCodeAt(0);

    let d_value = -1;
    let g_value = -1;

    for(const i in fr){
        if(fr[i] === 7){
            let tmp = parseInt(i);
            if(d_value === -1){
                d_value = tmp;
            }else{
                g_value = tmp;
            }
        }
    }

    let ok = false;
    for(const i in inputs){
        if(inputs[i].includes(String.fromCharCode(d_value + 'a'.charCodeAt(0)))){
            if(inputs[i].includes(String.fromCharCode(a_value + 'a'.charCodeAt(0))) === false){
                ok = true;
            }
        }
    }

    if(ok === true){
        mapping[d_value] = 'd'.charCodeAt(0) - 'a'.charCodeAt(0);
        mapping[g_value] = 'g'.charCodeAt(0) - 'a'.charCodeAt(0);
    }else{
        mapping[d_value] = 'g'.charCodeAt(0) - 'a'.charCodeAt(0);
        mapping[g_value] = 'd'.charCodeAt(0) - 'a'.charCodeAt(0);
    }

    return mapping;
}

const code_to_digit = {
    "abcefg"  : 0,
    "cf"      : 1,
    "acdeg"   : 2,
    "acdfg"   : 3,
    "bcdf"    : 4,
    "abdfg"   : 5,
    "abdefg"  : 6,
    "acf"     : 7,
    "abcdefg" : 8,
    "abcdfg"  : 9
};

async function decode(mapping, code){
    let real_code = "";
    for(const i in code){
        real_code += String.fromCharCode(mapping[code.charCodeAt(i) - 'a'.charCodeAt(0)] + 'a'.charCodeAt(0));
    }
    real_code = real_code.split("").sort().join("");
    return code_to_digit[real_code];
}

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        if(line.trim() !== ""){
            input_lines.push(line.trim());
        }
    }).on('close', async () => {
        let sum = 0;
        //let count = 0;
        //const search = "1478"
        for(const h in input_lines){
            let line = input_lines[h];
            const parts = line.split("|");
            let inputs = parts[0].trim().split(" ");
            let results = parts[1].trim().split(" ");

            let mapping = await get_mapping(inputs);
            let number_results = [];

            for(const i in results){
                number_results.push(await decode(mapping, results[i]));
            }
            //for(const i in number_results){
            //    if(search.includes(String.fromCharCode(number_results[i] + '0'.charCodeAt(0)))){
            //        count++;
            //    }
            //}
            let number = 0;
            for(const i in number_results){
                number = number * 10 + number_results[i];
            }
            sum += number;
        }
        //console.log(count);
        console.log(sum);
    });


}

main();
