import bisect
word = input()
N = int(input())

alfabet = [[] for i in range(26)]
for i in range(len(word)):
    alfabet[ord(word[i])-97] += [i]


ans = 0
for i in range(N):
    synonym = input()
    double = False
    prev = -10**9
    extra = -10**9
    for j in range(len(synonym)):
        letter = ord(synonym[j])-97
        thing = bisect.bisect_left(alfabet[letter], prev+1)
        if thing >= len(alfabet[letter]):
            break
        else:
            index = alfabet[letter][thing]
        if index > extra and extra != -10**9:
            double = True
        
        if thing+1 < len(alfabet[letter]):
            extra = alfabet[letter][thing+1]
            if j==len(synonym)-1:
                double = True
        else:
            extra = 10**9
        
        prev = index
        
        if j==len(synonym)-1 and double == True:
            ans+=1
print(ans)
