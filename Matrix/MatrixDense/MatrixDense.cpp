#include <iostream>

using namespace std;

template <typename T=double>

class MatrixDense
{
    unsigned _m;
    unsigned _n;
    T* _data;

    public:
    MatrixDense (unsigned m, unsigned n): _m(m), _n(n)
    {
        _data = new T[_m * _n];
    }

    ~MatrixDense()
    {
        delete[] _data;
    }

    void Print()
    {
        cout<<"_m="<<_m<<" "<<endl<<"_n="<<_n<<" "<<endl;

        for (unsigned i = 0; i < _m; i++)
        {
            for (unsigned j = 0; j < _n; j++)
            {
                cout<<getElement(i,j)<<" ";
            }
            cout<<endl;
        }
    }

    void setElement(unsigned i, unsigned j, T value)
    {
        unsigned ind = j + i * _n;
        _data[ind] = value;
    }

    T getElement(unsigned i, unsigned j)
    {
        return _data[i + j * _n];
    }

    MatrixDense operator+ (const MatrixDense& m2)
    {
        MatrixDense res(_m*_n);
        for (int i=0; i<_m*_n; i++)
        {
            
        }
    }
};


int main()
{
    MatrixDense M(3.0,4.0);
    int I;
    int J;
    double Value;
    cin >> I >> J >> Value;
    M.setElement(I, J, Value);
    M.Print();
    return 0;
}