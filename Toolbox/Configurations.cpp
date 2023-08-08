#include <string>
#include <iostream>
#include "Dep/Configurations.h"
using namespace std;

string Configurations:: connectionCheckerURL="http://10.35.42.249:8081/CIS4ITM/api/CIS/GetScriptFileNames";//(Connection checker API URL)
//string Configurations:: connectionCheckerURL="http://10.73.65.135:8081/CIS4ITM/api/CIS/GetScriptFileNames";//(Connection checker API URL)
string Configurations:: fingerprinterURL="http://10.3.149.150:84/api/CIS4ITM/DownloadFile?fileName=CIS-Inventory-Start.exe";//(Finger printer download URL)
string Configurations:: fingerprinter="CIS-Inventory-Start.exe";
//string Configurations:: scheduletask= ("Anusf"+"ü"+"hrung plane").c_str();

string Configurations:: logFolderName="Logs";
string Configurations:: option="Options:";
string Configurations:: optionde="Optionen:";
string Configurations:: defaulten="Default";
string Configurations:: defaultde="Standardeinstellungen";
string Configurations:: advanced="Advanced";
string Configurations:: advancedde="Erweitert";
string Configurations:: german="Deutsch (de)";
string Configurations:: english="English (en)";
string Configurations:: connection="1. Check connection";
string Configurations:: connectionde="1. Verbindung testen";
string Configurations:: folder="2. Create folder";
string Configurations:: folderde="2. Verzeichnis anlegen";
string Configurations:: download="3. Download client";
string Configurations:: ACL="4. Set local folder permissions";
string Configurations:: downloadde="3. Client herunter laden";
string Configurations:: ACLde="4. Lokale Zugriffsrechte auf Ordner anpassen                                                                             C:\\CIS4ITM";
string Configurations:: schedule="5. Schedule task";   
string Configurations:: weekday1="Monday";
string Configurations:: weekday2="Tuesday";
string Configurations:: weekday3="Wednesday";
string Configurations:: weekday4="Thursday";
string Configurations:: weekday5="Friday";
string Configurations:: weekdayde1="Montag";
string Configurations:: weekdayde2="Dienstag";
string Configurations:: weekdayde3="Mittwoch";
string Configurations:: weekdayde4="Donnerstag";
string Configurations:: weekdayde5="Freitag";
string Configurations:: randomize="Randomize start +- 15 Min";
string Configurations:: randomizeadv="Randomize start (mins)";
string Configurations:: randomizede="Startzeitpunkt per Zufallswert modifizieren +-15 Min";
string Configurations:: randomizeadvde="Startzeitpunkt per Zufallswert modifizieren(Min)";
//string Configurations:: randomizeadvde="Startzeitpunkt per ";
string Configurations:: textbox11="min";
string Configurations:: onstart="At startup";
string Configurations:: onstartde="Beim Windows-Start";
string Configurations:: start="Start!";
string Configurations:: textbox8="C:\\CIS4ITM";
string Configurations::textbox15="C:\\CIS4ITM";
string Configurations::taskfailed="Failure: Task scheduling failed";
string Configurations::connectionfailed="Failure: Connection to the CIS Server failed!";
string Configurations::skippedfailed="Failure: Skipped due to failure";
string Configurations::connectionsuccess="Success: Connection to the CIS server";
string Configurations::tasksuccess="Success: CIS4ITM_Package_execute task created";
string Configurations::folderexists="Warning: Folder already exists";
string Configurations::foldersuccess="Success: Folder created";
string Configurations::folderfailure="Failure: Unable to create folder";
string Configurations::folderwarning="Error: Please create C:\\CIS4ITM folder first";
string Configurations::folderwarningde="Fehler: Bitte erstellen Sie zuerst den C:\\CIS4ITM-Ordner";
string Configurations::taskfailedde="Fehler: Aufgabenplanung fehlgeschlagen";
string Configurations::connectionfailedde="Fehler: Verbindung zum CIS-Server fehlgeschlagen!";
string firstde = "Fehler: Wegen Fehler ";
string lastde = "bersprungen";
char asciide = char(252);
//string Configurations::skippedfailedde="Fehler: Wegen Fehler übersprungen";
string Configurations::skippedfailedde=firstde + asciide + lastde;
string Configurations::connectionsuccessde="Erfolg: Die Verbindung zum CIS-Server ist erfolgreich";
string Configurations::folderexistsde="Erfolg: Ordner existiert bereits";
string Configurations::foldersuccessde="Erfolg: Ordner erfolgreich erstellt";
string Configurations::folderfailurede="Fehler: Ordner kann nicht erstellt werden";
string Configurations::tasksuccessde="Erfolg: Die Aufgabe CIS4ITM_Package_execute wurde erfolgreich erstellt";
string Configurations::showlog="Show log file";
string firstdaily="T";
string lastdaily="glich";
char asciidaily = char(228);
string Configurations::dailyde=firstdaily+asciidaily+lastdaily;
string firstweekly="W";
string lastweekly="chentlich";
char asciiweekly = char(246);
string Configurations::weeklyde=firstweekly+asciiweekly+lastweekly;
string Configurations::monthlyde="Monatlich";



