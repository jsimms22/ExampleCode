/* https://www.learncpp.com/cpp-tutorial/bitwise-operators/ */

#include <iostream>
#include <bitset>
#include <iomanip>  

/* C++ provides 6 bit manip operators, often called bitwise operators:
 * OPERATOR         SYMBOL      FORM        OPERATION
 * left shift       <<          x << y      all bits in x shifted left y bits 
 * right shift      >>          x >> y      all bits in x shifted right y bits
 * bitwise NOT      ~           ~x          all bits in x flipped
 * bitwise AND      &           x & y       each bit in x AND each bit in y
 * bitwise OR       |           x | y       each bit in x OR each bit in y
 * bitwise XOR      ^           x ^ y       each bit in x XOR each bit in y
*/

/* C++ provides 6 bit manip assignment operators, often called bitwise assignment operators:
 * OPERATOR         SYMBOL      FORM        OPERATION
 * left shift       <<=         x <<= y     shift x left by y bits
 * right shift      >>=         x >>= y     shift x right by y bits
 * bitwise AND      &=          x &= y      assign x & y to x
 * bitwise OR       |=          x |= y      assign x | y to x
 * bitwise XOR      ^=          x ^= y      assign x ^ y to x
*/

int main()
{
    // Example 1:
    std::cout << "Example 1:\n";
    std::bitset<4> x{ 0b1100 };

    std::cout << x << "\n";
    std::cout << (x >> 1) << '\n'; // shift right by 1, yielding 0110
    std::cout << (x << 1) << '\n'; // shift left by 1, yielding 1100

    // bits shifted off the edge of the memory allocated space are lost forever
    std::cout << (x << 2) << '\n'; // bits shifted let but still within allocated memory, yielding 0000
    std::cout << (x >> 2) << '\n'; // undo previous shift, yielding 1100
    std::cout << (x >> 4) << '\n'; // bits shifted too far to the right, yielding 0000
    std::cout << (x << 4) << '\n'; // attempt to undo error, yielding 0000

    // Example 2:
    std::cout << "\nExample 2:\n";

    // bitwise NOT is dependent on what size your data type is
    std::cout << std::setw(16) << "Starting with: ";
    std::cout << std::bitset<4>{0b0100} << ' ' << std::bitset<8>{ 0b0100 } << '\n';
    std::cout << std::setw(16) << "After NOT flip: "; 
    std::cout << ~std::bitset<4>{0b0100} << ' ' << ~std::bitset<8>{ 0b0100 } << '\n';

    // Example 3:
    std::cout << "\nExample 3:\n";

    // bitwise OR
    std::cout << "0101 " << "OR\n";
    std::cout << "0110\n";
    std::cout << "----\n";
    std::cout << (std::bitset<4>{ 0b0101 } | std::bitset<4>{ 0b0110 }) << '\n';

    // Example 4:
    std::cout << "\nExample 4:\n";

    // bitwise OR
    std::cout << "0101 " << "AND\n";
    std::cout << "0110\n";
    std::cout << "----\n";
    std::cout << (std::bitset<4>{ 0b0101 } & std::bitset<4>{ 0b0110 }) << '\n';

    // Example 5:
    std::cout << "\nExample 5:\n";

    // bitwise OR
    std::cout << "0101 " << "XOR\n";
    std::cout << "0110\n";
    std::cout << "----\n";
    std::cout << (std::bitset<4>{ 0b0101 } ^ std::bitset<4>{ 0b0110 }) << '\n';

    return 0;
}