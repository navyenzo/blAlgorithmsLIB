#ifndef BL_CYCLICSTLALGORITHMS_HPP
#define BL_CYCLICSTLALGORITHMS_HPP



//-------------------------------------------------------------------
// FILE:            blCyclicStlAlgorithms.hpp
//
//
//
// PURPOSE:         Cyclic versions of common stl-algorithms such
//                  as std::copy and std::find but with a parameter
//                  that allows a user to specify the maximum
//                  number of cycles when using cyclic iterators
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
// Includes needed by this class
//-------------------------------------------------------------------
#include <cstddef>
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blAlgorithmsLIB namespace
//-------------------------------------------------------------------
namespace blAlgorithmsLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function copies content
// from input buffer to output buffer
// stopping whenever it reaches the end
// of either buffer
//-------------------------------------------------------------------
template<typename blBuffer1IteratorType,
         typename blBuffer2IteratorType>

inline blBuffer2IteratorType copy(const blBuffer1IteratorType& inputBegin,
                                  const blBuffer1IteratorType& inputEnd,
                                  const blBuffer2IteratorType& outputBegin,
                                  const blBuffer2IteratorType& outputEnd,
                                  const std::ptrdiff_t& numberOfTimesToCycleOverInputIfInputIteratorIsCyclic,
                                  const std::ptrdiff_t& numberOfTimesToCycleOverOutputIfOutputIteratorIsCyclic)
{
    auto currentInputIter = inputBegin;
    auto currentOutputIter = outputBegin;

    std::ptrdiff_t numberOfInputRepeats = 0;
    std::ptrdiff_t numberOfOutputRepeats = 0;

    while( (currentInputIter != inputEnd) &&
           (currentOutputIter != outputEnd) &&
           (numberOfInputRepeats <= numberOfTimesToCycleOverInputIfInputIteratorIsCyclic) &&
           (numberOfOutputRepeats <= numberOfTimesToCycleOverOutputIfOutputIteratorIsCyclic) )
    {
        (*currentOutputIter) = (*currentInputIter);

        ++currentInputIter;
        ++currentOutputIter;

        if(currentInputIter == inputBegin)
            ++numberOfInputRepeats;

        if(currentOutputIter == outputBegin)
            ++numberOfOutputRepeats;
    }



    return currentOutputIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Overload with predicate functor
//-------------------------------------------------------------------
template<typename blBuffer1IteratorType,
         typename blBuffer2IteratorType>

inline blBuffer2IteratorType copy(const blBuffer1IteratorType& inputBegin,
                                  const blBuffer1IteratorType& inputEnd,
                                  const blBuffer2IteratorType& outputBegin,
                                  const blBuffer2IteratorType& outputEnd,
                                  const std::ptrdiff_t& numberOfTimesToCycleOverInputIfInputIteratorIsCyclic,
                                  const std::ptrdiff_t& numberOfTimesToCycleOverOutputIfOutputIteratorIsCyclic,
                                  blBuffer1IteratorType& inputBufferPlaceAfterLastCopiedElement)
{
    auto currentInputIter = inputBegin;
    auto currentOutputIter = outputBegin;

    std::ptrdiff_t numberOfInputRepeats = 0;
    std::ptrdiff_t numberOfOutputRepeats = 0;

    while( (currentInputIter != inputEnd) &&
           (currentOutputIter != outputEnd) &&
           (numberOfInputRepeats <= numberOfTimesToCycleOverInputIfInputIteratorIsCyclic) &&
           (numberOfOutputRepeats <= numberOfTimesToCycleOverOutputIfOutputIteratorIsCyclic) )
    {
        (*currentOutputIter) = (*currentInputIter);

        ++currentInputIter;
        ++currentOutputIter;

        if(currentInputIter == inputBegin)
            ++numberOfInputRepeats;

        if(currentOutputIter == outputBegin)
            ++numberOfOutputRepeats;
    }

    inputBufferPlaceAfterLastCopiedElement = currentInputIter;



    return currentOutputIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function searches for tokens in a buffer
//-------------------------------------------------------------------
template<typename blTokenType,
         typename blBufferIteratorType>

inline blBufferIteratorType find(const blBufferIteratorType& beginIter,
                                 const blBufferIteratorType& endIter,
                                 const blTokenType& token,
                                 const std::ptrdiff_t& numberOfTimesToCycleIfIteratorIsCyclic)
{
    blBufferIteratorType currentIter = beginIter;

    std::ptrdiff_t numberOfRepeats = 0;

    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if((*currentIter) == token)
        {
            return currentIter;
        }

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    return endIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Overload with predicate functor
//-------------------------------------------------------------------
template<typename blTokenType,
         typename blBufferIteratorType,
         typename blPredicateFunctorType>

inline blBufferIteratorType find(blBufferIteratorType beginIter,
                                 const blBufferIteratorType& endIter,
                                 const blTokenType& token,
                                 const std::ptrdiff_t& numberOfTimesToCycleIfIteratorIsCyclic,
                                 const blPredicateFunctorType& predicateFunctor)
{
    blBufferIteratorType currentIter = beginIter;

    std::ptrdiff_t numberOfRepeats = 0;

    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if(predicateFunctor((*currentIter),token))
        {
            return currentIter;
        }

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    return endIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function searches a buffer for the
// last occurrance of a specified token
//-------------------------------------------------------------------
template<typename blTokenType,
         typename blBufferIteratorType>

inline blBufferIteratorType find_last(const blBufferIteratorType& beginIter,
                                      const blBufferIteratorType& endIter,
                                      const blTokenType& token,
                                      const std::ptrdiff_t& numberOfTimesToCycleIfIteratorIsCyclic)
{
    blBufferIteratorType currentIter = beginIter;

    blBufferIteratorType iterToLastOccurrence = currentIter;

    std::ptrdiff_t numberOfRepeats = 0;



    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if((*currentIter) == token)
            iterToLastOccurrence = currentIter;

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    if((*iterToLastOccurrence) == token)
        return iterToLastOccurrence;
    else
        return endIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Overload with predicate functor
//-------------------------------------------------------------------
template<typename blTokenType,
         typename blBufferIteratorType,
         typename blPredicateFunctorType>

inline blBufferIteratorType find_last(const blBufferIteratorType& beginIter,
                                      const blBufferIteratorType& endIter,
                                      const blTokenType& token,
                                      const std::ptrdiff_t& numberOfTimesToCycleIfIteratorIsCyclic,
                                      const blPredicateFunctorType& predicateFunctor)
{
    blBufferIteratorType currentIter = beginIter;

    blBufferIteratorType iterToLastOccurrence = currentIter;

    std::ptrdiff_t numberOfRepeats = 0;



    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if(predicateFunctor(*currentIter,token))
            iterToLastOccurrence = currentIter;

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    if((*iterToLastOccurrence) == token)
        return iterToLastOccurrence;
    else
        return endIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function searches for first place in a buffer
// where a specified token does not occur
//-------------------------------------------------------------------
template<typename blTokenType,
         typename blBufferIteratorType>

inline blBufferIteratorType find_not(const blBufferIteratorType& beginIter,
                                     const blBufferIteratorType& endIter,
                                     const blTokenType& token,
                                     const std::ptrdiff_t& numberOfTimesToCycleIfIteratorIsCyclic)
{
    blBufferIteratorType currentIter = beginIter;

    std::ptrdiff_t numberOfRepeats = 0;

    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if((*currentIter) != token)
        {
            return currentIter;
        }

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    return endIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Overload with predicate functor
//-------------------------------------------------------------------
template<typename blTokenType,
         typename blBufferIteratorType,
         typename blPredicateFunctorType>

inline blBufferIteratorType find_not(blBufferIteratorType beginIter,
                                     const blBufferIteratorType& endIter,
                                     const blTokenType& token,
                                     const std::ptrdiff_t& numberOfTimesToCycleIfIteratorIsCyclic,
                                     const blPredicateFunctorType& predicateFunctor)
{
    blBufferIteratorType currentIter = beginIter;

    std::ptrdiff_t numberOfRepeats = 0;

    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if(!predicateFunctor((*currentIter),token))
        {
            return currentIter;
        }

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    return endIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function searches a buffer for the
// last place in the buffer where a specified token
// does not appear
//-------------------------------------------------------------------
template<typename blTokenType,
         typename blBufferIteratorType>

inline blBufferIteratorType find_last_not(const blBufferIteratorType& beginIter,
                                          const blBufferIteratorType& endIter,
                                          const blTokenType& token,
                                          const std::ptrdiff_t& numberOfTimesToCycleIfIteratorIsCyclic)
{
    blBufferIteratorType currentIter = beginIter;

    blBufferIteratorType iterToLastNotOccurrence = currentIter;

    std::ptrdiff_t numberOfRepeats = 0;



    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if((*currentIter) != token)
            iterToLastNotOccurrence = currentIter;

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    if((*iterToLastNotOccurrence) != token)
        return iterToLastNotOccurrence;
    else
        return endIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Overload with predicate functor
//-------------------------------------------------------------------
template<typename blTokenType,
         typename blBufferIteratorType,
         typename blPredicateFunctorType>

inline blBufferIteratorType find_last_not(const blBufferIteratorType& beginIter,
                                          const blBufferIteratorType& endIter,
                                          const blTokenType& token,
                                          const std::ptrdiff_t& numberOfTimesToCycleIfIteratorIsCyclic,
                                          const blPredicateFunctorType& predicateFunctor)
{
    blBufferIteratorType currentIter = beginIter;

    blBufferIteratorType iterToLastNotOccurrence = currentIter;

    std::ptrdiff_t numberOfRepeats = 0;



    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if(!predicateFunctor(*currentIter,token))
            iterToLastNotOccurrence = currentIter;

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    if(!predicateFunctor(*iterToLastNotOccurrence,token))
        return iterToLastNotOccurrence;
    else
        return endIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function searches a buffer for any of the user
// specified tokens and returns an iterator to the location where
// it found the first matching token
//-------------------------------------------------------------------
template<typename blBufferIteratorType,
         typename blTokenIteratorType>

inline blBufferIteratorType find_first_of(const blBufferIteratorType& bufferBeginIter,
                                          const blBufferIteratorType& bufferEndIter,
                                          const blTokenIteratorType& tokenListBeginIter,
                                          const blTokenIteratorType& tokenListEndIter,
                                          const std::ptrdiff_t& numberOfTimesToCycleIfIteratorIsCyclic)
{
    blBufferIteratorType bufferCurrentIter = bufferBeginIter;

    std::ptrdiff_t numberOfRepeats = 0;

    blTokenIteratorType tokenIter = tokenListBeginIter;



    while(bufferCurrentIter != bufferEndIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        tokenIter = find(tokenListBeginIter,tokenListEndIter,*bufferCurrentIter,0);

        if(tokenIter != tokenListEndIter)
            return bufferCurrentIter;

        ++bufferCurrentIter;
    }



    return bufferEndIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Overload with predicate functor
//-------------------------------------------------------------------
template<typename blBufferIteratorType,
         typename blTokenIteratorType,
         typename blPredicateFunctorType>

inline blBufferIteratorType find_first_of(const blBufferIteratorType& bufferBeginIter,
                                          const blBufferIteratorType& bufferEndIter,
                                          const blTokenIteratorType& tokenListBeginIter,
                                          const blTokenIteratorType& tokenListEndIter,
                                          const std::ptrdiff_t& numberOfTimesToCycleIfIteratorIsCyclic,
                                          const blPredicateFunctorType& predicateFunctor)
{
    blBufferIteratorType bufferCurrentIter = bufferBeginIter;

    std::ptrdiff_t numberOfRepeats = 0;

    blTokenIteratorType tokenIter = tokenListBeginIter;



    while(bufferCurrentIter != bufferEndIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        tokenIter = find(tokenListBeginIter,tokenListEndIter,*bufferCurrentIter,0,predicateFunctor);

        if(tokenIter != tokenListEndIter)
            return bufferCurrentIter;

        ++bufferCurrentIter;
    }



    return bufferEndIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function searches a buffer for the first place
// not matching any of the specified tokens
//-------------------------------------------------------------------
template<typename blBufferIteratorType,
         typename blTokenIteratorType>

inline blBufferIteratorType find_first_not_of(const blBufferIteratorType& bufferBeginIter,
                                              const blBufferIteratorType& bufferEndIter,
                                              const blTokenIteratorType& tokenListBeginIter,
                                              const blTokenIteratorType& tokenListEndIter,
                                              const std::ptrdiff_t& numberOfTimesToCycleIfIteratorIsCyclic)
{
    blBufferIteratorType bufferCurrentIter = bufferBeginIter;

    std::ptrdiff_t numberOfRepeats = 0;

    blTokenIteratorType tokenIter = tokenListBeginIter;



    while(bufferCurrentIter != bufferEndIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        tokenIter = find(tokenListBeginIter,tokenListEndIter,*bufferCurrentIter,0);

        if(tokenIter == tokenListEndIter)
            return bufferCurrentIter;

        ++bufferCurrentIter;
    }



    return bufferEndIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Overload with predicate functor
//-------------------------------------------------------------------
template<typename blBufferIteratorType,
         typename blTokenIteratorType,
         typename blPredicateFunctorType>

inline blBufferIteratorType find_first_not_of(const blBufferIteratorType& bufferBeginIter,
                                              const blBufferIteratorType& bufferEndIter,
                                              const blTokenIteratorType& tokenListBeginIter,
                                              const blTokenIteratorType& tokenListEndIter,
                                              const std::ptrdiff_t& numberOfTimesToCycleIfIteratorIsCyclic,
                                              const blPredicateFunctorType& predicateFunctor)
{
    blBufferIteratorType bufferCurrentIter = bufferBeginIter;

    std::ptrdiff_t numberOfRepeats = 0;

    blTokenIteratorType tokenIter = tokenListBeginIter;



    while(bufferCurrentIter != bufferEndIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        tokenIter = find(tokenListBeginIter,tokenListEndIter,*bufferCurrentIter,0,predicateFunctor);

        if(tokenIter == tokenListEndIter)
            return bufferCurrentIter;

        ++bufferCurrentIter;
    }



    return bufferEndIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function searches for a sequence within a
// user specified buffer and returns the iterator to the
// beginning of the sequence
//-------------------------------------------------------------------
template<typename blBufferIteratorType,
         typename blSequenceIteratorType>

inline blBufferIteratorType search(const blBufferIteratorType& bufferBeginIter,
                                   const blBufferIteratorType& bufferEndIter,
                                   const blSequenceIteratorType& sequenceBeginIter,
                                   const blSequenceIteratorType& sequenceEndIter)
{
    for(auto bufferIter = bufferBeginIter;
        bufferIter != bufferEndIter;
        ++bufferIter)
    {
        auto bufferCheckIter = bufferIter;

        for(auto sequenceIter = sequenceBeginIter;
            sequenceIter != sequenceEndIter;
            ++sequenceIter,++bufferCheckIter)
        {
            if(sequenceIter == sequenceEndIter)
                return bufferIter;
            else if(bufferCheckIter == bufferEndIter)
                return bufferEndIter;
            else if(*bufferCheckIter != *sequenceIter)
                break;
        }
    }

    return bufferEndIter;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_CYCLICSTLALGORITHMS_HPP
