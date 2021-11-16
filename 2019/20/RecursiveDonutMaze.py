from queue import SimpleQueue




class Portal():
    def __init__(self, entrance, exit, name):
        self.entrance = entrance
        self.exit = exit
        self.name = name

def isLetter(chr):
    return ordA <= ord(chr) <= ordZ

def findEntrance(poses):
    toCheck = []
    for pos in poses:
        for dx in [-1,1]:
            toCheck.append((pos[0]+dx,pos[1]))
        for dy in [-1,1]:
            toCheck.append((pos[0],pos[1]+dy))
    for pos in toCheck:
        if mazeRaw[pos[1]][pos[0]] == '.':
            return pos

def printMaze(maze):
    sizeY = len(maze)
    sizeX = len(maze[0])
    for y in range(sizeY):
        for x in range(sizeX):
            print(maze[y][x],end='')
        print('')

def freeSpots(pos, maze, explored):
    toCheck = []
    for dx in [-1,1]:
        toCheck.append((pos[0]+dx,pos[1],pos[2]))
    for dy in [-1,1]:
        toCheck.append((pos[0],pos[1]+dy,pos[2]))
    
    freeList = []
    for testPos in toCheck:
        if testPos in explored:
            continue
        mazeVal = maze[testPos[1]][testPos[0]]
        #print(testPos)
        #print(mazeVal)
        if mazeVal == '.':
            freeList.append(testPos)
        elif isLetter(mazeVal):
            print("Standing at ({},{}) at layer {} found letter {}".format(pos[0],pos[1],pos[2],mazeVal))
            for portal in portals:
                print("Checking {} with entrance {} and exit {}".format(portal, portals[portal].entrance, portals[portal].exit))
                if (pos[0],pos[1]) == portals[portal].entrance:
                    print("Tog portal {} upp ett lager".format(portal))
                    newPos = (portals[portal].exit[0], portals[portal].exit[1], pos[2]+1)
                    if newPos not in explored:
                        freeList.append(newPos)
                elif (pos[0],pos[1]) == portals[portal].exit:
                    print("Tog portal {} ner ett lager".format(portal))
                    if pos[2] != 0:
                        newPos = (portals[portal].entrance[0], portals[portal].entrance[1], pos[2]-1)
                        if newPos not in explored:
                            freeList.append(newPos)
                    elif portal == 'ZZ':
                        newPos = (portals[portal].entrance[0], portals[portal].entrance[1], pos[2]-1)

                
    return freeList

def exploreMaze(posA,posZ, maze):
    
    headsA = SimpleQueue()
    headsA.put(posA)
    exploredA = {posA : 0}
    headsZ = SimpleQueue()
    headsZ.put(posZ)
    exploredZ = {posZ : 0}
    running = True
    while running:
        
        toMoveA = headsA.get()
        #print("Vi är på ({},{})".format(toMove[0],toMove[1]))
        newHeads = freeSpots(toMoveA, maze, exploredA)
        for head in newHeads:
            headsA.put(head)
            if head in exploredZ:
                running = False
                print("Chains found eachother after A : {} and Z : {} steps in total {} steps.".format(exploredA[toMoveA]+1,exploredZ[head],exploredA[toMoveA]+1+exploredZ[head]))
            exploredA[head] = exploredA[toMoveA] + 1
        if headsA.empty():
            running = False
            print("Out of heads")
        
        toMoveZ = headsZ.get()
        #print("Vi är på ({},{})".format(toMove[0],toMove[1]))
        newHeads = freeSpots(toMoveZ, maze, exploredZ)
        for head in newHeads:
            headsZ.put(head)
            if head in exploredA:
                running = False
                print("Chains found eachother after A : {} and Z : {} steps in total {} steps.".format(exploredA[head],exploredZ[toMoveZ]+1,exploredA[head]+exploredZ[toMoveZ]+1))
            exploredZ[head] = exploredZ[toMoveZ] + 1
        if headsZ.empty():
            running = False
            print("Out of heads")

mazeFile = open('2019/20/input', 'r')
mazeRaw = mazeFile.read().splitlines()
mazeFile.close()
for y in range(len(mazeRaw)):
	mazeRaw[y] = [char for char in mazeRaw[y]]

#print(mazeRaw)
sizeY = len(mazeRaw)
sizeX = len(mazeRaw[0])

ordA = ord('A')
ordZ = ord('Z')
portals = {}
portLocs = {}
for y in range(sizeY-1):
    for x in range(sizeX-1):
        if isLetter(mazeRaw[y][x]):
            #PORTAL!!
            name = ''
            ent = False
            if isLetter(mazeRaw[y][x+1]):
                name = ''.join([mazeRaw[y][x],mazeRaw[y][x+1]])
                ent = findEntrance([(x,y),(x+1,y)])
            elif isLetter(mazeRaw[y+1][x]):
                name = ''.join([mazeRaw[y][x],mazeRaw[y+1][x]])
                ent = findEntrance([(x,y),(x,y+1)])
            if ent:
                if ent[0] == 2 or ent[1] == 2 or ent[0] == sizeX - 3 or ent[1] == sizeY - 3:
                    if name in portals:
                        portals[name].exit = ent
                    else:
                       portals[name] = Portal((0,0),ent, name)
                else:
                    if name in portals:
                        portals[name].entrance = ent
                    else:
                        portals[name] = Portal(ent, (0,0), name)
portals['ZZ'].entrance = (-1,-1)
print(portals.keys())

mazeToPrint = mazeRaw.copy()

# for portal in portals:
#     ent = portals[portal].entrance
#     mazeToPrint[ent[1]][ent[0]] = '@'
#     ext = portals[portal].exit
#     if ext != (0,0):
#         mazeToPrint[ext[1]][ext[0]] = '%'

# printMaze(mazeToPrint)

exploreMaze((portals['AA'].exit[0],portals['AA'].exit[1],0),(portals['ZZ'].exit[0],portals['ZZ'].exit[1],0),mazeRaw)