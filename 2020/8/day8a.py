



def run(instructions, visited, indX, acc, hasChanged):
	print('start')
	runing = True
	while runing:
		if indX == len(instructions)-1:
			print(acc)
			return acc
		if visited[indX] == 1:
			print('2')
			return 0
		visited[indX] = 1
		[inst, val] = instructions[indX].split(' ')
		if inst == "nop":
			if not hasChanged:
				run(instructions, visited.copy(), indX + int(val), acc, 1)
			indX += 1
		elif inst == "acc":
			acc += int(val)
			indX += 1
		elif inst == "jmp":
			if not hasChanged:
				run(instructions, visited.copy(), indX+1, acc, 1)
			indX += int(val)


with open("input.txt") as f:
	instructions = f.read().splitlines()

visited = [0]*len(instructions)
indX = 0
acc = 0
run(instructions, visited, indX, acc, 0)

print(acc)