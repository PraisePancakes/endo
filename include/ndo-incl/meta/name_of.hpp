#pragma once
#include <cstdint>
#include <iostream>

namespace ndo {

/**
 * \brief Compile-time type name mapping.
 *
 * Provides a constexpr string literal representing the name of a type `T`.
 * By default, the value is an empty string.
 *
 * Specializations are provided for common fundamental types.
 *
 * Usage example:
 * \code
 * constexpr auto int_name = ndo::name_of<int>::value; // "int"
 * \endcode
 *
 * @tparam T The type to get the name of.
 */
template <typename T>
struct name_of {
    /// String literal representing the name of the type T.
    static constexpr auto value = "";
};

/// Specializations for fundamental and standard types:
template <>
struct name_of<int> {
    static constexpr auto value = "int";
};

template <>
struct name_of<char> {
    static constexpr auto value = "char";
};

template <>
struct name_of<float> {
    static constexpr auto value = "float";
};

template <>
struct name_of<long> {
    static constexpr auto value = "long";
};

template <>
struct name_of<void> {
    static constexpr auto value = "void";
};

template <>
struct name_of<std::uint8_t> {
    static constexpr auto value = "uint8_t";
};

template <>
struct name_of<std::uint16_t> {
    static constexpr auto value = "uint16_t";
};

template <>
struct name_of<std::uint32_t> {
    static constexpr auto value = "uint32_t";
};

template <>
struct name_of<std::uint64_t> {
    static constexpr auto value = "uint64_t";
};

}  // namespace ndo
