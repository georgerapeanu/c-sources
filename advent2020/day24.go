package main

import (
        "fmt"
        "os"
        "bufio"
       )

func get_value (s string)(int,bool){
    ans := 0;

    for _,c := range s{
        if c < '0' || c > '9'{
            return 0,false;
        }else{
            ans = ans * 10 + int(c - '0');
        }
    }

    return ans,true;
}

type Cell struct{
    x,y int;
}

func cleanup(state *map[Cell]bool){
    var to_delete []Cell;
    for cell,value := range (*state){
        if value == false{
            to_delete = append(to_delete,cell);
        }
    }
    for _,cell := range to_delete{
        delete(*state,cell);
    }
}

var dx [6]int = [6]int{1,1,0,-1,-1,0};
var dy [6]int = [6]int{0,1,1,0,-1,-1};

func do_cycle(state *map[Cell]bool){
    new_state := make(map[Cell]bool);

    for cell := range (*state){
        new_state[cell] = true;
        for k := 0;k < 6;k++{
            new_state[Cell{cell.x + dx[k],cell.y + dy[k]}] = true;
        }
    }

    for cell := range new_state{
        cnt := 0;
        for k := 0; k < 6;k++{
            neighbor_cell := Cell{cell.x + dx[k],cell.y + dy[k]};
            if _,ok := (*state)[neighbor_cell];ok == true{
                cnt++;
            }
        }
        if _,ok := (*state)[cell];ok{
            if cnt == 1 || cnt == 2{
                new_state[cell] = true;
            }else{
                new_state[cell] = false;
            }
        }else{
            if cnt == 2{
                new_state[cell] = true;
            }else{
                new_state[cell] = false;
            }
        }
    }

    *state = new_state;
}

func main(){

    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }

    scanner := bufio.NewScanner(file);
    state := make(map[Cell]bool);

    for scanner.Scan(){
        if len(scanner.Text()) == 0{
            break;
        }

        ind := 0;
        x := 0;
        y := 0;

        for ind < len(scanner.Text()){
            switch (scanner.Text())[ind]{
                case 'e':
                    x++;
                case 'w':
                    x--;
                case 'n':
                    y++;
                    ind++;
                    if (scanner.Text())[ind] == 'e'{
                        x++;
                    }
                case 's':
                    y--;
                    ind++;
                    if (scanner.Text())[ind] == 'w'{
                        x--;
                    }
            }
            ind++;
        }

        cell := Cell{x,y};

        if _,ok := state[cell];ok == false{
            state[cell] = false;
        }

        state[cell] = !state[cell];
    }

    cleanup(&state);

    for i := 0;i < 100;i++{
        do_cycle(&state);
        cleanup(&state);
    }

    fmt.Println(len(state));
}
