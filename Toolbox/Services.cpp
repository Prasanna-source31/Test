#define CURL_STATICLIB
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <fstream>
#include <ftw.h>
#define GetCurrentDir _getcwd
using namespace std;
#include "Curl/curl.h"
#include "Dep/configurations.h"
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"Normaliz.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Wldap32.lib")
#pragma comment(lib,"Crypt32.lib")
#pragma comment(lib,"advapi32.lib")

string GetcurrentworkingDirectory()
{
char buff[FILENAME_MAX];
 GetCurrentDir(buff, FILENAME_MAX);
 string current_working_dir(buff);
 return current_working_dir;
}
int Showlog()
{

}


static size_t my_write(void* buffer, size_t size, size_t nmedb, void* param)
{
	string& text = *static_cast<string*>(param);
	size_t totalsize = size * nmedb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}

int ConnectionChecker()
{
    int status;
    string connectionCheckerURL=Configurations:: connectionCheckerURL;
    string result;
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, connectionCheckerURL.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        res = curl_easy_perform(curl);
        
        curl_easy_cleanup(curl);
        if (res == CURLE_OK)
        {
            cout<<"Success"<<endl;
            status=1;
            //break;
        }
        else
        {
             cout<<"Fail"<<endl;
             status=0;
        }
    }
    return status;
}

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

int DownloadFingerprinter()
{
  
  string downloadURL = Configurations::fingerprinterURL;
  CURL *curl_handle;
  static const char *pagefilename = (Configurations::fingerprinter).c_str();
  FILE *pagefile;

  curl_global_init(CURL_GLOBAL_ALL);
  curl_handle = curl_easy_init();
  curl_easy_setopt(curl_handle, CURLOPT_URL, downloadURL.c_str());
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
  pagefile = fopen(pagefilename, "wb");
  if (pagefile)
  {
      curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);
      curl_easy_perform(curl_handle);
      fclose(pagefile);
     string getdirectory=GetcurrentworkingDirectory();
     cout<<getdirectory<<endl;
 system(("move "+getdirectory+"\\CIS-Inventory-Start.exe"+ " C:\\CIS4ITM\\CIS-Inventory-Start.exe").c_str());
  }
  curl_easy_cleanup(curl_handle);
  curl_global_cleanup();
  return 0;
}
