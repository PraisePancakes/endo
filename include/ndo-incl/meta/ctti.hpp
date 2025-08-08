#pragma once

/// \ingroup meta
/// \brief Namespace for metaprogramming utilities.
namespace ndo {

/**
 * \struct hash_t
 * \brief Provides a unique type-based identifier.
 *
 * This utility generates a unique address (pointer) per type `C` at compile-time,
 * which can be used as a unique type identifier.
 *
 * Example usage:
 * \code
 * constexpr auto id_int = ndo::hash_t<int>::id;
 * constexpr auto id_float = ndo::hash_t<float>::id;
 * // id_int != id_float
 * \endcode
 *
 * @tparam C The type to generate a unique id for.
 */
template <typename C>
struct hash_t {
   private:
    constexpr static int _var{0};

   public:
    constexpr static auto id{&_var};
};

}  // namespace ndo
