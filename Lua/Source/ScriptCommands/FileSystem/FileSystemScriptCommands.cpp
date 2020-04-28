#include "ScriptCommands/FileSystem/FileSystemScriptCommands.h"
#include "ScriptCommands/FileSystem/PathScriptCommands.h"
#include "ScriptCommands/FileSystem/DirectoryScriptCommands.h"
#include "ScriptCommands/FileSystem/FileScriptCommands.h"


namespace Celeste::Lua::FileSystem::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    PathScriptCommands::initialize(state);
    DirectoryScriptCommands::initialize(state);
    FileScriptCommands::initialize(state);
  }
}