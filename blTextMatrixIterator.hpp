#ifndef BL_TEXTMATRIXITERATOR_HPP
#define BL_TEXTMATRIXITERATOR_HPP



//-------------------------------------------------------------------
// FILE:            blTextMatrixIterator.hpp
// CLASS:           blTextMatrixIterator
// BASE CLASS:      None
//
//
//
// PURPOSE:         Based on blTextColumnVectorIterator, this class assumes
//                  the string is an (n x 1) column vector of values, representing
//                  data points, where each data point is a matrix of data of
//                  size (rows x cols), the string is assumed to be formatted as
//                  follows:
//
//                  Line 1 -- Serial number (a number representing a signature/type)
//                  Line 2 -- rows
//                  Line 3 -- cols
//                  Line 4 - Line n -- The data points one matrix at a time
//
//                  NOTE:  If the matrix is a 2d matrix then the cols = 1, for
//                         3d matrices the cols > 1
//
//                  -- For example a (2xN) matrix would look like the following:
//
//                     -- 123454321 (some serial number)
//                     -- 2 (the rows in each data point)
//                     -- 1 (the columns in each data point, so this means each
//                        data point is a single column vector
//                     -- 0,0
//                     -- 1,0
//                     -- 2,0
//                     -- 0,1
//                     -- 1,1
//                     -- 2,1
//                     -- 0,2
//                     -- 1,2
//                     -- 2,2
//                     -- 0,3
//                     -- ...
//                     -- 2,N
//                     -- End of file
//
//                  -- The iterator assumes that the data is formatted
//                     as text as a single column of values separated
//                     by a '\n' newline character
//
//                  -- This class and its functions are defined within
//                     the "blAlgorithmsLIB" namespace
//
//
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
//
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes needed for this file
//-------------------------------------------------------------------
#include "blTextColumnVectorIterator.hpp"
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blAlgorithmsLIB namespace
//-------------------------------------------------------------------
namespace blAlgorithmsLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

class blTextMatrixIterator : public blTextColumnVectorIterator<blDataIteratorType,blNumberType>
{
public:

    // Iterator traits

    using iterator_category = std::random_access_iterator_tag;
    using value_type = blNumberType;
    using difference_type = ptrdiff_t;
    using pointer = blNumberType*;
    using reference = blNumberType&;



public: // Constructors and destructor



    // No default constructor

    blTextMatrixIterator() = delete;



    // Constructor from two iterators

    blTextMatrixIterator(const blDataIteratorType& beginIter,
                         const blDataIteratorType& endIter);



    // Default copy constructor

    blTextMatrixIterator(const blTextMatrixIterator<blDataIteratorType,blNumberType>& stringColumnVectorIterator2) = default;



    // Destructor

    ~blTextMatrixIterator();



public: // Assignment operator



    // Default assignment operator

    blTextMatrixIterator<blDataIteratorType,blNumberType>&      operator=(const blTextMatrixIterator<blDataIteratorType,blNumberType>& stringColumnVectorIterator2) = default;



public: // Public functions



    // Overloaded function used to set
    // the begin/end iterators

    void                            setIterators(const blDataIteratorType& beginIter,
                                                 const blDataIteratorType& endIter);



    // Let's override the arithmetic operators
    // to make this move like a row-major matrix

    blTextMatrixIterator<blDataIteratorType,blNumberType>&       operator+=(const ptrdiff_t& movement);
    blTextMatrixIterator<blDataIteratorType,blNumberType>&       operator-=(const ptrdiff_t& movement);
    blTextMatrixIterator<blDataIteratorType,blNumberType>&       operator++();
    blTextMatrixIterator<blDataIteratorType,blNumberType>&       operator--();
    blTextMatrixIterator<blDataIteratorType,blNumberType>        operator++(int);
    blTextMatrixIterator<blDataIteratorType,blNumberType>        operator--(int);
    blTextMatrixIterator<blDataIteratorType,blNumberType>        operator+(const ptrdiff_t& movement)const;
    blTextMatrixIterator<blDataIteratorType,blNumberType>        operator-(const ptrdiff_t& movement)const;



    // Let's override the access operators so that
    // they access only the data points and not
    // the string header (serial number, rows, cols)

    const blNumberType&             operator[](const ptrdiff_t& index);
    const blNumberType&             operator()(const ptrdiff_t& index);
    const blNumberType&             operator()(const int& row,const int& col);
    const blNumberType&             at(const ptrdiff_t& index);
    const blNumberType&             at(const int& row,const int& col);



    // Functions used to get the string/stream header

    const int&                      getSerialNumber()const;
    const int&                      getRows()const;
    const int&                      getCols()const;
    const int&                      getCurrentRow()const;
    const int&                      getCurrentCol()const;
    const int&                      getTotalNumberOfDataPointsPerRow()const;



protected: // Protected variables



    // Serial number

    int                             m_serialNumber;



    // Data is represented as rows x cols

    int                             m_rows;
    int                             m_cols;



    // Total number of data points per row

    int                             m_totalNumberOfDataPointsPerRow;



    //  Current row and column in the buffer

    int                             m_currentRow;
    int                             m_currentCol;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blTextMatrixIterator<blDataIteratorType,blNumberType>::blTextMatrixIterator(const blDataIteratorType& beginIter,
                                                                                   const blDataIteratorType& endIter)
                                                                                   : blTextColumnVectorIterator<blDataIteratorType,blNumberType>(beginIter,
                                                                                                                                                 endIter)
{
    m_serialNumber = blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(0);

    m_rows = blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(1);
    m_cols = blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(2);

    m_totalNumberOfDataPointsPerRow  = std::max(this->m_totalNumberOfLines - 3,0) / m_rows;

    m_currentRow = 0;
    m_currentCol = 0;

    ++(*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blTextMatrixIterator<blDataIteratorType,blNumberType>::~blTextMatrixIterator()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Overloaded function used to set the begin/end iterators
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline void blTextMatrixIterator<blDataIteratorType,blNumberType>::setIterators(const blDataIteratorType& beginIter,
                                             const blDataIteratorType& endIter)
{
    blTextColumnVectorIterator<blDataIteratorType,blNumberType>::setIterators(beginIter,endIter);

    m_serialNumber = blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(0);

    m_rows = blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(1);
    m_cols = blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(2);

    m_totalNumberOfDataPointsPerRow  = std::max(this->m_totalNumberOfLines - 3,0) / m_rows;

    m_currentRow = 0;
    m_currentCol = 0;

    ++(*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Let's override the arithmetic operators
// to make this move like a row-major matrix
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blTextMatrixIterator<blDataIteratorType,blNumberType>& blTextMatrixIterator<blDataIteratorType,blNumberType>::operator+=(const ptrdiff_t& movement)
{
    int currentIndex = m_currentRow * m_totalNumberOfDataPointsPerRow + m_currentCol;
    int desiredIndex = currentIndex + movement;

    int desiredRow = desiredIndex / m_totalNumberOfDataPointsPerRow;
    int desiredCol = desiredIndex % m_totalNumberOfDataPointsPerRow;

    this->at(desiredRow,desiredCol);

    return (*this);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blTextMatrixIterator<blDataIteratorType,blNumberType>& blTextMatrixIterator<blDataIteratorType,blNumberType>::operator-=(const ptrdiff_t& movement)
{
    return this->operator+=(-movement);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blTextMatrixIterator<blDataIteratorType,blNumberType>& blTextMatrixIterator<blDataIteratorType,blNumberType>::operator++()
{
    return operator+=(1);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blTextMatrixIterator<blDataIteratorType,blNumberType>& blTextMatrixIterator<blDataIteratorType,blNumberType>::operator--()
{
    return operator+=(-1);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blTextMatrixIterator<blDataIteratorType,blNumberType> blTextMatrixIterator<blDataIteratorType,blNumberType>::operator++(int)
{
    auto temp(*this);

    operator+=(1);

    return temp;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blTextMatrixIterator<blDataIteratorType,blNumberType> blTextMatrixIterator<blDataIteratorType,blNumberType>::operator--(int)
{
    auto temp(*this);

    operator+=(-1);

    return temp;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blTextMatrixIterator<blDataIteratorType,blNumberType> blTextMatrixIterator<blDataIteratorType,blNumberType>::operator+(const ptrdiff_t& movement)const
{
    auto temp(*this);

    temp += movement;

    return temp;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blTextMatrixIterator<blDataIteratorType,blNumberType> blTextMatrixIterator<blDataIteratorType,blNumberType>::operator-(const ptrdiff_t& movement)const
{
    auto temp(*this);

    temp -= movement;

    return temp;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Let's override the access operators so that
// they access only the data points and not
// the string header (serial number, rows, cols)
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blTextMatrixIterator<blDataIteratorType,blNumberType>::operator[](const ptrdiff_t& index)
{
    blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(index + 3);

    return this->m_number;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blTextMatrixIterator<blDataIteratorType,blNumberType>::operator()(const ptrdiff_t& index)
{
    blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(index + 3);

    return this->m_number;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blTextMatrixIterator<blDataIteratorType,blNumberType>::operator()(const int& row,const int& col)
{
    return this->at(row,col);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blTextMatrixIterator<blDataIteratorType,blNumberType>::at(const ptrdiff_t& index)
{
    blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(index + 3);

    return this->m_number;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blTextMatrixIterator<blDataIteratorType,blNumberType>::at(const int& row,const int& col)
{
    // First we try to find
    // the correct line
    // in the buffer

    blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(row + this->m_rows * col + 3);



    // Then we update the
    // current row and column

    m_currentRow = (this->m_currentLine - 3) % m_rows;
    m_currentCol = (this->m_currentLine - 3) / m_rows;

    return this->m_number;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get the string/stream header
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline const int& blTextMatrixIterator<blDataIteratorType,blNumberType>::getSerialNumber()const
{
    return m_serialNumber;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const int& blTextMatrixIterator<blDataIteratorType,blNumberType>::getRows()const
{
    return m_rows;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const int& blTextMatrixIterator<blDataIteratorType,blNumberType>::getCols()const
{
    return m_cols;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const int& blTextMatrixIterator<blDataIteratorType,blNumberType>::getCurrentRow()const
{
    return m_currentRow;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const int& blTextMatrixIterator<blDataIteratorType,blNumberType>::getCurrentCol()const
{
    return m_currentCol;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const int& blTextMatrixIterator<blDataIteratorType,blNumberType>::getTotalNumberOfDataPointsPerRow()const
{
    return m_totalNumberOfDataPointsPerRow;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_TEXTMATRIXITERATOR_HPP
