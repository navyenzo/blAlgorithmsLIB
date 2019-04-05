#ifndef BL_BYTESMANIPULATION_HPP
#define BL_BYTESMANIPULATION_HPP



//-------------------------------------------------------------------
// NOTE: These functions are defined within the
// blAlgorithmsLIB namespace
//-------------------------------------------------------------------
namespace blAlgorithmsLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Generic functions swapping bytes from
// little endian to big endian and viceversa
//-------------------------------------------------------------------
template<typename blDataType>

inline blDataType swapEndianess(const blDataType& value)
{
    blDataType swappedValue;

    for(int i = 0; i < sizeof(blDataType); ++i)
    {
        reinterpret_cast<unsigned char*>(&swappedValue)[i] = reinterpret_cast<const unsigned char*>(&value)[sizeof(blDataType) - 1 - i];
    }

    return swappedValue;
}



template<typename blDataType>

inline void swapEndianess(const blDataType& sourceValue,
                          blDataType& destinationValue)
{
    for(int i = 0; i < sizeof(blDataType); ++i)
    {
        reinterpret_cast<unsigned char*>(&destinationValue)[i] = reinterpret_cast<const unsigned char*>(&sourceValue)[sizeof(blDataType) - 1 - i];
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_BYTESMANIPULATION_HPP
