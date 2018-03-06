#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "Matrix.h"

using namespace std;

Matrix * matrixGenerator(ostream& stream, int resolution, int probability, int maxValue);

int main() {
    ofstream outputFile("fileOut.csv");
    Matrix* matrix = matrixGenerator((ostream&) outputFile, 10, 6, 5);
    outputFile.close();
    ofstream compressedFile("compress.csv");
    compressedFile << *matrix;
    compressedFile.close();
    ifstream compr("compress.csv");
    Matrix* inpMatr = new Matrix();
    compr >> *inpMatr;
    return 0;
}

Matrix* matrixGenerator(ostream& stream, int resolution, int probability, int maxValue) {
    Matrix* matrix = new Matrix;
    maxValue += 1;
    srand(static_cast<unsigned int>(time(nullptr)));
    for(int i = 0; i < resolution; i++) {
        for(int j = 0; j < resolution; j++) {
            int value = rand() % probability == 0 ? rand() % maxValue : 0;
            matrix->set(i, j, value);
            stream << (value) << " ";
        }
        stream << endl;
    }
    return matrix;
}

Matrix* readSorceMatrix(string fileName) {
    ifstream inputFile(fileName);

}