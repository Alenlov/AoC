def int2bin(val):
    out = []
    for i in range(36):
        if 2**(35-i) <= val:
            out.append('1')
            val -= 2**(35-i)
        else:
            out.append('0')
    return out

def bin2int(val):
    out = 0
    for i in range(36):
        out += int(val[35-i])*2**i
    return out

def writeMemSpots(memSpot):
    outList = []
    firstX = memSpot.find('X')
    if firstX == -1:
        outList.append(memSpot)
        return outList
    listWith1 = writeMemSpots(memSpot[:firstX] + '1' + memSpot[firstX+1:])
    listWith0 = writeMemSpots(memSpot[:firstX] + '0' + memSpot[firstX+1:])
    outList.extend(listWith1)
    outList.extend(listWith0)
    return outList

with open("14/input.txt") as f:
	initCode = f.read().splitlines()


memory = {}
activeMask = ''
for instruction in initCode:
    [code, val] = instruction.split(' = ')
    if code == 'mask':
        activeMask = val
    else:
        memSpot = code[4:-1]
        valbin = int2bin(int(memSpot))
        toSave = activeMask
        for i in range(len(activeMask)):
            if activeMask[i] == '0':
                toSave = toSave[:i] + valbin[i] + toSave[i+1:]
        memSpotList = writeMemSpots(toSave)
        for memSpot in memSpotList:
            memory[memSpot] = int(val)

sumOfMem = 0
for _,val in memory.items():
    sumOfMem += val


print(sumOfMem)

