class ALU:

    def __init__(self, instructions):
        self.program = instructions
        self.memory = {'w':0,'x':0,'y':0,'z':0}
        self.memOrder = ['z']
    
    def setMemory(self, memory):
        for place in memory:
            self.memory[place] = memory[place]

    def runProgram(self, inputTuple):
        inputs = [inputTuple[0]]
        self.memory['z'] = inputTuple[1]
        self.memory['x'] = 0
        self.memory['y'] = 0
        for line in self.program:
            line = line.split(" ")
            inst = line[0]
            if inst == "inp":
                if len(inputs) == 0:
                    return self.memory
                else:
                    self.memory[line[1]] = inputs.pop(0)
            else:
                if line[2] in self.memory:
                    val = self.memory[line[2]]
                else:
                    val = int(line[2])
                if inst == "add":
                    self.memory[line[1]] += val
                elif inst == "mul":
                    self.memory[line[1]] *= val
                elif inst == "div":
                    if val == 0:
                        print("error in div")
                        return None
                    self.memory[line[1]] //= val
                elif inst == "mod":
                    if (val <= 0) or (self.memory[line[1]] < 0):
                        print("error in mod")
                        return None
                    self.memory[line[1]] %= val
                elif inst == "eql":
                    if self.memory[line[1]] == val:
                        self.memory[line[1]] = 1
                    else:
                        self.memory[line[1]] = 0
        
        return self.memory[self.memOrder[0]]

instructions = open('2021/24/input').read().splitlines()
instructionPerNum = []
instPart = []
for line in instructions:
    if line[:3] == 'inp':
        if len(instPart) > 0:
            instructionPerNum.append(instPart)
        instPart = [line]
    else:
        instPart.append(line)
instructionPerNum.append(instPart)
xaddvals = []
for inst in instructionPerNum:
    xaddvals.append(int(inst[5][6:]))
memOrder = ['y','z']
numbers = [1,2,3,4,5,6,7,8,9]
numLen = 14
alus = []
memDicts = []
prevMemories = set()
prevMemories.add(0)
for i in range(numLen):
    memDicts.append({})
    alus.append(ALU(instructionPerNum[i]))
    newPrevMem = set()
    val = xaddvals[i]
    
    for mems in prevMemories:
        if val < 0:
            test = (mems % 26) + val
            if 1 <= test <= 9:
                numSet = [test]
            else:
                numSet = []
        else:
            numSet = numbers
        for n in numSet:
            
            inputTuple = (n, mems)
            output = alus[i].runProgram(inputTuple)
            memDicts[i][(n,mems)] = output
            newPrevMem.add(output)
    prevMemories = newPrevMem
revMemdict = []
for i in range(numLen):
    revMemdict.append({})
toFind = {0}
for i in range(numLen):
    j = numLen - i - 1
    newToFind = set()
    for outVal in toFind:
        for key in memDicts[j]:
            if memDicts[j][key] == outVal:
                if key[1] not in revMemdict[j]:
                    revMemdict[j][key[1]] = []
                revMemdict[j][key[1]].append((key[0],outVal))
                newToFind.add(key[1])
    toFind = newToFind
bestVal = []
inVal = 0
for i in range(numLen):
    possible = []
    for key in revMemdict[i]:
        if key == inVal:
            possible.extend(revMemdict[i][key])
    maxVal = 0
    newIn = None
    for pos in possible:
        if pos[0] > maxVal:
            newIn = pos[1]
            maxVal = pos[0]
    bestVal.append(maxVal)
    inVal = newIn
ansA = ""
for val in bestVal:
    ansA += str(val)

worstVal = []
inVal = 0
for i in range(numLen):
    possible = []
    for key in revMemdict[i]:
        if key == inVal:
            possible.extend(revMemdict[i][key])
    minVal = 10
    newIn = None
    for pos in possible:
        if pos[0] < minVal:
            newIn = pos[1]
            minVal = pos[0]
    worstVal.append(minVal)
    inVal = newIn
ansB = ""
for val in worstVal:
    ansB += str(val)

print("Answer part A: the highest value is {}".format(ansA))
print("Answer part B: the smallest value is {}".format(ansB))




