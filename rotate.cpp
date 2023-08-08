#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include<iostream>
#include <filesystem>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sstream>


using namespace std;

int main() {
  int count;
  vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
  cout << "Original vector: ";
  for (int x: vec)
    cout << x << " ";

     std::filesystem::path p1 { "C:/CIS4ITM/Logs/" };
    for (auto& p : std::filesystem::directory_iterator(p1))
  {
    
     ++count;
   }

  
  cout << endl;

  std::string path = "C:/CIS4ITM/Logs/";

if(count>=0 && count<10) {
    //std::string filename = "Log" + std::to_string(vec) + ".txt";
   std::string filename = "Log" + std::to_string(count) + ".txt";
     std::ofstream file(path + filename,std::ios_base::app);
    file <<"DATE|TIME|LINE|FUNCTION|COMPONENT|SEVERITY|MESSAGE\n";
     file.close();
}
else{

  rotate(vec.begin(), vec.begin() + 0, vec.end());
  cout << "Rotated vector: ";
  for (int x: vec)
    cout << x << " ";

}
  return 0;
}