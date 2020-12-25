package main

import (
        "fmt"
        "os"
        "strings"
        "bufio"
       )

type edge_t struct{
    bag string
    cnt int
}

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

func dfs(nod string,graph *map[string]([]edge_t),viz *map[string]int){
    (*viz)[nod] = 1;

    for _,it := range (*graph)[nod]{
        if _,ok := (*viz)[it.bag];ok == false{
            dfs(it.bag,graph,viz);
        }
        (*viz)[nod] += (*viz)[it.bag] * it.cnt;
    }
}

func main(){


    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }

    scanner := bufio.NewScanner(file);

    graph := make(map[string]([]edge_t));
    t_graph := make(map[string]([]edge_t));

    for scanner.Scan(){
        tmp := scanner.Text()
        if len(tmp) == 0{
            break;
        }
        s := strings.Split(tmp,"bag");
        data := strings.Fields(s[0]);
        bag_name := data[len(data) - 2] + data[len(data) - 1];
        for i := len(s) - 2;i > 0;i--{
            data := strings.Fields(s[i]);
            if data[len(data) - 1] == "other"{
                continue;
            }
            cnt,_ := get_value(data[len(data) - 3]);
            name := data[len(data) - 2] + data[len(data) - 1];
            graph[bag_name] = append(graph[bag_name],edge_t{name,cnt});
            t_graph[name] = append(t_graph[name],edge_t{bag_name,cnt});
        }
    }

    viz := make(map[string]int);

    dfs("shinygold",&graph,&viz);

    fmt.Println(viz["shinygold"] - 1);
}
