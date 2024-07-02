#ifndef NONMOVABLE_H
#define NONMOVABLE_H

/**
 * @brief Utility class. Inheriting from it deletes the move constructor and move assignment.
 * 
 */
struct NonMovable {
    NonMovable() = default;
    NonMovable& operator=(NonMovable&&) = delete;
    NonMovable(NonMovable&&) = delete;
};

#endif