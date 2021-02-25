
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../src/os_path.hpp"

using namespace std;
using namespace CppUnit;

class CTestAbspath
{
	private:
		os_path* m_pObj;

	public:
		CTestAbspath();
		~CTestAbspath();
		void Test1();
		void Test2();
};

CTestAbspath::CTestAbspath()
{
	m_pObj = new os_path();
}

CTestAbspath::~CTestAbspath()
{
	delete m_pObj;
}

void CTestAbspath::Test1()
{
	CPPUNIT_ASSERT_MESSAGE("Prob in Test1()", "/home/hrishib/Hrishi/cos/tests/src" == m_pObj->abspath("."));
}

void CTestAbspath::Test2()
{
	CPPUNIT_ASSERT_MESSAGE("Prob in Test2()", "/home/hrishib/Hrishi/" == m_pObj->abspath("."));
}

