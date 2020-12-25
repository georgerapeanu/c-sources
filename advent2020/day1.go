package main

import (
        "fmt"
        "io"
        "sort"
       );

func main(){
    var v []int;
    for{
        var val int;
        _,err := fmt.Scan(&val);
        if err == io.EOF{
            break;
        }
        v = append(v,val);
    }
    sort.Sort(sort.IntSlice(v));

    for i := 0;i < len(v);i++{
        for j := i + 1;j < len(v);j++{
            for k := j + 1;k < len(v);k++{
                if v[i] + v[j] + v[k] == 2020{
                    fmt.Printf("%v\n",int64(v[i]) * int64(v[j]) * int64(v[k]));
                }
            }
        }
    }
}
