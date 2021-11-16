class IntComputer():
	def __init__(self, codeList, toPrint = 1):
		self.codeList = codeList
		self.length = len(codeList)
		self.inputs = []
		self.head = 0
		self.relBase = 0
		self.done = False
		self.numInstructions = 0
		self.toPrint = toPrint
		
	def getVal(self, mode,pos):
		if pos < 0:
			print('Negative position, pos: {}'.format(pos))
		return self.codeList[self.getPos(mode,pos)]
	
	def getPos(self, mode, pos):
		if mode == 0:
			pos = self.codeList[pos]
		elif mode == 1:
			pos = pos
		elif mode == 2:
			 pos = self.relBase + self.codeList[pos]
		else:
			print('Wrong mode, encountered mode: {}, pos: {}'.format(mode,pos))
			self.runing = False
		
		if pos >= self.length:
			self.codeList.extend([0]*(pos - self.length + 1))
			self.length = len(self.codeList)
		
		return pos
	
	def getInstruction(self, head):
		instruction = self.codeList[head]
		opCode = instruction % 100
		instruction = int(instruction / 100)
		mode1 = instruction % 10
		instruction = int(instruction / 10)
		mode2 = instruction % 10
		instruction = int(instruction / 10)
		mode3 = instruction % 10
		return (opCode, mode1, mode2, mode3)
		
	def runProgram(self, inputs):
		head = self.head
		#codeList = self.codeList
		self.inputs.extend(inputs)
		inputs = self.inputs
		outputs = []
		self.runing = True
		while self.runing:
			(opCode, mode1, mode2, mode3) = self.getInstruction(head)
			self.numInstructions += 1
			if opCode == 1:
				val1 = self.getVal(mode1,head+1)
				val2 = self.getVal(mode2,head+2)
				pos3 = self.getPos(mode3,head+3)
				self.codeList[pos3] = val1 + val2
				head += 4
			elif opCode == 2:
				val1 = self.getVal(mode1,head+1)
				val2 = self.getVal(mode2,head+2)
				pos3 = self.getPos(mode3,head+3)
				self.codeList[pos3] = val1 * val2
				head += 4
			elif opCode == 3:
				if inputs:
					val1 = inputs.pop(0)
					if self.toPrint: print('Input : {}'.format(val1))
					pos1 = self.getPos(mode1,head+1)
					self.codeList[pos1] = val1
					head += 2
				else:
					if self.toPrint: print('Waiting for input')
					self.runing = False
					break
			elif opCode == 4:
				val1 = self.getVal(mode1,head+1)
				if self.toPrint: print('Output : {}'.format(val1))
				outputs.append(val1)
				head += 2
			elif opCode == 5:
				val1 = self.getVal(mode1,head+1)
				val2 = self.getVal(mode2,head+2)
				if val1 == 0:
					head += 3
				else:
					head = val2
			elif opCode == 6:
				val1 = self.getVal(mode1,head+1)
				val2 = self.getVal(mode2,head+2)
				if val1 != 0:
					head += 3
				else:
					head = val2
			elif opCode == 7:
				val1 = self.getVal(mode1,head+1)
				val2 = self.getVal(mode2,head+2)
				pos3 = self.getPos(mode3,head+3)
				if val1 < val2:
					toStore = 1
				else:
					toStore = 0
				self.codeList[pos3] = toStore
				head += 4
			elif opCode == 8:
				val1 = self.getVal(mode1,head+1)
				val2 = self.getVal(mode2,head+2)
				pos3 = self.getPos(mode3,head+3)
				if val1 == val2:
					toStore = 1
				else:
					toStore = 0
				self.codeList[pos3] = toStore
				head += 4
			elif opCode == 9:
				val1 = self.getVal(mode1,head+1)
				self.relBase += val1
				head += 2
			elif opCode == 99:
				self.runing = False
				self.done = True
				break
			else:
				print('Error!, head = {}'.format(head))
		self.head = head
		return outputs

def canFitShip(x,y):
    intComp = IntComputer(codeList.copy(), toPrint = 0)
    result1 = intComp.runProgram([x+shipSize-1,y])[0]
    print("Tested ({},{}) got {}".format(x+shipSize, y, result1))
    intComp = IntComputer(codeList.copy(), toPrint = 0)
    result2 = intComp.runProgram([x,y+shipSize-1])[0]
    print("Tested ({},{}) got {}".format(x, y+shipSize, result2))
    return result1, result2


intcode = open('2019/19/input','r')
code = intcode.read()
intcode.close()
codeList = [ int(x) for x in code.split(',')]

intComp = IntComputer(codeList.copy(), toPrint = 0)
results = []
maxX = 50
maxY = 50
goodPoints = []
badPoints = []
shipSize = 100
for x in range(maxX):
    for y in range(maxY):
        intComp = IntComputer(codeList.copy(), toPrint = 0)
        res1 = intComp.runProgram([x,y])
        if res1[0] == 1:
            goodPoints.append((x,y))
        else:
            badPoints.append((x,y))
        results.extend(res1)
print((goodPoints))
print("Answer part A : {}".format(sum(results)))

x = 0
y = 0
fitShip = False
start_row = 0
updateStart = True
while not fitShip:
    print("Testing ({},{})".format(x,y))
    res1, res2 = canFitShip(x,y)
    if res1 == 0:
        y += 1
    elif res2 == 0:
        x += 1
    else:
        fitShip = True

    #print(len(badPoints))

    #print(len(goodPoints))
    # if x > 10 and y > 20:
    #     fitShip = True

print("Answer part B = 10000 * {} + {} = {}".format(x,y,10000*x + y))

x_ans = x
y_ans = y

for y in range(maxY):
    for x in range(maxX):
        if x == x_ans and y == y_ans:
            print('O',end='')
        elif (x,y) in goodPoints:
            print('#',end='')
        else:
            print('.',end='')
    print('')