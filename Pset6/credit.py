import sys

def main():
    while True:
        creditcard = input("Credit Card Number: ")
        cardlength = len(creditcard)
        if cardlength>0 and creditcard.isdigit():
            break
    control(cardlength,creditcard)

def control(cardlength,creditcard):
    if cardlength<13 or cardlength>16 or cardlength == 14:
        print("Invalid")
        sys.exit(0)
    odd=0
    oddmult=0
    even=0
    sum=0
    #Amex
    x = int(creditcard)
    y = int(creditcard)
    for i in range (0,cardlength,2):
        even += x%10
        x = x//100
    for j in range (1,cardlength,2):
        oddmult = y%100//10*2
        y=y//100
        if oddmult>9:
            odd += oddmult%10 + oddmult//10
        else:
            odd += oddmult
    sum= odd + even
    sum=sum%10
    if sum == 0 and cardlength==15 and creditcard.startswith("34") or creditcard.startswith("37"):
        print("Amex")
    elif sum == 0 and cardlength==16 and creditcard.startswith("51") or creditcard.startswith("52") or creditcard.startswith("53") or creditcard.startswith("54") or creditcard.startswith("55"):
        print("MasterCard")
    elif sum == 0 and (cardlength==13 or cardlength==16 ) and creditcard.startswith("4"):
        print("Visa")
    else:
        print("Invalid")

if __name__ == "__main__":
    main()