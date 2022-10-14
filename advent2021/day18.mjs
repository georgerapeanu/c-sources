import {stdin} from 'process';
import * as readline from 'node:readline/promises';
import * as assert from "assert";
const rl = await readline.createInterface({input:stdin, output:null});

class Node{
    constructor(){
        this.value = 0;
        this.sons = [];
        this.father = null;
        this.weight = 0;
    }
}

class NodeUtils{

    static calculate_weight(node){
        node.weight = 0;
        for(const son in node.sons){
            NodeUtils.calculate_weight(node.sons[son]);
            node.weight += node.sons[son].weight;
        }
        if(node.weight === 0){
            node.weight = 1;
        }
    }

    static string_to_node(s){
        let root = new Node();
        let current_nodes = [root];

        for(let i = 0;i < s.length;i++){
            if(s[i] === '['){
                let father = null;
                if(current_nodes.length !== 0){
                    father = current_nodes[current_nodes.length - 1];
                }
                let current = new Node();
                current.father = father;
                if(father !== null){
                    father.sons.push(current);
                }
                current_nodes.push(current);
            }else if(s[i] === ','){
                let father = null;
                if(current_nodes.length - 1 !== 0){
                    father = current_nodes[current_nodes.length - 2];
                }
                let current = new Node();
                current.father = father;
                if(father !== null){
                    father.sons.push(current);
                }
                current_nodes[current_nodes.length - 1] = current;
            }else if(s[i] === ']'){
                current_nodes.pop();
            }else{
                current_nodes[current_nodes.length - 1].value *= 10;
                current_nodes[current_nodes.length - 1].value += s.charCodeAt(i) - '0'.charCodeAt(0);
            }
        }
        NodeUtils.calculate_weight(root);
        return root;
    }

    static get_regular_position(node){
        let ancestors = [node];
        while(ancestors[ancestors.length - 1].father !== null){
            ancestors.push(ancestors[ancestors.length - 1].father);
        }
        let pos = 0;
        for(let i = ancestors.length - 1;i > 0;i--){
            if(ancestors[i - 1] === ancestors[i].sons[1]){
                pos += ancestors[i].sons[0].weight;
            }
        }
        return pos;
    }

    static get_node_from_regular_position(node, pos){
        if(pos < 0 || node.weight <= pos){
            return null;
        }
        if(node.sons.length === 0){
            return node;
        }
        if(pos < node.sons[0].weight){
            return NodeUtils.get_node_from_regular_position(node.sons[0], pos);
        }
        return NodeUtils.get_node_from_regular_position(node.sons[1], pos - node.sons[0].weight);
    }

    static __find_first_explodeable(node, level){
        if(node.sons.length === 0){
            return null;
        }
        if(level >= 4){
            return node;
        }
        let tmp = NodeUtils.__find_first_explodeable(node.sons[0], level + 1);
        if(tmp !== null){
            return tmp;
        }
        return NodeUtils.__find_first_explodeable(node.sons[1], level + 1);
    }

    static find_first_explodeable(node){
        return NodeUtils.__find_first_explodeable(node, 0);
    }

    static find_first_splitable(node){

        if(node.sons.length === 0){
            if(node.value > 9){
                return node;
            }
            return null;
        }

        let tmp = NodeUtils.find_first_splitable(node.sons[0]);
        if(tmp !== null){
            return tmp;
        }
        return NodeUtils.find_first_splitable(node.sons[1]);
    }

    static NodeDeepCopy(root){
        let copy_root = new Node();
        copy_root.weight = root.weight;
        copy_root.value = root.value;
        if(root.sons.length === 0){
            return copy_root;
        }

        for(const i in root.sons){
            let son = NodeUtils.NodeDeepCopy(root.sons[i]);
            copy_root.sons.push(son);
            son.father = copy_root;
        }
        return copy_root;
    }

    static add(a, b){
        let c = NodeUtils.NodeDeepCopy(a);
        let d = NodeUtils.NodeDeepCopy(b);
        let root = new Node();
        root.weight = c.weight + d.weight;
        root.sons = [c, d];
        c.father = root;
        d.father = root;
        return NodeUtils.reduce(root);
    }

    static reduce(root){
        //console.log("reduce");
        while(true){
            //console.log(NodeUtils.node_to_string(root));
            if(NodeUtils.find_first_explodeable(root) !== null){
                //console.log("explode");
                let explode = NodeUtils.find_first_explodeable(root);
                let a = explode.sons[0].value;
                let b = explode.sons[1].value;
                explode.sons = [];
                explode.value = 0;
                NodeUtils.calculate_weight(root);
                let explode_pos = NodeUtils.get_regular_position(explode);
                //console.log("explode_node ", explode);
                if(NodeUtils.get_node_from_regular_position(root, explode_pos - 1) !== null){
                    NodeUtils.get_node_from_regular_position(root, explode_pos - 1).value += a;
                }
                if(NodeUtils.get_node_from_regular_position(root, explode_pos + 1) !== null){
                    NodeUtils.get_node_from_regular_position(root, explode_pos + 1).value += b;
                }
                continue;
            }else if(NodeUtils.find_first_splitable(root) !== null){
          //      console.log("split");
                let split = NodeUtils.find_first_splitable(root);
                split.sons = [new Node(), new Node()];
                split.sons[0].value = Math.floor(split.value / 2);
                split.sons[1].value = Math.ceil(split.value / 2);
                split.sons[0].father = split;
                split.sons[1].father = split;
                split.value = 0;
                NodeUtils.calculate_weight(root);
                continue;
            }
            break;
        }
        return root;
    }

    static node_to_string(root){
        if(root.sons.length === 0){
            return root.value.toString();
        }
        return "[" + NodeUtils.node_to_string(root.sons[0]) + "," + NodeUtils.node_to_string(root.sons[1]) + "]";
    }

    static get_magnitutde(root){
        if(root.sons.length === 0){
            return root.value;
        }
        return 3 * NodeUtils.get_magnitutde(root.sons[0]) + 2 * NodeUtils.get_magnitutde(root.sons[1]);
    }

    static make_garbage_collectable(local_root) {
        if(local_root.sons.length === 0){
            local_root.father = null;
            return ;
        }
        for(const son in local_root.sons){
            NodeUtils.make_garbage_collectable(local_root.sons[son]);
        }
        for(const son in local_root.sons){
            local_root.sons[son] = null;
        }
        local_root.sons = [];
        local_root.father = null;
    }
}

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        if(line.trim().length !== 0){
            input_lines.push(line.trim());
        }
    }).on('close', async () => {
        let numbers = [];
        for(const i in input_lines){
            numbers.push(NodeUtils.string_to_node(input_lines[i]));
            //console.log(NodeUtils.node_to_string(numbers[numbers.length - 1]));
        }

        /*
        let ans = numbers[0];
        for(let i = 1;i < numbers.length;i++){
            ans = NodeUtils.add(ans, numbers[i]);
        }
        console.log(NodeUtils.get_magnitutde(ans));
        */
        let ans = 0;
        for(let i = 0;i < numbers.length;i++){
            for(let j = 0; j < numbers.length;j++){
                if(i === j){
                    continue;
                }
                console.log("doing ", i, j);

                let local_root = NodeUtils.add(numbers[i], numbers[j]);
                let local_ans = NodeUtils.get_magnitutde(local_root);
                NodeUtils.make_garbage_collectable(local_root);
                if(local_ans > ans){
                    ans = local_ans;
                }
            }
        }
        console.log(ans);
    });

}

main();
