#include <iostream>
#include <ostream>

template <typename T> class Matrix;
template<typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &_M)
{
    for(size_t i = 0; i < _M.get_rows(); i++)
    {
        for(size_t j = 0; j < _M.get_cols(); j++)
        {
            os << _M.M[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}



template<typename T>

class Matrix
{
private:
    T** M;
    unsigned rows;
    unsigned cols;
public:
    Matrix(); //without param
    ~Matrix(); // destructor
    Matrix(unsigned _n, unsigned _m); // with param
    Matrix(const Matrix  &_M); // copy-constructor
    T& operator()(unsigned row, unsigned col);
    T operator()(unsigned row, unsigned col ) const ;
    Matrix<T> &operator=(const Matrix<T> &_M);
    Matrix<T> operator+(const Matrix<T> &_M);
    Matrix<T> operator-(const Matrix<T> &_M);
    Matrix<T> operator*(const Matrix<T> &_M);
    friend std::ostream &operator<< <T> (std::ostream &os, const Matrix &_M);
    int get_rows() const;
    int get_cols() const;
    Matrix<T> transpose();
};

template<typename T>
T& Matrix<T>::operator()(unsigned i, unsigned j) 
{
    return M[i][j];
}
template<typename T>
T Matrix<T>::operator()(unsigned i, unsigned j) const 
{
    return M[i][j];
}

template<typename T>
Matrix<T>::Matrix()
{
    rows = cols  = 0;
    M = nullptr;
}

template<typename T>
Matrix<T>::Matrix(unsigned _m, unsigned _n)
{
    rows = _m;
    cols = _n;

    M = (T**) new T*[rows]; 

    for(int i = 0; i < rows; i++)
    {
        M[i] = (T*)new T[cols];
    }
    
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            M[i][j] = 0;
        }
    }
}
template<typename T>
Matrix<T>::Matrix(const Matrix<T> &_M)
{
    rows = _M.rows;
    cols = _M.cols;

    M = (T**) new T*[rows];

    for(int i = 0; i < rows; i++)
    {
        M[i] = (T*) new T[cols];
    }

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            M[i][j] = _M(i, j); // _M.M[i][j]
        }
    }
}



template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &_M)
{
    if(cols > 0)
    {
        for(int i = 0; i < rows; i++)
        {
            delete[] M[i];
        }
    }
    if(rows > 0)
    {
        delete[] M;
    }

    rows = _M.rows;
    cols = _M.cols;
    M = (T**) new T*[rows];
    for(int i = 0; i < rows; i++)
    {
        M[i] = (T*) new T[cols];
    }

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            M[i][j] = _M(i,j); //_M.M[i][j]
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::transpose()
{
    Matrix<T> N(cols, rows);
    for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < rows; j++) N.M[i][j] = M[j][i]; //N.M[i][j] = M.M[j][i];
    }
    return N;
}   

template<typename T>
Matrix<T>::~Matrix()
{
    if(cols > 0)
    {
        for(int i = 0; i < rows; i++)
        {
            delete[] M[i];
        }
    }
    if(rows > 0)
    {
        delete[] M;
    }
}
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &_M)
{
    try
    {
        if( (rows !=_M.rows) || (cols != _M.cols))
        {
            throw "Matrices have different sizes.";
        } 
        else
        {
            Matrix<T> S(rows,cols);
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols;j++)
                {
                    S.M[i][j] = M[i][j] + _M(i,j); // _M.M[i][j]
                }
            }
            return S;
        }

    }
    catch(const char* exception)
    {
        std::cerr << "Error: " << exception << '\n';
        return Matrix<int>(0,0);
    }
    
}
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &_M)
{
    try
    {
        if( (rows !=_M.rows) || (cols != _M.cols))
        {
            throw "Matrices have different sizes.";
        } 
        else
        {
            Matrix<T> S(rows,cols);
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols;j++)
                {
                    S.M[i][j] = M[i][j] - _M(i,j); // _M.M[i][j]
                }
            }
            return S;
        }

    }
    catch(const char* exception)
    {
        std::cerr << "Error: " << exception << '\n';
        return Matrix<int>(0,0);
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &_M)
{
    try
    {
        if(cols != _M.rows)
        {
            throw "the number of columns of the left matrix != the number of rows of the right one.";
        }
        
        Matrix<T> P(rows, _M.cols);
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < _M.cols ; j++)
            {
                for(int k = 0; k < cols; k++)
                {
                    P.M[i][j] += M[i][k] * _M.M[k][j];
                }
            }
        }
        return P; 
    }
    catch(const char* exception)
    {
        std::cerr << "Error: " << exception << "\n";
        return Matrix<int>(0,0);
    }
    
}



template<typename T>
int Matrix<T>::get_rows() const
{
    return rows;
}

template<typename T>
int Matrix<T>::get_cols() const
{
    return cols;
}


// частичная специализация для векторов

// template<typename T>
// class Matrix<std::vector<T>>
// {   
// private:
//     T** M;
//     unsigned cols;
//     unsigned rows; 
//     unsigned high;
// public:
//     Matrix(m,n,k)
//     {
//         rows = m;
//         cols = n;
//         M = (std::vector<T>**) new std::vector<T>*[rows]; 

//         for(int i = 0; i < rows; i++)
//         {
//             M[i] = (std::vector<T>*)new std::vector<T>[cols];
//         }

//         for(int i = 0; i < rows; i++)
//         {
//             for(int j = 0; j < cols; j++)
//             {
//                 M[i][j] = new std::vector<T>(high);
//                 for(int k = 0; k < high; k++)
//                 {
//                     M[i][j][k] = 0;
//                 }
//             }
//         }
//     }
//     ~Matrix()
//     {
//         if(high > 0)
//         {
//             for(int i = 0; i < rows; i++)
//             {
//                 for(int j = 0; j < cols; j++)
//                 {
//                     delete M[i][j];
//                 }
//             }
//         }
//         if(cols > 0)
//         {
//             for(int i = 0; i < rows; i++)
//             {
//                 delete[] M[i];
//             }
//         }
//         if(rows > 0)
//         {
//             delete[] M;
//         }
//     }



// };

