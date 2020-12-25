package main

import (
        "fmt"
        "os"
        "bufio"
        "math"
        "math/cmplx"
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

    z := 10 + 1i;
    ship := 0 + 0i;

    for scanner.Scan(){
        tmp := scanner.Text()
        if len(tmp) == 0{
            break;
        }
        cmd := byte(tmp[0]);
        value,_ := get_value(tmp[1:]);

        if cmd == 'L'{
            angle := float64(value)/ float64(180) * float64(math.Pi);
            z *= cmplx.Rect(1,angle);
        }else if cmd == 'R'{
            angle := float64(value)/ float64(180) * float64(math.Pi);
            z *= cmplx.Rect(1,-angle);
        }else if cmd == 'F'{
            ship += z * complex(float64(value),0);
        }else if cmd == 'N'{
            z += complex(0,1) * complex(float64(value),0);
        }else if cmd == 'E'{
            z += complex(1,0) * complex(float64(value),0);
        }else if cmd == 'S'{
            z += complex(0,-1) * complex(float64(value),0);
        }else{
            z += complex(-1,0) * complex(float64(value),0);
        }
    }

    fmt.Println(math.Abs(real(ship)) + math.Abs(imag(ship)));
}
