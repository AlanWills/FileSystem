#include "TestUtils/TestUtils.h"
#include "Assert/Assert.h"
#include "Assert/NullAsserter.h"


namespace TestFileSystemLua
{
  //------------------------------------------------------------------------------------------------
  TEST_MODULE_INITIALIZE(TestFileSystemLua_Initialize)
  {
    Celeste::Assertion::setAsserter(std::make_unique<Celeste::NullAsserter>());
  }
}