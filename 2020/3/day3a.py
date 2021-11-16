with open("input.txt") as f:
	tree_map = f.read().splitlines()


toWrap = len(tree_map[0])
toEnd = len(tree_map)

posX = 0
posY = 0

movX = 3
movY = 1

print(toWrap, toEnd)

moving = True

numTrees = 0

while moving:
	posX = (posX + movX) % toWrap
	posY = posY + movY
	print(posX, posY)
	if tree_map[posY][posX] == '#':
		numTrees += 1
	if posY == toEnd - 1:
		break

print(numTrees)