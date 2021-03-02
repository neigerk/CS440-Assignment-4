#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Record.h"

using namespace std;
const int M = 22;
const string outputfile = "OUTPUT";


int main(){
  fstream empIn;
  empIn.open("Emp.csv", ios::in);
  int level = 0;
  int run = 0;
  int prevRuns = 0;
  //int prevRecords = 0;
  Record blocks[M];
  bool flag = true;

  //Pass 0
  while (flag) {
    int numRecords = PullRecords(blocks, M, empIn);
    if (numRecords < M){
      flag = false;
    }
    SortRecords(blocks, numRecords);
    //PrintRecords(blocks, numRecords);
    WriteRecords(blocks, numRecords, level, run);
    run++;
  }
  empIn.close();
  //Setting up for pass i
  prevRuns = run;
  run = 0;
  level++;
  //prevRecords = M;

  //ALL RUNS
  while (prevRuns > 1){
    int currRun = 0;
    //Pass i
    while (currRun < prevRuns){
      fstream infile[M-1];
      int remaining = prevRuns - currRun;
      int low = (M-1) * run;
      for (currRun; currRun < low + (M-1); currRun++){
        if (currRun == prevRuns) break;
        stringstream ss;
        ss << level - 1 << "r" << currRun;
        infile[currRun-low].open(ss.str(), ios::in);
        blocks[currRun-low] = Record(infile[currRun-low]);
      }
      stringstream out;
      out << level << "r" << run;
      fstream outfile;
      outfile.open(out.str(), ios::out);

      //int newRecords = prevRecords * (M-1);
      //Write smallest record

      blocks[M-1] = blocks[0];
      while(1){

        int smallestPlace;
        for (int i = 0; i < M-1 && i < remaining; i++){
          if (blocks[i].IsValid()){
            if (blocks[i].GetEid() < blocks[M-1].GetEid()){
              blocks[M-1] = blocks[i];
              smallestPlace = i;
            }
            if (!blocks[M-1].IsValid()){
              blocks[M-1] = blocks[i];
              smallestPlace = i;
            }
          }
        }
        if (blocks[M-1].IsValid()){
          blocks[M-1].WriteRecord(outfile);
          blocks[smallestPlace] = Record(infile[smallestPlace]);
          blocks[M-1] = Record();
        } else {
          break;
        }
      }

      //close files
      for (int i = 0; i < M-1 && i < remaining; i++){
        infile[i].close();
      }
      outfile.close();
      run++;
    }
    prevRuns = run;
    run = 0;
    level++;
  }


  stringstream s;
  s << level - 1 << "r" << run;
  //cout << s.str();
  fstream lastrun;
  lastrun.open(s.str(), ios::in);
  fstream sorted;
  sorted.open(outputfile, ios::out);
  blocks[M-1] = Record(lastrun);
  while(blocks[M-1].IsValid()){
    blocks[M-1].WriteRecord(sorted);
    blocks[M-1] = Record(lastrun);
  }
  lastrun.close();
  sorted.close();
}
