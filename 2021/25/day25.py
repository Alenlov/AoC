cucumbers = open('2021/25/input').read().splitlines()

southCucmbers = set()
eastCucumbers = set()
y = 0
for line in cucumbers:
    for x in range(len(line)):
        if line[x] == 'v':
            southCucmbers.add((x,y))
        elif line[x] == '>':
            eastCucumbers.add((x,y))
    y += 1
maxY = y
maxX = len(line)
print(maxX,maxY)
print(eastCucumbers)
print(southCucmbers)

def printCucumbers():
    print('')
    for y in range(maxY):
        for x in range(maxX):
            if (x,y) in southCucmbers:
                print('v',end='')
            elif (x,y) in eastCucumbers:
                print('>',end='')
            else:
                print('.',end='')
        print('')
    print('')

running = True
itr = 0
while running:
    # printCucumbers()
    # Move east
    numMoved = 0
    newEastCucumbers = set()
    for pos in eastCucumbers:
        newX = (pos[0] + 1) % maxX
        newPos = (newX, pos[1])
        if (newPos not in eastCucumbers) and (newPos not in southCucmbers):
            newEastCucumbers.add(newPos)
            numMoved += 1
        else:
            newEastCucumbers.add(pos)
    eastCucumbers = newEastCucumbers.copy()
    # Move south
    newSouthCucumbers = set()
    for pos in southCucmbers:
        newY = (pos[1] + 1) % maxY
        newPos = (pos[0], newY)
        if newPos not in eastCucumbers and newPos not in southCucmbers:
            newSouthCucumbers.add(newPos)
            numMoved += 1
        else:
            newSouthCucumbers.add(pos)
    southCucmbers = newSouthCucumbers.copy()
    itr += 1
    if numMoved == 0:
        running = False
    # if itr == 2:
    #     break

print("Answer part A: the first iteration where all ahve stopped moving is {}".format(itr))
