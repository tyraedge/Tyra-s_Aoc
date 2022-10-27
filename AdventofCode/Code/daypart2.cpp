/*
* File: day1.cpp
  First Three Days of Advent of Code 
  https://adventofcode.com/2021/
*/

#include<iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>
#include <numeric>
using namespace std;

namespace Day1 {
    struct Measurements{
        std::vector<std::vector<int>> measurements;
        void add(int num);
        void finish();
        void print();
    };
    void Day1::Measurements::add(int num){
        if(measurements.size() != 0){
            for(int i=0; i<measurements.size();i++){
                if(measurements[i].size()!=3){
                    measurements[i].push_back(num);
                }
            }
        }
        vector<int> vect{num};
        measurements.push_back(vect);
    }

    void Day1::Measurements::finish(){
        int prev_sum = accumulate(measurements[0].begin(), measurements[0].end(), 0);
        int count=0;
        for(int i=1; i<measurements.size();i++){
            int cur_sum=accumulate(measurements[i].begin(), measurements[i].end(), 0);
            // printf("%d", cur_sum);
            if(cur_sum>prev_sum){
                count++;
            }
            prev_sum = cur_sum;
        }
        printf("%d", count);
    }

    void Day1::Measurements::print(){
        for (int i=0 ;i<measurements.size();i++){
            for (int j=0 ;j<measurements[i].size();j++){
                printf("%d ", measurements[i][j]);
            }
            printf("\n");
        }
    }

    void start(){
        ifstream file;
        file.open("day1_input.txt");
        std::string s;
        struct Measurements m;
        while(getline(file, s)){
            int num = stoi(s);
            m.add(num);
        }
        m.finish();
        // m.print();
        file.close();
    }
}

namespace Day2{
    struct Move{
        std::string dir;
        int count;
    };

    struct Coordinates{
        int x=0;
        int y=0;
        int aim=0;
        void move(Move m);
    };

    void Day2::Coordinates::move(Day2::Move m){
        if(m.dir == "up"){
            aim -= m.count;
        }else if(m.dir == "down"){
            aim += m.count;
        }else{
            x += m.count;
            y+= (aim*m.count);
        }
    }

    void start(){
        std::ifstream file("day2_input.txt");
        std::string str;
        int i;
        struct Coordinates cord;
        while(file >> str >> i){
            struct Move m;
            m.dir = str; m.count = i;
            cord.move(m);
        }
        printf("%d\n", cord.x * cord.y);
        file.close();
    }
}

namespace Day3{
    struct Pipeline{
        std::vector<std::string> vect = std::vector<std::string>(12);
        std::vector<std::string> oxygen;
        std::vector<std::string> C02;
        void add(std::string);
        void print();
        char mostCommon(int);
        char leastCommon(int);
        void getVars();
    };
    void Day3::Pipeline::add(std::string number){
        for (int i=0 ;i<12;i++){
            vect[i] += number[i];
        }
        oxygen.push_back(number);
        C02.push_back(number);
    }

    void Day3::Pipeline::print(){
        for (int i=0 ;i<vect.size();i++){
            printf("%s\n", vect[i].c_str());
        }
    }

    char Day3::Pipeline::mostCommon(int pos){
        int ones = 0;
        int zeros = 0;
        for(int i=0;i<oxygen.size();i++){
            if(oxygen[i][pos] == '1'){ ones++;}
            if(oxygen[i][pos] == '0'){ zeros++;}
        }
        return (ones >= zeros)?'1':'0';
    }

    char Day3::Pipeline::leastCommon(int pos){
        int ones = 0;
        int zeros = 0;
        for(int i=0;i<C02.size();i++){
            if(C02[i][pos] == '1'){ ones++;}
            if(C02[i][pos] == '0'){ zeros++;}
        }
        return (ones >= zeros)?'0':'1';
    }

    void Day3::Pipeline::getVars(){
        int i=0;
        // printf("%d",oxygen.size());
        while(oxygen.size()>1){
            char mc = mostCommon(i);
            // printf("%c %d\n",mc, i);
            auto it = oxygen.begin();
            // printf("before\n");
            while(it!=oxygen.end()){
                if(mc!=(*it)[i]){
                    oxygen.erase(it);
                }else{
                    it++;
                }
            }
            // printf("after\n");
            i++;
        }
        printf("\n%d\n",stoi(*(oxygen.begin()), 0, 2));
        printf("\n%s\n",oxygen.begin()[0].c_str());

        i=0;
        while(C02.size()>1){
            char lc = leastCommon(i);
            auto it = C02.begin();
            // printf("%d",C02.size());
            while(it!=C02.end()){
                if(lc!=(*it)[i]){
                    C02.erase(it);
                }else{
                    it++;
                }
            }
            i++;
        }
        // printf("%d",C02.size());
        printf("\n%d\n",stoi(*(C02.begin()), 0, 2));
        printf("\n%s\n",C02.begin()[0].c_str());
        printf("\n%d\n",stoi(*(C02.begin()), 0, 2)*stoi(*(oxygen.begin()), 0, 2));
    }

    void start(){
        std::ifstream file("day3_input.txt");
        std::string str;
        struct Pipeline pipe;
        while(getline(file, str)){
            //printf("%s\n", str.c_str());
            pipe.add(str);
        }
        pipe.getVars();
        // printf("%d", pipe.gamma*pipe.epsilon);
        file.close();
    }
}

int main(){
    Day3::start();
}