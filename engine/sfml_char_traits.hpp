#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cwchar>
#include <iosfwd>
#include <limits>

namespace sfml_compat {
template <typename T>
struct basic_char_traits {
    using char_type = T;
    using int_type = uint_least32_t;
    using off_type = std::streamoff;
    using pos_type = std::streampos;
    using state_type = mbstate_t;

    static void assign(char_type& r, const char_type& a) noexcept { r = a; }
    static constexpr bool eq(char_type a, char_type b) noexcept { return a == b; }
    static constexpr bool lt(char_type a, char_type b) noexcept { return a < b; }

    static int compare(const char_type* s1, const char_type* s2, size_t n) noexcept {
        for (size_t i = 0; i < n; ++i) {
            if (lt(s1[i], s2[i])) {
                return -1;
            }
            if (lt(s2[i], s1[i])) {
                return 1;
            }
        }
        return 0;
    }

    static size_t length(const char_type* s) noexcept {
        size_t i = 0;
        while (s[i] != 0) {
            ++i;
        }
        return i;
    }

    static const char_type* find(const char_type* s, size_t n, const char_type& a) noexcept {
        for (size_t i = 0; i < n; ++i) {
            if (eq(s[i], a)) {
                return s + i;
            }
        }
        return nullptr;
    }

    static char_type* move(char_type* s1, const char_type* s2, size_t n) noexcept {
        return static_cast<char_type*>(memmove(s1, s2, n * sizeof(char_type)));
    }

    static char_type* copy(char_type* s1, const char_type* s2, size_t n) noexcept {
        return static_cast<char_type*>(memcpy(s1, s2, n * sizeof(char_type)));
    }

    static char_type* assign(char_type* s, size_t n, char_type a) noexcept {
        for (size_t i = 0; i < n; ++i) {
            s[i] = a;
        }
        return s;
    }

    static constexpr int_type not_eof(int_type c) noexcept { return eq_int_type(c, eof()) ? 0 : c; }
    static constexpr char_type to_char_type(int_type c) noexcept { return static_cast<char_type>(c); }
    static constexpr int_type to_int_type(char_type c) noexcept { return static_cast<int_type>(c); }
    static constexpr bool eq_int_type(int_type c1, int_type c2) noexcept { return c1 == c2; }
    static constexpr int_type eof() noexcept { return std::numeric_limits<int_type>::max(); }
};
} // namespace sfml_compat

namespace std {
template <>
struct char_traits<unsigned int> : sfml_compat::basic_char_traits<unsigned int> {};

template <>
struct char_traits<unsigned char> : sfml_compat::basic_char_traits<unsigned char> {};
} // namespace std
