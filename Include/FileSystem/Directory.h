#pragma once

#include "File.h"
#include "dirent.h"

#include <string>
#include <vector>

namespace Celeste
{
  class Directory
  {
    public:
      Directory(const std::string& fullDirectoryPath);
      Directory(const Path& path) : Directory(path.as_string()) { }
      Directory(const Directory& directory) : Directory(directory.m_dirPath.as_string()) { }

      Directory& operator=(const Directory&);
      inline bool operator==(const Directory& rhs) const { return m_dirPath == rhs.m_dirPath; }

      /// \brief Get the directory of the executing .exe
      static void getExecutingAppDirectory(std::string& outputDir);
      static std::string getExecutingAppDirectory()
      {
        std::string buffer;
        getExecutingAppDirectory(buffer);

        return buffer;
      }

      /// \brief Checks to see if a directory exists
      /// Returns true if it does
      static bool exists(const std::string& directoryFullPath);
      static bool exists(const Path& directoryPath) { return exists(directoryPath.as_string()); }
      bool exists() const { return exists(m_dirPath.as_string()); }

      /// \brief Creates a directory and any necessary parent directories if it does not already exist
      bool create() const;

      /// \brief Removes a directory and all of the contents inside it if it exists
      bool remove() const;

      /// \brief Obtain all of the files in the current directory and add them to the inputted vector
      /// Can provide a file extension filter to limit the files we are considering - by default considers all files
      /// Can provide a flag to search recursively through subdirectories too - by default will not search recursively
      void findFiles(
        std::vector<File>& files,
        const std::string& extension = ".",
        bool includeSubDirectories = false) const;

      /// \brief Obtain all of the directories in the current directory and add them to the inputted vector
      /// Can provide a flag to search recursively through subdirectories too - by default will not search recursively
      void findDirectories(
        std::vector<Directory>& directories,
        bool includeSubDirectories = false) const;

      /// \brief Various creation functions for objects relative to this directory
      File createFile(const std::string& fileName);
      Directory createDirectory(const std::string& directoryName);

      /// \brief Returns the name of this directory relative to it's parent.  Contains no path delimiters
      std::string getDirectoryName() const;

      const Path& getDirectoryPath() const { return m_dirPath; }

    private:
      Path m_dirPath;
  };
}