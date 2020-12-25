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

func list2string(list []int)string{
    ans := "";
    for _,x := range list{
        ans += string(x) + string(',');
    }
    return ans;
}

func do_game(deck1,deck2 []int)(int,[]int){
    viz := make(map[string]bool);
    for len(deck1) != 0 && len(deck2) != 0{
        if _,ok := viz[list2string(deck1) + "|" + list2string(deck2)];ok{
            return 0,deck1;
        }
        viz[list2string(deck1) + "|" + list2string(deck2)] = true;
        a := deck1[0];deck1 = deck1[1:];
        b := deck2[0];deck2 = deck2[1:];
        if len(deck1) >= a && len(deck2) >= b{
            var new_deck1,new_deck2 []int;
            for i := 0;i < a;i++{
                new_deck1 = append(new_deck1,deck1[i]);
            }
            for i := 0;i < b;i++{
                new_deck2 = append(new_deck2,deck2[i]);
            }
            winner,_ := do_game(new_deck1,new_deck2);
            if winner == 0{
                deck1 = append(deck1,a);
                deck1 = append(deck1,b);
            }else{
                deck2 = append(deck2,b);
                deck2 = append(deck2,a);
            }
        }else{
            if a > b{
                deck1 = append(deck1,a);
                deck1 = append(deck1,b);
            }else{
                deck2 = append(deck2,b);
                deck2 = append(deck2,a);
            }
        }
    }

    if len(deck1) == 0{
        return 1,deck2;
    }
    return 0,deck1;
}

func main(){

    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }

    scanner := bufio.NewScanner(file);

    var deck1,deck2 []int;

    for scanner.Scan();scanner.Scan();{
        if len(scanner.Text()) == 0{
            break;
        }
        value,_ := get_value(scanner.Text());
        deck1 = append(deck1,value);
    }

    for scanner.Scan();scanner.Scan();{
        if len(scanner.Text()) == 0{
            break;
        }
        value,_ := get_value(scanner.Text());
        deck2 = append(deck2,value);
    }

    _,winner_deck := do_game(deck1,deck2);

    ans := 0;

    for i := 0;i < len(winner_deck);i++{
        ans += (len(winner_deck) - i) * winner_deck[i];
    }


    fmt.Println(ans);
}
