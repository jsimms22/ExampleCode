/* https://www.learncpp.com/cpp-tutorial/bit-flags-and-bit-manipulation-via-stdbitset/ */

#include <iostream>
#include <bitset> // for std::bitset

[[maybe_unused]] constexpr int isHungry   { 0 };
[[maybe_unused]] constexpr int isSad      { 1 };
[[maybe_unused]] constexpr int isMad      { 2 };
[[maybe_unused]] constexpr int isHappy    { 3 };
[[maybe_unused]] constexpr int isLaughing { 4 };
[[maybe_unused]] constexpr int isAsleep   { 5 };
[[maybe_unused]] constexpr int isDead     { 6 };
[[maybe_unused]] constexpr int isCrying   { 7 };

int main()
{
    // object holding a single value
    int foo {5};
    std::cout << foo << std::endl;

    // Example 1
    std::bitset<8> mybitset{}; // 8 bits in memory
    // bit manip is one of the few times when you should unambiguously use uint

    /* 7654 3210 -> bit position
     * 0000 0101 -> bit sequence
     * order is generally little endian (right to left)
     * in our example, order is 0 then 2
     */

    /* std::bitset provide 4 key member functions that are useful for bit manip
     * test() - allows us to query whether a bit is 0 or 1
     * set() - allows us to turn a bit on (does nothing if bit is already on)
     * reset() - allows us to turn a bit off (doess nothing if bit is already off)
     * flip() - allows us to flip a bit value from a 0 to a 1 or vica versa
     */

    // Example 2
    std::cout << "\nExample 2:\n";
    std::bitset<8> bits{ 0b0000'0101 }; // bit pattern 0000 0101

    bits.set(3); // set bit position 3 to 1 (0000 1101)
    bits.flip(4); // flip bit 4 (0001 1101)
    bits.reset(4); // set bit 4 off (0000 1101)

    std::cout << "All the bits: " << bits << '\n';
    std::cout << "Bit 3 has value: " << bits.test(3) << '\n';
    std::cout << "Bit 4 has value: " << bits.test(4) << '\n';

    //Example 3
    std::cout << "\nExample 3:\n";
    std::bitset<8> me{ 0b0000'0101 };

    me.set(isHappy);
    me.flip(isLaughing);
    me.reset(isLaughing);
 
    std::cout << "All the bits: " << me << '\n';
    std::cout << "I am happy: " << me.test(isHappy) << '\n';
    std::cout << "I am laughing: " << me.test(isLaughing) << '\n';

    /* std::bitset is optimized for speed, not memory savings
     * The size of a std::bitset is typically the number of bytes needed to hold the bits
     * rounded up to the nearest sizeof(size_t)
     * which is 4 bytes on 32-bit machines, and 8-bytes on 64-bit machines
     * 
     * std::bitset<8> will typically use either 4 or 8 bytes of memory, 
     * even though it technically only needs 1 byte to store 8 bits
    */

   /* There are a few other member functions that are often useful:
    * size() - returns the number of bits in the bitset
    * count() - returns the number of bits in the set that are set to true
    * all() - returns a boolean indicating whether all bits are set to true
    * any() - returns a boolean indicating whether any bits are set to true
    * none() - returns a boolean indicating whether no bits are set to true
   */

    // Example 4
    std::cout << "\nExample 4:\n";
    std::bitset<8> bits2{ 0b0000'0101 };
    std::cout << bits2.size() << " bits are in the bitset\n";
    std::cout << bits2.count() << " bits are set to 1\n";

    std::cout << std::boolalpha;
    std::cout << "All bits are true: " << bits.all() << '\n';
    std::cout << "Some bits are true: " << bits.any() << '\n';
    std::cout << "No bits are true: " << bits.none() << '\n';

    return 0;
}   