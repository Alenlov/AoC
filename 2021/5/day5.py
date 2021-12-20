lines = open('2021/5/input').read().splitlines()

ventsA = {}
ventsB = {}
for line in lines:
    start, end = line.split(" -> ")
    x1,y1 = start.split(',')
    x1 = int(x1)
    y1 = int(y1)
    x2,y2 = end.split(',')
    x2 = int(x2)
    y2 = int(y2)
    if x1 == x2:
        if y1 < y2:
            minY = y1
            maxY = y2
        else:
            minY = y2
            maxY = y1
        for y in range(minY,maxY+1):
            if (x1,y) not in ventsA:
                ventsA[(x1,y)] = 0
            ventsA[(x1,y)] += 1
            if (x1,y) not in ventsB:
                ventsB[(x1,y)] = 0
            ventsB[(x1,y)] += 1
    elif y1 == y2:
        if x1 < x2:
            minX = x1
            maxX = x2
        else:
            minX = x2
            maxX = x1
        for x in range(minX, maxX + 1):
            if (x,y1) not in ventsA:
                ventsA[(x,y1)] = 0
            ventsA[(x,y1)] += 1
            if (x,y1) not in ventsB:
                ventsB[(x,y1)] = 0
            ventsB[(x,y1)] += 1
    else:
        if x1 < x2:
            dirx = 1
        else:
            dirx = -1
        if y1 < y2:
            diry = 1
        else:
            diry = -1
        num = (x2-x1)*dirx
        for n in range(num+1):
            x = x1 + n*dirx
            y = y1 + n*diry
            if (x,y) not in ventsB:
                ventsB[(x,y)] = 0
            ventsB[(x,y)] += 1
answerA = 0
for pos in ventsA:
    if ventsA[pos] > 1:
        answerA += 1
print("Answer part A: The number of vents with more than 2 is {}".format(answerA))
answerB = 0
for pos in ventsB:
    if ventsB[pos] > 1:
        answerB += 1
print("Answer part B: The number of vents with more than two lines is {}".format(answerB))