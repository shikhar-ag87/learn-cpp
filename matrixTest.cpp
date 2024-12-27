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

    matrix(int rows, int cols, const T** data) {
        rows_ = rows;
        cols_ = cols;
        // data_ = data;
        memcpy(data_, data, rows*cols*sizeof(T));
    }


    T getCell(int i, int j) {
        return data_[i][j];
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
    matrix<int> mat(3,4);
    vector<int> vec;
    
    pair<int, int> matSize = mat.dimensions();
    cout << matSize.first*matSize.second << endl;
    cout << mat << endl;

    return 0;
}
