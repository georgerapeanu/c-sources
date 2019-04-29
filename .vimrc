set autoindent
set cindent
set tabstop=4
set shiftwidth=4
set expandtab

function Comp()
    :w
    :!g++ --std=c++11 -Wall -O2 -static -o _%< % -lm
endfunction

function Exec()
    :w     
    :!g++ --std=c++11 -Wall -O2 -static -o _%< % -lm && ./_%<
endfunction

function Debug()
    :w
    :!g++ --std=c++11 -Wall -O0 -o _%< % -lm -g -fsanitize=address && ./_%<
endfunction

function Input()
    :exec ":vs " . expand("%:r") . ".in"
endfunction

function Output()
    :exec ":vs " . expand("%:r") . ".out"
endfunction

let mapleader = " "

map<leader>c :call Comp()<Return>
map<leader>e :call Exec()<Return>
map<leader>i :call Input()<Return>
map<leader>o :call Output()<Return>
map<leader>d :call Debug()<Return>
