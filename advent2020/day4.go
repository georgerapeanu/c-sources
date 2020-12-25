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
        }
        ans = ans * 10 + int(c - '0');
    }

    return ans,true;
}

func is_valid_color(s string) bool{
    if len(s) != 7{
        return false;
    }
    if s[0] != '#'{
        return false;
    }

    for i := 1;i < 7;i++{
        value := s[i];
        if (value < '0' || value > '9') && (value < 'a' || value > 'f'){
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

    current_passport := make(map[string]string);
    target_keys := []string{"byr","iyr","eyr","hgt","hcl","ecl","pid"};

    cnt_valid := 0;

    for scanner.Scan(){
        if len(scanner.Text()) == 0{
            valid := true;

            for _,key := range target_keys{
                if _,ok := current_passport[key];ok == false{
                    valid = false;
                }
            }

            if valid{
                if val,ok := get_value(current_passport["byr"]);ok == false || val < 1920 || val > 2002{
                    valid = false;
                }

                if val,ok := get_value(current_passport["iyr"]);ok == false || val < 2010 || val > 2020{
                    valid = false;
                }

                if val,ok := get_value(current_passport["eyr"]);ok == false || val < 2020 || val > 2030{
                    valid = false;
                }

                if strings.HasSuffix(current_passport["hgt"],"cm"){
                    if val,ok := get_value(strings.TrimSuffix(current_passport["hgt"],"cm"));ok == false || val < 150 || val > 193{
                        valid = false;
                    }
                }else if strings.HasSuffix(current_passport["hgt"],"in"){
                    if val,ok := get_value(strings.TrimSuffix(current_passport["hgt"],"in"));ok == false || val < 59 || val > 76{
                        valid = false;
                    }
                }else{
                    valid = false;
                }

                if is_valid_color(current_passport["hcl"]) == false{
                    valid = false;
                }

                if s := current_passport["ecl"]; s != "amb" && s != "blu" && s != "brn" && s != "gry" && s != "grn" && s != "hzl" && s != "oth"{
                    valid = false;
                }

                if _,ok := get_value(current_passport["pid"]);ok == false || len(current_passport["pid"]) != 9{
                    valid = false;
                }

                if valid{
                    cnt_valid++;
                }
            }

            current_passport = make(map[string]string);
        }else{
            tmp := strings.Fields(scanner.Text())
            for _,item := range tmp{
                values := strings.Split(item,":");
                key := values[0];
                value := values[1];
                current_passport[key] = value;
            }
        }
    }
    fmt.Println(cnt_valid);
}
