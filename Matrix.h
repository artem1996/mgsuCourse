//
// Created by as on 21.02.18.
//

#ifndef MGSUCOURSE_MATRIX_H
#define MGSUCOURSE_MATRIX_H

#include <ostream>

class Point {
public:
    int column;
    int value;
    Point* next;
public:
    Point(int columnNumber);
    void setValue(int value);
    void setNext(Point *next);

public:
    int getColumn() const;
    int getValue() const;
    Point *getNext() const;
    int getMaxColumn();

    virtual ~Point();
};

class Row {
    int rowNumber;
    Point* firstPoint;
public:
    Point *getFirstPoint() const;

private:
    Row* next;
public:
    Row(int rowNumber);

    void setNext(Row *next);
    bool setColumn(int columnNumber, int value);

public:
    int getNumber();
    int getColumn(int columnNumber);
    int getMaxRow();
    int getMaxColumn();
    Row* getNext();

    virtual ~Row();
};

class Matrix {
public:
    int columns;
    Matrix(int columns);

public:
    Row* firstRow;
//    Matrix(int rows, int columns);

    int get(int row, int column);
    void set(int row, int column, int value);
    int getMaxRow();
    int getMaxColumn();

    virtual ~Matrix();

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
    friend std::istream &operator>>(std::istream &is, Matrix &matrix);
};


#endif //MGSUCOURSE_MATRIX_H
