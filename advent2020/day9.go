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

func main(){


    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }

    scanner := bufio.NewScanner(file);

    values := make(map[int]int);
    var q []int;
    var v []int;
    cnt := 0;
    invalid_value := -1;

    for scanner.Scan(){
        tmp := scanner.Text()
        if len(tmp) == 0{
            break;
        }

        value,_ := get_value(tmp);
        v = append(v,value);

        if invalid_value != -1{
            continue;
        }

        if cnt < 25{
            values[value]++;
            q = append(q,value);
            cnt++;
        }else{
            is_ok := false;
            for a,_ := range values{
                if _,ok := values[value - a];ok && value - a != a{
                    is_ok = true;
                    break;
                }
            }
            if is_ok == false{
                invalid_value = value;
            }
            values[value]++;
            q = append(q,value);
            values[q[0]]--;
            if values[q[0]] == 0{
                delete(values,q[0]);
            }
            q = q[1:];
        }
    }

    pref_sum := int64(0);
    pref_sums := make(map[int64]int);
    pref_sums[0] = 0;

    for i,_ := range v{
        pref_sum += int64(v[i]);
        if ind,ok := pref_sums[pref_sum - int64(invalid_value)];ok{
            mi := int64(1e18);
            ma := -int64(1e18);
            for j := ind + 1;j <= i;j++{
                if mi > int64(v[j]){
                    mi = int64(v[j]);
                }
                if ma < int64(v[j]){
                    ma = int64(v[j]);
                }
            }
            fmt.Println(ma + mi);
            return ;
        }
        pref_sums[pref_sum] = i;
    }

}
