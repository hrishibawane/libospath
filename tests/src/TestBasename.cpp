
#include "TestBasename.hpp"

void CTestBasename::setUp() 
{
	m_pObj = new os_path();	
}

void CTestBasename::tearDown()
{
	delete m_pObj;
}

void CTestBasename::TestForAbspath()
{
	CPPUNIT_ASSERT_EQUAL(string("xyz"), m_pObj->basename("/abc/pqr/xyz"));
	CPPUNIT_ASSERT_EQUAL(string("text.txt"), m_pObj->basename("/abc/pqr/xyz/text.txt"));
	CPPUNIT_ASSERT_EQUAL(string(""), m_pObj->basename("/"));
}

void CTestBasename::TestForRelpath()
{
	CPPUNIT_ASSERT_EQUAL(string("xyz"), m_pObj->basename("../../xyz"));
	CPPUNIT_ASSERT_EQUAL(string("text.txt"), m_pObj->basename("../../xyz/text.txt"));
	CPPUNIT_ASSERT_EQUAL(string(".."), m_pObj->basename("../.."));
	CPPUNIT_ASSERT_EQUAL(string(""), m_pObj->basename("./"));
}

void CTestBasename::TestForBlank()
{
	CPPUNIT_ASSERT_EQUAL(string(""), m_pObj->basename(""));
}

