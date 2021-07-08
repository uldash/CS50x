import sys
import csv


def main(fdata, fsequence):
    with open(fdata, "r") as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            if match_sequence(row, fsequence):
                print(row["name"])
                sys.exit(0)
    print("No match")
    sys.exit(1)


def match_sequence(row, fsequence):
    sequences = dict(row)
    sequences.pop("name")

    file = open(fsequence, "r")
    line = file.read()

    score = len(sequences)
    for sequence in sequences:
        tmp = line.find(sequence * int(sequences[sequence]))
        tmp_more = line.find(sequence * (int(sequences[sequence]) + 1))
        if tmp != tmp_more:
            score -= 1
    file.close()

    if score == 0:
        return True

    return False


if __name__ == "__main__":
    if len(sys.argv) == 3:
        main(sys.argv[1], sys.argv[2])
    else:
        print("Usage: python dna.py data.csv sequence.txt")