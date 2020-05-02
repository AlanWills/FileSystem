#include "TestUtils/TestUtils.h"

#include "Assert/Assert.h"
#include "Assert/NullAsserter.h"


namespace TestFileSystem
{
  //------------------------------------------------------------------------------------------------
  TEST_MODULE_INITIALIZE(TestFileSystem_Initialize)
  {
    Celeste::Assertion::setAsserter(std::make_unique<Celeste::NullAsserter>());
  }
}