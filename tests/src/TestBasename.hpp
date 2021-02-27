#pragma once
#ifndef TESTBASENAME_HPP
#define TESTBASENAME_HPP

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../src/os_path.hpp"

using namespace std;
using namespace CppUnit;

class CTestBasename : public CppUnit::TestFixture
{
	private:
		CPPUNIT_TEST_SUITE(CTestBasename);
		CPPUNIT_TEST(TestForAbspath);
		CPPUNIT_TEST(TestForRelpath);
		CPPUNIT_TEST(TestForBlank);
		CPPUNIT_TEST_SUITE_END();

		os_path* m_pObj;

	public:
		void setUp();
		void tearDown();
		void TestForAbspath();
		void TestForRelpath();
		void TestForBlank();
};


#endif

