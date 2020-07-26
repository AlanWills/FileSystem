#include "TestUtils/TestUtils.h"
#include "ScriptCommands/FileSystem/FileSystemScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestFileSystem::Lua::ScriptCommands
{
  BASE_TEST_CLASS(TestFileSystemScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileSystemScriptCommands_initialize_AddsDirectoryUserType_ToGlobalTable)
  {
    sol::state state;

    Assert::IsFalse(state["Directory"].valid());

    Celeste::Lua::FileSystem::ScriptCommands::initialize(state);

    Assert::IsTrue(state["Directory"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileSystemScriptCommands_initialize_AddsFileUserType_ToGlobalTable)
  {
    sol::state state;

    Assert::IsFalse(state["File"].valid());

    Celeste::Lua::FileSystem::ScriptCommands::initialize(state);

    Assert::IsTrue(state["File"].valid());
  }

#pragma endregion

  };
}