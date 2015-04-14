import csv
import glob

__author__ = 'warreee'


def clear(amount, filename):
    csvMatrix = []
    with open(filename, newline='\n') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        for row in reader:
            csvMatrix.append(row)

    return csvMatrix[amount:]


def writeOutput(filename, csvMatrix):
    with open(filename[:-4] + "_cleared.csv", newline='\n', mode='w') as result:
        wtr = csv.writer( result )
        for r in csvMatrix:
            test = r[3]
            wtr.writerow( (r[3], r[4], r[5]) )




def main():

    for filename in glob.glob("*.csv"):
        writeOutput(filename, clear(33, filename))
        print("The following file is cleared: " + filename)

if __name__ == "__main__":
    main()