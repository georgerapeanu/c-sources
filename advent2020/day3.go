package main

import (
        "fmt"
       );

func main(){
    var ans int64 = 1;

    var v []string;

    for{
        var s string;
        _,err := fmt.Scanf("%s",&s);
        if err != nil{
            break;
        }
        v = append(v,s);
    }
    dx := []int{1,1,1,1,2};
    dy := []int{1,3,5,7,1};

    for i := 0;i < len(dx);i++{
        cnt := 0;
        x := 0;
        y := 0;
        for x < len(v){
            if v[x][y] == '#'{
                cnt++;
            }
            y += dy[i];y %= len(v[x]);
            x += dx[i];
        }
        ans *= int64(cnt);
    }

    fmt.Println(ans);
}
