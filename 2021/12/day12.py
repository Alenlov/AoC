mapFile = open('2021/12/input').read().splitlines()

caves = {}



def numPathsA(curr,history):
    
    newHistory = history.copy()
    newHistory.append(curr)
    if curr == 'end':
        return 1
    else:
        tot = 0
        for c in caves[curr]:
            if ord(c[0]) < ord('a'): #Upper Case
                tot += numPathsA(c,newHistory)
            else:
                if c not in newHistory:
                    tot += numPathsA(c,newHistory)
        return tot

def numPathsB(curr,history):

    newHistory = history.copy()
    if (ord(curr[0])>=ord('a')):
        if curr in newHistory:
            newHistory[0] = 1
    newHistory.append(curr)

    if curr == 'end':
        return 1
    else:
        tot = 0
        for c in caves[curr]:
            if c != 'start':
                if ord(c[0]) < ord('a'): #Upper Case
                    tot += numPathsB(c,newHistory)
                else:
                    if newHistory[0] == 0:
                        tot += numPathsB(c,newHistory)
                    else:
                        if c not in newHistory:
                            tot += numPathsB(c,newHistory)
                
        return tot


for m in mapFile:
    lhs, rhs = m.split('-')
    if lhs not in caves:
        caves[lhs] = [rhs]
    else:
        caves[lhs].append(rhs)
    if rhs not in caves:
        caves[rhs] = [lhs]
    else:
        caves[rhs].append(lhs)



print("Answer part A: The number of paths is {}".format(numPathsA('start',[])))
print("Answer part B: The number of paths is {}".format(numPathsB('start',[0])))