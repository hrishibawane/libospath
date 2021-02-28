#pragma once
#ifndef TESTABSPATH_HPP
#define TESTABSPATH_HPP

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../src/os_path.hpp"

using namespace std;
using namespace CppUnit;

class CTestAbspath : public CppUnit::TestFixture
{
	private:
		CPPUNIT_TEST_SUITE(CTestAbspath);
		CPPUNIT_TEST(TestCurrDir);
		CPPUNIT_TEST(TestPrevDir);
		CPPUNIT_TEST(TestNextDir);
		CPPUNIT_TEST(TestRandomDir);
		CPPUNIT_TEST(TestAbvRootDir);
		CPPUNIT_TEST(TestBlank);
		CPPUNIT_TEST(TestAbsPath);
		CPPUNIT_TEST_SUITE_END();

		os_path* m_pObj;

	public:
		void setUp();
		void tearDown();
		void TestCurrDir();
		void TestPrevDir();
		void TestNextDir();
		void TestRandomDir();
		void TestAbvRootDir();
		void TestBlank();
		void TestAbsPath();
};


#endif

