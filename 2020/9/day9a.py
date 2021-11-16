import numpy as np

def sumOf(tar, vals):
	for i in range(len(vals)):

		for j in range(i+1,len(vals)):
			if vals[i] + vals[j] == tar:
				return True

	return False


code = np.genfromtxt("input.txt")
indx = 25
while sumOf(code[indx], code[indx-25:indx]):
	indx += 1

ansA = code[indx]

start = 0
end = 1
val = code[start] + code[end]
while val != ansA:
	if val < ansA:
		end += 1
		val += code[end]
	elif val > ansA:
		start += 1
		val -= code[start-1]
ansB = np.min(code[start:end+1]) + np.max(code[start:end+1])

print(ansA)
print(ansB)
