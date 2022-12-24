import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")


    # Read database file into a variable
    people = []
    STR = []
    with open(sys.argv[1], "r") as database:
        reader = csv.reader(database)
        firstRow = True
        for row in reader:
            # Populate STR array with STRs from the first line of database
            if firstRow:
                STR = row[1:]
                firstRow = False
                continue
            people.append(row)




    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as dna_sequence:
        data = dna_sequence.read()

        # Find longest match of each STR in DNA sequence
        matches = {}
        for i in range(len(STR)):
            matches[STR[i]] = longest_match(data, STR[i])


    # print(f"STR: {STR}")
    # print(f"people: {people}")
    # print(f"matches: {matches}")

    # TODO: Check database for matching profiles
    match = False
    count = 0
    for i in range(len(people)):
        for j in range(len(STR)):
            if (j + 1) <= len(STR):
                if int(people[i][j+1]) != matches[STR[j]]:
                    match = False
                    break
                else:
                    match = True
                    continue
        if match == True:
            print(people[i][0])
            count += 1
    if count == 0:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
