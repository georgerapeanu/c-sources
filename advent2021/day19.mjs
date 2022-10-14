import {stdin} from 'process';
import * as readline from 'node:readline/promises';
import * as assert from "assert";
const rl = await readline.createInterface({input:stdin, output:null});

class Scanner{
    constructor(){
        this.x = 0;
        this.y = 0;
        this.z = 0;
        this.points = [];
        this.version = 0;
    }

    ///Horrible
    get_next_version(){
        for(const i in this.points){
            let tmp = this.points[i][0];
            this.points[i][0] = this.points[i][1];
            this.points[i][1] = -tmp;
            if(this.version % 4 === 3){
                let tmp = this.points[i][0];
                this.points[i][0] = this.points[i][1];
                this.points[i][1] = this.points[i][2];
                this.points[i][2] = tmp;
                if(this.version % 12 === 11){
                    this.points[i][0] *= -1;
                    this.points[i][1] *= -1;
                    this.points[i][2] *= -1;
                    let tmp = this.points[i][0];
                    this.points[i][0] = this.points[i][1];
                    this.points[i][1] = tmp;
                }
            }
        }
        this.version++;
        this.version %= 24;
    }

    change_coords(x, y, z){
        for(const i in this.points){
            this.points[i][0] += x - this.x;
            this.points[i][1] += y - this.y;
            this.points[i][2] += z - this.z;
        }
        this.x = x;
        this.y = y;
        this.z = z;
    }

    get_version(version){
        while(this.version !== version){
            this.get_next_version();
        }
    }
}

class DSU{
    constructor(n){
        this.father = Array(n).fill(-1);
    }

    find_root(x){
        if(this.father[x] === -1){
            return x;
        }
        return this.father[x] = this.find_root(this.father[x]);
    }

    unite(x, y){
        x = this.find_root(x);
        y = this.find_root(y);
        if(x === y){
            return false;
        }

        this.father[x] = y;

        return true;
    }
}

function match(fst, snd){
    for(let i = 0;i < fst.points.length;i++){
        for(let j = 0;j < snd.points.length;j++){
            let snd_coords = [fst.points[i][0] - snd.points[j][0],
                              fst.points[i][1] - snd.points[j][1],
                              fst.points[i][2] - snd.points[j][2],
            ];
            let all_points = [];
            for(const i in fst.points){
                all_points.push([fst.points[i][0], fst.points[i][1], fst.points[i][2]].toString());
            }
            for(const i in snd.points){
                all_points.push([snd.points[i][0] + snd_coords[0],
                                 snd.points[i][1] + snd_coords[1],
                                 snd.points[i][2] + snd_coords[2]
                ].toString());
            }

            all_points = all_points.filter((value, index, self) => {
                return self.indexOf(value) === index;
            });

            for(const i in all_points){
                all_points[i] = JSON.parse("[" + all_points[i] +"]");
            }

            let cnt_1 = 0;
            let cnt_2 = 0;
            let cnt_both = 0;

            for(const i in all_points){
                let inside_1 = false, inside_2 = false;
                if(all_points[i][0] >= -1000 && all_points[i][0] <= 1000 &&
                   all_points[i][1] >= -1000 && all_points[i][1] <= 1000 &&
                   all_points[i][2] >= -1000 && all_points[i][2] <= 1000){
                    inside_1 = true;
                }
                if(all_points[i][0] >= snd_coords[0] - 1000 && all_points[i][0] <= snd_coords[0] + 1000 &&
                   all_points[i][1] >= snd_coords[1] - 1000 && all_points[i][1] <= snd_coords[1] + 1000 &&
                   all_points[i][2] >= snd_coords[2] - 1000 && all_points[i][2] <= snd_coords[2] + 1000){
                    inside_2 = true;
                }
                if(inside_1){
                    cnt_1++;
                }
                if(inside_2){
                    cnt_2++;
                }
                if(inside_1 && inside_2){
                    cnt_both++;
                }
            }
             if(cnt_1 === fst.points.length && cnt_2 === snd.points.length && cnt_both >= 12){
                return snd_coords;
            }
        }
    }
    return null;
}

let rot = {};
function compose_rotations(x, y){
    if(!([x, y] in rot)){
        let tmp_scanner = new Scanner();
        tmp_scanner.points.push([1,2,3]);
        tmp_scanner.get_version(x);
        tmp_scanner.version = 0;
        tmp_scanner.get_version(y);
        let tmp_scanner2 = new Scanner();
        tmp_scanner2.points.push([1,2,3]);
        while(tmp_scanner.points[0].toString() !== tmp_scanner2.points[0].toString()){
            tmp_scanner2.get_next_version();
        }
        rot[[x,y]] = tmp_scanner2.version;
    }
    return rot[[x,y]];
}

async function main(){
      let input_lines = [];
    rl.on('line', (line) => {
        if(line.trim().length !== 0){
            input_lines.push(line.trim());
        }
    }).on('close', async () => {
        let scanners = [];

        for(const i in input_lines){
            if(input_lines[i].includes("scanner")){
                scanners.push(new Scanner());
            }else{
                let coords = input_lines[i].split(",");
                for(const i in coords){
                    coords[i] = parseInt(coords[i]);
                }
                scanners[scanners.length - 1].points.push(coords);
            }
        }

        let graph = [];
        let viz = [];
        for(let i = 0;i < scanners.length;i++){
            graph.push([]);
            viz.push(false);
        }

        let dsu = new DSU(scanners.length);

        for(let i = 0;i < scanners.length;i++){
            for(let j = i + 1;j < scanners.length;j++){
                console.log("doing ",i, j);
                if(dsu.find_root(i) === dsu.find_root(j)){
                    continue;
                }
                for(let k = 0;k < 24;k++){
                    let tmp = match(scanners[i], scanners[j]);
                    if(tmp !== null){
                        graph[i].push([j, k, tmp]);
                        let k2 = 0;
                        for(k2 = 0;k2 < 24;k2++){
                            if(compose_rotations(k, k2) === 0){
                                break;
                            }
                        }
                  //      console.log(i, j, k, tmp);
                        let tmp_scanner = new Scanner();
                        tmp_scanner.points.push([tmp[0], tmp[1], tmp[2]]);
                        tmp_scanner.get_version(k2);
                        for(let j = 0;j < 3;j++){
                            tmp_scanner.points[0][j] *= -1;
                        }
                        graph[j].push([i, k2, tmp_scanner.points[0]]);
                  //      console.log(j, i, k2, tmp_scanner.points[0])
                        dsu.unite(i, j);
                    }
                    scanners[j].get_next_version();
                }
            }
        }

        let nodes = [0];
        viz[0] = true;
        for(let i = 0;i < nodes.length;i++){
            for(const j in graph[nodes[i]]){
                let edge = graph[nodes[i]][j];
                if(viz[edge[0]] === false){
                    viz[edge[0]] = true;
                    nodes.push(edge[0]);
                    let tmp_scanner = new Scanner();
                    tmp_scanner.points.push(edge[2]);
                    tmp_scanner.get_version(scanners[nodes[i]].version);
                    let x = tmp_scanner.points[0][0] + scanners[nodes[i]].x;
                    let y = tmp_scanner.points[0][1] + scanners[nodes[i]].y;
                    let z = tmp_scanner.points[0][2] + scanners[nodes[i]].z;

                    scanners[edge[0]].get_version(compose_rotations(edge[1], scanners[nodes[i]].version));
                    scanners[edge[0]].change_coords(x, y, z);
                }
            }
        }

        /*
        for(const i in scanners){
            console.log(scanners[i].x, scanners[i].y, scanners[i].z);
        }
        */
        /*
        let all_beacons = [];
        for(const i in scanners){
            for(const j in scanners[i].points){
                all_beacons.push(scanners[i].points[j].toString());
            }
        }

        all_beacons = all_beacons.filter((value, index, self) => {
            return self.indexOf(value) === index;
        });
        */

        let ans = undefined;

        for(let i = 0;i < scanners.length;i++){
            for(let j = i + 1;j < scanners.length;j++){
                let dist = 0;
                dist += Math.abs(scanners[i].x - scanners[j].x);
                dist += Math.abs(scanners[i].y - scanners[j].y);
                dist += Math.abs(scanners[i].z - scanners[j].z);
                if(ans === undefined || dist > ans){
                    ans = dist;
                }
            }
        }

        console.log(ans);
    });

}

main();
