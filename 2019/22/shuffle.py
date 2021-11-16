

def cut(N, a, b):
    #newPos = (pos - N)
    return a, b-N

def inc(N, a, b):
    #newPos = (pos*N)
    return a*N, b*N

def deal(a, b):
    #newPos = (-1 * pos - 1)
    return a*(-1), b*(-1)-1

def revCut(N, a, b):
    #newPos = (pos + N)
    return a, b+N

def revInc(N, l, a, b):
    #newPos = inverse(N, l+1) * pos
    inv = inverse(N,l+1)
    return a*inv, b*inv

def expRec(a,n,l):
    if n == 0:
        return 1
    elif n & 1 == 1:
        e = (a*a) % (l+1)
        return (a * expRec(e, n//2,l)) % (l+1)
    else:
        e = (a*a) % (l+1)
        return expRec(e, n//2,l) % (l+1)

def sumRec(b,n,l):
    if n == 0:
        return 1
    elif n & 1 == 1:
        e = (b*b) % (l+1)
        return ((1+b) * sumRec(e, n//2, l)) % (l+1)
    else:
        e = (b*b) % (l+1)
        return (1 + (b + e) * sumRec(e, n//2 -1,l )) % (l+1)


def inverse(a,l):
    t = 0
    newt = 1
    r = l
    newr = a
    while newr != 0:
        quot = r // newr
        qt = t - quot * newt
        qr = r - quot * newr
        t = newt
        r = newr
        newt = qt
        newr = qr
    
    if r > 1:
        print("INV NOT POSSIBLE {}, {}".format(a,l))
        return False

    if t < 0:
        t += l
    
    return t


instructionFile = open('2019/22/input','r')
shuffleOrder = instructionFile.read().splitlines()
instructionFile.close()

## PART A

pos = 2019
l = 10006
a = 1
b = 0
for shuffle in shuffleOrder:
    thisShuffle = shuffle.split(' ')
    if len(thisShuffle) == 2:
        a,b = cut(int(thisShuffle[1]),a,b)
    else:
        if len(thisShuffle[2]) == 3:
            a,b = deal(a, b)
        else:
            a,b = inc(int(thisShuffle[3]),a,b)
    a %= (l + 1)
    b %= (l + 1)
endedIn = (a*pos + b )% (l+1)
print('Answer part A. Card 2019 ends up at position {}'.format(endedIn))

## PART B


whereToEnd = 2020
l = 119315717514047 - 1
#whereToEnd = endedIn % (l+1)
endPos = whereToEnd
totItr = 101741582076661
shuffleOrder.reverse()
a_rev = 1
b_rev = 0
for shuffle in shuffleOrder:
    thisShuffle = shuffle.split(' ')
    if len(thisShuffle) == 2:
        a_rev, b_rev = revCut(int(thisShuffle[1]),a_rev,b_rev)
    else:
        if len(thisShuffle[2]) == 3:
            a_rev, b_rev = deal(a_rev, b_rev)
        else:
            a_rev, b_rev = revInc(int(thisShuffle[3]),l,a_rev,b_rev)



a_final = expRec(a_rev,totItr,l)
b_final = (b_rev * sumRec(a_rev,totItr-1,l)) % (l+1)

print('Answer Part B: The card that ended up on place {} after all {} shuffles was {}'.format(whereToEnd,totItr,(a_final*whereToEnd + b_final) % (l+1)))
