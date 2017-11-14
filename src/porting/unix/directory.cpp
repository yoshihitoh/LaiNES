#pragma once


#include <dirent.h>
#include <unistd.h>


namespace PORTING {

// TODO: add unix implementation

#if 0
struct DirentResource
{
    DIR* p_dir;
    DirentResource(const char* dir_path)
        : p_dir(opendir(dir_path))
    {
    }

    ~DirentResource()
    {
        if (p_dir != nullptr) {
            closedir(p_dir);
        }
    }
};


static void ForEachDirEntries(const char* root_path, const Directory::EntryHandler& entry_handler)
{
    DirentResource dirent_resource(root_path);

    struct dirent* p_dirent;
    while ((p_dirent = readdir(dirent_resource.p_dir)) != NULL)
    {
        std::string name = dirp->d_name;
        auto dir_entry = dirp->d_type == DT_DIR
            ? DirectoryEntry::Directory(name.c_str())
            : DirectoryEntry::File(name.c_str());

        entry_handler(dir_entry);
    }
}


static std::string GetWorkingDirectory()
{
    char path_buff[512 + 1] = {};
    return std::string(getcwd(path_buff, 512));
}
#endif


}
