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

    group_questions := make(map[byte]int);
    people_count := 0;

    ans := 0;

    for scanner.Scan(){
        tmp := scanner.Text()
        if len(tmp) == 0{
            for _,value := range group_questions{
                if value == people_count{
                    ans++;
                }
            }
            group_questions = make(map[byte]int);
            people_count = 0;
        }else{
            people_count++;
            for _,question := range tmp{
                group_questions[byte(question)]++;
            }
        }
    }

    fmt.Println(ans);
}

