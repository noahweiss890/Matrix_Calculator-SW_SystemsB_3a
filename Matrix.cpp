#include <iostream>
#include <string.h>
#include <sstream>
#include "Matrix.hpp"

using namespace zich;

namespace zich {

    Matrix::Matrix(vector<double> vec, int rows, int cols) {
        if(vec.size() != rows * cols || rows < 0 || cols < 0) {
            throw invalid_argument("not a legal matrix!");
        }
        this->mat = vec;
        this->rows = rows;
        this->columns = cols;
    }

    vector<double> Matrix::getMat(){
        return this->mat;
    }

    int Matrix::getRows() {
        return this->rows;
    }

    int Matrix::getColumns() {
        return this->columns;
    }

    ostream& operator<<(ostream& os, const Matrix &mat) {
        for(unsigned long i = 0; i < mat.rows; i++) {
            for(unsigned long k = 0; k < mat.columns; k++) {
                if(k == 0) {
                    os << "[" << mat.mat[i * (unsigned long)mat.columns + k];
                }
                else {
                    os << " " << mat.mat[i * (unsigned long)mat.columns + k];
                }
            }
            os << "]" << endl;
        }
        return os;
    }

    istream& operator>>(istream& is, Matrix &mat) {
        mat.mat.clear();
        int rows = 0;
        int columns = 0;
        string str;
        getline(is, str);
        stringstream ss(str);
        string word;
        while(getline(ss, word, ' ')) {
            if(word[0] != '[') {
                throw invalid_argument("bad input! 1");
            }
            rows++;
            mat.mat.push_back(stod(word.substr(1)));
            columns++;
            while(getline(ss, word, ' ') && word.back() != ']' && (word.size() < 2 || word.substr(word.size()-2) != "],")) {
                mat.mat.push_back(stod(word));
                columns++;
            }
            if(word.back() == ']') {
                mat.mat.push_back(stod(word.substr(0, word.size()-1)));
            }
            else {
                mat.mat.push_back(stod(word.substr(0, word.size()-2)));
            }
            columns++;
        }
        mat.rows = rows;
        mat.columns = columns/rows;
        return is;
    }
    
    Matrix Matrix::operator-() const {
        vector<double> vec;
        for(unsigned long i  = 0; i < mat.size(); i++) {
            if(mat[i] == 0) {
                vec.push_back(0);
            }
            else {
                vec.push_back(-mat[i]);
            }
        }
        return Matrix(vec, rows, columns);
    }

    Matrix Matrix::operator+() const {
        vector<double> vec;
        for(unsigned long i  = 0; i < mat.size(); i++) {
            vec.push_back(mat[i]);
        }
        return Matrix(vec, rows, columns);
    }

    Matrix Matrix::operator++() {
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i]++;
        }
        return *this;
    }

    Matrix Matrix::operator++(int dummy_flag_for_postfix_increment) {
        Matrix copy = *this;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i]++;
        }
        return copy;
    }

    Matrix Matrix::operator--() {
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i]--;
        }
        return *this;
    }

    Matrix Matrix::operator--(int dummy_flag_for_postfix_decrement) {
        Matrix copy = *this;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i]--;
        }
        return copy;
    }

    void Matrix::operator*=(int n) {
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i] *= n;
        }
    }

    void Matrix::operator+=(int n) {
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i] += n;
        }
    }

    void Matrix::operator-=(int n) {
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i] -= n;
        }
    }

    void Matrix::operator+=(const Matrix &mat) {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i] += mat.mat[i];
        }
    }

    void Matrix::operator-=(const Matrix &mat) {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i] -= mat.mat[i];
        }
    }

    void Matrix::operator*=(const Matrix &mat) {
        if(this->columns != mat.rows) {
            throw invalid_argument("illegal matrix multiplication!");
        }
        Matrix res = *this * mat;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i] = res.mat[i];
        }
    }

    Matrix operator*(int n, const Matrix &mat) {
        vector<double> vec;
        for(unsigned long i = 0; i < mat.mat.size(); i++) {
            vec.push_back(mat.mat[i]*n);
        }
        return Matrix(vec, mat.rows, mat.columns);
    }

    Matrix Matrix::operator*(int n) {
        vector<double> vec;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            vec.push_back(this->mat[i]*n);
        }
        return Matrix(vec, this->rows, this->columns);
    }

    Matrix Matrix::operator+(const Matrix &mat) {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        vector<double> vec;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            vec.push_back(this->mat[i] + mat.mat[i]);
        }
        return Matrix(vec, this->rows, this->columns);
    }

    Matrix Matrix::operator-(const Matrix &mat) {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        vector<double> vec;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            vec.push_back(this->mat[i] - mat.mat[i]);
        }
        return Matrix(vec, this->rows, this->columns);
    }

    Matrix Matrix::operator*(const Matrix &mat) {
        if(this->columns != mat.rows) {
            throw invalid_argument("illegal matrix multiplication!");
        }
        vector<double> vec;
        double sum;
        for(unsigned long i = 0; i < this->rows; i++) {
            for(unsigned long j = 0; j < mat.columns; j++) {
                sum = 0;
                for(unsigned long k = 0; k < this->columns; k++) {
                    sum += this->mat[i * (unsigned long)this->columns + k] * mat.mat[k * (unsigned long)mat.columns + j];
                }
                vec.push_back(sum);
            }
        }
        return Matrix(vec, this->rows, mat.columns);
    }

    bool Matrix::operator<(const Matrix &mat) const {
        double sum1 = 0;
        double sum2 = 0;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            sum1 += this->mat[i];
        }
        for(unsigned long i = 0; i < mat.mat.size(); i++) {
            sum2 += mat.mat[i];
        }
        if(sum1 < sum2) {
            return true;
        }
        return false;
    }

    bool Matrix::operator>(const Matrix &mat) const {
        double sum1 = 0;
        double sum2 = 0;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            sum1 += this->mat[i];
        }
        for(unsigned long i = 0; i < mat.mat.size(); i++) {
            sum2 += mat.mat[i];
        }
        if(sum1 > sum2) {
            return true;
        }
        return false;
    }

    bool Matrix::operator<=(const Matrix &mat) const {
        double sum1 = 0;
        double sum2 = 0;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            sum1 += this->mat[i];
        }
        for(unsigned long i = 0; i < mat.mat.size(); i++) {
            sum2 += mat.mat[i];
        }
        if(sum1 <= sum2) {
            return true;
        }
        return false;
    }

    bool Matrix::operator>=(const Matrix &mat) const {
        double sum1 = 0;
        double sum2 = 0;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            sum1 += this->mat[i];
        }
        for(unsigned long i = 0; i < mat.mat.size(); i++) {
            sum2 += mat.mat[i];
        }
        if(sum1 >= sum2) {
            return true;
        }
        return false;
    }

    bool Matrix::operator==(const Matrix &mat) const {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            if(this->mat[i] != mat.mat[i]) {
                return false;
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix &mat) const {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        return !(this == &mat);
    }
}