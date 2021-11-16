with open("input.txt") as f:
	tree_map = f.read().splitlines()


toWrap = len(tree_map[0])
toEnd = len(tree_map)


movers = [[1,1],[3,1],[5,1],[7,1],[1,2]]
prodTrees = 1

for moves in movers:
	posX = 0
	posY = 0

	movX = moves[0]
	movY = moves[1]

	moving = True

	numTrees = 0

	while moving:
		posX = (posX + movX) % toWrap
		posY = posY + movY
		print(posX, posY)
		if tree_map[posY][posX] == '#':
			numTrees += 1
		if posY + movY >= toEnd:
			break

	prodTrees *= numTrees

print(prodTrees)