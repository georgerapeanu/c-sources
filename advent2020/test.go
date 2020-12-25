package main

import (
        "fmt"
        "os"
        "bufio"
        "strings"
       )

type ValuesRange struct{
    x1,y1 int;
    x2,y2 int;
}

type Ticket struct{
    values []int;
}

func (this *ValuesRange) is_valid(value int) (bool){
    return (this.x1 <= value && value <= this.y1) || (this.x2 <= value && value <= this.y2);
}

func (this *Ticket) Read(s string){
    tmp := strings.Split(s,",");

    for _,val := range tmp{
        value,_ := get_value(val);
        this.values = append(this.values,value);
    }
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

func lgpow(b,e,mod int) (int){
    p := 1;
    b %= mod;

    for ;e > 0;e >>= 1{
        if (e % 2) != 0{
            p = p * b % mod;
        }
        b = b * b % mod;
    }

    return p;
}

func only_spaces(s string)(bool){
    for _,val := range s{
        if byte(val) != byte(' '){
            return false;
        }
    }
    return true;
}

func main(){


    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }

    scanner := bufio.NewScanner(file);

    ranges := make(map[string]ValuesRange);

    for scanner.Scan(){
        if only_spaces(scanner.Text()){
            break;
        }
        var name string;
        var current_range ValuesRange;
        tmp := strings.Split(scanner.Text(),": ");
        name = tmp[0];
        fmt.Sscanf(tmp[1],"%d-%d or %d-%d",&current_range.x1,&current_range.y1,&current_range.x2,&current_range.y2);
        ranges[name] = current_range;
    }

    var my_ticket Ticket;
    var tickets []Ticket;

    scanner.Scan();
    scanner.Scan();
    my_ticket.Read(scanner.Text());

    scanner.Scan();
    scanner.Scan();

    for scanner.Scan(){
        if only_spaces(scanner.Text()){
            break;
        }
        var tmp Ticket;
        tmp.Read(scanner.Text());
        tickets = append(tickets,tmp);
    }

    coef := make(map[string]([]int));

    for name := range ranges{
        coef[name] = make([]int,len(my_ticket.values));
    }

    cnt_valid := 0;
    for _,ticket := range tickets{
        ok := true;
        for _,value := range ticket.values{
            if ok == false{
                break;
            }
            local_ok := false;
            for _,_range := range ranges{
                if _range.is_valid(value){
                    local_ok = true;
                    break;
                }
            }
            if(local_ok == false){
                ok = false;
                break;
            }
        }
        if ok == true{
            cnt_valid++;
            for name,_range := range ranges{
                for i,value := range ticket.values{
                    if _range.is_valid(value){
                        coef[name][i]++;
                    }
                }
            }
        }
    }

    for name,row := range coef{
        for pos,elem := range row{
            if elem == cnt_valid{
                coef[name][pos] = 1;
            }else{
                coef[name][pos] = 0;
            }
        }
    }

    perm := make(map[string]int);

    for true{
        found := false;
        for name,row := range coef{
            sum := 0;
            lst_one := -1;
            for pos,elem := range row{
                sum += elem;
                if elem == 1{
                    lst_one = pos;
                }
            }
            if sum == 1{
                found = true
                perm[name] = lst_one;
                for name2 := range coef{
                    coef[name2][lst_one] = 0;
                }
                break;
            }
        }
        if found == false{
            break;
        }
    }

    ans := 1;

    for name,value := range perm{
        if strings.HasPrefix(name,"departure"){
            ans *= my_ticket.values[value];
        }
    }

    fmt.Println(ans);
}
