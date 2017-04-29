#include <iostream>
#include <vector>
#include <math.h>
#include <sstream>

long double pi = acos(-1.0L);

template <class T> class mat {
  private:
    std::vector<T> data_;
    int cols_;
    int rows_;

  public:
    mat(int rows, int cols);
    mat(int rows, int cols, T value);
    ~mat();
    T at(int rows, int cols);
    void set(int rows, int cols, T value);
    void print();
    mat<T> prod(mat m);
    int cols();
    int rows();
    void addAt(int rows, int cols, T value);
    void id();
    mat<T> operator+(mat<T>&);
    void operator+=(mat<T>&);
    mat<T> operator-(mat<T>&);
    void operator-=(mat<T>&);
    mat<T> operator*(mat<T>&);


};



template<class T> inline std::ostream& operator<<(std::ostream& os, mat<T>& m){
      for (int i = 0; i < m.rows(); ++i) {
        std::cout << std::endl;
        for (int j = 0; j < m.cols(); ++j) {
            std::stringstream ss;
            ss << m.at(i,j);
            std::string str = ss.str();
            int len = str.length();
            int maxSpaces = 7; //TODO: Use max of matrix instead of a fixed value.
            int spaces = maxSpaces - len;
            while (spaces > 0) {
                os << " ";
                spaces--;
            }
            os << " " << m.at(i,j);
        }
    }
    os << std::endl;
}



template<typename T>
mat<T> mat<T>::operator+( mat<T>& b) {
    mat<T> res(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            res.set(i, j, at(i, j) + b.at(i, j));
        }
    }
    return res;
}

template<typename T>
void mat<T>::operator+=( mat<T>& b) {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            set(i, j, at(i, j) + b.at(i, j));
        }
    }
}

template<typename T>
mat<T> mat<T>::operator-( mat<T>& b) {
    mat<T> res(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            res.set(i, j, at(i, j) - b.at(i, j));
        }
    }
    return res;
}

template<typename T>
void mat<T>::operator-=( mat<T>& b) {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            set(i, j, at(i, j) - b.at(i, j));
        }
    }
}

template <class T> mat<T>::mat(int rows, int cols) {
    std::vector<T> tmp(cols * rows);
    data_ = tmp; //TODO: Does this take O(nm) time?
    rows_ = rows;
    cols_ = cols;
}


template <class T> mat<T>::mat(int rows, int cols, T value) {
    std::vector<T> tmp(cols * rows);
    data_ = tmp;
    rows_ = rows;
    cols_ = cols;
    for (int i = 0; i < rows_ * cols_; ++i) {
        data_[i] = value;
    }
}

template <class T> mat<T>::~mat() {
//delete(data_); //Throws double free, but why?
}

template <class T> void mat<T>::id() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (i == j) {
                set(i, j, 1);
            } else {
                set(i, j, 0);
            }
        }

    }
}

template <class T> void mat<T>::print() {
    for (int i = 0; i < rows_; ++i) {
        std::cout << std::endl;
        for (int j = 0; j < cols_; ++j) {
            std::stringstream ss;
            ss << data_[i * cols_ + j];
            std::string str = ss.str();
            int len = str.length();
            int maxSpaces = 7; //TODO: Use max of matrix instead of a fixed value.
            int spaces = maxSpaces - len;
            while (spaces > 0) {
                std::cout << " ";
                spaces--;
            }
            std::cout << " " << data_[i * cols_ + j];
        }
    }
    std::cout << std::endl;
}


template <class T> T mat<T>::at(int rows, int cols) {
    return data_[rows * cols_ + cols];
}


template <class T> void mat<T>::set(int rows, int cols, T value) {
    data_[rows * cols_ + cols] = value;
}


template<typename T>
mat<T> mat<T>::operator*( mat<T>& m) {
    int mr = m.rows();
    int mc = m.cols();
    if (cols_ != mr) {
        //ERROR. //TODO: Implement.
    }
    mat<T> res(rows_, mc, 0);

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < mc; ++j) {
            for (int k = 0; k < rows_; ++k) {
                res.addAt(i, j, at(i, k)*m.at(k, j));
            }
        }
    }

    return res;
}

template <class T> int mat<T>::cols() {
    return cols_;
}

template <class T> int mat<T>::rows() {
    return rows_;
}

template <class T> void mat<T>::addAt(int rows, int cols, T value) {
    data_[rows * cols_ + cols] += value;
}