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
        }
        ans = ans * 10 + int(c - '0');
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

    var ids []int;

    for scanner.Scan(){
        tmp := scanner.Text()
        if len(tmp) == 0{
            break;
        }
        row,col := 0,0;
        for i := 0;i < 7;i++{
            if tmp[i] == 'B'{
                row |= (1 << (6 - i));
            }
        }

        for i := 7;i < 10;i++{
            if tmp[i] == 'R'{
                col |= (1 << (9 - i));
            }
        }

        ids = append(ids,row * 8 + col);
    }

    sort.Sort(sort.IntSlice(ids));

    for i := 0;i < len(ids) - 1;i++{
        if ids[i] + 1 == ids[i + 1] - 1{
            fmt.Println(ids[i] + 1);
        }
    }
}

