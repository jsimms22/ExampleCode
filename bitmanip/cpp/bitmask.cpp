/* https://www.learncpp.com/cpp-tutorial/bit-manipulation-with-bitwise-operators-and-bit-masks/ */

#include <bitset>
#include <iostream>
#include <cstdint>
#include <bit>

// A bit mask is a predefined set of bits that is used to select which 
// specifc bits will be modified by subsequent operations

// Defining bit masks in C++14
[[maybe_unused]] constexpr std::uint8_t mask0_14{ 0b0000'0001 }; // represents bit 0
[[maybe_unused]] constexpr std::uint8_t mask1_14{ 0b0000'0010 }; // represents bit 1
[[maybe_unused]] constexpr std::uint8_t mask2_14{ 0b0000'0100 }; // represents bit 2
[[maybe_unused]] constexpr std::uint8_t mask3_14{ 0b0000'1000 }; // represents bit 3
[[maybe_unused]] constexpr std::uint8_t mask4_14{ 0b0001'0000 }; // represents bit 4
[[maybe_unused]] constexpr std::uint8_t mask5_14{ 0b0010'0000 }; // represents bit 5
[[maybe_unused]] constexpr std::uint8_t mask6_14{ 0b0100'0000 }; // represents bit 6
[[maybe_unused]] constexpr std::uint8_t mask7_14{ 0b1000'0000 }; // represents bit 7

// Defining bit masks in C++11 (no binary literals)
[[maybe_unused]] constexpr std::uint8_t mask0_11a{ 0x01 }; // hex for 0000 0001
[[maybe_unused]] constexpr std::uint8_t mask1_11a{ 0x02 }; // hex for 0000 0010
[[maybe_unused]] constexpr std::uint8_t mask2_11a{ 0x04 }; // hex for 0000 0100
[[maybe_unused]] constexpr std::uint8_t mask3_11a{ 0x08 }; // hex for 0000 1000
[[maybe_unused]] constexpr std::uint8_t mask4_11a{ 0x10 }; // hex for 0001 0000
[[maybe_unused]] constexpr std::uint8_t mask5_11a{ 0x20 }; // hex for 0010 0000
[[maybe_unused]] constexpr std::uint8_t mask6_11a{ 0x40 }; // hex for 0100 0000
[[maybe_unused]] constexpr std::uint8_t mask7_11a{ 0x80 }; // hex for 1000 0000

// however, an easier method may be to use left-shifter operator
// 0x01 may end up dropping the leading 0 making it harder to read
[[maybe_unused]] constexpr std::uint8_t mask0_11b{ 1 << 0 }; // 0000 0001
[[maybe_unused]] constexpr std::uint8_t mask1_11b{ 1 << 1 }; // 0000 0010
[[maybe_unused]] constexpr std::uint8_t mask2_11b{ 1 << 2 }; // 0000 0100
[[maybe_unused]] constexpr std::uint8_t mask3_11b{ 1 << 3 }; // 0000 1000
[[maybe_unused]] constexpr std::uint8_t mask4_11b{ 1 << 4 }; // 0001 0000
[[maybe_unused]] constexpr std::uint8_t mask5_11b{ 1 << 5 }; // 0010 0000
[[maybe_unused]] constexpr std::uint8_t mask6_11b{ 1 << 6 }; // 0100 0000
[[maybe_unused]] constexpr std::uint8_t mask7_11b{ 1 << 7 }; // 1000 0000

int main()
{
    std::uint8_t flags{ 0b0000'0101 };

    // Example 1: Testing a bit
    std::cout << "Example 1:\n";
    std::cout << "bit 0 is " << (static_cast<bool>(flags & mask0_14) ? "on\n" : "off\n");
    std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1_14) ? "on\n" : "off\n");

    // Example 2: Setting a bit
    std::cout << "\nExample 2:\n";
    flags |= mask1_14; // turn on bit 1 with bitwise OR
    std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1_14) ? "on\n" : "off\n");

    // Exmaple 3: Setting a bit with multiple masks
    std::cout << "\nExample 3:\n";
    flags |= (mask4_14 | mask5_14); // turn bits 4 and 5 on at the same time
    std::cout << static_cast<std::bitset<8>>(flags) << '\n';

    // Exmaple 4: Resetting a bit
    std::cout << "\nExample 4:\n";
    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2_14) ? "on\n" : "off\n");
    flags &= ~mask2_14; // turn off bit 2
    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2_14) ? "on\n" : "off\n");
    flags &= ~(mask4_14 | mask5_14); // turn bits 4 and 5 off at the same time
    std::cout << static_cast<std::bitset<8>>(flags) << '\n';

    // NOTE: flags &= static_cast<std::uint8_t>(~mask2);
    // May be necessary if the compiler complains about size differences

    // Exmaple 5: Flipping a bit
    std::cout << "\nExample 5:\n";
    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2_14) ? "on\n" : "off\n");
    flags &= ~mask2_14; // turn off bit 2
    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2_14) ? "on\n" : "off\n");

    return 0;
}