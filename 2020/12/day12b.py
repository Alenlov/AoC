
class Ship:
	waypointX = 10
	waypointY = 1
	posX = 0
	posY = 0
	

	def processInstruction(self, instruction):
		letter = instruction[0]
		amount = int(instruction[1:])
		if letter == 'E':
			self.waypointX += amount
		elif letter == 'W':
			self.waypointX -= amount
		elif letter == 'N':
			self.waypointY += amount
		elif letter == 'S':
			self.waypointY -= amount
		elif letter == 'F':
			self.posX += amount*self.waypointX
			self.posY += amount*self.waypointY
		elif letter == 'L':
			turns = int(amount/90)
			for i in range(turns):
				waypointX = -self.waypointY
				self.waypointY = self.waypointX
				self.waypointX = waypointX
		elif letter == 'R':
			turns = int(amount/90)
			for i in range(turns):
				waypointX = self.waypointY
				self.waypointY = - self.waypointX
				self.waypointX = waypointX



with open("input.txt") as f:
	instructions = f.read().splitlines()

ship = Ship()

for instruction in instructions:
	ship.processInstruction(instruction)

ansA = abs(ship.posX) + abs(ship.posY)
print(ansA)