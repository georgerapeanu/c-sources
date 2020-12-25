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

type Tile struct{
    id int;
    stuff []string;
};

type Data struct{
    tile Tile;
    x,y int;
}

func flip_v (tile Tile)Tile{
    var ans Tile;
    ans.id = tile.id;
    n := len(tile.stuff);
    m := len(tile.stuff[0]);
    ans.stuff = make([]string,n);
    for i := 0;i < n;i++{
        line := "";
        for j := 0;j < m;j++{
            line += string(tile.stuff[n - 1 - i][j]);
        }
        ans.stuff[i] = line;
    }

    return ans;
}

func rot90(tile Tile)Tile{
    var ans Tile;
    ans.id = tile.id;
    n := len(tile.stuff);
    m := len(tile.stuff[0]);
    ans.stuff = make([]string,m);
    for i := 0;i < m;i++{
        line := "";
        for j := 0;j < n;j++{
            line += string(tile.stuff[j][n - 1 - i]);
        }
        ans.stuff[i] = line;
    }

    return ans;
}

func make_2d_slice(n,m int)[][]byte{
    var ans [][]byte;

    for i := 0;i < n;i++{
        var row []byte;
        for j := 0;j < m;j++{
            row = append(row,byte(0));
        }
        ans = append(ans,row);
    }
    return ans;
}

func image_rot90(image [][]byte)[][]byte{
    n := len(image);
    m := len(image[0]);

    ans := make_2d_slice(m,n);

    for i := 0;i < m;i++{
        for j := 0;j < n;j++{
            ans[i][j] = image[n - 1 - j][i];
        }
    }
    return ans;
}

func image_flip(image [][]byte)[][]byte{
    n := len(image);
    m := len(image[0]);

    ans := make_2d_slice(n,m);

    for i := 0;i < n;i++{
        for j := 0;j < m;j++{
            ans[i][j] = image[n - 1 - i][j];
        }
    }

    return ans;
}
func main(){

    file, err := os.Open("./in");

    if err != nil{
        fmt.Println(err);
        return ;
    }
    tiles := []Tile{};

    scanner := bufio.NewScanner(file);
    for scanner.Scan(){
        var tile Tile = Tile{};

        fmt.Sscanf(scanner.Text(),"Tile %d:",&tile.id);

        for scanner.Scan(){
            if len(scanner.Text()) == 0{
                break;
            }
            tile.stuff = append(tile.stuff,scanner.Text());
        }

        tiles = append(tiles,tile);
    }

    var stuff []Data;
    var taken []bool;

    for i := 0;i < len(tiles);i++{
        taken = append(taken,false);
    }

    stuff = append(stuff,Data{tiles[0],0,0});
    taken[0] = true;

    for i := 0;i < len(stuff);i++{
        tile := stuff[i].tile;
        for j := 0;j < len(tiles);j++{
            if taken[j]{
                continue;
            }

            found := false;
            for dir := 0;dir < 4 && found == false;dir++{
                tiles[j] = rot90(tiles[j]);
                for flip := 0;flip < 2;flip++{
                    tiles[j] = flip_v(tiles[j]);
                    if len(tiles[j].stuff) != len(tile.stuff){
                        continue;
                    }
                    n := len(tile.stuff);
                    m := len(tile.stuff[0]);

                    var ok bool;

                    ok = true;
                    for i := 0;i < m;i++{
                        if tile.stuff[0][i] != tiles[j].stuff[n - 1][i]{
                            ok = false;
                        }
                    }
                    if ok{
                        var tmp Data;
                        tmp.tile = tiles[j];
                        tmp.x = stuff[i].x - 1;
                        tmp.y = stuff[i].y;
                        stuff = append(stuff,tmp);
                        found = true;
                        break;
                    }

                    ok = true;
                    for i := 0;i < n;i++{
                        if tile.stuff[i][m - 1] != tiles[j].stuff[i][0]{
                            ok = false;
                        }
                    }
                    if ok{
                        var tmp Data;
                        tmp.tile = tiles[j];
                        tmp.x = stuff[i].x;
                        tmp.y = stuff[i].y + 1;
                        stuff = append(stuff,tmp);
                        found = true;
                        break;
                    }

                    ok = true;
                    for i := 0;i < m;i++{
                        if tile.stuff[n - 1][i] != tiles[j].stuff[0][i]{
                            ok = false;
                        }
                    }
                    if ok{
                        var tmp Data;
                        tmp.tile = tiles[j];
                        tmp.x = stuff[i].x + 1;
                        tmp.y = stuff[i].y;
                        stuff = append(stuff,tmp);
                        found = true;
                        break;
                    }

                    ok = true;
                    for i := 0;i < n;i++{
                        if tile.stuff[i][0] != tiles[j].stuff[i][m - 1]{
                            ok = false;
                        }
                    }
                    if ok{
                        var tmp Data;
                        tmp.tile = tiles[j];
                        tmp.x = stuff[i].x;
                        tmp.y = stuff[i].y - 1;
                        stuff = append(stuff,tmp);
                        found = true;
                        break;
                    }
                }
            }
            if found == true{
                taken[j] = true;
            }
        }
    }

    mi_x := 10000;
    ma_x := -10000;
    mi_y := 10000;
    ma_y := -10000;

    for _,val := range stuff{
        if mi_x > val.x{
            mi_x = val.x;
        }
        if ma_x < val.x{
            ma_x = val.x;
        }
        if mi_y > val.y{
            mi_y = val.y;
        }
        if ma_y < val.y{
            ma_y = val.y;
        }
    }

    n := len(stuff[0].tile.stuff);
    m := len(stuff[0].tile.stuff[0]);

    image := make_2d_slice((n - 2) * (ma_x - mi_x + 1),(m - 2) * (ma_y - mi_y + 1));

    for _,val := range stuff{
        X := val.x - mi_x;
        Y := val.y - mi_y;
        for i := 1;i < n - 1;i++{
            for j := 1;j < m - 1;j++{
                image[(i - 1) + X * (n - 2)][(j - 1) + Y * (n - 2)] = val.tile.stuff[i][j];
            }
        }
    }

    var pattern [][]byte;
    pattern = make_2d_slice(3,20);

    for i := 0;i < 3;i++{
        for j := 0;j < 20;j++{
            pattern[i][j] = byte(' ');
        }
    }

    pattern[0][18] = byte('#');
    pattern[1][0] = byte('#');
    pattern[1][5] = byte('#');
    pattern[1][6] = byte('#');
    pattern[1][11] = byte('#');
    pattern[1][12] = byte('#');
    pattern[1][17] = byte('#');
    pattern[1][18] = byte('#');
    pattern[1][19] = byte('#');
    pattern[2][1] = byte('#');
    pattern[2][4] = byte('#');
    pattern[2][7] = byte('#');
    pattern[2][10] = byte('#');
    pattern[2][13] = byte('#');
    pattern[2][16] = byte('#');

    for rot := 0;rot < 4;rot++{
        image = image_rot90(image);
        for flip := 0;flip < 2;flip++{
            image = image_flip(image);
            for i := 0;i + 2 < len(image);i++{
                for j := 0;j + 19 < len(image[i]);j++{
                    ok := true;
                    for k := 0;k < 3 && ok;k++{
                        for l := 0;l < 20 && ok;l++{
                            if pattern[k][l] == byte('#'){
                                if image[i + k][j + l] != byte('#'){
                                    ok = false;
                                }
                            }
                        }
                    }

                    if ok == true{
                        for k := 0;k < 3 && ok;k++{
                            for l := 0;l < 20 && ok;l++{
                                if pattern[k][l] == byte('#'){
                                    image[i + k][j + l] = byte('o');
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ans := 0;

    for i := 0;i < len(image);i++{
        for _,x := range image[i]{
            if x == byte('#'){
                ans++;
            }
        }
    }

    fmt.Println(ans);
}
