import {stdin} from 'process';
import * as readline from 'node:readline/promises';
import * as assert from "assert";
const rl = await readline.createInterface({input:stdin, output:null});

function access(dp, i, j, s1, s2, k){
    if(s1 >= 21){
        return 1 - k;
    }else if(s2 >= 21){
        return k;
    }
    return dp[i][j][s1][s2][k];
}

function unique(v){
    let ans = [];
    for(const i in v){
        if(ans.length === 0 || v[i] !== ans[ans.length - 1]){
            ans.push(v[i]);
        }
    }
    return ans;
}

function get_index(v, value){
    let st = -1;
    let dr = v.length;

    while(dr - st > 1){
        let mid = Math.floor((st + dr) / 2);
        if(v[mid] < value){
            st = mid;
        }else{
            dr = mid;
        }
    }
    return dr;
}

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        if(line.trim().length !== 0){
            input_lines.push(line.trim());
        }
    }).on('close', async () => {
        let ranges = [];
        let commands = [];
        for(const i in input_lines){
            let coords = input_lines[i].split(",");
            commands.push(input_lines[i].split(" ")[0].trim());
            let range = [];
            for(const i in coords){
                coords[i] = coords[i].split("=")[1];
                range.push([parseInt(coords[i].split("..")[0]), parseInt(coords[i].split("..")[1]) + 1]);
            }
            ranges.push(range);
        }

        let xs = [];
        let ys = [];
        let zs = [];

        for(const i in ranges){
            xs.push(ranges[i][0][0]);
            xs.push(ranges[i][0][1]);
            ys.push(ranges[i][1][0]);
            ys.push(ranges[i][1][1]);
            zs.push(ranges[i][2][0]);
            zs.push(ranges[i][2][1]);
        }

        xs.sort((a, b) => a - b);
        ys.sort((a, b) => a - b);
        zs.sort((a, b) => a - b);

        xs = unique(xs);
        ys = unique(ys);
        zs = unique(zs);

        for(const i in ranges){
            ranges[i][0][0] = get_index(xs, ranges[i][0][0]);
            ranges[i][0][1] = get_index(xs, ranges[i][0][1]);
            ranges[i][1][0] = get_index(ys, ranges[i][1][0]);
            ranges[i][1][1] = get_index(ys, ranges[i][1][1]);
            ranges[i][2][0] = get_index(zs, ranges[i][2][0]);
            ranges[i][2][1] = get_index(zs, ranges[i][2][1]);
        }


        let ans = 0;

        for(let x = 0;x < xs.length - 1;x++){
            for(let y = 0;y < ys.length - 1;y++){
                for(let z = 0;z < zs.length - 1;z++){
                    for(let i = ranges.length - 1;i >= 0;i--){
                        if(ranges[i][0][0] <= x && x < ranges[i][0][1]){
                            if(ranges[i][1][0] <= y && y < ranges[i][1][1]){
                                if(ranges[i][2][0] <= z && z < ranges[i][2][1]){
                                    if(commands[i] === "on"){
                                        ans +=  (xs[x + 1] - xs[x]) *
                                                (ys[y + 1] - ys[y]) *
                                                (zs[z + 1] - zs[z]);
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        console.log(ans);
    });

}

main();
