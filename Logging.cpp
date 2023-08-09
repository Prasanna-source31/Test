#include<iostream>
#include <dirent.h>
#include "Dep/Log.h"
#include<windows.h>
#include<dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fstream>
#include <ftw.h>
#include <direct.h>
#include <vector>
#include "Dep/Configurations.h"

#define GetCurrentDir _getcwd



string GetcurrentDirectory()
{
char buff[FILENAME_MAX];
 GetCurrentDir(buff, FILENAME_MAX);
 string current_working_dir(buff);
 return current_working_dir;
}


void Logger()
{

    string dir=GetcurrentDirectory();
    string logfileName="Log";
     string log= Configurations:: logFolderName;
     CreateDirectory ((dir + "\\" + log).c_str(), NULL);
     DIR *dp;
    int count;
    int i = 0;
    struct dirent *ep;
    dp = opendir((dir + "\\" + log).c_str());
    if (dp != NULL) {
        while (ep = readdir(dp))
            i++;
        (void)closedir(dp);
    }
    else
        cout<<"Couldn't open the directory";
    count = i - 2; 
    char date[20];
    char systemtime[20];
    struct tm *sTm;
    // To get actual date and time
    time_t now = time(0);
    sTm = localtime(&now);
    // To format the time
    strftime(date, sizeof(date), "%Y%m%d", sTm);
    strftime(systemtime, sizeof(systemtime), "%H%M", sTm);
    // if count is within 10
    if (count >= 0 && count < 10)
    {
        string path = (dir + "\\" + log+"\\").c_str();
        //remove((path + logfileName + "_" + date  + ".txt").c_str());
        ofstream FILE(path + logfileName + "_" + date  + ".txt",ios_base::app);
        FILE << "DATE|TIME|LINE|FUNCTION|COMPONENT|SEVERITY|MESSAGE\n";
        FILE.close();
    }
    // if count is more than 10 , delete the older file by calling check if older function
    else
    {
        // ftw((dir + "\\" + log+"\\").c_str(), CheckIfOlder, 1);
       
          string path = (dir + "\\" + log+"\\").c_str();
           cout<<(path + logfileName + "_" + date  + ".txt").c_str()<<endl;
          remove((path + logfileName + "_" + date  + ".txt").c_str());
          ofstream FILE(path + logfileName + "_" + date  + ".txt",ios_base::app);
          FILE << "DATE|TIME|LINE|FUNCTION|COMPONENT|SEVERITY|MESSAGE\n";
          FILE.close();
    }
}
void Log(LogPriority priority, const char *message, string component, int line, string functionName)
{
     string dir=GetcurrentDirectory();
     string logfileName="Log";
     string log= Configurations:: logFolderName;
     char date[20];
    char systemtime[20];
    char filedate[20];
    char filetime[20];
    struct tm *sTm;
    // To get actual date and time
    time_t now = time(0);
    sTm = localtime(&now);
    // To format the time for filename
    strftime(date, sizeof(date), "%Y%m%d", sTm);
    strftime(systemtime, sizeof(systemtime), "%H%M", sTm);
    // To format the time for printing message within the log file
    strftime(filedate, sizeof(date), "%Y-%m-%d", sTm);
    strftime(filetime, sizeof(systemtime), "%H:%M:%S", sTm);
    // Create the file where message needs to be logged
    string path = (dir + "\\" + log+"\\").c_str();

     ofstream FILE(path + logfileName + "_" + date  + ".txt",ios_base::app);
     //logic to check the size of the file and truncate if it is more than 25KB
     int size;
     struct stat st;
     string Filename = path + logfileName + "_" + string (date)  + ".txt";
     stat(Filename.c_str(), &st);
     size = st.st_size;
     cout<<size<<endl;
     if (size > 25600)
     {
         FILE << "DATE|TIME|LINE|FUNCTION|COMPONENT|SEVERITY|MESSAGE\n";
         ofstream FILE(path + logfileName + "_" + date  + ".txt", ios_base::trunc);
     }
    // Log the message based on severity
    switch (priority)
    {
    case TraceP:
        FILE << filedate << "|" << filetime << "|" << line << "|" << functionName << "|" << component << "|"
             << "Trace"
             << "|" << message << "\n";
        break;
    case DebugP:
        FILE << filedate << "|" << filetime << "|" << line << "|" << functionName << "|" << component << "|"
             << "Debug"
             << "|" << message << "\n";
        break;
    case InfoP:
    cout<<"Info"<<endl;
        FILE << filedate << "|" << filetime << "|" << line << "|" << functionName << "|" << component << "|"
             << "Info"
             << "|" << message << "\n";
        break;
    case WarnP:
        FILE << filedate << "|" << filetime << "|" << line << "|" << functionName << "|" << component << "|"
             << "Warn"
             << "|" << message << "\n";
        break;
    case ErrorP:
        FILE << filedate << "|" << filetime << "|" << line << "|" << functionName << "|" << component << "|"
             << "Error"
             << "|" << message;
        break;
       
    } 
     FILE.close(); 
}
