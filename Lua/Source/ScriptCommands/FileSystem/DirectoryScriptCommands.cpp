#include "ScriptCommands/FileSystem/DirectoryScriptCommands.h"
#include "sol/sol.hpp"
#include "FileSystem/Directory.h"


namespace Celeste::Lua::FileSystem::DirectoryScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    bool exists_Instance(const Directory& directory)
    {
      return directory.exists();
    }

    //------------------------------------------------------------------------------------------------
    bool exists_String(const std::string& directoryPath)
    {
      return Directory::exists(directoryPath);
    }

    //------------------------------------------------------------------------------------------------
    bool exists_Path(const Path& directoryPath)
    {
      return Directory::exists(directoryPath);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    state.new_usertype<Directory>(
      "Directory", 
      sol::constructors<Directory(const std::string&), Directory(const Path&)>(),
      "exists", sol::overload(&Internals::exists_Instance, &Internals::exists_String, &Internals::exists_Path),
      "create", &Directory::create);
  }
}