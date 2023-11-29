from cs50 import get_float

while True:
    n = get_float("Change owned: ")

    if n > 0:
        break
i=0
cent =round(n*100)
while cent >= 25:
    cent = cent - 25
    i += 1
while cent >= 10:
    cent = cent - 10
    i += 1
while cent >= 5:
    cent= cent - 5
    i += 1
while cent >= 1:
    cent = cent -1
    i += 1

print(i)