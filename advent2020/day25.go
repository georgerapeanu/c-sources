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

var BASE int = 7;
var INV_BASE = 14429448;
var MOD int = 20201227;

func lgpow(b,e,mod int)int{
    p := 1;

    for ;e > 0;e >>= 1{
        if((e & 1) == 1){
            p = p * b % mod;
        }
        b = b * b % mod;
    }

    return p;
}

func main(){

    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }

    scanner := bufio.NewScanner(file);

    scanner.Scan();
    card_public,_ := get_value(scanner.Text());
    scanner.Scan();
    door_public,_ := get_value(scanner.Text());

    card_loop := 0;
    door_loop := 0;

    for card_public != 1{
        card_public = card_public * INV_BASE % MOD;
        card_loop++;
    }

    for door_public != 1{
        door_public = door_public * INV_BASE % MOD;
        door_loop++;
    }

    fmt.Println(lgpow(BASE,card_loop * door_loop % (MOD - 1),MOD));
}
