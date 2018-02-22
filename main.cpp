#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void matrixGenerator(ostream& stream, int resolution, int probability, int maxValue);

int main() {
    ofstream outputFile("fileOut.csv");
    matrixGenerator((ostream&) outputFile, 100000, 10, 5);
//    outputFile << "Hello, Word!" << std::endl;
    outputFile.close();
    ofstream compressedFile("compress.csv");
    ifstream inputFile("fileOut.csv");
    int temp;
    int strNumber = 1;
    while (!inputFile.eof()) {
        int colNumber = 1;
        string str;
        getline(inputFile, str);
        istringstream strin(str);
        bool isStrDefined = false;
        while (strin >> temp) {
            if (temp > 0) {
                if(!isStrDefined) {
                    compressedFile << 0 << ':' << strNumber << ';';
                    isStrDefined = true;
                }
                compressedFile << temp << ':' << colNumber << ';';
            }
            colNumber++;
        }
        strNumber++;
    }
    compressedFile << "0:0;";
    compressedFile.close();
    return 0;
}

void matrixGenerator(ostream& stream, int resolution, int probability, int maxValue) {
    maxValue += 1;
    srand(static_cast<unsigned int>(time(nullptr)));
    for(int i = 0; i < resolution; i++) {
        for(int j = 0; j < resolution; j++) {
            stream << (rand() % probability == 0 ? rand() % maxValue : 0) << " ";
        }
        stream << endl;
    }
}