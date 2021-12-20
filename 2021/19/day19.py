import math

class Scanner:
    def __init__(self, id):
        self.id = id
        self.beacons = []
        self.transformations = {}

    def calculateDistances(self):
        self.distances = []
        for i in range(len(self.beacons)):
            beaconDistances = []
            for j in range(len(self.beacons)):
                totDist = 0
                for k in range(len(self.beacons[i])):
                    totDist += abs( self.beacons[i][k] - self.beacons[j][k] )
                beaconDistances.append(totDist)
            self.distances.append(beaconDistances)

    def overlapping(self, other):
        for i in range(len(self.distances)):
            for j in range(len(other.distances)):
                same = {}
                for k in range(len(self.distances[i])):
                    dist = self.distances[i][k]
                    if dist > 0 and dist in other.distances[j]:
                        testInd = []
                        for l in range(len(other.distances[j])):
                            if other.distances[j][l] == dist:
                                testInd.append(l)
                        indices = testInd.copy()
                        for ind in testInd:
                            diff1 = []
                            diff2 = []
                            for l in range(len(self.beacons[i])):
                                diff1.append(abs(self.beacons[i][l] - self.beacons[k][l]))
                                diff2.append(abs(other.beacons[j][l] - other.beacons[ind][l]))
                            for d in diff1:
                                if d not in diff2:
                                    if ind in indices:
                                        indices.remove(ind)
                        if len(indices) > 0:
                            same[k] = indices
                if len(same) >= 11:
                    same[i] = [j]
                    # Twelve overlapping
                    return same
        return None

    def combineScanners(self, other):
        self.calculateDistances()
        same = self.overlapping(other)
        s1 = None
        s2 = None
        t1 = None
        t2 = None
        for s in same:
            t = same[s]
            if len(t) == 1:
                if not s1:
                    s1 = s
                    t1 = t[0]
                elif not s2:
                    s2 = s
                    t2 = t[0]
        diff1 = []
        diff2 = []
        for i in range(len(self.beacons[s1])):
            diff1.append( self.beacons[s1][i] - self.beacons[s2][i] )
            diff2.append( other.beacons[t1][i] - other.beacons[t2][i])
        
        transformMap = {}

        for i in range(len(diff1)):
            d1 = diff1[i]
            if d1 in diff2:
                transformMap[i] = ('+', diff2.index(d1))
            elif -d1 in diff2:
                transformMap[i] = ('-', diff2.index(-d1))
            else:
                print("Problem!")

        transformVector = {}
        for i in transformMap:
            s,v = transformMap[i]
            if s == '+':
                transformVector[i] = self.beacons[s1][i] - other.beacons[t1][v]
            elif s == '-':
                transformVector[i] = self.beacons[s1][i] + other.beacons[t1][v]
        numFailed = 0
        for t in same:
            for o in same[t]:
                newBeacon = [0]*3
                for i in transformMap:
                    s,v = transformMap[i]
                    if s == '+':
                        newBeacon[i] = other.beacons[o][v] + transformVector[i]
                    elif s == '-':
                        newBeacon[i] = -other.beacons[o][v] + transformVector[i]
                newBeacon = tuple(newBeacon)
                if newBeacon != self.beacons[t]:
                    numFailed += 1
        if numFailed == 0:
            self.transformations[other.id] = (transformMap,transformVector)
        # for beacon in other.beacons:
        #     newBeacon = [0]*3
        #     for i in transformMap:
        #         s,v = transformMap[i]
        #         if s == '+':
        #             newBeacon[i] = beacon[v] + transformVector[i]
        #         elif s == '-':
        #             newBeacon[i] = -beacon[v] + transformVector[i]
        #     newBeacon = tuple(newBeacon)
        #     if newBeacon not in self.beacons:
        #         self.beacons.append(newBeacon)

    def addBeacon(self, relCords):
        self.beacons.append(relCords)

input = open('2021/19/input').read().splitlines()

scanners = {}
scannerId = 0
for line in input:
    if len(line) == 0:
        scanners[scannerId].calculateDistances()
        #Increase scanner id
        scannerId += 1
    elif line[0:3] == '---':
        #Start of scanner
        scanners[scannerId] = Scanner(scannerId) 
    else:
        cords = [int(x) for x in line.split(',')]
        scanners[scannerId].addBeacon(tuple(cords))
scanners[scannerId].calculateDistances()

linkedScanners = {}
for s in scanners:
    for t in scanners:
        if t > s:
            same = scanners[s].overlapping(scanners[t])
            if same:
                if s not in linkedScanners:
                    linkedScanners[s] = []
                if t not in linkedScanners:
                    linkedScanners[t] = []
                linkedScanners[s].append(t)
                linkedScanners[t].append(s)


for s in linkedScanners:
    for t in linkedScanners[s]:
        scanners[s].combineScanners(scanners[t])

finalBeacons = set()
scannersToAdd = [0]
scannersAdded = set()
scannerPos = {}
history = []
while len(scannersToAdd) > 0:
    head = scannersToAdd.pop()
    if head not in scannersAdded:
        if head == 0:
            for beacon in scanners[head].beacons:
                finalBeacons.add(beacon)
            scannersAdded.add(head)
            scannerPos[0] = (0,0,0)
        else:
            beacons = scanners[head].beacons.copy()
            sPos = [0]*3
            for i in range(len(history)):
                if i == 0:
                    tMap, tVec = scanners[history[-1]].transformations[head]
                else:
                    tMap, tVec = scanners[history[-(1+i)]].transformations[history[-(i)]]
                newBeacons = []
                for beacon in beacons:
                    newBeacon = [0]*3
                    for dim in range(len(beacon)): 
                        s,v = tMap[dim]
                        if s == '+':
                            newBeacon[dim] = beacon[v] + tVec[dim]
                        elif s == '-':
                            newBeacon[dim] = -beacon[v] + tVec[dim]
                    newBeacons.append(tuple(newBeacon))
                beacons = newBeacons
                newSpos = [0]*3
                for dim in range(len(beacon)): 
                    s,v = tMap[dim]
                    if s == '+':
                        newSpos[dim] = sPos[v] + tVec[dim]
                    elif s == '-':
                        newSpos[dim] = -sPos[v] + tVec[dim]
                sPos = newSpos
            for beacon in beacons:
                finalBeacons.add(beacon)
            scannerPos[head] = tuple(sPos)
            scannersAdded.add(head)

    for next in linkedScanners[head]:
        if next not in scannersAdded:
            scannersToAdd.append(next)
            history.append(head)
            break
    if len(scannersToAdd) == 0 and len(history) > 0:
        prev = history.pop()
        scannersToAdd.append(prev)


# scannersToAdd = linkedScanners[0].copy()
# scannersAdded = [0]

# while scannersToAdd:
#     print(scannersToAdd)
#     o = scannersToAdd.pop(0)

#     if o not in scannersAdded:
#         scanners[0].combineScanners(scanners[o])
#         scannersAdded.append(o)
#         for next in linkedScanners[o]:
#             if next not in scannersAdded and next not in scannersToAdd:
#                 scannersToAdd.append(next)

print(linkedScanners)
print("Answer part A: the number of beacons is {}".format(len(finalBeacons)))
maxDist = 0
for i in range(len(scannerPos)):
    for j in range(len(scannerPos)):
        if i > j:
            totDist = 0
            for dim in range(len(scannerPos[i])):
                totDist += abs(scannerPos[i][dim] - scannerPos[j][dim])
            if totDist > maxDist:
                maxDist = totDist
print("Answer part B: The maximum dist between scanners is {}".format(maxDist))
