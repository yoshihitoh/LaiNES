#pragma once
#include <functional>
#include <memory>
#include <string>
#include "common.hpp"

namespace PORTING {


enum class DirectoryItemType {
    DIRECTORY,
    FILE,
};


struct DirectoryItem {
    DirectoryItemType item_type;
    std::string  name;

    bool IsDirectory() const { return item_type == DirectoryItemType::DIRECTORY; }
    bool IsFile() const { return item_type == DirectoryItemType::FILE; }
};


using DirectoryItemHandler = std::function<void(const DirectoryItem&)>;


class Directory {
public:
    virtual ~Directory() {}
    virtual const char* GetRootPath() const = 0;
    virtual void ForEachItems(const DirectoryItemHandler& handler) const = 0;
};


int MakeDirectory(const char* dir_path, int mode);
std::unique_ptr<Directory> GetDirectoryFor(const char* root_path);
std::unique_ptr<Directory> GetWorkingDirectory();


}
