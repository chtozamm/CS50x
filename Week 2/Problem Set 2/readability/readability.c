#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
void calculate_text_index(int count_letter, int count_word, int count_sentence);

int main(void)
{
    // Prompt user for a text
    string text = get_string("Text: ");

    // Count for letters, words, sentences
    int count_letter = count_letters(text);
    int count_word = count_words(text);
    int count_sentence = count_sentences(text);

    // Print Grade X
    calculate_text_index(count_letter, count_word, count_sentence);

    return 0;
}

int count_letters(string text)
{
    // Go through each character in string
    // If character is in range of letters (ASCII), count_letter++
    int count_letter = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            count_letter++;
        }
    }

    printf("%i letters\n", count_letter);
    return count_letter;
}

int count_words(string text)
{
    int count_word = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == 32 || text[i] == 33 || text[i] == 44 || text[i] == 46 || text[i] == 63)
        {
            if (text[i] == 44 && text[i+1] == 32)
            {
                count_word++;
                i++;
            }
            else if (text[i] == 46 && text[i + 1] == 32)
            {
                count_word++;
                i++;
            }
            else
            {
                count_word++;
            }
        }
    }

    printf("%i words\n", count_word);
    return count_word;
}

int count_sentences(string text)
{
    int count_sentence = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            count_sentence++;
        }
    }

    printf("%i sentences\n", count_sentence);
    return count_sentence;
}

void calculate_text_index(int count_letter, int count_word, int count_sentence)
{
    int text_grade = 0;

    // Average number of letters per 100 words
    float L = (float) count_letter / count_word * 100;
    // Average number of sentences per 100 words
    float S = (float) count_sentence / count_word * 100;

    printf("L: %f\n", L);
    printf("S: %f\n", S);

    // Calculate index of given text using Coleman-Liau formula
    text_grade = round(0.0588 * L - 0.296 * S - 15.8);

    // Print out text's grade
    if (text_grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (text_grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", text_grade);
    }

    return;
}