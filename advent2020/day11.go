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

var dx = [8]int{-1,-1,0,1,1,1,0,-1};
var dy = [8]int{0,1,1,1,0,-1,-1,-1};

func get_next (v [][]byte) ([][]byte,bool){
    var ans [][]byte;

    for i := 0;i < len(v);i++{
        var row []byte;
        for j := 0;j < len(v[i]);j++{
            row = append(row,v[i][j]);
        }
        ans = append(ans,row);
    }

    ok := false;

    for i := 0;i < len(v);i++{
        for j := 0;j < len(v[i]);j++{
            if v[i][j] == '.'{
                continue;
            }else{
                cnt := 0;
                for k := 0;k < 8;k++{
                    for l := 1;true;l++{
                        x := i + l * dx[k];
                        y := j + l * dy[k];
                        if x < 0 || y < 0 || x >= len(v) || y >= len(v[x]){
                            break;
                        }else if v[x][y] == '#'{
                            cnt++;
                            break;
                        }else if v[x][y] == 'L'{
                            break;
                        }

                    }
                }
                if v[i][j] == '#' && cnt >= 5{
                    ans[i][j] = 'L';
                    ok = true;
                }else if v[i][j] == 'L' && cnt == 0{
                    ans[i][j] = '#';
                    ok = true;
                }
            }
        }
    }

    return ans,ok;
}

func main(){


    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }

    scanner := bufio.NewScanner(file);

    var v [][]byte;

    for scanner.Scan(){
        tmp := scanner.Text()
        if len(tmp) == 0{
            break;
        }

        var row []byte;
        for _,val := range tmp{
            row = append(row,byte(val));
        }
        v = append(v,row);
    }

    var new_v [][]byte;
    ok := true;

    for ok{
        new_v,ok = get_next(v);
        if ok{
            v = new_v;
        }
    }

    ans := 0;

    for _,row := range v{
        for _,elem := range row{
            if elem == '#'{
                ans++;
            }
        }
    }

    fmt.Println(ans);
}
