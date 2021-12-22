import time

rules = open('2021/22/input').read().splitlines()

dims = {'x':0, 'y':1, 'z':2}

class Cubes:
    def __init__(self, limits, state):
        self.state = state
        self.limits = limits
        self.corners = set()
        for x in limits['x']:
            for y in limits['y']:
                for z in limits['z']:
                    self.corners.add((x,y,z))
        self.removed = []

    def inside(self, point):
        for dim in self.limits:
            if self.limits[dim][0] > point[dims[dim]] or self.limits[dim][1] < point[dims[dim]]:
                return False
        return True

    def combineWith(self, other):
        overlapLimits = self.overlap(other)
        if overlapLimits:
            self.removeCube(Cubes(overlapLimits,'off'))
            return True
        else:
            return False

    def removeCube(self, other):
        for rem in self.removed:
            rem.combineWith(other)
        self.removed.append(other)

    def overlap(self,other):
        overlapLimits = {}
        for dim in self.limits:
            thisMin = self.limits[dim][0]
            thisMax = self.limits[dim][1]
            otherMin = other.limits[dim][0]
            otherMax = other.limits[dim][1]
            overlapMin = max(thisMin, otherMin)
            overlapMax = min(thisMax, otherMax)
            if overlapMin <= overlapMax:
                overlapLimits[dim] = [overlapMin, overlapMax]
            else:
                return None
        return overlapLimits
        
    def volume(self):
        vol = 1
        for dim in self.limits:
            vol *= (self.limits[dim][1] - self.limits[dim][0] + 1) 
        removedVol = 0
        for rem in self.removed:
            removedVol += rem.volume()
        return vol - removedVol

cubes = {}
cubesA = {}
cubeA = Cubes({'x':[-50,50],'y':[-50,50],'z':[-50,50]},'A')
time2 = time.time()
id = 0
for rule in rules:
    state, poses = rule.split()
    poses = [ x.split('=') for x in poses.split(',')]
    vals = {}
    for pos in poses:
        vals[pos[0]] = [int(x) for x in pos[1].split('..')]
    newCube = Cubes(vals,state)
    
    for i in range(id):
        cubes[i].combineWith(newCube)
    if state == 'on':
        cubes[id] = newCube
        id += 1
        if cubeA.overlap(newCube):
            cubesA[id] = newCube
totVolA = 0
for c in cubesA:
    totVolA += cubesA[c].volume()


totVol = 0
for c in cubes:
    totVol += cubes[c].volume()
partBtime = time.time() - time2
print("Answer part A: the total number of cubes in [-50,50]^3 is {}".format(totVolA))
print("Answer part B: the total number of cubes that are on is {} took {} s".format(totVol,partBtime))