from queue import Queue
with open('input') as f:
    lines = f.read().splitlines()

garden = dict()
startPos = (0,0)

for row, line in enumerate(lines):
    for col in range(0,len(line)):
        if line[col] == 'S':
            startPos = (row, col, 0)
            garden[(row,col)] = '.'
        else:
            garden[(row,col)] = line[col]

def walk(numberOfSteps):
    steps = Queue()
    steps.put(startPos)
    evensteps = dict()
    oddsteps = dict()

    while not steps.empty():
        pos = steps.get()
        # print(pos)
        row = pos[0]
        col = pos[1]
        nbr = pos[2]

        goNext = True
        if nbr % 2 == 0:
            if (row, col) not in evensteps:
                evensteps[(row, col)] = True
            else:
                goNext = False
        else:
            if (row, col) not in oddsteps:
                oddsteps[(row, col)] = True
            else:
                goNext = False
        # else:
        s = len(lines)
        if goNext:
            newNbr = nbr + 1
            if newNbr <= numberOfSteps:
                if garden[((row+1) % s, col % s)] != '#':
                    steps.put((row+1, col, newNbr))
                if garden[((row-1) % s, col % s)] != '#':
                    steps.put((row-1, col, newNbr))
                if  garden[(row %s, (col+1)%s)] != '#':#
                    steps.put((row, col+1, newNbr))
                if garden[(row%s, (col-1)%s) ] != '#':
                    steps.put((row, col-1, newNbr))
    if numberOfSteps % 2 == 0:
        return len(evensteps)
    else:
        return len(oddsteps)

print(walk(65))
print(walk(196))
print(walk(65+131*2))
steps0 = walk(65)
steps1 = walk(65+131*1)
steps2 = walk(65+131*2)
c = steps0
a = (steps2-2*steps1+c) / 2.0
b = steps1 - c - a

largeNumber = (26501365 - 65) / 131.0
# print(a,b,c, largeNumber)
print(a*largeNumber*largeNumber+b*largeNumber+c)

# 584211423220706 too high