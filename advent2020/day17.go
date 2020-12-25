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

func main(){

    CYCLES := 6;

    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }

    scanner := bufio.NewScanner(file);

    var initial [][]int;

    for scanner.Scan(){
        tmp := scanner.Text()
        if len(tmp) == 0{
            break;
        }

        var row []int;
        for _,val := range tmp{
            if byte(val) == byte('.'){
                row = append(row,0);
            }else{
                row = append(row,1);
            }
        }
        initial = append(initial,row);
    }

    v := make_4d_slice(2 * CYCLES + 1,2 * CYCLES + 1,len(initial) + 2 * CYCLES,len(initial[0]) + 2 * CYCLES);

    for i := 0;i < len(initial);i++{
        for j := 0;j < len(initial[i]);j++{
            v[CYCLES][CYCLES][i + CYCLES][j + CYCLES] = initial[i][j];
        }
    }

    for h := 0;h < CYCLES;h++{
        new_v := make_4d_slice(len(v),len(v[0]),len(v[0][0]),len(v[0][0][0]));
        for i := 0;i < len(v);i++{
            for j := 0;j < len(v[i]);j++{
                for k := 0;k < len(v[i][j]);k++{
                    for l := 0;l < len(v[i][j][k]);l++{
                        cnt_active := 0;
                        for dx := -1;dx <= 1;dx++{
                            for dy := -1;dy <= 1;dy++{
                                for dz := -1;dz <= 1;dz++{
                                    for dw := -1;dw <= 1;dw++{
                                        if dx == 0 && dy == 0 && dz == 0 && dw == 0{
                                            continue;
                                        }
                                        x := i + dx;
                                        y := j + dy;
                                        z := k + dz;
                                        w := l + dw;
                                        if 0 <= x && x < len(v) && 0 <= y && y < len(v[x]) && 0 <= z && z < len(v[x][y]) && 0 <= w && w < len(v[x][y][z]){
                                            cnt_active += v[x][y][z][w];
                                        }
                                    }
                                }
                            }
                        }
                        if (v[i][j][k][l] == 1 && (cnt_active == 2 || cnt_active == 3)) || (v[i][j][k][l] == 0 && cnt_active == 3){
                            new_v[i][j][k][l] = 1;
                        }else{
                            new_v[i][j][k][l] = 0;
                        }
                    }
                }
            }
        }
        v = new_v;
    }

    sum := 0;

    for i := 0;i < len(v);i++{
        for j := 0;j < len(v[i]);j++{
            for k := 0;k < len(v[i][j]);k++{
                for l := 0;l < len(v[i][j][k]);l++{
                    sum += v[i][j][k][l];
                }
            }
        }
    }

    fmt.Println(sum);
}
