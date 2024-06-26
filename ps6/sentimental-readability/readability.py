import sys


def main():
    text = str(input("Text: "))
    # calculations
    letterCount, punctuationCount, wordCount = 0, 0, 1

    n = len(text)
    for letter in range(n):
        if text[letter].isalpha():
            letterCount += 1
        elif ord(text[letter]) == 46 or ord(text[letter]) == 63 or ord(text[letter]) == 33:  # ascii
            punctuationCount += 1
        elif text[letter] == ' ':
            wordCount += 1

    # calculating L & S
    L = letterCount / wordCount * 100
    S = punctuationCount / wordCount * 100
    index = (0.0588 * L) - (0.296 * S) - 15.8
    index += 0.5
    index = int(index)

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
