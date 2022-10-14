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

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        if(line.trim() !== ""){
            input_lines.push(line.trim());
        }
    }).on('close', async () => {
        let to_norm = {};
        let graph = [];
        let last_id = 0;
        let cnt_low = 0;
        let cnt_high = 0;

        for(const i in input_lines){
            let nodes = input_lines[i].trim().split("-");
            assert.equal(nodes.length, 2);
            if(!(nodes[0].trim() in to_norm)){
                to_norm[nodes[0].trim()] = last_id++;
                graph.push([]);
                if(nodes[0].trim().toLowerCase() === nodes[0]){
                    cnt_low++;
                }else{
                    cnt_high++;
                }
            }
            if(!(nodes[1].trim() in to_norm)){
                to_norm[nodes[1].trim()] = last_id++;
                graph.push([]);
                if(nodes[1].trim().toLowerCase() === nodes[1]){
                    cnt_low++;
                }else{
                    cnt_high++;
                }
            }
            graph[to_norm[nodes[0].trim()]].push(to_norm[nodes[1].trim()]);
            graph[to_norm[nodes[1].trim()]].push(to_norm[nodes[0].trim()]);
        }
        let start = to_norm["start"];
        let end = to_norm["end"];
        let dp = [];
        let to_norm_low = {};
        let to_norm_low_cnt = 0;
        for(const i in to_norm){
            if(i.toLowerCase() === i){
                to_norm_low[to_norm[i]] = to_norm_low_cnt++;
            }
        }
        for(let i = 0;i < (1 << cnt_low);i++){
            dp.push([]);
            for(let j = 0;j < cnt_low + cnt_high;j++){
                dp[i].push([0, 0]);
            }
        }

        dp[1 << to_norm_low[start]][start][0] = 1;
        let ans = 0;
        for(let h = 0;h < 2;h++){
            for(let conf = 0;conf < (1 << cnt_low);conf++){
                for(const j in to_norm_low){
                    let nod = parseInt(j);
                    for(const k in graph[nod]){
                        let it = graph[nod][parseInt(k)];
                        if(it in to_norm_low){
                            if(((conf >> to_norm_low[it]) & 1) === 0){
                                dp[conf | (1 << to_norm_low[it])][it][h] += dp[conf][nod][h];
    //                            await debug(conf, nod, conf | (1 << to_norm_low[it]), it, dp[conf][nod]);
                            }else{
                                if(h < 1 && it !== start && it !== end){
                                    dp[conf][it][h + 1] += dp[conf][nod][h];
                                }
                            }
                        }else{
                            dp[conf][it][h] += dp[conf][nod][h];
    //                        await debug(conf, nod, conf, it, dp[conf][nod]);
                        }
                    }
                }
                for(let nod = 0;nod < cnt_low + cnt_high;nod++){
                    if(!(nod in to_norm_low)){
                        for(const k in graph[nod]){
                            let it = graph[nod][parseInt(k)];
                            if(it in to_norm_low){
                                if(((conf >> to_norm_low[it]) & 1) === 0){
                                    dp[conf | (1 << to_norm_low[it])][it][h] += dp[conf][nod][h];
    //                                await debug(conf, nod, conf | (1 << to_norm_low[it]), it, dp[conf][nod]);
                                }else{
                                    if(h < 1 && it !== start && it !== end){
                                        dp[conf][it][h + 1] += dp[conf][nod][h];
                                    }
                                }
                            }else{
                                assert.equal(true,false);
                            }
                        }
                    }
                    if(((conf >> to_norm_low[end]) & 1) && nod === end){
                        ans += dp[conf][nod][h];
                    }
                }
            }
        }
        console.log(ans);
    });

}

main();
