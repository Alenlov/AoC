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

with open("14/input.txt") as f:
	initCode = f.read().splitlines()

print(int2bin(256))

memory = {}
activeMask = ''
for instruction in initCode:
    [code, val] = instruction.split(' = ')
    if code == 'mask':
        activeMask = val
    else:
        memSpot = code[4:-1]
        valbin = int2bin(int(val))
        toSave = activeMask
        for i in range(len(activeMask)):
            if activeMask[i] == 'X':
                toSave = toSave[:i] + valbin[i] + toSave[i+1:]
        memory[memSpot] = toSave

sumOfMem = 0
for _,val in memory.items():
    sumOfMem += bin2int(val)


print(sumOfMem)

