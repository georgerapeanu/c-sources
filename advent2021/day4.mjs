import {exit, stdin, stdout} from 'process';
import * as readline from 'node:readline/promises';
const rl = await readline.createInterface({input:stdin, output:null});

class BingoBoard{
    constructor() {
        this.last_drawn_number = 0;
        this.board = [];
        this.active = [];
        for(let i = 0;i < 5;i++){
            let row = [];
            let active_row = [];
            for(let j = 0;j < 5;j++){
                row.push(0);
                active_row.push(false);
            }
            this.board.push(row);
            this.active.push(active_row);
        }
    }

    update_position(i, j, value){
        this.board[i][j] = value;
    }

    activate_value(value){
        this.last_drawn_number = value;
        for(let i = 0;i < 5;i++){
            for(let j = 0;j < 5;j++){
                if(this.board[i][j] === value){
                    this.active[i][j] = true;
                }
            }
        }
    }

    get win(){
        for(let i = 0;i < 5;i++){
            let all_row = true;
            let all_col = true;
            for(let j = 0;j < 5;j++){
                if(this.active[i][j] === false){
                    all_row = false;
                }
                if(this.active[j][i] === false){
                    all_col = false;
                }
            }
            if(all_row || all_col){
                return true;
            }
        }
        return false;
    }

    get score(){
        let score = 0;
        for(let i = 0;i < 5;i++){
            for(let j = 0;j < 5;j++){
                if(this.active[i][j] === false){
                    score += this.board[i][j];
                }
            }
        }
        return score * this.last_drawn_number;
    }
}

async function main(){
    let lines = [];
    rl.on('line', (line) => {
        if(line.trim() !== ""){
            lines.push(line.trim());
        }
    }).on('close', async () => {
        let drawn_numbers = lines[0].split(",");
        for(const i in drawn_numbers){
            drawn_numbers[i] = parseInt(drawn_numbers[i].trim());
        }

        let board_numbers = [];

        for(const i in lines){
            if(i === "0"){///why is it a string
                continue;
            }
            const line_numbers = lines[i].split(" ");
            for(const i in line_numbers){
                if(line_numbers[i].trim() !== ""){
                    board_numbers.push(parseInt(line_numbers[i].trim()));
                }
            }
        }

        let boards = [];

        for(const i in board_numbers){
            if(parseInt(i) % 25 === 0){
                boards.push(new BingoBoard());
            }
            let l = Math.floor((parseInt(i) % 25) / 5)
            let r = (parseInt(i) % 25) % 5;
            boards[boards.length - 1].update_position(l, r, board_numbers[i]);
        }

        for(const i in drawn_numbers){
            let have_not_win = false;
            for(const board in boards){
                boards[board].activate_value(drawn_numbers[i]);
                if(boards[board].win === false){
                    have_not_win = true;
                }
            }
            if(have_not_win === true){
                boards = boards.filter(board => board.win === false);
            }else{
                console.log(boards[0].score);
                exit(0);
            }
        }
    });


}

main();
