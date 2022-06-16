#include <vector>
#include <iostream>
#include <cassert>
#include <functional>
#include<cmath>
using namespace std;

    class Matrix2D
    {
    public:
        uint32_t _cols;
        uint32_t _rows;
        vector<float> _vals;


    public:
        Matrix2D(uint32_t cols, uint32_t rows) //3 2
            : _cols(cols),            
            _rows(rows),
            _vals({})
        {
            _vals.resize(rows * cols, 0.0f);
        }

        Matrix2D()
             : _cols(0),
            _rows(0),
            _vals({})
        {
        }

   //done this
         float &at(uint32_t col, uint32_t row)    
        {
            return _vals[row * _cols + col];   
        }


//done this 
        Matrix2D negetive()
        {
            Matrix2D output(_cols, _rows);
            for (uint32_t y = 0; y < output._rows; y++)
                for (uint32_t x = 0; x < output._cols; x++)
                {
                    output.at(x, y) = -at(x, y);
                }
            return output;
        }

//done this
        Matrix2D multiply(Matrix2D& target)
        { 
            assert(_cols == target._rows);
            Matrix2D output(target._cols, _rows);
            for (uint32_t y = 0; y < output._rows; y++)
                for (uint32_t x = 0; x < output._cols; x++)
                {
                    float result = 0.0f;
                    for (uint32_t k = 0; k < _cols; k++)
                        result += at(k, y) * target.at(x, k);
                    output.at(x, y) = result;
                }
            return output;
        }
//done this 
        Matrix2D multiplyElements(Matrix2D& target)
        {
            assert(_rows == target._rows && _cols == target._cols);
            Matrix2D output(_cols, _rows);
            for (uint32_t y = 0; y < output._rows; y++)
                for (uint32_t x = 0; x < output._cols; x++)
                {
                    output.at(x, y) = at(x, y) * target.at(x, y);
                }
            return output;
        }

//donne thisss
        Matrix2D add(Matrix2D& target)
        {
            assert(_rows == target._rows && _cols == target._cols);
            Matrix2D output(_cols, _rows);
            for (uint32_t y = 0; y < output._rows; y++)
                for (uint32_t x = 0; x < output._cols; x++)
                {
                    output.at(x, y) = at(x, y) + target.at(x, y);
                }
            return output;
        }
//done this 
        Matrix2D applyFunction(function<float(const float&)> func)
        {
            Matrix2D output(_cols, _rows);
            for (uint32_t y = 0; y < output._rows; y++)
                for (uint32_t x = 0; x < output._cols; x++)
                {
                    output.at(x, y) = func(at(x, y));
                }
            return output;
        }
//done this 
        Matrix2D multiplyScaler(float s)
        {
            Matrix2D output(_cols, _rows);
            for (uint32_t y = 0; y < output._rows; y++)
                for (uint32_t x = 0; x < output._cols; x++)
                {
                    output.at(x, y) = at(x, y) * s;
                }
            return output;

        }
//done this
        Matrix2D addScaler(float s)
        {
            Matrix2D output(_cols, _rows);
            for (uint32_t y = 0; y < output._rows; y++)
                for (uint32_t x = 0; x < output._cols; x++)
                {
                    output.at(x, y) = at(x, y) + s;
                }
            return output;

        }
//done this
        Matrix2D transpose()
        {
            Matrix2D output(_rows, _cols);
            for (uint32_t y = 0; y < _rows; y++)
                for (uint32_t x = 0; x < _cols; x++)
                {
                    output.at(y, x) = at(x, y);
                }
            return output;
        }


       
    }; // class Matrix2D


