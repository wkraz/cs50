import sys


def main():
    num = int(input("Number: "))

    l = num
    length = 0
    while l > 0:
        l = l // 10
        length += 1
    if length != 13 and length != 15 and length != 16:
        print("INVALID")
        sys.exit(0)
    sum1, sum2, total, mod1, mod2, d1, d2 = 0, 0, 0, 0, 0, 0, 0
    x = num

    while True:
        mod1 = x % 10
        x = x // 10
        sum1 += mod1

        mod2 = x % 10
        x = x // 10

        mod2 *= 2
        d1 = mod2 % 10
        d2 = mod2 // 10
        sum2 = sum2 + d1 + d2

        if x <= 0:
            break

    total = sum1 + sum2

    if total % 10 != 0:
        print("INVALID")
        sys.exit(1)

    s = num
    while True:
        s = s // 10
        if s <= 100:
            break

    if (s // 10 == 5) and (0 < s % 10 and s % 10 < 6) and length == 16:
        print("MASTERCARD")
    elif (s // 10 == 3) and (s % 10 == 4 or s % 10 == 7) and length == 15:
        print("AMEX")
    elif s // 10 == 4 and (length == 13 or length == 16):
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
