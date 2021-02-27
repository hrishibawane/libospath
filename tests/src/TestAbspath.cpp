
#include "TestAbspath.hpp"

void CTestAbspath::setUp() 
{
	m_pObj = new os_path();	
}

void CTestAbspath::tearDown()
{
	delete m_pObj;
}

void CTestAbspath::TestCurrDir()
{
	CPPUNIT_ASSERT_EQUAL(string("/home/hrishib/Hrishi/cos/tests/src"), m_pObj->abspath("."));
	CPPUNIT_ASSERT_EQUAL(string("/home/hrishib/Hrishi/cos/tests/src/x.cpp"), m_pObj->abspath("x.cpp"));
	CPPUNIT_ASSERT_EQUAL(string("/home/hrishib/Hrishi/cos/tests/src/x.cpp"), m_pObj->abspath("./x.cpp"));
}

void CTestAbspath::TestPrevDir()
{
	CPPUNIT_ASSERT_EQUAL(string("/home/hrishib/Hrishi/cos/tests"), m_pObj->abspath("../"));
	CPPUNIT_ASSERT_EQUAL(string("/home/hrishib/Hrishi/cos/tests/x.cpp"), m_pObj->abspath("../x.cpp"));
}

void CTestAbspath::TestNextDir()
{
	CPPUNIT_ASSERT_EQUAL(string("/home/hrishib/Hrishi/cos/tests/src/XYZ"), m_pObj->abspath("XYZ/"));
	CPPUNIT_ASSERT_EQUAL(string("/home/hrishib/Hrishi/cos/tests/src/XYZ/x.cpp"), m_pObj->abspath("XYZ/x.cpp"));
}

void CTestAbspath::TestRandomDir()
{
	CPPUNIT_ASSERT_EQUAL(string("/abc/def/ghi/jkl"), m_pObj->abspath("../../../../../../abc/def/ghi/jkl"));
	CPPUNIT_ASSERT_EQUAL(string("/abc/def/ghi/jkl/x.cpp"), m_pObj->abspath("../../../../../../abc/def/ghi/jkl/x.cpp"));
}



