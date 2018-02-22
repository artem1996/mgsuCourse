//
// Created by as on 21.02.18.
//

#ifndef MGSUCOURSE_MATRIX_H
#define MGSUCOURSE_MATRIX_H

class point {
    int column;
    int value;
    point* next;
public:
    void setValue(int value);

    void setNext(point *next);

public:
    int getColumn() const;
    int getValue() const;
    point *getNext() const;
};

class row {
    int rowNumber;
    point* firstPoint;
    row* next;
public:
    void setNext(row *next);
    bool setColumn(int columnNumber, int value);

public:
    int getNumber();
    int getColumn(int columnNumber);
    row* getNext();
};

class matrix {
    row* firstRow;
public:
    int get(int row, int column);
    int set(int row, int column, int value);
};


#endif //MGSUCOURSE_MATRIX_H
