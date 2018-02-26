#ifndef BL_CONSTANTSANDENUMS_HPP
#define BL_CONSTANTSANDENUMS_HPP



//-------------------------------------------------------------------
// NOTE: These constants and enums are defined within the
// blAlgorithmsLIB namespace
//-------------------------------------------------------------------
namespace blAlgorithmsLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Enum used to decide how to advance iterators
// for matrix iterators defined in this library
//-------------------------------------------------------------------
enum blAdvancingIteratorMethod {COL_MAJOR = 0,
                                ROW_MAJOR = 1,
                                COL_PAGE_MAJOR = 2,
                                ROW_PAGE_MAJOR = 3};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_CONSTANTSANDENUMS_HPP
