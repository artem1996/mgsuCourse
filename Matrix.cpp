//
// Created by as on 21.02.18.
//

#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <sstream>

int Matrix::get(int rowNumber, int columnNumber) {
    Row* tempRow = firstRow;
    while (true) {
        if (tempRow == nullptr || tempRow->getNumber() > rowNumber)
            return 0;
        if(tempRow->getNumber() == rowNumber)
            return tempRow->getColumn(columnNumber);
        tempRow = tempRow->getNext();
    }
}

void Matrix::set(int rowNumber, int columnNumber, int value) {
    Row* prevRow = nullptr;
    Row* tempRow = firstRow;
    while (true) {
        if(tempRow == nullptr || tempRow->getNumber() > rowNumber) {
            if(value == 0) return;
            if(prevRow == nullptr) {
                firstRow = new Row(rowNumber);
                firstRow->setColumn(columnNumber, value);
            } else {
                auto * newRow = new Row(rowNumber);
                newRow->setNext(tempRow);
                prevRow->setNext(newRow);
                newRow->setColumn(columnNumber, value);
            }
            return;
        }
        if(tempRow->getNumber() == rowNumber) {
            if(!tempRow->setColumn(columnNumber, value)) {
                if(prevRow == nullptr) {
                    firstRow = tempRow->getNext();
                } else {
                    prevRow->setNext(tempRow->getNext());
                }
                delete(tempRow);
            }
            return;
        }
        prevRow = tempRow;
        tempRow = prevRow->getNext();
    }
}

Matrix::~Matrix() {
    if(firstRow != nullptr)
        delete(firstRow);
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    os << matrix.columns << std::endl;
    Row* tempRow = matrix.firstRow;
    while (tempRow != nullptr) {
        int additionalCoefficient = tempRow->getNumber() * matrix.columns;
        Point* tempPoint = tempRow->getFirstPoint();
        while (tempPoint != nullptr) {
            os << " " << additionalCoefficient + tempPoint->getColumn();
            tempPoint = tempPoint->getNext();
        }
        tempRow = tempRow->getNext();
    }
    os << std::endl;
    tempRow = matrix.firstRow;
    while (tempRow != nullptr) {
        Point* tempPoint = tempRow->getFirstPoint();
        while (tempPoint != nullptr) {
            os << " " << tempPoint->getValue();
            tempPoint = tempPoint->getNext();
        }
        tempRow = tempRow->getNext();
    }
    return os;
}

std::istream &operator>>(std::istream &is, Matrix &matrix) {
    is >> matrix.columns;
    do {
        int tempValue;
        is >> tempValue;
        matrix.set(tempValue / matrix.columns, tempValue % matrix.columns, 1);
    } while (is.get() != '\n');
    Row* tempRow = matrix.firstRow;
    Point* tempPoint = tempRow->getFirstPoint();
    do {
        is >> tempPoint->value;
        tempPoint = tempPoint->getNext();
        if(tempPoint == nullptr) {
            tempRow = tempRow->getNext();
            if(tempRow != nullptr)
                tempPoint = tempRow->getFirstPoint();
        }
    } while (!is.eof());
}

Matrix::Matrix(int columns) : columns(columns), firstRow(nullptr) {}

int Row::getNumber() {
    return rowNumber;
}

Row *Row::getNext() {
    return next;
}

int Row::getColumn(int columnNumber) {
    Point* tempColumn = firstPoint;
    while (true) {
        if(tempColumn == nullptr || tempColumn->getColumn() > columnNumber)
            return 0;
        if(tempColumn->getColumn() == columnNumber)
            return tempColumn->getValue();
        tempColumn = tempColumn->getNext();
    }
}

void Row::setNext(Row *next) {
    Row::next = next;
}

bool Row::setColumn(int columnNumber, int value) {
    Point* prevPoint = nullptr;
    Point* tempPoint = firstPoint;
    while (true) {
        if(tempPoint == nullptr || tempPoint ->getColumn() > columnNumber) {
            if(value == 0)
                return (firstPoint != nullptr);
            auto * newPoint = new Point(columnNumber);
            newPoint->setValue(value);
            newPoint->setNext(tempPoint);
            if(prevPoint == nullptr)
                firstPoint = newPoint;
            else
                prevPoint->setNext(newPoint);
            return true;
        }
        if(tempPoint->getColumn() == columnNumber)
            if(value == 0) {
                if(prevPoint != nullptr)
                    prevPoint->setNext(tempPoint->getNext());
                else
                    firstPoint = tempPoint->getNext();
                delete(tempPoint);
                return (firstPoint != nullptr);
            } else {
                tempPoint->setValue(value);
                return true;
            }
        prevPoint = tempPoint;
        tempPoint = prevPoint->getNext();
    }
}

Row::Row(int rowNumber) {
    Row::rowNumber = rowNumber;
    firstPoint = nullptr;
    next = nullptr;
}

Row::~Row() {
    if(firstPoint != nullptr)
        delete(firstPoint);
    if(next != nullptr)
        delete(next);
}

Point *Row::getFirstPoint() const {
    return firstPoint;
}

int Point::getColumn() const {
    return column;
}

int Point::getValue() const {
    return value;
}

Point *Point::getNext() const {
    return next;
}

void Point::setValue(int value) {
    Point::value = value;
}

void Point::setNext(Point *next) {
    Point::next = next;
}

Point::Point(int columnNumber) {
    value = 0;
    next = nullptr;
    column = columnNumber;
}

Point::~Point() {
    if(next != nullptr)
        delete(next);
}
