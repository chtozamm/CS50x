# from cs50 import get_string

def main():
    # Prompt user for a text
    text = input("Text: ")

    # Get numbers of letters, words and sentences
    count_letter = count_letters(text)
    count_word = count_words(text)
    count_sentence = count_sentences(text)

    # Print Grade
    calculate_text_index(count_letter, count_word, count_sentence)

    return 0

def count_letters(text):
    count_letter = 0

    for i in range(len(text)):
        if (ord(text[i]) >= 65 and ord(text[i]) <= 90) or (ord(text[i]) >= 97 and ord(text[i]) <= 122):
            count_letter += 1

    # print(f"{count_letter} letters")
    return count_letter


def count_words(text):
    count_word = 0

    for i in range(len(text)):
        if ord(text[i]) == 32 or ord(text[i]) == 33 or ord(text[i]) == 44 or ord(text[i]) == 46 or ord(text[i]) == 63:
            if ord(text[i]) == 44 and ord(text[i+1]) == 32:
                continue
            elif (i+1 != len(text)) and ord(text[i]) == 46 and ord(text[i+1]) == 32:
                continue
            else:
                count_word += 1

    # print(f"{count_word} words")
    return count_word

def count_sentences(text):
    count_sentence = 0

    for i in range(len(text)):
        if ord(text[i]) == 33 or ord(text[i]) == 46 or ord(text[i]) == 63:
            count_sentence += 1

    # print(f"{count_sentence} sentences")
    return count_sentence

def calculate_text_index(count_letter, count_word, count_sentence):
    text_grade = 0

    L = count_letter / count_word * 100
    S = count_sentence / count_word * 100

    text_grade = round(0.0588 * L - 0.296 * S - 15.8)

    if text_grade < 1:
        print("Before Grade 1")
    elif text_grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {text_grade}")

    return

main()