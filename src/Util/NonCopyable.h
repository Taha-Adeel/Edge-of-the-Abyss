#pragma once

/**
 * @brief Utility class. Inheriting from it deletes the copy constructor and copy assignment.
 * 
 */
struct NonCopyable {
    NonCopyable() = default;
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable(const NonCopyable&) = delete;
};