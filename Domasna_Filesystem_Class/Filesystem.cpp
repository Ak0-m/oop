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

    name = n;
    extension = ext;
    byteSize = bs;
    if (!(dir->moveFile(this)))
    {
        throw std::invalid_argument("File with same name already exists in parent directory");
    }
}
std::string File::getFullFilename() const
{
    return name + '.' + extension;
}
uint64_t File::getSize() const
{
    return byteSize;
}

// bool File::move();

Directory::Directory(std::string n, Directory *p)
{
    parent = p;
    name = n;

    if (!(p->moveDir(this)))
    {
        throw std::invalid_argument("Directory with same name already exists in parent directory");
    }
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
Directory *Directory::up()
{
    if (parent == nullptr)
    {
        std::cout << "\\(root)\n";
    }
    return parent;
}
std::string Directory::getName()
{
    return name;
}
void Directory::printDir(const std::string &pad)
{
    std::cout << pad << "d: " << name << '\n';
    for (size_t i = 0; i < files.size(); i++)
    {
        std::cout << pad << " f " << files[i]->getFullFilename() << '\n';
    }
    for (size_t i = 0; i < dirs.size(); i++)
    {
        dirs[i]->printDir(pad + " ");
    }
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
    for (size_t i = 0; i < files.size(); ++i)
    {
        if (files[i]->getFullFilename() == f->getFullFilename())
        {
            return false;
        }
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
    for (int i = 0; i < dirs.size(); ++i)
    {
        if (dirs[i]->name == d->name)
        {
            return false;
        }
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
    Directory Dir3("Photos", &Dir1);

    File file1("document1", "txt", 5120, &Dir1);
    File file2("document2", "txt", 6620, &Dir1);
    File file3("document2", "txt", 10120, &Dir2);

    File photo1("video", "mp4", 60120, &Dir3);
    File photo2("photo1", "jpg", 56620, &Dir3);
    File photo3("photo2", "png", 20120, &Dir3);

    Dir1.printDir();

    std::cout << Dir1.getDirectorySize() << "\n";
    std::cout << Dir3.up()->getName() << "\n";

    auto video = Dir1.findFile("video.mp4");

    if (video != nullptr)
    {
        std::cout << "video found in " << Dir1.getName() << "\n";
    }
    else
    {
        std::cout << "video not found in " << Dir1.getName() << "\n";
    }

    Dir3.removeFile(video);

    if (Dir3.findFile("video.mp4"))
    {
        std::cout << "video found in " << Dir3.getName() << "\n";
    }
    else
    {
        std::cout << "video not found in " << Dir3.getName() << "\n";
    }

    return 0;
}
