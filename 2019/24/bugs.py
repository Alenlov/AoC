def biodiversity(bugs):
    sum = 0
    power = 0
    for i in range(5):
        for j in range(5):
            if bugs[i][j] == '#':
                sum += 2**power
            power += 1
    return sum

def neighboors(bugs, i, j):
    num = 0
    if i > 0:
        if bugs[i-1][j] == '#':
            num += 1
    if i < 4:
        if bugs[i+1][j] == '#':
            num += 1
    if j > 0:
        if bugs[i][j-1] == '#':
            num += 1
    if j < 4:
        if bugs[i][j+1] == '#':
            num += 1
    return num

def updateBugs(bugs):
    newBugs = []
    for i in range(5):
        row = ''
        for j in range(5):
            numNgbr = neighboors(bugs, i,j)
            if bugs[i][j] == '#' and numNgbr == 1:
                row += '#'
            elif bugs[i][j] == '.' and 0 < numNgbr < 3:
                row += '#'
            else:
                row += '.'
        newBugs.append(row)
    return newBugs

def updateBugsRecursive(bugs):
    newBugs = {}
    candidateBugs = {}
    for bug in bugs:
        x = bug[0]
        y = bug[1]
        layer = bug[2]
        poses = []
        poses.append((x-1,y,layer))
        poses.append((x+1,y,layer))
        poses.append((x,y-1,layer))
        poses.append((x,y+1,layer))
        finalPoses = []
        #print(poses)
        for pos in poses:
            if pos[0] < 0:
                finalPoses.append((1,2,layer-1))
            elif pos[0] > 4:
                finalPoses.append((3,2,layer-1))
            elif pos[1] < 0:
                finalPoses.append((2,1,layer-1))
            elif pos[1] > 4:
                finalPoses.append((2,3,layer-1))
            elif (pos[0] == 2) and (pos[1] == 2):
                if x == 2:
                    if y == 1:
                        for i in range(5):
                            finalPoses.append((i,0,layer+1))
                    elif y == 3:
                        for i in range(5):
                            finalPoses.append((i,4,layer+1))
                elif y == 2:
                    if x == 1:
                        for i in range(5):
                            finalPoses.append((0,i,layer+1))
                    elif x == 3:
                        for i in range(5):
                            finalPoses.append((4,i,layer+1))
            else:
                finalPoses.append(pos)
        for pos in finalPoses:
            if pos in candidateBugs:
                candidateBugs[pos] += 1
            else:
                candidateBugs[pos] = 1
    #print(candidateBugs)
    for pos in candidateBugs:
        if pos in bugs:
            if candidateBugs[pos] == 1:
                newBugs[pos] = 0
        else:
            if 0 < candidateBugs[pos] < 3:
                newBugs[pos] = 0
    return newBugs


startingFile = open('2019/24/input','r')
startingBugs = startingFile.read().splitlines()
startingFile.close()
bioValues = set(str(biodiversity(startingBugs)))
bugs = startingBugs
running = True
while running:
    #print(bugs)
    bugs = updateBugs(bugs)
    val = str(biodiversity(bugs))
    if val in bioValues:
        print("The first repeat Biodiversity is {}".format(val))
        running = False
    else:
        bioValues.add(val)

bugs = {}
layer = 0
for i in range(5):
    for j in range(5):
        if startingBugs[i][j] == '#':
            bugs[(j,i,layer)] = 0
print(bugs)
for i in range(200):
    bugs = updateBugsRecursive(bugs)
print(bugs)

print("After 200 minutes there are {} bugs.".format(len(bugs)))