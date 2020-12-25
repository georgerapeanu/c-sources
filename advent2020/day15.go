package main

import (
        "fmt"
        "os"
        "bufio"
        "strings"
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

func lgpow(b,e,mod int) (int){
    p := 1;
    b %= mod;

    for ;e > 0;e >>= 1{
        if (e % 2) != 0{
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

    mem := make(map[int]int);

    scanner.Scan();
    vals := strings.Split(scanner.Text(),",");

    lst := -1;
    cnt := 0;
    for i := range vals{
        mem[lst] = cnt;
        value,_ := get_value(vals[i]);
        cnt++;
        lst = value;
    }

    for cnt < 30000000{
        if turn,ok := mem[lst];ok{
            mem[lst] = cnt;
            lst = cnt - turn;
        }else{
            mem[lst] = cnt;
            lst = 0;
        }
        cnt++;
    }

    fmt.Println(lst);
}
