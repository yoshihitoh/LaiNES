#pragma once

#include <direct.h>
#include <windows.h>
#include "porting/directory.hpp"


namespace PORTING {

namespace {
class WindowsDirectory : public Directory
{
public:
    explicit WindowsDirectory(const char* dir_path);
    const char* GetRootPath() const override;
    void ForEachItems(const DirectoryItemHandler& handler) const override;

private:
    std::string dir_path_;
};

struct FindContext {
    WIN32_FIND_DATAA find_data;
    HANDLE find_handle;

    explicit FindContext(const char* dir_path);
    ~FindContext();
};
}


static bool isValidHandle(HANDLE handle)
{
    return handle != INVALID_HANDLE_VALUE;
}


FindContext::FindContext(const char* dir_path)
    : find_data({})
    , find_handle(FindFirstFileA((std::string(dir_path) + "/*").c_str(), &find_data))
{
}


FindContext::~FindContext()
{
    if (isValidHandle(find_handle)) {
        FindClose(find_handle);
    }
}


WindowsDirectory::WindowsDirectory(const char* dir_path)
    : dir_path_(dir_path)
{
}


const char* WindowsDirectory::GetRootPath() const
{
    return dir_path_.c_str();
}


void WindowsDirectory::ForEachItems(const DirectoryItemHandler& handler) const
{
    FindContext context(dir_path_.c_str());
    if (!isValidHandle(context.find_handle)) return;

    auto has_file = true;
    while (has_file) {
        const auto item_type = context.find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
            ? DirectoryItemType::DIRECTORY
            : DirectoryItemType::FILE;

        const DirectoryItem dir_item{ item_type, context.find_data.cFileName };
        handler(dir_item);

        has_file = FindNextFileA(context.find_handle, &context.find_data);
    }
}


int MakeDirectory(const char* dir_path, int)
{
    return _mkdir(dir_path);
}


std::unique_ptr<Directory> GetDirectoryFor(const char* root_path)
{
    return std::unique_ptr<Directory>(std::make_unique<WindowsDirectory>(root_path));
}


std::unique_ptr<Directory> GetWorkingDirectory()
{
    char path[MAX_PATH + 1] = {};
    GetCurrentDirectoryA(MAX_PATH, path);
    return GetDirectoryFor(path);
}


}
