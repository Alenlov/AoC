visited = set()

def finished(state):
    gen = state[0]
    mic = state[1]
    fl = state[2]
    if fl != 4:
        return False
    for i in range(len(gen)):
        if mic[i] != 4:
            return False
        if gen[i] != 4:
            return False
    return True

def stateOk(state):
    gen = state[0]
    mic = state[1]
    fl = state[2]
    if fl < 1 or fl > 4:
        return False
    for i in range(len(mic)):
        if mic[i] != gen[i]: # G och M inte på samma våning
            if mic[i] in gen:
                return False
    return True

def statesToVisit(setToVisit):
    toVisit = set()
    for state in setToVisit:
        if finished(state):
            return None
        visited.add(state)
        gen = state[0]
        mic = state[1]
        fl = state[2]
        # Kan ta en eller två saker upp eller ner en våning.
        for i in range(len(gen)):
            if gen[i] == fl: # Kan flytta
                nG = list(gen)
                nG[i] += 1
                testState = ( tuple(nG) , mic, fl+1)
                if stateOk(testState):
                    if testState not in visited:
                        toVisit.add(testState)
                nG[i] -= 2
                testState = ( tuple(nG) , mic, fl-1)
                if stateOk(testState):
                    if testState not in visited:
                        toVisit.add(testState)
                for j in range(i+1, len(gen)):
                    if gen[j] == fl:
                        nG = list(gen)
                        nG[i] += 1
                        nG[j] += 1
                        testState = (tuple(nG), mic, fl+1)
                        if stateOk(testState):
                            if testState not in visited:
                                toVisit.add(testState)
                        nG[i] -= 2
                        nG[j] -= 2
                        testState = ( tuple(nG) , mic, fl-1)
                        if stateOk(testState):
                            if testState not in visited:
                                toVisit.add(testState)
                for j in range(len(mic)):
                    if mic[j] == fl:
                        nG = list(gen)
                        nM = list(mic)
                        nG[i] += 1
                        nM[j] += 1
                        testState = ( tuple(nG), tuple(nM), fl + 1)
                        if stateOk(testState):
                            if testState not in visited:
                                toVisit.add(testState)
                        nG[i] -= 2
                        nM[j] -= 2
                        testState = ( tuple(nG), tuple(nM), fl - 1)
                        if stateOk(testState):
                            if testState not in visited:
                                toVisit.add(testState)
        for i in range(len(mic)):
            if mic[i] == fl:
                nM = list(mic)
                nM[i] += 1
                testState = (gen, tuple(nM), fl+1)
                if stateOk(testState):
                    if testState not in visited:
                        toVisit.add(testState)
                nM[i] -= 2
                testState = (gen, tuple(nM), fl-1)
                if stateOk(testState):
                    if testState not in visited:
                        toVisit.add(testState)
                for j in range(i+1, len(mic)):
                    if mic[j] == fl:
                        nM = list(mic)
                        nM[i] += 1
                        nM[j] += 1
                        testState = (gen, tuple(nM), fl+1)
                        if stateOk(testState):
                            if testState not in visited:
                                toVisit.add(testState)
                        nM[i] -= 2
                        nM[j] -= 2
                        testState = (gen, tuple(nM), fl-1)
                        if stateOk(testState):
                            if testState not in visited:
                                toVisit.add(testState)
    return toVisit

gD = (4, 4, 4, 4)
mD = (4, 4, 4, 4)


#generators = (1, 2, 2, 2, 2)
#microchips = (1, 3, 3, 3, 3)
#generators = (2,3)
#microchips = (1,1)
generators = (1,1,1, 2, 2, 2, 2)
microchips = (1,1,1, 3, 3, 3, 3)
floor = 1
state = (generators, microchips, floor)
visited.add(state)
setsToVisit = {state}
steps = 0
done = False
while not done:
    print(steps)
    #print(len(visited))
    setsToVisit = statesToVisit(setsToVisit)
    #print(setsToVisit)
    if setsToVisit == None :
        done = True
    else:
        steps += 1
