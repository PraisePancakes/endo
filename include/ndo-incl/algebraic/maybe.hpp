#pragma once
#include <functional>
#include <variant>

#include "nothing.hpp"

/// \ingroup algebraic
/// \brief Namespace for algebraic types.
namespace ndo {

/**
 * \brief A container that may hold a value or nothing.
 *
 * The `maybe<T>` type is used to represent an optional value of type `T`.
 * It can either hold a valid value (`T`) or represent an empty state using `ndo_null_t`.
 * It provides utilities for value access, transformation, and monadic chaining.
 *
 * @tparam T The type of the value that may be held.
 */
template <typename T>
class maybe {
    std::variant<T, ndo_null_t> value;  ///< Internal storage for the value or nothing.

   public:
    /// Default constructor, initializes to empty state.
    constexpr maybe() : value(ndo_nothing) {}

    /// Constructs a `maybe` holding a value.
    constexpr maybe(const T& v) : value(v) {}

    /// Constructs a `maybe` by moving a value.
    constexpr maybe(T&& v) : value(std::move(v)) {}

    /// Copy constructor.
    constexpr maybe(const maybe<T>& o) : value(std::move(o.value)) {}

    /// Assignment from a value.
    constexpr maybe& operator=(const T& v) {
        value = v;
        return *this;
    }

    /// Assignment from empty state.
    constexpr maybe& operator=(const ndo_null_t& n) {
        value = n;
        return *this;
    }

    /// Checks whether the container holds a value.
    explicit constexpr operator bool() const noexcept {
        return std::holds_alternative<T>(value);
    }

    /// Checks whether the container holds a value.
    constexpr bool has_value() const noexcept {
        return this->operator bool();
    }

    /**
     * \brief Returns the contained value or throws if empty.
     * \throws std::runtime_error if no value is present.
     */
    constexpr T& just_or_throw() {
        if (has_value()) {
            return std::get<T>(value);
        }
        throw std::runtime_error("just_or_throw exception");
    }

    /**
     * \brief Returns the value if present, otherwise returns default-constructed T.
     */
    constexpr T just_or_default() const {
        if (has_value()) {
            return std::get<T>(value);
        }
        return {};
    }

    /**
     * \brief Returns the value if present, otherwise returns fallback `v`.
     * @param v Fallback value to return.
     */
    constexpr T just_or(const T& v) {
        if (has_value()) {
            return just_or_throw();
        }
        return v;
    }

    /**
     * \brief Applies function `f` to the contained value, or throws if empty.
     * @tparam F A callable taking a `T`.
     */
    template <typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_throw(F&& f) {
        return std::invoke(f, std::forward<T>(just_or_throw()));
    }

    /**
     * \brief Applies function `f` to the contained value and casts to `Target`.
     * @tparam Target The desired return type.
     * @tparam F A callable taking a `T`.
     */
    template <typename Target, typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_throw(F&& f) {
        return static_cast<Target>(std::invoke(f, std::forward<T>(just_or_throw())));
    }

    /**
     * \brief Applies function `f` to the value or default-constructed T if empty.
     * @tparam F A callable taking a `T`.
     */
    template <typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_default(F&& f) const noexcept {
        return std::invoke(f, std::forward<T>(just_or_default()));
    }

    /**
     * \brief Applies function `f` to the value and casts to `Target`, or uses default.
     * @tparam Target The desired return type.
     * @tparam F A callable taking a `T`.
     */
    template <typename Target, typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_default(F&& f) const noexcept {
        return static_cast<Target>(std::invoke(f, std::forward<T>(just_or_default())));
    }

    /**
     * \brief Applies a function returning another `maybe`, only if value is present.
     *
     * This is the monadic bind operation.
     *
     * @tparam F A callable taking a `T` and returning `maybe<U>`.
     */
    template <typename F>
    [[nodiscard]] constexpr auto and_then(F&& f) {
        using result_t = std::decay_t<std::invoke_result_t<F, T>>;
        if (has_value()) {
            return maybe<result_t>({std::invoke(std::forward<F>(f), std::forward<T>(just_or_throw()))});
        }
        return maybe<result_t>();
    }

    /**
     * \brief Safe version of `and_then`, uses default value if empty.
     *
     * This is a safer variant of monadic bind that avoids throwing.
     *
     * @tparam F A callable taking a `T` and returning `maybe<U>`.
     */
    template <typename F>
    [[nodiscard]] constexpr auto and_then_safe(F&& f) {
        using result_t = std::decay_t<std::invoke_result_t<F, T>>;
        if (has_value()) {
            return maybe<result_t>({std::invoke(std::forward<F>(f), std::forward<T>(just_or_default()))});
        }
        return maybe<result_t>();
    }

    /// Destructor.
    ~maybe() = default;
};

/**
 * \brief Specialization of `maybe` for `ndo_null_t`.
 *
 * This represents an always-empty maybe. Useful as a no-op container.
 */
template <>
class maybe<ndo_null_t> {
   public:
    /// Default constructor (empty).
    constexpr maybe() noexcept = default;

    /// Construct from `ndo_nothing`.
    constexpr maybe(ndo_null_t) noexcept {}

    /// Copy constructor.
    constexpr maybe(const maybe&) noexcept = default;

    /// Move constructor.
    constexpr maybe(maybe&&) noexcept = default;

    /// Destructor.
    ~maybe() = default;

    /// Always false: this type never holds a value.
    explicit constexpr operator bool() const noexcept {
        return false;
    }

    /// Always false: this type never holds a value.
    constexpr bool has_value() const noexcept {
        return false;
    }

    /// Always returns `ndo_nothing`.
    constexpr ndo_null_t just_or_throw() {
        return ndo_nothing;
    }

    /// Always returns `ndo_nothing`.
    constexpr ndo_null_t just_or_default() const {
        return ndo_nothing;
    }

    /// Always returns `ndo_nothing`.
    constexpr ndo_null_t just_or(void) {
        return ndo_nothing;
    }

    /// Always returns `ndo_nothing`.
    template <typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_throw(F&& f) {
        return ndo_nothing;
    }

    /// Always returns `ndo_nothing`.
    template <typename Target, typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_throw(F&& f) {
        return ndo_nothing;
    }

    /// Always returns `ndo_nothing`.
    template <typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_default(F&& f) const noexcept {
        return ndo_nothing;
    }

    /// Always returns `ndo_nothing`.
    template <typename Target, typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_default(F&& f) const noexcept {
        return ndo_nothing;
    }

    /// Always returns empty `maybe<ndo_null_t>`.
    template <typename F>
    [[nodiscard]] constexpr auto and_then(F&& f) {
        return maybe<ndo_null_t>();
    }
};

}  // namespace ndo
