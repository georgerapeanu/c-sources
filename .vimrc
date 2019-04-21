set tabstop=4
set shiftwidth=4
set expandtab
set autoindent
set cindent

" this functions only work for cwd :(

function Compile()
    :w
     :!g++ --std=c++11 -o2 -Wall -Wpedantic -o %<.exe %
endfunction

function Exec()
    :w
     :!(g++ --std=c++11 -o2 -Wall -Wpedantic -o %<.exe % && ./%<.exe)
endfunction

function Input()
    :execute ':vs ' . expand('%:r') . ".in"
endfunction

function Output()
    :execute ':vs ' . expand('%:r') . ".out"
endfunction

let mapleader = " "
map<leader>c :call Compile()<Return>
map<leader>e :call Exec()<Return>
map<leader>i :call Input()<Return>
map<leader>o :call Output()<Return>
