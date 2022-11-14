/*
* File: day1.cpp
  First Day of Advent of Code 
  https://adventofcode.com/2021/day/1
*/

#include<iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

namespace Day1 {
    void start(){
        ifstream file;
        file.open("../Text Files/day1_input.txt");
        std::string s;
        getline(file, s);
        int previous_num = stoi(s);
        printf("%d: (N/A)\n", previous_num);
        int count = 0;
        while(getline(file, s)){
            int current_num = stoi(s);
            if(current_num > previous_num){
                //printf("%d: (increased)\n", current_num);
                count++;
            }else{
                //printf("%d: (decreased)\n", current_num);
            }
            previous_num = current_num;
        }
        printf("There are %d measurements that are larger than the previous measurement.", count);
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
        int mult;
        void move(Move m);
    };

    void Day2::Coordinates::move(Day2::Move m){
        if(m.dir == "up"){
            y -= m.count;
        }else if(m.dir == "down"){
            y+= m.count;
        }else{
            x += m.count;
        }
    }

    void start(){
        std::ifstream file("../Text Files/day2_input.txt");
        std::string str;
        int i;
        struct Coordinates cord;
        while(file >> str >> i){
            struct Move m;
            m.dir = str; m.count = i;
            cord.move(m);
        }
        printf("%d", cord.x * cord.y);
        file.close();
    }
}

namespace Day3{
    struct Pipeline{
        std::vector<std::string> vect = std::vector<std::string>(12);
        int gamma;
        int epsilon;
        void add(std::string);
        void print();
        char mostCommon(std::string);
        void getVars();
    };
    void Day3::Pipeline::add(std::string number){
        for (int i=0 ;i<12;i++){
            vect[i] += number[i];
        }
    }

    void Day3::Pipeline::print(){
        for (int i=0 ;i<vect.size();i++){
            printf("%s\n", vect[i].c_str());
        }
    }

    char Day3::Pipeline::mostCommon(std::string str){
        int ones = 0;
        int zeros = 0;
        for(int i=0;i<str.size();i++){
            if(str[i] == '1'){ ones++;}
            if(str[i] == '0'){ zeros++;}
        }
        return (ones > zeros)?'1':'0';
    }

    void Day3::Pipeline::getVars(){
        std::string gam;
        std::string eps;

        for(int i=0;i<vect.size();i++){
            char mc = mostCommon(vect[i]);
            gam += mc;
            char lc = mc=='1'? '0':'1';
            eps += lc;
        }
        printf("%s %s\n", gam.c_str(), eps.c_str());
        gamma = stoi(gam, 0, 2);
        epsilon = stoi(eps, 0, 2);
        printf("%d %d\n", gamma, epsilon);
    }

    void start(){
        std::ifstream file("../Text Files/day3_input.txt");
        std::string str;
        struct Pipeline pipe;
        while(getline(file, str)){
            //printf("%s\n", str.c_str());
            pipe.add(str);
        }
        pipe.getVars();
        printf("%d", pipe.gamma*pipe.epsilon);
        file.close();
    }
}

int main(){
    Day3::start();
}