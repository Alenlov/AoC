
class Ship:
	posX = 0
	posY = 0
	directions = {0 : (1,0), 1 : (0, 1), 2 : (-1,0), 3: (0,-1)}
	direction = 0

	def processInstruction(self, instruction):
		letter = instruction[0]
		amount = int(instruction[1:])
		if letter == 'E':
			self.posX += amount
		elif letter == 'W':
			self.posX -= amount
		elif letter == 'N':
			self.posY += amount
		elif letter == 'S':
			self.posY -= amount
		elif letter == 'F':
			direction = self.directions[self.direction]
			self.posX += amount*direction[0]
			self.posY += amount*direction[1]
		elif letter == 'L':
			turns = amount/90
			self.direction = (self.direction + turns) % 4
		elif letter == 'R':
			turns = amount/90
			self.direction = (self.direction - turns) % 4



with open("input.txt") as f:
	instructions = f.read().splitlines()

ship = Ship()

for instruction in instructions:
	ship.processInstruction(instruction)

ansA = abs(ship.posX) + abs(ship.posY)
print(ansA)