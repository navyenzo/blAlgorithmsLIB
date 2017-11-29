#ifndef BL_BINARYMATRIXITERATOR_HPP
#define BL_BINARYMATRIXITERATOR_HPP



//-------------------------------------------------------------------
// FILE:            blBinaryMatrixIterator.hpp
// CLASS:           blBinaryMatrixIterator
// BASE CLASS:      None
//
//
//
// PURPOSE:         A custom iterator that can be used to parse serialized
//                  binary data.
//
//                  The iterator assumes that the binary data is an (n x 1)
//                  vector of values, representing data points, where each data
//                  point is a matrix of data of size (rows x cols)
//
//                  The binary data is provided as a stream/string of bytes through
//                  user specified begin/end iterators and then converted to the
//                  user specified data type
//
//                  The binary data is assumed to be formatted as follows:
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
//                  -- The iterator assumes that all single values in the data
//                     are of the same type (the type specified by the user through
//                     the template parameter)
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

class blBinaryMatrixIterator
{
public: // Type aliases



    // Iterator traits

    using iterator_category = std::random_access_iterator_tag;
    using value_type = blNumberType;
    using difference_type = std::ptrdiff_t;
    using pointer = blNumberType*;
    using reference = blNumberType&;



public: // Constructors and destructor



    // No default constructor

    blBinaryMatrixIterator() = delete;



    // Constructor from two iterators

    blBinaryMatrixIterator(const blDataIteratorType& beginIter,
                           const blDataIteratorType& endIter);



    // Default copy constructor

    blBinaryMatrixIterator(const blBinaryMatrixIterator<blDataIteratorType,blNumberType>& binaryMatrixIterator) = default;



    // Destructor

    ~blBinaryMatrixIterator();



public: // Assignment operator



    // Default assignment operator

    blBinaryMatrixIterator<blDataIteratorType,blNumberType>&            operator=(const blBinaryMatrixIterator<blDataIteratorType,blNumberType>& binaryMatrixIterator) = default;



public: // Equality operators



    bool                                                                operator==(const blBinaryMatrixIterator<blDataIteratorType,blNumberType>& binaryMatrixIterator)const;
    bool                                                                operator!=(const blBinaryMatrixIterator<blDataIteratorType,blNumberType>& binaryMatrixIterator)const;



public: // Reference and Dereference operators



    blNumberType*                                                       operator->();
    blNumberType&                                                       operator*();
    const blNumberType&                                                 operator*()const;



public: // Access operators



    // Access operators treating the data
    // as a one-dimensional data buffer

    blNumberType&                                                       operator[](const std::ptrdiff_t& index);
    blNumberType&                                                       operator()(const std::ptrdiff_t& index);
    blNumberType&                                                       at(const std::ptrdiff_t& index);

    const blNumberType&                                                 operator[](const std::ptrdiff_t& index)const;
    const blNumberType&                                                 operator()(const std::ptrdiff_t& index)const;
    const blNumberType&                                                 at(const std::ptrdiff_t& index)const;



    // Access operators treating the data
    // as a two-dimensional data buffer

    blNumberType&                                                       operator()(const std::ptrdiff_t& rowIndex,
                                                                                   const std::ptrdiff_t& colIndex);
    blNumberType&                                                       at(const std::ptrdiff_t& rowIndex,
                                                                           const std::ptrdiff_t& colIndex);

    const blNumberType&                                                 operator()(const std::ptrdiff_t& rowIndex,
                                                                                   const std::ptrdiff_t& colIndex)const;
    const blNumberType&                                                 at(const std::ptrdiff_t& rowIndex,
                                                                           const std::ptrdiff_t& colIndex)const;



    // Access operators treating the data
    // as a three-dimensional data buffer

    blNumberType&                                                       operator()(const std::ptrdiff_t& rowIndex,
                                                                                   const std::ptrdiff_t& colIndex,
                                                                                   const std::ptrdiff_t& pageIndex);
    blNumberType&                                                       at(const std::ptrdiff_t& rowIndex,
                                                                           const std::ptrdiff_t& colIndex,
                                                                           const std::ptrdiff_t& pageIndex);

    const blNumberType&                                                 operator()(const std::ptrdiff_t& rowIndex,
                                                                                   const std::ptrdiff_t& colIndex,
                                                                                   const std::ptrdiff_t& pageIndex)const;
    const blNumberType&                                                 at(const std::ptrdiff_t& rowIndex,
                                                                           const std::ptrdiff_t& colIndex,
                                                                           const std::ptrdiff_t& pageIndex)const;



public: // Public functions



    // Overloaded function used to set
    // the begin/end iterators

    void                                                                setIterators(const blDataIteratorType& beginIter,
                                                                                     const blDataIteratorType& endIter);



    // Functions used to move the current
    // iterator position to the beginning
    // or to the end

    blBinaryMatrixIterator<blDataIteratorType,blNumberType>&            moveToTheBeginning();
    blBinaryMatrixIterator<blDataIteratorType,blNumberType>&            moveToTheEnd();



    // Let's override the arithmetic operators
    // to make this move like a col-major matrix

    blBinaryMatrixIterator<blDataIteratorType,blNumberType>&            operator+=(const std::ptrdiff_t& movement);
    blBinaryMatrixIterator<blDataIteratorType,blNumberType>&            operator-=(const std::ptrdiff_t& movement);
    blBinaryMatrixIterator<blDataIteratorType,blNumberType>&            operator++();
    blBinaryMatrixIterator<blDataIteratorType,blNumberType>&            operator--();
    blBinaryMatrixIterator<blDataIteratorType,blNumberType>             operator++(int);
    blBinaryMatrixIterator<blDataIteratorType,blNumberType>             operator--(int);
    blBinaryMatrixIterator<blDataIteratorType,blNumberType>             operator+(const std::ptrdiff_t& movement)const;
    blBinaryMatrixIterator<blDataIteratorType,blNumberType>             operator-(const std::ptrdiff_t& movement)const;



    // Operator used to "subtract"
    // two pointers (it gives the
    // distance)

    std::ptrdiff_t                                                      operator-(const blBinaryMatrixIterator<blDataIteratorType,blNumberType>& binaryMatrixIterator)const;



    // Functions used to get the
    // matrix header information

    const std::ptrdiff_t&                                               serialNumber()const;
    const std::size_t&                                                  rows()const;
    const std::size_t&                                                  cols()const;
    const std::size_t&                                                  pages()const;
    const std::size_t&                                                  currentIndex()const;
    const std::size_t&                                                  currentRow()const;
    const std::size_t&                                                  currentCol()const;
    const std::size_t&                                                  currentPage()const;
    const std::size_t&                                                  size()const;
    const std::size_t&                                                  length()const;



    // Functions used to get the
    // begin/end/iter iterators
    // useful when copying this
    // smart iterator

    const blDataIteratorType&                                           getBeginIter()const;
    const blDataIteratorType&                                           getEndIter()const;
    const blDataIteratorType&                                           getIter()const;



    // Functions used to get the
    // begin/end iterators so that
    // this can be used in stl
    // algorithms

    blBinaryMatrixIterator<blDataIteratorType,blNumberType>             begin()const;
    blBinaryMatrixIterator<blDataIteratorType,blNumberType>             end()const;



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



    // Serial number

    std::ptrdiff_t                                                      m_serialNumber;



    // Data is represented as pages x rows x cols

    std::size_t                                                         m_rows;
    std::size_t                                                         m_cols;
    std::size_t                                                         m_pages;



    // Total size of matrix (pages * rows * cols)

    std::size_t                                                         m_size;



    //  Current row, column and page in the buffer

    std::size_t                                                         m_currentIndex;
    std::size_t                                                         m_currentRow;
    std::size_t                                                         m_currentCol;
    std::size_t                                                         m_currentPage;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blBinaryMatrixIterator<blDataIteratorType,blNumberType>::blBinaryMatrixIterator(const blDataIteratorType& beginIter,
                                                                                       const blDataIteratorType& endIter)
{
    setIterators(beginIter,endIter);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blBinaryMatrixIterator<blDataIteratorType,blNumberType>::~blBinaryMatrixIterator()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Equality operators
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline bool blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator==(const blBinaryMatrixIterator<blDataIteratorType,blNumberType>& binaryMatrixIterator)const
{
    if(m_iter == binaryMatrixIterator.getIter())
        return true;

    return false;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline bool blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator!=(const blBinaryMatrixIterator<blDataIteratorType,blNumberType>& binaryMatrixIterator)const
{
    if(m_iter != binaryMatrixIterator.getIter())
        return true;

    return false;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Overloaded function used to set the begin/end iterators
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline void blBinaryMatrixIterator<blDataIteratorType,blNumberType>::setIterators(const blDataIteratorType& beginIter,
                                                                                  const blDataIteratorType& endIter)
{
    // First we save the newly supplied
    // begin/end iterators and set the
    // current iterator position to the
    // begin iterator

    m_beginIter = beginIter;
    m_endIter = endIter;
    m_iter = m_beginIter;



    // Then we calculate the total number
    // of entrees in the supplied stream

    std::size_t totalNumberOfEntreesInStream = static_cast<std::size_t>(std::distance(m_beginIter,m_endIter)) / static_cast<std::size_t>(sizeof(blNumberType));



    // Then we read the serial number,
    // rows and columns by reading the
    // first 3 entrees in the supplied
    // stream

    if(totalNumberOfEntreesInStream <= 3)
    {
        // This means the supplied stream
        // does not have the expected format

        // We just default everything to 0

        m_serialNumber = static_cast<std::ptrdiff_t>(0);
        m_rows = static_cast<std::size_t>(0);
        m_cols = static_cast<std::size_t>(0);
        m_pages = static_cast<std::size_t>(0);
        m_size = static_cast<std::size_t>(0);
    }
    else
    {
        // First we read the serial number, rows and cols

        m_serialNumber = static_cast<std::ptrdiff_t>( *(reinterpret_cast<blNumberType*>(&(*m_iter))) );
        m_iter += sizeof(blNumberType);
        m_rows = static_cast<std::size_t>( *(reinterpret_cast<blNumberType*>(&(*m_iter))) );
        m_iter += sizeof(blNumberType);
        m_cols = static_cast<std::size_t>( *(reinterpret_cast<blNumberType*>(&(*m_iter))) );
        m_iter += sizeof(blNumberType);



        // From that information, knowing that
        // the first three entrees represent
        // the serial number, the rows and
        // columns, we find the number of pages
        // by calculating how many (rows x cols)
        // entrees there are in the stream

        m_pages = (totalNumberOfEntreesInStream - static_cast<std::size_t>(3)) / (m_rows * m_cols);



        // Let's not forget to save the
        // total length of the data

        m_size = m_pages * m_rows * m_cols;
    }



    // We also default all current
    // indexes to 0

    m_currentIndex = static_cast<std::ptrdiff_t>(0);
    m_currentRow = static_cast<std::ptrdiff_t>(0);
    m_currentCol = static_cast<std::ptrdiff_t>(0);
    m_currentPage = static_cast<std::ptrdiff_t>(0);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to move the current iterator position
// to the beginning or to the end
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blBinaryMatrixIterator<blDataIteratorType,blNumberType>& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::moveToTheBeginning()
{
    // We move the iterator enough to
    // make it point back to the beginning

    this->operator+=(-m_currentIndex);

    return (*this);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blBinaryMatrixIterator<blDataIteratorType,blNumberType>& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::moveToTheEnd()
{
    // We move the iterator enough to
    // make it point back to the beginning

    this->operator+=(m_size - m_currentIndex);

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Arithmetic operators to make the iterator
// move like a col-major matrix
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blBinaryMatrixIterator<blDataIteratorType,blNumberType>& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator+=(const std::ptrdiff_t& movement)
{
    // First we advance the current index
    // making sure it never goes below
    // zero or above the length of the data

    if(movement < 0)
    {
        if(static_cast<std::size_t>(-movement) < m_currentIndex)
            m_currentIndex -= static_cast<std::size_t>(-movement);
        else
            m_currentIndex = 0;
    }
    else
    {
        m_currentIndex += movement;

        if(m_currentIndex > m_size)
            m_currentIndex = m_size;
    }



    // We then move the current iterator
    // to point to the current index in
    // a circular way, so that it wraps
    // around, whether moving in the positive
    // or negative direction

    m_iter = m_beginIter + ( (m_currentIndex + 3) * sizeof(blNumberType) );



    // We now calculate the current row
    // column and page

    m_currentPage = m_currentIndex / (m_rows * m_cols);
    m_currentRow = (m_currentIndex - m_currentPage * m_rows * m_cols) / m_cols;
    m_currentCol = m_currentIndex % m_cols;



    // We're done

    return (*this);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blBinaryMatrixIterator<blDataIteratorType,blNumberType>& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator-=(const std::ptrdiff_t& movement)
{
    return this->operator+=(-movement);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blBinaryMatrixIterator<blDataIteratorType,blNumberType>& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator++()
{
    return operator+=(1);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blBinaryMatrixIterator<blDataIteratorType,blNumberType>& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator--()
{
    return operator+=(-1);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blBinaryMatrixIterator<blDataIteratorType,blNumberType> blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator++(int)
{
    auto temp(*this);

    operator+=(1);

    return temp;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blBinaryMatrixIterator<blDataIteratorType,blNumberType> blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator--(int)
{
    auto temp(*this);

    operator+=(-1);

    return temp;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blBinaryMatrixIterator<blDataIteratorType,blNumberType> blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator+(const std::ptrdiff_t& movement)const
{
    auto temp(*this);

    temp += movement;

    return temp;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blBinaryMatrixIterator<blDataIteratorType,blNumberType> blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator-(const std::ptrdiff_t& movement)const
{
    auto temp(*this);

    temp -= movement;

    return temp;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Operator used to subtract two iterators (returns the distance)
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline std::ptrdiff_t blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator-(const blBinaryMatrixIterator<blDataIteratorType,blNumberType>& binaryMatrixIterator)const
{
    return (m_iter - binaryMatrixIterator.getIter())/static_cast<std::ptrdiff_t>(sizeof(blNumberType));
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Reference and Dereference operators
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blNumberType* blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator->()
{
    return reinterpret_cast<double*>(m_iter);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator*()
{
    return (*reinterpret_cast<double*>(m_iter));
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator*()const
{
    return (*reinterpret_cast<double*>(m_iter));
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Let's override the access operators so that
// they access only the data points and not
// the string header (serial number, rows, cols)
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator[](const std::ptrdiff_t& index)
{
    return (reinterpret_cast<double*>(m_beginIter)[index + 3]);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator[](const std::ptrdiff_t& index)const
{
    return (reinterpret_cast<double*>(m_beginIter)[index + 3]);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator()(const std::ptrdiff_t& index)
{
    return (reinterpret_cast<double*>(m_beginIter)[index + 3]);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator()(const std::ptrdiff_t& index)const
{
    return (reinterpret_cast<double*>(m_beginIter)[index + 3]);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::at(const std::ptrdiff_t& index)
{
    return (reinterpret_cast<double*>(m_beginIter)[index + 3]);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::at(const std::ptrdiff_t& index)const
{
    return (reinterpret_cast<double*>(m_beginIter)[index + 3]);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator()(const std::ptrdiff_t& rowIndex,
                                                                                         const std::ptrdiff_t& colIndex)
{
    return at(colIndex * m_rows + rowIndex);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator()(const std::ptrdiff_t& rowIndex,
                                                                                               const std::ptrdiff_t& colIndex)const
{
    return at(colIndex * m_rows + rowIndex);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::at(const std::ptrdiff_t& rowIndex,
                                                                                 const std::ptrdiff_t& colIndex)
{
    return at(colIndex * m_rows + rowIndex);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::at(const std::ptrdiff_t& rowIndex,
                                                                                       const std::ptrdiff_t& colIndex)const
{
    return at(colIndex * m_rows + rowIndex);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator()(const std::ptrdiff_t& rowIndex,
                                                                                         const std::ptrdiff_t& colIndex,
                                                                                         const std::ptrdiff_t& pageIndex)
{
    return at(pageIndex * m_rows * m_cols + colIndex * m_rows + rowIndex);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::operator()(const std::ptrdiff_t& rowIndex,
                                                                                               const std::ptrdiff_t& colIndex,
                                                                                               const std::ptrdiff_t& pageIndex)const
{
    return at(pageIndex * m_rows * m_cols + colIndex * m_rows + rowIndex);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::at(const std::ptrdiff_t& rowIndex,
                                                                                 const std::ptrdiff_t& colIndex,
                                                                                 const std::ptrdiff_t& pageIndex)
{
    return at(pageIndex * m_rows * m_cols + colIndex * m_rows + rowIndex);
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blNumberType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::at(const std::ptrdiff_t& rowIndex,
                                                                                       const std::ptrdiff_t& colIndex,
                                                                                       const std::ptrdiff_t& pageIndex)const
{
    return at(pageIndex * m_rows * m_cols + colIndex * m_rows + rowIndex);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions use to get the begin/end iterators
// so that this smart iterator can work with
// stl algorithms
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline blBinaryMatrixIterator<blDataIteratorType,blNumberType> blBinaryMatrixIterator<blDataIteratorType,blNumberType>::begin()const
{
    auto copiedSmartIterator = (*this);

    copiedSmartIterator.moveToTheBeginning();

    return copiedSmartIterator;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline blBinaryMatrixIterator<blDataIteratorType,blNumberType> blBinaryMatrixIterator<blDataIteratorType,blNumberType>::end()const
{
    auto copiedSmartIterator = (*this);

    copiedSmartIterator.moveToTheEnd();

    return copiedSmartIterator;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get data stream header information
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline const std::ptrdiff_t& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::serialNumber()const
{
    return m_serialNumber;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::size_t& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::rows()const
{
    return m_rows;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::size_t& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::cols()const
{
    return m_cols;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::size_t& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::pages()const
{
    return m_pages;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::size_t& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::currentIndex()const
{
    return m_currentIndex;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::size_t& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::currentRow()const
{
    return m_currentRow;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::size_t& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::currentCol()const
{
    return m_currentCol;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::size_t& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::currentPage()const
{
    return m_currentPage;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::size_t& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::size()const
{
    return m_size;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const std::size_t& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::length()const
{
    return m_size;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get the raw iterators
// useful when copying the smart iterator
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

inline const blDataIteratorType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::getBeginIter()const
{
    return m_beginIter;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blDataIteratorType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::getEndIter()const
{
    return m_endIter;
}



template<typename blDataIteratorType,
         typename blNumberType>

inline const blDataIteratorType& blBinaryMatrixIterator<blDataIteratorType,blNumberType>::getIter()const
{
    return m_iter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_BINARYMATRIXITERATOR_HPP
