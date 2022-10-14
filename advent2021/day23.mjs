///i did part 1 manually I'm so sorry
import {stdin} from 'process';
import * as readline from 'node:readline/promises';
import * as assert from "assert";
const rl = await readline.createInterface({input:stdin, output:null});



const LAYERS = 4;
const COST = [1, 10, 100, 1000];
const TRANSIT = [1,2,2,2,2,1];

class State{

    constructor(){
        this.cost = 0;
        this.hallway = [];
        this.stacks = [];
    }

    static from_string(lines, cost){
        let ans = new State();
        ans.cost = cost;
        ans.hallway = Array(7).fill(0);
        ans.stacks = [[], [], [], []];
        ans.hallway[0] = lines[1].charCodeAt(1) - 'A'.charCodeAt(0);
        ans.hallway[1] = lines[1].charCodeAt(2) - 'A'.charCodeAt(0);
        ans.hallway[2] = lines[1].charCodeAt(4) - 'A'.charCodeAt(0);
        ans.hallway[3] = lines[1].charCodeAt(6) - 'A'.charCodeAt(0);
        ans.hallway[4] = lines[1].charCodeAt(8) - 'A'.charCodeAt(0);
        ans.hallway[5] = lines[1].charCodeAt(9) - 'A'.charCodeAt(0);
        ans.hallway[6] = lines[1].charCodeAt(10) - 'A'.charCodeAt(0);
        for(const i in ans.hallway){
            if(ans.hallway[i] === '.'.charCodeAt(0) - 'A'.charCodeAt(0)){
                ans.hallway[i] = -1;
            }
        }
        for(let i = lines.length - 2;i > 1;i--){
            for(let j = 3;j < 11;j += 2){
                if(lines[i][j] !== '.'){
                    ans.stacks[(j - 3) / 2].push(lines[i].charCodeAt(j) - 'A'.charCodeAt(0));
                }
            }
        }
        return ans;
    }
    
    static from_state(state, cost){
        let ans = new State();
        ans.hallway = JSON.parse(JSON.stringify(state.hallway));
        ans.cost = cost;
        ans.stacks = JSON.parse(JSON.stringify(state.stacks));
        return ans;
    }

    get_next_states(){
        let moves = [];

        ///to hallway moves
        for(let j = 0;j < 4;j++){
            if(this.stacks[j].length === 0){
                continue;
            }
            let makes_sense = false;
            for(const k in this.stacks[j]){
                if(this.stacks[j][k] !== j){
                    makes_sense = true;
                }
            }
            if(makes_sense === false){
                continue;
            }
            let top = this.stacks[j][this.stacks[j].length - 1];
            let distance = LAYERS - this.stacks[j].length + 2;///distance to either j + 1 or j + 2
            let running_distance = distance;
            for(let i = j + 1;i >= 0;i--){
                if(this.hallway[i] !== -1){
                    break;
                }
                let new_state = State.from_state(this, this.cost + running_distance * COST[top]);
                new_state.hallway[i] = top;
                new_state.stacks[j].pop();
                moves.push(new_state);
                if(i > 0){
                    running_distance += TRANSIT[i - 1];
                }
            }
            running_distance = distance;
            for(let i = j + 2;i < this.hallway.length;i++){
                if(this.hallway[i] !== -1){
                    break;
                }
                let new_state = State.from_state(this, this.cost + running_distance * COST[top]);
                new_state.hallway[i] = top;
                new_state.stacks[j].pop();
                moves.push(new_state);
                if(i > 0){
                    running_distance += TRANSIT[i];
                }
            }
        }

        ///from hallway moves

        for(let j = 0;j < 4;j++){
            if(this.stacks[j].length === LAYERS){
                continue;
            }
            let makes_sense = true;
            for(const k in this.stacks[j]){
                if(this.stacks[j][k] !== j){
                    makes_sense = false;
                }
            }
            if(makes_sense === false){
                continue;
            }
            let distance = LAYERS - this.stacks[j].length + 1; /// distance from either j + 1 or j + 2
            let running_distance = distance;
            for(let i = j + 1;i >= 0;i--){
                if(this.hallway[i] !== -1){
                    if(this.hallway[i] !== j){
                        break;
                    }
                    let new_state = State.from_state(this, this.cost + running_distance * COST[this.hallway[i]]);
                    new_state.hallway[i] = -1;
                    new_state.stacks[j].push(this.hallway[i]);
                    moves.push(new_state);
                    break;
                }
                if(i > 0){
                    running_distance += TRANSIT[i - 1];
                }
            }
            running_distance = distance;
            for(let i = j + 2;i < this.hallway.length;i++){
                if(this.hallway[i] !== -1){
                    if(this.hallway[i] !== j){
                        break;
                    }
                    let new_state = State.from_state(this, this.cost + running_distance * COST[this.hallway[i]]);
                    new_state.hallway[i] = -1;
                    new_state.stacks[j].push(this.hallway[i]);
                    moves.push(new_state);
                    break;
                }
                if(i > 0){
                    running_distance += TRANSIT[i];
                }
            }
        }

        return moves;
    }

    to_string(){
        let tmp = State.from_state(this);
        delete tmp.cost;
        return JSON.stringify(tmp);
    }

    is_final(){
        for(const i in this.hallway){
            if(this.hallway[i] !== -1){
                return false;
            }
        }
        for(let j = 0;j < 4;j++){
            if(this.stacks[j].length !== LAYERS){
                return false;
            }
            for(const k in this.stacks[j]){
                if(this.stacks[j][k] !== j){
                    return false;
                }
            }
        }
        return true;
    }

    to_char(c){
        if(c === -1){
            return ".";
        }
        return String.fromCharCode(c + "A".charCodeAt(0));
    }

    debug_string(){
        let ans = "#############";
        ans += "\n";
        ans += "#";
        let last = 0;
        for(let i = 0;i < 11;i++){
            if(i === 2 || i === 4 || i === 6 || i === 8){
                ans += ".";
            }else{
                ans += this.to_char(this.hallway[last]); ///TODO
                last++;
            }
        }
        ans += "\n";
        for(let i = LAYERS - 1;i >= 0;i--){
            ans += "  #";
            for(let j = 0;j < 4;j++){
                if(i >= this.stacks[j].length){
                    ans += ".";
                }else{
                    ans += this.to_char(this.stacks[j][i]);
                }
                ans += "#";
            }
            ans += "\n";
        }
        ans += "  #########"
        ans += "\n\n";
        return ans;
    }
}


class PriorityQueue{
    constructor(cmp){
        this.cmp = cmp;
        this.nodes = [0];
    }

    upheap(index){
        while(index !== 1){
            let father = Math.floor(index / 2);
            if(this.cmp(this.nodes[father], this.nodes[index]) === -1){
                let tmp = this.nodes[father];
                this.nodes[father] = this.nodes[index];
                this.nodes[index] = tmp;
                index = father;
            }else{
                break;
            }
        }
    }

    downheap(index){
        while(true){
            if(index * 2 >= this.nodes.length){
                break;
            }
            let best_child = index * 2;
            if(index * 2 + 1 < this.nodes.length){
                if(this.cmp(this.nodes[best_child], this.nodes[index * 2 + 1]) === -1){
                    best_child = index * 2 + 1;
                }
            }
            if(this.cmp(this.nodes[index], this.nodes[best_child]) === -1){
                let tmp = this.nodes[index];
                this.nodes[index] = this.nodes[best_child];
                this.nodes[best_child] = tmp;
                index = best_child;
            }else{
                break;
            }
        }
    }

    get length(){
        return this.nodes.length - 1;
    }

    top(){
        return this.nodes[1];
    }

    pop(){
        let ans = this.nodes[1];
        this.nodes[1] = this.nodes[this.nodes.length - 1];
        this.nodes.pop();
        this.downheap(1);
        return ans;
    }

    push(node){
        this.nodes.push(node);
        this.upheap(this.nodes.length - 1);
    }
}

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        if(line.trim().length !== 0){
            input_lines.push(line);
        }
    }).on('close', async () => {
        let new_lines = [];
        for(let i = 0;i < input_lines.length;i++){
            new_lines.push(input_lines[i]);
            if(i === 2){
                new_lines.push("  #D#C#B#A#");
                new_lines.push("  #D#B#A#C#");
            }
        }

        let state = State.from_string(new_lines, 0);

        let dist = {};
        let prev = {};
        dist[state.to_string()] = state.cost;
        let compare = ((x, y) => x.cost < y.cost ? 1 : (x.cost > y.cost ? -1:0));
        const pq = new PriorityQueue(compare);
        pq.push(state);

        let final_state = null;
        while(pq.length > 0){
            let state = pq.pop();
            if(state.cost !== dist[state.to_string()]){
                continue;
            }
            if(state.is_final()){
                console.log(state.cost);
                final_state = state;
                break;
            }
            let moves = state.get_next_states();

            for(const move in moves){
                if((!(moves[move].to_string() in dist)) || dist[moves[move].to_string()] > moves[move].cost){
                    dist[moves[move].to_string()] = moves[move].cost;
                    prev[moves[move].to_string()] = state;
                    pq.push(moves[move]);
                }
            }
        }

        return; ///apparently there are no "in between" moves on the hallway
                ///but somehow ignoring this passes the first part too

        while(final_state.to_string() in prev){
            console.log(final_state.cost);
            console.log(final_state.debug_string());
            final_state = prev[final_state.to_string()];
        }
        console.log(final_state);
    });

}

main();
