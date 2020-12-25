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

    scanner.Scan();
    scanner.Scan();
    tmp := strings.Split(scanner.Text(),",")

    ans := 0;
    p := 1;

    var values []int;
    var r []int;
    for i,val := range tmp{
        if strings.HasPrefix(val,"x") == false{
            id,_ := get_value(val);
            values = append(values,id);
            r = append(r,((id - (i % id) % id)) % id);
            p *= id;
        }
    }

    for i := range values{
        coef := lgpow(p / values[i],values[i] - 2,values[i]);
        ans += (p / values[i]) * coef * r[i];
        fmt.Println(values[i],r[i],coef);
        ans %= p;
    }
    fmt.Println(ans,p);
}
