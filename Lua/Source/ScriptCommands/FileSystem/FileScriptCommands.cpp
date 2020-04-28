#include "ScriptCommands/FileSystem/FileScriptCommands.h"
#include "sol/sol.hpp"
#include "FileSystem/File.h"


namespace Celeste::Lua::FileSystem::FileScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    bool exists_Instance(const File& file)
    {
      return file.exists();
    }

    //------------------------------------------------------------------------------------------------
    bool exists_String(const std::string& filePath)
    {
      return File::exists(filePath);
    }

    //------------------------------------------------------------------------------------------------
    bool exists_Path(const Path& filePath)
    {
      return File::exists(filePath);
    }

    //------------------------------------------------------------------------------------------------
    void create(File& file)
    {
      file.create();
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    state.new_usertype<File>(
      "File",
      sol::constructors<File(const std::string&), File(const Path&)>(),
      "exists", sol::overload(&Internals::exists_Instance, &Internals::exists_String, &Internals::exists_Path),
      "create", &Internals::create);
  }
}