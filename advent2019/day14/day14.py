#!/usr/bin/python3

import collections

def run(recipe,val_recipe,b_gr,val):
    proc = [];
    amount = collections.defaultdict(lambda : 0);
    gr = b_gr.copy();
    for x in recipe:
        amount[x] = (val if x == "FUEL" else 0);
        if gr[x] == 0:
            proc.append(x);
    while len(proc) > 0:
        elem = proc[0];
        proc.pop(0);
        if elem == "ORE":
            continue;
        amount[elem] = int((amount[elem] + val_recipe[elem] - 1) / val_recipe[elem]) * val_recipe[elem];
        for ing in recipe[elem]:
            amount[ing] = amount[ing] + int(amount[elem] / val_recipe[elem]) * recipe[elem][ing];
            gr[ing] = gr[ing] - 1;
            if gr[ing] == 0:
               proc.append(ing);

    print(amount["ORE"]);
    return amount["ORE"]

def __main__():
    
    f = open("in","r");

    gr = collections.defaultdict(lambda : 0);
    recipe = {};
    val_recipe = {};

    for line in f:
        tmp = line.rstrip().split(' ')
        result = (int(tmp[len(tmp) - 2]),tmp[len(tmp) - 1]);
        tmp.pop(len(tmp) - 1);
        tmp.pop(len(tmp) - 1);
        tmp.pop(len(tmp) - 1);
        ingredients = [];
        for i in range(0,len(tmp),2):
            if tmp[i + 1][len(tmp[i + 1]) - 1] == ',':
                tmp[i + 1] = tmp[i + 1][:-1];
            ingredients.append((tmp[i],tmp[i + 1]))
        print(ingredients)
        tmp_recipe = {};
        for x in ingredients:
            tmp_recipe[x[1]] = int(x[0]);
            gr[x[1]] = gr[x[1]] + 1;
        val_recipe[result[1]] = int(result[0]);
        recipe[result[1]] = tmp_recipe;

    
    l = 0;
    r = int(1e7 + 1);

    while r - l > 1:
        print(l,r);
        m = int((l + r) / 2);
        if run(recipe,val_recipe,gr,m) <= 1000000000000:
            l = m;
        else:
            r = m;
    
    print(l);

__main__();
