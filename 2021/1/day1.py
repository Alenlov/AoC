import numpy as np

depths = np.genfromtxt('2021/1/input',dtype='int')
print("Answer Part A: the number of increases is {}".format(np.sum( (np.diff(depths)>0))))

depths3 = np.zeros(len(depths)-2)
print(depths[0:3])
for i in range(len(depths3)):
    depths3[i] = np.sum(depths[i:i+3])

print("Answer Part B: the number of increases is {}".format(np.sum( (np.diff(depths3)>0))))