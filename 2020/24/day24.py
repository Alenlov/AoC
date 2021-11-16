with open("24/input.txt") as f:
	tilesToFlip = f.read().splitlines()

tileDict = {}

moveDict = {'e' : (1,1,0), 'se' : (1,0,-1), 'sw' : (0,-1,-1), 'w' : (-1,-1,0), 'nw' : (-1,0,1), 'ne' : (0,1,1)} 

for direction in tilesToFlip:
    pos = [0,0,0]
    while direction:
        if direction.startswith('e'):
            direction = direction[1:]
            dir = 'e'
        elif direction.startswith('se'):
            direction = direction[2:]
            dir = 'se'
        elif direction.startswith('sw'):
            direction = direction[2:]
            dir = 'sw'
        elif direction.startswith('w'):
            direction = direction[1:]
            dir = 'w'
        elif direction.startswith('nw'):
            direction = direction[2:]
            dir = 'nw'
        elif direction.startswith('ne'):
            direction = direction[2:]
            dir = 'ne'
        move = moveDict[dir]
        pos[0] = pos[0] + move[0]
        pos[1] = pos[1] + move[1]
        pos[2] = pos[2] + move[2]
    pos = tuple(pos)
    if pos in tileDict:
        tileDict.pop(pos)
    else:
        tileDict[pos] = True
print('Answer part A = {}'.format(len(tileDict)))

for i in range(100):
    tilesToCheckDict = {}
    for key, _ in tileDict.items():
        if key not in tilesToCheckDict:
            tilesToCheckDict[key] = True
        for dir, move in moveDict.items():
            pos = list(key)
            pos[0] = pos[0] + move[0]
            pos[1] = pos[1] + move[1]
            pos[2] = pos[2] + move[2]
            pos = tuple(pos)
            if pos not in tilesToCheckDict:
                tilesToCheckDict[pos] = True
    newTileDict = {}
    for key, _ in tilesToCheckDict.items():
        numNgbr = 0
        for dir, move in moveDict.items():
            pos = list(key)
            pos[0] = pos[0] + move[0]
            pos[1] = pos[1] + move[1]
            pos[2] = pos[2] + move[2]
            pos = tuple(pos)
            if pos in tileDict:
                numNgbr += 1
        if key in tileDict and 1<=numNgbr<=2:
            newTileDict[key] = True
        elif key not in tileDict and numNgbr == 2:
            newTileDict[key] = True
    tileDict = newTileDict

print('Answer part B = {}'.format(len(tileDict)))