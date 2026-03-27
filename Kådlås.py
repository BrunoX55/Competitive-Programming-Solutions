height, width = map(int, input().split()) 
out = 0
allLists = [] 
isBlocked = False
for i in range(height): 
    allLists.append(list(input())) 
    hasDot = False
    for j in range(len(allLists[i])):
        if allLists[i][j] == '.':
            hasDot = True
    if hasDot == False:
        isBlocked = True


def Search(opens, index, memo = [{} for i in range(height)]):
    global out
    value=0
    if tuple(opens) in memo[index]:
        return memo[index][tuple(opens)]
    for i in range(width):
        newOpens = []
        for j in range(len(opens)):
            if allLists[index][(opens[j] + i)%width] == '.':
                newOpens.append(opens[j])
        if len(newOpens) != 0 and index != height-1:
            value+=Search(newOpens, index+1, memo)
        elif len(newOpens) != 0 and index == height-1:
            value+=1
        elif len(newOpens) == 1:
            value+=1
    #print(opens, index, memo)
    memo[index][tuple(opens)]=value
    return value
firstOpen = []
for i in range(width):
    if allLists[0][i] == '.':
        firstOpen.append(i)
if isBlocked == False:
    print(Search(firstOpen,1)*width)
else:
    print(0)
