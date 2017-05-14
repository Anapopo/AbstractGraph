#pragma once
#include <iostream>
using namespace std;
class Triple
{
public:
    int row;
    int column;
    int value;

    Triple(int row = 0, int column = 0, int value = 0)
    {
        if (row >= 0 && column >= 0)
        {
            this->row = row;
            this->column = column;
            this->value = value;
        }
        else throw invalid_argument("row and column must be larger than 0!");
    }

    friend ostream& operator<<(ostream& out, Triple &t)
    {
        out << "(" << t.row << "," << t.column << "," << t.value << ")";
        return out;
    }

    bool operator==(Triple &t)
    {
        return this->row == t.row && this->column == t.column;
    }

    bool operator!=(Triple &t)
    {
        return !(*this == t);
    }

    bool operator>(Triple &t)
    {
        return this->row > t.row || this->row == t.row && this->column > t.column;
    }

    bool operator>=(Triple &t)
    {
        return this->row > t.row || this->row == t.row && this->column >= t.column;
    }

    bool operator<(Triple &t)
    {
        return this->row < t.row || this->row == t.row && this->column < t.column;
    }

    bool operator<=(Triple &t)
    {
        return this->row < t.row || this->row == t.row && this->column <= t.column;
    }

    Triple symmetry()
    {
        return Triple(this->column, this->row, this->value);
    }
};
