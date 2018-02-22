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

Matrix::Matrix() {
    firstRow = nullptr;
}

Matrix::~Matrix() {
    if(firstRow != nullptr)
        delete(firstRow);
}

int Matrix::getMaxRow() {
    if(firstRow == nullptr)
        return 0;
    else
        return firstRow->getMaxRow();
}

int Matrix::getMaxColumn() {
    if(firstRow == nullptr)
        return 0;
    int maxColumn = 0;
    Row* tempRow = firstRow;
    while (tempRow->getNext() != nullptr) {
        int tempColumn = tempRow->getMaxColumn();
        if(tempColumn > maxColumn)
            maxColumn = tempColumn;
    }
    return maxColumn;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    Row* tempRow = matrix.firstRow;
    while (tempRow != nullptr) {
        os << *tempRow;
        tempRow = tempRow->getNext();
    }
    os << "0:0;";
    return os;
}

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

int Row::getMaxRow() {
    if(next == nullptr)
        return rowNumber;
    else
        next->getMaxRow();
}

int Row::getMaxColumn() {
    return firstPoint->getMaxColumn();
}

std::ostream &operator<<(std::ostream &os, const Row &row) {
    os << "0:" << row.rowNumber + 1 << ";";
    Point* tempPoint = row.firstPoint;
    while (tempPoint != nullptr) {
        os << *tempPoint;
        tempPoint = tempPoint->getNext();
    }
    return os;
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

int Point::getMaxColumn() {
    if(next == nullptr)
        return column;
    else
        return next->getMaxColumn();
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << point.column + 1 << ":" << point.value << ";";
    return os;
}

std::istream &operator>>(std::istream &is, const Point &point) {
    is.ignore(':');
    is.ignore(';');
    is >> point.column >> point.value;
    return is;
}
