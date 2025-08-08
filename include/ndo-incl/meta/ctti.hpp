#pragma once

namespace ndo {
template <typename C>
struct hash_t {
   private:
    constexpr static int _var{0};

   public:
    constexpr static auto id{&_var};
};

}  // namespace ndo