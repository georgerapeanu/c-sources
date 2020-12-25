package main

import (
        "fmt"
        "os"
        "bufio"
        "strings"
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

type Edge struct{
    ingredient, alergent string;
}

func pairup(ingredient string,graph *map[string]([]string),viz *map[string]bool,l *map[string]string,r *map[string]string) bool{
    if (*viz)[ingredient] == true{
        return false;
    }
    (*viz)[ingredient] = true;

    for _,alergent := range (*graph)[ingredient]{
        if (*r)[alergent] == ""{
            (*r)[alergent] = ingredient;
            (*l)[ingredient] = alergent;
            return true;
        }
    }

    for _,alergent := range (*graph)[ingredient]{
        if pairup((*r)[alergent],graph,viz,l,r) == true{
            (*r)[alergent] = ingredient;
            (*l)[ingredient] = alergent;
            return true;
        }
    }

    return false;
}

func main(){

    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }

    scanner := bufio.NewScanner(file);

    fr := make(map[string]int);
    cnt_edge := make(map[Edge]int);
    graph := make(map[string]([]string));

    var ingredient_list [][]string;
    var alergent_list [][]string;

    for scanner.Scan(){
        if len(scanner.Text()) == 0{
            break;
        }

        ingredients := strings.Split(strings.Split(scanner.Text()," (")[0]," ");
        alergents := strings.Split(strings.TrimPrefix(strings.TrimSuffix(strings.Split(scanner.Text()," (")[1],")"),"contains "),", ");

        ingredient_list = append(ingredient_list,ingredients);
        alergent_list = append(alergent_list,alergents);

        for _,ingredient := range ingredients{
            if _,ok := graph[ingredient];ok == false{
                graph[ingredient] = make([]string,0);
            }
        }

        for _,ingredient := range ingredients{
            for _,alergent := range alergents{
                cnt_edge[Edge{ingredient,alergent}]++;
            }
        }

        for _,alergent := range alergents{
            fr[alergent]++;
        }
    }


    for pair := range cnt_edge{
        if cnt_edge[pair] == fr[pair.alergent]{
            graph[pair.ingredient] = append(graph[pair.ingredient],pair.alergent);
        }
    }

    l := make(map[string]string);
    r := make(map[string]string);
    viz := make(map[string]bool);

    var alergents []string;

    for ingredient := range graph{
        l[ingredient] = "";
        viz[ingredient] = false;
        for _,alergent := range graph[ingredient]{
            r[alergent] = "";
            alergents = append(alergents,alergent);
        }
    }

    sort.Strings(alergents);

    var tmp []string;

    tmp = make([]string,0);

    for _,alergent := range alergents{
        if len(tmp) == 0 || tmp[len(tmp) - 1] != alergent{
            tmp = append(tmp,alergent);
        }
    }

    alergents = tmp;

    ok := true;

    for ok{
        ok = false;
        for ingredient := range viz{
            viz[ingredient] = false;
        }

        for ingredient := range graph{
            if l[ingredient] == "" && pairup(ingredient,&graph,&viz,&l,&r) == true{
                ok = true;
            }
        }
    }

    ans := "";

    for _,alergent := range alergents{
        ans += r[alergent] + ",";
    }
    ans = strings.TrimSuffix(ans,",");

    fmt.Println(ans);
}
