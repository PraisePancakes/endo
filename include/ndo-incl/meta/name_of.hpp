#pragma once
#include <cstdint>
#include <iostream>

namespace ndo {
template <typename T>
struct name_of {
    /// String literal representing the name of the type T.
    static constexpr auto value = "";
};

/// Specialization for `int`.
template <>
struct name_of<int> {
    static constexpr auto value = "int";
};

/// Specialization for `char`.
template <>
struct name_of<char> {
    static constexpr auto value = "char";
};

/// Specialization for `float`.
template <>
struct name_of<float> {
    static constexpr auto value = "float";
};

/// Specialization for `long`.
template <>
struct name_of<long> {
    static constexpr auto value = "long";
};

/// Specialization for `void`.
template <>
struct name_of<void> {
    static constexpr auto value = "void";
};

/// Specialization for `std::uint8_t`.
template <>
struct name_of<std::uint8_t> {
    static constexpr auto value = "uint8_t";
};

/// Specialization for `std::uint16_t`.
template <>
struct name_of<std::uint16_t> {
    static constexpr auto value = "uint16_t";
};

/// Specialization for `std::uint64_t`.
template <>
struct name_of<std::uint64_t> {
    static constexpr auto value = "uint64_t";
};

/// Specialization for `std::uint32_t`.
template <>
struct name_of<std::uint32_t> {
    static constexpr auto value = "uint32_t";
};
}  // namespace ndo