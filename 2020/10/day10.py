import numpy as np

def comb(val):
	if val == 1:
		return 1
	elif val == 2:
		return 2
	elif val == 3:
		return 4
	else:
		return comb(val-1) + comb(val-2) + comb(val-3)



adapters = np.genfromtxt("input.txt")

adapters.sort()
adapters = np.insert(adapters,0,0)
adapters = np.append(adapters,adapters[-1]+3)

adapterDiff = np.diff(adapters)

ansA = (np.sum(adapterDiff == 1))*(np.sum(adapterDiff==3))

numOnes = []
numberInRow = 0
for i in range(len(adapterDiff)):
	if adapterDiff[i] == 1:
		numberInRow += 1
	elif adapterDiff[i] == 3 and numberInRow != 0:
		numOnes.append(numberInRow)
		numberInRow = 0
numOnes = np.array(numOnes)
maxInRow = np.max(numOnes)
ansB = 1
for i in range(maxInRow):
	ansB *= comb(i+1)**(np.sum(numOnes == i+1))



print(ansA)
print(ansB)
