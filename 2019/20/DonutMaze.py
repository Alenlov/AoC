from queue import SimpleQueue




class Portal():
    def __init__(self, entrance, name):
        self.entrance = entrance
        self.exit = (0,0)
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
        toCheck.append((pos[0]+dx,pos[1]))
    for dy in [-1,1]:
        toCheck.append((pos[0],pos[1]+dy))
    
    freeList = []
    for testPos in toCheck:
        if testPos in explored:
            continue
        mazeVal = maze[testPos[1]][testPos[0]]
        print(testPos)
        print(mazeVal)
        if mazeVal == '.':
            freeList.append(testPos)
        elif isLetter(mazeVal):
            print("Standing at ({},{}) found letter {}".format(pos[0],pos[1],mazeVal))
            for portal in portals:
                print("Checking {} with entrance {} and exit {}".format(portal, portals[portal].entrance, portals[portal].exit))
                if pos == portals[portal].entrance:
                    print("Tog portal {}".format(portal))
                    newPos = portals[portal].exit
                    if newPos not in explored:
                        freeList.append(newPos)
                elif pos == portals[portal].exit:
                    print("Tog portal {}".format(portal))
                    newPos = portals[portal].entrance
                    if newPos not in explored:
                        freeList.append(newPos)
                
    return freeList

def exploreMaze(pos, maze):
    heads = SimpleQueue()
    heads.put(pos)
    explored = {pos : 0}
    running = True
    while running:
        toMove = heads.get()
        #print("Vi är på ({},{})".format(toMove[0],toMove[1]))
        newHeads = freeSpots(toMove, maze, explored)
        for head in newHeads:
            heads.put(head)
            if head == (-1,-1):
                running = False
                print("Found ZZ after {} steps.".format(explored[toMove]))
            explored[head] = explored[toMove] + 1

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
            if isLetter(mazeRaw[y][x+1]):
                name = ''.join([mazeRaw[y][x],mazeRaw[y][x+1]])
                ent = findEntrance([(x,y),(x+1,y)])
                if name in portals:
                    portals[name].exit = ent
                else:
                    portals[name] = Portal(ent, name)
            elif isLetter(mazeRaw[y+1][x]):
                name = ''.join([mazeRaw[y][x],mazeRaw[y+1][x]])
                ent = findEntrance([(x,y),(x,y+1)])
                if name in portals:
                    portals[name].exit = ent
                else:
                    portals[name] = Portal(ent, name)
portals['ZZ'].exit = (-1,-1)
#print(portals.keys())

# mazeToPrint = mazeRaw.copy()

# for portal in portals:
#     ent = portals[portal].entrance
#     mazeToPrint[ent[1]][ent[0]] = '@'
#     ext = portals[portal].exit
#     if ext != (0,0):
#         mazeToPrint[ext[1]][ext[0]] = '%'

#printMaze(mazeToPrint)

exploreMaze(portals['AA'].entrance,mazeRaw)