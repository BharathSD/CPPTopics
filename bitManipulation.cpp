#include <iostream>
#include <bit>
#include <bitset>

/*
Bit manipulation library in cpp20.
The usage of bit manipulation functions can be seen in the example below.
*/
int main() {

#pragma region std::bit_cast
    // std::bit_cast example
    unsigned int value = 0b0000'1111; // 15 in decimal
    float floatValue = std::bit_cast<float>(value);
    std::cout << "Float value: " << floatValue << std::endl;

    constexpr double f64v = 19880124.0; 
    constexpr auto u64v = std::bit_cast<std::uint64_t>(f64v);
    std::cout
        << "std::bit_cast<std::uint64_t>(" << std::fixed << f64v << ") == 0x"
        << std::hex << u64v << std::endl;

    
    constexpr std::uint64_t u64v1 = 0x3fe9000000000000ull;
    constexpr auto f64v1 = std::bit_cast<double>(u64v1);
    std::cout
        << "std::bit_cast<double>(0x" << std::hex << u64v1 << ") == "
        << std::fixed << f64v1 << std::endl;

    
    constexpr std::uint32_t u32v1 = 0x41424344;
    constexpr auto f32v1 = std::bit_cast<float>(u32v1);
    std::cout
        << "std::bit_cast<float>(0x" << std::hex << u32v1 << ") == "
        << std::fixed << f32v1 << std::endl;
#pragma endregion

#pragma region std::byte_swap
/*
Demonstrates the use of std::byteswap for swapping byte order.
This is used to convert between little-endian and big-endian representations.
*/
    // std::byteswap example
    constexpr std::uint16_t u16v2 = 0x4142;
    constexpr auto u16v2_swapped = std::byteswap(u16v2);
    std::cout
        << "std::byteswap(0x" << std::hex << u16v2 << ") == 0x"
        << std::hex << u16v2_swapped << std::endl;

    constexpr std::uint32_t u32v2 = 0x41424344;
    constexpr auto u32v2_swapped = std::byteswap(u32v2);
    std::cout
        << "std::byteswap(0x" << std::hex << u32v2 << ") == 0x"
        << std::hex << u32v2_swapped << std::endl;

    constexpr std::uint64_t u64v2 = 0x4142434445464748ull;
    constexpr auto u64v2_swapped = std::byteswap(u64v2);
    std::cout
        << "std::byteswap(0x" << std::hex << u64v2 << ") == 0x"
        << std::hex << u64v2_swapped << std::endl;

    constexpr std::uint8_t u8v2 = 0x41;
    constexpr auto u8v2_swapped = std::byteswap(u8v2);
    std::cout
        << "std::byteswap(0x" << std::hex << u8v2 << ") == 0x"
        << std::hex << u8v2_swapped << std::endl;
#pragma endregion

#pragma region std::has_single_bit
/*
std::has_single_bit can be used to check if a value is a power of two.
*/
    constexpr std::uint32_t u32v3 = 0x00000001;
    std::cout << "std::has_single_bit(0x" << std::hex << u32v3 << ") == "
              << std::boolalpha << std::has_single_bit(u32v3) << std::endl;

    constexpr std::uint32_t u32v3_1 = 0x00000002;
    std::cout << "std::has_single_bit(0x" << std::hex << u32v3_1 << ") == "
              << std::boolalpha << std::has_single_bit(u32v3_1) << std::endl;

    constexpr std::uint32_t u32v3_2 = 0x00000003;
    std::cout << "std::has_single_bit(0x" << std::hex << u32v3_2 << ") == "
              << std::boolalpha << std::has_single_bit(u32v3_2) << std::endl;

#pragma endregion

#pragma region std::bit_ceil
/*
std::bit_ceil can be used to find the smallest power of two greater than or equal to a given value.
*/
    constexpr std::uint32_t u32v4 = 0x00000001;
    std::cout << "std::bit_ceil(0x" << std::hex << u32v4 << ") == 0x"
              << std::hex << std::bit_ceil(u32v4) << std::endl;

    constexpr std::uint32_t u32v4_1 = 0x00000002;
    std::cout << "std::bit_ceil(0x" << std::hex << u32v4_1 << ") == 0x"
              << std::hex << std::bit_ceil(u32v4_1) << std::endl;

    constexpr std::uint32_t u32v4_2 = 0x00000003;
    std::cout << "std::bit_ceil(0x" << std::hex << u32v4_2 << ") == 0x"
              << std::hex << std::bit_ceil(u32v4_2) << std::endl;

    constexpr std::uint32_t u32v4_3 = 0x00000014;
    std::cout << "std::bit_ceil(0x" << std::hex << u32v4_3 << ") == 0x"
              << std::hex << std::bit_ceil(u32v4_3) << std::endl;

#pragma endregion

#pragma region std::bit_floor
/*
std::bit_floor can be used to find the largest power of two less than or equal to a given value.
*/
    constexpr std::uint32_t u32v5 = 0x00000001;
    std::cout << "std::bit_floor(0x" << std::hex << u32v5 << ") == 0x"
              << std::hex << std::bit_floor(u32v5) << std::endl;

    constexpr std::uint32_t u32v5_1 = 0x00000002;
    std::cout << "std::bit_floor(0x" << std::hex << u32v5_1 << ") == 0x"
              << std::hex << std::bit_floor(u32v5_1) << std::endl;

    constexpr std::uint32_t u32v5_2 = 0x00000003;
    std::cout << "std::bit_floor(0x" << std::hex << u32v5_2 << ") == 0x"
              << std::hex << std::bit_floor(u32v5_2) << std::endl;
    
    constexpr std::uint32_t u32v5_3 = 0x00000014;
    std::cout << "std::bit_floor(0x" << std::hex << u32v5_3 << ") == 0x"
              << std::hex << std::bit_floor(u32v5_3) << std::endl;
#pragma endregion

#pragma region std::bit_width
    constexpr std::uint32_t u32v6 = 0x00000001;
    std::cout << "std::bit_width(0x" << std::hex << u32v6 << ") == "
              << std::dec << std::bit_width(u32v6) << std::endl;
    
    constexpr std::uint32_t u32v6_1 = 0x00000002;
    std::cout << "std::bit_width(0x" << std::hex << u32v6_1 << ") == "
              << std::dec << std::bit_width(u32v6_1) << std::endl;

    constexpr std::uint32_t u32v6_2 = 0x00000003;
    std::cout << "std::bit_width(0x" << std::hex << u32v6_2 << ") == "
              << std::dec << std::bit_width(u32v6_2) << std::endl;

    constexpr std::uint32_t u32v6_3 = 0x00000014;
    std::cout << "std::bit_width(0x" << std::hex << u32v6_3 << ") == "
              << std::dec << std::bit_width(u32v6_3) << std::endl;

#pragma endregion

#pragma region std::rotl
    constexpr std::uint8_t u8v7 = 0b0001'0011;
    constexpr auto u8v7_rotl = std::rotl(u8v7, 2);
    std::cout
        << "std::rotl(0b" << std::bitset<8>(u8v7) << ", 2) == 0b"
        << std::bitset<8>(u8v7_rotl) << std::endl;

    constexpr std::uint8_t u8v7_1 = 0b1001'0011;
    constexpr auto u8v7_1_rotl = std::rotl(u8v7_1, 3);
    std::cout
        << "std::rotl(0b" << std::bitset<8>(u8v7_1) << ", 3) == 0b"
        << std::bitset<8>(u8v7_1_rotl) << std::endl;
#pragma endregion

#pragma region std::rotr
    constexpr std::uint8_t u9v7 = 0b0001'0011;
    constexpr auto u9v7_rotr = std::rotr(u9v7, 2);
    std::cout
        << "std::rotr(0b" << std::bitset<8>(u9v7) << ", 2) == 0b"
        << std::bitset<8>(u9v7_rotr) << std::endl;

    constexpr std::uint8_t u9v7_1 = 0b1001'0011;
    constexpr auto u9v7_1_rotr = std::rotr(u9v7_1, 3);
    std::cout
        << "std::rotr(0b" << std::bitset<8>(u9v7_1) << ", 3) == 0b"
        << std::bitset<8>(u9v7_1_rotr) << std::endl;

    constexpr std::uint8_t u9v7_2 = 0b1001'0011;
    constexpr auto u9v7_2_rotr = std::rotr(u9v7_2, 3);
    std::cout
        << "std::rotr(0b" << std::bitset<8>(u9v7_2) << ", 3) == 0b"
        << std::bitset<8>(u9v7_2_rotr) << std::endl;
#pragma endregion

#pragma region std::countl_zero
    constexpr std::uint32_t u32v8 = 0x00000001;
    std::cout << "std::countl_zero(0x" << std::hex << u32v8 << ") == "
              << std::dec << std::countl_zero(u32v8) << std::endl;

    constexpr std::uint32_t u32v8_1 = 0x00000002;
    std::cout << "std::countl_zero(0x" << std::hex << u32v8_1 << ") == "
              << std::dec << std::countl_zero(u32v8_1) << std::endl;

    constexpr std::uint32_t u32v8_2 = 0x00000003;
    std::cout << "std::countl_zero(0x" << std::hex << u32v8_2 << ") == "
              << std::dec << std::countl_zero(u32v8_2) << std::endl;

    constexpr std::uint32_t u32v8_3 = 0x00000014;
    std::cout << "std::countl_zero(0x" << std::hex << u32v8_3 << ") == "
              << std::dec << std::countl_zero(u32v8_3) << std::endl;
#pragma endregion

#pragma region std::countl_one
    constexpr std::uint32_t u32v9 = 0x00000001;
    std::cout << "std::countl_one(0x" << std::hex << u32v9 << ") == "
              << std::dec << std::countl_one(u32v9) << std::endl;

    constexpr std::uint32_t u32v9_1 = 0x00000002;
    std::cout << "std::countl_one(0x" << std::hex << u32v9_1 << ") == "
              << std::dec << std::countl_one(u32v9_1) << std::endl;

    constexpr std::uint32_t u32v9_2 = 0x00000003;
    std::cout << "std::countl_one(0x" << std::hex << u32v9_2 << ") == "
              << std::dec << std::countl_one(u32v9_2) << std::endl;

    constexpr std::uint32_t u32v9_3 = 0x00000014;
    std::cout << "std::countl_one(0x" << std::hex << u32v9_3 << ") == "
              << std::dec << std::countl_one(u32v9_3) << std::endl;
#pragma endregion

#pragma region std::countr_zero
    constexpr std::uint32_t u32v10 = 0x00000001;
    std::cout << "std::countr_zero(0x" << std::hex << u32v10 << ") == "
              << std::dec << std::countr_zero(u32v10) << std::endl;

    constexpr std::uint32_t u32v10_1 = 0x00000002;
    std::cout << "std::countr_zero(0x" << std::hex << u32v10_1 << ") == "
              << std::dec << std::countr_zero(u32v10_1) << std::endl;

    constexpr std::uint32_t u32v10_2 = 0x00000003;
    std::cout << "std::countr_zero(0x" << std::hex << u32v10_2 << ") == "
              << std::dec << std::countr_zero(u32v10_2) << std::endl;

    constexpr std::uint32_t u32v10_3 = 0x00000014;
    std::cout << "std::countr_zero(0x" << std::hex << u32v10_3 << ") == "
              << std::dec << std::countr_zero(u32v10_3) << std::endl;
#pragma endregion

#pragma region std::countr_one
    constexpr std::uint32_t u32v11 = 0x00000001;
    std::cout << "std::countr_one(0x" << std::hex << u32v11 << ") == "
              << std::dec << std::countr_one(u32v11) << std::endl;

    constexpr std::uint32_t u32v11_1 = 0x00000002;
    std::cout << "std::countr_one(0x" << std::hex << u32v11_1 << ") == "
              << std::dec << std::countr_one(u32v11_1) << std::endl;

    constexpr std::uint32_t u32v11_2 = 0x00000003;
    std::cout << "std::countr_one(0x" << std::hex << u32v11_2 << ") == "
              << std::dec << std::countr_one(u32v11_2) << std::endl;

    constexpr std::uint32_t u32v11_3 = 0x00000014;
    std::cout << "std::countr_one(0x" << std::hex << u32v11_3 << ") == "
              << std::dec << std::countr_one(u32v11_3) << std::endl;
#pragma endregion

#pragma region std::popcount
    constexpr std::uint32_t u32v12 = 0x00000001;
    std::cout << "std::popcount(0x" << std::hex << u32v12 << ") == "
              << std::dec << std::popcount(u32v12) << std::endl;

    constexpr std::uint32_t u32v12_1 = 0x00000002;
    std::cout << "std::popcount(0x" << std::hex << u32v12_1 << ") == "
              << std::dec << std::popcount(u32v12_1) << std::endl;

    constexpr std::uint32_t u32v12_2 = 0x00000003;
    std::cout << "std::popcount(0x" << std::hex << u32v12_2 << ") == "
              << std::dec << std::popcount(u32v12_2) << std::endl;

    constexpr std::uint32_t u32v12_3 = 0x00000014;
    std::cout << "std::popcount(0x" << std::hex << u32v12_3 << ") == "
              << std::dec << std::popcount(u32v12_3) << std::endl;
#pragma endregion

    if (std::endian::native == std::endian::little) {
        std::cout << "System is little-endian." << std::endl;
    } else if (std::endian::native == std::endian::big) {
        std::cout << "System is big-endian." << std::endl;
    } else {
        std::cout << "System has mixed-endian." << std::endl;
    }

    /*
    Hamming distance between the two numbers using std::popcount
    Hamming distance is the number of differing bits between two binary representations.
    */
    constexpr std::uint32_t u32v13 = 0x00000011;
    constexpr std::uint32_t u32v13_1 = 0x00000002;
    std::cout << "Hamming distance between 0x" << std::hex << u32v13 << " and 0x" << std::hex << u32v13_1 << " is "
              << std::dec << std::popcount(u32v13 ^ u32v13_1) << std::endl;

    return 0;
}