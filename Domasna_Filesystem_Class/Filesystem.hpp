#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Directory;

class File
{
private:
    std::string name;
    std::string extension;
    uint64_t byteSize;

  public:
    File(std::string n, std::string ext, uint64_t bs);
    File(std::string n, std::string ext, uint64_t bs, Directory *dir);
    std::string getFullFilename() const;
    uint64_t getSize() const;
};

class Directory
{
private:
    Directory *parent;
    std::string name;
    std::vector<File *> files;
    std::vector<Directory *> dirs;

  public:
    Directory(std::string n, Directory *p);
    Directory(std::string n);
    uint64_t getDirectorySize();
    Directory *up();
    std::string getName();
    void printDir(const std::string &pad = "");
    File *findFile(std::string fn);
    bool removeFile(File *f);
    bool moveFile(File *f, Directory *old_parent = nullptr);
    Directory *findDir(std::string dn);
    bool removeDir(Directory *d);
    bool moveDir(Directory *d, Directory *old_parent = nullptr);
};        
