import numpy as np

dirs = ['N', 'S', 'E', 'W']

seaMonster=''                  # 
#    ##    ##    ###
 #  #  #  #  #  #   


def printPic(bigPictue):
    maxX, maxY = bigPictue.shape
    for y in range(maxY):
        printString = ''
        for x in range(maxX):
            printString = printString + bigPictue[y,x]
        print(printString)

class Tile:

    def __init__(self, id, tile):
        self.id = id
        self.tile = tile
        self.pos = None
        self.connection = {'N' : [], 'S' : [], 'E' : [], 'W' : []}
    
    def rotate(self):
        """
            Rotate 90 degrees
        """
        self.tile = np.rot90(self.tile)
        return
    
    def flipX(self):
        """
            Flip x-axis
        """
        self.tile = np.flip(self.tile, axis = 1)
        return

    def flipY(self):
        """
            Flip y-axis
        """
        self.tile = np.flip(self.tile, axis = 0)
        return
    
    def getEdge(self, dir):
        if dir == 'N':
            return self.tile[0,:]
        elif dir == 'S':
            return self.tile[-1,:]
        elif dir == 'E':
            return self.tile[:,-1]
        elif dir == 'W':
            return self.tile[:,0]

    def getInner(self):
        return self.tile[1:-1,1:-1]

    def checkMatch(self, dir, edgeToMatch, pos):
        edgeRev = np.flip(edgeToMatch)
        for _ in range(4):
            if edgesEqual(self.getEdge(dir), edgeToMatch):
                self.pos = pos
                return True
            elif edgesEqual(self.getEdge(dir), edgeRev):
                if dir in ('N', 'S'):
                    self.flipX()
                elif dir in ('E', 'W'):
                    self.flipY()
                self.pos = pos
                return True
            self.rotate()
        return False

def edgesEqual(firstEdge, secondEdge):
    n1 = len(firstEdge)
    n2 = len(secondEdge)
    if n1 == n2:
        for i in range(n1):
            if firstEdge[i] != secondEdge[i]:
                return False
        return True
    return False

def containsSeamonster(bigPicture, seaMonster):
    numMonsters = 0
    yM, xM = seaMonster.shape
    yP, xP = bigPictue.shape
    for y in range(yP):
        if y + yM > yP:
            break
        for x in range(xP):
            if x + xM > xP:
                break
            foundMonster = True
            for y2 in range(yM):
                for x2 in range(xM):
                    if seaMonster[y2,x2] == '#':
                        if bigPictue[y+y2,x+x2] != '#':
                            foundMonster = False
            if foundMonster:
                numMonsters += 1
    return numMonsters

with open("20/input.txt") as f:
	tiles = f.read().splitlines()

with open("20/seamonster.txt") as f:
    seaMonster = f.read().splitlines()

seaMonsterPattern = []
for line in seaMonster:
    seaMonsterPattern.append(list(line))
seaMonster = np.array(seaMonsterPattern)
print(seaMonster)
tileDict = {}
for line in tiles:
    if line[:4] == 'Tile':
        id = int(line[5:-1])
        tileMap = []
    elif line != '':
        tileMap.append(list(line))
    else:
        tileMap = np.array(tileMap)
        newTile = Tile(id, tileMap)
        tileDict[id] = newTile
tileMap = np.array(tileMap)
newTile = Tile(id, tileMap)
tileDict[id] = newTile
pos = (0,0)
idToPlace, tileToPlace = tileDict.popitem()
tileToPlace.pos = pos
tilesToPlaceDict = {idToPlace : tileToPlace}
placedTiles = {}
minX = 0
minY = 0
maxX = 0
maxY = 0

while tilesToPlaceDict:
    idToPlace, tileToPlace = tilesToPlaceDict.popitem()
    placedTiles[idToPlace] = tileToPlace
    for dir in dirs:
        edgeToMatch = tileToPlace.getEdge(dir)
        pos = tileToPlace.pos
        posX = pos[0]
        posY = pos[1]
        if dir == 'N':
            posY += 1
            dirToCheck = 'S'
        elif dir == 'S':
            posY-= 1
            dirToCheck = 'N'
        elif dir == 'E':
            posX += 1
            dirToCheck = 'W'
        elif dir == 'W':
            posX -= 1
            dirToCheck = 'E'
        posToPlace = (posX, posY)
        foundMatch = False
        for idToCheck, tileToCheck in tileDict.items():
            if tileToCheck.checkMatch(dirToCheck, edgeToMatch, posToPlace):
                foundMatch = True
                idFound = idToCheck
                tileFound = tileToCheck
                if posX < minX:
                    minX = posX
                elif posX > maxX:
                    maxX = posX
                if posY < minY:
                    minY = posY
                elif posY > maxY:
                    maxY = posY
                break
        if foundMatch:
            tilesToPlaceDict[idToCheck] = tileToCheck
            tileDict.pop(idToCheck)
xLength = (maxX-minX+1)*8
yLength = (maxY-minY+1)*8
bigPictue = np.empty(((maxX-minX+1)*8, (maxY-minY+1)*8),dtype=np.unicode_)
for x in range(minX, maxX+1):
    indX = x - minX
    for y in range(minY, maxY+1):
        indY = y - minY
        for id, tile in placedTiles.items():
            if tile.pos == (x,y):
                bigPictue[yLength-indY*8 - 8:(yLength-indY*8),indX*8:(indX*8+8)] = tile.getInner()


numSeamonsters = containsSeamonster(bigPictue, seaMonster)
tries = 1
while not numSeamonsters:
    bigPictue = np.rot90(bigPictue)
    tries += 1
    if tries == 4:
        bigPictue = np.flip(bigPictue, axis = 1)
    elif tries == 8:
        bigPictue = np.flip(bigPictue, axis = 0)
    numSeamonsters = containsSeamonster(bigPictue, seaMonster)
    if tries == 15:
        break

totWaves = np.sum(bigPictue == '#')
seaMonsterHas = np.sum(seaMonster == '#')
print('Found {} Sea Monsters, found {} waves'.format(numSeamonsters,totWaves - seaMonsterHas*numSeamonsters))
print(numSeamonsters)
    