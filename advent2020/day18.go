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
        }else{
            ans = ans * 10 + int(c - '0');
        }
    }

    return ans,true;
}

func term(s *string,ind *int)(int){
    ans := 0;
    if (*s)[*ind] == '('{
        *ind++;
        ans = expr(s,ind);
        *ind++;
    }else{
        for *ind < len(*s) && '0' <= (*s)[*ind] && (*s)[*ind] <= '9'{
            ans = ans * 10 + int((*s)[*ind] - '0');
            *ind++;
        }
    }
    return ans;
}

func factor(s *string,ind *int)(int){
    ans := term(s,ind);

    for *ind < len(*s) && (*s)[*ind] == '+'{
        *ind++;
        ans += term(s,ind);
    }

    return ans;
}

func expr(s *string,ind *int)(int){
    ans := factor(s,ind);
    for *ind < len(*s) && (*s)[*ind] == '*'{
        *ind++;
        ans *= factor(s,ind);
    }

    return ans;
}

func main(){

    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }

    scanner := bufio.NewScanner(file);
    ans := 0;

    for scanner.Scan(){
        tmp := scanner.Text()
        if len(tmp) == 0{
            break;
        }

        var equation string;
        for _,val := range tmp{
            if byte(val) != byte(' '){
                equation += string(val);
            }
        }
        ind := 0;
        ans += expr(&equation,&ind);
    }

    fmt.Println(ans);
}
