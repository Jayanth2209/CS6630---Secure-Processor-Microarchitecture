prime = 19

def substitution(char):
    switch = {
        'a' : 'z',
        'b' : 'j',
        'c' : 's',
        'd' : 'q',
        'e' : 'r',
        'f' : 'y',
        'g' : 'i',
        'h' : 'w',
        'i' : 'm',
        'j' : 'h',
        'k' : 'f',
        'l' : 'g',
        'm' : 'b',
        'n' : 'c',
        'o' : 'x',
        'p' : 'e',
        'q' : 'a',
        'r' : 't',
        's' : 'u',
        't' : 'o',
        'u' : 'd',
        'v' : 'k',
        'w' : 'n',
        'x' : 'l',
        'y' : 'p',
        'z' : 'v',
        '{' : '=',
        '}' : '_',
        '=' : '}',
        '_' : '{'
        }
    return switch.get(char,char)

# compute hash of the supplied string
def compute_hash(password):
    password = password.ljust(prime,"=")[0:prime]
    hash = ""
    for i in range(prime):
        hash += substitution(password[(7*i+4)%prime])
    return hash

HASH_IDXS = []
for i in range(prime):
    HASH_IDXS.append((7*i+4)%prime)
print(HASH_IDXS)

stored_password = "spm{Fast_&_Furious}"

blah = ""
for i in HASH_IDXS:
    blah += stored_password[i]
print(blah)

print("Hash of spm{Fast_&_Furious}: ", compute_hash(stored_password))
print("Hash of spm{Fast_&_Furious}xyz: ", compute_hash(stored_password+"xyz"))
