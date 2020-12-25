package main

import (
        "fmt"
       );

func main(){
    cnt := 0;
    for{
        var low,high int;
        var c byte;
        var tmp,s string;
        _,err := fmt.Scanf("%d-%d %s %s",&low,&high,&tmp,&s);
        if err != nil{
            break;
        }
        c = tmp[0];

        if (s[low - 1] == c) != (s[high - 1] == c){
            cnt++;
        }
    }
    fmt.Println(cnt);
}
