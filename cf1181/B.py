l = int(input())
n = int(input())

a = []

while n != 0:
    a.append(n % 10)
    n = int(n / 10)

a.reverse()

x = int(l / 2)
y = x + 1
z = x - 1

while a[z] == 0:
    z = z - 1
while a[x] == 0:
    x = x - 1
while (a[y] == 0) and y < l:
    y = y + 1

b=0
c=0

i=0;

ans = 10**100002

if x != 1:
    i=0;
    b=0;
    c=0;
    while i < x:
        b = b * 10 + a[i];
        i = i + 1
    while i < l:
        c = c * 10 + a[i];
        i = i + 1
    ans = min(ans,abs(b + c));

if z != 1:
    i=0;
    b=0;
    c=0;
    while i < z:
        b = b * 10 + a[i];
        i = i + 1
    while i < l:
        c = c * 10 + a[i];
        i = i + 1
    ans = min(ans,abs(b + c));
        
if y != l:
    i=0;
    b=0;
    c=0;
    while i < y:
        b = b * 10 + a[i];
        i = i + 1
    while i < l:
        c = c * 10 + a[i];
        i = i + 1
    ans = min(ans,abs(b + c));

print(ans)

