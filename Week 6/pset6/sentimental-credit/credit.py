from cs50 import get_int

def main():
    # Prompt card number
    card_number = get_int("Number: ")

    if validate_card(card_number):
        print(get_card_system(card_number))
    else:
        print("INVALID")

    return 0

def get_card_system(card_number):
    # 1. Check the length of card number
    # 2. Check the first two digits
    start = card_number
    while start > 100:
        start = start // 10
    if ((start == 34) or (start == 37)) and len(str(card_number)) == 15:
        card_system = "AMEX"
    elif (start >= 51) and (start < 56) and len(str(card_number)) == 16:
        card_system = "MASTERCARD"
    elif (start >= 40) and (start < 50) and len(str(card_number)) >= 13 and len(str(card_number)) < 17:
        card_system = "VISA"
    else:
        card_system = "INVALID"
    return card_system

def validate_card(card_number):
    first_sum = 0
    second_sum = 0
    copy_card_number = card_number
    second_card_number = card_number
    x = 0
    i = 0
    while (i < 15):
        first_sum += copy_card_number % 10
        copy_card_number = copy_card_number // 100
        i += 2
    i = 0
    while (i < 15):
        second_card_number = second_card_number // 10
        x = (second_card_number % 10) * 2
        if x > 9:
            second_sum += x % 10
            x = x // 10
            second_sum += x % 10
            x = 0
            second_card_number = second_card_number // 10
            i += 2
        else:
            second_sum += x
            second_card_number = second_card_number // 10
            i += 2
    if (first_sum + second_sum) % 10 == 0:
        return True
    else:
        return False

main()