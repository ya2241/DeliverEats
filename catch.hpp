/*
 * Minimal Catch2 v2 compatibility stub.
 * REPLACE with the real catch.hpp on the lab VM:
 *   wget https://github.com/catchorg/Catch2/releases/download/v2.13.10/catch.hpp
 */

#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <cmath>
#include <stdexcept>

struct Approx
{
    explicit Approx(double v) : val(v), eps(1e-6) {}
    double val, eps;
    bool operator==(double other) const { return std::fabs(val - other) <= eps; }
};
inline bool operator==(double lhs, Approx rhs) { return rhs == lhs; }

inline std::vector<std::pair<std::string, std::function<void()>>>& test_registry()
{
    static std::vector<std::pair<std::string, std::function<void()>>> reg;
    return reg;
}

// Use a struct whose constructor registers the test - avoids naming issues
struct AutoReg
{
    AutoReg(const char* name, std::function<void()> fn)
    {
        test_registry().push_back({name, fn});
    }
};

// Paste helper - evaluates __LINE__ before pasting
#define CATCH_PASTE2(a, b) a##b
#define CATCH_PASTE(a, b)  CATCH_PASTE2(a, b)

/*
 * TEST_CASE macro strategy:
 *  1. Forward-declare a free function with a name derived from __LINE__.
 *  2. Create a file-scope AutoReg object (also named from __LINE__) that
 *     registers that function.
 *  3. Define the function body - the { } that follows the macro call becomes
 *     the body of this function.
 */
#define TEST_CASE(test_name, tags)                                    \
    static void CATCH_PASTE(catch_test_, __LINE__)();                 \
    static AutoReg CATCH_PASTE(catch_reg_, __LINE__)(                 \
        test_name, CATCH_PASTE(catch_test_, __LINE__));               \
    static void CATCH_PASTE(catch_test_, __LINE__)()

#define SECTION(desc) if (true)

#define REQUIRE(expr)                                                    \
    do {                                                                 \
        if (!(expr)) {                                                   \
            std::cerr << "  FAILED: " #expr                             \
                      << "  [" << __FILE__ << ":" << __LINE__ << "]\n"; \
            throw std::runtime_error("Assertion failed: " #expr);       \
        }                                                                \
    } while (false)

#define CHECK(expr) REQUIRE(expr)

#define CATCH_CONFIG_MAIN

int main(int, char**)
{
    int passed = 0;
    int failed = 0;

    for (auto& tc : test_registry())
    {
        try
        {
            tc.second();
            std::cout << "[PASS] " << tc.first << "\n";
            ++passed;
        }
        catch (const std::exception& e)
        {
            std::cout << "[FAIL] " << tc.first << "\n"
                      << "       " << e.what() << "\n";
            ++failed;
        }
    }

    std::cout << "\n" << passed << " passed, " << failed << " failed.\n";
    return (failed == 0) ? 0 : 1;
}
