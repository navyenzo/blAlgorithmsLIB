#ifndef BL_COUNTANDFIND_HPP
#define BL_COUNTANDFIND_HPP



//-------------------------------------------------------------------
// FILE:            blCountAndFind.hpp
//
//
//
// PURPOSE:         Counting algorithms useful that count "rows" and/or
//                  "columns" of data in generic data streams/buffers,
//                  as well as finding algorithms that find the beginning
//                  and/or end of a specified "row" and/or "column", that
//                  find the beginning and/or end of the "Nth" row and
//                  "Mth" column and more.
//
//                  -- Very useful in parsing such things as csv files
//                     or other table-like data, whether the data is
//                     text or binary
//
//                  -- All functions/algorithms are defined within
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
// The following functions count the number of
// data rows in a buffer by searching for "data row"
// tokens in the buffer
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType>

inline size_t countDataRows(const blDataIteratorType& beginIter,
                            const blDataIteratorType& endIter,
                            const blTokenType& rowToken,
                            const bool& shouldZeroLengthRowsBeCounted)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // In this case there
        // are no rows

        return size_t(0);
    }

    // Iterators used to
    // find the tokens in
    // the data buffer

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = beginIter;

    // The total number
    // of rows found by
    // this function

    size_t totalNumberOfRows = size_t(0);

    while(firstTokenIterator != endIter)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0);

        if(secondTokenIterator == firstTokenIterator &&
           !shouldZeroLengthRowsBeCounted)
        {
            // In this case,
            // we do not want
            // to count this
            // as a data row

            ++firstTokenIterator;
        }
        else
        {
            // Increse the total
            // number of rows

            ++totalNumberOfRows;

            firstTokenIterator = secondTokenIterator;

            // Advance the iterator
            // if we've not reached
            // the end yet

            if(firstTokenIterator != endIter)
                ++firstTokenIterator;

            // In case of circular
            // iterators we might
            // be back to the
            // beginning, so we
            // quit in that case

            if(firstTokenIterator == beginIter)
                break;
        }
    }

    // We're done counting

    return totalNumberOfRows;
}


template<typename blDataIteratorType,
         typename blTokenType,
         typename blPredicateFunctorType>

inline size_t countDataRows(const blDataIteratorType& beginIter,
                            const blDataIteratorType& endIter,
                            const blTokenType& rowToken,
                            const bool& shouldZeroLengthRowsBeCounted,
                            const blPredicateFunctorType& predicateFunctor)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // In this case there
        // are no rows

        return size_t(0);
    }

    // Iterators used to
    // find the tokens in
    // the data buffer

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = beginIter;

    // The total number
    // of rows found by
    // this function

    size_t totalNumberOfRows = size_t(0);

    while(firstTokenIterator != endIter)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0,
                                   predicateFunctor);

        if(secondTokenIterator == firstTokenIterator &&
           !shouldZeroLengthRowsBeCounted)
        {
            // In this case,
            // we do not want
            // to count this
            // as a data row

            ++firstTokenIterator;
        }
        else
        {
            // Increse the total
            // number of rows

            ++totalNumberOfRows;

            firstTokenIterator = secondTokenIterator;

            // Advance the iterator
            // if we've not reached
            // the end yet

            if(firstTokenIterator != endIter)
                ++firstTokenIterator;

            // In case of circular
            // iterators we might
            // be back to the
            // beginning, so we
            // quit in that case

            if(firstTokenIterator == beginIter)
                break;
        }
    }

    // We're done counting

    return totalNumberOfRows;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following functions find data rows in a
// buffer by searching for the specified row
// token and then count the length of each row
// to find the length of the longest one
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType>

inline size_t findLengthOfLongestDataRow(const blDataIteratorType& beginIter,
                                         const blDataIteratorType& endIter,
                                         const blTokenType& rowToken)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // Error -- Passed a zero
        //          length buffer

        return size_t(0);
    }

    // The iterators to
    // the tokens found
    // in the data buffer

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = endIter;

    // The length of the
    // longest data row

    size_t longestLength = 0;

    // The length of the
    // current data row

    size_t lengthOfCurrentRow = 0;

    while(firstTokenIterator != endIter)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0);

        // Calculate the
        // length of the
        // current data row

        if(firstTokenIterator != secondTokenIterator)
            lengthOfCurrentRow = std::distance(firstTokenIterator,secondTokenIterator) - 1;
        else
            lengthOfCurrentRow = 0;

        // Compare the lengths

        if(lengthOfCurrentRow > longestLength)
        {
            longestLength = lengthOfCurrentRow;
        }

        firstTokenIterator = secondTokenIterator;

        // Advance the iterator
        // if we've not reached
        // the end yet

        if(firstTokenIterator != endIter)
            ++firstTokenIterator;

        // In case of circular
        // iterators we might
        // be back to the
        // beginning, so we
        // quit in that case

        if(firstTokenIterator == beginIter)
            break;
    }

    // We're done
    // counting

    return longestLength;
}


template<typename blDataIteratorType,
         typename blTokenType,
         typename blPredicateFunctorType>

inline size_t findLengthOfLongestDataRow(const blDataIteratorType& beginIter,
                                         const blDataIteratorType& endIter,
                                         const blTokenType& rowToken,
                                         const blPredicateFunctorType& predicateFunctor)
{
    // Check the inputs
    if(beginIter == endIter)
    {
        // Error -- Passed a zero
        //          length buffer

        return size_t(0);
    }

    // The iterators to
    // the tokens found
    // in the data buffer

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = endIter;

    // The length of the
    // longest data row

    size_t longestLength = 0;

    // The length of the
    // current data row

    size_t lengthOfCurrentRow = 0;

    while(firstTokenIterator != endIter)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0,
                                   predicateFunctor);

        // Calculate the
        // length of the
        // current data row

        if(firstTokenIterator != secondTokenIterator)
            lengthOfCurrentRow = std::distance(firstTokenIterator,secondTokenIterator) - 1;
        else
            lengthOfCurrentRow = 0;

        // Compare the lengths

        if(lengthOfCurrentRow > longestLength)
        {
            longestLength = lengthOfCurrentRow;
        }

        firstTokenIterator = secondTokenIterator;

        // Advance the iterator
        // if we've not reached
        // the end yet

        if(firstTokenIterator != endIter)
            ++firstTokenIterator;

        // In case of circular
        // iterators we might
        // be back to the
        // beginning, so we
        // quit in that case

        if(firstTokenIterator == beginIter)
            break;
    }

    // We're done
    // counting

    return longestLength;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following functions count the total
// number of rows in a buffer together with
// the length of the longest row
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blDataIteratorType countDataRowsAndLongestRowLength(const blDataIteratorType& beginIter,
                                                           const blDataIteratorType& endIter,
                                                           const blTokenType& rowToken,
                                                           const bool& shouldZeroLengthRowsBeCounted,
                                                           blIntegerType& totalNumberOfRows,
                                                           blIntegerType& lengthOfLongestRow)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // Error -- Passed a zero
        //          length buffer

        return endIter;
    }

    // The iterators to
    // the tokens found
    // in the data buffer

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = endIter;
    blDataIteratorType iteratorToBeginningOfLongestDataRow;

    // The length of the
    // longest data row

    lengthOfLongestRow = 0;

    // The length of the
    // current data row

    blIntegerType lengthOfCurrentRow = 0;

    // The total
    // number of
    // rows

    totalNumberOfRows = 0;

    while(firstTokenIterator != endIter)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0);

        if(secondTokenIterator == firstTokenIterator &&
           !shouldZeroLengthRowsBeCounted)
        {
            // In this we don't
            // count the zero
            // sized row

            ++firstTokenIterator;
        }
        else
        {
            // Increse the
            // total number
            // of rows

            ++totalNumberOfRows;

            // Calculate the
            // length of
            // the current
            // data row

            lengthOfCurrentRow = std::distance(firstTokenIterator,secondTokenIterator);

            // Compare the
            // lengths

            if(lengthOfCurrentRow > lengthOfLongestRow)
            {

                lengthOfLongestRow = lengthOfCurrentRow;
                iteratorToBeginningOfLongestDataRow = firstTokenIterator;
            }

            firstTokenIterator = secondTokenIterator;

            // Advance the iterator
            // if we've not reached
            // the end yet

            if(firstTokenIterator != endIter)
                ++firstTokenIterator;
        }

        // In case of circular
        // iterators we might
        // be back to the
        // beginning, so we
        // quit in that case

        if(firstTokenIterator == beginIter)
            break;
    }

    return iteratorToBeginningOfLongestDataRow;
}


template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType,
         typename blPredicateFunctorType>

inline blDataIteratorType countDataRowsAndLongestRowLength(const blDataIteratorType& beginIter,
                                                           const blDataIteratorType& endIter,
                                                           const blTokenType& rowToken,
                                                           const bool& shouldZeroLengthRowsBeCounted,
                                                           blIntegerType& totalNumberOfRows,
                                                           blIntegerType& lengthOfLongestRow,
                                                           const blPredicateFunctorType& predicateFunctor)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // Error -- Passed a zero
        //          length buffer

        return endIter;
    }

    // The iterators to
    // the tokens found
    // in the data buffer

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = endIter;
    blDataIteratorType iteratorToBeginningOfLongestDataRow;

    // The length of the
    // longest data row

    lengthOfLongestRow = 0;

    // The length of the
    // current data row

    blIntegerType lengthOfCurrentRow = 0;

    // The total
    // number of
    // rows

    totalNumberOfRows = 0;

    while(firstTokenIterator != endIter)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0,
                                   predicateFunctor);

        if(secondTokenIterator == firstTokenIterator &&
           !shouldZeroLengthRowsBeCounted)
        {
            // In this we don't
            // count the zero
            // sized row

            ++firstTokenIterator;
        }
        else
        {
            // Increse the
            // total number
            // of rows

            ++totalNumberOfRows;

            // Calculate the
            // length of
            // the current
            // data row

            lengthOfCurrentRow = std::distance(firstTokenIterator,secondTokenIterator);

            // Compare the
            // lengths

            if(lengthOfCurrentRow > lengthOfLongestRow)
            {

                lengthOfLongestRow = lengthOfCurrentRow;
                iteratorToBeginningOfLongestDataRow = firstTokenIterator;
            }

            firstTokenIterator = secondTokenIterator;

            // Advance the iterator
            // if we've not reached
            // the end yet

            if(firstTokenIterator != endIter)
                ++firstTokenIterator;
        }

        // In case of circular
        // iterators we might
        // be back to the
        // beginning, so we
        // quit in that case

        if(firstTokenIterator == beginIter)
            break;
    }

    return iteratorToBeginningOfLongestDataRow;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// THe following functions find the corresponding
// row and column position of the user specified
// buffer position
//
// NOTES:               For example:  We have a text string and we
//                                    want to know in which line
//                                    and character position the
//                                    99th character of the text
//                                    lies in.
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline void getRowAndColNumberOfPositionInDataBuffer(const blDataIteratorType& beginIter,
                                                     const blDataIteratorType& endIter,
                                                     const blTokenType& token,
                                                     const bool& shouldZeroLengthRowsBeCounted,
                                                     const blDataIteratorType& iteratorToDataPosition,
                                                     blIntegerType& rowNumber,
                                                     blIntegerType& colNumber)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // In this case, we
        // have no data to
        // parse, or no
        // tokens to find

        if(!shouldZeroLengthRowsBeCounted)
        {
            rowNumber = blIntegerType(-1);
            colNumber = blIntegerType(-1);
        }
        else
        {
            rowNumber = blIntegerType(0);
            colNumber = blIntegerType(0);
        }

        return;
    }

    // The iterator to
    // the tokens found
    // in the data

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = beginIter;

    // The starting
    // position of the
    // row we're currently
    // parsing

    blDataIteratorType startingPositionOfCurrentRow = beginIter;

    // We initialize the
    // row number differently
    // depending on whether
    // or not rows of zero size
    // are to be counted

    if(shouldZeroLengthRowsBeCounted)
        rowNumber = blIntegerType(0);
    else
        rowNumber = blIntegerType(-1);

    while(firstTokenIterator != endIter &&
          std::distance(firstTokenIterator,iteratorToDataPosition) > 0)
    {
        // Find the next
        // token in the
        // data buffer

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   token,
                                   0);

        // Check to see if
        // the row we found
        // was a zero length
        // row

        if(secondTokenIterator != endIter &&
           secondTokenIterator == firstTokenIterator &&
           !shouldZeroLengthRowsBeCounted)
        {
            // In this case,
            // the row is of
            // zero length and
            // we don't count it

            ++firstTokenIterator;
        }
        else if(secondTokenIterator != endIter &&
                std::distance(secondTokenIterator,iteratorToDataPosition) >= 0)
        {
            ++rowNumber;

            firstTokenIterator = secondTokenIterator;
            ++firstTokenIterator;

            startingPositionOfCurrentRow = firstTokenIterator;
        }
        else
        {
            firstTokenIterator = secondTokenIterator;
        }
    }

    // We calculated the
    // row, now we need
    // to calculate the
    // column

    colNumber = std::distance(startingPositionOfCurrentRow,iteratorToDataPosition);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// This function gets an iterator to the
// beginning of the user specified nth row.
// The function returns the "actual" row found
// in case that there are less than "n" rows.
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blIntegerType findBeginningOfNthDataRow(const blDataIteratorType& beginIter,
                                               const blDataIteratorType& endIter,
                                               const blTokenType& rowToken,
                                               const bool& shouldZeroLengthRowsBeCounted,
                                               const blIntegerType& whichRowToFind,
                                               blDataIteratorType& nthRowBeginIter)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // In this case
        // we have no
        // data to look
        // through

        nthRowBeginIter = beginIter;

        return blIntegerType(0);
    }

    // The iterator
    // to the tokens
    // found in the data

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = beginIter;

    nthRowBeginIter = firstTokenIterator;

    // The current
    // data row

    blIntegerType currentRow = blIntegerType(-1);

    while(firstTokenIterator != endIter &&
          currentRow < whichRowToFind)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0);

        if(secondTokenIterator == firstTokenIterator &&
           !shouldZeroLengthRowsBeCounted)
        {
            // In this case,
            // the row is of
            // zero length and
            // we don't count it

            ++firstTokenIterator;
        }
        else
        {
            ++currentRow;

            nthRowBeginIter = firstTokenIterator;

            firstTokenIterator = secondTokenIterator;

            // If we have not
            // reached the end,
            // then we advance
            // the iterator

            if(firstTokenIterator != endIter)
                ++firstTokenIterator;
        }
    }

    // We're done

    return currentRow;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// This function gets an iterator to the
// beginning of the user specified nth row.
// The function returns the "actual" row found
// in case that there are less than "n" rows.
// The function allows the user to specify
// whether or not to count zero sized rows.
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blIntegerType findBeginAndEndOfNthDataRow(const blDataIteratorType& beginIter,
                                                 const blDataIteratorType& endIter,
                                                 const blTokenType& rowToken,
                                                 const bool& shouldZeroLengthRowsBeCounted,
                                                 const blIntegerType& whichRowToFind,
                                                 blDataIteratorType& nthRowBeginIter,
                                                 blDataIteratorType& nthRowEndIter)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // In this case
        // we have no
        // data to look
        // through

        nthRowBeginIter = beginIter;
        nthRowEndIter = beginIter;

        return blIntegerType(0);
    }

    // The iterator
    // to the tokens
    // found in the data

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = beginIter;

    nthRowBeginIter = firstTokenIterator;
    nthRowEndIter = firstTokenIterator;

    // The current
    // data row

    blIntegerType currentRow = blIntegerType(-1);

    while(firstTokenIterator != endIter &&
          currentRow < whichRowToFind)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0);

        if(secondTokenIterator == firstTokenIterator &&
           !shouldZeroLengthRowsBeCounted)
        {
            // In this case,
            // the row is of
            // zero length and
            // we don't count it

            ++firstTokenIterator;
        }
        else
        {
            ++currentRow;

            nthRowBeginIter = firstTokenIterator;
            nthRowEndIter = secondTokenIterator;

            firstTokenIterator = secondTokenIterator;

            // If we have not
            // reached the end,
            // then we advance
            // the iterator

            if(firstTokenIterator != endIter)
                ++firstTokenIterator;
        }
    }

    // We're done

    return currentRow;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// This function, just like the one above
// finds the beginning and end of the user
// specified nth row.
// The function returns the "actual" row found
// in case that there are less than "n" rows.
// The function allows the user to specify
// whether or not to count zero sized rows.
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blIntegerType findBeginAndEndOfNthDataRow2(const blDataIteratorType& beginIter,
                                                  const blDataIteratorType& endIter,
                                                  const blTokenType& rowToken,
                                                  const bool& shouldZeroLengthRowsBeCounted,
                                                  const blIntegerType& whichRowToFind,
                                                  blIntegerType& nthRowBeginIndex,
                                                  blIntegerType& nthRowEndIndex)
{
    blDataIteratorType nthRowBeginIter;
    blDataIteratorType nthRowEndIter;

    blIntegerType actualRowFound = findBeginAndEndOfNthDataRow(beginIter,
                                                               endIter,
                                                               rowToken,
                                                               shouldZeroLengthRowsBeCounted,
                                                               whichRowToFind,
                                                               nthRowBeginIter,
                                                               nthRowEndIter);

    nthRowBeginIndex = std::distance(beginIter,nthRowBeginIter);
    nthRowEndIndex = std::distance(beginIter,nthRowEndIter);

    return actualRowFound;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// This function gets an iterator to a data
// point in the data array corresponding to
// the specified Nth data row and Mth data
// column
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blDataIteratorType findIterToNthDataRowAndMthDataCol(const blDataIteratorType& beginIter,
                                                            const blDataIteratorType& endIter,
                                                            const blTokenType& rowToken,
                                                            const bool& shouldZeroLengthRowsBeCounted,
                                                            const blIntegerType& whichRowToFind,
                                                            const blIntegerType& whichColToFind)
{
    // We first try to
    // find the starting
    // and ending positions
    // of the specified
    // Nth data row

    blDataIteratorType iteratorToPositionOfNthRowAndMthColumn;
    blDataIteratorType iteratorToEndingPositionOfNthRow;

    findBeginAndEndOfNthDataRow(beginIter,
                                endIter,
                                rowToken,
                                shouldZeroLengthRowsBeCounted,
                                whichRowToFind,
                                iteratorToPositionOfNthRowAndMthColumn,
                                iteratorToEndingPositionOfNthRow);

    // We calculate the
    // actual column
    // that the iterator
    // will be pointing to

    blIntegerType actualColFound = std::min( whichColToFind,
                                             blIntegerType(std::distance(iteratorToPositionOfNthRowAndMthColumn,
                                                                         iteratorToEndingPositionOfNthRow)) );

    // Advance the iterator
    // to get it to the Mth
    // column making sure
    // it does not pass the
    // end of the row

    std::advance(iteratorToPositionOfNthRowAndMthColumn,actualColFound);

    return iteratorToPositionOfNthRowAndMthColumn;
}


template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blDataIteratorType findIterToNthDataRowAndMthDataCol(const blDataIteratorType& beginIter,
                                                            const blDataIteratorType& endIter,
                                                            const blTokenType& rowToken,
                                                            const bool& shouldZeroLengthRowsBeCounted,
                                                            const blIntegerType& whichRowToFind,
                                                            const blIntegerType& whichColToFind,
                                                            blIntegerType& actualRowFound,
                                                            blIntegerType& actualColFound)
{
    // We first try to
    // find the starting
    // and ending positions
    // of the specified
    // Nth data row

    blDataIteratorType iteratorToPositionOfNthRowAndMthColumn;
    blDataIteratorType iteratorToEndingPositionOfNthRow;

    actualRowFound = findBeginAndEndOfNthDataRow(beginIter,
                                                 endIter,
                                                 rowToken,
                                                 shouldZeroLengthRowsBeCounted,
                                                 whichRowToFind,
                                                 iteratorToPositionOfNthRowAndMthColumn,
                                                 iteratorToEndingPositionOfNthRow);

    // We calculate the
    // actual column
    // that the iterator
    // will be pointing to

    actualColFound = std::min( whichColToFind,
                               blIntegerType(std::distance(iteratorToPositionOfNthRowAndMthColumn,
                                                           iteratorToEndingPositionOfNthRow)) );

    // Advance the iterator
    // to get it to the Mth
    // column making sure
    // it does not pass the
    // end of the row

    std::advance(iteratorToPositionOfNthRowAndMthColumn,actualColFound);

    return iteratorToPositionOfNthRowAndMthColumn;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// This function gets the position in the
// data buffer of a data point specified
// by its Nth Row and Mth Column
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blIntegerType findPositionOfNthDataRowAndMthDataCol(const blDataIteratorType& beginIter,
                                                           const blDataIteratorType& endIter,
                                                           const blTokenType& rowToken,
                                                           const bool& shouldZeroLengthRowsBeCounted,
                                                           const blIntegerType& whichRowToFind,
                                                           const blIntegerType& whichColToFind)
{
    // We first try to
    // find the starting
    // and ending positions
    // of the specified
    // Nth data row

    blDataIteratorType iteratorToPositionOfNthRowAndMthColumn = findIterToNthDataRowAndMthDataCol(beginIter,
                                                                                                  endIter,
                                                                                                  rowToken,
                                                                                                  shouldZeroLengthRowsBeCounted,
                                                                                                  whichRowToFind,
                                                                                                  whichColToFind);

    return std::distance(beginIter,iteratorToPositionOfNthRowAndMthColumn);
}


template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blIntegerType findPositionOfNthDataRowAndMthDataCol(const blDataIteratorType& beginIter,
                                                           const blDataIteratorType& endIter,
                                                           const blTokenType& rowToken,
                                                           const bool& shouldZeroLengthRowsBeCounted,
                                                           const blIntegerType& whichRowToFind,
                                                           const blIntegerType& whichColToFind,
                                                           blIntegerType& actualRowFound,
                                                           blIntegerType& actualColFound)
{
    // We first try to
    // find the starting
    // and ending positions
    // of the specified
    // Nth data row

    blDataIteratorType iteratorToPositionOfNthRowAndMthColumn = findIterToNthDataRowAndMthDataCol(beginIter,
                                                                                                  endIter,
                                                                                                  rowToken,
                                                                                                  shouldZeroLengthRowsBeCounted,
                                                                                                  whichRowToFind,
                                                                                                  whichColToFind,
                                                                                                  actualRowFound,
                                                                                                  actualColFound);

    return std::distance(beginIter,iteratorToPositionOfNthRowAndMthColumn);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// std::string specializations
// of the
// above functions
//-------------------------------------------------------------------
template<typename blTokenType,
         typename blIntegerType>

inline blIntegerType findPositionOfNthDataRowAndMthDataColInString(const std::string& theString,
                                                                   const blTokenType& rowToken,
                                                                   const blIntegerType& whichRowToFind,
                                                                   const blIntegerType& whichColToFind)
{
    return findPositionOfNthDataRowAndMthDataCol(theString.begin(),
                                                 theString.end(),
                                                 rowToken,
                                                 true,
                                                 whichRowToFind,
                                                 whichColToFind);
}


template<typename blTokenType,
         typename blIntegerType>

inline blIntegerType findPositionOfNthDataRowAndMthDataColInString(const std::string& theString,
                                                                   const blTokenType& rowToken,
                                                                   const blIntegerType& whichRowToFind,
                                                                   const blIntegerType& whichColToFind,
                                                                   blIntegerType& actualRowFound,
                                                                   blIntegerType& actualColFound)
{
    return findPositionOfNthDataRowAndMthDataCol(theString.begin(),
                                                 theString.end(),
                                                 rowToken,
                                                 true,
                                                 whichRowToFind,
                                                 whichColToFind,
                                                 actualRowFound,
                                                 actualColFound);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_COUNTANDFIND_HPP
