// ConsoleShellExecuteA.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
// Execute command or exe and get the output of the command

#include <iostream>
#include <Windows.h>
#include <shellapi.h>

#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}

int main()
{
    std::cout << "Performs an operation on a specified file\n";

    // Example 1: using ShellExecuteA
    // It will run exe on another command prompt
    // -------------------------------------------------------------------------- //
    //HWND handle = nullptr;
    //LPCSTR lop = "open";
    //LPCSTR lfile = "netcoreapp3.1\\ConsoleCmdLineArgs.exe";
    //LPCSTR lparam = "In 1";
    //LPCSTR ldirectory = nullptr;
    //int nsh = 1;

    //ShellExecuteA(handle, lop, lfile, lparam, ldirectory, nsh);

    // Example 2: using system()
    // It will run exe on the same command prompt
    // ------------------------------------------------------------------------- //
    //int retCode = system("netcoreapp3.1\\ConsoleCmdLineArgs.exe In 1");

    // Example 3:
    // Execute a command and get the output of the command
    // ------------------------------------------------------------------------- //
    std::string myResult;
    std::string userinput = "";

    std::cout << "Input command: ";
    std::getline(std::cin, userinput);

    myResult = exec(userinput.c_str());
    //myResult = exec("netcoreapp3.1\\ConsoleCmdLineArgs.exe In 1");
    std::cout << "Return Result: " + myResult;
}


/* Output */
// Performs an operation on a specified file
// Return Result : ConsoleCmdLineArgs is 1

