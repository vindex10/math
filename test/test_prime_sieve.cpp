// Copyright 2020 Matt Borland
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/math/special_functions/prime_sieve.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <boost/math/special_functions/interval_sieve.hpp>
#include <boost/math/special_functions/detail/linear_prime_sieve.hpp>
#include <list>
#include <deque>
#include <array>
#include <vector>
#include <iostream>
#include <chrono>
#include <algorithm>

template<typename Integer>
void test_prime_sieve()
{
    std::vector<Integer> primes;
    Integer ref {168}; // Calculated with wolfram-alpha

    // Does the function work with a vector
    boost::math::prime_sieve(std::execution::par, static_cast<Integer>(1'000), primes);
    BOOST_TEST_EQ(primes.size(), ref);

    // Tests for correctness
    // 2
    primes.clear();
    boost::math::prime_sieve(std::execution::par, static_cast<Integer>(2), primes);
    BOOST_TEST_EQ(primes.size(), 0);

    // 100
    primes.clear();
    boost::math::prime_sieve(std::execution::par, static_cast<Integer>(100), primes);
    BOOST_TEST_EQ(primes.size(), 25);

    // 10'000
    primes.clear();
    boost::math::prime_sieve(std::execution::par, static_cast<Integer>(10'000), primes);
    BOOST_TEST_EQ(primes.size(), 1229);

    // 100'000
    primes.clear();
    boost::math::prime_sieve(std::execution::par, static_cast<Integer>(100'000), primes);
    BOOST_TEST_EQ(primes.size(), 9592);

    // 1'000'000
    primes.clear();
    boost::math::prime_sieve(std::execution::par, static_cast<Integer>(1'000'000), primes);
    BOOST_TEST_EQ(primes.size(), 78498);

    // Does the function work with a deque?
    std::deque<Integer> d_primes;
    boost::math::prime_sieve(std::execution::par, static_cast<Integer>(1'000), d_primes);
    BOOST_TEST_EQ(d_primes.size(), ref);
}

template<typename Integer>
void test_sequential_prime_sieve()
{
    std::vector<Integer> primes;

    // 10'000
    primes.clear();
    boost::math::prime_sieve(static_cast<Integer>(10'000), primes);
    BOOST_TEST_EQ(primes.size(), 1229);

    // 100'000
    primes.clear();
    boost::math::prime_sieve(static_cast<Integer>(100'000), primes);
    BOOST_TEST_EQ(primes.size(), 9592);

    // 1'000'000
    primes.clear();
    boost::math::prime_sieve(static_cast<Integer>(1'000'000), primes);
    BOOST_TEST_EQ(primes.size(), 78498);
}

template<typename Integer>
void test_prime_range()
{
    std::vector<Integer> primes;
    Integer ref {168}; // Calculated with wolfram-alpha

    // Does the upper and lower bound call work
    boost::math::prime_range(std::execution::par, static_cast<Integer>(2), static_cast<Integer>(1'000), primes);
    BOOST_TEST_EQ(primes.size(), ref);

    // Does parallel version work
    primes.clear();
    boost::math::prime_range(std::execution::par, static_cast<Integer>(2), static_cast<Integer>(1'000), primes);
    BOOST_TEST_EQ(primes.size(), ref);

    // Does it work with a deque?
    std::deque<Integer> d_primes;
    boost::math::prime_range(std::execution::par, static_cast<Integer>(2), static_cast<Integer>(1'000), d_primes);
    BOOST_TEST_EQ(d_primes.size(), ref);

    // Does the lower bound change the results?
    ref = 143; // Calculated with wolfram-alpha
    primes.clear();
    boost::math::prime_range(std::execution::par, static_cast<Integer>(100), static_cast<Integer>(1'000), primes);
    BOOST_TEST_EQ(primes.size(), ref);

    // Will it call the sieve for large input
    ref = 78498; // Calculated with wolfram-alpha
    primes.clear();
    boost::math::prime_range(std::execution::par, static_cast<Integer>(2), static_cast<Integer>(1'000'000), primes);
    BOOST_TEST_EQ(primes.size(), ref);
}

template<typename Integer>
void test_prime_range_large()
{
    std::vector<Integer> primes;
    Integer ref;

    // Larger numbers
    ref = 586'081; // Calculated with wolfram-alpha
    primes.clear();
    boost::math::prime_range(std::execution::par, static_cast<Integer>(1'000'000), static_cast<Integer>(10'000'000), primes);
    BOOST_TEST_EQ(primes.size(), ref);

    ref = 5'096'876; // Calculated with wolfram-alpha
    primes.clear();
    boost::math::prime_range(std::execution::par, static_cast<Integer>(10'000'000), static_cast<Integer>(100'000'000), primes);
    BOOST_TEST_EQ(primes.size(), ref);

    ref = 48'638'573;
    primes.clear();
    boost::math::prime_range(std::execution::par, static_cast<Integer>(100'000'000), static_cast<Integer>(1'073'741'824), primes);
    BOOST_TEST_EQ(primes.size(), ref);
}

template<typename Integer>
void test_prime_range_seq()
{
    std::vector<Integer> primes;
    Integer ref {168}; // Calculated with wolfram-alpha

    // Does the upper and lower bound call work
    boost::math::prime_range(static_cast<Integer>(2), static_cast<Integer>(1'000), primes);
    BOOST_TEST_EQ(primes.size(), ref);

    // Does parallel version work
    primes.clear();
    boost::math::prime_range(static_cast<Integer>(2), static_cast<Integer>(1'000), primes);
    BOOST_TEST_EQ(primes.size(), ref);

    // Does it work with a deque?
    std::deque<Integer> d_primes;
    boost::math::prime_range(static_cast<Integer>(2), static_cast<Integer>(1'000), d_primes);
    BOOST_TEST_EQ(d_primes.size(), ref);

    // Does the lower bound change the results?
    ref = 143; // Calculated with wolfram-alpha
    primes.clear();
    boost::math::prime_range(static_cast<Integer>(100), static_cast<Integer>(1'000), primes);
    BOOST_TEST_EQ(primes.size(), ref);

    // Will it call the sieve for large input
    ref = 78498; // Calculated with wolfram-alpha
    primes.clear();
    boost::math::prime_range(static_cast<Integer>(2), static_cast<Integer>(1'000'000), primes);
    BOOST_TEST_EQ(primes.size(), ref);
}

template<typename Integer>
void test_prime_range_seq_large()
{
    std::vector<Integer> primes;
    Integer ref;
    
    // Larger numbers
    ref = 586'081; // Calculated with wolfram-alpha
    primes.clear();
    boost::math::prime_range(static_cast<Integer>(1'000'000), static_cast<Integer>(10'000'000), primes);
    BOOST_TEST_EQ(primes.size(), ref);

    ref = 5'096'876; // Calculated with wolfram-alpha
    primes.clear();
    boost::math::prime_range(static_cast<Integer>(10'000'000), static_cast<Integer>(100'000'000), primes);
    BOOST_TEST_EQ(primes.size(), ref);

    ref = 48'638'573;
    primes.clear();
    boost::math::prime_range(static_cast<Integer>(100'000'000), static_cast<Integer>(1'073'741'824), primes);
    BOOST_TEST_EQ(primes.size(), ref);
}

template<typename Integer>
void test_par_prime_sieve_large()
{
    std::vector<Integer> primes;
    Integer ref {54400028}; // Calculated with wolfram-alpha

    // Force the sieve into the multi-threading section and test reserve functionality
    boost::math::prime_reserve(static_cast<Integer>(1073741824), primes);
    boost::math::prime_sieve(std::execution::par, static_cast<Integer>(1073741824), primes);
    BOOST_TEST_EQ(primes.size(), ref);
}

template<typename Integer>
void test_interval_sieve()
{
    std::vector<Integer> pre_sieved_primes {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};
    std::vector<Integer> primes;

    boost::math::detail::IntervalSieve sieve(static_cast<Integer>(1'000), static_cast<Integer>(10'000), pre_sieved_primes, primes);
    BOOST_TEST_EQ(primes.size(), 1'061);

    primes.clear();
    sieve.NewRange(static_cast<Integer>(10'000), static_cast<Integer>(100'000), primes);
    BOOST_TEST_EQ(primes.size(), 8'363);

    primes.clear();
    sieve.NewRange(static_cast<Integer>(100'000), static_cast<Integer>(1'000'000), primes);
    BOOST_TEST_EQ(primes.size(), 68'906);
}

template<typename Integer>
void test_linear_sieve()
{
    std::vector<Integer> primes;

    boost::math::detail::linear_sieve(static_cast<Integer>(1'000), primes);
    BOOST_TEST_EQ(primes.size(), 168);

    primes.clear();
    boost::math::detail::linear_sieve(static_cast<Integer>(10'000), primes);
    BOOST_TEST_EQ(primes.size(), 1229);

    primes.clear();
    boost::math::detail::linear_sieve(static_cast<Integer>(100'000), primes);
    BOOST_TEST_EQ(primes.size(), 9592);
}

template<typename Integer>
void test_linear_sieve_iterator()
{
    constexpr std::size_t array_size {10'000};
    std::array<Integer, array_size> primes;
    std::fill(primes.begin(), primes.end(), 0);

    boost::math::detail::prime_sieve::linear_sieve(static_cast<Integer>(1'000), primes.begin());
    BOOST_TEST_EQ(array_size - std::count(primes.cbegin(), primes.cend(), 0), 168);

    std::fill(primes.begin(), primes.end(), 0);
    boost::math::detail::prime_sieve::linear_sieve(static_cast<Integer>(10'000), primes.begin());
    BOOST_TEST_EQ(array_size - std::count(primes.cbegin(), primes.cend(), 0), 1'229);

    std::fill(primes.begin(), primes.end(), 0);
    boost::math::detail::prime_sieve::linear_sieve(static_cast<Integer>(100'000), primes.begin());
    BOOST_TEST_EQ(array_size - std::count(primes.cbegin(), primes.cend(), 0), 9'592);
}

int main()
{
    // Individual Algorithms
    test_linear_sieve<int>();
    test_linear_sieve<int32_t>();
    test_linear_sieve<int64_t>();
    test_linear_sieve<uint32_t>();
    test_linear_sieve<boost::multiprecision::cpp_int>();
    test_linear_sieve<boost::multiprecision::mpz_int>();
    
    test_interval_sieve<int>();
    test_interval_sieve<int32_t>();
    test_interval_sieve<int64_t>();
    test_interval_sieve<uint32_t>();
    test_interval_sieve<boost::multiprecision::cpp_int>();
    test_interval_sieve<boost::multiprecision::mpz_int>();

    // Individual Algorithms with Iterators
    test_linear_sieve_iterator<int>();
    test_linear_sieve_iterator<int32_t>();
    test_linear_sieve_iterator<int64_t>();
    test_linear_sieve_iterator<uint32_t>();
    test_linear_sieve_iterator<boost::multiprecision::cpp_int>();
    test_linear_sieve_iterator<boost::multiprecision::mpz_int>();

    // Composite
    test_prime_sieve<int>();
    test_prime_sieve<int32_t>();
    test_prime_sieve<int64_t>();
    test_prime_sieve<uint32_t>();
    test_prime_sieve<boost::multiprecision::cpp_int>();
    test_prime_sieve<boost::multiprecision::mpz_int>();

    test_sequential_prime_sieve<int>();
    test_sequential_prime_sieve<int32_t>();
    test_sequential_prime_sieve<int64_t>();
    test_sequential_prime_sieve<uint32_t>();
    test_sequential_prime_sieve<boost::multiprecision::cpp_int>();
    test_sequential_prime_sieve<boost::multiprecision::mpz_int>();

    test_prime_range<int>();
    test_prime_range<int32_t>();
    test_prime_range<int64_t>();
    test_prime_range<uint32_t>();
    test_prime_range<boost::multiprecision::cpp_int>();
    test_prime_range<boost::multiprecision::mpz_int>();

    test_prime_range_seq<int>();
    test_prime_range_seq<int32_t>();
    test_prime_range_seq<int64_t>();
    test_prime_range_seq<uint32_t>();
    test_prime_range_seq<boost::multiprecision::cpp_int>();
    test_prime_range_seq<boost::multiprecision::mpz_int>();

    // Large composite tests (Commented out for CI)
    //test_par_prime_sieve_large<int>();
    //test_par_prime_sieve_large<int32_t>();
    //test_par_prime_sieve_large<int64_t>();
    //test_par_prime_sieve_large<uint32_t>();
    //test_par_prime_sieve_large<boost::multiprecision::cpp_int>();
    //test_par_prime_sieve_large<boost::multiprecision::mpz_int>();

    //test_prime_range_large<int>();
    //test_prime_range_large<int32_t>();
    //test_prime_range_large<int64_t>();
    //test_prime_range_large<uint32_t>();
    //test_prime_range_large<boost::multiprecision::cpp_int>();
    //test_prime_range_large<boost::multiprecision::mpz_int>();

    //test_prime_range_seq_large<int>();
    //test_prime_range_seq_large<int32_t>();
    //test_prime_range_seq_large<int64_t>();
    //test_prime_range_seq_large<uint32_t>();
    //test_prime_range_seq_large<boost::multiprecision::cpp_int>();
    //test_prime_range_seq_large<boost::multiprecision::mpz_int>();
    
    boost::report_errors();
}