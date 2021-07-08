def main():
    while True:
        text = input("Text: ")
        if len(text) > 0:
            break

    letter = 0
    word = 1
    sentence = 0

    for c in text:
        c = c.upper()
        if c >= "A" and c <= "Z":
            letter += 1
        if c == " ":
            word += 1
        if c == "." or c == "!" or c == "?":
            sentence += 1

    # print(f"letter: {letter} word: {word} sentence: {sentence}")

    index = coleman_liau_index(letter, word, sentence)

    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


def coleman_liau_index(letter, word, sentence):
    return round(0.0588 * (letter * 100.0 / word) - 0.296 * (sentence * 100.0 / word) - 15.8)


if __name__ == "__main__":
    main()