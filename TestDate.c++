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
            CPPUNIT_ASSERT(std::strcmp(e.what(), "Date::Date()") == 0);}
        
        try {
            const Date<int> x(29, 2, 2017);
            CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
           CPPUNIT_ASSERT(std::strcmp(e.what(), "Date::Date()") == 0);}

        try {
            const Date<int> x(29, 2, 2000);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
	}
	
	// -------------
	// test_to_days
	// -------------
	void test_to_days () {
	    try
	    {
	        const Date<int> b(1, 1, 1600); //0
	        CPPUNIT_ASSERT(b.get_days() == 0);
	                
            const Date<int> y(2, 1, 1601); //367
   	        CPPUNIT_ASSERT(y.get_days() == 367);
	                
            const Date<int> z(2, 1, 3601); //730852
	        CPPUNIT_ASSERT(z.get_days() == 730852);
	                            
            const Date<int> a(1, 3, 2000); //146157
	        CPPUNIT_ASSERT(a.get_days() == 146157);
	                
            const Date<int> c(1, 1, 2400); //292194
	        CPPUNIT_ASSERT(c.get_days() == 292194);
	                
            const Date<int> d(1, 1, 2404); //293655
	        CPPUNIT_ASSERT(d.get_days() == 293655);
	                
            const Date<int> e(1, 3, 2600); //365302
	        CPPUNIT_ASSERT(e.get_days() == 365302);
	                
            const Date<int> f(1, 3, 2601); //365667
	        CPPUNIT_ASSERT(f.get_days() == 365667);
	                
            const Date<int> h(1, 3, 3612); //734928
	        CPPUNIT_ASSERT(h.get_days() == 734928);
	                
            const Date<int> g(1, 3, 3613); //735293
	        CPPUNIT_ASSERT(g.get_days() == 735293);
	                
            const Date<int> ee(1,1,3650);  //748748
	        CPPUNIT_ASSERT(ee.get_days() == 748748);
	                
            const Date<int> aa(1,1,3601);  //730851
	        CPPUNIT_ASSERT(aa.get_days() == 730851);
	                
            const Date<int> bb(1,1,3604);  //731946
	        CPPUNIT_ASSERT(bb.get_days() == 731946);
	                
            const Date<int> cc(1,1,3700);  //767010
	        CPPUNIT_ASSERT(cc.get_days() == 767010);
	                
            const Date<int> dd(1,1,3600);  //730485
	        CPPUNIT_ASSERT(dd.get_days() == 730485);
	                
            const Date<int> ff(1,1,3705);  //768836
	        CPPUNIT_ASSERT(ff.get_days() == 768836);

            const Date<int> xx(7,12,1848);  //90921
	        CPPUNIT_ASSERT(xx.get_days() == 90921);
        }        
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
        
    }
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
            CPPUNIT_ASSERT(x + 366 == y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
        try {
            const Date<int> x(1, 1, 2000);
            const Date<int> y(1, 1, 2001);
            CPPUNIT_ASSERT(366 + x == y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}            
            }

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
            std::ostringstream out1;
            out1 << x;
            CPPUNIT_ASSERT(out1.str() == "16 Jun 2008");
            
            const Date<int> b(1, 1, 1600); //0
            std::ostringstream out2;
            out2 << b;
            CPPUNIT_ASSERT(out2.str() == "1 Jan 1600");	                

            const Date<int> y(2, 1, 1601); //367
            std::ostringstream out3;
            out3 << y;
            CPPUNIT_ASSERT(out3.str() == "2 Jan 1601");
            	                
            const Date<int> z(2, 1, 3601); //730852
            std::ostringstream out4;
            out4 << z;
            CPPUNIT_ASSERT(out4.str() == "2 Jan 3601");	                            

            const Date<int> a(1, 3, 2000); //146157
            std::ostringstream out5;
            out5 << a;
            CPPUNIT_ASSERT(out5.str() == "1 Mar 2000");
            	                
            const Date<int> c(1, 1, 2400); //292194
            std::ostringstream out6;
            out6 << c;
            CPPUNIT_ASSERT(out6.str() == "1 Jan 2400");
            	                
            const Date<int> d(1, 1, 2404); //293655
            std::ostringstream out7;
            out7 << d;
            CPPUNIT_ASSERT(out7.str() == "1 Jan 2404");	                
            
            const Date<int> e(1, 3, 2600); //365302
	        std::ostringstream out8;
            out8 << e;
            CPPUNIT_ASSERT(out8.str() == "1 Mar 2600");        
            
            const Date<int> f(1, 3, 2601); //365667
            std::ostringstream out9;
            out9 << f;
            CPPUNIT_ASSERT(out9.str() == "1 Mar 2601");	                

            const Date<int> ff(1,1,3705);  //768836
            std::ostringstream out11;
            out11 << ff;
            CPPUNIT_ASSERT(out11.str() == "1 Jan 3705");

            const Date<int> xx(7,12,1848);  //90921
            std::ostringstream out12;
            out12 << xx;
            CPPUNIT_ASSERT(out12.str() == "7 Dec 1848");
            }
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
    CPPUNIT_TEST(test_to_days);
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

