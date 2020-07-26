#include "TestUtils/TestUtils.h"
#include "ScriptCommands/FileSystem/DirectoryScriptCommands.h"
#include "Lua/LuaState.h"
#include "FileSystem/Directory.h"
#include "TestUtils/TestResources/TempDirectory.h"
#include "TestUtils/Assert/DirectoryAssert.h"
#include "TestUtils/Assert/LuaAssert.h"

using namespace Celeste;
using LuaState = Celeste::Lua::LuaState;


namespace TestFileSystem::Lua::ScriptCommands
{
  BASE_TEST_CLASS(TestDirectoryScriptCommands)

#pragma region Initialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DirectoryScriptCommands_initialize_AddsDirectoryUserType_ToGlobalTable)
  {
    sol::state state;

    Assert::IsFalse(state["Directory"].valid());

    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    Assert::IsTrue(state["Directory"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_initialize_Adds_new_ToDirectoryTable)
  {
    sol::state state;

    Assert::IsFalse(state["Directory"]["new"].valid());

    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    Assert::IsTrue(state["Directory"]["new"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_initialize_Adds_exists_ToDirectoryTable)
  {
    sol::state state;

    Assert::IsFalse(state["Directory"]["exists"].valid());

    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    Assert::IsTrue(state["Directory"]["exists"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_initialize_Adds_create_ToDirectoryTable)
  {
    sol::state state;

    Assert::IsFalse(state["Directory"]["create"].valid());

    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    Assert::IsTrue(state["Directory"]["create"].valid());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_new_InputtingString_ReturnsDirectoryWithCorrectPath)
  {
    sol::state state;
    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    auto result = state["Directory"]["new"].get<sol::protected_function>().call("Test");

    Assert::IsTrue(result.valid());
    Assert::AreEqual("Test", result.get<Directory>().getDirectoryPath().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_new_InputtingPath_ReturnsDirectoryWithCorrectPath)
  {
    sol::state state;
    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    auto result = state["Directory"]["new"].get<sol::protected_function>().call(Path("Test"));

    Assert::IsTrue(result.valid());
    Assert::AreEqual(Path("Test"), result.get<Directory>().getDirectoryPath());
  }

#pragma endregion

#pragma region Exists Tests

#pragma region String Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_exists_InputtingInvalidDirectoryString_ReturnsFalse)
  {
    sol::state state;
    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    auto result = state["Directory"]["exists"].get<sol::protected_function>().call("12312e1__~~");

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_exists_InputtingNonExistentDirectoryString_ReturnsFalse)
  {
    sol::state state;
    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    auto result = state["Directory"]["exists"].get<sol::protected_function>().call("Test");

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_exists_InputtingExistentDirectoryString_ReturnsTrue)
  {
    Directory directory(Path(TempDirectory::getFullPath(), "Test"));
    directory.create();

    DirectoryAssert::DirectoryExists(directory.getDirectoryPath().as_string());

    sol::state state;
    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    auto result = state["Directory"]["exists"].get<sol::protected_function>().call(directory.getDirectoryPath().as_string());

    Assert::IsTrue(result.valid());
    Assert::IsTrue(result.get<bool>());
  }

#pragma endregion

#pragma region Path Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_exists_InputtingInvalidDirectoryPath_ReturnsFalse)
  {
    sol::state state;
    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    auto result = state["Directory"]["exists"].get<sol::protected_function>().call(Path("12312e1__~~"));

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_exists_InputtingNonExistentDirectoryPath_ReturnsFalse)
  {
    sol::state state;
    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    auto result = state["Directory"]["exists"].get<sol::protected_function>().call(Path("Test"));

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_exists_InputtingExistentDirectoryPath_ReturnsTrue)
  {
    Directory directory(Path(TempDirectory::getFullPath(), "Test"));
    directory.create();

    DirectoryAssert::DirectoryExists(directory.getDirectoryPath().as_string());

    sol::state state;
    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    auto result = state["Directory"]["exists"].get<sol::protected_function>().call(directory.getDirectoryPath());

    Assert::IsTrue(result.valid());
    Assert::IsTrue(result.get<bool>());
  }

#pragma endregion

#pragma region Instance Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_exists_InputtingInvalidInstance_ReturnsFalse)
  {
    Directory directory(Path("12312e1__~~"));

    sol::state state;
    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    auto result = state["Directory"]["exists"].get<sol::protected_function>().call(directory);

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_exists_InputtingNonExistentInstance_ReturnsFalse)
  {
    Directory directory(Path("Test"));
    
    sol::state state;
    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    auto result = state["Directory"]["exists"].get<sol::protected_function>().call(directory);

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_exists_InputtingExistentInstance_ReturnsTrue)
  {
    Directory directory(Path(TempDirectory::getFullPath(), "Test"));
    directory.create();

    DirectoryAssert::DirectoryExists(directory.getDirectoryPath().as_string());

    sol::state state;
    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    auto result = state["Directory"]["exists"].get<sol::protected_function>().call(directory);

    Assert::IsTrue(result.valid());
    Assert::IsTrue(result.get<bool>());
  }

#pragma endregion

#pragma endregion

#pragma region Create Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_create_InputtingInvalidInstance_ReturnsFalseAndDoesNotCreateDirectory)
  {
    Directory directory(Path("12312e1__~~"));

    Assert::IsFalse(directory.exists());

    sol::state state;
    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    auto result = state["Directory"]["create"].get<sol::protected_function>().call(directory);

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
    Assert::IsFalse(directory.exists());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_create_InputtingNonExistentInstance_ReturnsTrueAndCreateDirectory)
  {
    Directory directory(Path(TempDirectory::getFullPath(), "Test"));

    Assert::IsFalse(directory.exists());

    sol::state state;
    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    auto result = state["Directory"]["create"].get<sol::protected_function>().call(directory);

    Assert::IsTrue(result.get<bool>());
    Assert::IsTrue(directory.exists());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DirectoryScriptCommands_create_InputtingExistentInstance_ReturnsTrue)
  {
    Directory directory(Path(TempDirectory::getFullPath(), "Test"));
    directory.create();
    directory.createFile("Test.xml");

    Assert::IsTrue(directory.exists());

    sol::state state;
    Celeste::Lua::FileSystem::DirectoryScriptCommands::initialize(state);

    auto result = state["Directory"]["create"].get<sol::protected_function>().call(directory);

    Assert::IsTrue(result.get<bool>());
    Assert::IsTrue(directory.exists());
    Assert::IsTrue(File::exists(Path(directory.getDirectoryPath(), "Test.xml")));
  }

#pragma endregion

  };
}