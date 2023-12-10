import random
from itertools import chain, combinations

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

class Room():
    def __init__(self, name,descr):
        self.name = name
        self.doors = {}
        self.items = set()
        self.descript = descr
    
    def setDoors(self, doors):
        if len(self.doors) == 0:
            for door in doors:
                self.doors[door] = ''
    
    def getDoors(self):
        doors = []
        for door in self.doors:
            doors.append(door)
        return doors

    def setDest(self, door, room):
        self.doors[door] = room
    
    def unOpenedDoors(self):
        unopened = []
        for door in self.doors:
            if self.doors[door] == '':
                unopened.append(door)
        return unopened
    
    def addItems(self, items):
        for item in items:
            self.items.add(item)
    
    def getItem(self, item):
        if item in self.items:
            self.items.remove(item)
        else:
            print("Error item not found!")


def possibleMovement(outString):
    possibleDirections = []
    possibleItems = []
    i = 0
    #print(len(outString))
    while i < len(outString):
        line = outString[i]
        
        if len(line) > 0:
            if line == 'Doors here lead:':
                #print('Here!')
                i += 1
                line = outString[i]
                while len(line) > 0:
                    if line[0] == '-':
                        possibleDirections.append(line[2:])
                    i += 1
                    line = outString[i]
            if line == 'Items here:':
                while len(outString[i+1]) > 0:
                    line = outString[i+1]
                    possibleItems.append(line[2:])
                    i += 1
        i += 1
    return possibleDirections, possibleItems

def toASCII(input):
    ascii = []
    for c in input:
        ascii.append(ord(c))
    return ascii

def fromASCII(input):
    string = ''
    for c in input:
        string += chr(c)
    return string

def takeItem(item):
    return toASCII('take ' + item + '\n')

def dropItem(item):
    return toASCII('drop ' + item + '\n')

commands = {'north' : toASCII('north\n'), 'south' : toASCII('south\n'), 'west' : toASCII('west\n'), 'east' : toASCII('east\n') }
reverse = {'north' : 'south', 'south' : 'north', 'west' : 'east', 'east' : 'west'}
map = {}

def findRoom(curr,name,dir):
    path = {}
    if dir == '':
        prev = dir
    else:
        prev = reverse[dir]
    for door in map[curr].doors:
        if map[curr].doors[door] == name:
            #print("Found {} it is behind {} in {}. Check = {}".format(name, door, curr, map[curr].doors[door]))
            return [door]
        elif door != prev:
            path[door] = findRoom(map[curr].doors[door], name, door)
    #print(path)
    #print(curr)
    for door in path:
        if len(path[door]) > 0:
            a = [door]
            a.extend(path[door])
            #print(path[door])
            #print(a)
            return a
    return []

def powerset(iterable):
    s = list(iterable)
    return chain.from_iterable(combinations(s,r) for r in range(len(s)+1))


itemMap = {}
carriedItems = set()
history = []
historyRooms = []
location = ''
intcode = open('2019/25/input','r')
code = intcode.read()
intcode.close()
codeList = [ int(x) for x in code.split(',')]



computer = IntComputer(codeList.copy(), toPrint=0)
# output = computer.runProgram([])
# outString = fromASCII(output).splitlines()
# move, items = possibleMovement(outString)
# input = commands[random.choice(move)]
input = []
running = True
prevRoom = ""
prevMove = ""
while running:
    output = computer.runProgram(input)
    outString = fromASCII(output).splitlines()
    #print(fromASCII(output))
    if not outString[1] == "You can't go that way.":
        doors, items = possibleMovement(outString)
        roomName = outString[3][3:-3]
        descript = outString[4]
        location = roomName
        if roomName not in map:
            map[roomName] = Room(roomName,descript)
            map[roomName].setDoors(doors)
            map[roomName].addItems(items)
            if len(items) > 0:
                for item in items:
                    if item != "infinite loop" and item != "giant electromagnet" and item != "photons" and item != "molten lava" and item != "escape pod":
                        takeInput = takeItem(item)
                        output = computer.runProgram(takeInput)
                        map[roomName].getItem(item)
                        carriedItems.add(item)
                        #print(fromASCII(output))
        if roomName == "Pressure-Sensitive Floor":
            map[roomName].setDoors(['east'])
            #print(doors)
            #print(history[-3:])
            history.pop()
            #Moved to security checkpoint
            location = "Security Checkpoint"
            doors = map[location].getDoors()
        if len(prevRoom) > 0:
            map[prevRoom].setDest(prevMove,roomName)
            map[roomName].setDest(reverse[prevMove],prevRoom)

    else:
        print(prevRoom)
        print(prevMove)  
    
    possibleMoves = map[location].unOpenedDoors()
    if len(possibleMoves) == 0:
        if len(history) > 0:
            lastMove = history.pop()
            moveToDo = reverse[lastMove]
            
        else:
            running = False
            break
    else:
        moveToDo = random.choice(possibleMoves)
        history.append(moveToDo)
    input = commands[moveToDo]
    prevMove = moveToDo
    prevRoom = location
    # oldOutstring = outString
    # oldMove = fromASCII(input)

print(len(map))
for room in map:
    print("-------")
    print(room)
    print(map[room].descript)
    print(map[room].items)
    for door in map[room].doors:
        print("{} of {} is {}".format(door, room, map[room].doors[door]))
#print(itemMap)
#print(location)
#print(fromASCII(computer.runProgram(toASCII('inv\n'))))
#print(carriedItems)
#print(history)

path = findRoom(location, "Security Checkpoint",'')

#print(findRoom(location,"Security Checkpoint",''))

for move in path:
    input = commands[move]
    output = computer.runProgram(input)
    #print(fromASCII(output))
#print(fromASCII(computer.runProgram(toASCII('inv\n'))))
for item in carriedItems:
    input = dropItem(item)
    output = computer.runProgram(input)
    #print(fromASCII(output))

location = "Security Checkpoint"

path = findRoom(location, "Pressure-Sensitive Floor", '')

numItems = len(carriedItems)
itemsOnGround = list(carriedItems)
itemsCarried = []
#print(2**numItems)
for combination in powerset(carriedItems):
    #print(combination)
    for item in combination:
        #print(item)
        if item not in itemsCarried:
            input = takeItem(item)
            #print(input)
            computer.runProgram(input)
    for item in itemsCarried:
        if item not in combination:
            input = dropItem(item)
            computer.runProgram(input)
    itemsCarried = list(combination)
    #print(path[0])
    
    input = commands[path[0]]
    output = computer.runProgram(input)
    outString = fromASCII(output).splitlines()
    alertLine = outString[9]
    if "heavier" not in alertLine and "lighter" not in alertLine:
        print(fromASCII(output))
        break
