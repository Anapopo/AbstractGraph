#pragma once
#include <iostream>
using namespace std;
#include <iomanip>
class Matrix
{
private:
    int rows;
    int columns;
    int **element;

    void init(int rows, int columns);
    void init(int rows, int columns, int x);

public:
    Matrix(int rows = 0); 
    Matrix(int rows, int columns);
    Matrix(int rows, int columns, int x);
    Matrix(int rows, int columns, int values[]);
    ~Matrix();

    friend ostream& operator<<(ostream& out, Matrix&);
    int get(int i, int j);
    void set(int i, int j, int x);
    bool exists(int x);
    bool contain(Matrix &mat);
    int getRows();
    int getColumns();
    void setRowsColumns(int rows, int columns);
    
    Matrix(Matrix &mat);
    Matrix& operator=(Matrix &mat);
    bool operator==(Matrix &mat);
    void operator+=(Matrix &mat);
    Matrix operator+(Matrix &mat);
    void operator*=(Matrix &mat);
    Matrix operator*(Matrix &mat);
    Matrix transpose();
    bool isTriangular(bool up);
    bool isSymmetric();
    int saddlePoint();
};

void Matrix::init(int rows, int columns)
{
    if (rows >= 0 && columns >= 0)
    {
        this->rows = rows;
        this->columns = columns;
        this->element = new int*[rows];
        for (int i = 0; i < rows; i++)
            this->element[i] = new int[columns];
    }
    else throw invalid_argument("rows or columns must be larger than 0!");
}

void Matrix::init(int rows, int columns, int x)
{
    this->init(rows, columns);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            this->element[i][j] = x;
}

Matrix::Matrix(int rows) { this->init(rows, rows); }

Matrix::Matrix(int rows, int columns) { this->init(rows, columns); }

Matrix::Matrix(int rows, int columns, int x) { this->init(rows, columns, x); }

Matrix::Matrix(int rows, int columns, int values[])
{
    this->init(rows, columns);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            this->element[i][j] = values[i * columns + j];
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
        delete this->element[i];
    delete this->element;
}

ostream& operator<<(ostream& out, Matrix &mat)
{
    out << "Matrix (" << mat.rows << "X" << mat.columns << ")" << endl;
    for (int i = 0; i < mat.rows; i++)
    {
        for (int j = 0; j < mat.columns; j++)
            out << setw(4) << mat.element[i][j];
        out << endl;
    }
    return out;
}

void Matrix::set(int i, int j, int x)
{
    if (i >= 0 && i < rows && j >= 0 && j < columns)
        this->element[i][j] = x;
    else throw out_of_range("i and j must be range from 0 to rows/columns");
}

int Matrix::get(int i, int j)
{   
    if (i >= 0 && i < rows && j >= 0 && j < columns)
        return this->element[i][j];
    throw out_of_range("can not find the specify i and j!");
}

void Matrix::setRowsColumns(int rows, int columns)
{
    if (rows > this->rows || columns > this->columns)
    {
        int rows_old = this->rows;
        int columns_old = this->columns;
        int **temp = this->element;
        this->init(rows, columns);
        for (int i = 0; i < rows_old; i++)
            for (int j = 0; j < columns_old; j++)
                this->element[i][j] = temp[i][j];

        for (int i = 0; i < rows_old; i++)
            delete temp[i];
        delete temp;
    }
}

int Matrix::getRows() { return this->rows; }

int Matrix::getColumns() { return this->columns; }

Matrix::Matrix(Matrix &mat)
{
    this->init(mat.getRows(), mat.getColumns());
    for (int i = 0; i < mat.getRows(); i++)
        for (int j = 0; j < mat.getColumns(); j++)
            this->element[i][j] = mat.get(i, j);
}

Matrix& Matrix::operator=(Matrix &mat)
{
    if (this != &mat)
    {
        this->~Matrix();
        this->init(mat.getRows(), mat.getColumns());
        for (int i = 0; i < mat.getRows(); i++)
            for (int j = 0; j < mat.getColumns(); j++)
                this->element[i][j] = mat.get(i, j);
    }
    return *this;
}

bool Matrix::operator==(Matrix &mat)
{   
    if (this->rows != mat.getRows() || this->columns != mat.getColumns())
        return false;
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            if (this->element[i][j] != mat.get(i, j))
                return false;
    return true;
}

void Matrix::operator+=(Matrix &mat)
{
    if (this->rows == mat.getRows() && this->columns == mat.getColumns())
    {
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->columns; j++)
                this->element[i][j] += mat.get(i,j);
    }
    else throw invalid_argument("The specify matrix's rows/columns must be the same as this");
}

Matrix Matrix::operator+(Matrix &mat)
{
    if (this->rows == mat.getRows() && this->columns == mat.getColumns())
    {
        Matrix temp(*this);
        temp += mat;
        return temp;
    }
    else throw invalid_argument("The specify matrix's rows/columns must be the same as this");
}

void Matrix::operator*=(Matrix &mat)
{
    if (this->columns == mat.getRows())
    {   
        Matrix temp(this->rows, mat.getColumns());
        
        for (int i = 0; i < this->rows; i++)
        {
            for (int k = 0; k < mat.getColumns(); k++)
            {
                int sum = 0;
                for (int j = 0; j < mat.getRows(); j++)
                    sum += this->element[i][j] * mat.get(j, k);
                
                temp.set(i, k, sum);
            }
        }

        this->setRowsColumns(temp.getRows(), temp.getColumns());
        for (int x = 0; x < this->rows; x++)
            for (int y = 0; y < this->columns; y++)
                this->element[x][y] = temp.get(x, y);
        

    }
    else throw invalid_argument("The specify matrix error");
}

Matrix Matrix::operator*(Matrix &mat)
{
    if (this->columns == mat.getRows())
    {
        Matrix temp(this->rows, mat.getColumns());

        for (int i = 0; i < this->rows; i++)
        {
            for (int k = 0; k < mat.getColumns(); k++)
            {
                int sum = 0;
                for (int j = 0; j < mat.getRows(); j++)
                    sum += this->element[i][j] * mat.get(j, k);
                temp.set(i, k, sum);
            }
        }
        return temp;
    }
    else throw invalid_argument("The specify matrix error");
}

bool Matrix::exists(int x)
{    
    bool flag = false;
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
        {
            if (this->element[i][j] == x)
            {
                flag = true;
                break;
            }
        }
    return flag;        
}

bool Matrix::contain(Matrix &mat)
{
    bool flag = true;
    for (int i = 0; i < mat.getRows(); i++)
        for (int j = i + 1; j < mat.getColumns(); j++)
            if (!this->exists(mat.get(i, j)))
                flag = false;
    return flag;
}

Matrix Matrix::transpose()
{
    Matrix temp(this->columns, this->rows);

    for (int i = 0; i < temp.getRows(); i++)
        for (int j = 0; j < temp.getColumns(); j++)
            temp.set(i, j, this->element[j][i]);
    return temp;
}

bool Matrix::isTriangular(bool up)
{
    for (int i = 0; i < this->rows; i++)
        for (int j = (up ? i : 0); j < (up ? this->columns : i + 1); j++)
            if (!this->element[i][j])
                return false;
    return true;
}

bool Matrix::isSymmetric()
{
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
        {
            if (i == j) continue;
            if (this->element[i][j] != this->element[j][i])
                return false;
        }
    return true;
}

int Matrix::saddlePoint()
{   
    int flag;
    for (int i = 0; i < this->rows; i++)
    {   
        int rows_min = this->element[i][0];
        int rows_min_j = 0;
        for (int j = 1; j < this->columns; j++)
        {
            if (this->element[i][j] < this->element[i][rows_min_j])
            {
                rows_min_j = j;
                rows_min = this->element[i][j];
            }    
        }
        
        flag = 1;
        for (int k = 0; k < this->rows; k++)
        {
            if (this->element[k][rows_min_j] > rows_min)
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {   
            cout << "saddlePoint(i,j)=" << rows_min << ",i=" << i << ",j=" << rows_min_j << "." << endl;
            return rows_min;
        }
    }
    return -1;    
}
