import numpy as np

entries = np.genfromtxt("input.txt")
entries.sort()
for i in range(len(entries)):
	for j in range(i+1,len(entries)):
		ei = entries[i]
		ej = entries[j]
		if ei + ej == 2020:
			print('{} + {} = 2020, product = {}'.format(ei,ej,ei*ej))
		elif ei + ej > 2020:
			break
