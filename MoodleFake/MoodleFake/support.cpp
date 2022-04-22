#include <iostream>
#include <fstream>
//#include <dirent.h>

#include <string.h>
#include <sys/stat.h>
#include <windows.h>
#include <direct.h>
#include <conio.h>;
#include <string>
using namespace std;
void reset_cache()
{
    remove_dir("data/cache");
    mkdir("data/cache");
    mkdir("data/cache/Semester");
    mkdir("data/cache/Semester/coureses");
    mkdir("data/cache/Semester/students");
    mkdir("data/cache/csvFile");
}

void remove_dir(char* path)
{
    struct dirent* entry = NULL;
    DIR* dir = NULL;
    dir = opendir(path);
    while (entry = readdir(dir))
    {
        DIR* sub_dir = NULL;
        FILE* file = NULL;
        char abs_path[100] = { 0 };
        if (*(entry->d_name) != '.')
        {
            sprintf(abs_path, "%s/%s", path, entry->d_name);
            if (sub_dir = opendir(abs_path))
            {
                closedir(sub_dir);
                remove_dir(abs_path);
            }
            else
            {
                if (file = fopen(abs_path, "r"))
                {
                    fclose(file);
                    remove(abs_path);
                }
            }
        }
    }
    remove(path);
    rmdir(path);
}
void Pull()
{
    string YY, TERM;
    string path_in = "data/cache/currentSemester.txt";
    ifstream fin;
    fin.open(path_in);
    fin >> YY >> TERM;
    fin.close();

    string srcDir = "data/" + YY + '/' + TERM; // Folder truyen di
    string destDir = "data/cache/Semester";   // Folder den
    copyDir_(srcDir.c_str(), destDir);

    srcDir = "csvFile/" + YY + '/' + TERM; // Folder truyen di
    destDir = "data/cache/csvFile";   // Folder den
    copyDir_(srcDir.c_str(), destDir);
}

void Push()
{
    string YY, TERM;
    string path_in = "data/cache/currentSemester.txt";
    ifstream fin;
    fin.open(path_in);
    fin >> YY >> TERM;
    fin.close();

    string srcDir = "data/cache/Semester";
    string destDir = "data/" + YY + '/' + TERM; // Folder truyen di
    // Folder den
    copyDir_(srcDir.c_str(), destDir);

    destDir = "csvFile/" + YY + '/' + TERM; // Folder truyen di
    srcDir = "data/cache/csvFile";   // Folder den
    copyDir_(srcDir.c_str(), destDir);
}

void copyDir_(const char* inputDir, string outDir)
{

    DIR* pDIR;
    struct dirent* entry;
    string tmpStr, tmpStrPath, outStrPath, inputDir_str = inputDir;

    if (is_dir(inputDir) == false)
    {
        cout << "This is not a folder " << endl;
        return;
    }


    if (pDIR = opendir(inputDir_str.c_str()))
    {

        while (entry = readdir(pDIR)) // get folders and files names
        {

            tmpStr = entry->d_name;
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                tmpStrPath = inputDir_str;
                tmpStrPath.append("\\");
                tmpStrPath.append(tmpStr);

                cout << entry->d_name;
                if (is_dir(tmpStrPath.c_str()))
                {
                    cout << "--> It's a folder" << "\n";
                    // Create Folder on the destination path
                    outStrPath = outDir;
                    outStrPath.append("\\");
                    outStrPath.append(tmpStr);
                    mkdir(outStrPath.c_str());

                    copyDir_(tmpStrPath.c_str(), outStrPath);
                }
                else
                {
                    cout << "--> It's a file" << "\n";
                    // copy file on the destination path
                    outStrPath = outDir;
                    outStrPath.append("\\");
                    outStrPath.append(tmpStr);
                    copyFile_(tmpStrPath.c_str(), outStrPath.c_str());
                }
            }
        }
        closedir(pDIR);
    }
}

bool is_dir(const char* path)
{
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

void copyFile_(string inDir, string outDir)
{
    CopyFile(inDir.c_str(), outDir.c_str(), 0);
    DWORD Error = GetLastError();
}