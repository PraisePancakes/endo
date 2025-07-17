#pragma once

namespace ndo {

template <typename Left, typename Right>
class either {
    Left left_value;
    Right right_value;

    either() {};

    ~either() {};
};
}  // namespace ndo