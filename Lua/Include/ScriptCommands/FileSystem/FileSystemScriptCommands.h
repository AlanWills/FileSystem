#pragma once


namespace sol
{
  class state;
}

namespace Celeste::Lua::FileSystem::ScriptCommands
{
  void initialize(sol::state& state);
}