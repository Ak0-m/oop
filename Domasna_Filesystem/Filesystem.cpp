#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

// Homework for 21.10.2026

// To complete the homework, it MUST be uploaded to your oop repo on Github!!

// 0. Enforce that no file/directory with the same nameext can be created in the same dir.
// 1. When printing the directory, print the contents of all child directories!!!
// 2. Implement 'Up' function that return the parent directory of the current directory
//    If no parent is available, print '/(root)'
// 3. Implement "Find" that searches for a file or directory inside a specific directory.
//    The file/directory can be nested inside a subdirectory
// 4. DirectorySize function includes the size of child directoriesg

using namespace std;

struct File
{
    string name;
    string extension;
    uint64_t byteSize;
};

string getFullFilename(File &f)
{
    return f.name + '.' + f.extension;
}

struct Directory
{
    Directory *parent = nullptr;
    string name;
    vector<File *> files;
    vector<Directory *> dirs;
};

// 4. DirectorySize function includes the size of child directoriesg
uint64_t getDirectorySize(Directory &d)
{
    uint64_t sz = 0;
    for (size_t i = 0; i < d.files.size(); i++)
    {
        sz += d.files[i]->byteSize;
    }
    for (size_t i = 0; i < d.dirs.size(); ++i)
    {
        sz += getDirectorySize(*d.dirs[i]);
    }

    return sz;
}

// 0. Enforce that no file/directory with the same nameext can be created in the same dir.
bool addFile(File *f, Directory &dir)
{
    string name = getFullFilename(*f);

    for (size_t i = 0; i < dir.files.size(); ++i)
    {
        if (getFullFilename(*dir.files[i]) == name)
        {
            return false;
        }
    }
    dir.files.push_back(f);
    return true;
}
bool addDir(Directory *d_added, Directory &dir)
{
    if (d_added->parent != nullptr)
    {
        return false;
    }
    for (size_t i = 0; i < dir.dirs.size(); ++i)
    {
        if (dir.dirs[i]->name == d_added->name)
        {
            return false;
        }
    }
    dir.dirs.push_back(d_added);
    d_added->parent = &dir;
    return true;
}

bool moveDir(const string &dirname, Directory &from, Directory &to)
{
    Directory *dir = nullptr;
    for (size_t i = 0; i < to.dirs.size() - 1; i++)
    {
        if (to.dirs[i]->name == dirname)
        {
            return false;
        }
    }
    for (size_t i = 0; i < from.dirs.size(); i++)
    {
        if (dirname == from.dirs[i]->name)
        {
            dir = from.dirs[i];
            for (size_t j = i; j < from.dirs.size() - 1; j++)
            {
                from.dirs[j] = from.dirs[j + 1];
            }
            from.dirs.pop_back();

            dir->parent = &to;
            to.dirs.push_back(dir);
            return true;
        }
    }
    return false;
}

bool moveFile(const string &filename, Directory &from, Directory &to)
{
    File *file = nullptr;
    for (size_t i = 0; i < to.files.size() - 1; i++)
    {
        if (to.files[i]->name == filename)
        {
            return false;
        }
    }
    for (size_t i = 0; i < from.files.size(); i++)
    {
        if (filename == getFullFilename(*from.files[i]))
        {
            file = from.files[i];
            for (size_t j = i; j < from.files.size() - 1; j++)
            {
                from.files[j] = from.files[j + 1];
            }
            from.files.pop_back();

            to.files.push_back(file);
            return true;
        }
    }
    return false;
}

// 1. When printing the directory, print the contents of all child directories!!!
void printDir(Directory &d, const string &pad = "")
{
    std::cout << pad << "d: " << d.name << '\n';
    for (size_t i = 0; i < d.files.size(); i++)
    {
        std::cout << pad << " f " << getFullFilename(*d.files[i]) << '\n';
    }
    for (size_t i = 0; i < d.dirs.size(); i++)
    {
        printDir(*d.dirs[i], pad + " ");
    }
    std::cout << pad << "Size: " << getDirectorySize(d) << " B\n";
}

// 2. Implement 'Up' function that return the parent directory of the current directory
//    If no parent is available, print '/(root)'
Directory *Up(Directory &d)
{
    if (d.parent == nullptr)
    {
        cout << "\\(root)\n";
    }
    return d.parent;
}

File *findFile(const string &f, Directory &d)
{
    for (size_t i = 0; i < d.files.size(); ++i)
    {
        if (f == getFullFilename(*d.files[i]))
        {
            return d.files[i];
        }
    }
    for (size_t i = 0; i < d.dirs.size(); ++i)
    {
        File *r = findFile(f, *d.dirs[i]);
        if (r != nullptr)
        {
            return r;
        }
    }
    return nullptr;
}
Directory *findDir(const string &search_d, Directory &d)
{
    for (size_t i = 0; i < d.dirs.size(); ++i)
    {
        if (search_d == d.dirs[i]->name)
        {
            return d.dirs[i];
        }
    }
    for (size_t i = 0; i < d.dirs.size(); ++i)
    {
        Directory *r = findDir(search_d, *d.dirs[i]);
        if (r != nullptr)
        {
            return r;
        }
    }
    return nullptr;
}

int main()
{
    Directory my, tx;
    my.name = "documents";
    File x, y, z;
    x.name = "X";
    x.extension = "txt";
    x.byteSize = 1024;

    y.name = "Y";
    y.extension = "jpeg";
    y.byteSize = 56281022;

    z.name = "z";
    z.extension = "mov";
    z.byteSize = 1556281022;

    addFile(&x, my);
    addFile(&z, my);
    addFile(&y, my);
    addFile(&x, my);

    y.name = "YYY";

    Directory child;
    child.name = "Child One";

    tx.name = "TX";

    addDir(&child, my);
    addDir(&tx, child);

    printDir(my);

    moveFile(getFullFilename(z), my, child);

    cout << "AFTER MOVE\n";
    printDir(my, "");

    cout << findFile("z.mov", my) << "\n";
    return 0;
}
