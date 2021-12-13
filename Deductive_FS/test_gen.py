import random
import argparse
import subprocess

def generateTest(sequence):
    word = ''
    for x in sequence:
        if x == 'X':
            word += str(random.randint(0,1))
        else:
            word += x
    return word


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('sequence')
    args = parser.parse_args()

    binary_test = generateTest(args.sequence)
    print(binary_test)
