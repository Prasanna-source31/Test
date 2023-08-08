#include <windows.h>
#include <Lmcons.h>
#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include "Dep/Services.h"
#include <commctrl.h>
#include <bits/stdc++.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "Dep/Log.h"

//#define WS_BORDER 0x00800000L

using namespace std;
static HWND hwndtextbox7;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#define ID_COMBO 1
#define ID_FOLDER 3
#define ID_CHECKBOX 4
#define ID_DOWNLOAD 5
#define ID_ACL 6
#define ID_SCHTASK 7
#define ID_DAILY 8
#define ID_WEEKLY 9
#define ID_MONTHLY 10
#define ID_WEEKDAYS 11
#define ID_START 12
#define ID_QUICKWEEKDAYS 13
#define ID_QUICKDATE 14
#define ID_ONSTART 15
#define ID_ADVANCED 16
#define ID_TEXTBOX8 17
#define ID_RANDOM 18
#define ID_RANDOMADV 19
#define ID_STARTUPADV 20
#define ID_USER 21
#define ID_SCHEDULE 22
//german
#define ID_COMBODE 30
  SYSTEMTIME add( SYSTEMTIME s, double seconds ) {

    FILETIME f;
    SystemTimeToFileTime( &s, &f );

    ULARGE_INTEGER u  ; 
    memcpy( &u  , &f , sizeof( u ) );

    const double c_dSecondsPer100nsInterval = 100.*1.e-9;
    const double c_dNumberOf100nsIntervals = 
                    seconds / c_dSecondsPer100nsInterval;

    // note: you may want to round the number of intervals.
    u.QuadPart += c_dNumberOf100nsIntervals;

    memcpy( &f, &u, sizeof( f ) );

    FileTimeToSystemTime( &f, &s );
    return s;
 }
int Randomize()
{
    int size = 2;
    int array[size];
    int Random;
        array[0]=10;
        array[1]=-10;
    int index = rand() % size;
    Random = array[index];
  return Random;
}
void Download()
{
    printf("Hi from download");
}

//  CreateDatePick creates a DTP control within a dialog box.
//  Returns the handle to the new DTP control if successful, or NULL
//  otherwise.
//
//    hwndMain - The handle to the main window.
//    g_hinst  - global handle to the program instance.

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance,
         PWSTR lpCmdLine, int nCmdShow)
{
   ShowWindow(::GetConsoleWindow(), SW_HIDE);

   Logger();
   //Log(InfoP,"length","Deployment Toolbox",__LINE__,"main");

    MSG msg;
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"CIS4ITM Deployment-toolbox";
    wc.hInstance = hInstance;
    // wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"CIS4ITM Deployment-toolbox",
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE,
                  300, 300, 300, 200, 0, 0, hInstance, 0);

    while (GetMessage(&msg, NULL, 0, 0))
    {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
                         WPARAM wParam, LPARAM lParam)
{

    static HWND hwndcombo;
    static HWND hwndconnection;
    static HWND hwndfolder;
    static HWND hwndtextbox;
    static HWND hwndtextbox2;
    static HWND hwndtextbox3;
    static HWND hwndtextbox4;
    static HWND hwndtextbox5;
    static HWND hwndtextbox6;
  
    static HWND hwndtextbox8;
    static HWND hwndtextbox9;
    static HWND hwnddownload;
    static HWND hwndACL;
    static HWND hwndschtask;
    static HWND hwnddaily;
    static HWND hwndweekly;
    static HWND hwndmonthly;
    static HWND hwndweekdays;
    static HWND hwnddatetTimer;
    static HWND hwndstart;
    static HWND hwndquickweekdays;
    static HWND hwndquickdatetTimer;
    static HWND hwndstartup;
    static HWND hwnddailydatetTimer;
    static HWND hwndadvancedstart;
    static HWND hwndrandomize;
    static HWND  hwndrandomtime;
    static HWND hwndtextbox10;
    static HWND hwndrandomizeadv;
    static HWND hwndtextbox11;
    static HWND hwndonstart;
    static HWND hwndonstartadv;
    static HWND hwndschedule;
    static HWND  hwndtextbox12;
    //german
    static HWND hwndcombode;
    static HWND hwndtextboxde;
    
    

    string user = getenv("username");
    string domain = getenv("userdomain");
    string userid=domain+"\\"+ user;
  

    TCHAR A[16];
    int k = 0;

    switch (msg)
    {

    case WM_CREATE:

        hwndtextbox = CreateWindow("EDIT", "Options:", WS_CHILD | WS_VISIBLE, 10, 10, 150, 20, hwnd, NULL,  (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
         SendMessage(hwndtextbox,EM_SETREADONLY,TRUE ,NULL);
        hwndtextboxde = CreateWindow("EDIT", "Optionen:", WS_CHILD | WS_VISIBLE, 10, 10, 70, 20, hwnd, NULL,  (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
       ShowWindow(hwndtextbox,SW_HIDE);
       SendMessage(hwndtextbox,EM_SETREADONLY,TRUE ,NULL);

        hwndcombo = CreateWindow("COMBOBOX", NULL, CBS_DROPDOWN | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 10, 40, 150, 150, hwnd, (HMENU)ID_COMBO, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
        hwndcombode = CreateWindow("COMBOBOX", NULL, CBS_DROPDOWN | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 10, 10, 150, 150, hwnd, (HMENU)ID_COMBODE, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

        SendMessage(hwndcombode, CB_ADDSTRING, (WPARAM)0, (LPARAM) "Standardeinstellungen");
        SendMessage(hwndcombode, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM) "Erweitert");
        SendMessage(hwndcombode, CB_SETCURSEL, NULL, (LPARAM) "Standardeinstellungen");
        ShowWindow(hwndcombo,SW_HIDE);
         SendMessage(hwndcombode,EM_SETREADONLY,TRUE ,NULL);
        SendMessage(hwndcombo,EM_SETREADONLY,TRUE ,NULL);

        // Add string to combobox.
        SendMessage(hwndcombo, CB_ADDSTRING, (WPARAM)0, (LPARAM) "Default");
        SendMessage(hwndcombo, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM) "Advanced");
        SendMessage(hwndcombo, CB_SETCURSEL, NULL, (LPARAM) "Default");
        hwndconnection = CreateWindowEx(0, "BUTTON", "Check connection", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BST_CHECKED,
                                        10, 95, 150, 20, hwnd, (HMENU)ID_CHECKBOX, NULL, NULL);

        SendMessage(hwndconnection, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndconnection, FALSE);
        hwndfolder = CreateWindowEx(0, "BUTTON", "Create folder", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                    10, 125, 280, 20, hwnd, (HMENU)ID_FOLDER, NULL, NULL);
        SendMessage(hwndfolder, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndfolder, FALSE);
        hwnddownload = CreateWindowEx(0, "BUTTON", "Download client", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                      10, 155, 130, 20, hwnd, (HMENU)ID_DOWNLOAD, NULL, NULL);
        SendMessage(hwnddownload, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwnddownload, FALSE);
        hwndACL = CreateWindowEx(0, "BUTTON", "Set local folder permission", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                 10, 185, 280, 20, hwnd, (HMENU)ID_ACL, NULL, NULL);
         hwndtextbox12 = CreateWindowEx(0, "EDIT", " C:\\CIS4ITM", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                 210, 185, 280, 20, hwnd, NULL, NULL, NULL);
        EnableWindow(hwndtextbox12,FALSE);
        SendMessage(hwndACL, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndACL, FALSE);
          hwndtextbox7 = CreateWindow("EDIT", "GetUserName(username, &username_len)", WS_CHILD | WS_VISIBLE|WS_BORDER|ES_LEFT , 210, 215, 200, 20, hwnd, (HMENU)21, NULL, NULL);

        SetWindowText(hwndtextbox7, string("User-ID: " + userid).c_str());
        EnableWindow(hwndtextbox7, FALSE);


        hwndtextbox9 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 245, 400, 25, hwnd, NULL, NULL, NULL);

        //  //SetWindowText(hwndtextbox7 ,string("User ID: "+user).c_str());
        ShowWindow(hwndtextbox9, SW_HIDE);

       // hwndtextbox8 = CreateWindow("EDIT", "C:\\CIS4ITM", WS_CHILD | WS_VISIBLE,210,125,150,20, hwnd, NULL, NULL, NULL);
       hwndtextbox8 = CreateWindowEx(0,"EDIT", "C:\\CIS4ITM", WS_CHILD | WS_VISIBLE,210,125,150,20, hwnd, NULL, NULL, NULL);
   

        EnableWindow(hwndtextbox8, FALSE);
        hwndschtask = CreateWindowEx(0, "BUTTON", "Schedule task", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                     10, 245, 130, 20, hwnd, (HMENU)ID_SCHTASK, NULL, NULL);
        SendMessage(hwndschtask, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndschtask, FALSE);

         hwndtextbox10 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 15, 395, 400, 25, hwnd, NULL, NULL, NULL);

        ShowWindow(hwndtextbox10, SW_HIDE);

        hwndquickweekdays = CreateWindow("COMBOBOX", NULL,
                                         CBS_DROPDOWN | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
                                         50, 275, 130, 150, hwnd, (HMENU)ID_QUICKDATE, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

        SendMessage(hwndquickweekdays, CB_ADDSTRING, (WPARAM)0, (LPARAM) "Monday");
        SendMessage(hwndquickweekdays, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM) "Tuesday");
        SendMessage(hwndquickweekdays, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM) "Wednesday");
        SendMessage(hwndquickweekdays, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM) "Thursday");
        SendMessage(hwndquickweekdays, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM) "Friday");
        SendMessage(hwndquickweekdays, CB_SETCURSEL, NULL, (LPARAM) "Weekday");
        hwndquickdatetTimer = CreateWindowEx(0, DATETIMEPICK_CLASS, "DATE TIME ", (WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | DTS_TIMEFORMAT), 195, 275, 130, 30, hwnd, NULL, NULL, NULL);
        DateTime_SetFormat(hwndquickdatetTimer, TEXT("HH:mm"));

        hwndrandomize = CreateWindowEx(0, "BUTTON", "Randomize start +- 10 Min", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                     10, 335, 330, 20, hwnd, (HMENU)ID_RANDOM, NULL, NULL);
        SendMessage(hwndrandomize, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndrandomize, FALSE);

        hwndrandomizeadv = CreateWindowEx(0, "BUTTON", "Randomize start", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                     10, 420, 330, 20, hwnd, (HMENU)ID_RANDOMADV, NULL, NULL);
        SendMessage(hwndrandomizeadv, BM_SETCHECK, BST_CHECKED, 1);
        ShowWindow(hwndrandomizeadv,FALSE);

        hwndrandomtime = CreateWindowEx(0, DATETIMEPICK_CLASS, "10 ", (WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | DTS_TIMEFORMAT), 140, 420, 130, 30, hwnd, NULL, NULL, NULL);
        DateTime_SetFormat(hwndrandomtime, TEXT("mm"));
        ShowWindow(hwndrandomtime,FALSE);

        hwndtextbox11 = CreateWindow("EDIT", "min", WS_CHILD | WS_VISIBLE, 280, 420, 400, 25, hwnd, NULL, NULL, NULL);

        //  //SetWindowText(hwndtextbox7 ,string("User ID: "+user).c_str());
        ShowWindow(hwndtextbox11, SW_HIDE);
        hwndonstart = CreateWindowEx(0, "BUTTON", "At startup", WS_VISIBLE | WS_CHILD |BS_AUTORADIOBUTTON,
                                               30, 305, 330, 20, hwnd, (HMENU)ID_ONSTART, NULL, NULL);
        
        hwndschedule = CreateWindowEx(0, "BUTTON", "", WS_VISIBLE | WS_CHILD |BS_AUTORADIOBUTTON,
                                               30, 275, 20, 20, hwnd, (HMENU)ID_SCHEDULE, NULL, NULL);
        
         SendMessage(hwndschedule, BM_SETCHECK, BST_CHECKED, 1);





        hwndstart = CreateWindowEx(0, "BUTTON", "Start!", WS_VISIBLE | WS_CHILD,
                                  10, 450, 100, 25, hwnd, (HMENU)ID_START, NULL, NULL);



        break;

    case WM_COMMAND:

 if (LOWORD(wParam) == ID_ONSTART)
        {
            ShowWindow(hwndquickweekdays, SW_SHOW);
            ShowWindow(hwndquickdatetTimer, SW_SHOW);
            SendMessage(hwndrandomize, BM_SETCHECK, BST_CHECKED, 1);


            // system("schtasks /create /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /sc onstart /F /RL HIGHEST");
            // ShowWindow(hwndtextbox9, SW_SHOW);
            // SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");

        }

        // UINT checkedstartupdef = SendMessage(hwndonstart, BM_GETCHECK, 0, 0);

        //              if (checkedstartupdef==BST_UNCHECKED)
        // {
        //         SendMessage(hwndrandomize, BM_SETCHECK, BST_CHECKED, 1);
        // }


       


        if (LOWORD(wParam) == ID_START)
        {
         cout<<"Task Creation"<<endl;

            TCHAR strText[255] = {0};
            int idx_row = SendMessage(hwndcombo, CB_GETCURSEL, 0, 0);
            SendMessage(hwndcombo, CB_GETLBTEXT, idx_row, (LPARAM)strText);

            TCHAR strText1[255] = {0};
            int idx_row1 = SendMessage(hwndquickweekdays, CB_GETCURSEL, 0, 0);
            SendMessage(hwndquickweekdays, CB_GETLBTEXT, idx_row1, (LPARAM)strText1);

           
            if (idx_row == 0)
            {
                int connection{ConnectionChecker()};
                if (connection == 0)
                {

                    ShowWindow(hwndtextbox9, SW_SHOW);
                    SetWindowText(hwndtextbox9, "Task scheduling failed");
                    Log(InfoP,"Task scheduling failed","Deployment Toolbox",__LINE__,"main");

                hwndtextbox2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE , 330, 95, 550, 20, hwnd, NULL, NULL, NULL);
                 ShowWindow(hwndtextbox2, SW_SHOW);
                SetWindowText(hwndtextbox2, TEXT("\r\nConnection to CIS server failed"));
                Log(InfoP,"Connection to CIS server failed","Deployment Toolbox",__LINE__,"main");
                  hwndtextbox3 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 125, 530, 20, hwnd, NULL, NULL, NULL);
                ShowWindow(hwndtextbox3, SW_SHOW);
                SetWindowText(hwndtextbox3, TEXT("\r\nSkipped due to failure"));
                Log(InfoP,"Skipped due to failure","Deployment Toolbox",__LINE__,"main");
                hwndtextbox4 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 155, 520, 20, hwnd, NULL, NULL, NULL);
                ShowWindow(hwndtextbox4, SW_SHOW);
                SetWindowText(hwndtextbox4, TEXT("\r\nSkipped due to failure"));
                Log(InfoP,"Skipped due to failure","Deployment Toolbox",__LINE__,"main");
                hwndtextbox5 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 185, 510, 20, hwnd, NULL, NULL, NULL);
                 ShowWindow(hwndtextbox5, SW_SHOW);
                SetWindowText(hwndtextbox5, TEXT("\r\nSkipped due to failure"));
               Log(InfoP,"Skipped due to failure","Deployment Toolbox",__LINE__,"main");
                
                }
                if (connection == 1)
                {
            SYSTEMTIME st{};
            DateTime_GetSystemtime(hwndquickdatetTimer, &st);
            int Random=Randomize();
            SYSTEMTIME s2 = add( st, 60*(Random) );
            cout<<"Time:"<<endl;
             char buffer[256];
            sprintf(buffer,
                    "%02d:%02d",
                    s2.wHour,
                    s2.wMinute);
            std::string strMessage;
            strMessage = buffer;
            cout << strMessage << endl;

                        hwndtextbox2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE , 330, 95, 550, 20, hwnd, NULL, NULL, NULL);

                        SetWindowText(hwndtextbox2, TEXT("\r\nConnection to the CIS server is successful"));
                         Log(InfoP,"Connection to the CIS server is successful ","Deployment Toolbox",__LINE__,"main");
                      const char *dir = "C:\\CIS4ITM\\";
                    struct stat sb;
                    // If the file/directory exists at the path returns 0
                    if (stat(dir, &sb) == 0)
                    {

                        hwndtextbox3 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 125, 530, 20, hwnd, NULL, NULL, NULL);
                        SetWindowText(hwndtextbox3, TEXT("\r\nFolder already exists"));
                             Log(InfoP,"Folder already exists","Deployment Toolbox",__LINE__,"main");
                    }
                    else
                    {
                        // cout << "The folder does not exist\n";

                        hwndtextbox3 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 125, 530, 20, hwnd, NULL, NULL, NULL);
                        SetWindowText(hwndtextbox3, TEXT("\r\nFolder does not exists,creating folder"));
                        Log(InfoP,"Folder does not exists,creating folder","Deployment Toolbox",__LINE__,"main");
                        int check;
                        check = mkdir("C:\\CIS4ITM");

                        // check if directory is created or not
                        if (!check)
                        {
                            hwndtextbox3 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 125, 530, 20, hwnd, NULL, NULL, NULL);
                            SetWindowText(hwndtextbox3, TEXT("\r\nFolder created successfully"));
                            Log(InfoP,"Folder created successfully","Deployment Toolbox",__LINE__,"main");
                        }
                        else
                        {
                            hwndtextbox3 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 125, 530, 20, hwnd, NULL, NULL, NULL);
                            SetWindowText(hwndtextbox3, TEXT("\r\nUnable to create folder"));
                            Log(InfoP,"Unable to create folder","Deployment Toolbox",__LINE__,"main");
                        }
                    }

                  fstream fileStream;
                   fileStream.open("C:\\CIS4ITM\\CIS-Inventory-Start.exe");
                    if (!fileStream.fail())
   
                    {
                        hwndtextbox4 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 155, 520, 20, hwnd, NULL, NULL, NULL);
                        SetWindowText(hwndtextbox4, TEXT("\r\nClient exe already exists"));
                        Log(InfoP,"Client exe already exists","Deployment Toolbox",__LINE__,"main");

                        // SetWindowText(hwndtextbox2, TEXT("\r\nClient exe downloaded successfully"));
                    }
                    else
                    {
                        DownloadFingerprinter();
                        hwndtextbox4 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 155, 520, 20, hwnd, NULL, NULL, NULL);
                        SetWindowText(hwndtextbox4, TEXT("Client exe downloaded successfully"));
                        Log(InfoP,"Client exe downloaded successfully","Deployment Toolbox",__LINE__,"main");
                    }
                    
    int len = GetWindowTextLengthW(GetDlgItem(hwnd, 21)) + 1;
    wchar_t text[len];
    GetWindowTextW(GetDlgItem(hwnd, 21), text, len);
    wstring ws(text);
    string str(ws.begin(), ws.end());
    cout<<str<<endl;
    string split=str.substr(str.find(":") + 1);
   cout<<split<<endl;
                    //system(("net localgroup administrators" +split +" /add").c_str());
                    cout<<"net localgroup administrators" +split +" /add"<<endl;
                    system("icacls C:\\CIS4ITM  /inheritance:d /remove:g *S-1-5-11");
                    system("icacls C:\\CIS4ITM  /inheritance:d /remove:g *S-1-5-11");
                    system("icacls C:\\CIS4ITM  /inheritance:d /remove:g "
                           "Users");

                    // system("for %A IN ("Authenticated Users" "Users" ) do @cacls C:\\CIS4ITM1 /e /c /d %~A:F");

                    hwndtextbox5 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 185, 510, 20, hwnd, NULL, NULL, NULL);
                    SetWindowText(hwndtextbox5, TEXT("\r\nFolder permission set successfully"));
                    Log(InfoP,"Folder permission set successfully","Deployment Toolbox",__LINE__,"main");
UINT checkedstartup = SendMessage(hwndonstart, BM_GETCHECK, 0, 0);
cout<<"check status"<<endl;
                     if (checkedstartup==BST_CHECKED)
        {
            //SendMessage(hwndrandomize, BM_SETCHECK, BST_UNCHECKED, 1);
            ShowWindow(hwndquickweekdays, SW_HIDE);
            ShowWindow(hwndquickdatetTimer, SW_HIDE);
            cout<<"hide"<<endl;
            system("schtasks /create /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /sc onstart /F /RL HIGHEST");
            ShowWindow(hwndtextbox9, SW_SHOW);
            SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");
            Log(InfoP,"CIS4ITM_Package_execute task created successfully","Deployment Toolbox",__LINE__,"main");

        }
        

if(checkedstartup==0){


                    if (idx_row1 == 0)
                    {
                        ShowWindow(hwndquickdatetTimer, SW_SHOW);
                        system(("schtasks /create /sc weekly /D MON /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessage).c_str());
                        ShowWindow(hwndtextbox9, SW_SHOW);
                        SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");
                        Log(InfoP,"CIS4ITM_Package_execute task created successfully","Deployment Toolbox",__LINE__,"main");
                    }
                    if (idx_row1 == 1)
                    {
                        ShowWindow(hwndquickdatetTimer, SW_SHOW);
                        system(("schtasks /create /sc weekly /D TUE /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessage).c_str());
                        ShowWindow(hwndtextbox9, SW_SHOW);
                        SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");
                        Log(InfoP,"CIS4ITM_Package_execute task created successfully","Deployment Toolbox",__LINE__,"main");

                    }
                    if (idx_row1 == 2)
                    {
                        ShowWindow(hwndquickdatetTimer, SW_SHOW);
                        system(("schtasks /create /sc weekly /D WED /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessage).c_str());
                        ShowWindow(hwndtextbox9, SW_SHOW);
                        SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");
                        Log(InfoP,"CIS4ITM_Package_execute task created successfully","Deployment Toolbox",__LINE__,"main");
                    }
                    if (idx_row1 == 3)
                    {
                        ShowWindow(hwndquickdatetTimer, SW_SHOW);
                        system(("schtasks /create /sc weekly /D THU /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessage).c_str());
                        ShowWindow(hwndtextbox9, SW_SHOW);
                        SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");
                        Log(InfoP,"CIS4ITM_Package_execute task created successfully","Deployment Toolbox",__LINE__,"main");
                    }
                    if (idx_row1 == 4)
                    {
                        ShowWindow(hwndquickdatetTimer, SW_SHOW);
                         
                        system(("schtasks /create /sc weekly /D FRI /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessage).c_str());
                        ShowWindow(hwndtextbox9, SW_SHOW);
                        SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");
                         Log(InfoP,"CIS4ITM_Package_execute task created successfully","Deployment Toolbox",__LINE__,"main");
                    }

                      if (idx_row1 == 5)
                    {
                ShowWindow(hwndquickdatetTimer, SW_HIDE);
                system("schtasks /create /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /sc onstart /F /RL HIGHEST");
                ShowWindow(hwndtextbox9, SW_SHOW);
                SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");
                Log(InfoP,"CIS4ITM_Package_execute task created successfully","Deployment Toolbox",__LINE__,"main");
                    }
}

                }

            }
            if (idx_row == 1)
            {
                SendMessage(hwndrandomize, BM_SETCHECK, BST_CHECKED, 1);
                UINT checkedconnection = SendMessage(hwndconnection, BM_GETCHECK, 0, 0);
                UINT checkedfolder = SendMessage(hwndfolder, BM_GETCHECK, 0, 0);
                UINT checkeddownload = SendMessage(hwnddownload, BM_GETCHECK, 0, 0);
                UINT checkedACL = SendMessage(hwndACL, BM_GETCHECK, 0, 0);
                UINT checkedschtask = SendMessage(hwndschtask, BM_GETCHECK, 0, 0);
                int connection{ConnectionChecker()};

                if (connection==1)
                {

                if (checkedconnection == BST_UNCHECKED)
                {
                    ShowWindow(hwndtextbox2, SW_HIDE);
                    EnableWindow(hwnddownload, TRUE);
                }

                if (checkedconnection == BST_CHECKED)
                {
                    // MessageBox(NULL, "Checkbox Selected", "Success", MB_OK | MB_ICONINFORMATION);

                    int connection{ConnectionChecker()};
                    // printf("status: %d\n",connection);
                    cout << "\nstatus:" << connection;
                    if (connection == 1)
                    {
                        hwndtextbox2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE , 330, 95, 550, 20, hwnd, NULL, NULL, NULL);

                        SetWindowText(hwndtextbox2, TEXT("\r\nConnection to the CIS Server is successful"));
                         Log(InfoP,"Connection to the CIS Server is successful","Deployment Toolbox",__LINE__,"main");
                        

                        

                        SetTextColor((HDC)hwndtextbox2, RGB(255, 0, 0));
                    }
                    else
                    {
                        hwndtextbox2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 95, 550, 20, hwnd, NULL, NULL, NULL);
                        SetWindowText(hwndtextbox2, TEXT("\r\nConnection is not successful"));
                               Log(InfoP,"Connection is not successful","Deployment Toolbox",__LINE__,"main");
                        EnableWindow(hwnddownload, FALSE);
                        ShowWindow(hwndtextbox4, SW_HIDE);
                        EnableWindow(hwndfolder, FALSE);
                        ShowWindow(hwndtextbox5, SW_HIDE);
                        EnableWindow(hwndACL, FALSE);
                        ShowWindow(hwndtextbox6, SW_HIDE);
                        EnableWindow(hwndACL, FALSE);
                        ShowWindow(hwndtextbox3, SW_HIDE);
                        EnableWindow(hwndschtask, FALSE);
                        goto label;
                    }
                }

                if (checkedfolder == BST_CHECKED and connection==1)
                {

                    const char *dir = "C:\\CIS4ITM\\";
                    struct stat sb;
                    // If the file/directory exists at the path returns 0
                    if (stat(dir, &sb) == 0)
                    {

                        hwndtextbox3 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 125, 530, 20, hwnd, NULL, NULL, NULL);
                        SetWindowText(hwndtextbox3, TEXT("\r\nFolder already exists"));
                        Log(InfoP,"Folder already exists","Deployment Toolbox",__LINE__,"main");
                    }
                    else
                    {
                        // cout << "The folder does not exist\n";

                        // hwndtextbox3 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 125, 530, 20, hwnd, NULL, NULL, NULL);
                        // SetWindowText(hwndtextbox3, TEXT("\r\nFolder does not exists,creating folder"));
                        int check;
                        check = mkdir("C:\\CIS4ITM");

                        // check if directory is created or not
                        if (!check)
                        {
                            hwndtextbox3 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 125, 530, 20, hwnd, NULL, NULL, NULL);
                            SetWindowText(hwndtextbox3, TEXT("\r\nFolder created successfully"));
                            Log(InfoP,"Folder created successfully","Deployment Toolbox",__LINE__,"main");
                        }
                        else
                        {
                            hwndtextbox3 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 125, 530, 20, hwnd, NULL, NULL, NULL);
                            SetWindowText(hwndtextbox3, TEXT("\r\nUnable to create folder"));
                             Log(InfoP,"Unable to create folder","Deployment Toolbox",__LINE__,"main");
                        }
                    }
                }

                if (checkedfolder == BST_UNCHECKED)
                {
                    ShowWindow(hwndtextbox3, SW_HIDE);
                }

                  const char *dir = "C:\\CIS4ITM\\";
                    struct stat sb;
                    if(checkeddownload == BST_CHECKED and stat(dir, &sb) != 0 ){
                         hwndtextbox4 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 155, 520, 20, hwnd, NULL, NULL, NULL);
                        SetWindowText(hwndtextbox4, TEXT("\r\n Please create CIS4ITM folder"));
                            Log(InfoP,"Please create CIS4ITM folder","Deployment Toolbox",__LINE__,"main");
                        
                    }
                
                if (checkeddownload == BST_CHECKED and stat(dir, &sb) == 0 )
                {

                
                    fstream fileStream;
                   fileStream.open("C:\\CIS4ITM\\CIS-Inventory-Start.exe");
                    if (fileStream.fail())
                    {
                        DownloadFingerprinter();
                        hwndtextbox4 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 155, 520, 20, hwnd, NULL, NULL, NULL);
                        SetWindowText(hwndtextbox4, TEXT("Client exe downloaded successfully"));
                        Log(InfoP,"Client exe downloaded successfully","Deployment Toolbox",__LINE__,"main");

                        // SetWindowText(hwndtextbox2, TEXT("\r\nClient exe downloaded successfully"));
                    }
                    else
                    {
                        
                        hwndtextbox4 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 155, 520, 20, hwnd, NULL, NULL, NULL);
                        SetWindowText(hwndtextbox4, TEXT("\r\nClient exe already exists"));
                                      Log(InfoP,"Client exe already exists","Deployment Toolbox",__LINE__,"main");
                    }
                }

                if (checkeddownload == BST_UNCHECKED)
                {
                    ShowWindow(hwndtextbox4, SW_HIDE);
                }

                  
        
                    
                    if (checkedACL == BST_CHECKED and stat(dir, &sb) != 0 ){
                       hwndtextbox5 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 185, 510, 20, hwnd, NULL, NULL, NULL);
                    SetWindowText(hwndtextbox5, TEXT("\r\nPlease create the CIS4ITM folder before setting the folder permission")); 
                       Log(InfoP,"Please create the CIS4ITM folder before setting the folder permission","Deployment Toolbox",__LINE__,"main");    
                    }
                    fstream fileStream;
                   fileStream.open("C:\\CIS4ITM\\CIS-Inventory-Start.exe");
                     if (checkedACL == BST_CHECKED and fileStream.fail() )
                {
                    hwndtextbox5 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 185, 510, 20, hwnd, NULL, NULL, NULL);
                    SetWindowText(hwndtextbox5, TEXT("\r\nPlease download the client exe before setting the folder permission"));  
                    Log(InfoP,"Please download the client exe before setting the folder permission","Deployment Toolbox",__LINE__,"main");     
                }
                if (checkedACL == BST_CHECKED and !fileStream.fail())
                {
                
                TCHAR uservalue[255] = {0};
            int idx_row10 = SendMessage(hwndtextbox7, WM_GETTEXT, 0, 0);
            SendMessage(hwndtextbox7, WM_GETTEXT, idx_row10, (LPARAM)uservalue);
            cout<<idx_row10<<endl;

               int len = GetWindowTextLengthW(GetDlgItem(hwnd, 21)) + 1;
    wchar_t text[len];
    GetWindowTextW(GetDlgItem(hwnd, 21), text, len);
    wstring ws(text);
    string str(ws.begin(), ws.end());
    cout<<str<<endl;
    string split=str.substr(str.find(":") + 1);
   cout<<split<<endl;
                    system(("net localgroup administrators" +split +" /add").c_str());
                    cout<<"net localgroup administrators" +split +" /add"<<endl;
                   
                    system("icacls C:\\CIS4ITM  /inheritance:d /remove:g *S-1-5-11");
                    system("icacls C:\\CIS4ITM  /inheritance:d /remove:g *S-1-5-11");
                    system("icacls C:\\CIS4ITM  /inheritance:d /remove:g "
                           "Users");

                    // system("for %A IN ("Authenticated Users" "Users" ) do @cacls C:\\CIS4ITM1 /e /c /d %~A:F");

                    hwndtextbox5 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 185, 510, 20, hwnd, NULL, NULL, NULL);
                    SetWindowText(hwndtextbox5, TEXT("\r\nFolder permission set successfully"));
                     Log(InfoP,"Folder permission set successfully","Deployment Toolbox",__LINE__,"main");     
                }
                if (checkedACL == BST_UNCHECKED)
                {
                    ShowWindow(hwndtextbox5, SW_HIDE);
                }

                 if (checkedschtask==BST_CHECKED and fileStream.fail() ){

     ShowWindow(hwndtextbox9, SW_SHOW);
     SetWindowText(hwndtextbox9, "Please download the client exe");
    Log(InfoP,"Please download the client exe","Deployment Toolbox",__LINE__,"main"); 

                  }

                 if(checkedschtask==BST_CHECKED and stat(dir, &sb) != 0)
                 {

                       ShowWindow(hwndtextbox9, SW_SHOW);
                       SetWindowText(hwndtextbox9, "Please create CIS4ITM folder");
                        Log(InfoP,"Please create CIS4ITM folder","Deployment Toolbox",__LINE__,"main"); 

                 }

            if (checkedschtask==BST_CHECKED and !fileStream.fail() and stat(dir, &sb) == 0)
             {

                TCHAR strText2[255] = {0};
            int idx_row2 = SendMessage(hwndweekdays, CB_GETCURSEL, 0, 0);
            SendMessage(hwndweekdays, CB_GETLBTEXT, idx_row2, (LPARAM)strText1);

       SYSTEMTIME sts{};
       SYSTEMTIME randomweekly{};
            DateTime_GetSystemtime(hwnddatetTimer, &sts);
            DateTime_GetSystemtime(hwndrandomtime, &randomweekly);

            SYSTEMTIME stsweekly=add( sts, 60 * (randomweekly.wMinute) );

            char buffers[256];
            sprintf(buffers,
                    "%02d:%02d",
                    stsweekly.wHour,
                    stsweekly.wMinute);
            std::string strMessage1;
            strMessage1 = buffers;
            SYSTEMTIME stdaily{};
            SYSTEMTIME randomdaily{};
            DateTime_GetSystemtime(hwnddailydatetTimer, &stdaily);
             DateTime_GetSystemtime(hwndrandomtime, &randomdaily);
            SYSTEMTIME stsdaily=add( stdaily, 60 * (randomdaily.wMinute) );

            char bufferdaily[256];
            sprintf(bufferdaily,
                    "%02d:%02d",
                    stsdaily.wHour,
                    stsdaily.wMinute);
            std::string strMessagedaily;
            strMessagedaily = bufferdaily;
UINT checkeddaily = SendMessage(hwnddaily, BM_GETCHECK, 0, 0);
UINT checkedweekly = SendMessage(hwndweekly, BM_GETCHECK, 0, 0);
//time_t newTime = strMessagedaily + (60 * 10);

if(checkeddaily==1){
  system(("schtasks /create /sc daily /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessagedaily).c_str());
  ShowWindow(hwndtextbox9, SW_SHOW);
  SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");
   Log(InfoP,"CIS4ITM_Package_execute task created successfully","Deployment Toolbox",__LINE__,"main"); 
}
if(checkedweekly==1){
              if (idx_row2 == 0)
                    {

                        system(("schtasks /create /sc weekly /D MON /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessage1).c_str());
                        ShowWindow(hwndtextbox9, SW_SHOW);
                        SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");
                         Log(InfoP,"CIS4ITM_Package_execute task created successfully","Deployment Toolbox",__LINE__,"main"); 
                    }

                    if (idx_row2 == 1)
                    {

                        system(("schtasks /create /sc weekly /D TUE /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessage1).c_str());
                        ShowWindow(hwndtextbox9, SW_SHOW);
                        SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");
                         Log(InfoP,"CIS4ITM_Package_execute task created successfully","Deployment Toolbox",__LINE__,"main"); 
                    }
                      if (idx_row2 == 2)
                    {

                        system(("schtasks /create /sc weekly /D WED /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessage1).c_str());
                        ShowWindow(hwndtextbox9, SW_SHOW);
                        SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");
                         Log(InfoP,"CIS4ITM_Package_execute task created successfully","Deployment Toolbox",__LINE__,"main"); 
                    }
                       if (idx_row2 == 3)
                    {

                        system(("schtasks /create /sc weekly /D THU /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessage1).c_str());
                        ShowWindow(hwndtextbox9, SW_SHOW);
                        SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");
                         Log(InfoP,"CIS4ITM_Package_execute task created successfully","Deployment Toolbox",__LINE__,"main"); 
                    }
                         if (idx_row2 == 4)
                    {

                        system(("schtasks /create /sc weekly /D FRI /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessage1).c_str());
                        ShowWindow(hwndtextbox9, SW_SHOW);
                        SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");
                         Log(InfoP,"CIS4ITM_Package_execute task created successfully","Deployment Toolbox",__LINE__,"main"); 
                    }
                     
}
UINT checkedstartupadv = SendMessage(hwndonstartadv, BM_GETCHECK, 0, 0);
if (checkedstartupadv==BST_CHECKED){
                  ShowWindow(hwnddatetTimer, SW_HIDE);
                  EnableWindow(hwndrandomizeadv,FALSE);
                  EnableWindow(hwndrandomtime,FALSE);
                  ShowWindow(hwndrandomtime,SW_HIDE);
            ShowWindow(hwnddailydatetTimer, SW_HIDE);
             ShowWindow(hwndweekdays, SW_HIDE);
             system("schtasks /create /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /sc onstart /F /RL HIGHEST");
            ShowWindow(hwndtextbox9, SW_SHOW);
            SetWindowText(hwndtextbox9, "CIS4ITM_Package_execute task created successfully");
             Log(InfoP,"CIS4ITM_Package_execute task created successfully","Deployment Toolbox",__LINE__,"main"); 
       
}
                }

                 
            //      if (checkedschtask==BST_UNCHECKED)
            //     {
            //         ShowWindow(hwnddaily, SW_HIDE);
            //         ShowWindow(hwndweekly, SW_HIDE);
            //         ShowWindow(hwndmonthly, SW_HIDE);
            //         ShowWindow(hwnddatetTimer, SW_HIDE);
            //         ShowWindow(hwndweekdays, SW_HIDE);
            //         ShowWindow(hwnddailydatetTimer, SW_HIDE);
            //     }
         

            }

            if(connection==0){
                ShowWindow(hwndtextbox9, SW_SHOW);
                SetWindowText(hwndtextbox9, "Task scheduling failed");
                 Log(InfoP,"Task scheduling failed","Deployment Toolbox",__LINE__,"main"); 
                hwndtextbox2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE , 330, 95, 550, 20, hwnd, NULL, NULL, NULL);
                ShowWindow(hwndtextbox2, SW_SHOW);
                SetWindowText(hwndtextbox2, TEXT("\r\nConnection to the CIS Server failed!"));
                Log(InfoP,"Connection to the CIS Server failed!","Deployment Toolbox",__LINE__,"main"); 
                hwndtextbox3 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 125, 530, 20, hwnd, NULL, NULL, NULL);
                ShowWindow(hwndtextbox3, SW_SHOW);
                SetWindowText(hwndtextbox3, TEXT("\r\nSkipped due to failure"));
                Log(InfoP,"Skipped due to failure","Deployment Toolbox",__LINE__,"main"); 
                hwndtextbox4 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 155, 520, 20, hwnd, NULL, NULL, NULL);
                ShowWindow(hwndtextbox4, SW_SHOW);
                SetWindowText(hwndtextbox4, TEXT("\r\nSkipped due to failure"));
                Log(InfoP,"Skipped due to failure","Deployment Toolbox",__LINE__,"main"); 
                hwndtextbox5 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 330, 185, 510, 20, hwnd, NULL, NULL, NULL);
                 ShowWindow(hwndtextbox5, SW_SHOW);
                SetWindowText(hwndtextbox5, TEXT("\r\nSkipped due to failure"));
                Log(InfoP,"Skipped due to failure","Deployment Toolbox",__LINE__,"main"); 
                

            }
        label:
            break;
            }
        }

        
    

        if (LOWORD(wParam) == ID_SCHTASK)
        {
         cout<<"start the task creation"<<endl;
            switch (HIWORD(wParam))
            {
            case BN_CLICKED:
                if (SendDlgItemMessage(hwnd, ID_SCHTASK, BM_GETCHECK, 0, 0))
                {
                    hwnddaily = CreateWindowEx(0, "BUTTON", "Daily", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                               10, 275, 130, 20, hwnd, (HMENU)ID_DAILY, NULL, NULL);
                    hwndweekly = CreateWindowEx(0, "BUTTON", "Weekly", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                                10, 305, 130, 20, hwnd, (HMENU)ID_WEEKLY, NULL, NULL);
                    hwndmonthly = CreateWindowEx(0, "BUTTON", "Monthly", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                                 10, 335, 130, 20, hwnd, (HMENU)ID_MONTHLY, NULL, NULL);

                    hwndonstartadv = CreateWindowEx(0, "BUTTON", "At Startup", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                                 10, 365, 130, 20, hwnd, (HMENU)ID_STARTUPADV, NULL, NULL);


                }
                else
                {
                    ShowWindow(hwnddaily, SW_HIDE);
                    ShowWindow(hwndweekly, SW_HIDE);
                    ShowWindow(hwndmonthly, SW_HIDE);
                    ShowWindow(hwndonstartadv, SW_HIDE);
                    ShowWindow(hwnddatetTimer, SW_HIDE);
                    ShowWindow(hwndweekdays, SW_HIDE);
                    ShowWindow(hwnddailydatetTimer, SW_HIDE);
                }
            }
        }


        if (LOWORD(wParam) == ID_DAILY)
        {
            SendMessage(hwndrandomizeadv, BM_SETCHECK, BST_CHECKED, 1);
            EnableWindow(hwndrandomtime,TRUE);
            EnableWindow(hwndtextbox11,TRUE);
            ShowWindow(hwnddatetTimer, SW_HIDE);
            ShowWindow(hwndweekdays, SW_HIDE);

            hwnddailydatetTimer = CreateWindowEx(                                                //
                /* Extended Style   */ 0,                                                        //
                /* Class Name       */ DATETIMEPICK_CLASS,                                       //
                /* Element Name     */ "DATE TIME ",                                             //
                /* Style            */ (WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | DTS_TIMEFORMAT), //
                /* X Position       */ 150,                                                      //
                /* Y Position       */ 275,                                                      //
                /* Width            */ 130,                                                      //
                /* Height           */ 30,                                                       //
                /* Parent Window    */ hwnd,                                                     //
                /* Menu             */ NULL,                                                     //
                /* Instance         */ NULL,                                                     //
                /* Parameter        */ NULL);
            DateTime_SetFormat(hwnddailydatetTimer, TEXT("HH:mm"));
        }

        if (LOWORD(wParam) == ID_WEEKLY)
        {
            SendMessage(hwndrandomizeadv, BM_SETCHECK, BST_CHECKED, 1);
            EnableWindow(hwndrandomtime,TRUE);
            EnableWindow(hwndtextbox11,TRUE);
            ShowWindow(hwnddailydatetTimer, SW_HIDE);
            hwndweekdays = CreateWindow("COMBOBOX", NULL,
                                        CBS_DROPDOWN | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
                                        150, 305, 130, 150, hwnd, (HMENU)ID_WEEKDAYS, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

            SendMessage(hwndweekdays, CB_ADDSTRING, (WPARAM)0, (LPARAM) "Monday");
            SendMessage(hwndweekdays, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM) "Tuesday");
            SendMessage(hwndweekdays, (UINT)CB_ADDSTRING, (WPARAM)2, (LPARAM) "Wednesday");
            SendMessage(hwndweekdays, (UINT)CB_ADDSTRING, (WPARAM)3, (LPARAM) "Thursday");
            SendMessage(hwndweekdays, (UINT)CB_ADDSTRING, (WPARAM)4, (LPARAM) "Friday");
            SendMessage(hwndweekdays, CB_SETCURSEL, NULL, (LPARAM) "Monday");
            hwnddatetTimer = CreateWindowEx(                                                     //
                /* Extended Style   */ 0,                                                        //
                /* Class Name       */ DATETIMEPICK_CLASS,                                       //
                /* Element Name     */ "DATE TIME ",                                             //
                /* Style            */ (WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | DTS_TIMEFORMAT), //
                /* X Position       */ 300,                                                      //
                /* Y Position       */ 305,                                                      //
                /* Width            */ 130,                                                      //
                /* Height           */ 30,                                                       //
                /* Parent Window    */ hwnd,                                                     //
                /* Menu             */ NULL,                                                     //
                /* Instance         */ NULL,                                                     //
                /* Parameter        */ NULL);
            DateTime_SetFormat(hwnddatetTimer, TEXT("HH:mm"));
        }

        if (LOWORD(wParam) == ID_MONTHLY)
        {
            ShowWindow(hwnddatetTimer, SW_HIDE);
            ShowWindow(hwndweekdays, SW_HIDE);
            ShowWindow(hwnddailydatetTimer, SW_HIDE);
             ShowWindow(hwnddailydatetTimer, SW_HIDE);
              ShowWindow(hwnddatetTimer, SW_HIDE);
             ShowWindow(hwndweekdays, SW_HIDE);
               EnableWindow(hwndrandomtime,TRUE);
            EnableWindow(hwndtextbox11,TRUE);
             SendMessage(hwndrandomizeadv, BM_SETCHECK, BST_CHECKED, 1);
        }
       

         if (LOWORD(wParam) == ID_STARTUPADV)
        {
            ShowWindow(hwnddatetTimer, SW_HIDE);
            ShowWindow(hwndweekdays, SW_HIDE);
            ShowWindow(hwnddailydatetTimer, SW_HIDE);
             ShowWindow(hwnddailydatetTimer, SW_HIDE);
              ShowWindow(hwnddatetTimer, SW_HIDE);
             ShowWindow(hwndweekdays, SW_HIDE);
            EnableWindow(hwndrandomtime,FALSE);
            EnableWindow(hwndrandomtime,FALSE);
            EnableWindow(hwndtextbox11,FALSE);
             SendMessage(hwndrandomizeadv, BM_SETCHECK, BST_UNCHECKED, 1);
        }
       
        switch (LOWORD(wParam))

        {
        case ID_COMBO:

        {

            TCHAR strText[255] = {0};
            int idx_row = SendMessage(hwndcombo, CB_GETCURSEL, 0, 0);
            SendMessage(hwndcombo, CB_GETLBTEXT, idx_row, (LPARAM)strText);

            // switch(HIWORD(wParam))
            switch (idx_row)

            {

            case 0:
            {
                  
                EnableWindow(hwndconnection, FALSE);
                SendMessage(hwndconnection, BM_SETCHECK, BST_CHECKED, 1);
                EnableWindow(hwndfolder, FALSE);
                SendMessage(hwndfolder, BM_SETCHECK, BST_CHECKED, 1);
                EnableWindow(hwnddownload, FALSE);
                SendMessage(hwnddownload, BM_SETCHECK, BST_CHECKED, 1);
                EnableWindow(hwndACL, FALSE);
                SendMessage(hwndACL, BM_SETCHECK, BST_CHECKED, 1);
                EnableWindow(hwndschtask, FALSE);
                SendMessage(hwndschtask, BM_SETCHECK, BST_CHECKED, 1);
                ShowWindow(hwndquickdatetTimer, SW_SHOW);
                ShowWindow(hwndstartup, SW_SHOW);
                ShowWindow(hwndquickweekdays, SW_SHOW);
                EnableWindow(hwndtextbox7, FALSE);
                EnableWindow(hwndtextbox8, FALSE);
                ShowWindow(hwnddaily, SW_HIDE);
                ShowWindow(hwndweekly, SW_HIDE);
                ShowWindow(hwndmonthly, SW_HIDE);
                ShowWindow(hwndweekdays, SW_HIDE);
                ShowWindow(hwnddailydatetTimer, SW_HIDE);
                ShowWindow(hwnddatetTimer, SW_HIDE);
                ShowWindow(hwnddatetTimer, SW_HIDE);
                ShowWindow(hwndtextbox2, SW_HIDE);
                ShowWindow(hwndtextbox3, SW_HIDE);
                ShowWindow(hwndtextbox4, SW_HIDE);
                ShowWindow(hwndtextbox5, SW_HIDE);
                ShowWindow(hwndtextbox6, SW_HIDE);
                 ShowWindow(hwndrandomize, SW_SHOW);
                SendMessage(hwndrandomize, BM_SETCHECK, BST_CHECKED, 1);
                EnableWindow(hwndrandomize, FALSE);
                ShowWindow(hwndtextbox10, SW_HIDE);
                ShowWindow(hwndrandomizeadv, SW_HIDE);
                 ShowWindow(hwndrandomtime, SW_HIDE);
                ShowWindow(hwndtextbox11, SW_HIDE);
                 ShowWindow(hwndonstart,SW_SHOW);
                  ShowWindow(hwndonstartadv,SW_HIDE);
                  ShowWindow(hwndschedule,SW_SHOW);
                 SendMessage(hwndschedule, BM_SETCHECK, BST_CHECKED, 1);
                SendMessage(hwndonstart, BM_SETCHECK, BST_UNCHECKED, 1);
                 EnableWindow(hwndtextbox12,FALSE);
               
        
                // ShowWindow(hwndtextbox7,SW_HIDE);
                //  ShowWindow(hwndtextbox8,SW_HIDE);

                break;
            }

            case 1:
            {

      
                EnableWindow(hwndconnection, TRUE);
                SendMessage(hwndconnection, BM_SETCHECK, BST_UNCHECKED, 1);
                EnableWindow(hwndfolder, TRUE);
                SendMessage(hwndfolder, BM_SETCHECK, BST_UNCHECKED, 1);
                EnableWindow(hwnddownload, TRUE);
                SendMessage(hwnddownload, BM_SETCHECK, BST_UNCHECKED, 1);
                EnableWindow(hwndACL, TRUE);
                SendMessage(hwndACL, BM_SETCHECK, BST_UNCHECKED, 1);
                EnableWindow(hwndschtask, TRUE);
                SendMessage(hwndschtask, BM_SETCHECK, BST_UNCHECKED, 1);
                ShowWindow(hwndquickdatetTimer, SW_HIDE);
                ShowWindow(hwndstartup, SW_HIDE);
                ShowWindow(hwndquickweekdays, SW_HIDE);
                EnableWindow(hwndtextbox7, TRUE);
                EnableWindow(hwndtextbox8, TRUE);
                ShowWindow(hwndtextbox9, SW_HIDE);
                ShowWindow(hwndrandomize, FALSE);
                ShowWindow(hwndtextbox10, SW_SHOW);
                EnableWindow(hwndtextbox10, FALSE);
                ShowWindow(hwndrandomizeadv,TRUE);
                EnableWindow(hwndrandomizeadv,FALSE);
                SendMessage(hwndrandomizeadv, BM_SETCHECK, BST_CHECKED, 1);
                ShowWindow(hwndrandomtime, SW_SHOW);
                EnableWindow(hwndrandomtime, TRUE);
                ShowWindow(hwndtextbox11, SW_SHOW);
                ShowWindow(hwndonstart,SW_HIDE);
                ShowWindow(hwndschedule,SW_HIDE);
                  EnableWindow(hwndtextbox12,TRUE);
                
               
           

                break;
            }

                // Handle notification code

                // //      default:  { EnableWindow(hwndconnection , TRUE);
                //             EnableWindow(hwndfolder ,  TRUE);
                //              EnableWindow(hwnddownload ,  TRUE);
                //               EnableWindow(hwndACL ,  TRUE);

                //    }
            }
        }
        break;
        }

        break;

    case WM_DESTROY:

        PostQuitMessage(0);
        break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}
