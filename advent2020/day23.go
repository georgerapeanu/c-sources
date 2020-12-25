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

func main(){

    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }

    scanner := bufio.NewScanner(file);

    next := make([]int,1000000 + 1);

    var deck []int;

    scanner.Scan();
    for _,x := range scanner.Text(){
        deck = append(deck,int(byte(x) - byte('0')));
    }

    for i := len(deck) + 1;i <= 1000000;i++{
        deck = append(deck,i);
    }

    for i := 0;i < len(deck);i++{
        next[deck[i]] = deck[(i + 1) % len(deck)];
    }

    head := deck[0];

    for i := 0;i < 10000000;i++{
        transfer := make([]int,0);
        node := next[head];

        for k := 0;k < 3;k++{
            transfer = append(transfer,node);
            node = next[node];
        }

        next_id := head;

        for true{
            found := false;

            if head == next_id{
                found = true;
            }

            for i := range transfer{
                if transfer[i] == next_id{
                    found = true;
                }
            }

            if found == false{
                break;
            }
            next_id--;
            if next_id == 0{
                next_id = len(deck);
            }
        }

        next[head] = next[transfer[len(transfer) - 1]];
        next[transfer[len(transfer) - 1]] = next[next_id];
        next[next_id] = transfer[0];

        head = next[head];
    }

    fmt.Println(next[1] * next[next[1]]);
}
