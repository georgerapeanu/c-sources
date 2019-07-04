def comb(n,m):
    ans = 1;
    for x in range(n - m + 1,n + 1):
        ans = ans * x
    for x in range(1,m + 1):
        ans = ans / x
    return ans

ans = 0
ans = ans + comb(4,1) * comb(5,1)
ans = ans + comb(4,2) * comb(5,2)
ans = ans + comb(4,3) * comb(5,3)
ans = ans + comb(4,4) * comb(5,4)

print(ans)
