import datetime

with open('2022/17/input') as f:
    lines = f.read().splitlines()
    #lines = [int(x) for x in lines] 

movement = lines[0]
length = len(movement)
movementIndex = 0

room = [[1,1,1,1,1,1,1], [0,0,0,0,0,0,0], [0,0,0,0,0,0,0], [0,0,0,0,0,0,0], [0,0,0,0,0,0,0], [0,0,0,0,0,0,0], [0,0,0,0,0,0,0], [0,0,0,0,0,0,0]]
currentMax = 0

def overlaps(rock, room):
    for x in range(0,len(rock)):
        for y in range(0,len(rock[0])):
            if rock[x][y] == 1 and room[x][y] == 1:
                return True
    return False


def merge(room, rock):
    for x in range(0,len(rock)):
        for y in range(0,len(rock[0])):
            if rock[x][y] == 1 or room[x][y] == 1:
                room[x][y] = 1


def newLine():
    l = [0,0,0,0,0,0,0]
    room.append(l)
listToSave = list()
prevCurMax = 0
repCand = False
startHeight = 0

for i in range(0,1000000000000):
    # Save i%5 and movementIndex%length
    newTuple = (i%5, movementIndex%length, currentMax - prevCurMax)
    if newTuple in listToSave and not repCand:
        startIndex = listToSave.index(newTuple)
        checkIndex = startIndex
        startHeight = currentMax
        periodLength = i - startIndex
        repCand = True
    listToSave.append(newTuple)
    if repCand:
        if listToSave[checkIndex] == newTuple:
            if checkIndex == startIndex + periodLength:
                noPattern = False
                break
            checkIndex += 1
        else:
            repCand = False
    prevCurMax = currentMax
    y = currentMax + 4
    falling = True

    if i%5 == 0:
        rock = [0,0,1,1,1,1,0]
        while falling:
            move = movement[movementIndex%length]
            if move == '<':
                if rock[0] != 1:
                    rock.pop(0)
                    rock.append(0)
                    if overlaps([rock], [room[y]]):
                        rock.pop()
                        rock.insert(0, 0)
            else:
                if rock[-1] != 1:
                    rock.pop()
                    rock.insert(0,0)
                    if overlaps([rock], [room[y]]):
                        rock.pop(0)
                        rock.append(0)
            if not overlaps([rock], [room[y-1]]):
                y -= 1
            else:
                merge([room[y]], [rock])
                if y > currentMax:
                    currentMax = y
                    newLine()
                falling = False

            movementIndex += 1
    
    if i%5 == 1:
        rock = [[0,0,0,1,0,0,0], [0,0,1,1,1,0,0], [0,0,0,1,0,0,0]]
        while falling:
            move = movement[movementIndex%length]
            if move == '<':
                if rock[1][0] != 1:
                    rock[0].pop(0)
                    rock[0].append(0)
                    rock[1].pop(0)
                    rock[1].append(0)
                    rock[2].pop(0)
                    rock[2].append(0)
                    if overlaps(rock, [room[y], room[y+1], room[y+2]]):
                        rock[0].pop()
                        rock[0].insert(0,0)
                        rock[1].pop()
                        rock[1].insert(0,0)
                        rock[2].pop()
                        rock[2].insert(0,0)
            else:
                if rock[1][-1] != 1:
                    rock[0].pop()
                    rock[0].insert(0,0)
                    rock[1].pop()
                    rock[1].insert(0,0)
                    rock[2].pop()
                    rock[2].insert(0,0)
                    if overlaps(rock, [room[y], room[y+1], room[y+2]]):
                        rock[0].pop(0)
                        rock[0].append(0)
                        rock[1].pop(0)
                        rock[1].append(0)
                        rock[2].pop(0)
                        rock[2].append(0)

            if not overlaps(rock, [room[y-1], room[y], room[y+1]]):
                y -= 1
            else:
                merge([room[y], room[y+1], room[y+2]], rock)
                if y+2 > currentMax:
                    currentMax = y+2
                    newLine()
                    newLine()
                    newLine()
                falling = False

            movementIndex += 1

    if i%5 == 2:
        rock = [[0,0,1,1,1,0,0], [0,0,0,0,1,0,0], [0,0,0,0,1,0,0]]
        while falling:
            move = movement[movementIndex%length]
            if move == '<':
                if rock[0][0] != 1:
                    rock[0].pop(0)
                    rock[0].append(0)
                    rock[1].pop(0)
                    rock[1].append(0)
                    rock[2].pop(0)
                    rock[2].append(0)
                    if overlaps(rock, [room[y], room[y+1], room[y+2]]):
                        rock[0].pop()
                        rock[0].insert(0,0)
                        rock[1].pop()
                        rock[1].insert(0,0)
                        rock[2].pop()
                        rock[2].insert(0,0)
            else:
                if rock[0][-1] != 1:
                    rock[0].pop()
                    rock[0].insert(0,0)
                    rock[1].pop()
                    rock[1].insert(0,0)
                    rock[2].pop()
                    rock[2].insert(0,0)
                    if overlaps(rock, [room[y], room[y+1], room[y+2]]):
                        rock[0].pop(0)
                        rock[0].append(0)
                        rock[1].pop(0)
                        rock[1].append(0)
                        rock[2].pop(0)
                        rock[2].append(0)

            if not overlaps(rock, [room[y-1], room[y], room[y+1]]):
                y -= 1
            else:
                merge([room[y], room[y+1], room[y+2]], rock)
                if y+2 > currentMax:
                    currentMax = y+2
                    newLine()
                    newLine()
                    newLine()
                falling = False

            movementIndex += 1
    
    if i%5 == 3:
        rock = [[0,0,1,0,0,0,0], [0,0,1,0,0,0,0], [0,0,1,0,0,0,0], [0,0,1,0,0,0,0]]
        while falling:
            move = movement[movementIndex%length]
            if move == '<':
                if rock[2][0] != 1:
                    rock[0].pop(0)
                    rock[0].append(0)
                    rock[1].pop(0)
                    rock[1].append(0)
                    rock[2].pop(0)
                    rock[2].append(0)
                    rock[3].pop(0)
                    rock[3].append(0)
                    if overlaps(rock, [room[y], room[y+1], room[y+2], room[y+3]]):
                        rock[0].pop()
                        rock[0].insert(0,0)
                        rock[1].pop()
                        rock[1].insert(0,0)
                        rock[2].pop()
                        rock[2].insert(0,0)
                        rock[3].pop()
                        rock[3].insert(0,0)
            else:
                if rock[0][-1] != 1:
                    rock[0].pop()
                    rock[0].insert(0,0)
                    rock[1].pop()
                    rock[1].insert(0,0)
                    rock[2].pop()
                    rock[2].insert(0,0)
                    rock[3].pop()
                    rock[3].insert(0,0)
                    if overlaps(rock, [room[y], room[y+1], room[y+2], room[y+3]]):
                        rock[0].pop(0)
                        rock[0].append(0)
                        rock[1].pop(0)
                        rock[1].append(0)
                        rock[2].pop(0)
                        rock[2].append(0)
                        rock[3].pop(0)
                        rock[3].append(0)

            if not overlaps(rock, [room[y-1], room[y], room[y+1], room[y+2]]):
                y -= 1
            else:
                merge([room[y], room[y+1], room[y+2], room[y+3]], rock)
                if y+3 > currentMax:
                    currentMax = y+3
                    newLine()
                    newLine()
                    newLine()
                    newLine()
                falling = False

            movementIndex += 1
    
    if i%5 == 4:
        rock = [[0,0,1,1,0,0,0], [0,0,1,1,0,0,0]]
        while falling:
            move = movement[movementIndex%length]
            if move == '<':
                if rock[0][0] != 1:
                    rock[0].pop(0)
                    rock[0].append(0)
                    rock[1].pop(0)
                    rock[1].append(0)
                    if overlaps(rock, [room[y], room[y+1]]):
                        rock[0].pop()
                        rock[0].insert(0,0)
                        rock[1].pop()
                        rock[1].insert(0,0)
            else:
                if rock[0][-1] != 1:
                    rock[0].pop()
                    rock[0].insert(0,0)
                    rock[1].pop()
                    rock[1].insert(0,0)
                    if overlaps(rock, [room[y], room[y+1]]):
                        rock[0].pop(0)
                        rock[0].append(0)
                        rock[1].pop(0)
                        rock[1].append(0)

            if not overlaps(rock, [room[y-1], room[y]]):
                y -= 1
            else:
                merge([room[y], room[y+1]], rock)
                if y+1 > currentMax:
                    currentMax = y+1
                    newLine()
                    newLine()
                falling = False

            movementIndex += 1

row1 = room[129]
row2 = room[130]
row3 = room[131]
diffList = list()
for i in range(129, len(room)-2):
    if room[i] == row1 and room[i+1] == row2 and room[i+2] == row3:
        print(i)
        diffList.append(i)
for i in range(0,len(diffList)-1):
    print(diffList[i+1]-diffList[i])
heightInPattern = 0
for i in range(0,periodLength):
    heightInPattern += listToSave[startIndex+i][2]
print(currentMax)
print(listToSave)
print(startIndex, periodLength, startHeight)
print(currentMax, startHeight+heightInPattern)
height = int((1000000000000-startIndex)/periodLength - 1)*heightInPattern + startHeight
for i in range(0, (1000000000000 - startIndex) % periodLength):
    height += listToSave[startIndex+1+i][2]
print(height)
