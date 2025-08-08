#pragma once

/// \ingroup algebraic
/// \brief Namespace for algebraic types.
namespace ndo {

/**
 * \brief Tag type used to represent "no value".
 *
 * `ndo_null_t` is a sentinel type used in types like `maybe` and `either`
 * to explicitly indicate an empty or uninitialized state. It acts similarly
 * to `std::nullopt_t` in `std::optional`.
 *
 * Use `ndo_nothing` as the singleton instance of this type.
 */
struct ndo_null_t {};

/**
 * \brief Singleton instance of `ndo_null_t`.
 *
 * Used as the default "empty" value in `maybe` or `either`.
 */
inline constexpr ndo_null_t ndo_nothing{};

}  // namespace ndo