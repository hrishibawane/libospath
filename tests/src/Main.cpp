
#include <iostream>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>

#include "../../src/os_path.hpp"
#include "TestAbspath.hpp"
#include "TestBasename.hpp"

using namespace std;
using namespace CppUnit;

CPPUNIT_TEST_SUITE_REGISTRATION(CTestAbspath);
CPPUNIT_TEST_SUITE_REGISTRATION(CTestBasename);

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



