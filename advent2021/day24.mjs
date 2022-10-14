import {stdin} from 'process';
import * as readline from 'node:readline/promises';
import * as assert from "assert";
const rl = await readline.createInterface({input:stdin, output:null});

class ALUExpression{
    constructor(lines){
        this.eip = 0;
        this.registers = {
            "x": "x",
            "y": "y",
            "z": "z",
            "w": "w"
        }
        this.instructions = JSON.parse(JSON.stringify(lines));
    }

    run(){
        let input_count = 0;
        while(this.eip < this.instructions.length){
            let parts = this.instructions[this.eip].split(" ");
            for(const i in parts){
                parts[i] = parts[i].trim();
            }
            if(parts[0] === "inp"){
                this.registers[parts[1]] = "inp" + input_count.toString();
                input_count++;
            }else if(parts[0] === "add" ){
                if(parts[2] in this.registers){
                    if(this.registers[parts[1]] === "0"){
                        this.registers[parts[1]] = this.registers[parts[2]];
                    }else{
                        this.registers[parts[1]] = this.registers[parts[1]] + " + " + this.registers[parts[2]];
                    }
                }else if(parseInt(parts[2]) !== 0){
                    if(parseInt(parts[2]) < 0){
                        if(this.registers[parts[1]] === "0"){
                            this.registers[parts[1]] = "-" + -parts[2];
                        }else{
                            this.registers[parts[1]] = this.registers[parts[1]] + " - " + -parts[2];
                        }
                    }else{
                        if(this.registers[parts[1]] === "0"){
                            this.registers[parts[1]] = parts[2];
                        }else{
                            this.registers[parts[1]] = this.registers[parts[1]] + " + " + parts[2];
                        }
                    }
                }
            }else if(parts[0] === "mul"){
                if(this.registers[parts[1]] === "0"){
                    ;
                }else if(parts[2] in this.registers){
                    if(this.registers[parts[2]] === "0"){
                        this.registers[parts[1]] = "0";
                    }else{
                        this.registers[parts[1]] = "(" + this.registers[parts[1]] + ") * (" + this.registers[parts[2]] + ")";
                    }

                }else{
                    if(parseInt(parts[2]) === 0){
                        this.registers[parts[1]] = "0";
                    }else{
                        this.registers[parts[1]] = "(" + this.registers[parts[1]] + ") * " + parts[2];
                    }
                }
            }else if(parts[0] === "div"){
                if(this.registers[parts[1]] === "0"){
                    ;
                }
                else if(parts[2] in this.registers){
                    if(this.registers[parts[2]] === "0"){
                        assert.equal(false, true);
                    }else{
                        this.registers[parts[1]] = "(" + this.registers[parts[1]] + ") / (" + this.registers[parts[2]] + ")";
                    }

                }else{
                    if(parseInt(parts[2]) === 0){
                        assert.equal(false, true);
                    }else{
                        this.registers[parts[1]] = "(" + this.registers[parts[1]] + ") / " + parts[2];
                    }
                }
            }else if(parts[0] === "mod"){
                if(this.registers[parts[1]] === "0"){
                    ;
                }
                else if(parts[2] in this.registers){
                    if(this.registers[parts[2]] === "0"){
                        assert.equal(false, true);
                    }else{
                        this.registers[parts[1]] = "(" + this.registers[parts[2]] + ") % (" + this.registers[parts[2]] + ")";
                    }

                }else{
                    if(parseInt(parts[2]) <= 0){
                        assert.equal(false, true);
                    }else{
                        this.registers[parts[1]] = "(" + this.registers[parts[1]] + ") % " + parts[2];
                    }
                }
            }else if(parts[0] === "eql"){
                if(parts[2] in this.registers){
                    this.registers[parts[1]] = "(" + this.registers[parts[1]] + ") === (" + this.registers[parts[2]] + ")";
                }else{
                    this.registers[parts[1]] = "(" + this.registers[parts[1]] + ") === " + parts[2];
                }
            }
            this.eip++;
        }
        return JSON.stringify(this.registers);
    }
}

class ALUSimulator{
    constructor(lines){
        this.eip = 0;
        this.registers = {
            "x": 0,
            "y": 0,
            "z": 0,
            "w": 0
        }
        this.instructions = JSON.parse(JSON.stringify(lines));
    }

    init(input){
        this.eip = 0;
        this.registers = {
            "x": 0,
            "y": 0,
            "z": 0,
            "w": 0
        }
        this.input = input
    }

    run(){
        let input_count = 0;
        while(this.eip < this.instructions.length){
            let parts = this.instructions[this.eip].split(" ");
            for(const i in parts){
                parts[i] = parts[i].trim();
            }
            if(parts[0] === "inp"){
                if(input_count >= this.input.length){
                    break;
                }
                this.registers[parts[1]] = this.input[input_count];
                input_count++;
            }else if(parts[0] === "add" ){
                if(parts[2] in this.registers){
                    this.registers[parts[1]] = this.registers[parts[1]] + this.registers[parts[2]];
                }else {
                    this.registers[parts[1]] = this.registers[parts[1]] + parseInt(parts[2]);
                }
            }else if(parts[0] === "mul"){
                if(parts[2] in this.registers){
                    this.registers[parts[1]] = this.registers[parts[1]] * this.registers[parts[2]];
                }else{
                    this.registers[parts[1]] = this.registers[parts[1]] * parseInt(parts[2]);
                }
            }else if(parts[0] === "div"){
                if(parts[2] in this.registers){
                    this.registers[parts[1]] = Math.floor(this.registers[parts[1]] / this.registers[parts[2]]);
                }else{
                    this.registers[parts[1]] = Math.floor(this.registers[parts[1]] / parseInt(parts[2]));
                }
            }else if(parts[0] === "mod"){
                if(parts[2] in this.registers){
                    this.registers[parts[1]] = this.registers[parts[2]] % this.registers[parts[2]];
                }else{
                    this.registers[parts[1]] = this.registers[parts[1]] % parseInt(parts[2]);
                }
            }else if(parts[0] === "eql"){
                if(parts[2] in this.registers){
                    if(this.registers[parts[1]] === this.registers[parts[2]]){
                        this.registers[parts[1]] = 1;
                    }else{
                        this.registers[parts[1]] = 0;
                    }

                }else{
                    if(this.registers[parts[1]] === parseInt(parts[2])){
                        this.registers[parts[1]] = 1;
                    }else{
                        this.registers[parts[1]] = 0;
                    }
                }
            }
            this.eip++;
        }
        return JSON.stringify(this.registers);
    }
}

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        if(line.trim().length !== 0){
            input_lines.push(line);
        }
    }).on('close', async () => {
        /*
        let alu = new ALUSimulator(input_lines);
        let plm = {};
        const LIM = 1e6;
        for(let input = 0;input < LIM;input++){
            let l = []
            for(let i = LIM / 10;i > 0;i = Math.floor(i / 10)){
                l.push(Math.floor(input / i) % 10);
            }
            alu.init(l);
            plm[JSON.parse(alu.run())["z"]] = 1;
        }
        console.log(Object.keys(plm).length);
         */



        //alu.init([1]);
        //console.log(alu.run());

        let states = {0:0};

        let curr_lines = [];
        for(let i = 0;i < input_lines.length;i++){
            curr_lines.push(input_lines[i]);
            if(i % 18 === 17){///hardcoded I'm sorry
                console.log(`doing ${(i + 1) / 18} ${Object.keys(states).length}`);
                let new_states = {};
                let cnt = 0;
                for(const state in states){
                    cnt++;
                    if(cnt % 5000 === 0){
                        console.log(`now at ${cnt}`);
                    }
                    let alu = new ALUSimulator(curr_lines);
                    for(let c = 1;c <= 9;c++){
                        alu.init([c]);
                        alu.registers["z"] = parseInt(state); ///manually setting z in order to resume
                        let tmp = JSON.parse(alu.run());
                        if(tmp["z"] >= Math.pow(26, input_lines.length / 18 - (i + 1) / 18)){
                            continue;
                        }
                        if(!(tmp["z"] in new_states)){
                            new_states[tmp["z"]] = states[state] * 10 + c;
                        }else if(new_states[tmp["z"]] > states[state] * 10 + c){
                            new_states[tmp["z"]] = states[state] * 10 + c;
                        }
                    }
                }
                states = new_states;
                curr_lines = [];
            }
        }
        console.log(states["0"]);

        /*
        let curr_lines = [];
        for(let i = 0;i < input_lines.length;i++){
            curr_lines.push(input_lines[i]);
            if(i % 18 === 17){///hardcoded I'm sorry
                let alu_expression = new ALUExpression(curr_lines);
                let tmp = JSON.parse(alu_expression.run());
            //    console.log(tmp['x']);
            //    console.log(tmp['y']);
                console.log(tmp['z']);
            //    console.log(tmp['w']);
                console.log(" ");
                ///at the end of a block the variables are all functions of the last z and the new input
                ///that means that between each block x, y, w are discarded so we can just ignore them
                ///I could build a transpiler using this information
                ///useful, going back to the meet in the middle, looks like z reaches 5 digits in base26 tops
                curr_lines = [];
            }
        }
         */
    });

}

main();
