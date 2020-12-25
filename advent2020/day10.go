package main

import (
        "fmt"
        "os"
        "bufio"
        "sort"
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

    var v []int;

    v = append(v,0);

    for scanner.Scan(){
        tmp := scanner.Text()
        if len(tmp) == 0{
            break;
        }

        value,_ := get_value(tmp);
        v = append(v,value);
    }
    sort.Sort(sort.IntSlice(v));
    v = append(v,v[len(v) - 1] + 3);

    dp := make([]int,len(v));

    dp[0] = 1;
    j := 0;
    for i := 1;i < len(v);i++{
        for v[j] < v[i] - 3{
            j++;
        }
        for k := j;k < i;k++{
            dp[i] += dp[k];
        }
    }

    fmt.Println(dp[len(v) - 1]);
}
