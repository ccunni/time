// --------------------------
// projects/date/TestDate.c++
// Copyright (C) 2010
// Glenn P. Downing
// --------------------------

/*
To test the program:
    % g++ -ansi -pedantic -lcppunit -ldl -Wall TestDate.c++ -o TestDate.app
    % valgrind TestDate.app >& TestDate.out
*/

// --------
// includes
// --------

#include <cstring>   // strcmp
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TestSuite.h"               // TestSuite
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Date.h"

// --------
// TestDate
// --------

struct TestDate : CppUnit::TestFixture {
    // ----------------
    // test_constructor
    // ----------------

    void test_constructor () {
        try {
            const Date<int> x(0, 1, 1600);
            CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(std::strcmp(e.what(), "Date()") == 0);}}

    // -------------
    // test_equal_to
    // -------------

    void test_equal_to () {
        try {
            const Date<int> x(28, 2, 2000);
            const Date<int> y(28, 2, 2000);
            CPPUNIT_ASSERT(x == y);
            CPPUNIT_ASSERT(!(x != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---------
    // test_less
    // ---------

    void test_less () {
        try {
            const Date<int> x(27, 2, 2000);
            const Date<int> y(28, 2, 2000);
            CPPUNIT_ASSERT(x <  y);
            CPPUNIT_ASSERT(x <= y);
            CPPUNIT_ASSERT(!(x >  y));
            CPPUNIT_ASSERT(!(x >= y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---------
    // test_plus
    // ---------

    void test_plus () {
        try {
            const Date<int> x(1, 1, 2000);
            const Date<int> y(1, 1, 2001);
            CPPUNIT_ASSERT(x + 365 == y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ----------
    // test_minus
    // ----------

    void test_minus () {
        try {
            const Date<int> x(1, 1, 2000);
            const Date<int> y(1, 1, 2001);
            CPPUNIT_ASSERT(y - 366 == x);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // -----------
    // test_output
    // -----------

    void test_output () {
        try {
            const Date<int> x(16, 6, 2008);
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "16 Jun 2008");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --------------
    // test_leap_year
    // --------------

    void test_leap_year () {
        try {
            CPPUNIT_ASSERT(Date<int>(1, 1, 2000).leap_year());}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDate);
    CPPUNIT_TEST(test_constructor);
    CPPUNIT_TEST(test_equal_to);
    CPPUNIT_TEST(test_less);
    CPPUNIT_TEST(test_plus);
    CPPUNIT_TEST(test_minus);
    CPPUNIT_TEST(test_output);
    CPPUNIT_TEST(test_leap_year);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestDate.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDate::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
