import math

targetArea = open('2021/17/input').read().strip()
_, targetArea = targetArea.split(': ')
xArea, yArea = targetArea.split(', ')
minX, maxX = xArea[2:].split('..')
minY, maxY = yArea[2:].split('..')
minX = int(minX)
maxX = int(maxX)
minY = int(minY)
maxY = int(maxY)

print(xArea,yArea)

def arSum(v):
    return v*(v+1)//2

print("Answer part A: the maximum height is {}".format(arSum(abs(minY)-1)))

# X -values stopping in area, this is slowest x that will get us there

minV = math.ceil(-1/2 + math.sqrt(2*minX + 1/4))
maxV = math.floor(-1/2 + math.sqrt(2*maxX + 1/4))

print(minV, maxV)



xDict = {}
for x in range(minV, maxX+1):
    t = 0
    vx = x
    pos = 0
    while pos < maxX:
        pos += vx
        t += 1
        vx -= 1
        if vx < 0:
            vx = 0
        if minX <= pos <= maxX:
            if t not in xDict:
                xDict[t] = []
            xDict[t].append(x)
        if vx == 0:
            pos = maxX

print(xDict)

yDict = {}
for y in range( minY , abs(minY) ):
    t = 0
    vy = y
    pos = 0
    while pos > minY:
        pos += vy
        vy -= 1
        t += 1
        if minY <= pos <= maxY:
            if t not in yDict:
                yDict[t] = []
            yDict[t].append(y)

print(yDict)
comboSet = set()
combos = 0
for t in yDict:
    if t not in xDict:
        xvals = []
    else:
        xvals = xDict[t]
    for v in range(minV,maxV+1):
        if t > v:
            xvals.append(v)
    
    for y in yDict[t]:
        for x in xvals:
            comboSet.add((x,y))
print("Answer part B: number of combos is {}".format(len(comboSet)))