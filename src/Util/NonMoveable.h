#ifndef NONMOVABLE_H
#define NONMOVABLE_H

struct NonMovable {
    NonMovable() = default;
    NonMovable& operator=(NonMovable&&) = delete;
    NonMovable(NonMovable&&) = delete;
};

#endif