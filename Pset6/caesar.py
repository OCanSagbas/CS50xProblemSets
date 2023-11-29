from sys import argv
import sys

if len(argv) != 2 or not argv[1].isdigit():
    sys.exit(0)

plaintext = input("Plaintext:")
key = int(argv[1])


for i in plaintext:
    if(i.isalpha()):
        pi = i.lower()
        pi = ord(pi) - ord("a")
        pi = (pi+key) % 26 + ord("a")
        pi = chr(pi)
        if i.islower():
            i = pi
        else:
            i = pi.upper()
    else:
        i
print(f"Ciphertext: {plaintext}", end="")
print()