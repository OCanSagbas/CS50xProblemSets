from cs50 import get_int

while True:
    height = int(get_int("Height: "))
    if height > 0 and height < 9:
        break

for i in range(height):
    for j in range(height-(i+1)):
        print(" ",  end='')
    for z in range(i+1):
        print("#",  end='')
    print(" ", end="")
    for x in range(i+1):
        print("#",  end='')
    print()

