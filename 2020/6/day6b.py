import numpy as np
with open("input.txt") as f:
	groups = f.read().split('\n\n')

val = 0
for group in groups:
	persons = group.splitlines()
	yesSet = set('abcdefghijklmnopqrstuvwxyz')
	for person in persons:
		yesSet = set.intersection(yesSet, set(person))
	val += len(yesSet)

print(val)
	