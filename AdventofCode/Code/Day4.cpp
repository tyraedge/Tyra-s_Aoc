/*
* File: 
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
#include <numeric>
using namespace std;

namespace Day4 {
    struct Number{
        int number;
        bool called;
        Number(int num){
            number = num;
            called = false;
        }
    };
    struct Bingo{
        std::vector<std::vector<std::vector<Number>>> boards;
        std::vector<int> numbers;
        int current_number;
        void addBall(int number);
        void addNumbertoBoards(int number);
        bool isBingo(int i, int j, int k);
        bool callBall(int num);
        int sumBoard(int i);
        void print();
        void start();
    };

    void Day4::Bingo::addBall(int number){
        numbers.push_back(number);
    }

    void Day4::Bingo::addNumbertoBoards(int num){
        int lastBoardNum = boards.size() - 1;
        //add a new board when all boards are empty or the previous is full
        struct Number number(num);
        if(lastBoardNum == -1){
            std::vector<std::vector<Number>> new_board{{number}};
            boards.push_back(new_board);
        } else {
            int lastColumnNum = boards[lastBoardNum].size()-1;
            if(lastColumnNum == 4 && boards[lastBoardNum][lastColumnNum].size()==5){
                std::vector<std::vector<Number>> new_board{{number}};
                boards.push_back(new_board);
            } else if(boards[lastBoardNum][lastColumnNum].size() == 5){ //add a new row when previous is full
                std::vector<Number> new_row{number};
                boards[lastBoardNum].push_back(new_row);
            } else { //add a number to an existing row in a board
                boards[lastBoardNum][lastColumnNum].push_back(number);
            }
        }
    }

    void Day4::Bingo::print(){
        printf("Bingo Balls: ");
        for(int i=0; i<numbers.size();i++){ printf("%d ", numbers[i]);}
        printf("\n");
        printf("Bingo Boards:\n");
        for(int i=0;i<boards.size();i++){
            for(int j=0;j<boards[i].size();j++){
                for(int k=0;k<boards[i][j].size();k++){
                    printf("%d ",boards[i][j][k].number);
                }
                printf("\n");
            }
            printf("\n\n");
        }
    }

    int Day4::Bingo::sumBoard(int i){
        int sum = 0;
        for(int j=0;j<5;j++){
            for(int k=0;k<5;k++){
                if(!boards[i][j][k].called)
                    sum += boards[i][j][k].number;
            }
        }
        return sum;
    }

    bool Day4::Bingo::isBingo(int i, int j, int k){
        int rows = 0;
        int rows_sum = 0;
        int columns = 0;
        int columns_sum = 0;
        for(int p = 0; p<5;p++){
            if(boards[i][j][p].called){
                columns++;
            }
            if(boards[i][p][k].called){
                rows++;
            }
        }
        return rows ==5 || columns ==5;
    }

    bool Day4::Bingo::callBall(int num){
        for(int i=0;i<boards.size();i++){
            for(int j=0;j<boards[i].size();j++){
                for(int k=0;k<boards[i][j].size();k++){
                    if(boards[i][j][k].number == num){
                        boards[i][j][k].called = true;
                        if(isBingo(i, j, k)){
                            printf("found Bingo: %d!!!\n", sumBoard(i)*num);
                            printf("%d %d %d", i, j, k);
                            return true;
                        }
                    }
                }
            }
            
        }
        return false;
    }

    void Day4::Bingo::start(){
        for(int i=0;i<numbers.size();i++){
            if(callBall(numbers[i])){
                break;
            }
        }
    }

    void start(){
        ifstream file;
        file.open("../Text Files/day4_input.txt");
        int num;
        file >> num;
        struct Bingo bingo;
        bingo.addBall(num);
        char c;
        while(file >> c >> num && c == ','){
            bingo.addBall(num);
        }
        bingo.addNumbertoBoards(num);
        while(file >> num){
            bingo.addNumbertoBoards(num);
        }
        bingo.start();
        //bingo.print();
    }
}

int main(){
    Day4::start();
}