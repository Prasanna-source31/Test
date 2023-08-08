#include <windows.h>
#include <Lmcons.h>
#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include "Dep/Services.h"
#include "Dep/Configurations.h"
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
#define ID_TOOLTIP 23
#define ID_CALENDER 24
#define ID_SHOWLOG 25
// german
#define ID_COMBODE 30
#define ID_COMBOlangde 31
#define ID_CHECKBOXDE 32
#define ID_FOLDERDE 33
#define ID_DOWNLOADDE 34
#define ID_ACLDE 35
#define ID_SCHTASKDE 36
#define ID_RANDOMDE 37
#define ID_RANDOMADVDE 38
#define ID_QUICKDATEDE 39
#define ID_ONSTARTDE 40
#define ID_DAILYDE 41
#define ID_WEEKLYDE 42
#define ID_MONTHLYDE 43
#define ID_STARTUPADVDE 44

SYSTEMTIME add(SYSTEMTIME s, double seconds)
{

    FILETIME f;
    SystemTimeToFileTime(&s, &f);

    ULARGE_INTEGER u;
    memcpy(&u, &f, sizeof(u));

    const double c_dSecondsPer100nsInterval = 100. * 1.e-9;
    const double c_dNumberOf100nsIntervals =
        seconds / c_dSecondsPer100nsInterval;

    // note: you may want to round the number of intervals.
    u.QuadPart += c_dNumberOf100nsIntervals;

    memcpy(&f, &u, sizeof(f));

    FileTimeToSystemTime(&f, &s);
    return s;
}
int Randomize(int mins)
{
    int min = -(mins);
    int max = mins;
    static bool first = true;
    if (first)
    {
        srand(time(NULL));
        first = false;
    }
    int randNum = rand() % (max - min + 1) + min;
}
HWND CreateToolTip(int toolID, HWND hDlg, PTSTR pszText)
{
    if (!toolID || !hDlg || !pszText)
    {
        return FALSE;
    }
    // Get the window of the tool.
    HWND hwndTool = GetDlgItem(hDlg, toolID);

    // Create the tooltip. g_hInst is the global instance handle.
    HWND hwndTip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,
                                  WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
                                  CW_USEDEFAULT, CW_USEDEFAULT,
                                  CW_USEDEFAULT, CW_USEDEFAULT,
                                  hDlg, NULL,
                                  (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), NULL);

    if (!hwndTool || !hwndTip)
    {
        return (HWND)NULL;
    }

    // Associate the tooltip with the tool.
    TOOLINFO toolInfo = {0};
    toolInfo.cbSize = sizeof(toolInfo);
    toolInfo.hwnd = hDlg;
    toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
    toolInfo.uId = (UINT_PTR)hwndTool;
    toolInfo.lpszText = pszText;
    SendMessage(hwndTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);

    return hwndTip;
}
// Tooltip end

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance,
         PWSTR lpCmdLine, int nCmdShow)
{
    // ShowWindow(::GetConsoleWindow(), SW_HIDE);
    Logger();
    MSG msg;
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"CIS4ITM Deployment-toolbox";
    wc.hInstance = hInstance;
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
// start
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
                         WPARAM wParam, LPARAM lParam)
{
    // English
    static HWND hwndcombo;
    static HWND hwndtextbox;
    static HWND hwndconnection;
    static HWND hwndfolder;
    static HWND hwnddownload;
    static HWND hwndACL;
    static HWND hwndtextbox7;
    static HWND hwndtextbox8;
    static HWND hwndtextbox9;
    static HWND hwndschtask;
    static HWND hwndtextbox10;
    static HWND hwndquickweekdays;
    static HWND hwndquickdatetTimer;
    static HWND hwndrandomize;
    static HWND hwndrandomizeadv;
    static HWND hwndrandomtime;
    static HWND hwndonstart;
    static HWND hwndschedule;
    static HWND hwndstart;
    static HWND hwndtextbox15;
    static HWND hwndtextbox2;
    static HWND hwndtextbox3;
    static HWND hwndtextbox4;
    static HWND hwndtextbox5;
    static HWND hwndonstartadv;
    static HWND hwnddaily;
    static HWND hwndmonthly;
    static HWND hwndweekly;
    static HWND hwnddatetTimer;
    static HWND hwnddailydatetTimer;
    static HWND hwndmonthlydatetTimer;
    static HWND hwndweekdays;
    static HWND hwndtextbox6;
    static HWND hwndcalender;
    static HWND hwndshowlog;

    string user = getenv("username");
    string domain = getenv("userdomain");
    string userid = domain + "\\" + user;

    // german
    static HWND hwndtextboxde;
    static HWND hwndlangde;
    static HWND hwndcombode;
    static HWND hwndconnectionde;
    static HWND hwndfolderde;
    static HWND hwnddownloadde;
    static HWND hwndACLde;
    static HWND hwndschtaskde;
    static HWND hwndquickweekdaysde;
    static HWND hwndrandomizede;
    static HWND hwndrandomizeadvde;
    static HWND hwndrandomtimede;
    static HWND hwndonstartde;
    static HWND hwnddailyde;
    static HWND hwndweeklyde;
    static HWND hwndmonthlyde;
    static HWND hwndonstartadvde;
    string first = "5. Ausf";
    string last = "hrung planen";
    char ascii = char(252);
    string schedulede = first + ascii + last;
    switch (msg)
    {
    case WM_CREATE:
    {
        // english
        hwndtextbox = CreateWindow("EDIT", (Configurations::option).c_str(), WS_CHILD | WS_VISIBLE, 10, 10, 70, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        SendMessage(hwndtextbox, EM_SETREADONLY, TRUE, NULL);
        hwndcombo = CreateWindow("COMBOBOX", NULL, CBS_DROPDOWN | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 260, 10, 180, 150, hwnd, (HMENU)ID_COMBO, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
        CreateToolTip(ID_COMBO, hwnd, LPTSTR((LPCTSTR) "Advanced and default options can be used to create scheduled task."));
        SendMessage(hwndcombo, EM_SETREADONLY, TRUE, NULL);
        SendMessage(hwndcombo, CB_ADDSTRING, (WPARAM)0, (LPARAM)(Configurations::defaulten).c_str());
        SendMessage(hwndcombo, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM)(Configurations::advanced).c_str());
        SendMessage(hwndcombo, CB_SETCURSEL, NULL, (LPARAM)(Configurations::defaulten).c_str());
        ShowWindow(hwndcombo, SW_HIDE);
        SendMessage(hwndcombo, EM_SETREADONLY, TRUE, NULL);
        hwndconnection = CreateWindowEx(0, "BUTTON", (Configurations::connection).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BST_CHECKED,
                                        10, 55, 150, 20, hwnd, (HMENU)ID_CHECKBOX, NULL, NULL);
        CreateToolTip(ID_CHECKBOX, hwnd, LPTSTR((LPCTSTR) "Connection check with CIS server will be performed."));
        ShowWindow(hwndconnection, SW_HIDE);
        SendMessage(hwndconnection, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndconnection, FALSE);
        hwndfolder = CreateWindowEx(0, "BUTTON", (Configurations::folder).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                    10, 85, 180, 20, hwnd, (HMENU)ID_FOLDER, NULL, NULL);
        SendMessage(hwndfolder, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndfolder, FALSE);

        ShowWindow(hwndfolder, SW_HIDE);
        hwnddownload = CreateWindowEx(0, "BUTTON", (Configurations::download).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                      10, 115, 150, 20, hwnd, (HMENU)ID_DOWNLOAD, NULL, NULL);
        SendMessage(hwnddownload, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwnddownload, FALSE);
        ShowWindow(hwnddownload, SW_HIDE);
        hwndACL = CreateWindowEx(0, "BUTTON", (Configurations::ACL).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                 10, 145, 280, 20, hwnd, (HMENU)ID_ACL, NULL, NULL);

        ShowWindow(hwndACL, SW_HIDE);
        SendMessage(hwndACL, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndACL, FALSE);
        hwndtextbox7 = CreateWindow("EDIT", "GetUserName(username, &username_len)", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 330, 170, 200, 20, hwnd, (HMENU)21, NULL, NULL);

        SetWindowText(hwndtextbox7, string("User-ID: " + userid).c_str());
        EnableWindow(hwndtextbox7, FALSE);

        hwndtextbox9 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 550, 190, 400, 25, hwnd, NULL, NULL, NULL);
        ShowWindow(hwndtextbox9, SW_HIDE);
        hwndtextbox8 = CreateWindow("EDIT", "C:\\CIS4ITM", WS_CHILD | WS_VISIBLE, 330, 85, 150, 20, hwnd, NULL, NULL, NULL);
        ShowWindow(hwndtextbox8, SW_SHOW);
        EnableWindow(hwndtextbox8, FALSE);
        hwndschtask = CreateWindowEx(0, "BUTTON", (Configurations::schedule).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                     10, 190, 160, 20, hwnd, (HMENU)ID_SCHTASK, NULL, NULL);
        SendMessage(hwndschtask, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndschtask, FALSE);
        ShowWindow(hwndschtask, SW_HIDE);
        hwndtextbox10 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 15, 395, 400, 25, hwnd, NULL, NULL, NULL);
        ShowWindow(hwndtextbox10, SW_HIDE);
        hwndquickweekdays = CreateWindow("COMBOBOX", NULL,
                                         CBS_DROPDOWN | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
                                         50, 225, 130, 150, hwnd, (HMENU)ID_QUICKDATE, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
        // Add options to weekdays
        SendMessage(hwndquickweekdays, CB_ADDSTRING, (WPARAM)0, (LPARAM)(Configurations::weekday1).c_str());
        SendMessage(hwndquickweekdays, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM)(Configurations::weekday2).c_str());
        SendMessage(hwndquickweekdays, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM)(Configurations::weekday3).c_str());
        SendMessage(hwndquickweekdays, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM)(Configurations::weekday4).c_str());
        SendMessage(hwndquickweekdays, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM)(Configurations::weekday5).c_str());
        SendMessage(hwndquickweekdays, CB_SETCURSEL, NULL, (LPARAM) "Weekday");
        ShowWindow(hwndquickweekdays, SW_HIDE);
        hwndquickdatetTimer = CreateWindowEx(0, DATETIMEPICK_CLASS, "DATE TIME ", (WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | DTS_TIMEFORMAT), 195, 225, 130, 30, hwnd, NULL, NULL, NULL);
        DateTime_SetFormat(hwndquickdatetTimer, TEXT("HH:mm"));
        // hwndrandomize = CreateWindowEx(0, "BUTTON", (Configurations::randomize).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
        //  30, 295, 330, 20, hwnd, (HMENU)ID_RANDOM, NULL, NULL);
        hwndrandomize = CreateWindow("EDIT", (Configurations::randomize).c_str(), WS_CHILD | WS_VISIBLE, 30, 295, 330, 20, hwnd, (HMENU)ID_RANDOM, NULL, NULL);
        SendMessage(hwndrandomize, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndrandomize, FALSE);
        ShowWindow(hwndrandomize, SW_HIDE);

        hwndrandomizeadv = CreateWindow("EDIT", (Configurations::randomizeadv).c_str(), WS_VISIBLE | WS_CHILD,
                                        10, 290, 150, 20, hwnd, (HMENU)ID_RANDOMADV, NULL, NULL);
        // EnableWindow(hwndrandomizeadv, FALSE);
        ShowWindow(hwndrandomizeadv, SW_HIDE);
        hwndrandomtime = CreateWindowEx(0, DATETIMEPICK_CLASS, "10 ", (WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | DTS_TIMEFORMAT), 170, 290, 130, 30, hwnd, NULL, NULL, NULL);
        //SetWindowText(hwndrandomtime, TEXT("15"));
       
        DateTime_SetFormat(hwndrandomtime, TEXT("mm"));
        SendMessage(hwndrandomtime, EM_SETSEL, 0, -1);
        //  DateTime_SetSystemtime(hwndrandomtime,"15","15");
        //DateTime_SetRange(hwndrandomtime,00,60);
        
        ShowWindow(hwndrandomtime, FALSE);

        hwndtextbox15 = CreateWindow("EDIT", "C:\\CIS4ITM", WS_CHILD | WS_VISIBLE, 330, 145, 100, 20, hwnd, NULL, NULL, NULL);
        EnableWindow(hwndtextbox15, FALSE);
        hwndonstart = CreateWindowEx(0, "BUTTON", (Configurations::onstart).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                     30, 265, 330, 20, hwnd, (HMENU)ID_ONSTART, NULL, NULL);
        ShowWindow(hwndonstart, SW_HIDE);
        hwndschedule = CreateWindowEx(0, "BUTTON", "", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                      30, 225, 20, 20, hwnd, (HMENU)ID_SCHEDULE, NULL, NULL);

        SendMessage(hwndschedule, BM_SETCHECK, BST_CHECKED, 1);

        hwndstart = CreateWindowEx(0, "BUTTON", (Configurations::start).c_str(), WS_VISIBLE | WS_CHILD,
                                   10, 325, 100, 25, hwnd, (HMENU)ID_START, NULL, NULL);
        hwndshowlog = CreateWindowEx(0, "BUTTON", (Configurations::showlog).c_str(), WS_VISIBLE | WS_CHILD,
                                     150, 325, 100, 25, hwnd, (HMENU)ID_SHOWLOG, NULL, NULL);
        hwndtextbox2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 550, 55, 550, 20, hwnd, NULL, NULL, NULL);
        hwndtextbox3 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 550, 85, 530, 20, hwnd, NULL, NULL, NULL);
        hwndtextbox4 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 550, 115, 520, 20, hwnd, NULL, NULL, NULL);
        hwndtextbox5 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 550, 145, 510, 20, hwnd, NULL, NULL, NULL);

        // ShowWindow(hwndstart, SW_HIDE);

        // German
        hwndtextboxde = CreateWindow("EDIT", (Configurations::optionde).c_str(), WS_CHILD | WS_VISIBLE, 10, 10, 70, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        ShowWindow(hwndtextbox, SW_HIDE);
        SendMessage(hwndtextboxde, EM_SETREADONLY, TRUE, NULL);
        hwndlangde = CreateWindow("COMBOBOX", NULL, CBS_DROPDOWN | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 90, 10, 150, 150, hwnd, (HMENU)ID_COMBOlangde, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
        hwndconnectionde = CreateWindowEx(0, "BUTTON", (Configurations::connectionde).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BST_CHECKED,
                                          10, 55, 170, 20, hwnd, (HMENU)ID_CHECKBOXDE, NULL, NULL);
        SendMessage(hwndconnectionde, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndconnectionde, FALSE);
        hwndfolderde = CreateWindowEx(0, "BUTTON", (Configurations::folderde).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                      10, 85, 280, 20, hwnd, (HMENU)ID_FOLDERDE, NULL, NULL);
        SendMessage(hwndfolderde, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndfolderde, FALSE);
        hwnddownloadde = CreateWindowEx(0, "BUTTON", (Configurations::downloadde).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                        10, 115, 180, 20, hwnd, (HMENU)ID_DOWNLOADDE, NULL, NULL);
        SendMessage(hwnddownloadde, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwnddownloadde, FALSE);
        hwndACLde = CreateWindowEx(0, "BUTTON", (Configurations::ACLde).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                   10, 145, 320, 20, hwnd, (HMENU)ID_ACLDE, NULL, NULL);

        SendMessage(hwndACLde, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndACLde, FALSE);
        hwndschtaskde = CreateWindowEx(0, "BUTTON", string(schedulede).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                       10, 190, 160, 20, hwnd, (HMENU)ID_SCHTASKDE, NULL, NULL);
        SendMessage(hwndschtaskde, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndschtaskde, FALSE);
        // hwndrandomizede = CreateWindowEx(0, "BUTTON", (Configurations::randomizede).c_str(), WS_VISIBLE | WS_CHILD|BS_AUTOCHECKBOX,
        // 30, 295, 450, 20, hwnd, (HMENU)ID_RANDOMDE, NULL, NULL);
        hwndrandomizede = CreateWindow("EDIT", (Configurations::randomizede).c_str(), WS_CHILD | WS_VISIBLE, 30, 295, 450, 20, hwnd, (HMENU)ID_RANDOMDE, NULL, NULL);
        SendMessage(hwndrandomizede, BM_SETCHECK, BST_CHECKED, 1);
        EnableWindow(hwndrandomizede, FALSE);
        hwndrandomizeadvde = CreateWindow("EDIT", (Configurations::randomizeadvde).c_str(), WS_VISIBLE | WS_CHILD,
                                          10, 290, 305, 20, hwnd, (HMENU)ID_RANDOMADVDE, NULL, NULL);
        // EnableWindow(hwndrandomizeadvde, FALSE);
        ShowWindow(hwndrandomizeadvde, SW_HIDE);

        hwndrandomtimede = CreateWindowEx(0, DATETIMEPICK_CLASS, "10 ", (WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | DTS_TIMEFORMAT), 320, 290, 130, 30, hwnd, NULL, NULL, NULL);
        DateTime_SetFormat(hwndrandomtimede, TEXT("mm"));
        ShowWindow(hwndrandomtimede, FALSE);
        hwndonstartde = CreateWindowEx(0, "BUTTON", (Configurations::onstartde).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                       30, 265, 330, 20, hwnd, (HMENU)ID_ONSTARTDE, NULL, NULL);
        // Add values to weekdays dropdown
        hwndquickweekdaysde = CreateWindow("COMBOBOX", NULL,
                                           CBS_DROPDOWN | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
                                           50, 225, 130, 150, hwnd, (HMENU)ID_QUICKDATEDE, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

        SendMessage(hwndquickweekdaysde, CB_ADDSTRING, (WPARAM)0, (LPARAM)(Configurations::weekdayde1).c_str());
        SendMessage(hwndquickweekdaysde, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM)(Configurations::weekdayde2).c_str());
        SendMessage(hwndquickweekdaysde, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM)(Configurations::weekdayde3).c_str());
        SendMessage(hwndquickweekdaysde, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM)(Configurations::weekdayde4).c_str());
        SendMessage(hwndquickweekdaysde, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM)(Configurations::weekdayde5).c_str());
        SendMessage(hwndquickweekdaysde, CB_SETCURSEL, NULL, (LPARAM) "Weekday");

        // Add Values to language dropdown
        SendMessage(hwndlangde, CB_ADDSTRING, (WPARAM)0, (LPARAM)(Configurations::german).c_str());
        SendMessage(hwndlangde, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM)(Configurations::english).c_str());
        SendMessage(hwndlangde, CB_SETCURSEL, NULL, (LPARAM)(Configurations::german).c_str());
        hwndcombode = CreateWindow("COMBOBOX", NULL, CBS_DROPDOWN | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 260, 10, 180, 150, hwnd, (HMENU)ID_COMBODE, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
        SendMessage(hwndcombode, CB_ADDSTRING, (WPARAM)0, (LPARAM)(Configurations::defaultde).c_str());
        SendMessage(hwndcombode, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM)(Configurations::advancedde).c_str());
        SendMessage(hwndcombode, CB_SETCURSEL, NULL, (LPARAM)(Configurations::defaultde).c_str());
        SendMessage(hwndcombode, EM_SETREADONLY, TRUE, NULL);

        break;
    }
    case WM_COMMAND:

        if (LOWORD(wParam) == ID_ONSTART)
        {
            ShowWindow(hwndquickweekdays, SW_SHOW);
            ShowWindow(hwndquickdatetTimer, SW_SHOW);
            SendMessage(hwndrandomize, BM_SETCHECK, BST_CHECKED, 1);
        }
        if (LOWORD(wParam) == ID_START)

        {
            ShowWindow(hwndtextbox2, SW_HIDE);
            ShowWindow(hwndtextbox3, SW_HIDE);
            ShowWindow(hwndtextbox4, SW_HIDE);
            ShowWindow(hwndtextbox5, SW_HIDE);
            ShowWindow(hwndtextbox6, SW_HIDE);
            ShowWindow(hwndtextbox9, SW_HIDE);
            int idx_rowde = SendMessage(hwndlangde, CB_GETCURSEL, 0, 0);
            TCHAR strText[255] = {0};
            SendMessage(hwndlangde, CB_GETLBTEXT, idx_rowde, (LPARAM)strText);
            TCHAR strTextde[255] = {0};
            int idx_rowdeadv = SendMessage(hwndcombode, CB_GETCURSEL, 0, 0);
            SendMessage(hwndcombode, CB_GETLBTEXT, idx_rowdeadv, (LPARAM)strTextde);
            TCHAR strTextcombo[255] = {0};
            int idx_rowcombo = SendMessage(hwndcombo, CB_GETCURSEL, 0, 0);
            SendMessage(hwndcombo, CB_GETLBTEXT, idx_rowcombo, (LPARAM)strTextcombo);
            if (idx_rowde == 0)
            {
                if (idx_rowdeadv == 0)
                {
                    TCHAR strText[255] = {0};
                    int idx_row = SendMessage(hwndcombo, CB_GETCURSEL, 0, 0);
                    SendMessage(hwndcombo, CB_GETLBTEXT, idx_row, (LPARAM)strText);

                    TCHAR strText1[255] = {0};
                    int idx_row1 = SendMessage(hwndquickweekdays, CB_GETCURSEL, 0, 0);
                    SendMessage(hwndquickweekdays, CB_GETLBTEXT, idx_row1, (LPARAM)strText1);

                    TCHAR strText1de[255] = {0};
                    int idx_row1de = SendMessage(hwndquickweekdaysde, CB_GETCURSEL, 0, 0);
                    SendMessage(hwndquickweekdaysde, CB_GETLBTEXT, idx_row1de, (LPARAM)strText1de);

                    int connection{ConnectionChecker()};
                    if (connection == 0)
                    {

                        ShowWindow(hwndtextbox9, SW_SHOW);
                        SetWindowText(hwndtextbox9, (Configurations::taskfailedde).c_str());
                        Log(InfoP, (Configurations::taskfailed).c_str(), "Deployment Toolbox", __LINE__, "main");
                        ShowWindow(hwndtextbox2, SW_SHOW);
                        SetWindowText(hwndtextbox2, (Configurations::connectionfailedde).c_str());
                        Log(InfoP, (Configurations::taskfailed).c_str(), "Deployment Toolbox", __LINE__, "main");
                        ShowWindow(hwndtextbox3, SW_SHOW);
                        SetWindowText(hwndtextbox3, (Configurations::skippedfailedde).c_str());
                        Log(InfoP, (Configurations::skippedfailed).c_str(), "Deployment Toolbox", __LINE__, "main");
                        ShowWindow(hwndtextbox4, SW_SHOW);
                        SetWindowText(hwndtextbox4, (Configurations::skippedfailedde).c_str());
                        Log(InfoP, (Configurations::skippedfailed).c_str(), "Deployment Toolbox", __LINE__, "main");
                        ShowWindow(hwndtextbox5, SW_SHOW);
                        SetWindowText(hwndtextbox5, (Configurations::skippedfailedde).c_str());
                        Log(InfoP, (Configurations::skippedfailed).c_str(), "Deployment Toolbox", __LINE__, "main");
                    }
                    if (connection == 1)
                    {
                        SYSTEMTIME st{};
                        DateTime_GetSystemtime(hwndquickdatetTimer, &st);
                        int Random = Randomize(15);
                        SYSTEMTIME s2 = add(st, 60 * (Random));
                        cout << "Time:" << endl;
                        char buffer[256];
                        sprintf(buffer,
                                "%02d:%02d",
                                s2.wHour,
                                s2.wMinute);
                        std::string strMessage;
                        strMessage = buffer;
                        cout << strMessage << endl;
                        ShowWindow(hwndtextbox2, SW_SHOW);
                        SetWindowText(hwndtextbox2, (Configurations::connectionsuccessde).c_str());
                        Log(InfoP, "Connection to the CIS server is successful ", "Deployment Toolbox", __LINE__, "main");
                        const char *dir = "C:\\CIS4ITM\\";
                        struct stat sb;
                        // If the file/directory exists at the path returns 0
                        if (stat(dir, &sb) == 0)
                        {
                            ShowWindow(hwndtextbox3, SW_SHOW);
                            SetWindowText(hwndtextbox3, (Configurations::folderexistsde).c_str());
                            Log(InfoP, "Folder already exists", "Deployment Toolbox", __LINE__, "main");
                        }
                        else
                        {
                            // cout << "The folder does not exist\n";
                            ShowWindow(hwndtextbox3, SW_SHOW);
                            SetWindowText(hwndtextbox3, TEXT("\r\nOrdner existiert nicht, Ordner wird erstellt"));
                            Log(InfoP, "Folder does not exists,creating folder", "Deployment Toolbox", __LINE__, "main");
                            int check;
                            check = mkdir("C:\\CIS4ITM");

                            // check if directory is created or not
                            if (!check)
                            {
                                ShowWindow(hwndtextbox3, SW_SHOW);
                                SetWindowText(hwndtextbox3, (Configurations::foldersuccessde).c_str());
                                Log(InfoP, "Folder created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                            else
                            {
                                ShowWindow(hwndtextbox3, SW_SHOW);
                                SetWindowText(hwndtextbox3, (Configurations::folderfailurede).c_str());
                                Log(InfoP, "Unable to create folder", "Deployment Toolbox", __LINE__, "main");
                            }
                        }

                        fstream fileStream;
                        fileStream.open("C:\\CIS4ITM\\CIS-Inventory-Start.exe");
                        if (!fileStream.fail())

                        {
                            ShowWindow(hwndtextbox4, SW_SHOW);
                            SetWindowText(hwndtextbox4, TEXT("\r\nErfolg: Client-exe existiert bereits"));
                            Log(InfoP, "Client exe already exists", "Deployment Toolbox", __LINE__, "main");

                            // SetWindowText(hwndtextbox2, TEXT("\r\nClient exe downloaded successfully"));
                        }
                        else
                        {
                            DownloadFingerprinter();
                            ShowWindow(hwndtextbox4, SW_SHOW);
                            SetWindowText(hwndtextbox4, TEXT("Erfolg: Client-exe erfolgreich heruntergeladen"));
                            Log(InfoP, "Client exe downloaded successfully", "Deployment Toolbox", __LINE__, "main");
                        }

                        int len = GetWindowTextLengthW(GetDlgItem(hwnd, 21)) + 1;
                        wchar_t text[len];
                        GetWindowTextW(GetDlgItem(hwnd, 21), text, len);
                        wstring ws(text);
                        string str(ws.begin(), ws.end());
                        cout << str << endl;
                        string split = str.substr(str.find(":") + 1);
                        cout << split << endl;
                        // system(("net localgroup administrators" +split +" /add").c_str());
                        // cout << "net localgroup administrators" + split + " /add" << endl;
                        system("icacls C:\\CIS4ITM  /inheritance:d /remove:g *S-1-5-11");
                        system("icacls C:\\CIS4ITM  /inheritance:d /remove:g *S-1-5-11");
                        system("icacls C:\\CIS4ITM  /inheritance:d /remove:g "
                               "Users");
                        system(("icacls C:\\CIS4ITM /grant "+split+ ":(OI)(CI)F /T").c_str());
                        system("cacls C:\\CIS4ITM  /inheritance:d /remove:g "
                               "Users");

                        // system("for %A IN ("Authenticated Users" "Users" ) do @cacls C:\\CIS4ITM1 /e /c /d %~A:F");
                        ShowWindow(hwndtextbox5, SW_SHOW);
                        SetWindowText(hwndtextbox5, TEXT("\r\nErfolg: Die Ordnerberechtigung wurde erfolgreich festgelegt"));
                        Log(InfoP, "Folder permission set successfully", "Deployment Toolbox", __LINE__, "main");
                        UINT checkedstartup = SendMessage(hwndonstart, BM_GETCHECK, 0, 0);
                        cout << "check status" << endl;
                        if (checkedstartup == BST_CHECKED)
                        {
                            // SendMessage(hwndrandomize, BM_SETCHECK, BST_UNCHECKED, 1);
                            ShowWindow(hwndquickweekdaysde, SW_SHOW);
                            ShowWindow(hwndquickdatetTimer, SW_SHOW);
                            cout << "hide" << endl;
                            system("schtasks /create /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /sc onstart /F /RL HIGHEST /RU SYSTEM");
                            ShowWindow(hwndtextbox9, SW_SHOW);
                            SetWindowText(hwndtextbox9, ("Erfolg: Die Aufgabe CIS4ITM_Package_execute wurde erfolgreich erstellt"));
                            Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                        }

                        if (checkedstartup == 0)
                        {

                            if (idx_row1de == 0)
                            {
                                ShowWindow(hwndquickdatetTimer, SW_SHOW);
                                system(("schtasks /create /sc weekly /D MON /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage).c_str());
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccessde).c_str());
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                            if (idx_row1de == 1)
                            {
                                ShowWindow(hwndquickdatetTimer, SW_SHOW);
                                system(("schtasks /create /sc weekly /D TUE /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessage).c_str());
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccessde).c_str());
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                            if (idx_row1de == 2)
                            {
                                ShowWindow(hwndquickdatetTimer, SW_SHOW);
                                system(("schtasks /create /sc weekly /D WED /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage).c_str());
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccessde).c_str());
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                            if (idx_row1de == 3)
                            {
                                ShowWindow(hwndquickdatetTimer, SW_SHOW);
                                system(("schtasks /create /sc weekly /D THU /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessage).c_str());
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccessde).c_str());
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                            if (idx_row1de == 4)
                            {
                                ShowWindow(hwndquickdatetTimer, SW_SHOW);

                                system(("schtasks /create /sc weekly /D FRI /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage).c_str());
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccessde).c_str());
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }

                            if (idx_row1de == 5)
                            {
                                ShowWindow(hwndquickdatetTimer, SW_HIDE);
                                system("schtasks /create /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /sc onstart /F /RU SYSTEM /RL HIGHEST");
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccessde).c_str());
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                        }
                    }
                }
                // german and advanced
                if (idx_rowdeadv == 1)
                {

                    SendMessage(hwndrandomize, BM_SETCHECK, BST_CHECKED, 1);
                    UINT checkedconnectionde = SendMessage(hwndconnectionde, BM_GETCHECK, 0, 0);
                    UINT checkedfolderde = SendMessage(hwndfolderde, BM_GETCHECK, 0, 0);
                    UINT checkeddownloadde = SendMessage(hwnddownloadde, BM_GETCHECK, 0, 0);
                    UINT checkedACLde = SendMessage(hwndACLde, BM_GETCHECK, 0, 0);
                    UINT checkedschtaskde = SendMessage(hwndschtaskde, BM_GETCHECK, 0, 0);
                    int connection{ConnectionChecker()};

                    if (connection == 1)
                    {

                        if (checkedconnectionde == BST_UNCHECKED)
                        {
                            ShowWindow(hwndtextbox2, SW_HIDE);
                            EnableWindow(hwnddownload, TRUE);
                        }

                        if (checkedconnectionde == BST_CHECKED)
                        {
                            int connection{ConnectionChecker()};
                            if (connection == 1)
                            {
                                ShowWindow(hwndtextbox2, SW_SHOW);
                                SetWindowText(hwndtextbox2, (Configurations::connectionsuccessde).c_str());
                                Log(InfoP, "Connection to the CIS Server is successful", "Deployment Toolbox", __LINE__, "main");

                                SetTextColor((HDC)hwndtextbox2, RGB(255, 0, 0));
                            }
                            else
                            {
                                ShowWindow(hwndtextbox2, SW_SHOW);
                                SetWindowText(hwndtextbox2, (Configurations::connectionfailedde).c_str());
                                Log(InfoP, "Connection is not successful", "Deployment Toolbox", __LINE__, "main");
                                EnableWindow(hwnddownload, FALSE);
                                ShowWindow(hwndtextbox4, SW_HIDE);
                                EnableWindow(hwndfolder, FALSE);
                                ShowWindow(hwndtextbox5, SW_HIDE);
                                EnableWindow(hwndACL, FALSE);
                                ShowWindow(hwndtextbox6, SW_HIDE);
                                EnableWindow(hwndACL, FALSE);
                                ShowWindow(hwndtextbox3, SW_HIDE);
                                EnableWindow(hwndschtask, FALSE);
                                goto label1;
                            }
                        }

                        if (checkedfolderde == BST_CHECKED and connection == 1)
                        {

                            const char *dir = "C:\\CIS4ITM\\";
                            struct stat sb;
                            // If the file/directory exists at the path returns 0
                            if (stat(dir, &sb) == 0)
                            {
                                ShowWindow(hwndtextbox3, SW_SHOW);
                                SetWindowText(hwndtextbox3, (Configurations::folderexistsde).c_str());
                                Log(InfoP, "Folder already exists", "Deployment Toolbox", __LINE__, "main");
                            }
                            else
                            {
                                int check;
                                check = mkdir("C:\\CIS4ITM");

                                // check if directory is created or not
                                if (!check)
                                {
                                    ShowWindow(hwndtextbox3, SW_SHOW);
                                    SetWindowText(hwndtextbox3, (Configurations::foldersuccessde).c_str());
                                    Log(InfoP, "Folder created successfully", "Deployment Toolbox", __LINE__, "main");
                                }
                                else
                                {
                                    ShowWindow(hwndtextbox3, SW_SHOW);
                                    SetWindowText(hwndtextbox3, (Configurations::folderfailurede).c_str());
                                    Log(InfoP, "Unable to create folder", "Deployment Toolbox", __LINE__, "main");
                                }
                            }
                        }

                        if (checkedfolderde == BST_UNCHECKED)
                        {
                            ShowWindow(hwndtextbox3, SW_HIDE);
                        }

                        const char *dir = "C:\\CIS4ITM\\";
                        struct stat sb;
                        if (checkeddownloadde == BST_CHECKED and stat(dir, &sb) != 0)
                        {
                            ShowWindow(hwndtextbox4, SW_SHOW);
                            SetWindowText(hwndtextbox4, (Configurations::folderwarningde).c_str());
                            Log(InfoP, "Please create CIS4ITM folder", "Deployment Toolbox", __LINE__, "main");
                        }

                        if (checkeddownloadde == BST_CHECKED and stat(dir, &sb) == 0)
                        {

                            fstream fileStream;
                            fileStream.open("C:\\CIS4ITM\\CIS-Inventory-Start.exe");
                            if (fileStream.fail())
                            {
                                DownloadFingerprinter();
                                ShowWindow(hwndtextbox4, SW_SHOW);
                                SetWindowText(hwndtextbox4, TEXT("Erfolg: Client-exe heruntergeladen"));
                                Log(InfoP, "Client exe downloaded successfully", "Deployment Toolbox", __LINE__, "main");

                                // SetWindowText(hwndtextbox2, TEXT("\r\nClient exe downloaded successfully"));
                            }
                            else
                            {
                                ShowWindow(hwndtextbox4, SW_SHOW);
                                SetWindowText(hwndtextbox4, TEXT("\r\nWarnung: Client-exe existiert bereits"));
                                Log(InfoP, "Client exe already exists", "Deployment Toolbox", __LINE__, "main");
                            }
                        }

                        if (checkeddownloadde == BST_UNCHECKED)
                        {
                            ShowWindow(hwndtextbox4, SW_HIDE);
                        }

                        if (checkedACLde == BST_CHECKED and stat(dir, &sb) != 0)
                        {
                            ShowWindow(hwndtextbox5, SW_SHOW);
                            SetWindowText(hwndtextbox5, TEXT("\r\nWarnung: Bitte erstellen Sie den C:\\CIS4ITM-Ordner, bevor Sie die Ordnerberechtigungen festlegen"));
                            Log(InfoP, "Please create the C:\\CIS4ITM folder before setting the folder permission", "Deployment Toolbox", __LINE__, "main");
                        }
                        fstream fileStream;
                        fileStream.open("C:\\CIS4ITM\\CIS-Inventory-Start.exe");
                        if (checkedACLde == BST_CHECKED and fileStream.fail())
                        {
                            ShowWindow(hwndtextbox5, SW_SHOW);
                            SetWindowText(hwndtextbox5, TEXT("\r\nFehler: Bitte erstellen Sie den C:\\CIS4ITM-Ordner, bevor Sie die Ordnerberechtigungen festlegen"));
                            Log(InfoP, "Please create C:\\CIS4ITM folder before setting the folder permissions", "Deployment Toolbox", __LINE__, "main");
                        }
                        if (checkedACLde == BST_CHECKED and !fileStream.fail())
                        {

                            TCHAR uservalue[255] = {0};
                            int idx_row10 = SendMessage(hwndtextbox7, WM_GETTEXT, 0, 0);
                            SendMessage(hwndtextbox7, WM_GETTEXT, idx_row10, (LPARAM)uservalue);
                            cout << idx_row10 << endl;

                            int len = GetWindowTextLengthW(GetDlgItem(hwnd, 21)) + 1;
                            wchar_t text[len];
                            GetWindowTextW(GetDlgItem(hwnd, 21), text, len);
                            wstring ws(text);
                            string str(ws.begin(), ws.end());
                            cout << str << endl;
                            string split = str.substr(str.find(":") + 1);
                            cout << split << endl;
                            // system(("net localgroup administrators" + split + " /add").c_str());
                            // cout << "net localgroup administrators" + split + " /add" << endl;

                            system("icacls C:\\CIS4ITM  /inheritance:d /remove:g *S-1-5-11");
                            system("icacls C:\\CIS4ITM  /inheritance:d /remove:g *S-1-5-11");
                            system("icacls C:\\CIS4ITM  /inheritance:d /remove:g "
                                   "Users");
                            system(("icacls C:\\CIS4ITM /grant "+split+ ":(OI)(CI)F /T").c_str());
                            system("cacls C:\\CIS4ITM  /inheritance:d /remove:g "
                                   "Users");

                            // system("for %A IN ("Authenticated Users" "Users" ) do @cacls C:\\CIS4ITM1 /e /c /d %~A:F");
                            ShowWindow(hwndtextbox5, SW_SHOW);
                            SetWindowText(hwndtextbox5, TEXT("\r\nErfolg: Die Ordnerberechtigung ist festgelegt"));
                            Log(InfoP, "Folder permission set successfully", "Deployment Toolbox", __LINE__, "main");
                        }
                        if (checkedACLde == BST_UNCHECKED)
                        {
                            ShowWindow(hwndtextbox5, SW_HIDE);
                        }

                        if (checkedschtaskde == BST_CHECKED and fileStream.fail())
                        {

                            ShowWindow(hwndtextbox9, SW_SHOW);
                            SetWindowText(hwndtextbox9, "Warnung: Bitte laden Sie die Client-Exe herunter");
                            Log(InfoP, "Please download the client exe", "Deployment Toolbox", __LINE__, "main");
                        }

                        if (checkedschtaskde == BST_CHECKED and stat(dir, &sb) != 0)
                        {

                            ShowWindow(hwndtextbox9, SW_SHOW);
                            SetWindowText(hwndtextbox9, (Configurations::folderwarningde).c_str());
                            Log(InfoP, "Please create C:\\CIS4ITM folder", "Deployment Toolbox", __LINE__, "main");
                        }

                        if (checkedschtaskde == BST_CHECKED and !fileStream.fail() and stat(dir, &sb) == 0)
                        {

                            TCHAR strText2[255] = {0};
                            int idx_row2 = SendMessage(hwndweekdays, CB_GETCURSEL, 0, 0);
                            SendMessage(hwndweekdays, CB_GETLBTEXT, idx_row2, (LPARAM)strText2);

                            SYSTEMTIME sts{};
                            SYSTEMTIME randomweekly{};
                            DateTime_GetSystemtime(hwnddatetTimer, &sts);
                            DateTime_GetSystemtime(hwndrandomtimede, &randomweekly);
                            int Randomadv = Randomize(randomweekly.wMinute);
                            SYSTEMTIME stsweekly = add(sts, 60 * (Randomadv));

                            char buffers[256];
                            sprintf(buffers,
                                    "%02d:%02d",
                                    stsweekly.wHour,
                                    stsweekly.wMinute);
                            std::string strMessage1;
                            strMessage1 = buffers;
                            SYSTEMTIME stdaily{};

                            SYSTEMTIME stsm{};
                            SYSTEMTIME randommonthly{};
                            DateTime_GetSystemtime(hwndmonthlydatetTimer, &stsm);
                            DateTime_GetSystemtime(hwndrandomtimede, &randommonthly);
                            int Randomadvmpnthly = Randomize(randommonthly.wMinute);
                            SYSTEMTIME stsmonthly = add(stsm, 60 * (Randomadvmpnthly));

                            char buffersmon[256];
                            sprintf(buffersmon,
                                    "%02d:%02d",
                                    stsmonthly.wHour,
                                    stsmonthly.wMinute);
                            std::string strMessage7;
                            strMessage7 = buffersmon;

                            SYSTEMTIME randomdaily{};
                            DateTime_GetSystemtime(hwnddailydatetTimer, &stdaily);
                            DateTime_GetSystemtime(hwndrandomtimede, &randomdaily);
                            int Randomadvdaily = Randomize(randomdaily.wMinute);
                            SYSTEMTIME stsdaily = add(stdaily, 60 * (Randomadvdaily));

                            char bufferdaily[256];
                            sprintf(bufferdaily,
                                    "%02d:%02d",
                                    stsdaily.wHour,
                                    stsdaily.wMinute);
                            std::string strMessagedaily;
                            strMessagedaily = bufferdaily;
                            UINT checkeddailyde = SendMessage(hwnddailyde, BM_GETCHECK, 0, 0);
                            UINT checkedweeklyde = SendMessage(hwndweeklyde, BM_GETCHECK, 0, 0);
                            UINT checkedmonthlyde = SendMessage(hwndmonthlyde, BM_GETCHECK, 0, 0);
                            // time_t newTime = strMessagedaily + (60 * 10);

                            if (checkeddailyde == 1)
                            {
                                system(("schtasks /create /sc daily /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessagedaily).c_str());
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccessde).c_str());
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                            if (checkedweeklyde == 1)
                            {
                                if (idx_row2 == 0)
                                {

                                    system(("schtasks /create /sc weekly /D MON /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage1).c_str());
                                    ShowWindow(hwndtextbox9, SW_SHOW);
                                    SetWindowText(hwndtextbox9, (Configurations::tasksuccessde).c_str());
                                    Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                                }

                                if (idx_row2 == 1)
                                {

                                    system(("schtasks /create /sc weekly /D TUE /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage1).c_str());
                                    ShowWindow(hwndtextbox9, SW_SHOW);
                                    SetWindowText(hwndtextbox9, (Configurations::tasksuccessde).c_str());
                                    Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                                }
                                if (idx_row2 == 2)
                                {

                                    system(("schtasks /create /sc weekly /D WED /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage1).c_str());
                                    ShowWindow(hwndtextbox9, SW_SHOW);
                                    SetWindowText(hwndtextbox9, (Configurations::tasksuccessde).c_str());
                                    Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                                }
                                if (idx_row2 == 3)
                                {

                                    system(("schtasks /create /sc weekly /D THU /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage1).c_str());
                                    ShowWindow(hwndtextbox9, SW_SHOW);
                                    SetWindowText(hwndtextbox9, (Configurations::tasksuccessde).c_str());
                                    Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                                }
                                if (idx_row2 == 4)
                                {

                                    system(("schtasks /create /sc weekly /D FRI /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage1).c_str());
                                    ShowWindow(hwndtextbox9, SW_SHOW);
                                    SetWindowText(hwndtextbox9, (Configurations::tasksuccessde).c_str());
                                    Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                                }
                            }
                            if (checkedmonthlyde == 1)
                            {
                                system(("schtasks /create /sc monthly /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage7).c_str());
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccessde).c_str());
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }

                            UINT checkedstartupadvde = SendMessage(hwndonstartadvde, BM_GETCHECK, 0, 0);
                            if (checkedstartupadvde == BST_CHECKED)
                            {
                                ShowWindow(hwnddatetTimer, SW_HIDE);
                                // EnableWindow(hwndrandomizeadv, FALSE);
                                EnableWindow(hwndrandomtime, FALSE);
                                ShowWindow(hwndrandomtime, SW_HIDE);
                                ShowWindow(hwndrandomtimede, SW_HIDE);
                                ShowWindow(hwnddailydatetTimer, SW_HIDE);
                                ShowWindow(hwndweekdays, SW_HIDE);
                                system("schtasks /create /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /sc onstart /F /RU SYSTEM /RL HIGHEST");
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccessde).c_str());
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                        }

                        if (checkedschtaskde == BST_UNCHECKED)
                        {
                            ShowWindow(hwndtextbox9, SW_HIDE);
                        }
                    }

                    if (connection == 0)
                    {
                        if (checkedschtaskde == 1)
                        {
                            ShowWindow(hwndtextbox9, SW_SHOW);
                            SetWindowText(hwndtextbox9, (Configurations::taskfailedde).c_str());
                            Log(InfoP, "Task scheduling failed", "Deployment Toolbox", __LINE__, "main");
                        }
                        if (checkedschtaskde == 0)
                        {
                            ShowWindow(hwndtextbox9, SW_HIDE);
                        }
                        if (checkedconnectionde == 1)
                        {
                            ShowWindow(hwndtextbox2, SW_SHOW);
                            SetWindowText(hwndtextbox2, (Configurations::connectionfailedde).c_str());
                            Log(InfoP, "Connection to the CIS Server failed!", "Deployment Toolbox", __LINE__, "main");
                        }
                        if (checkedconnectionde == 0)
                        {
                            ShowWindow(hwndtextbox2, SW_HIDE);
                        }
                        if (checkedfolderde == 1)
                        {
                            ShowWindow(hwndtextbox3, SW_SHOW);
                            SetWindowText(hwndtextbox3, (Configurations::skippedfailedde).c_str());
                            Log(InfoP, "Skipped due to failure", "Deployment Toolbox", __LINE__, "main");
                        }
                        if (checkedfolderde == 0)
                        {
                            ShowWindow(hwndtextbox3, SW_HIDE);
                        }
                        if (checkeddownloadde == 1)
                        {
                            ShowWindow(hwndtextbox4, SW_SHOW);
                            SetWindowText(hwndtextbox4, (Configurations::skippedfailedde).c_str());
                            Log(InfoP, "Skipped due to failure", "Deployment Toolbox", __LINE__, "main");
                        }
                        if (checkeddownloadde == 0)
                        {
                            ShowWindow(hwndtextbox4, SW_HIDE);
                        }
                        if (checkedACLde == 1)
                        {
                            ShowWindow(hwndtextbox5, SW_SHOW);
                            SetWindowText(hwndtextbox5, (Configurations::skippedfailedde).c_str());
                            Log(InfoP, "Skipped due to failure", "Deployment Toolbox", __LINE__, "main");
                        }
                        if (checkedACLde == 0)
                        {
                            ShowWindow(hwndtextbox5, SW_HIDE);
                        }
                    }
                label1:
                    break;
                }
            }

            if (idx_rowde == 1)
            {

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
                        SetWindowText(hwndtextbox9, (Configurations::taskfailed).c_str());
                        Log(ErrorP, (Configurations::taskfailed).c_str(), "Deployment Toolbox", __LINE__, "main");
                        ShowWindow(hwndtextbox2, SW_SHOW);
                        SetWindowText(hwndtextbox2, (Configurations::connectionfailed).c_str());
                        Log(ErrorP, (Configurations::taskfailed).c_str(), "Deployment Toolbox", __LINE__, "main");
                        ShowWindow(hwndtextbox3, SW_SHOW);
                        SetWindowText(hwndtextbox3, (Configurations::skippedfailed).c_str());
                        Log(ErrorP, (Configurations::skippedfailed).c_str(), "Deployment Toolbox", __LINE__, "main");
                        ShowWindow(hwndtextbox4, SW_SHOW);
                        SetWindowText(hwndtextbox4, (Configurations::skippedfailed).c_str());
                        Log(ErrorP, (Configurations::skippedfailed).c_str(), "Deployment Toolbox", __LINE__, "main");
                        ShowWindow(hwndtextbox5, SW_SHOW);
                        SetWindowText(hwndtextbox5, (Configurations::skippedfailed).c_str());
                        Log(ErrorP, (Configurations::skippedfailed).c_str(), "Deployment Toolbox", __LINE__, "main");
                    }

                    if (connection == 1)
                    {
                        SYSTEMTIME st{};
                        DateTime_GetSystemtime(hwndquickdatetTimer, &st);
                        int Random = Randomize(15);
                        SYSTEMTIME s2 = add(st, 60 * (Random));
                        cout << "Time:" << endl;
                        char buffer[256];
                        sprintf(buffer,
                                "%02d:%02d",
                                s2.wHour,
                                s2.wMinute);
                        std::string strMessage;
                        strMessage = buffer;
                        cout << strMessage << endl;
                        ShowWindow(hwndtextbox2, SW_SHOW);
                        SetWindowText(hwndtextbox2, (Configurations::connectionsuccess).c_str());
                        Log(InfoP, "Connection to the CIS server is successful ", "Deployment Toolbox", __LINE__, "main");
                        const char *dir = "C:\\CIS4ITM\\";
                        struct stat sb;
                        // If the file/directory exists at the path returns 0
                        if (stat(dir, &sb) == 0)
                        {
                            ShowWindow(hwndtextbox3, SW_SHOW);
                            SetWindowText(hwndtextbox3, (Configurations::folderexists).c_str());
                            Log(WarnP, "Folder already exists", "Deployment Toolbox", __LINE__, "main");
                        }
                        else
                        {
                            // cout << "The folder does not exist\n";
                            ShowWindow(hwndtextbox3, SW_SHOW);
                            SetWindowText(hwndtextbox3, TEXT("\r\nFolder does not exists,creating folder"));
                            Log(InfoP, "Folder does not exists,creating folder", "Deployment Toolbox", __LINE__, "main");
                            int check;
                            check = mkdir("C:\\CIS4ITM");

                            // check if directory is created or not
                            if (!check)
                            {
                                ShowWindow(hwndtextbox3, SW_SHOW);
                                SetWindowText(hwndtextbox3, (Configurations::foldersuccess).c_str());
                                Log(InfoP, "Folder created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                            else
                            {
                                ShowWindow(hwndtextbox3, SW_SHOW);
                                SetWindowText(hwndtextbox3, (Configurations::folderfailure).c_str());
                                Log(ErrorP, "Unable to create folder", "Deployment Toolbox", __LINE__, "main");
                            }
                        }

                        fstream fileStream;
                        fileStream.open("C:\\CIS4ITM\\CIS-Inventory-Start.exe");
                        if (!fileStream.fail())

                        {
                            ShowWindow(hwndtextbox4, SW_SHOW);
                            SetWindowText(hwndtextbox4, TEXT("\r\nWarning: Client exe already exists"));
                            Log(WarnP, "Client exe already exists", "Deployment Toolbox", __LINE__, "main");

                            // SetWindowText(hwndtextbox2, TEXT("\r\nClient exe downloaded successfully"));
                        }
                        else
                        {
                            DownloadFingerprinter();
                            ShowWindow(hwndtextbox4, SW_SHOW);
                            SetWindowText(hwndtextbox4, TEXT("Success: Client exe downloaded"));
                            Log(InfoP, "Client exe downloaded successfully", "Deployment Toolbox", __LINE__, "main");
                        }

                        int len = GetWindowTextLengthW(GetDlgItem(hwnd, 21)) + 1;
                        wchar_t text[len];
                        GetWindowTextW(GetDlgItem(hwnd, 21), text, len);
                        wstring ws(text);
                        string str(ws.begin(), ws.end());
                        cout << str << endl;
                        string split = str.substr(str.find(":") + 1);
                        cout << split << endl;
                        // system(("net localgroup administrators" +split +" /add").c_str());
                        // cout << "net localgroup administrators" + split + " /add" << endl;
                        system("icacls C:\\CIS4ITM  /inheritance:d /remove:g *S-1-5-11");
                        system("icacls C:\\CIS4ITM  /inheritance:d /remove:g *S-1-5-11");
                        system("icacls C:\\CIS4ITM  /inheritance:d /remove:g "
                               "Users");
                        system(("icacls C:\\CIS4ITM /grant "+split+ ":(OI)(CI)F /T").c_str());
                       
                        system("cacls C:\\CIS4ITM  /inheritance:d /remove:g "
                               "Users");

                        // system("for %A IN ("Authenticated Users" "Users" ) do @cacls C:\\CIS4ITM1 /e /c /d %~A:F");
                        ShowWindow(hwndtextbox5, SW_SHOW);
                        SetWindowText(hwndtextbox5, TEXT("\r\nSuccess: Folder permission is set"));
                        Log(InfoP,("User ID:"+split).c_str(), "Deployment Toolbox", __LINE__, "main");
                        Log(InfoP, "Folder permission set successfully", "Deployment Toolbox", __LINE__, "main");
                        UINT checkedstartup = SendMessage(hwndonstart, BM_GETCHECK, 0, 0);
                        cout << "check status" << endl;
                        if (checkedstartup == BST_CHECKED)
                        {
                            // SendMessage(hwndrandomize, BM_SETCHECK, BST_UNCHECKED, 1);
                            ShowWindow(hwndquickweekdays, SW_SHOW);
                            ShowWindow(hwndquickdatetTimer, SW_SHOW);
                            cout << "hide" << endl;
                            system("schtasks /create /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /sc onstart /F /RU SYSTEM /RL HIGHEST");
                            ShowWindow(hwndtextbox9, SW_SHOW);
                            SetWindowText(hwndtextbox9, (Configurations::tasksuccess).c_str());
                            Log(InfoP, "Schedule type:onstart", "Deployment Toolbox", __LINE__, "main");
                            Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                        }

                        if (checkedstartup == 0)
                        {

                            if (idx_row1 == 0)
                            {
                                ShowWindow(hwndquickdatetTimer, SW_SHOW);
                                system(("schtasks /create /sc weekly /D MON /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessage).c_str());
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccess).c_str());
                                Log(InfoP, ("Schedule type:Weekly,Monday,schedule time:"+strMessage).c_str(), "Deployment Toolbox", __LINE__, "main");
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                            if (idx_row1 == 1)
                            {
                                ShowWindow(hwndquickdatetTimer, SW_SHOW);
                                system(("schtasks /create /sc weekly /D TUE /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage).c_str());
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccess).c_str());
                                 Log(InfoP, ("Schedule type:Weekly,Tuesday,schedule time:"+strMessage).c_str(), "Deployment Toolbox", __LINE__, "main");
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                            if (idx_row1 == 2)
                            {
                                ShowWindow(hwndquickdatetTimer, SW_SHOW);
                                system(("schtasks /create /sc weekly /D WED /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /ST " + strMessage).c_str());
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccess).c_str());
                                  Log(InfoP, ("Schedule type:Weekly,Wednesday,schedule time:"+strMessage).c_str(), "Deployment Toolbox", __LINE__, "main");
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                            if (idx_row1 == 3)
                            {
                                ShowWindow(hwndquickdatetTimer, SW_SHOW);
                                system(("schtasks /create /sc weekly /D THU /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage).c_str());
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccess).c_str());
                                  Log(InfoP, ("Schedule type:Weekly,Thursday,schedule time:"+strMessage).c_str(), "Deployment Toolbox", __LINE__, "main");
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                            if (idx_row1 == 4)
                            {
                                ShowWindow(hwndquickdatetTimer, SW_SHOW);

                                system(("schtasks /create /sc weekly /D FRI /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage).c_str());
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccess).c_str());
                                  Log(InfoP, ("Schedule type:Weekly,Friday,schedule time:"+strMessage).c_str(), "Deployment Toolbox", __LINE__, "main");
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }

                            if (idx_row1 == 5)
                            {
                                ShowWindow(hwndquickdatetTimer, SW_HIDE);
                                system("schtasks /create /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /sc onstart /F /RU SYSTEM /RL HIGHEST");
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccess).c_str());
                                  Log(InfoP, "Schedule type:onstart", "Deployment Toolbox", __LINE__, "main");
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
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

                    if (connection == 1)
                    {

                        if (checkedconnection == BST_UNCHECKED)
                        {
                            ShowWindow(hwndtextbox2, SW_HIDE);
                            EnableWindow(hwnddownload, TRUE);
                        }

                        if (checkedconnection == BST_CHECKED)
                        {
                            int connection{ConnectionChecker()};
                            if (connection == 1)
                            {
                                ShowWindow(hwndtextbox2, SW_SHOW);
                                SetWindowText(hwndtextbox2, (Configurations::connectionsuccess).c_str());
                                Log(InfoP, "Connection to the CIS Server is successful", "Deployment Toolbox", __LINE__, "main");

                                SetTextColor((HDC)hwndtextbox2, RGB(255, 0, 0));
                            }
                            else
                            {
                                ShowWindow(hwndtextbox2, SW_SHOW);
                                SetWindowText(hwndtextbox2, (Configurations::connectionfailed).c_str());
                                Log(ErrorP, "Connection is not successful", "Deployment Toolbox", __LINE__, "main");
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

                        if (checkedfolder == BST_CHECKED and connection == 1)
                        {

                            const char *dir = "C:\\CIS4ITM\\";
                            struct stat sb;
                            // If the file/directory exists at the path returns 0
                            if (stat(dir, &sb) == 0)
                            {
                                ShowWindow(hwndtextbox3, SW_SHOW);
                                SetWindowText(hwndtextbox3, (Configurations::folderexists).c_str());
                                Log(WarnP, "Folder already exists", "Deployment Toolbox", __LINE__, "main");
                            }
                            else
                            {
                                int check;
                                check = mkdir("C:\\CIS4ITM");

                                // check if directory is created or not
                                if (!check)
                                {
                                    ShowWindow(hwndtextbox3, SW_SHOW);
                                    SetWindowText(hwndtextbox3, (Configurations::foldersuccess).c_str());
                                    Log(WarnP, "Folder created successfully", "Deployment Toolbox", __LINE__, "main");
                                }
                                else
                                {
                                    ShowWindow(hwndtextbox3, SW_SHOW);
                                    SetWindowText(hwndtextbox3, (Configurations::folderfailure).c_str());
                                    Log(ErrorP, "Unable to create folder", "Deployment Toolbox", __LINE__, "main");
                                }
                            }
                        }

                        if (checkedfolder == BST_UNCHECKED)
                        {
                            ShowWindow(hwndtextbox3, SW_HIDE);
                        }

                        const char *dir = "C:\\CIS4ITM\\";
                        struct stat sb;
                        if (checkeddownload == BST_CHECKED and stat(dir, &sb) != 0)
                        {
                            ShowWindow(hwndtextbox4, SW_SHOW);
                            SetWindowText(hwndtextbox4, (Configurations::folderwarning).c_str());
                            Log(ErrorP, "Please create C:\\CIS4ITM folder", "Deployment Toolbox", __LINE__, "main");
                        }

                        if (checkeddownload == BST_CHECKED and stat(dir, &sb) == 0)
                        {

                            fstream fileStream;
                            fileStream.open("C:\\CIS4ITM\\CIS-Inventory-Start.exe");
                            if (fileStream.fail())
                            {
                                DownloadFingerprinter();
                                ShowWindow(hwndtextbox4, SW_SHOW);
                                SetWindowText(hwndtextbox4, TEXT("Success: Client exe downloaded"));
                                Log(InfoP, "Client exe downloaded successfully", "Deployment Toolbox", __LINE__, "main");

                                // SetWindowText(hwndtextbox2, TEXT("\r\nClient exe downloaded successfully"));
                            }
                            else
                            {
                                ShowWindow(hwndtextbox4, SW_SHOW);
                                SetWindowText(hwndtextbox4, TEXT("\r\nWarning: Client exe already exists"));
                                Log(WarnP, "Client exe already exists", "Deployment Toolbox", __LINE__, "main");
                            }
                        }

                        if (checkeddownload == BST_UNCHECKED)
                        {
                            ShowWindow(hwndtextbox4, SW_HIDE);
                        }

                        if (checkedACL == BST_CHECKED and stat(dir, &sb) != 0)
                        {
                            ShowWindow(hwndtextbox5, SW_SHOW);
                            SetWindowText(hwndtextbox5, TEXT("\r\nWarning: Please create the C:\\CIS4ITM folder before setting the folder permission"));
                            Log(WarnP, "Please create the C:\\CIS4ITM folder before setting the folder permission", "Deployment Toolbox", __LINE__, "main");
                        }
                        fstream fileStream;
                        fileStream.open("C:\\CIS4ITM\\CIS-Inventory-Start.exe");
                        if (checkedACL == BST_CHECKED and fileStream.fail())
                        {
                            ShowWindow(hwndtextbox5, SW_SHOW);
                            SetWindowText(hwndtextbox5, TEXT("\r\nError: Please create C:\\CIS4ITM folder before setting the folder permissions"));
                            Log(InfoP, "Please create C:\\CIS4ITM folder before setting the folder permissions", "Deployment Toolbox", __LINE__, "main");
                        }
                        if (checkedACL == BST_CHECKED and !fileStream.fail())
                        {

                            TCHAR uservalue[255] = {0};
                            int idx_row10 = SendMessage(hwndtextbox7, WM_GETTEXT, 0, 0);
                            SendMessage(hwndtextbox7, WM_GETTEXT, idx_row10, (LPARAM)uservalue);
                            cout << idx_row10 << endl;

                            int len = GetWindowTextLengthW(GetDlgItem(hwnd, 21)) + 1;
                            wchar_t text[len];
                            GetWindowTextW(GetDlgItem(hwnd, 21), text, len);
                            wstring ws(text);
                            string str(ws.begin(), ws.end());
                            cout << str << endl;
                            string split = str.substr(str.find(":") + 1);
                            cout << split << endl;
                            // system(("net localgroup administrators" + split + " /add").c_str());
                            // cout << "net localgroup administrators" + split + " /add" << endl;

                            system("icacls C:\\CIS4ITM  /inheritance:d /remove:g *S-1-5-11");
                            system("icacls C:\\CIS4ITM  /inheritance:d /remove:g *S-1-5-11");
                            system("icacls C:\\CIS4ITM  /inheritance:d /remove:g "
                                   "Users");
                             system(("icacls C:\\CIS4ITM /grant "+split+ ":(OI)(CI)F /T").c_str());
                            system("cacls C:\\CIS4ITM  /inheritance:d /remove:g "
                                   "Users");

                            // system("for %A IN ("Authenticated Users" "Users" ) do @cacls C:\\CIS4ITM1 /e /c /d %~A:F");
                            ShowWindow(hwndtextbox5, SW_SHOW);
                            SetWindowText(hwndtextbox5, TEXT("\r\nSuccess: Folder permission is set"));
                            Log(InfoP,("User ID:"+split).c_str(), "Deployment Toolbox", __LINE__, "main");
                            Log(InfoP, "Folder permission set successfully", "Deployment Toolbox", __LINE__, "main");
                        }
                        if (checkedACL == BST_UNCHECKED)
                        {
                            ShowWindow(hwndtextbox5, SW_HIDE);
                        }

                        if (checkedschtask == BST_CHECKED and fileStream.fail())
                        {

                            ShowWindow(hwndtextbox9, SW_SHOW);
                            SetWindowText(hwndtextbox9, " Warning: Please download the client exe");
                            Log(WarnP, "Please download the client exe", "Deployment Toolbox", __LINE__, "main");
                        }

                        if (checkedschtask == BST_CHECKED and stat(dir, &sb) != 0)
                        {

                            ShowWindow(hwndtextbox9, SW_SHOW);
                            SetWindowText(hwndtextbox9, (Configurations::folderwarning).c_str());
                            Log(WarnP, "Please create C:\\CIS4ITM folder", "Deployment Toolbox", __LINE__, "main");
                        }

                        if (checkedschtask == BST_CHECKED and !fileStream.fail() and stat(dir, &sb) == 0)
                        {

                            TCHAR strText2[255] = {0};
                            int idx_row2 = SendMessage(hwndweekdays, CB_GETCURSEL, 0, 0);
                            SendMessage(hwndweekdays, CB_GETLBTEXT, idx_row2, (LPARAM)strText1);

                            SYSTEMTIME sts{};
                            SYSTEMTIME randomweekly{};
                            DateTime_GetSystemtime(hwnddatetTimer, &sts);
                            DateTime_GetSystemtime(hwndrandomtime, &randomweekly);
                            int Randomadv = Randomize(randomweekly.wMinute);
                            SYSTEMTIME stsweekly = add(sts, 60 * (Randomadv));

                            char buffers[256];
                            sprintf(buffers,
                                    "%02d:%02d",
                                    stsweekly.wHour,
                                    stsweekly.wMinute);
                            std::string strMessage1;
                            strMessage1 = buffers;
                            SYSTEMTIME stdaily{};

                            SYSTEMTIME stsm{};
                            SYSTEMTIME randommonthly{};
                            DateTime_GetSystemtime(hwndmonthlydatetTimer, &stsm);
                            DateTime_GetSystemtime(hwndrandomtime, &randommonthly);

                            SYSTEMTIME stsmonthly = add(stsm, 60 * (randommonthly.wMinute));

                            char buffersmon[256];
                            sprintf(buffersmon,
                                    "%02d:%02d",
                                    stsmonthly.wHour,
                                    stsmonthly.wMinute);
                            std::string strMessage7;
                            strMessage7 = buffersmon;

                            SYSTEMTIME randomdaily{};
                            DateTime_GetSystemtime(hwnddailydatetTimer, &stdaily);
                            DateTime_GetSystemtime(hwndrandomtime, &randomdaily);
                            SYSTEMTIME stsdaily = add(stdaily, 60 * (randomdaily.wMinute));

                            char bufferdaily[256];
                            sprintf(bufferdaily,
                                    "%02d:%02d",
                                    stsdaily.wHour,
                                    stsdaily.wMinute);
                            std::string strMessagedaily;
                            strMessagedaily = bufferdaily;
                            UINT checkeddaily = SendMessage(hwnddaily, BM_GETCHECK, 0, 0);
                            UINT checkedweekly = SendMessage(hwndweekly, BM_GETCHECK, 0, 0);
                            UINT checkedmonthly = SendMessage(hwndmonthly, BM_GETCHECK, 0, 0);
                            // time_t newTime = strMessagedaily + (60 * 10);

                            if (checkeddaily == 1)
                            {
                                system(("schtasks /create /sc daily /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessagedaily).c_str());
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, "Success: CIS4ITM_Package_execute task created");
                                   Log(InfoP, ("Schedule type:Daily,schedule time:"+strMessagedaily).c_str(), "Deployment Toolbox", __LINE__, "main");
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                            if (checkedweekly == 1)
                            {
                                if (idx_row2 == 0)
                                {

                                    system(("schtasks /create /sc weekly /D MON /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage1).c_str());
                                    ShowWindow(hwndtextbox9, SW_SHOW);
                                    SetWindowText(hwndtextbox9, (Configurations::tasksuccess).c_str());
                                       Log(InfoP, ("Schedule type:Weekly,Monday,schedule time:"+strMessage1).c_str(), "Deployment Toolbox", __LINE__, "main");
                                    Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                                }

                                if (idx_row2 == 1)
                                {

                                    system(("schtasks /create /sc weekly /D TUE /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage1).c_str());
                                    ShowWindow(hwndtextbox9, SW_SHOW);
                                    SetWindowText(hwndtextbox9, (Configurations::tasksuccess).c_str());
                                    Log(InfoP, ("Schedule type:Weekly,Tuesday,schedule time:"+strMessage1).c_str(), "Deployment Toolbox", __LINE__, "main");
                                    Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                                }
                                if (idx_row2 == 2)
                                {

                                    system(("schtasks /create /sc weekly /D WED /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage1).c_str());
                                    ShowWindow(hwndtextbox9, SW_SHOW);
                                    SetWindowText(hwndtextbox9, (Configurations::tasksuccess).c_str());
                                    Log(InfoP, ("Schedule type:Weekly,Wednesday,schedule time:"+strMessage1).c_str(), "Deployment Toolbox", __LINE__, "main");
                                    Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                                }
                                if (idx_row2 == 3)
                                {

                                    system(("schtasks /create /sc weekly /D THU /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage1).c_str());
                                    ShowWindow(hwndtextbox9, SW_SHOW);
                                    SetWindowText(hwndtextbox9, (Configurations::tasksuccess).c_str());
                                    Log(InfoP, ("Schedule type:Weekly,Thursday,schedule time:"+strMessage1).c_str(), "Deployment Toolbox", __LINE__, "main");
                                    Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                                }
                                if (idx_row2 == 4)
                                {

                                    system(("schtasks /create /sc weekly /D FRI /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage1).c_str());
                                    ShowWindow(hwndtextbox9, SW_SHOW);
                                    SetWindowText(hwndtextbox9, (Configurations::tasksuccess).c_str());
                                    Log(InfoP, ("Schedule type:Weekly,Friday,schedule time:"+strMessage1).c_str(), "Deployment Toolbox", __LINE__, "main");
                                    Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                                }
                            }
                            if (checkedmonthly == 1)
                            {
                                 SYSTEMTIME st{};
                              DateTime_GetSystemtime(hwndcalender, &st);
                              TCHAR buf[100]{};
                              wsprintf(buf, "%d",st.wDay);
                              //MessageBox(hwnd, buf, "Time", 0);

                                //  int idx_monthdate = SendMessage(hwndcalender, DTM_GETMONTHCAL, 0, 0);
                                //  TCHAR strTextdate[255] = {0};
                                // SendMessage(hwndcalender,CB_GETCURSEL, idx_monthdate, (LPARAM)strTextdate);
                                // strTextdate= DateTime_GetMonthCal(hwndcalender);
                                //cout << strTextdate << endl;
                                system(("schtasks /create /sc monthly /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /F /RU SYSTEM /ST " + strMessage7 + " /d " + buf).c_str());
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccess).c_str());
                                Log(InfoP, ("Schedule type:Monthly,schedule time:"+strMessage7+",scheduled date :"+buf).c_str(), "Deployment Toolbox", __LINE__, "main");
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }

                            UINT checkedstartupadv = SendMessage(hwndonstartadv, BM_GETCHECK, 0, 0);
                            if (checkedstartupadv == BST_CHECKED)
                            {
                                ShowWindow(hwnddatetTimer, SW_HIDE);
                                // EnableWindow(hwndrandomizeadv, FALSE);
                                EnableWindow(hwndrandomtime, FALSE);
                                ShowWindow(hwndrandomtime, SW_HIDE);
                                ShowWindow(hwndrandomtimede, SW_HIDE);
                                ShowWindow(hwnddailydatetTimer, SW_HIDE);
                                ShowWindow(hwndweekdays, SW_HIDE);
                                system("schtasks /create /tn CIS4ITM_Package_execute /tr C:\\CIS4ITM\\CIS-Inventory-Start.exe /sc onstart /F /RU SYSTEM /RL HIGHEST");
                                ShowWindow(hwndtextbox9, SW_SHOW);
                                SetWindowText(hwndtextbox9, (Configurations::tasksuccess).c_str());
                                Log(InfoP, "Schedule type:onstart", "Deployment Toolbox", __LINE__, "main");
                                Log(InfoP, "CIS4ITM_Package_execute task created successfully", "Deployment Toolbox", __LINE__, "main");
                            }
                        }

                        if (checkedschtask == BST_UNCHECKED)
                        {
                            ShowWindow(hwndtextbox9, SW_HIDE);
                        }
                    }

                    if (connection == 0)
                    {
                        if (checkedschtask == 1)
                        {
                            ShowWindow(hwndtextbox9, SW_SHOW);
                            SetWindowText(hwndtextbox9, (Configurations::taskfailed).c_str());
                            Log(ErrorP, "Task scheduling failed", "Deployment Toolbox", __LINE__, "main");
                        }
                        if (checkedschtask == 0)
                        {
                            ShowWindow(hwndtextbox9, SW_HIDE);
                        }
                        if (checkedconnection == 1)
                        {
                            ShowWindow(hwndtextbox2, SW_SHOW);
                            SetWindowText(hwndtextbox2, (Configurations::connectionfailed).c_str());
                            Log(ErrorP, "Connection to the CIS Server failed!", "Deployment Toolbox", __LINE__, "main");
                        }
                        if (checkedconnection == 0)
                        {
                            ShowWindow(hwndtextbox2, SW_HIDE);
                        }
                        if (checkedfolder == 1)
                        {
                            ShowWindow(hwndtextbox3, SW_SHOW);
                            SetWindowText(hwndtextbox3, (Configurations::skippedfailed).c_str());
                            Log(ErrorP, "Skipped due to failure", "Deployment Toolbox", __LINE__, "main");
                        }
                        if (checkedfolder == 0)
                        {
                            ShowWindow(hwndtextbox3, SW_HIDE);
                        }
                        if (checkeddownload == 1)
                        {
                            ShowWindow(hwndtextbox4, SW_SHOW);
                            SetWindowText(hwndtextbox4, (Configurations::skippedfailed).c_str());
                            Log(ErrorP, "Skipped due to failure", "Deployment Toolbox", __LINE__, "main");
                        }
                        if (checkeddownload == 0)
                        {
                            ShowWindow(hwndtextbox4, SW_HIDE);
                        }
                        if (checkedACL == 1)
                        {
                            ShowWindow(hwndtextbox5, SW_SHOW);
                            SetWindowText(hwndtextbox5, (Configurations::skippedfailed).c_str());
                            Log(ErrorP, "Skipped due to failure", "Deployment Toolbox", __LINE__, "main");
                        }
                        if (checkedACL == 0)
                        {
                            ShowWindow(hwndtextbox5, SW_HIDE);
                        }
                    }
                label:
                    break;
                }
            }
        }

        if (LOWORD(wParam) == ID_SCHTASK)
        {
            cout << "start the task creation" << endl;
            switch (HIWORD(wParam))
            {
            case BN_CLICKED:
                if (SendDlgItemMessage(hwnd, ID_SCHTASK, BM_GETCHECK, 0, 0))
                {
                    hwnddaily = CreateWindowEx(0, "BUTTON", "Daily", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                               25, 220, 70, 20, hwnd, (HMENU)ID_DAILY, NULL, NULL);
                    hwndweekly = CreateWindowEx(0, "BUTTON", "Weekly", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                                120, 220, 70, 20, hwnd, (HMENU)ID_WEEKLY, NULL, NULL);
                    hwndmonthly = CreateWindowEx(0, "BUTTON", "Monthly", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                                 230, 220, 70, 20, hwnd, (HMENU)ID_MONTHLY, NULL, NULL);

                    hwndonstartadv = CreateWindowEx(0, "BUTTON", "At Startup", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                                    350, 220, 130, 20, hwnd, (HMENU)ID_STARTUPADV, NULL, NULL);
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
                    ShowWindow(hwndmonthlydatetTimer, SW_HIDE);
                    ShowWindow(hwndcalender, SW_HIDE);
                }
            }
        }

        if (LOWORD(wParam) == ID_DAILY)
        {
            EnableWindow(hwndrandomtime, TRUE);
            ShowWindow(hwnddatetTimer, SW_HIDE);
            ShowWindow(hwndweekdays, SW_HIDE);
            ShowWindow(hwndmonthlydatetTimer, SW_HIDE);
            ShowWindow(hwndcalender, SW_HIDE);

            hwnddailydatetTimer = CreateWindowEx(                                                //
                /* Extended Style   */ 0,                                                        //
                /* Class Name       */ DATETIMEPICK_CLASS,                                       //
                /* Element Name     */ "DATE TIME ",                                             //
                /* Style            */ (WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | DTS_TIMEFORMAT), //
                /* X Position       */ 25,                                                       //
                /* Y Position       */ 250,                                                      //
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
            EnableWindow(hwndrandomtime, TRUE);
            ShowWindow(hwndmonthlydatetTimer, SW_HIDE);
            ShowWindow(hwndcalender, SW_HIDE);
            ShowWindow(hwnddailydatetTimer, SW_HIDE);
            hwndweekdays = CreateWindow("COMBOBOX", NULL,
                                        CBS_DROPDOWN | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
                                        25, 250, 130, 150, hwnd, (HMENU)ID_WEEKDAYS, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

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
                /* X Position       */ 170,                                                      //
                /* Y Position       */ 250,                                                      //
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
            EnableWindow(hwndrandomtime, TRUE);
            hwndmonthlydatetTimer = CreateWindowEx(                                              //
                /* Extended Style   */ 0,                                                        //
                /* Class Name       */ DATETIMEPICK_CLASS,                                       //
                /* Element Name     */ "DATE TIME ",                                             //
                /* Style            */ (WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | DTS_TIMEFORMAT), //
                /* X Position       */ 230,                                                      //
                /* Y Position       */ 250,                                                      //
                /* Width            */ 130,                                                      //
                /* Height           */ 30,                                                       //
                /* Parent Window    */ hwnd,                                                     //
                /* Menu             */ NULL,                                                     //
                /* Instance         */ NULL,                                                     //
                /* Parameter        */ NULL);
            DateTime_SetFormat(hwndmonthlydatetTimer, TEXT("HH:mm"));

            //    hwndcalender= CreateWindowEx(0,
            //                DATETIMEPICK_CLASS,
            //                 "Month Calendar",
            //                 WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_LONGDATEFORMAT,
            //                 500, 250, 150, 30,
            //                 NULL,
            //                 (HMENU) ID_CALENDER,
            //                 NULL,
            //                 NULL);
            hwndcalender = CreateWindowEx(0, MONTHCAL_CLASS, "Month Calendar",
                                          WS_BORDER | WS_CHILD | WS_VISIBLE | MCS_DAYSTATE | MCS_NOTODAYCIRCLE,
                                          390, 250, 250, 200, // resize it later
                                          hwnd,
                                          (HMENU)ID_CALENDER,
                                          NULL,
                                          NULL);
        }

        if (LOWORD(wParam) == ID_STARTUPADV)
        {
            ShowWindow(hwnddatetTimer, SW_HIDE);
            ShowWindow(hwndweekdays, SW_HIDE);
            ShowWindow(hwnddailydatetTimer, SW_HIDE);
            ShowWindow(hwnddailydatetTimer, SW_HIDE);
            ShowWindow(hwnddatetTimer, SW_HIDE);
            ShowWindow(hwndweekdays, SW_HIDE);
            EnableWindow(hwndrandomtime, FALSE);
            EnableWindow(hwndrandomtime, FALSE);
            ShowWindow(hwndmonthlydatetTimer, SW_HIDE);
            ShowWindow(hwndcalender, SW_HIDE);
        }

        // advanced german scheduling options
        if (LOWORD(wParam) == ID_SCHTASKDE)
        {
            cout << "start the task creation" << endl;
            switch (HIWORD(wParam))
            {
            case BN_CLICKED:
                if (SendDlgItemMessage(hwnd, ID_SCHTASKDE, BM_GETCHECK, 0, 0))
                {
                    hwnddailyde = CreateWindowEx(0, "BUTTON", (Configurations::dailyde).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                                 25, 220, 70, 20, hwnd, (HMENU)ID_DAILYDE, NULL, NULL);
                    hwndweeklyde = CreateWindowEx(0, "BUTTON", (Configurations::weeklyde).c_str(), WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                                  120, 220, 100, 20, hwnd, (HMENU)ID_WEEKLYDE, NULL, NULL);
                    hwndmonthlyde = CreateWindowEx(0, "BUTTON", "Monatlich", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                                   230, 220, 100, 20, hwnd, (HMENU)ID_MONTHLYDE, NULL, NULL);

                    hwndonstartadvde = CreateWindowEx(0, "BUTTON", "Am Anfang", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                                      350, 220, 130, 20, hwnd, (HMENU)ID_STARTUPADVDE, NULL, NULL);
                }
                else
                {
                    ShowWindow(hwnddailyde, SW_HIDE);
                    ShowWindow(hwndweeklyde, SW_HIDE);
                    ShowWindow(hwndmonthlyde, SW_HIDE);
                    ShowWindow(hwndonstartadvde, SW_HIDE);
                    ShowWindow(hwnddatetTimer, SW_HIDE);
                    ShowWindow(hwndweekdays, SW_HIDE);
                    ShowWindow(hwnddailydatetTimer, SW_HIDE);
                    ShowWindow(hwndmonthlydatetTimer, SW_HIDE);
                    ShowWindow(hwndcalender, SW_HIDE);
                }
            }
        }

        if (LOWORD(wParam) == ID_DAILYDE)
        {
            EnableWindow(hwndrandomtime, TRUE);
            ShowWindow(hwnddatetTimer, SW_HIDE);
            ShowWindow(hwndweekdays, SW_HIDE);
            ShowWindow(hwndmonthlydatetTimer, SW_HIDE);
            ShowWindow(hwndcalender, SW_HIDE);

            hwnddailydatetTimer = CreateWindowEx(                                                //
                /* Extended Style   */ 0,                                                        //
                /* Class Name       */ DATETIMEPICK_CLASS,                                       //
                /* Element Name     */ "DATE TIME ",                                             //
                /* Style            */ (WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | DTS_TIMEFORMAT), //
                /* X Position       */ 25,                                                       //
                /* Y Position       */ 250,                                                      //
                /* Width            */ 130,                                                      //
                /* Height           */ 30,                                                       //
                /* Parent Window    */ hwnd,                                                     //
                /* Menu             */ NULL,                                                     //
                /* Instance         */ NULL,                                                     //
                /* Parameter        */ NULL);
            DateTime_SetFormat(hwnddailydatetTimer, TEXT("HH:mm"));
        }

        if (LOWORD(wParam) == ID_WEEKLYDE)
        {
            EnableWindow(hwndrandomtime, TRUE);
            ShowWindow(hwndmonthlydatetTimer, SW_HIDE);
            ShowWindow(hwndcalender, SW_HIDE);
            ShowWindow(hwnddailydatetTimer, SW_HIDE);
            hwndweekdays = CreateWindow("COMBOBOX", NULL,
                                        CBS_DROPDOWN | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
                                        25, 250, 130, 150, hwnd, (HMENU)ID_WEEKDAYS, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

            SendMessage(hwndweekdays, CB_ADDSTRING, (WPARAM)0, (LPARAM) "Montag");
            SendMessage(hwndweekdays, (UINT)CB_ADDSTRING, (WPARAM)1, (LPARAM) "Dienstag");
            SendMessage(hwndweekdays, (UINT)CB_ADDSTRING, (WPARAM)2, (LPARAM) "Mittwoch");
            SendMessage(hwndweekdays, (UINT)CB_ADDSTRING, (WPARAM)3, (LPARAM) "Donnerstag");
            SendMessage(hwndweekdays, (UINT)CB_ADDSTRING, (WPARAM)4, (LPARAM) "Freitag");
            SendMessage(hwndweekdays, CB_SETCURSEL, NULL, (LPARAM) "Montag");
            hwnddatetTimer = CreateWindowEx(                                                     //
                /* Extended Style   */ 0,                                                        //
                /* Class Name       */ DATETIMEPICK_CLASS,                                       //
                /* Element Name     */ "DATE TIME ",                                             //
                /* Style            */ (WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | DTS_TIMEFORMAT), //
                /* X Position       */ 170,                                                      //
                /* Y Position       */ 250,                                                      //
                /* Width            */ 130,                                                      //
                /* Height           */ 30,                                                       //
                /* Parent Window    */ hwnd,                                                     //
                /* Menu             */ NULL,                                                     //
                /* Instance         */ NULL,                                                     //
                /* Parameter        */ NULL);
            DateTime_SetFormat(hwnddatetTimer, TEXT("HH:mm"));
        }

        if (LOWORD(wParam) == ID_MONTHLYDE)
        {
            ShowWindow(hwnddatetTimer, SW_HIDE);
            ShowWindow(hwndweekdays, SW_HIDE);
            ShowWindow(hwnddailydatetTimer, SW_HIDE);
            ShowWindow(hwnddailydatetTimer, SW_HIDE);
            ShowWindow(hwnddatetTimer, SW_HIDE);
            ShowWindow(hwndweekdays, SW_HIDE);
            EnableWindow(hwndrandomtime, TRUE);
            hwndmonthlydatetTimer = CreateWindowEx(                                              //
                /* Extended Style   */ 0,                                                        //
                /* Class Name       */ DATETIMEPICK_CLASS,                                       //
                /* Element Name     */ "DATE TIME ",                                             //
                /* Style            */ (WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | DTS_TIMEFORMAT), //
                /* X Position       */ 230,                                                      //
                /* Y Position       */ 250,                                                      //
                /* Width            */ 130,                                                      //
                /* Height           */ 30,                                                       //
                /* Parent Window    */ hwnd,                                                     //
                /* Menu             */ NULL,                                                     //
                /* Instance         */ NULL,                                                     //
                /* Parameter        */ NULL);
            DateTime_SetFormat(hwndmonthlydatetTimer, TEXT("HH:mm"));
            hwndcalender = CreateWindowW(L"Month Calendar", L"Month Calendar",
                                         WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                         230, 350, 150, 30, 0, 0, NULL, 0);
            hwndcalender = CreateWindowEx(0,
                                          DATETIMEPICK_CLASS,
                                          "Month Calendar",
                                          WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_LONGDATEFORMAT,
                                          500, 250, 150, 30,
                                          NULL,
                                          (HMENU)ID_CALENDER,
                                          NULL,
                                          NULL);
        }

        if (LOWORD(wParam) == ID_STARTUPADVDE)
        {
            ShowWindow(hwnddatetTimer, SW_HIDE);
            ShowWindow(hwndweekdays, SW_HIDE);
            ShowWindow(hwnddailydatetTimer, SW_HIDE);
            ShowWindow(hwnddailydatetTimer, SW_HIDE);
            ShowWindow(hwnddatetTimer, SW_HIDE);
            ShowWindow(hwndweekdays, SW_HIDE);
            EnableWindow(hwndrandomtime, FALSE);
            EnableWindow(hwndrandomtime, FALSE);
            ShowWindow(hwndmonthlydatetTimer, SW_HIDE);
            ShowWindow(hwndcalender, SW_HIDE);
        }

        if (LOWORD(wParam) == ID_COMBOlangde or LOWORD(wParam) == ID_COMBO or LOWORD(wParam) == ID_COMBODE)
        {
            int idx_rowde = SendMessage(hwndlangde, CB_GETCURSEL, 0, 0);
            TCHAR strText[255] = {0};
            SendMessage(hwndlangde, CB_GETLBTEXT, idx_rowde, (LPARAM)strText);
            TCHAR strTextde[255] = {0};
            int idx_rowdeadv = SendMessage(hwndcombode, CB_GETCURSEL, 0, 0);
            SendMessage(hwndcombode, CB_GETLBTEXT, idx_rowdeadv, (LPARAM)strTextde);
            TCHAR strTextcombo[255] = {0};
            int idx_rowcombo = SendMessage(hwndcombo, CB_GETCURSEL, 0, 0);
            SendMessage(hwndcombo, CB_GETLBTEXT, idx_rowcombo, (LPARAM)strTextcombo);
            if (idx_rowde == 0)
            {
                ShowWindow(hwndcombode, SW_SHOW);
                ShowWindow(hwndcombo, SW_HIDE);
            }
            if (idx_rowde == 1)
            {
                ShowWindow(hwndcombo, SW_SHOW);
                ShowWindow(hwndcombode, SW_HIDE);
            }
            if (idx_rowde == 0 and idx_rowdeadv == 0)
            {
                ShowWindow(hwndcombo, SW_HIDE);
                cout << "germandefault" << endl;
                ShowWindow(hwndconnectionde, SW_SHOW);
                ShowWindow(hwndquickweekdays, SW_HIDE);
                // ShowWindow(hwndquickdatetTimer, SW_HIDE);

                EnableWindow(hwndconnectionde, FALSE);
                ShowWindow(hwndconnection, SW_HIDE);
                SendMessage(hwndconnectionde, BM_SETCHECK, BST_CHECKED, 1);
                ShowWindow(hwndfolderde, SW_SHOW);
                ShowWindow(hwndfolder, SW_HIDE);
                EnableWindow(hwndfolderde, FALSE);
                SendMessage(hwndfolderde, BM_SETCHECK, BST_CHECKED, 1);
                ShowWindow(hwnddownloadde, SW_SHOW);
                EnableWindow(hwnddownloadde, FALSE);
                ShowWindow(hwnddownload, SW_HIDE);
                SendMessage(hwnddownloadde, BM_SETCHECK, BST_CHECKED, 1);
                ShowWindow(hwndACLde, SW_SHOW);
                EnableWindow(hwndACLde, FALSE);
                ShowWindow(hwndACL, SW_HIDE);
                SendMessage(hwndACLde, BM_SETCHECK, BST_CHECKED, 1);
                ShowWindow(hwndschtaskde, SW_SHOW);
                EnableWindow(hwndschtaskde, FALSE);
                ShowWindow(hwndschtask, SW_HIDE);
                SendMessage(hwndschtaskde, BM_SETCHECK, BST_CHECKED, 1);
                ShowWindow(hwndquickdatetTimer, SW_SHOW);
                // ShowWindow(hwndstartup, SW_SHOW);
                ShowWindow(hwndquickweekdaysde, SW_SHOW);
                ShowWindow(hwndquickweekdays, SW_HIDE);
                EnableWindow(hwndtextbox7, FALSE);
                EnableWindow(hwndtextbox8, FALSE);
                ShowWindow(hwndrandomizeadv, FALSE);
                ShowWindow(hwnddaily, SW_HIDE);
                ShowWindow(hwndweekly, SW_HIDE);
                ShowWindow(hwndmonthly, SW_HIDE);
                ShowWindow(hwndweekdays, SW_HIDE);
                ShowWindow(hwnddailydatetTimer, SW_HIDE);
                ShowWindow(hwnddatetTimer, SW_HIDE);
                ShowWindow(hwnddatetTimer, SW_HIDE);
                ShowWindow(hwnddailyde, SW_HIDE);
                ShowWindow(hwndweeklyde, SW_HIDE);
                ShowWindow(hwndmonthlyde, SW_HIDE);
                ShowWindow(hwndweekdays, SW_HIDE);
                ShowWindow(hwnddailydatetTimer, SW_HIDE);
                ShowWindow(hwnddatetTimer, SW_HIDE);
                ShowWindow(hwnddatetTimer, SW_HIDE);
                ShowWindow(hwndtextbox2, SW_HIDE);
                ShowWindow(hwndtextbox3, SW_HIDE);
                ShowWindow(hwndtextbox4, SW_HIDE);
                ShowWindow(hwndtextbox5, SW_HIDE);
                ShowWindow(hwndtextbox6, SW_HIDE);
                ShowWindow(hwndrandomizede, SW_SHOW);
                ShowWindow(hwndrandomize, SW_HIDE);
                SendMessage(hwndrandomizede, BM_SETCHECK, BST_CHECKED, 1);
                EnableWindow(hwndrandomizede, FALSE);
                ShowWindow(hwndtextbox10, SW_HIDE);
                ShowWindow(hwndrandomizeadvde, SW_HIDE);
                ShowWindow(hwndrandomtime, SW_HIDE);
                ShowWindow(hwndrandomtimede, SW_HIDE);
                ShowWindow(hwndonstartde, SW_SHOW);
                ShowWindow(hwndonstartadv, SW_HIDE);
                ShowWindow(hwndonstartadvde, SW_HIDE);
                ShowWindow(hwndschedule, SW_SHOW);
                ShowWindow(hwndonstartde, SW_SHOW);
                ShowWindow(hwndonstart, SW_HIDE);
                ShowWindow(hwndquickweekdays, SW_HIDE);
                SendMessage(hwndschedule, BM_SETCHECK, BST_CHECKED, 1);
                SendMessage(hwndonstartde, BM_SETCHECK, BST_UNCHECKED, 1);
                // EnableWindow(hwndtextbox12, FALSE);
                ShowWindow(hwndstart, SW_SHOW);
                ShowWindow(hwndmonthlydatetTimer, SW_HIDE);
                ShowWindow(hwndcalender, SW_HIDE);
                ShowWindow(hwndonstart, SW_HIDE);
                EnableWindow(hwndtextbox15, FALSE);
                ShowWindow(hwndtextboxde, SW_SHOW);
                ShowWindow(hwndtextbox, SW_HIDE);
            }
            else if (idx_rowde == 0 and idx_rowdeadv == 1)
            {
                ShowWindow(hwndcombo, SW_HIDE);
                ShowWindow(hwndcombode, SW_SHOW);
                cout << "german adv" << endl;
                ShowWindow(hwndconnection, SW_HIDE);
                EnableWindow(hwndconnectionde, TRUE);
                ShowWindow(hwndconnectionde, SW_SHOW);
                SendMessage(hwndconnectionde, BM_SETCHECK, BST_UNCHECKED, 1);
                ShowWindow(hwndfolder, SW_HIDE);
                EnableWindow(hwndfolderde, TRUE);
                ShowWindow(hwndfolderde, SW_SHOW);
                SendMessage(hwndfolderde, BM_SETCHECK, BST_UNCHECKED, 1);
                ShowWindow(hwnddownload, SW_HIDE);
                EnableWindow(hwnddownloadde, TRUE);
                ShowWindow(hwnddownloadde, SW_SHOW);
                SendMessage(hwnddownloadde, BM_SETCHECK, BST_UNCHECKED, 1);
                ShowWindow(hwndACL, SW_HIDE);
                EnableWindow(hwndACLde, TRUE);
                ShowWindow(hwndACLde, SW_SHOW);
                SendMessage(hwndACLde, BM_SETCHECK, BST_UNCHECKED, 1);
                ShowWindow(hwndschtask, SW_HIDE);
                EnableWindow(hwndschtaskde, TRUE);
                ShowWindow(hwndschtaskde, SW_SHOW);
                SendMessage(hwndschtaskde, BM_SETCHECK, BST_UNCHECKED, 1);
                ShowWindow(hwndquickdatetTimer, SW_HIDE);
                ShowWindow(hwndonstart, SW_HIDE);
                ShowWindow(hwndquickweekdaysde, SW_HIDE);
                EnableWindow(hwndtextbox7, TRUE);
                EnableWindow(hwndtextbox8, TRUE);
                ShowWindow(hwndtextbox9, SW_HIDE);
                ShowWindow(hwndrandomizede, FALSE);
                ShowWindow(hwndtextbox10, SW_SHOW);
                EnableWindow(hwndtextbox10, FALSE);
                ShowWindow(hwndrandomizeadvde, TRUE);
                ShowWindow(hwndrandomizeadv, FALSE);
                // EnableWindow(hwndrandomizeadvde, FALSE);
                ShowWindow(hwndrandomtime, SW_HIDE);
                ShowWindow(hwndrandomtimede, SW_SHOW);
                EnableWindow(hwndrandomtime, TRUE);
                ShowWindow(hwndonstartde, SW_HIDE);
                ShowWindow(hwndschedule, SW_HIDE);
                // EnableWindow(hwndtextbox12, TRUE);
                ShowWindow(hwndstart, SW_SHOW);
                ShowWindow(hwndquickweekdays, SW_HIDE);
                ShowWindow(hwnddaily, SW_HIDE);
                ShowWindow(hwndweekly, SW_HIDE);
                ShowWindow(hwndmonthly, SW_HIDE);
                ShowWindow(hwnddailyde, SW_HIDE);
                ShowWindow(hwndweeklyde, SW_HIDE);
                ShowWindow(hwndmonthlyde, SW_HIDE);
                ShowWindow(hwndweekdays, SW_HIDE);
                ShowWindow(hwnddailydatetTimer, SW_HIDE);
                ShowWindow(hwnddatetTimer, SW_HIDE);
                ShowWindow(hwnddatetTimer, SW_HIDE);
                ShowWindow(hwndmonthlydatetTimer, SW_HIDE);
                ShowWindow(hwndcalender, SW_HIDE);
                ShowWindow(hwndonstartadv, SW_HIDE);
                ShowWindow(hwndonstartadvde, SW_HIDE);
                EnableWindow(hwndtextbox15, TRUE);
                ShowWindow(hwndtextboxde, SW_SHOW);
                ShowWindow(hwndtextbox, SW_HIDE);
            }
            else if (idx_rowde == 1 and idx_rowcombo == 0)
            {
                ShowWindow(hwndcombode, SW_HIDE);
                cout << "english default" << endl;
                EnableWindow(hwndtextbox15, FALSE);
                ShowWindow(hwndtextbox, SW_SHOW);
                ShowWindow(hwndtextboxde, SW_HIDE);
                ShowWindow(hwndquickweekdaysde, SW_HIDE);
                // ShowWindow(hwndquickdatetTimerde, SW_HIDE);
                ShowWindow(hwndconnection, SW_SHOW);
                EnableWindow(hwndconnection, FALSE);
                ShowWindow(hwndconnectionde, SW_HIDE);
                SendMessage(hwndconnection, BM_SETCHECK, BST_CHECKED, 1);
                ShowWindow(hwndfolder, SW_SHOW);
                ShowWindow(hwndfolderde, SW_HIDE);
                EnableWindow(hwndfolder, FALSE);
                SendMessage(hwndfolder, BM_SETCHECK, BST_CHECKED, 1);
                ShowWindow(hwnddownload, SW_SHOW);
                EnableWindow(hwnddownload, FALSE);
                ShowWindow(hwnddownloadde, SW_HIDE);
                SendMessage(hwnddownload, BM_SETCHECK, BST_CHECKED, 1);
                ShowWindow(hwndACL, SW_SHOW);
                EnableWindow(hwndACL, FALSE);
                ShowWindow(hwndACLde, SW_HIDE);
                SendMessage(hwndACL, BM_SETCHECK, BST_CHECKED, 1);
                ShowWindow(hwndschtask, SW_SHOW);
                EnableWindow(hwndschtask, FALSE);
                ShowWindow(hwndschtaskde, SW_HIDE);
                SendMessage(hwndschtask, BM_SETCHECK, BST_CHECKED, 1);
                ShowWindow(hwndquickdatetTimer, SW_SHOW);
                // ShowWindow(hwndstartup, SW_SHOW);
                ShowWindow(hwndquickweekdays, SW_SHOW);
                EnableWindow(hwndtextbox7, FALSE);
                EnableWindow(hwndtextbox8, FALSE);
                ShowWindow(hwnddaily, SW_HIDE);
                ShowWindow(hwndweekly, SW_HIDE);
                ShowWindow(hwndmonthly, SW_HIDE);
                ShowWindow(hwnddailyde, SW_HIDE);
                ShowWindow(hwndweeklyde, SW_HIDE);
                ShowWindow(hwndmonthlyde, SW_HIDE);
                ShowWindow(hwndweekdays, SW_HIDE);
                ShowWindow(hwnddailydatetTimer, SW_HIDE);
                ShowWindow(hwnddatetTimer, SW_HIDE);
                ShowWindow(hwnddatetTimer, SW_HIDE);
                ShowWindow(hwndtextbox2, SW_HIDE);
                ShowWindow(hwndtextbox3, SW_HIDE);
                ShowWindow(hwndtextbox4, SW_HIDE);
                ShowWindow(hwndtextbox5, SW_HIDE);
                ShowWindow(hwndtextbox9, SW_HIDE);
                ShowWindow(hwndtextbox6, SW_HIDE);
                ShowWindow(hwndrandomize, SW_SHOW);
                ShowWindow(hwndrandomizede, SW_HIDE);
                SendMessage(hwndrandomize, BM_SETCHECK, BST_CHECKED, 1);
                EnableWindow(hwndrandomize, FALSE);
                ShowWindow(hwndtextbox10, SW_HIDE);
                ShowWindow(hwndrandomizeadv, SW_HIDE);
                ShowWindow(hwndrandomtime, SW_HIDE);
                ShowWindow(hwndrandomtimede, SW_HIDE);
                ShowWindow(hwndonstart, SW_SHOW);
                ShowWindow(hwndonstartadv, SW_HIDE);
                ShowWindow(hwndonstartadvde, SW_HIDE);
                ShowWindow(hwndschedule, SW_SHOW);
                ShowWindow(hwndonstart, SW_SHOW);
                ShowWindow(hwndonstartde, SW_HIDE);
                ShowWindow(hwndquickweekdaysde, SW_HIDE);
                ShowWindow(hwndquickweekdays, SW_SHOW);
                SendMessage(hwndschedule, BM_SETCHECK, BST_CHECKED, 1);
                SendMessage(hwndonstart, BM_SETCHECK, BST_UNCHECKED, 1);
                // EnableWindow(hwndtextbox12, FALSE);
                ShowWindow(hwndstart, SW_SHOW);
                ShowWindow(hwndmonthlydatetTimer, SW_HIDE);
                ShowWindow(hwndcalender, SW_HIDE);
                ShowWindow(hwndrandomizeadvde, SW_HIDE);
            }
            else if (idx_rowde == 1 and idx_rowcombo == 1)
            {
                ShowWindow(hwndcombode, SW_HIDE);
                ShowWindow(hwndcombo, SW_SHOW);
                cout << "english adv" << endl;
                EnableWindow(hwndconnection, TRUE);
                ShowWindow(hwndconnectionde, SW_HIDE);
                ShowWindow(hwndconnection, SW_SHOW);
                ShowWindow(hwndtextbox, SW_SHOW);
                ShowWindow(hwndtextboxde, SW_HIDE);
                SendMessage(hwndconnection, BM_SETCHECK, BST_UNCHECKED, 1);
                ShowWindow(hwndfolderde, SW_HIDE);
                EnableWindow(hwndfolder, TRUE);
                ShowWindow(hwndfolder, SW_SHOW);
                SendMessage(hwndfolder, BM_SETCHECK, BST_UNCHECKED, 1);
                ShowWindow(hwnddownloadde, SW_HIDE);
                ShowWindow(hwnddownload, SW_SHOW);
                EnableWindow(hwnddownload, TRUE);
                SendMessage(hwnddownload, BM_SETCHECK, BST_UNCHECKED, 1);
                ShowWindow(hwndACLde, SW_HIDE);
                ShowWindow(hwndACL, SW_SHOW);
                EnableWindow(hwndACL, TRUE);
                SendMessage(hwndACL, BM_SETCHECK, BST_UNCHECKED, 1);
                ShowWindow(hwndschtaskde, SW_HIDE);
                ShowWindow(hwndschtask, SW_SHOW);
                EnableWindow(hwndschtask, TRUE);
                SendMessage(hwndschtask, BM_SETCHECK, BST_UNCHECKED, 1);
                ShowWindow(hwndquickdatetTimer, SW_HIDE);
                ShowWindow(hwndonstart, SW_HIDE);
                ShowWindow(hwndquickweekdays, SW_HIDE);
                EnableWindow(hwndtextbox7, TRUE);
                EnableWindow(hwndtextbox8, TRUE);
                ShowWindow(hwndrandomize, FALSE);
                ShowWindow(hwndtextbox10, SW_SHOW);
                EnableWindow(hwndtextbox10, FALSE);
                ShowWindow(hwndrandomizeadv, TRUE);
                // EnableWindow(hwndrandomizeadv, FALSE);
                ShowWindow(hwndrandomtime, SW_SHOW);
                ShowWindow(hwndrandomtimede, SW_HIDE);
                EnableWindow(hwndrandomtime, TRUE);
                ShowWindow(hwndonstart, SW_HIDE);
                ShowWindow(hwndschedule, SW_HIDE);
                // EnableWindow(hwndtextbox12, TRUE);
                ShowWindow(hwndstart, SW_SHOW);
                ShowWindow(hwndquickweekdays, SW_HIDE);
                ShowWindow(hwndrandomizeadvde, SW_HIDE);
                ShowWindow(hwndrandomizeadv, SW_SHOW);
                ShowWindow(hwndrandomizeadv, TRUE);
                ShowWindow(hwndonstartadv, SW_HIDE);
                EnableWindow(hwndtextbox15, TRUE);
                ShowWindow(hwndtextbox2, SW_HIDE);
                ShowWindow(hwndtextbox3, SW_HIDE);
                ShowWindow(hwndtextbox4, SW_HIDE);
                ShowWindow(hwndtextbox5, SW_HIDE);
                ShowWindow(hwndtextbox9, SW_HIDE);
            }
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}
