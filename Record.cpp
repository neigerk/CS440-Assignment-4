#include <iostream>
#include "Record.h"
#include <string>
#include <sstream>

using namespace std;

Record::Record()
  :eid(-1), ename(""), age(0), salary("0.0")
{}

Record::Record(std::fstream &empin){
  string line, word;
  //empin.seekg()
  if (getline(empin, line, '\n')){
    stringstream ss(line);
    getline(ss, word, ',');
    eid = stoi(word);

    getline(ss, word, ',');
    ename = word;

    getline(ss, word, ',');
    age = stoi(word);

    getline(ss, word, ',');
    salary = word;
  } else {
    eid = -1;
  }
}

void Record::WriteRecord(std::fstream &empout){
  empout << ToString();
}

std::string Record::ToString(){
  std::stringstream ss;
  ss << eid << "," << ename << "," << age << "," << salary << "\n";
  return ss.str();
}

bool Record::IsValid(){
  if (eid == -1){
    return false;
  } else {
    return true;
  }
}

int Record::GetEid(){
  return eid;
}

void SortRecords(Record records[], int num){
  for(int place = 0; place < num; place++){
    int lowestEid = records[place].GetEid();
    int lowestPlace = place;
    //Find next lowest value
    for (int check = place; check < num; check++){
      if (records[check].GetEid() < lowestEid){
        lowestEid = records[check].GetEid();
        lowestPlace = check;
      }
    }
    //swap records
    Record temp = records[place];
    records[place] = records[lowestPlace];
    records[lowestPlace] = temp;
  }
}

int PullRecords(Record blocks[], int num, fstream &empIn){
  for (int i = 0; i < num; i++){
    blocks[i] = Record(empIn);
    if (!blocks[i].IsValid()){
      return i;
    }
  }
  return num;
}

void PrintRecords(Record records[], int num){
  for (int i = 0; i < num; i ++){
    cout << records[i].ToString();
  }
}

void WriteRecords(Record records[], int num, int level, int run){
  stringstream ss;
  ss << level << "r" << run;
  fstream runfile;
  runfile.open(ss.str(), ios::out);
  for (int i = 0; i < num; i++){
    records[i].WriteRecord(runfile);
  }
  runfile.close();

}
