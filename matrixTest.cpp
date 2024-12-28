#include<iostream>
#include<vector>

using namespace std;


template <class T> // lets you use a type T provided
class matrix {
private:
    T** data_;
    int rows_ = 0;
    int cols_ = 0;
    
public:
    
    matrix(int rows, int cols) {
        rows_ = rows;
        cols_ = cols;
        data_ = new T*[rows];
        for(int i=0; i<rows; i++) {
            data_[i] = new T[cols];
        }

    }    
    matrix(int rows, int cols, T def) {
        rows_ = rows;
        cols_ = cols;
        data_ = new T*[rows];
        for(int i=0; i<rows; i++) {
            T* x = new T[cols];
            for(int j=0; j<cols; j++) {
                x[j] = def;
            }
            data_[i] = x;    
        }

    }

    matrix(int rows, int cols, T** data) {
        rows_ = rows;
        cols_ = cols;
        // data_ = data;
        memcpy(data_, data, rows*cols*sizeof(T));
    }


    matrix operator+(matrix<T> &mat2) {

        for (int i = 0; i < this->rows_; i++) {
            for (int j = 0; j < this->cols_; j++) {
                this->setCell(i,j,this->getCell(i,j) + mat2.getCell(i,j));
            }
        }

        return *this;
        
    }


    T getCell(int i, int j) {
        return this->data_[i][j];
    }

    void setCell(int i, int j, T val) {
        this->data_[i][j] = val;
    }

    pair<int, int> dimensions() {
        pair<int, int> x(rows_, cols_);
        return x;
    }

    int size() {
        return rows_*cols_;
    }

    // implement printing as an operator overloading on << with std output stream
    friend std::ostream& operator<<(std::ostream& os, matrix<T> mat) {
        pair<int, int> s = mat.dimensions();
        int r = s.first;
        int c = s.second;

        os << "{\n";
        for(int i=0; i<r; i++) {
            os << "\t{";
            for(int j=0; j<c; j++) {
                os << mat.getCell(i,j);
                if(j!=c-1) os << ", ";
            }
            os << "}";
            if(i!=r-1) os << ",\n";
        }
        os << "\n}";
        return os;
    }
};




int main()
{
    matrix<int> mat1(3,4,1);
    matrix<int> mat2(3,4,2);
    vector<int> vec;
    
    pair<int, int> matSize = mat1.dimensions();
    cout << matSize.first*matSize.second << endl;
    cout << mat1 << endl;
    cout << mat1 + mat2 << endl;

    return 0;
}
