import {exit, stdin, stdout} from 'process';
import * as readline from 'node:readline/promises';
const rl = await readline.createInterface({input:stdin, output:null});

class Matrix{
    constructor(n,m){
        this.n = n;
        this.m = m;
        this.a = [];
        for(let i = 0;i < n;i++){
            let row = [];
            for(let j = 0;j < m;j++){
                row.push(0);
            }
            this.a.push(row);
        }
    }

    mult(other) {
        let ans = new Matrix(this.n, other.m);

        for(let i = 0;i < ans.n;i++) {
            for (let j = 0; j < ans.m; j++) {
                for (let k = 0; k < this.m; k++) {
                    ans.a[i][j] += this.a[i][k] * other.a[k][j];
                }
            }
        }
        return ans;
    }

    pow(exp){
        let ans = new Matrix(this.n, this.m);
        let base = new Matrix(this.n, this.m);

        for(let i = 0;i < this.n;i++){
            for(let j = 0;j < this.m;j++){
                base.a[i][j] = this.a[i][j];
            }
        }

        for(let i = 0;i < this.n;i++){
            ans.a[i][i] = 1;
        }
        while(exp > 0){
            if(exp % 2 === 1){
                ans = ans.mult(base);
            }
            base = base.mult(base);
            exp = Math.floor(exp / 2);
        }
        return ans;
    }
}

async function main(){
    let input_lines = [];
    rl.on('line', (line) => {
        if(line.trim() !== ""){
            input_lines.push(line.trim());
        }
    }).on('close', async () => {
        const days = 256;
        let transform = new Matrix(9,9);
        for(let i = 0;i < 8;i++){
            transform.a[i][i + 1] += 1;
        }
        transform.a[6][0] += 1;
        transform.a[8][0] += 1;

        let base = new Matrix(9, 1);

        const numbers = input_lines[0].split(",");

        for(const i in numbers){
            numbers[i] = parseInt(numbers[i]);
            base.a[numbers[i]][0] += 1;
        }

        let final_state = transform.pow(days).mult(base);

        let ans = 0;

        for(const i in final_state.a){
            ans += final_state.a[i][0];
        }

        console.log(ans);
    });


}

main();
