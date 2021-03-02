
#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <fstream>

class Record {
  public:
    Record();
    Record(std::fstream &empin);
    void WriteRecord(std::fstream &empout);
    std::string ToString();
    bool IsValid();
    int GetEid();

  private:
    int eid;
    std::string ename;
    int age;
    std::string salary;

};

void SortRecords(Record records[], int num);

int PullRecords(Record blocks[], int num, std::fstream &empIn);

void PrintRecords(Record records[], int num);

void WriteRecords(Record records[], int num, int level, int run);


#endif
