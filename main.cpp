#include <iostream>
#include <string>
#include "FS.hpp"
using namespace std;

char file[] = "./FileSys";
FS fs(file);

int main()
{
    cout << "/>";
    string op;
    string contxt;
    string par;
    int wptr;
    while (cin >> op)
    {
        if (op == "ls")
        {
            char a = getchar();
            if (a == '\n')
            {
                char path[] = ".";
                fs.list(path);
            }
            else
            {
                cin >> par;
                fs.list(par.c_str());
            }
        }
        if (op == "cd")
        {
            cin >> par;
            fs.changedir(par.c_str());
        }
        if (op == "touch")
        {
            cin >> par;
            fs.createfile(par.c_str());
        }
        if (op == "mkdir")
        {
            cin >> par;
            fs.makedir(par.c_str());
        }
        if (op == "rmdir")
        {
            cin >> par;
            fs.removedir(par.c_str());
        }
        if (op == "open")
        {
            cin >> par;
            wptr = fs.openfile(par.c_str(), READ | WRITE);
        }
        if (op == "write")
        {
            cin >> par;
            char line[524288];
            contxt = "";
            cin.get();
            cin.getline(line, 524288, '\n');
            cin.clear();
            while (string(line) != "EOF")
            {
                contxt += string(line) + '\n';
                cin.getline(line, 1024, '\n');
                cin.clear();
            }
            fs.writefile(par.c_str(), contxt.c_str());
        }
        if (op == "cat")
        {
            cin >> par;
            fs.readfile(par.c_str());
        }
        if (op == "rm")
        {
            cin >> par;
            fs.removefile(par.c_str());
        }
        if (op == "quit")
            break;
        if (op == "close")
        {
            fs.close(wptr);
        }
        cout << fs.workpath << ">";
    }
}