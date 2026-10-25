#include "Filesystem.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

File::File(std::string n, std::string ext, uint64_t bs)
{
    name = n;
    extension = ext;
    byteSize = bs;
}
File::File(std::string n, std::string ext, uint64_t bs, Directory *dir)
{
    if (dir->findFile(n + '.' + ext) != nullptr)
    {
        throw std::invalid_argument("File with same name already exists in parent directory");
    }
    name = n;
    extension = ext;
    byteSize = bs;
    dir->moveFile(this);
}
std::string File::getFullFilename()
{
    return name + '.' + extension;
}
uint64_t File::getSize()
{
    return byteSize;
}

// bool File::move();

Directory::Directory(std::string n, Directory *p)
{

    if (!(p->moveDir(this)))
    {
        throw std::invalid_argument("Directory with same name already exists in parent directory");
    }

    parent = p;
    name = n;
}
Directory::Directory(std::string n)
{
    parent = nullptr;
    name = n;
}

uint64_t Directory::getDirectorySize()
{
    uint size = 0;
    for (size_t i = 0; i < files.size(); ++i)
    {
        size += files[i]->getSize();
    }
    for (size_t i = 0; i < dirs.size(); ++i)
    {
        size += dirs[i]->getDirectorySize();
    }
    return size;
}
File *Directory::findFile(std::string fn)
{
    for (size_t i = 0; i < files.size(); ++i)
    {
        if (fn == files[i]->getFullFilename())
        {
            return files[i];
        }
    }
    for (size_t i = 0; i < dirs.size(); ++i)
    {
        File *t = dirs[i]->findFile(fn);
        if (t != nullptr)
        {
            return t;
        }
    }
    return nullptr;
}
bool Directory::removeFile(File *f)
{
    for (size_t i = 0; i < files.size(); ++i)
    {
        if (f == files[i])
        {
            for (size_t j = i + 1; j < files.size(); ++j)
            {
                files[j - 1] = files[j];
            }
            files.pop_back();
            return true;
        }
    }
    return false;
}
bool Directory::moveFile(File *f, Directory *old_parent)
{
    if (findFile(f->getFullFilename()) != nullptr)
    {
        return false;
    }
    if (old_parent != nullptr)
    {
        if (!(old_parent->removeFile(f)))
        {
            return false;
        }
    }
    files.push_back(f);
    return true;
}
Directory *Directory::findDir(std::string dn)
{
    for (size_t i = 0; i < dirs.size(); ++i)
    {
        if (dn == dirs[i]->name)
        {
            return dirs[i];
        }
    }
    for (size_t i = 0; i < dirs.size(); ++i)
    {
        Directory *t = dirs[i]->findDir(dn);
        if (t != nullptr)
        {
            return t;
        }
    }
    return nullptr;
}
bool Directory::removeDir(Directory *d)
{
    for (size_t i = 0; i < dirs.size(); ++i)
    {
        if (d == dirs[i])
        {
            for (size_t j = i + 1; j < dirs.size(); ++j)
            {
                dirs[j - 1] = dirs[j];
            }
            dirs.pop_back();
            return true;
        }
    }
    return false;
}
bool Directory::moveDir(Directory *d, Directory *old_parent)
{
    if ((findDir(d->name)) != nullptr)
    {
        return false;
    }
    if (old_parent != nullptr)
    {
        if (!(old_parent->removeDir(d)))
        {
            return false;
        }
    }

    dirs.push_back(d);
    return true;
}

int main()
{
    Directory Dir1("Documents");
    Directory Dir2("Files", &Dir1);

    File file1("document1", "txt", 5120, &Dir1);
    File file2("document2", "txt", 6620, &Dir1);
    File file3("document3", "txt", 10120, &Dir2);

    std::cout << Dir1.getDirectorySize() << "\n";
    return 0;
}
