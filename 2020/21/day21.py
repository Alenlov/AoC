with open("21/input.txt") as f:
	foodList = f.read().splitlines()

allDict = {}

for food in foodList:
    food = food.replace('(','').replace(',','').replace(')','')
    [ingredients, allergens] = food.split(' contains ')
    ingList = ingredients.split(' ')
    allList = allergens.split(' ')
    for allergen in allList:
        possibleFood = set(ingList)
        if allergen not in allDict:
            allDict[allergen] = possibleFood
        prevSet = allDict[allergen]
        newSet = set.intersection(prevSet, possibleFood)
        allDict[allergen] = newSet
foodWithAllergens = set()
for allergen, possibleFood in allDict.items():
    print('Allergen {} can be in {}'.format(allergen,possibleFood))
    foodWithAllergens = set.union(foodWithAllergens, possibleFood)

numSafeIngredients = 0
for food in foodList:
    food = food.replace('(','').replace(',','').replace(')','')
    [ingredients, allergens] = food.split(' contains ')
    ingList = ingredients.split(' ')
    for ingredient in ingList:
        if ingredient not in foodWithAllergens:
            numSafeIngredients += 1

print('Number of safe ingredients = {}'.format(numSafeIngredients))
figuredOutAllergens = {}
while allDict:
    for allergen, possibleFood in allDict.items():
        if len(possibleFood) == 1:
            figuredOutAllergens[allergen] = possibleFood
            for allergen2, possibleFood2 in allDict.items():
                if allergen == allergen2:
                    continue
                newPossibleFood = possibleFood2 - possibleFood
                allDict[allergen2] = newPossibleFood
    for allergen, possibleFood in figuredOutAllergens.items():
        if allergen in allDict:
            allDict.pop(allergen)

for allergen, possibleFood in figuredOutAllergens.items():
    print('Allergen {} can be in {}'.format(allergen,possibleFood))
    foodWithAllergens = set.union(foodWithAllergens, possibleFood)

ansString = ''
while figuredOutAllergens:
    smallestAll = None
    for allergen, food in figuredOutAllergens.items():
        if not smallestAll:
            smallestAll = allergen
        elif allergen < smallestAll:
            smallestAll = allergen
    foodSet = figuredOutAllergens.pop(smallestAll)
    ansString = ansString + foodSet.pop() + ','
print(ansString[:-1])

