def energy(crabs, val):
    totEnergy = 0
    for c in crabs:
        totEnergy += abs(c - val)
    return totEnergy

def energyB(crabs, val):
    totEnergy = 0
    for c in crabs:
        diff = abs(c - val)
        totEnergy += int(diff * (diff+1) / 2)
    return totEnergy

crabs = [int(x) for x in open('2021/7/input').read().strip().split(',')]

minVal = min(crabs)
maxVal = max(crabs)
minEnergy = maxVal * len(crabs)
minEnergyB = maxVal * (maxVal+1) * len(crabs)
for mean in range(minVal,maxVal):
    energyAtMean = energy(crabs, mean)
    if energyAtMean < minEnergy:
        minEnergy = energyAtMean
    energyAtMeanB = energyB(crabs, mean)
    if energyAtMeanB < minEnergyB:
        minEnergyB = energyAtMeanB

print("Answer part A: The minium energy is {}".format(minEnergy))
print("Answer part B: The minium energy is {}".format(minEnergyB))