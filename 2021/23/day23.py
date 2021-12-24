import time
from queue import PriorityQueue
start = time.time()
initState = open('2021/23/input').read().splitlines()
fishVals = {'A':1,'B':10,'C':100,'D':1000}
finalStates = {'A':{(3,2),(3,3)},'B':{(5,2),(5,3)},'C':{(7,2),(7,3)},'D':{(9,2),(9,3)}}
caveOpenings = {(3,1),(5,1),(7,1),(9,1)}
diffs = {(-1,0),(1,0),(0,-1),(0,1)}
map = set()

def possibleMoves(pos, fishes):
    possibleCand = set()
    heads = [pos]
    while heads:
        head = heads.pop(0)
        for d in diffs:
            newPos = (head[0] + d[0], head[1] + d[1])
            if newPos not in fishes and newPos in map and newPos not in possibleCand:
                heads.append(newPos)
                possibleCand.add(newPos)
    possible = {}
    
    for p in possibleCand:
        if p not in caveOpenings:
            if (pos[1] in {2,3} and p[1] == 1):
                possible[p] = abs(pos[0] - p[0]) + abs(pos[1] - p[1])
            elif pos[1] == 1:
                if fishDone(p, fishes, variant=fishes[pos]):
                    return {p:abs(pos[0] - p[0]) + abs(pos[1] - p[1])}
                

    return possible

def allDone(fishes):
    done = 0
    for fish in fishes:
        if fish in finalStates[fishes[fish]]:
            done += 1
    return done

def hashFish(fishes):
    newDict = {}
    for fish in fishes:
        if fishes[fish] not in newDict:
            newDict[fishes[fish]] = []
        newDict[fishes[fish]].append(fish)
    output = ''
    for f in ['A','B','C','D']:
        output += f
        for pos in newDict[f]:
            output += str(pos[0]) + str(pos[1])
    return output



def fishDone(fish, fishes, variant=None):
    if not variant:
        variant = fishes[fish]
    if fish in finalStates[variant]:
        if fish[1] == 2:
            belowCord = (fish[0], 3)
            if belowCord in fishes:
                if fishes[belowCord] == variant:
                    return True
        else:
            return True
    return False


checkedStates = {}
statesToCheck = PriorityQueue()
fishes = {}

for y in range(len(initState)):
    for x in range(len(initState[y])):
        if initState[y][x] == '.':
            map.add((x,y))
        elif initState[y][x] in fishVals:
            map.add((x,y))
            fishes[(x,y)] = initState[y][x]

str2dict = {}

fishHash = hashFish(fishes)
str2dict[fishHash] = fishes

statesToCheck.put((0,fishHash))
while statesToCheck:
    (energy, state) = statesToCheck.get()
    if state in checkedStates:
        continue
    numDone = 0
    checkedStates[state] = energy
    fishes = str2dict[state]
    if allDone(fishes) == 8:
        ansA = energy
        break
    for fish in fishes:
        if not fishDone(fish,fishes):
            possible = possibleMoves(fish, fishes)
            for pos in possible:
                newState = fishes.copy()
                del newState[fish]
                newState[pos] = fishes[fish]
                nfStr = hashFish(newState)
                if nfStr not in checkedStates:
                    str2dict[nfStr] = newState
                    numDone = allDone(newState)
                    statesToCheck.put((energy + possible[pos]*fishVals[fishes[fish]], nfStr) )
        else:
            numDone += 1
print("Answer part A: minimum energy is {}, took {:.2f} s".format(ansA,time.time()-start))

