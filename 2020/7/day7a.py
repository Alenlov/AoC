class ColorBag():
	def __init__(self, name):
		self.name = name
		self.canBring = 0
		self.contains = {}
		self.containedIn = []

def getColorBag(bagDict, name):
	if name not in bagDict:
		bagDict[name] = ColorBag(name)
	return bagDict[name]

def bringable(bagList):
	containable = set()
	for bag in bagList:
		if bag.canBring == 1:
			containable.add(bag)
		if len(bag.containedIn) != 0:
			containable = containable.union(bringable(bag.containedIn))
			#print(len(containable))
	return containable

with open("7/input.txt") as f:
	rules = f.read().splitlines()


bagDict = {}
for rule in rules:
	[outer, inners] = rule.split(' contain ')
	[outerName, _] = outer.split(' bag')
	outerBag = getColorBag(bagDict, outerName)
	outerBag.canBring = 1
	inners = inners.split(', ')
	for inner in inners:
		indX = inner.find(' ')
		num = inner[:indX]
		if num == 'no':
			continue
		num = int(num)
		[innerName,_] = inner[(indX+1):].split(' bag')
		innerBag = getColorBag(bagDict, innerName)
		innerBag.containedIn.append(outerBag)
		if innerName in outerBag.contains:
			print('oj oj')
		outerBag.contains[innerBag] = num

ourBag = 'shiny gold'
bags = bringable(bagDict[ourBag].containedIn)
print(len(bags))




	