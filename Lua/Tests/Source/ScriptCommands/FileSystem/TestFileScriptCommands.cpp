#include "TestUtils/TestUtils.h"
#include "ScriptCommands/FileSystem/FileScriptCommands.h"
#include "Lua/LuaState.h"
#include "FileSystem/File.h"
#include "TestUtils/TestResources/TempDirectory.h"
#include "TestUtils/Assert/FileAssert.h"
#include "TestUtils/Assert/LuaAssert.h"

using namespace Celeste;
using LuaState = Celeste::Lua::LuaState;


namespace TestFileSystem::Lua::ScriptCommands
{
  BASE_TEST_CLASS(TestFileScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_initialize_AddsFileUserType_ToGlobalTable)
  {
    sol::state state;

    Assert::IsFalse(state["File"].valid());

    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    Assert::IsTrue(state["File"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_initialize_Adds_new_ToFileTable)
  {
    sol::state state;

    Assert::IsFalse(state["File"]["new"].valid());

    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    Assert::IsTrue(state["File"]["new"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_initialize_Adds_exists_ToFileTable)
  {
    sol::state state;

    Assert::IsFalse(state["File"]["exists"].valid());

    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    Assert::IsTrue(state["File"]["exists"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_initialize_Adds_create_ToFileTable)
  {
    sol::state state;

    Assert::IsFalse(state["File"]["create"].valid());

    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    Assert::IsTrue(state["File"]["create"].valid());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_new_InputtingString_ReturnsFileWithCorrectPath)
  {
    sol::state state;
    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    auto result = state["File"]["new"].get<sol::protected_function>().call("Test.xml");

    Assert::IsTrue(result.valid());

    File file = result.get<File>();

    Assert::AreEqual("Test.xml", file.getFilePath().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_new_InputtingPath_ReturnsFileWithCorrectPath)
  {
    sol::state state;
    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    auto result = state["File"]["new"].get<sol::protected_function>().call(Path("Parent", "Test.xml"));

    Assert::IsTrue(result.valid());

    File file = result.get<File>();

    Assert::AreEqual(Path("Parent", "Test.xml"), file.getFilePath());
  }

#pragma endregion

#pragma region Exists Tests

#pragma region String Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_exists_InputtingInvalidPathString_ReturnsFalse)
  {
    sol::state state;
    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    auto result = state["File"]["exists"].get<sol::protected_function>().call("12312_asdas");

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_exists_InputtingNonExistentPathString_ReturnsFalse)
  {
    sol::state state;
    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    auto result = state["File"]["exists"].get<sol::protected_function>().call("Test.xml");

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_exists_InputtingExistentPathString_ReturnsTrue)
  {
    File file(Path(TempDirectory::getFullPath(), "Test.xml"));
    file.create();

    FileAssert::FileExists(file.getFilePath());

    sol::state state;
    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    auto result = state["File"]["exists"].get<sol::protected_function>().call(file.getFilePath().as_string());

    Assert::IsTrue(result.valid());
    Assert::IsTrue(result.get<bool>());
  }

#pragma endregion

#pragma region Path Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_exists_InputtingInvalidPath_ReturnsFalse)
  {
    sol::state state;
    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    auto result = state["File"]["exists"].get<sol::protected_function>().call(Path("12312_asdas"));

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_exists_InputtingNonExistentPath_ReturnsFalse)
  {
    sol::state state;
    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    auto result = state["File"]["exists"].get<sol::protected_function>().call(Path("Test.xml"));

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_exists_InputtingExistentPath_ReturnsTrue)
  {
    File file(Path(TempDirectory::getFullPath(), "Test.xml"));
    file.create();

    FileAssert::FileExists(file.getFilePath());

    sol::state state;
    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    auto result = state["File"]["exists"].get<sol::protected_function>().call(file.getFilePath());

    Assert::IsTrue(result.valid());
    Assert::IsTrue(result.get<bool>());
  }

#pragma endregion

#pragma region Instance Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_exists_InputtingInstanceWithInvalidPath_ReturnsFalse)
  {
    File file(Path("12312_asdas"));

    Assert::IsFalse(file.exists());

    sol::state state;
    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    auto result = state["File"]["exists"].get<sol::protected_function>().call(file);

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_exists_InputtingInstanceWithNonExistentPath_ReturnsFalse)
  {
    File file(Path("Test.xml"));

    Assert::IsFalse(file.exists());

    sol::state state;
    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    auto result = state["File"]["exists"].get<sol::protected_function>().call(file);

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_exists_InputtingInstanceWithExistentPath_ReturnsTrue)
  {
    File file(Path(TempDirectory::getFullPath(), "Test.xml"));
    file.create();

    FileAssert::FileExists(file.getFilePath());

    sol::state state;
    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    auto result = state["File"]["exists"].get<sol::protected_function>().call(file);

    Assert::IsTrue(result.valid());
    Assert::IsTrue(result.get<bool>());
  }

#pragma endregion

#pragma endregion

#pragma region Create Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_create_InputtingInstanceWithInvalidPath_DoesNotCreateFile)
  {
    File file(Path("12312_asdas"));

    Assert::IsFalse(file.exists());

    sol::state state;
    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    auto result = state["File"]["create"].get<sol::protected_function>().call(file);

    LuaAssert::IsValid(result);
    Assert::IsFalse(file.exists());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_create_InputtingNonExistentPath_CreatesEmptyFile)
  {
    File file(Path(TempDirectory::getFullPath(), "Test.xml"));

    Assert::IsFalse(file.exists());

    sol::state state;
    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    auto result = state["File"]["create"].get<sol::protected_function>().call(file);

    LuaAssert::IsValid(result);
    Assert::IsTrue(file.exists());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileScriptCommands_create_InputtingExistentPath_ClearsExistentFile)
  {
    File file(Path(TempDirectory::getFullPath(), "Test.xml"));
    file.create();
    file.append("Hello");

    FileAssert::FileExists(file.getFilePath());
    FileAssert::FileContentsEqual(file.getFilePath().as_string(), "Hello");

    sol::state state;
    Celeste::Lua::FileSystem::FileScriptCommands::initialize(state);

    auto result = state["File"]["create"].get<sol::protected_function>().call(file);

    LuaAssert::IsValid(result);
    FileAssert::FileExists(file.getFilePath());
    FileAssert::FileContentsEqual(file.getFilePath().as_string(), "");
  }

#pragma endregion

  };
}