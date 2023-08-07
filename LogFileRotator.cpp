#include <fstream>
#include <iostream>
#include <stdexcept> 
#include <string>
 #include "stdafx.h"
    #include "FileRotator.h"
    #include "string.h"
	//#define _tmain main
   using namespace std;
    
   class MyLogger
   {
  public:
   	MyLogger() : mFileRotator(1024 /*bytes*/,"C:/CIS4ITM/log.txt")
   	{
  		mFileRotator.Open();
   	}
   	~MyLogger()
  	{
   		mFileRotator.Close();
  	}
   	int Log() 
   	{
  		//
   		// customize your log message like adding date time etc. here
  		//
  		string logStr = string("Info:") + "Hello" + string("\n");
		
  
  		return mFileRotator.Write(logStr.c_str());
 	}
   
   private:
  	FileRotator mFileRotator;
   };
  
  //int _tmain(int argc, _TCHAR* argv[])
  int main(int argc,char* argv[])
   {
  	MyLogger myLogger;
  
   	int i = 0;
  
  	while (i < 10000) {
  		myLogger.Log();
   		i++;
   	}
  
  	return 0;
   }