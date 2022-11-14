#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>
#include <numeric>
using namespace std;

namespace Day5 {
struct Coord{
    int x;
    int y;
    Coord(int x1, int y1){
        x = x1;
        y = y1;
    }
    bool vertical(const Coord& p){
        return x == p.x;
    }
    bool horizontal(const Coord& p){
        return y == p.y;
    }
    bool diagnol(const Coord& p){
        return abs(y - p.y) == abs(x - p.x);
    }
};

struct Board{
    std::vector<std::vector<int>> grid = std::vector<std::vector<int>> ( 100000 , vector<int> (100000, 0));
    int count =0;
    void add(Coord p1, Coord p2);
};

void Day5::Board::add(Coord p1, Coord p2){
        if(p1.vertical(p2)){
            int y1= p1.y>p2.y ? p2.y:p1.y;
            int y2 = p1.y<p2.y ? p2.y:p1.y;
            for(int i=y1; i<=y2;i++ ){
                grid[p1.x][i]++;
                if(grid[p1.x][i] == 2){
                    count++;
                }
            }
        }else if(p1.horizontal(p2)){
            int x1= p1.x>p2.x ? p2.x:p1.x;
            int x2 = p1.x<p2.x ? p2.x:p1.x;
            for(int i=x1; i<=x2;i++ ){
                grid[i][p1.y]++;
                if(grid[i][p1.y] == 2) count ++;
            }
        }else if(p1.diagnol(p2)){
            int inc_x = p1.x>p2.x? -1:1; 
            int inc_y = p1.y>p2.y? -1:1;
            for(int i=0;i<= abs(p1.x-p2.x);i++){
                grid[inc_x*i+p1.x][inc_y*i+p1.y]++;
                if(grid[inc_x*i+p1.x][inc_y*i+p1.y] ==2) count++;
            }
        }else{
            return;
        }
    }

void start(){
    ifstream file;
    file.open("../Text Files/day5_input.txt");
    struct Board board;
    printf("%d\n", board.grid[0][0]);
    int x1; int y1;
    int x2; int y2;
    char c; std::string s;
    while(file >> x1 >> c>> y1 >> s>> x2>> c>>y2&&c==','&&s=="->"){
        struct Coord p1(x1, y1);
        struct Coord p2(x2, y2);
        board.add(p1, p2);
    }
    printf("%d\n",board.count);
    for(int i=0; i< 10;i++){
        for(int j=0; j< 10;j++){
            if(board.grid[j][i]==0) printf(" . ");
            else printf(" %d ", board.grid[j][i]);
    }
    printf("\n");
    }
}
}

int main(){
    Day5::start();
}