#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include "porting/directory.hpp"


namespace PORTING {

namespace {

struct DirentResource
{
    DIR* p_dir;
    DirentResource(const char* dir_path);
    ~DirentResource();
};


class UnixDirectory : public Directory
{
public:
    explicit UnixDirectory(const char* dir_path);
    const char* GetRootPath() const override;
    void ForEachItems(const DirectoryItemHandler& handler) const override;

private:
    std::string dir_path_;
};

}


DirentResource::DirentResource(const char* dir_path)
    : p_dir(opendir(dir_path))
{
}


DirentResource::~DirentResource()
{
    if (p_dir != nullptr) {
        closedir(p_dir);
    }
}



UnixDirectory::UnixDirectory(const char* dir_path)
    : dir_path_(dir_path)
{
}


const char* UnixDirectory::GetRootPath() const
{
    return dir_path_.c_str();
}


void UnixDirectory::ForEachItems(const DirectoryItemHandler& handler) const
{
    DirentResource dirent_resource(GetRootPath());

    struct dirent* p_dirent;
    while ((p_dirent = readdir(dirent_resource.p_dir)) != NULL)
    {
        const auto item_type = p_dirent->d_type == DT_DIR
            ? DirectoryItemType::DIRECTORY
            : DirectoryItemType::FILE;

        const DirectoryItem dir_item{ item_type, p_dirent->d_name };
        handler(dir_item);
    }
}


int MakeDirectory(const char* dir_path, int mode)
{
    return mkdir(dir_path, mode);
}


std::unique_ptr<Directory> GetDirectoryFor(const char* root_path)
{
    return std::unique_ptr<Directory>(std::make_unique<UnixDirectory>(root_path));
}


std::unique_ptr<Directory> GetWorkingDirectory()
{
    char path[512] = {};
    return GetDirectoryFor(getcwd(path, 512));
}


}
