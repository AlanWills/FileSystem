#include "TestUtils.h"

#include "Assert/Assert.h"
#include "Assert/NullAsserter.h"


namespace TestFileSystem
{
  //------------------------------------------------------------------------------------------------
  TEST_MODULE_INITIALIZE(TestLog_Initialize)
  {
    Celeste::Assertion::setAsserter(std::make_unique<Celeste::NullAsserter>());
  }
}