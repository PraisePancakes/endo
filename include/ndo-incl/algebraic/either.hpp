#pragma once
#include "maybe.hpp"

/// \ingroup algebraic

namespace ndo {
/**
 * \brief Algebraic type that holds a value (Right) or an error (Left).
 *
 * The `either` type is a tagged union representing a value of one of two possible types:
 * - `Right`: representing success.
 * - `Left`: representing failure or error.
 *
 * This class wraps both types using the `maybe` type, and allows access to either depending
 * on which is active. It provides utility functions to extract the value or error with
 * optional fallbacks or error handling.
 *
 * @tparam Left  The type representing the error state.
 * @tparam Right The type representing the success state.
 *
 * @note Only one of the two (`left`, `right`) is expected to hold a value at a time.
 */
template <typename Left, typename Right>
class either {
    ndo::maybe<Left> left;    ///< Holds the error value if present.
    ndo::maybe<Right> right;  ///< Holds the success value if present.

   public:
    using left_type = Left;    ///< Alias for the error type.
    using right_type = Right;  ///< Alias for the success type.

    /// Default constructor. Initializes both states to empty.
    either() : left{}, right{} {};

    /// Construct with both Left and Right (non-standard use).
    either(const Left& l, const Right& r) : left{l}, right{r} {};

    /// Construct with both Left and Right (rvalue references).
    either(Left&& l, Right&& r) : left{std::move(l)}, right{std::move(r)} {};

    /// Construct with only an error value.
    explicit either(const Left& l) : left{l}, right{} {};

    /// Construct with only a success value.
    explicit either(const Right& r) : left{}, right{r} {};

    /// Construct with an rvalue error value.
    explicit either(Left&& l) : left{std::move(l)}, right{} {};

    /// Construct with an rvalue success value.
    explicit either(Right&& r) : left{}, right{std::move(r)} {};

    /// Assign from a pair of (Left, Right).
    either& operator=(const std::pair<Left, Right>& p) {
        left = p.first;
        right = p.second;
        return *this;
    };

    /// Assign from an error value.
    either& operator=(const Left& l) {
        left = l;
        return *this;
    };

    /// Copy assignment.
    either& operator=(const either& o) {
        left = o.left;
        right = o.right;
        return *this;
    };

    /// Assign from a success value (does nothing; placeholder).
    either& operator=(const Right& r) {
        return *this;
    };

    /**
     * @brief Returns the value if present, otherwise returns a default-constructed Right.
     */
    [[nodiscard]] constexpr Right just_or_default() const noexcept {
        return right.just_or_default();
    };

    /**
     * @brief Returns the value if present, otherwise throws.
     * @throws std::runtime_error if no value is held.
     */
    [[nodiscard]] constexpr Right& just_or_throw() {
        return right.just_or_throw();
    };

    /**
     * @brief Returns the error if present, otherwise throws.
     * @throws std::runtime_error if no error is held.
     */
    [[nodiscard]] constexpr Left& error_or_throw() const {
        return left.just_or_throw();
    }

    /**
     * @brief Returns the error if present, otherwise returns a default-constructed Left.
     */
    [[nodiscard]] constexpr Left error_or_default() const noexcept {
        return left.just_or_default();
    };

    /**
     * @brief Checks whether a success value is held.
     * @return true if a Right value is present; false otherwise.
     */
    constexpr explicit operator bool() const noexcept {
        return this->has_value();
    };

    /**
     * @brief Checks whether a success value is held.
     * @return true if a Right value is present; false otherwise.
     */
    [[nodiscard]] constexpr bool has_value() const noexcept {
        return right.has_value();
    };

    /**
     * @brief Returns the success value if present, otherwise returns the given fallback.
     * @param r The fallback value to return if no Right is present.
     */
    [[nodiscard]] constexpr Right just_or(const Right& r) const noexcept {
        return right.just_or(r);
    }

    /**
     * @brief Returns the error value if present, otherwise returns the given fallback.
     * @param l The fallback value to return if no Left is present.
     */
    [[nodiscard]] constexpr Left error_or(const Left& l) const noexcept {
        return left.just_or(l);
    }

    /**
     * @brief If a Right is present, calls `f` with the value.
     * @tparam F A callable accepting a Right and returning an `either`.
     * @param f The function to invoke.
     * @return Result of applying `f` if value is present; otherwise, propagates error.
     */
    template <typename F>
    [[nodiscard]] constexpr decltype(auto) and_then(F&& f) {
        return right.and_then(std::forward<F>(f));
    }

    /**
     * @brief Safe version of `and_then` that returns a `maybe` instead of throwing.
     * @tparam F A callable accepting a Right and returning a `maybe`.
     * @param f The function to invoke.
     * @return Result of applying `f` if value is present; otherwise, empty `maybe`.
     */
    template <typename F>
    [[nodiscard]] constexpr decltype(auto) and_then_safe(F&& f) {
        return right.and_then_safe(std::forward<F>(f));
    }

    /// Destructor.
    ~either() = default;
};

}  // namespace ndo

/// @}
