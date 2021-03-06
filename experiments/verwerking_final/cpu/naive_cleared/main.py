import glob
import os

__author__ = 'warreee'

import csv



def csvToMatrix(filename):
    csvMatrix = []
    with open(filename, newline='\n') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        for row in reader:
            csvMatrix.append(row)

    return csvMatrix

def parse(csvMatrix, filename):
    firstEntry = []
    lastEntry = []

    for index, item in enumerate(csvMatrix):
        if (index == len(csvMatrix) - 1):
            break

        firstRow = float(csvMatrix[index][2])
        nextRow = float(csvMatrix[index + 1][2])

        if ( firstRow < 3 and nextRow >= 3):
            firstEntry.append(float(csvMatrix[index][0]))
            continue

        if ( firstRow >= 3 and nextRow < 3):
            lastEntry.append(float(csvMatrix[index][0]))

    getTimeSpans(firstEntry, lastEntry, filename)

    print(firstEntry)
    print(lastEntry)


def getTimeSpans(first, last, filename):
    timeSpans = []
    output = open(filename[:-4] + ".timespans", 'w')
    for f, l in zip(first, last):
        timeSpans.append(abs(f - l))
        output.write(str(abs(f - l)) + '\n')
    print(timeSpans)


def main():

    for filename in glob.glob("*.csv"):
        parse(csvToMatrix(filename), filename)
        print(filename)


if __name__ == "__main__":
    main()
