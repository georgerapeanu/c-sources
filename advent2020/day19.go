package main

import (
        "fmt"
        "os"
        "bufio"
        "strings"
       )

type Rule struct{
    t bool;
    composition []int;
}

type Node struct{
    rules []Rule;
}

type State struct{
    rule,pos int;
}

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

func make_2d_slice(n,m int) ([][]int){
    var ans [][]int;

    for i := 0;i < n;i++{
        ans = append(ans,make([]int,m));
    }

    return ans;
}

func make_3d_slice(n,m,p int) ([][][]int){
    var ans [][][]int;

    for i := 0;i < n;i++{
        ans = append(ans,make_2d_slice(m,p));
    }

    return ans;
}

func make_4d_slice(n,m,p,q int) ([][][][]int){
    var ans [][][][]int;

    for i := 0;i < n;i++{
        ans = append(ans,make_3d_slice(m,p,q));
    }

    return ans;
}

///we suppose that only one subrule will fit a substring
func forward_match(s *string,pos int,id int,dict *map[int]Node,memo *map[State]int)int{
    if value,ok := (*memo)[State{id,pos}];ok{
        return value;
    }else{
        (*memo)[State{id,pos}] = -2;
    }

    for _,rule := range (*dict)[id].rules{
        if rule.t == false{
            ind := pos;
            ok := true;
            for _,x := range rule.composition{
                if ind >= len(*s){
                    ok = false;
                    break;
                }
                if int((*s)[ind]) != x{
                    ok = false;
                    break;
                }
                ind++;
            }
            if ok == true{
                (*memo)[State{id,pos}] = ind;
                return (*memo)[State{id,pos}];
            }
        }else{
            ind := pos;
            for _,x := range rule.composition{
                ind = forward_match(s,ind,x,dict,memo);
                if ind == -2{
                    break;
                }
            }
            if ind != -2{
                (*memo)[State{id,pos}] = ind;
                return (*memo)[State{id,pos}];
            }
        }
    }
    (*memo)[State{id,pos}] = -2;
    return (*memo)[State{id,pos}];
}

func backward_match(s *string,pos int,id int,dict *map[int]Node,memo *map[State]int)int{
    if value,ok := (*memo)[State{id,pos}];ok{
        return value;
    }else{
        (*memo)[State{id,pos}] = -2;
    }

    for _,rule := range (*dict)[id].rules{
        if rule.t == false{
            ind := pos;
            ok := true;
            for i := len(rule.composition) - 1;i >= 0;i--{
                x := rule.composition[i];
                if ind < 0{
                    ok = false;
                    break;
                }
                if int((*s)[ind]) != x{
                    ok = false;
                    break;
                }
                ind--;
            }
            if ok == true{
                (*memo)[State{id,pos}] = ind;
                return (*memo)[State{id,pos}];
            }
        }else{
            ind := pos;
            for i := len(rule.composition) - 1;i >= 0;i--{
                x := rule.composition[i];
                ind = backward_match(s,ind,x,dict,memo);
                if ind == -2{
                    break;
                }
            }
            if ind != -2{
                (*memo)[State{id,pos}] = ind;
                return (*memo)[State{id,pos}];
            }
        }
    }
    (*memo)[State{id,pos}] = -2;
    return (*memo)[State{id,pos}];
}

func match8(s *string,dict *map[int]Node)bool{
    memo := make(map[State]int);
    ind := len(*s) - 1;

    ok := false;

    for true{
        ind = backward_match(s,ind,42,dict,&memo);
        if ind == -2{
            ok = false;
            break;
        }else if ind < 0{
            ok = true;
            break;
        }
    }
    return ok;
}

func match11(s *string,dict *map[int]Node)bool{
    memo1 := make(map[State]int);
    memo2 := make(map[State]int);
    l := 0;
    r := len(*s) - 1;

    ok := false;

    for true{
        l = forward_match(s,l,42,dict,&memo1);
        r = backward_match(s,r,31,dict,&memo2);


        if l == -2 || r == -2{
            ok = false;
            break;
        }else if l > r + 1{
            ok = false;
            break;
        }else if l == r + 1{
            ok = true;
            break;
        }
    }
    return ok;
}

func main(){

    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }

    scanner := bufio.NewScanner(file);

    dict := make(map[int]Node);

    for scanner.Scan(){
        tmp := scanner.Text()
        if len(tmp) == 0{
            break;
        }

        rule := strings.Split(tmp,": ");
        id,_ := get_value(rule[0]);

        posibilities := strings.Split(rule[1],"| ");

        for _,composition := range posibilities{
            if byte(composition[0]) == byte('"'){
                tmp := []int{int(composition[1])};

                if node,ok := dict[id];ok{
                    node.rules = append(node.rules,Rule{false,tmp});
                    dict[id] = node;
                }else{
                    dict[id] = Node{[]Rule{Rule{false,tmp}}};
                }
            }else{
                subrules := strings.Split(composition," ");
                var rule Rule;
                rule.t = true;
                for i := 0;i < len(subrules);i++{
                    if len(subrules[i]) == 0{
                        continue;
                    }
                    if value,ok := get_value(subrules[i]);ok{
                        rule.composition = append(rule.composition,value);
                    }
                }
                if node,ok := dict[id];ok{
                    node.rules = append(node.rules,rule);
                    dict[id] = node;
                }else{
                    dict[id] = Node{[]Rule{rule}};
                }
            }
        }
    }

    ans := 0;

    for scanner.Scan(){
        tmp := scanner.Text();

        if len(tmp) == 0{
            continue;
        }

        ok := false;

        for i := 0;i < len(tmp) - 1;i++{
            pref := "";
            suff := "";

            for j := 0;j < len(tmp);j++{
                if j <= i{
                    pref = pref + string(tmp[j]);
                }else{
                    suff = suff + string(tmp[j]);
                }
            }

            if match8(&pref,&dict) && match11(&suff,&dict){
                ok = true;
                break;
            }
        }

        if ok == true{
            ans++;
        }
    }


    fmt.Println(ans);
}
