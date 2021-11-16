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


intcode = open('2019/23/input','r')
code = intcode.read()
intcode.close()
codeList = [ int(x) for x in code.split(',')]

numComp = 50
computers = {}
inputs = {}
for i in range(numComp):
    computers[i] = IntComputer(codeList.copy(), toPrint=0)
    computers[i].runProgram([i])
    inputs[i] = []
running = True
NAT = []
firstNAT = True
lastYNAT = -1
while running:
    allEmpty = True
    for i in range(numComp):
        if len(inputs[i]) == 0:
            inputs[i] = [-1]
        else:
            allEmpty = False
        output = computers[i].runProgram(inputs[i])
        inputs[i] = []
        j = 0
        while j < len(output):
            adress = output[j]
            if adress == 255:
                NAT = output[(j+1):(j+3)]
                if firstNAT:
                    print("The first package to {} has X {} and Y {}".format(adress, output[j+1], output[j+2]))
                    firstNAT = False
            else:
                #print("We have a package to {} containing {}".format(adress,output[(j+1):(j+3)]))
                inputs[adress].extend(output[(j+1):(j+3)])
            j += 3
    if allEmpty:
        inputs[0] = NAT
        if lastYNAT == NAT[1]:
            print("The Y value {} was delivered to 0 twice in a row.".format(lastYNAT))
            running = False
            break
        else:
            lastYNAT = NAT[1]


    

