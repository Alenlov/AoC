with open("input.txt") as f:
	groups = f.read().split('\n\n')

val = 0
for group in groups:
	group = group.replace('\n', '')
	val += len(set(group))
print(val)