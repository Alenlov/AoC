def activeNeighbors(x, y, z, w, cubeDict):
    numActive = 0
    for i in range(-1,2):
        for j in range(-1, 2):
            for k in range(-1, 2):
                for l in range(-1, 2):
                    if not (i == j == k == l == 0):
                        if (x + i, y + j, z + k, w + l) in cubeDict:
                            if cubeDict[(x+i,y+j,z+k,w+l)]:
                                numActive += 1
    return numActive

with open("17/input.txt") as f:
	cubes = f.read().splitlines()

cubeDict = {}
minY = 0
maxY = len(cubes)
minX = 0
maxX = len(cubes[0])
minZ = 0
maxZ = 1
minW = 0
maxW = 1
y = 0
z = 0
w = 0
for cubeLine in cubes:
    x = 0
    for cube in cubeLine:
        if cube == '#':
            cubeDict[(x,y,z,w)] = True
        elif cube == '.':
            cubeDict[(x,y,z,w)] = False
        x += 1
    y += 1

for turn in range(6):
    newCubeDict = {}
    for x in range(minX - 1 - turn, maxX + 1 + turn):
        for y in range(minY - 1 - turn, maxY + 1 + turn):
            for z in range(minZ - 1 - turn, maxZ + 1 + turn):
                for w in range(minW - 1 - turn, maxW + 1 + turn):
                    numActive = activeNeighbors(x,y,z,w,cubeDict)
                    if (x,y,z,w) in cubeDict:
                        if cubeDict[(x,y,z,w)]:
                            if (2 <= numActive <= 3):
                                newCubeDict[(x,y,z,w)] = True
                        else:
                            if numActive == 3:
                                newCubeDict[(x,y,z,w)] = True
                    else:
                        if numActive == 3:
                            newCubeDict[(x,y,z,w)] = True
    cubeDict = newCubeDict.copy()


numActive = 0
for val in cubeDict.values():
    if val:
        numActive += 1

print(numActive)
