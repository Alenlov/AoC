import time

file = open('2021/15/input').read().splitlines()

chitons = []

for line in file:
    chitons.append([int(x) for x in line])

def chitonsVal(x,y):
    N = len(chitons)
    inc = x//N + y//N
    x,y = (x%N, y%N)
    val = ((chitons[y][x] + inc - 1) % 9) + 1
    return val

diff = [-1,1]

path = {}

heads = [(0,0)] #Triplet, x,y
headVals = {(0,0):-chitons[0][0]}
itr = 0
start = time.time()

while heads:
    itr += 1
    if (itr % 100000) == 0:
        print(itr, len(path), len(heads), len(headVals),time.time() - start)
        start = time.time()
    x,y = heads.pop(0)
    val = headVals[(x,y)]
    del headVals[(x,y)]
    newVal = val + chitonsVal(x,y)
    if (x,y) in path:
        if path[(x,y)] <= newVal:
            continue
    
    path[(x,y)] = newVal
    for dx in diff:
        if -1 < (x + dx) < 5*len(chitons):
            if (x+dx,y) not in path:
                if (x+dx,y) not in heads:
                    heads.append((x+dx,y))
                    headVals[(x+dx,y)] = newVal
                else:
                    if headVals[(x+dx,y)] > newVal:
                        headVals[(x+dx,y)] = newVal
            else:
                if path[(x+dx,y)] > newVal + chitonsVal(x+dx,y):
                    if (x+dx,y) not in heads:
                        heads.append((x+dx,y))
                        headVals[(x+dx,y)] = newVal
                    else:
                        if headVals[(x+dx,y)] > newVal:
                            headVals[(x+dx,y)] = newVal
    for dy in diff:
        if -1 < (y + dy) < 5*len(chitons):
            if (x,y+dy) not in path:
                if (x,y+dy) not in heads:
                    heads.append((x,y+dy))
                    headVals[(x,y+dy)] = newVal
                else:
                    if headVals[(x,y+dy)] > newVal:
                        headVals[(x,y+dy)] = newVal
            else:
                if path[(x,y+dy)] > newVal + chitonsVal(x,y+dy):
                    if (x,y+dy) not in heads:
                        heads.append((x,y+dy))
                        headVals[(x,y+dy)] = newVal
                    else:
                        if headVals[(x,y+dy)] > newVal:
                            headVals[(x,y+dy)] = newVal

print(path[(len(chitons)-1,len(chitons[0])-1)],itr)
print(path[(5*len(chitons)-1,5*len(chitons[0])-1)],itr)    
    

