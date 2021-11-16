import numpy as np

class Tile:


    def __init__(self, id, tile):
        self.id = id
        self.edges = {}
        self.edgeMatch = {}
        self.edges['N'] = list(tile[0])
        self.edges['S'] = list(tile[9])
        east = []
        west = []
        for i in range(10):
            east.append(tile[i][9])
            west.append(tile[i][0])
        self.edges['W'] = west
        self.edges['E'] = east
        self.edgeMatch['N'] = []
        self.edgeMatch['S'] = []
        self.edgeMatch['W'] = []
        self.edgeMatch['E'] = []
        #print(tile)
        #print(self.edges)

    def flipY(self):
        newNorth = self.edges['S']
        self.edges['S'] = self.edges['N']
        self.edges['N'] = newNorth
        self.edges['E'].reverse()
        self.edges['W'].reverse()
        newNorthMatch = self.edgeMatch['S']
        self.edgeMatch['S'] = self.edgeMatch['N']
        self.edgeMatch['N'] = newNorthMatch
        return

    def flipX(self):
        newEast = self.edges['W']
        self.edges['W'] = self.edges['E']
        self.edges['E'] = newEast
        self.edges['N'].reverse()
        self.edges['S'].reverse()
        newEastMatch = self.edgeMatch['W']
        self.edgeMatch['W'] = self.edgeMatch['E']
        self.edgeMatch['E'] = newEastMatch
        return

    def rotateRight(self):
        newSouth = self.edges['E']
        self.edges['E'] = self.edges['N']
        self.edges['N'] = self.edges['W']
        self.edges['W'] = self.edges['S']
        self.edges['S'] = newSouth
        newSouthMatch = self.edgeMatch['E']
        self.edgeMatch['E'] = self.edgeMatch['N']
        self.edgeMatch['N'] = self.edgeMatch['W']
        self.edgeMatch['W'] = self.edgeMatch['S']
        self.edgeMatch['S'] = newSouthMatch
        return

    def rotateLeft(self):
        newSouth = self.edges['W']
        self.edges['W'] = self.edges['N']
        self.edges['N'] = self.edges['E']
        self.edges['E'] = self.edges['S']
        self.edges['S'] = newSouth
        newSouthMatch = self.edgeMatch['W']
        self.edgeMatch['W'] = self.edgeMatch['N']
        self.edgeMatch['N'] = self.edgeMatch['E']
        self.edgeMatch['E'] = self.edgeMatch['S']
        self.edgeMatch['S'] = newSouthMatch
        return
    
    def rotateEmpty(self, emptyList):
        done = False
        while not done:
            numMatches = 0
            for dir in emptyList:
                if not self.edgeMatch[dir]:
                    numMatches += 1
            if numMatches != len(emptyList):
                self.rotateRight()
            else:
                done = True
        return

    def placeTile(self, dir, edge):
        edgeRev = edge.copy()
        edgeRev.reverse()
        while True:
            if self.edges[dir] == edge:
                return
            if self.edges[dir] == edgeRev:
                if dir in ['N','S']:
                    self.flipX()
                else:
                    self.flipY()
                return
            self.rotateLeft()

            
            


    def matchesEdge(self, otherEdge):
        other = otherEdge.copy()
        for key,val in self.edges.items():
            
            if val == other:
                #print('Other = {}'.format(other))
                #print('Val = {} is {} edge of id {}'.format(val, key, self.id))
                return key
        other.reverse()
        for key,val in self.edges.items():
            if val == other:
                #print('Reversed of {}'.format(otherEdge))
                #print('Other = {}'.format(other))
                #print('Val = {} is {} edge of id {}'.format(val, key, self.id))
                return key
        return False

def emptyBorders(i,j,picLength):
    emptyList = []
    if i == 0:
        emptyList.append('W')
    elif i == picLength - 1:
        emptyList.append('E')
    if j == 0:
        emptyList.append('N')
    elif j == picLength - 1:
        emptyList.append('S')
    return emptyList
with open("20/input.txt") as f:
	tiles = f.read().splitlines()

tileList = {}

for line in tiles:
    if line[:4] == 'Tile':
        id = int(line[5:-1])
        tileMap = []
    elif line != '':
        tileMap.append(line)
    else:
        newTile = Tile(id, tileMap)
        tileList[id] = newTile
newTile = Tile(id, tileMap)
tileList[id] = newTile
cornerTiles = {}
edgeTiles = {}
centerTiles = {}
#print(tileList)
ansA = 1
for id, workingTile in tileList.items():
    
    numZero = 0
    for edgePos, edge in workingTile.edges.items():
        numMatches = 0
        #print('Looking at {} edge of id {}'.format(edgePos, workingTile.id))
        #print(edge)
        hasMatch = False
        for id2, tile2 in tileList.items():
            if id == id2:
                continue
            otherPos = tile2.matchesEdge(edge)
            if otherPos:
                hasMatch = True
                numMatches += 1
                workingTile.edgeMatch[edgePos].append(tile2.id)
        
        if not hasMatch:
            numZero += 1
    if numZero == 2:
        cornerTiles[workingTile.id] = workingTile
        ansA *= workingTile.id
    elif numZero == 1:
        edgeTiles[workingTile.id] = workingTile
    else:
        centerTiles[workingTile.id] = workingTile

print(ansA)
print(len(tileList))
print(len(cornerTiles))
print(len(centerTiles))
print(len(edgeTiles))

if len(tileList) == 9:
    picLength = 3
else:
    picLength = 12
corners = [(0,0),(0,picLength-1),(picLength-1,0),(picLength-1,picLength-1)]

picture = np.zeros((picLength,picLength),dtype=np.int32)
print(tileList[1217].edgeMatch)
for i in range(picLength):
    for j in range(picLength):
        if (i,j) == (0,0):        
            id, tileToPlace = cornerTiles.popitem()
            picture[i,j] = tileToPlace.id
            print(tileToPlace.edgeMatch)
            emptyList = emptyBorders(i,j,picLength)
            tileToPlace.rotateEmpty(emptyList)
            print(tileToPlace.edgeMatch)
            continue
        if j > 0:
            prev_i = i
            prev_j = j-1
            dir = 'W'
            prevDir = 'E'
        else:
            prev_i = i-1
            prev_j = j
            dir = 'N'
            prevDir = 'S'
        prevTileId = picture[prev_i,prev_j]
        prevTile = tileList[prevTileId]
        edgeToMatch = prevTile.edges[prevDir]
        print(len(prevTile.edgeMatch[prevDir]))
        print(picture)
        print((i,j))
        print(prevTile.edgeMatch)
        idToMatch = prevTile.edgeMatch[prevDir][0]
        picture[i,j] = idToMatch
        tileList[idToMatch].placeTile(dir, edgeToMatch)


        
        


            
print(picture)
