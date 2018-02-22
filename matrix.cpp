//
// Created by as on 21.02.18.
//

#include "matrix.h"

int matrix::get(int rowNumber, int columnNumber) {
    row* tempRow = firstRow;
    while (true) {
        if (tempRow == nullptr || tempRow->getNumber() > rowNumber)
            return 0;
        if(tempRow->getNumber() == rowNumber)
            return tempRow->getColumn(columnNumber);
        tempRow = tempRow->getNext();
    }
}

int matrix::set(int rowNumber, int columnNumber, int value) {
    row* prevRow = nullptr;
    row* tempRow = firstRow;
    while (true) {
        row* newRow = nullptr;
        if(tempRow == nullptr || tempRow->getNumber() > rowNumber) {
            newRow = new row;
            if(prevRow == nullptr) {
                firstRow = tempRow;
            } else {
                prevRow->setNext(tempRow);
            }
            newRow->setNext(tempRow);
        } else if(tempRow->getNumber() == rowNumber) {
            newRow = tempRow;
        }
        if(newRow != nullptr)
            return newRow->setColumn(columnNumber, value);
        prevRow = tempRow;
        tempRow = prevRow->getNext();
    }
}

int row::getNumber() {
    return rowNumber;
}

row *row::getNext() {
    return next;
}

int row::getColumn(int columnNumber) {
    point* tempColumn = firstPoint;
    while (true) {
        if(tempColumn == nullptr || tempColumn->getColumn() > columnNumber)
            return 0;
        if(tempColumn->getColumn() == columnNumber)
            return tempColumn->getValue();
        tempColumn = tempColumn->getNext();
    }
}

void row::setNext(row *next) {
    row::next = next;
}

bool row::setColumn(int columnNumber, int value) {
    point* prevPoint = nullptr;
    point* tempPoint = firstPoint;
    while (true) {
        if(tempPoint == nullptr || tempPoint ->getColumn() > columnNumber) {
            if(value == 0)
                return (firstPoint != nullptr);
            point* newPoint = new point();
            newPoint->setValue(value);
            newPoint->setNext(tempPoint);
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

int point::getColumn() const {
    return column;
}

int point::getValue() const {
    return value;
}

point *point::getNext() const {
    return next;
}

void point::setValue(int value) {
    point::value = value;
}

void point::setNext(point *next) {
    point::next = next;
}
