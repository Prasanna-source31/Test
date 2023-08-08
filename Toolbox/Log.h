#include<iostream>
#include "../Constants.cpp"
using namespace std;
void Logger();
string GetcurrentDirectory();
void Log(LogPriority priority, const char *message, string component, int line, string functionName);