import numpy as np

entries = np.genfromtxt("input.txt")
entries.sort()
for i in range(len(entries)):
	ei = entries[i]
	for j in range(i+1,len(entries)):
		ej = entries[j]
		if ei + ej > 2020:
			break
		for k in range(j+1, len(entries)):
			ek = entries[k]
			if ei + ej + ek == 2020:
				print('{0} + {1} + {2} = 2020 and {0} * {1} * {2} = {3}'.format(ei,ej,ek,ei*ej*ek))
				exit()
			elif ei + ej + ek > 2020:
				break
