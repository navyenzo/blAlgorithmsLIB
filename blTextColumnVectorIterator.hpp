#ifndef BL_TEXTCOLUMNVECTORITERATOR_HPP
#define BL_TEXTCOLUMNVECTORITERATOR_HPP



//-------------------------------------------------------------------
// FILE:            blTextColumnVectorIterator.hpp
// CLASS:           blTextColumnVectorIterator
// BASE CLASS:      None
//
//
//
// PURPOSE:         Custom iterator useful in parsing serialized data
//                  from generic text-data streams (for ex. files) and
//                  turn it into a numeric matrix
//
//                  -- The iterator assumes that the text data is
//                     formatted as a single column vector so that
//                     it only contains one number per row, where
//                     each row is separated by the '\n' newline
//                     token
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
// NOTE: This class is defined within the blAlgorithmsLIB namespace
//-------------------------------------------------------------------
namespace blAlgorithmsLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

class blTextColumnVectorIterator
{
public: // Iterator traits



    using iterator_category = std::random_access_iterator_tag;
    using value_type = blNumberType;
    using difference_type = ptrdiff_t;
    using pointer = blNumberType*;
    using reference = blNumberType&;



public: // Constructors and destructor



    // No default constructor

    blTextColumnVectorIterator() = delete;



    // Constructor from two iterators

    blTextColumnVectorIterator(const blDataIteratorType& beginIter,
                               const blDataIteratorType& endIter);



    // Default copy constructor

    blTextColumnVectorIterator(const blTextColumnVectorIterator<blDataIteratorType,blNumberType>& textColumnVectorIterator) = default;



    // Destructor

    ~blTextColumnVectorIterator();



public: // Assignment operators



    // Default assignment operator

    blTextColumnVectorIterator<blDataIteratorType,blNumberType>&        operator=(const blTextColumnVectorIterator<blDataIteratorType,blNumberType>& textColumnVectorIterator) = default;



public: // Conversion operators



    // Operator to convert this class to bool

    operator bool()const
    {
        return !(m_iter == m_endIter);
    }



public: // Comparison operators



    bool                                                                operator==(const blTextColumnVectorIterator<blDataIteratorType,blNumberType>& stringColumnVectorIterator)const;
    bool                                                                operator!=(const blTextColumnVectorIterator<blDataIteratorType,blNumberType>& stringColumnVectorIterator)const;



public: // Access operators and functions



    const blNumberType&                                                 operator[](const ptrdiff_t& index);
    const blNumberType&                                                 operator()(const ptrdiff_t& index);
    const blNumberType&                                                 at(const ptrdiff_t& index);



public: // Reference and Dereference operators



    blNumberType*                                                       operator->();
    const blNumberType&                                                 operator*()const;



public: // Arithmetic operators



    blTextColumnVectorIterator<blDataIteratorType,blNumberType>&        operator+=(const ptrdiff_t& movement);
    blTextColumnVectorIterator<blDataIteratorType,blNumberType>&        operator-=(const ptrdiff_t& movement);
    blTextColumnVectorIterator<blDataIteratorType,blNumberType>&        operator++();
    blTextColumnVectorIterator<blDataIteratorType,blNumberType>&        operator--();
    blTextColumnVectorIterator<blDataIteratorType,blNumberType>         operator++(int);
    blTextColumnVectorIterator<blDataIteratorType,blNumberType>         operator--(int);
    blTextColumnVectorIterator<blDataIteratorType,blNumberType>         operator+(const ptrdiff_t& movement)const;
    blTextColumnVectorIterator<blDataIteratorType,blNumberType>         operator-(const ptrdiff_t& movement)const;



    // Operator used to "subtract"
    // two pointers (it gives the
    // distance)

    std::ptrdiff_t                                                      operator-(const blTextColumnVectorIterator<blDataIteratorType,blNumberType>& stringColumnVectorIterator)const;



public: // Public functions



    // Function used to manually
    // set the data iterators

    void                                                                setIterators(const blDataIteratorType& beginIter,
                                                                                     const blDataIteratorType& endIter);



    // Function used to calculate the total
    // number of rows in the provided serialized
    // data

    const int&                                                          calculateTotalNumberOfRows();



    // Functions used to get this class' members

    const int&                                                          getCurrentLine()const;
    const blDataIteratorType&                                           getBeginIter()const;
    const blDataIteratorType&                                           getEndIter()const;
    const blDataIteratorType&                                           getIter()const;
    const blNumberType&                                                 getNumber()const;
    const int&                                                          getTotalNumberOfLines()const;



private: // Private functions



    // Function used to convert the text
    // we're currently pointing to into
    // a number

    void                                                                convertToNumberFromCurrentPosition();



protected: // Protected variables



    // Begin and end iterators
    // used to know where the
    // given buffer begins and
    // ends

    blDataIteratorType                                                  m_beginIter;
    blDataIteratorType                                                  m_endIter;



    // The iterator used to move through
    // the buffer

    blDataIteratorType                                                  m_iter;



    // The converted number of where the
    // iterator is currently pointing at
    // in the buffer

    blNumberType                                                        m_number;



    //  Current line in the buffer

    int                                                                 m_currentLine;



    // Total number of data rows

    int                                                                 m_totalNumberOfLines;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructor from two iterators
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blTextColumnVectorIterator<blDataIteratorType,blNumberType>::blTextColumnVectorIterator(const blDataIteratorType& beginIter,
                                                                                   const blDataIteratorType& endIter)
{
    m_beginIter = beginIter;
    m_endIter = endIter;
    m_iter = m_beginIter;

    m_number = 0;

    m_currentLine = 0;

    calculateTotalNumberOfRows();

    convertToNumberFromCurrentPosition();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blTextColumnVectorIterator<blDataIteratorType,blNumberType>::~blTextColumnVectorIterator()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Comparison operators
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline bool blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator==(const blTextColumnVectorIterator<blDataIteratorType,blNumberType>& textMatrixIterator)const
{
    return (m_iter == textMatrixIterator.getIter());
}



template<typename blDataIteratorType,
         typename blNumberType>

inline bool blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator!=(const blTextColumnVectorIterator<blDataIteratorType,blNumberType>& textMatrixIterator)const
{
    return (m_iter != textMatrixIterator.getIter());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Access operators and functions
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator[](const ptrdiff_t& index)
{
    (*this) += index - m_currentLine;
    return m_number;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator()(const ptrdiff_t& index)
{
    (*this) += index - m_currentLine;
    return m_number;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(const ptrdiff_t& index)
{
    (*this) += index - m_currentLine;
    return m_number;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Reference and Dereference operators
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blNumberType* blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator->()
{
    return &m_number;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator*()const
{
    return m_number;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// += arithmetic operator
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blTextColumnVectorIterator<blDataIteratorType,blNumberType>& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator+=(const ptrdiff_t& movement)
{
    if(movement > 0)
    {
        int actualMovement = blAlgorithmsLIB::findBeginningOfNthDataRow(m_iter,m_endIter,'\n',false,movement,m_iter);

        if(actualMovement < movement)
            m_iter = m_endIter;

        m_currentLine += actualMovement;

        convertToNumberFromCurrentPosition();
    }
    else if(movement < 0)
    {
        int newRowToFind = m_currentLine + movement;

        if(newRowToFind < 0)
        {
            m_currentLine = 0;
            m_iter = m_beginIter;
        }
        else
        {
            m_currentLine = blAlgorithmsLIB::findBeginningOfNthDataRow(m_beginIter,m_endIter,'\n',false,newRowToFind,m_iter);
        }

        convertToNumberFromCurrentPosition();
    }

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// All other arithmetic operators that use the += operator
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blTextColumnVectorIterator<blDataIteratorType,blNumberType>& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator-=(const ptrdiff_t& movement)
{
    return this->operator+=(-movement);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blTextColumnVectorIterator<blDataIteratorType,blNumberType>& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator++()
{
    return this->operator+=(1);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blTextColumnVectorIterator<blDataIteratorType,blNumberType>& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator--()
{
    return this->operator+=(-1);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blTextColumnVectorIterator<blDataIteratorType,blNumberType> blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator++(int)
{
    auto temp(*this);

    operator+=(1);

    return temp;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blTextColumnVectorIterator<blDataIteratorType,blNumberType> blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator--(int)
{
    auto temp(*this);

    operator+=(-1);

    return temp;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blTextColumnVectorIterator<blDataIteratorType,blNumberType> blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator+(const ptrdiff_t& movement)const
{
    auto temp(*this);

    temp += movement;

    return temp;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blTextColumnVectorIterator<blDataIteratorType,blNumberType> blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator-(const ptrdiff_t& movement)const
{
    auto temp(*this);

    temp -= movement;

    return temp;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Operator used to "subtract" two iterators
// (it returns the distance between the iterators)
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline std::ptrdiff_t blTextColumnVectorIterator<blDataIteratorType,blNumberType>::operator-(const blTextColumnVectorIterator<blDataIteratorType,blNumberType>& stringColumnVectorIterator)const
{
    return (m_iter - stringColumnVectorIterator.getIter());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to manually set the data iterators
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline void blTextColumnVectorIterator<blDataIteratorType,blNumberType>::setIterators(const blDataIteratorType& beginIter,
                                                                                const blDataIteratorType& endIter)
{
    m_beginIter = beginIter;
    m_endIter = endIter;
    m_iter = m_beginIter;

    m_number = 0;

    m_currentLine = 0;

    calculateTotalNumberOfRows();

    convertToNumberFromCurrentPosition();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to calculate the total number of rows
// in the provided serialized data
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline const int& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::calculateTotalNumberOfRows()
{
    m_totalNumberOfLines = blAlgorithmsLIB::countDataRows(m_beginIter,
                                                          m_endIter,
                                                          '\n',
                                                          false);

    return m_totalNumberOfLines;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get the class' members
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline const int& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::getCurrentLine()const
{
    return m_currentLine;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blDataIteratorType& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::getBeginIter()const
{
    return m_beginIter;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blDataIteratorType& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::getEndIter()const
{
    return m_endIter;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blDataIteratorType& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::getIter()const
{
    return m_iter;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::getNumber()const
{
    return m_number;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const int& blTextColumnVectorIterator<blDataIteratorType,blNumberType>::getTotalNumberOfLines()const
{
    return m_totalNumberOfLines;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to convert the text we're currently
// pointing to into a number, this function is called
// internally everytime the iterator is moved to a different
// location in the text
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline void blTextColumnVectorIterator<blDataIteratorType,blNumberType>::convertToNumberFromCurrentPosition()
{
    convertToNumber(m_iter,m_endIter,'.',m_number,0);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following functor based on the previous one, assumes
// the string is an (n x 1) column vector of values, representing
// data points, where each data point is a matrix of data of
// size (rows x cols), the string is assumed to be formatted as
// follows:
//
// Line 1 -- Serial number (a number representing a signature/type)
// Line 2 -- rows
// Line 3 -- cols
// Line 4 - Line n -- The data points one matrix at a time
// NOTE:  If the matrix is a 2d matrix then the cols = 1, for 3d matrices
//        the cols > 1
//
// For example a (2xN) matrix would look like the following:
//
// 123454321 (some serial number)
// 2 (the rows in each data point)
// 1 (the columns in each data point, so this means each data point
//   is a single column vector
// 0,0
// 1,0
// 2,0
// 0,1
// 1,1
// 2,1
// 0,2
// 1,2
// 2,2
// 0,3
// ...
// 2,N
// End of file
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

class blTextColumnVectorIterator2 : public blTextColumnVectorIterator<blDataIteratorType,blNumberType>
{
public:

    // Iterator traits

    using iterator_category = std::random_access_iterator_tag;
    using value_type = blNumberType;
    using difference_type = ptrdiff_t;
    using pointer = blNumberType*;
    using reference = blNumberType&;



    blTextColumnVectorIterator2(const blDataIteratorType& beginIter,
                            const blDataIteratorType& endIter)
                            : blTextColumnVectorIterator<blDataIteratorType,blNumberType>(beginIter,endIter)
    {
        m_serialNumber = blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(0);

        m_rows = blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(1);
        m_cols = blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(2);

        m_totalNumberOfDataPointsPerRow  = std::max(this->m_totalNumberOfLines - 3,0) / m_rows;

        m_currentRow = 0;
        m_currentCol = 0;

        ++(*this);
    }



    blTextColumnVectorIterator2(const blTextColumnVectorIterator2<blDataIteratorType,blNumberType>& stringColumnVectorIterator2) = default;



    ~blTextColumnVectorIterator2()
    {
    }



    blTextColumnVectorIterator2<blDataIteratorType,blNumberType>&      operator=(const blTextColumnVectorIterator2<blDataIteratorType,blNumberType>& stringColumnVectorIterator2) = default;



    void                            setIterators(const blDataIteratorType& beginIter,
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



    // Let's override the arithmetic operators
    // to make this move like a row-major matrix

    blTextColumnVectorIterator2<blDataIteratorType,blNumberType>&       operator+=(const ptrdiff_t& movement)
    {
        int currentIndex = m_currentRow * m_totalNumberOfDataPointsPerRow + m_currentCol;
        int desiredIndex = currentIndex + movement;

        int desiredRow = desiredIndex / m_totalNumberOfDataPointsPerRow;
        int desiredCol = desiredIndex % m_totalNumberOfDataPointsPerRow;

        this->at(desiredRow,desiredCol);

        return (*this);
    }

    blTextColumnVectorIterator2<blDataIteratorType,blNumberType>&       operator-=(const ptrdiff_t& movement)
    {
        return this->operator+=(-movement);
    }

    blTextColumnVectorIterator2<blDataIteratorType,blNumberType>&       operator++()
    {
        return operator+=(1);
    }

    blTextColumnVectorIterator2<blDataIteratorType,blNumberType>&       operator--()
    {
        return operator+=(-1);
    }

    blTextColumnVectorIterator2<blDataIteratorType,blNumberType>        operator++(int)
    {
        auto temp(*this);

        operator+=(1);

        return temp;
    }

    blTextColumnVectorIterator2<blDataIteratorType,blNumberType>        operator--(int)
    {
        auto temp(*this);

        operator+=(-1);

        return temp;
    }

    blTextColumnVectorIterator2<blDataIteratorType,blNumberType>        operator+(const ptrdiff_t& movement)const
    {
        auto temp(*this);

        temp += movement;

        return temp;
    }

    blTextColumnVectorIterator2<blDataIteratorType,blNumberType>        operator-(const ptrdiff_t& movement)const
    {
        auto temp(*this);

        temp -= movement;

        return temp;
    }



    // Let's override the access operators so that
    // they access only the data points and not
    // the string header (serial number, rows, cols)



    const blNumberType&             operator[](const ptrdiff_t& index)
    {
        blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(index + 3);

        return this->m_number;
    }



    const blNumberType&             operator()(const ptrdiff_t& index)
    {
        blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(index + 3);

        return this->m_number;
    }



    const blNumberType&             operator()(const int& row,
                                               const int& col)
    {
        return this->at(row,col);
    }



    const blNumberType&             at(const ptrdiff_t& index)
    {
        blTextColumnVectorIterator<blDataIteratorType,blNumberType>::at(index + 3);

        return this->m_number;
    }



    const blNumberType&             at(const int& row,
                                       const int& col)
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



    const int&                      getSerialNumber()const
    {
        return m_serialNumber;
    }

    const int&                      getRows()const
    {
        return m_rows;
    }

    const int&                      getCols()const
    {
        return m_cols;
    }



    const int&                      getCurrentRow()const
    {
        return m_currentRow;
    }

    const int&                      getCurrentCol()const
    {
        return m_currentCol;
    }



    int                             getTotalNumberOfDataPointsPerRow()const
    {
        return m_totalNumberOfDataPointsPerRow;
    }



protected:

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
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_TEXTCOLUMNVECTORITERATOR_HPP
