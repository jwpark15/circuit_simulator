import matplotlib.pyplot as plt
import subprocess
import argparse
import random
import bisect

def parseCircuit(filename):
    nets = set()
    counter = 0
    with open(filename, "r") as f:
        for line in f:
            if(line.startswith("INPUT")):
                for word in line.strip().split():
                    if not(word == "-1" or word == "INPUT"):
                        counter += 1
            else:
                for word in line.strip().split()[1:]:
                    if (int(word) >= 0):
                        nets.add(int(word))
                
    return counter, nets

def generateRandomInput(in_length, tests):
    while(True):
        key = ""
        for i in range(in_length):
            key += str(random.randint(0,1))

        if key not in tests:
            tests.add(key)
            break
        
    return key


def createPossibleTestList(key, in_len, n, test_set):
    if (in_len == n): 
        str_key = ""
        for x in key:
            str_key += str(x) 
        test_set.add(str_key)
        return

    key[n] = 0
    createPossibleTestList(key, in_len, n+1, test_set)

    key[n] = 1
    createPossibleTestList(key, in_len, n+1, test_set)
    
    
        
def generateUniqueTest(tests):
    key = random.choice(tuple(tests))
    tests.remove(key)
    return key


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('circuit')
    args = parser.parse_args()
    
    in_len, nets = parseCircuit(args.circuit)

    fault_set = set()
    for x in nets:
        fault_set.add((x, 0))
        fault_set.add((x, 1))
    
    total_faults = len(fault_set)

    detected_fault_set = set()
    
    iters = [0]
    detected = [0]
    
    above_75 = 0;
    above_90 = 0;

    tests = set() 
    """
    key = [None]*in_len
    createPossibleTestList(key, in_len, 0, tests)
    """
    #print(tests)
    x = 1
    while(not above_90):
        bin_in = generateRandomInput(in_len, tests)
        #bin_in = generateUniqueTest(tests)        

        # run C++ engine
        subprocess.run(['./dsim', args.circuit, bin_in])

        # read detected.faults to determine fault coverage
        flag = False
        with open("detected.faults", "r") as f:
            for line in f:
                if (flag):
                    if (line.startswith("NUMBER")):
                        break    
                    l = line.strip().split()
                    detected_fault_set.add((l[0], l[1]))
                     
                elif (line.startswith("NET")):
                    flag = True
                    continue

        iters.append(x)
        percent_detected = len(detected_fault_set) / total_faults
        detected.append(percent_detected)
        print(percent_detected)
    
        if (not above_75 and percent_detected > 0.75):
            above_75 = x

        if (not above_90 and percent_detected > 0.9):
            above_90 = x
        
        x += 1             
                    
    print(f'Iterations to above 75%: {above_75}')
    print(f'Iterations to above 90%: {above_90}')

    # plot results
    plt.plot(iters, detected)
    plt.ylabel('Percentage of Faults Detected')
    plt.xlabel('Number of Iterations')
    plt.show()

