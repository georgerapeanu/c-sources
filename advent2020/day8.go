package main

import (
        "fmt"
        "os"
        "strings"
        "bufio"
       )

func get_value (s string)(int,bool){
    ans := 0;
    sgn := 0;

    for _,c := range s{
        if c == '+' || c == '-'{
            if sgn != 0{
                return 0,false;
            }else if c == '+'{
                sgn = 1;
            }else{
                sgn = -1;
            }
        }else if c < '0' || c > '9'{
            return 0,false;
        }else{
            ans = ans * 10 + int(c - '0');
        }
    }

    ans *= sgn;

    return ans,true;
}

type Computer struct{
    commands []string;
    viz []bool;
    acc,idx int;
}

func (computer *Computer) init(commands []string) {
    for _,val := range commands{
        computer.commands = append(computer.commands,val);
    }
    computer.viz = make([]bool,len(computer.commands));
    computer.acc = 0;
    computer.idx = 0;
}

func (computer *Computer) run() (result int,finished bool){
    computer.acc = 0;
    computer.idx = 0;
    computer.viz = make([]bool,len(computer.commands));

    for computer.idx >= 0 && computer.idx < len(computer.commands) && computer.viz[computer.idx] == false{
        computer.viz[computer.idx] = true;

        if strings.HasPrefix(computer.commands[computer.idx],"nop"){
            computer.idx++;
        }else{
            val,ok := get_value(strings.Fields(computer.commands[computer.idx])[1]);
            if ok == false{
                fmt.Println("error malformed number\n");
                os.Exit(0);
            }else if strings.HasPrefix(computer.commands[computer.idx],"acc"){
                computer.acc += val;
                computer.idx++;
            }else{
                computer.idx += val;
            }
        }
    }

    if computer.idx == len(computer.commands){
        return computer.acc,true;
    }
    return computer.acc,false;
}


func main(){


    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }

    scanner := bufio.NewScanner(file);
    var commands []string;

    for scanner.Scan(){
        tmp := scanner.Text()
        if len(tmp) == 0{
            break;
        }
        commands = append(commands,tmp);
    }

    for i,_ := range commands{
        if strings.HasPrefix(commands[i],"nop"){
            commands[i] = strings.Replace(commands[i],"nop","jmp",1);
        }else if strings.HasPrefix(commands[i],"jmp"){
            commands[i] = strings.Replace(commands[i],"jmp","nop",1);
        }
        var computer Computer;
        computer.init(commands);
        if val,ok := computer.run();ok{
            fmt.Println(val);
        }
        if strings.HasPrefix(commands[i],"nop"){
            commands[i] = strings.Replace(commands[i],"nop","jmp",1);
        }else if strings.HasPrefix(commands[i],"jmp"){
            commands[i] = strings.Replace(commands[i],"jmp","nop",1);
        }
    }

}
