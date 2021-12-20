from typing_extensions import runtime


packets = open('2021/16/input').read().strip()

hexToBit = {'0':'0000',
'1':'0001',
'2':'0010',
'3':'0011',
'4':'0100',
'5':'0101',
'6':'0110',
'7':'0111',
'8':'1000',
'9':'1001',
'A':'1010',
'B':'1011',
'C':'1100',
'D':'1101',
'E':'1110',
'F':'1111'}

binString = ''

for c in packets:
    binString += hexToBit[c]

def parsePacket(packet,head):
    version = int(packet[head:head+3],2)
    head += 3
    type = int(packet[head:head+3],2)
    head += 3
    
    #print(version,type)
    if type == 4:
        # literal
        running = True
        val = ''
        while running:
            if packet[head] == '0':
                running = False
            head += 1
            val += packet[head:head+4]
            head += 4
        val = int(val,2)
        #print(val)
    else:
        vals = []
        if packet[head] == '0':
            head += 1
            numBits = int(packet[head:head+15],2)
            head += 15
            newHead = head
            while newHead != head + numBits:
                newHead, v, subVal = parsePacket(packet, newHead)
                version += v
                vals.append(subVal)
            head = newHead
        elif packet[head] == '1':
            head += 1
            numSubpackets = int(packet[head:head+11],2)
            head += 11
            for _ in range(numSubpackets):
                head, v, subVal = parsePacket(packet,head)
                version += v
                vals.append(subVal)
        if type == 0:
            val = sum(vals)
        elif type == 1:
            val = 1
            for v in vals:
                val *= v
        elif type == 2:
            val = vals[0]
            for v in vals:
                if v < val:
                    val = v
        elif type == 3:
            val = 0
            for v in vals:
                if v > val:
                    val = v
        elif type == 5:
            if vals[0] > vals[1]:
                val = 1
            else:
                val = 0
        elif type == 6:
            if vals[0] < vals[1]:
                val = 1
            else:
                val = 0
        elif type == 7:
            if vals[0] == vals[1]:
                val = 1
            else:
                val = 0
    return head, version, val

_, v, val = parsePacket(binString,0)
print("Answer part A: the sum of the versions is {}".format(v))
print("Answer part B: evaluating everything gives the value {}".format(val))
