package main

import (
        "fmt"
        "os"
        "bufio"
        "strings"
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

func main(){


    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }

    scanner := bufio.NewScanner(file);

    mask_floating_bits := 0;
    mask_bits := 0;

    mem := make(map[int]int);

    for scanner.Scan(){
        if len(scanner.Text()) == 0{
            break;
        }
        tmp := strings.Split(scanner.Text(), "=");
        if strings.HasPrefix(tmp[0],"mask"){
            tmp[1] = strings.TrimPrefix(tmp[1]," ");
            tmp[1] = strings.TrimSuffix(tmp[1]," ");
            mask_floating_bits = 0;
            mask_bits = 0;
            for i := 0;i < 36;i++{
                if tmp[1][36 - i - 1] == '1'{
                    mask_bits |= (1 << i);
                }else if tmp[1][36 - i - 1] == 'X'{
                    mask_floating_bits |= (1 << i);
                }
            }
        }else{
            tmp[0] = strings.TrimPrefix(tmp[0],"mem[");
            tmp[0] = strings.TrimSuffix(tmp[0],"] ");
            tmp[1] = strings.TrimPrefix(tmp[1]," ");
            tmp[1] = strings.TrimSuffix(tmp[1]," ");
            where,_ := get_value(tmp[0]);
            value,_ := get_value(tmp[1]);
            where |= mask_bits;
            conf := mask_floating_bits;
            where = where & (((1 << 36) - 1) & (^mask_floating_bits));
            for true{
                mem[where | conf] = value;
                if conf == 0{
                    break;
                }
                conf = (conf - 1) & mask_floating_bits;
            }

        }
    }

    ans := 0;

    for _,value := range mem{
        ans += value;
    }

    fmt.Println(ans);
}
