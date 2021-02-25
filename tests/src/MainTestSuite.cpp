
#include <iostream>
#include <string>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>

#include "../../src/os_path.hpp"
#include "TestAbspath.hpp"

using namespace std;
using namespace CppUnit;

class CMainTestSuite : public CppUnit::TestFixture
{
	private:
		CPPUNIT_TEST_SUITE(CMainTestSuite);
		CPPUNIT_TEST(TestAbspath);
		CPPUNIT_TEST_SUITE_END();

		os_path* m_pTestObj;

	public:
		void setUp();
		void tearDown();
	
	protected:
		void TestAbspath();
};

void CMainTestSuite::setUp()
{
	m_pTestObj = new os_path();
}

void CMainTestSuite::tearDown()
{
	delete m_pTestObj;
}

void CMainTestSuite::TestAbspath()
{
	CTestAbspath obj;
	obj.Test1();
	obj.Test2();
}

CPPUNIT_TEST_SUITE_REGISTRATION(CMainTestSuite);

int main(int argc, char* argv[])
{
	CPPUNIT_NS::TestResult cTestResult;

	CPPUNIT_NS::TestResultCollector cCollectedRes;
	cTestResult.addListener(&cCollectedRes);

	CPPUNIT_NS::BriefTestProgressListener cProgress;
	cTestResult.addListener(&cProgress);

	CPPUNIT_NS::TestRunner cTestRunner;
	cTestRunner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
	cTestRunner.run(cTestResult);
	
	return cCollectedRes.wasSuccessful() ? 0 : 1;
}



