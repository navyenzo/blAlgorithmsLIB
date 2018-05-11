#ifndef BL_CSVMATRIXITERATOR_HPP
#define BL_CSVMATRIXITERATOR_HPP



//-------------------------------------------------------------------
// FILE:            blCSVMatrixIterator.hpp
// CLASS:           blCSVMatrixIterator
// BASE CLASS:      None
//
//
//
// PURPOSE:         Custom iterator useful in parsing data from csv files
//                  and making it addressable like a numeric matrix
//
//                  -- The iterator assumes that the provided csv data is
//                     formatted such that it contains only valid numbers
//                     and if not it interprets that non-valid number as a
//                     zero
//
//                  -- The iterator assumes that the csv data has the same
//                     number of columns for every row, but it also provides
//                     a function that lets a user check whether that is true
//
//                  -- The iterator skips over empty row or empty columns
//
//                     -- If it finds two or more Row Tokens or Column Tokens
//                        next to each other it does not count that as a Row
//                        or as a column, it just skips over it
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
#include <iterator>
#include <string>
#include <vector>
#include <cstddef>
#include <iostream>
#include <atomic>
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

class blCSVMatrixIterator
{
public: // Iterator traits



    using iterator_category = std::random_access_iterator_tag;
    using value_type = blNumberType;
    using difference_type = std::ptrdiff_t;
    using pointer = blNumberType*;
    using reference = blNumberType&;



public: // Constructors and destructor



    // No default constructor

    blCSVMatrixIterator() = delete;



    // Constructor from two iterators
    // and row and column tokens

    blCSVMatrixIterator(const blDataIteratorType& beginIter,
                        const blDataIteratorType& endIter,
                        const std::string rowTokens = ";\r\n",
                        const std::string colTokens = " ,",
                        const blAdvancingIteratorMethod& advancingIteratorMethod = blAlgorithmsLIB::ROW_MAJOR);



    // Default copy constructor

    blCSVMatrixIterator(const blCSVMatrixIterator<blDataIteratorType,blNumberType>& csvMatrixIterator) = default;



    // Destructor

    ~blCSVMatrixIterator();



public: // Assignment operators



    // Default assignment operator

    blCSVMatrixIterator<blDataIteratorType,blNumberType>&               operator=(const blCSVMatrixIterator<blDataIteratorType,blNumberType>& csvMatrixIterator) = default;



public: // Conversion operators



    // Operator to convert this class to bool

    operator bool()const
    {
        return !(m_iter == m_endIter);
    }



public: // Comparison operators



    bool                                                                operator==(const blCSVMatrixIterator<blDataIteratorType,blNumberType>& csvMatrixIterator)const;
    bool                                                                operator!=(const blCSVMatrixIterator<blDataIteratorType,blNumberType>& csvMatrixIterator)const;



public: // Access operators and functions



    const blNumberType&                                                 operator[](const std::ptrdiff_t& index);
    const blNumberType&                                                 operator()(const std::ptrdiff_t& index);
    const blNumberType&                                                 at(const std::ptrdiff_t& index);



    const blNumberType&                                                 operator()(const std::ptrdiff_t& rowIndex,
                                                                                   const std::ptrdiff_t& colIndex);

    const blNumberType&                                                 at(const std::ptrdiff_t& rowIndex,
                                                                           const std::ptrdiff_t& colIndex);



public: // Reference and Dereference operators



    blNumberType*                                                       operator->();
    const blNumberType&                                                 operator*()const;



public: // Arithmetic operators



    blCSVMatrixIterator<blDataIteratorType,blNumberType>&               operator+=(const std::ptrdiff_t& movement);
    blCSVMatrixIterator<blDataIteratorType,blNumberType>&               operator-=(const std::ptrdiff_t& movement);
    blCSVMatrixIterator<blDataIteratorType,blNumberType>&               operator++();
    blCSVMatrixIterator<blDataIteratorType,blNumberType>&               operator--();
    blCSVMatrixIterator<blDataIteratorType,blNumberType>                operator++(int);
    blCSVMatrixIterator<blDataIteratorType,blNumberType>                operator--(int);
    blCSVMatrixIterator<blDataIteratorType,blNumberType>                operator+(const std::ptrdiff_t& movement)const;
    blCSVMatrixIterator<blDataIteratorType,blNumberType>                operator-(const std::ptrdiff_t& movement)const;



    // Operator used to "subtract"
    // two pointers (it gives the
    // distance)

    std::ptrdiff_t                                                      operator-(const blCSVMatrixIterator<blDataIteratorType,blNumberType>& csvMatrixIterator)const;



public: // Public functions



    // Function used to move the iterator by a
    // user specified amount
    // The iterator is moved "movement" data points
    // from its current position in the csv data
    // buffer

    void                                                                moveIterator(std::ptrdiff_t movement,
                                                                                     const blAdvancingIteratorMethod& advancingIteratorMethod);



    // Functions used to manually
    // set the data iterators and
    // the Row and Column Token

    void                                                                setRowTokens(const std::string& rowTokens);

    void                                                                setColTokens(const std::string& colTokens);

    void                                                                setRowAndColTokens(const std::string& rowTokens,
                                                                                           const std::string& colTokens);

    void                                                                setIterators(const blDataIteratorType& beginIter,
                                                                                     const blDataIteratorType& endIter);

    void                                                                setIterators(const blDataIteratorType& beginIter,
                                                                                     const blDataIteratorType& endIter,
                                                                                     const std::string& rowTokens,
                                                                                     const std::string& colTokens);



    // Function used to calculate the total
    // number of rows in the provided serialized
    // data

    void                                                                calculateTotalNumberOfRowsAndColumns();



    // Functions used to get this class' members

    const blDataIteratorType&                                           getBeginIter()const;
    const blDataIteratorType&                                           getEndIter()const;
    const blDataIteratorType&                                           getIter()const;
    const blDataIteratorType&                                           getFirstDataPointIter()const;
    const blNumberType&                                                 getNumber()const;

    const  std::ptrdiff_t&                                              rows()const;
    const  std::ptrdiff_t&                                              cols()const;

    const std::size_t&                                                  size()const;
    const std::size_t&                                                  length()const;

    const  std::ptrdiff_t&                                              rowIndex()const;
    const  std::ptrdiff_t&                                              colIndex()const;

    const std::string&                                                  rowTokens()const;
    const std::string&                                                  colTokens()const;

    const std::vector<std::string>&                                     getColumnNames()const;



    // Functions used to set/get
    // the advancing iterator method

    const blAdvancingIteratorMethod&                                    getAdvancingIteratorMethod()const;
    void                                                                setAdvancingIteratorMethod(const blAdvancingIteratorMethod& advancingIteratorMethod);



    // Functions used to move the current
    // iterator position to the beginning
    // or to the end

    blCSVMatrixIterator<blDataIteratorType,blNumberType>&               moveToTheBeginning();
    blCSVMatrixIterator<blDataIteratorType,blNumberType>&               moveToTheEnd();



    // Functions used to get the
    // begin/end iterators so that
    // this can be used in stl
    // algorithms

    blCSVMatrixIterator<blDataIteratorType,blNumberType>                begin()const;
    blCSVMatrixIterator<blDataIteratorType,blNumberType>                end()const;

    blCSVMatrixIterator<const blDataIteratorType,blNumberType>          cbegin()const;
    blCSVMatrixIterator<const blDataIteratorType,blNumberType>          cend()const;



private: // Static functions/variables/constants



    // Constant string used to find
    // a "digit" or characters that
    // would be used for digits

    const static std::string                                            s_digits;



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



    // Iterator pointing to the place
    // in the csv data where the first
    // data point starts

    blDataIteratorType                                                  m_firstDataPointIter;



    // The converted number of where the
    // iterator is currently pointing at
    // in the buffer

    blNumberType                                                        m_number;



    // Current row and column indexes
    // of where in the csv matrix data
    // the iterator is pointing at as well
    // as data point index when treated
    // as a 1-d array

    std::ptrdiff_t                                                      m_rowIndex;
    std::ptrdiff_t                                                      m_colIndex;
    std::ptrdiff_t                                                      m_dataIndex;



    // Total number of data rows
    // and columns per row in the
    // csv data

    std::ptrdiff_t                                                      m_rows;
    std::ptrdiff_t                                                      m_cols;



    // Total size of matrix (rows * cols)

    std::size_t                                                         m_size;



    // Tokens used to look for rows
    // and columns in the csv data

    std::string                                                         m_rowTokens;
    std::string                                                         m_colTokens;
    std::string                                                         m_rowAndColTokensCombined;



    // Variable used to decide how to advance
    // the iterator

    blAdvancingIteratorMethod                                           m_advancingIteratorMethod;



    // Vector of strings holding
    // the column names

    std::vector<std::string>                                            m_columnNames;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Static constants definitions
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

const std::string blCSVMatrixIterator<blDataIteratorType,blNumberType>::s_digits = "-+.0123456789";
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructor from two iterators and token strings
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<blDataIteratorType,blNumberType>::blCSVMatrixIterator(const blDataIteratorType& beginIter,
                                                                                 const blDataIteratorType& endIter,
                                                                                 const std::string rowTokens,
                                                                                 const std::string colTokens,
                                                                                 const blAdvancingIteratorMethod& advancingIteratorMethod)
{
    setIterators(beginIter,
                 endIter,
                 rowTokens,
                 colTokens);

    setAdvancingIteratorMethod(advancingIteratorMethod);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<blDataIteratorType,blNumberType>::~blCSVMatrixIterator()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Comparison operators
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline bool blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator==(const blCSVMatrixIterator<blDataIteratorType,blNumberType>& csvMatrixIterator)const
{
    return (m_iter == csvMatrixIterator.getIter());
}



template<typename blDataIteratorType,
         typename blNumberType>

inline bool blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator!=(const blCSVMatrixIterator<blDataIteratorType,blNumberType>& csvMatrixIterator)const
{
    return (m_iter != csvMatrixIterator.getIter());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Access operators and functions
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator[](const std::ptrdiff_t& index)
{
    moveIterator(index - m_dataIndex,m_advancingIteratorMethod);
    return m_number;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator()(const std::ptrdiff_t& index)
{
    moveIterator(index - m_dataIndex,m_advancingIteratorMethod);
    return m_number;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blCSVMatrixIterator<blDataIteratorType,blNumberType>::at(const std::ptrdiff_t& index)
{
    moveIterator(index - m_dataIndex,m_advancingIteratorMethod);
    return m_number;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator()(const std::ptrdiff_t& rowIndex,
                                                                                            const std::ptrdiff_t& colIndex)
{
    std::ptrdiff_t index = rowIndex * m_cols + colIndex;
    moveIterator(index - m_dataIndex,ROW_MAJOR);
    return m_number;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blCSVMatrixIterator<blDataIteratorType,blNumberType>::at(const std::ptrdiff_t& rowIndex,
                                                                                    const std::ptrdiff_t& colIndex)
{
    std::ptrdiff_t index = rowIndex * m_cols + colIndex;
    moveIterator(index - m_dataIndex,ROW_MAJOR);
    return m_number;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Reference and Dereference operators
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blNumberType* blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator->()
{
    return &m_number;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator*()const
{
    return m_number;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to manually set the data iterators and
// the token strings
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline void blCSVMatrixIterator<blDataIteratorType,blNumberType>::setIterators(const blDataIteratorType& beginIter,
                                                                               const blDataIteratorType& endIter,
                                                                               const std::string& rowTokens,
                                                                               const std::string& colTokens)
{
    m_beginIter = beginIter;
    m_endIter = endIter;
    m_iter = m_beginIter;
    m_firstDataPointIter = m_beginIter;



    m_rowTokens = rowTokens;
    m_colTokens = colTokens;
    m_rowAndColTokensCombined = m_rowTokens + m_colTokens;



    m_number = 0;



    calculateTotalNumberOfRowsAndColumns();

    convertToNumberFromCurrentPosition();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to manually set the data iterators and
// token strings
//-------------------------------------------------------------------
template<typename blDataIteratorType,
          typename blNumberType>

inline void blCSVMatrixIterator<blDataIteratorType,blNumberType>::setRowTokens(const std::string& rowTokens)
{
    setIterators(m_beginIter,
                 m_endIter,
                 rowTokens,
                 m_colTokens);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline void blCSVMatrixIterator<blDataIteratorType,blNumberType>::setColTokens(const std::string& colTokens)
{
    setIterators(m_beginIter,
                 m_endIter,
                 m_rowTokens,
                 colTokens);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline void blCSVMatrixIterator<blDataIteratorType,blNumberType>::setRowAndColTokens(const std::string& rowTokens,
                                                                                     const std::string& colTokens)
{
    setIterators(m_beginIter,
                 m_endIter,
                 rowTokens,
                 colTokens);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline void blCSVMatrixIterator<blDataIteratorType,blNumberType>::setIterators(const blDataIteratorType& beginIter,
                                                                               const blDataIteratorType& endIter)
{
    setIterators(beginIter,
                 endIter,
                 m_rowTokens,
                 m_colTokens);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to advance the iterator
// in a column-major way
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline void blCSVMatrixIterator<blDataIteratorType,blNumberType>::moveIterator(std::ptrdiff_t movement,
                                                                               const blAdvancingIteratorMethod& advancingIteratorMethod)
{
    // If we need to move in a column major
    // way we need to change the movement

    if(advancingIteratorMethod == COL_MAJOR ||
       advancingIteratorMethod == COL_PAGE_MAJOR)
    {
        // First we calculate the current index
        // in terms of column major counting

        std::ptrdiff_t dataIndex = m_colIndex * m_rows + m_rowIndex;
        dataIndex += movement;

        if(dataIndex < 0)
        {
            m_iter = m_firstDataPointIter;
            m_rowIndex = 0;
            m_colIndex = 0;
            m_dataIndex = 0;

            return;
        }
        else if(dataIndex >= m_size)
        {
            m_iter = m_endIter;
            m_rowIndex = m_rows;
            m_colIndex = m_cols;
            m_dataIndex = m_size;

            return;
        }

        std::ptrdiff_t newColIndex = dataIndex / m_rows;
        std::ptrdiff_t newRowIndex = dataIndex % m_rows;

        movement = (newRowIndex * m_cols + newColIndex) - m_dataIndex;
    }



    if(movement > 0)
    {
        int actualMovement = findBeginningOfNthDataPoint(m_iter,
                                                         m_endIter,
                                                         m_rowAndColTokensCombined.begin(),
                                                         m_rowAndColTokensCombined.end(),
                                                         false,
                                                         movement,
                                                         m_iter);

        if(actualMovement < movement)
            m_iter = m_endIter;

        m_dataIndex += actualMovement;
        m_rowIndex = m_dataIndex / m_cols;
        m_colIndex = m_dataIndex % m_cols;

        convertToNumberFromCurrentPosition();
    }
    else if(movement < 0)
    {
        int newDataPointToFind = m_dataIndex + movement;



        if(newDataPointToFind < 0)
        {
            m_dataIndex = 0;
            m_rowIndex = 0;
            m_colIndex = 0;
            m_iter = m_firstDataPointIter;
        }
        else
        {
            m_dataIndex = findBeginningOfNthDataPoint(m_firstDataPointIter,
                                                      m_endIter,
                                                      m_rowAndColTokensCombined.begin(),
                                                      m_rowAndColTokensCombined.end(),
                                                      false,
                                                      newDataPointToFind,
                                                      m_iter);

            m_rowIndex = m_dataIndex / m_cols;
            m_colIndex = m_dataIndex % m_cols;
        }



        convertToNumberFromCurrentPosition();
    }



    return;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to calculate the total number of rows
// in the provided csv data as well as the number of
// columns per row
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline void blCSVMatrixIterator<blDataIteratorType,blNumberType>::calculateTotalNumberOfRowsAndColumns()
{
    // The first row of the csv file
    // might contain headers instead
    // of numerical data, therefore we
    // search for the first row that
    // contains purely numerical data

    auto rowBeginIter = m_beginIter;
    auto rowEndIter = m_beginIter;
    auto previousRowBeginIter = m_beginIter;

    std::string purelyNumericalRowTokens = s_digits;
    purelyNumericalRowTokens += m_colTokens;

    int currentRowIndex = 0;



    while(rowBeginIter != m_endIter &&
          rowEndIter != m_endIter)
    {
        // Here we search for the next data row

        blAlgorithmsLIB::findBeginAndEndOfNthDataPoint(previousRowBeginIter,
                                                       m_endIter,
                                                       m_rowTokens.begin(),
                                                       m_rowTokens.end(),
                                                       false,
                                                       0,
                                                       rowBeginIter,
                                                       rowEndIter);



        // We then check whether this newly
        // found data row contains any non
        // numeric characters

        auto firstNonNumericalIter = blAlgorithmsLIB::find_first_not_of(rowBeginIter,rowEndIter,purelyNumericalRowTokens.begin(),purelyNumericalRowTokens.end(),0);


        if(firstNonNumericalIter == rowEndIter)
        {
            // This means we found our first
            // data row containing only numbers

            m_firstDataPointIter = rowBeginIter;
            break;
        }
        else
        {
            // This means the row we found contains
            // non numerical characters in it, so
            // we continue to the next data row

            previousRowBeginIter = rowEndIter;

            if(rowEndIter != m_endIter)
                ++previousRowBeginIter;

            m_firstDataPointIter = m_endIter;
        }

        ++currentRowIndex;
    }



    // If we didn't find a purely numerical
    // data row, then we set everything to
    // zero and quit

    if(m_firstDataPointIter == m_endIter)
        m_rows = 0;
    else
    {
        // We then count the number
        // of data rows

        m_rows = blAlgorithmsLIB::countDataRows(m_firstDataPointIter,
                                                m_endIter,
                                                m_rowTokens.begin(),
                                                m_rowTokens.end(),
                                                false);
    }



    // We assume the csv is properly formatted
    // to represent a matrix and therefore
    // only use the first row to count how many
    // columns there are per each row

    // NOTE:  We DO NOT count empty columns where in the
    //        provided csv we have two or more following
    //        column tokens (for ex. "3,,4,4,5" would be
    //        4 columns and not 5

    if(m_rows <= 0)
    {
        m_cols = 0;
        m_size = 0;
        m_rowIndex = 0;
        m_colIndex = 0;
        m_dataIndex = 0;
        m_columnNames.clear();
        m_iter = m_endIter;
    }
    else
    {
        // We set the current iterator to point
        // to the first data point

        m_iter = m_firstDataPointIter;

        m_rowIndex = 0;
        m_colIndex = 0;
        m_dataIndex = 0;



        // We then find the beginning and end of the
        // first data row

        blAlgorithmsLIB::findBeginAndEndOfNthDataPoint(m_firstDataPointIter,
                                                       m_endIter,
                                                       m_rowTokens.begin(),
                                                       m_rowTokens.end(),
                                                       false,
                                                       0,
                                                       rowBeginIter,
                                                       rowEndIter);



        // We then count the number of columns
        // in the first row and record that as
        // the number of columns per row without
        // whether that's true for all the rows
        // in the csv data

        m_cols = blAlgorithmsLIB::countDataRows(rowBeginIter,
                                                rowEndIter,
                                                m_colTokens.begin(),
                                                m_colTokens.end(),
                                                false);



        m_size = m_cols * m_rows;



        // We try to get the names
        // of each column by parsing
        // the data before the first
        // data point

        m_columnNames.clear();

        std::ptrdiff_t numberOfColumnNames = blAlgorithmsLIB::countDataRows(m_beginIter,
                                                                            m_firstDataPointIter,
                                                                            m_colTokens.begin(),
                                                                            m_colTokens.end(),
                                                                            false);

        auto columnNameBeginIter = m_beginIter;
        auto columnNameEndIter = m_beginIter;

        for(int i = 0; i < numberOfColumnNames && i < m_cols; ++i)
        {
            blAlgorithmsLIB::findBeginAndEndOfNthDataPoint(m_beginIter,
                                                           m_firstDataPointIter,
                                                           m_rowAndColTokensCombined.begin(),
                                                           m_rowAndColTokensCombined.end(),
                                                           false,
                                                           i,
                                                           columnNameBeginIter,
                                                           columnNameEndIter);

            m_columnNames.push_back(std::string(columnNameBeginIter,columnNameEndIter));
        }
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get the class' members
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline const blDataIteratorType& blCSVMatrixIterator<blDataIteratorType,blNumberType>::getBeginIter()const
{
    return m_beginIter;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blDataIteratorType& blCSVMatrixIterator<blDataIteratorType,blNumberType>::getEndIter()const
{
    return m_endIter;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blDataIteratorType& blCSVMatrixIterator<blDataIteratorType,blNumberType>::getIter()const
{
    return m_iter;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blDataIteratorType& blCSVMatrixIterator<blDataIteratorType,blNumberType>::getFirstDataPointIter()const
{
    return m_firstDataPointIter;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blCSVMatrixIterator<blDataIteratorType,blNumberType>::getNumber()const
{
    return m_number;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::ptrdiff_t& blCSVMatrixIterator<blDataIteratorType,blNumberType>::rows()const
{
    return m_rows;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::ptrdiff_t& blCSVMatrixIterator<blDataIteratorType,blNumberType>::cols()const
{
    return m_cols;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::size_t& blCSVMatrixIterator<blDataIteratorType,blNumberType>::size()const
{
    return m_size;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::size_t& blCSVMatrixIterator<blDataIteratorType,blNumberType>::length()const
{
    return m_size;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::ptrdiff_t& blCSVMatrixIterator<blDataIteratorType,blNumberType>::rowIndex()const
{
    return m_rowIndex;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::ptrdiff_t& blCSVMatrixIterator<blDataIteratorType,blNumberType>::colIndex()const
{
    return m_colIndex;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::string& blCSVMatrixIterator<blDataIteratorType,blNumberType>::rowTokens()const
{
    return m_rowTokens;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::string& blCSVMatrixIterator<blDataIteratorType,blNumberType>::colTokens()const
{
    return m_colTokens;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::vector<std::string>& blCSVMatrixIterator<blDataIteratorType,blNumberType>::getColumnNames()const
{
    return m_columnNames;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to set/get the advancing iterator method
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline const blAdvancingIteratorMethod& blCSVMatrixIterator<blDataIteratorType,blNumberType>::getAdvancingIteratorMethod()const
{
    return m_advancingIteratorMethod;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline void blCSVMatrixIterator<blDataIteratorType,blNumberType>::setAdvancingIteratorMethod(const blAdvancingIteratorMethod& advancingIteratorMethod)
{
    m_advancingIteratorMethod = advancingIteratorMethod;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to move the current iterator position
// to the beginning or to the end
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<blDataIteratorType,blNumberType>& blCSVMatrixIterator<blDataIteratorType,blNumberType>::moveToTheBeginning()
{
    // We set everything back to the beginning
    // of the supplied csv data stream

    // If the supplied csv data size is zero
    // then we set everything to the end

    if(m_size == 0)
        m_iter = m_endIter;
    else
        m_iter = m_firstDataPointIter;

    m_dataIndex = 0;
    m_rowIndex = 0;
    m_colIndex = 0;

    return (*this);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<blDataIteratorType,blNumberType>& blCSVMatrixIterator<blDataIteratorType,blNumberType>::moveToTheEnd()
{
    // We set everything to point to the end
    // of the supplied binary data stream

    m_iter = m_endIter;

    m_dataIndex = m_size;
    m_rowIndex = m_rows;
    m_colIndex = m_cols;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions use to get the begin/end iterators
// so that this smart iterator can work with
// stl algorithms
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<blDataIteratorType,blNumberType> blCSVMatrixIterator<blDataIteratorType,blNumberType>::begin()const
{
    auto copiedSmartIterator = (*this);

    copiedSmartIterator.moveToTheBeginning();

    return copiedSmartIterator;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<blDataIteratorType,blNumberType> blCSVMatrixIterator<blDataIteratorType,blNumberType>::end()const
{
    auto copiedSmartIterator = (*this);

    copiedSmartIterator.moveToTheEnd();

    return copiedSmartIterator;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<const blDataIteratorType,blNumberType> blCSVMatrixIterator<blDataIteratorType,blNumberType>::cbegin()const
{
    auto copiedSmartIterator = (*this);

    copiedSmartIterator.moveToTheBeginning();

    return copiedSmartIterator;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<const blDataIteratorType,blNumberType> blCSVMatrixIterator<blDataIteratorType,blNumberType>::cend()const
{
    auto copiedSmartIterator = (*this);

    copiedSmartIterator.moveToTheEnd();

    return copiedSmartIterator;
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

inline void blCSVMatrixIterator<blDataIteratorType,blNumberType>::convertToNumberFromCurrentPosition()
{
    blAlgorithmsLIB::convertToNumber(m_iter,m_endIter,'.',m_number,0);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Arithmetic operators
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<blDataIteratorType,blNumberType>& blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator+=(const std::ptrdiff_t& movement)
{
    moveIterator(movement,m_advancingIteratorMethod);
    return (*this);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<blDataIteratorType,blNumberType>& blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator-=(const std::ptrdiff_t& movement)
{
    moveIterator(-movement,m_advancingIteratorMethod);
    return (*this);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<blDataIteratorType,blNumberType>& blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator++()
{
    moveIterator(1,m_advancingIteratorMethod);
    return (*this);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<blDataIteratorType,blNumberType>& blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator--()
{
    moveIterator(-1,m_advancingIteratorMethod);
    return (*this);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<blDataIteratorType,blNumberType> blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator++(int)
{
    auto temp(*this);
    moveIterator(1,m_advancingIteratorMethod);
    return temp;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<blDataIteratorType,blNumberType> blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator--(int)
{
    auto temp(*this);
    moveIterator(-1,m_advancingIteratorMethod);
    return temp;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<blDataIteratorType,blNumberType> blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator+(const std::ptrdiff_t& movement)const
{
    auto temp(*this);
    temp += movement;
    return temp;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blCSVMatrixIterator<blDataIteratorType,blNumberType> blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator-(const std::ptrdiff_t& movement)const
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

inline std::ptrdiff_t blCSVMatrixIterator<blDataIteratorType,blNumberType>::operator-(const blCSVMatrixIterator<blDataIteratorType,blNumberType>& csvMatrixIterator)const
{
    return (m_iter - csvMatrixIterator.getIter());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_CSVMATRIXITERATOR_HPP
