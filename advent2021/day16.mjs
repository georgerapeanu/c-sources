import {stdin} from 'process';
import * as readline from 'node:readline/promises';
import * as assert from "assert";
const rl = await readline.createInterface({input:stdin, output:null});

class Node{
    constructor(){
        this.sons = []
        this.version = 0;
        this.type = 0;
        this.value = 0;
    }

    dfs(){
        /*
        let ans = this.version;
        for(const i in this.sons){
            ans += this.sons[i].dfs();
        }
        return ans;
         */
        if(this.type === 0){
            assert.equal((this.sons.length > 0), true);
            let ans = 0;
            for(const i in this.sons){
                ans += this.sons[parseInt(i)].dfs();
            }
            return ans;
        }else if(this.type === 1){
            assert.equal((this.sons.length > 0), true);
            let ans = 1;
            for(const i in this.sons){
                ans *= this.sons[parseInt(i)].dfs();
            }
            return ans;
        }else if(this.type === 2){
            assert.equal((this.sons.length > 0), true);
            let ans = undefined;
            for(const i in this.sons){
                if(ans === undefined){
                    ans = this.sons[parseInt(i)].dfs();
                }else{
                    ans = Math.min(ans, this.sons[parseInt(i)].dfs());
                }
            }
            return ans;
        }else if(this.type === 3){
            assert.equal((this.sons.length > 0), true);
            let ans = undefined;
            for(const i in this.sons){
                if(ans === undefined){
                    ans = this.sons[parseInt(i)].dfs();
                }else{
                    ans = Math.max(ans, this.sons[parseInt(i)].dfs());
                }
            }
            return ans;
        }else if(this.type === 4){
            return this.value;
        }else if(this.type === 5){
            assert.equal(this.sons.length, 2);
            if(this.sons[0].dfs() > this.sons[1].dfs()){
                return 1;
            }
            return 0;
        }else if(this.type === 6){
            assert.equal(this.sons.length, 2);
            if(this.sons[0].dfs() < this.sons[1].dfs()){
                return 1;
            }
            return 0;
        }else if(this.type === 7){
            assert.equal(this.sons.length, 2);
            if(this.sons[0].dfs() === this.sons[1].dfs()){
                return 1;
            }
            return 0;
        }
        assert.equal(false, true);
    }
}

class Parse{

    static converter = {
        '0': 0,
        '1': 1,
        '2': 2,
        '3': 3,
        '4': 4,
        '5': 5,
        '6': 6,
        '7': 7,
        '8': 8,
        '9': 9,
        'a': 10,
        'b': 11,
        'c': 12,
        'd': 13,
        'e': 14,
        'f': 15
    };

    static get_bit(s, pos){
        if(s.length * 4 <= pos){
            assert.equal(false, true);
        }
        let nibble = Parse.converter[s.toLowerCase()[Math.floor(pos / 4)]];
        return (nibble >> (3 - (pos & 3))) & 1;
    }

    static get_value(s, l, r){
        let value = 0;
        for(let i = l;i <= r;i++){
            value = value * 2 + Parse.get_bit(s, i);
        }
        return value;
    }

    static parse_literal_node(s, idx){
        return Parse.get_value(s, idx, idx + 4);
    }

    static parse_literal_value(s, idx){
        let value = 0;
        while(true){
            let current = Parse.parse_literal_node(s, idx);
            idx += 5;
            value = (value * 16) + (current & ((1 << 4) - 1));
            //value = (value << 4) | (current & ((1 << 4) - 1)); WHY is it not the same
            if((current >> 4) === 0){
                break;
            }
        }
        return [value, idx];
    }

    static parse_node(s, idx){
        let node = new Node();
        node.version = Parse.get_value(s, idx, idx + 2);
        idx += 3;
        node.type = Parse.get_value(s, idx, idx + 2);
        idx += 3;
        if(node.type === 4){
            [node.value, idx] = Parse.parse_literal_value(s, idx);
        }else{
            let type = Parse.get_bit(s, idx);
            idx++;
            if(type === 0){
                let total_length = Parse.get_value(s, idx, idx + 14);
                idx += 15;
                let end_point = idx + total_length;
                while(idx !== end_point){
                    let son;
                    [son, idx] = Parse.parse_node(s, idx);
                    node.sons.push(son);
                }
            }else{
                let subpackages = Parse.get_value(s, idx, idx + 10);
                idx += 11;
                for(let h = 0;h < subpackages;h++){
                    let son;
                    [son, idx] = Parse.parse_node(s, idx);
                    node.sons.push(son);
                }
            }
        }
        return [node, idx];
    }
}

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        input_lines.push(line.trim());
    }).on('close', async () => {
        let node, idx;
        [node, idx] = Parse.parse_node(input_lines[0], 0);
        if(idx > input_lines[0].length * 4){
            assert.equal(false, true);
        }

        console.log(node.dfs());

    });

}

main();
