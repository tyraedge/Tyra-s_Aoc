#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

namespace Day8
{
  struct DigitPatterns
  {
    vector<string> signals;
    vector<string> output;
    vector<string> numbers = std::vector<string>(10);
    DigitPatterns(string line);
    void AddSignal(string num);
    int SolvePattern();
    void SolveSignals();
  };

  DigitPatterns::DigitPatterns(string lin)
  {
    std::stringstream line(lin);
    string left;
    string right;
    string num;
    getline(line, left, '|');
    getline(line, right);

    std::stringstream signal(left);
    while (signal >> num)
    {
      if (num.size() == 2)
      {
        numbers[1] = num;
      }
      else if (num.size() == 4)
      {
        numbers[4] = num;
      }
      else if (num.size() == 7)
      {
        numbers[8] = num;
      }
      else if (num.size() == 3)
      {
        numbers[7] = num;
      }
      else
      {
        signals.push_back(num);
      }
    }

    std::stringstream out(right);
    while (out >> num)
    {
      output.push_back(num);
    }
  }

  int compare(string num1, string num2){
    int count=0;
    for(int i=0; i< num1.size();i++){
      bool equal = false;
      for(int j=0;j<num2.size();j++){
        if(num1[i] == num2[j]){ equal = true; }
      }
      if(!equal) count++;
    }
    return count;
  }

  int DigitPatterns::SolvePattern()
  {
    string solution="";
    for (int i = 0; i < 4; i++)
    {
      if (output[i].size() == 2)
      {
        solution+='1';
      }
      else if (output[i].size() == 4)
      {
        solution+='4';
      }
      else if (output[i].size() == 7)
      {
        solution+='8';
      }
      else if (output[i].size() == 3)
      {
        solution+='7';
      }else if (output[i].size() == 6)
      {
        int four_compare = compare(numbers[4], output[i]);
        int one_compare = compare(numbers[1], output[i]);

        if(one_compare==1){
          solution+='6';
        }else if(four_compare==0){
          solution+='9';
        }else{
          solution+='0';
        }
      }else if (output[i].size() == 5)
      {

        int four_compare = compare(numbers[4], output[i]);
        int one_compare = compare(numbers[1], output[i]);

        if(one_compare==0){
          solution+='3';
        }else if(four_compare==2){
          solution+='2';
        }else{
          solution+='5';
        }
      }
    }
    return stoi(solution);
  }

  void start()
  {
    ifstream file;
    file.open("../Text Files/day8_input.txt");
    string line;
    int count = 0;
    while (getline(file, line))
    {
      DigitPatterns digits(line);
      int sol = digits.SolvePattern();
      printf("%d\n", sol);
      count += sol;
    }
    printf("%d", count);
  }
}

int main()
{
  Day8::start();
}