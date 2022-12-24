#include <cs50.h>
#include <stdio.h>

void credit_card_system(long card_number)
{
    if (card_number < 3800000000000000 && card_number >= 3400000000000000)
    {
        printf("AMEX\n");
    }
    else if (card_number < 5600000000000000 && card_number >= 5100000000000000)
    {
        printf("MasterCard\n");
    }
    else if (card_number < 5000000000000000 && card_number >= 4000000000000000)
    {
        printf("Visa\n");
    }
    else {
        printf("Invalid card number.\n");
    }
}

void validate_card(long card_number)
{
    int first_sum = 0;
    long copy_card_number = card_number;
    long second_card_number = card_number;
    int x = 0;
    for (int i = 0; i < 15; i = i + 2)
    {
        first_sum += copy_card_number % 10;
        copy_card_number = copy_card_number / 100;
        printf("copy_card_number: %li, fist_sum: %i\n", copy_card_number, first_sum);
    }
    int second_sum = 0;
    for (int i = 0; i < 15; i = i + 2)
    {
        second_card_number = second_card_number / 10;
        x = (second_card_number % 10) * 2;
        if (x > 9)
        {
            second_sum += x % 10;
            x = x / 10;
            second_sum += x % 10;
            x = 0;
            second_card_number = second_card_number / 10;
        }
        else
        {
        second_sum += x;
        second_card_number = second_card_number / 10;
        }
        printf("second_sum: %i\n", second_sum);
    }
    if ((first_sum + second_sum) % 10 == 0)
    {
        printf("VALID\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int main(void)
{
    long card_number = get_long("Number: ");
    credit_card_system(card_number);
    validate_card(card_number);
}