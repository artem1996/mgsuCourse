#include <iostream>
#include <fstream>
#include <sstream>
#include "Matrix.h"

using namespace std;

Matrix * matrixGenerator(ostream& stream, int resolution, int probability, int maxValue);

int main() {
    ofstream outputFile("fileOut.csv");
    Matrix* matrix = matrixGenerator((ostream&) outputFile, 100, 100, 5);
//    outputFile << "Hello, Word!" << std::endl;
    outputFile.close();
    ofstream compressedFile("compress.csv");
    compressedFile << *matrix;
    compressedFile.close();
    ifstream compr("compress.csv");
    Matrix* inpMatr = new Matrix(100);
    compr >> *inpMatr;
    inpMatr->get(0,0);
//    int temp;
//    int strNumber = 1;
//    while (!inputFile.eof()) {
//        int colNumber = 1;
//        string str;
//        getline(inputFile, str);
//        istringstream strin(str);
//        bool isStrDefined = false;
//        while (strin >> temp) {
//            if (temp > 0) {
//                if(!isStrDefined) {
//                    compressedFile << 0 << ':' << strNumber << ';';
//                    isStrDefined = true;
//                }
//                compressedFile << temp << ':' << colNumber << ';';
//            }
//            colNumber++;
//        }
//        strNumber++;
//    }
//    compressedFile << "0:0;";
//    compressedFile.close();
    return 0;
}

Matrix* matrixGenerator(ostream& stream, int resolution, int probability, int maxValue) {
    Matrix* matrix = new Matrix(resolution);
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