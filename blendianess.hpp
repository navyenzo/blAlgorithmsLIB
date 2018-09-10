#ifndef BL_ENDIANESS_HPP
#define BL_ENDIANESS_HPP



//-------------------------------------------------------------------
// NOTE: These functions are defined within the
// blAlgorithmsLIB namespace
//-------------------------------------------------------------------
namespace blAlgorithmsLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Generic function swapping bytes from
// little endian to big endian and viceversa
//-------------------------------------------------------------------
template<typename blDataType>

blDataType swapEndianess(const blDataType& value)
{
    blDataType swappedValue;

    for(int i = 0; i < sizeof(blDataType); ++i)
    {
        reinterpret_cast<unsigned char*>(&swappedValue)[i] = reinterpret_cast<const unsigned char*>(&value)[sizeof(blDataType) - 1 - i];
    }

    return swappedValue;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------

#endif // BL_ENDIANESS_HPP
