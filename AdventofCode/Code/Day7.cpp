#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

namespace Day7{
    struct AssembleCrabs{
        std::vector<int> crabs;
        std::vector<int> pos_baselines;
        std::vector<int> fuel_by_steps;
        void AddCrab(int num);
        int FindRightPositions();
    };

    void AssembleCrabs::AddCrab(int num){
        // printf("num: %d ",num);
        crabs.push_back(num);
        if(pos_baselines.size()<=num){
            if(pos_baselines.size() == 0)
                for(int i=0;i<=num;i++){
                    pos_baselines.push_back(0);
                    fuel_by_steps.push_back( (i==0)? 0: fuel_by_steps[i-1]+i);
                }
            else
                // printf("second: %d sum before: %d ",pos_baselines.size(), fuel_by_steps[i-1]);
                for(int i=pos_baselines.size();i<=num;i++){
                    pos_baselines.push_back(0); 
                    int size = fuel_by_steps.size();
                    fuel_by_steps.push_back(fuel_by_steps[size-1]+size);
                }  
        }
        
    }

    int AssembleCrabs::FindRightPositions(){
        for(int i=0;i<pos_baselines.size();i++){
            for(int j=0;j<crabs.size();j++){
                pos_baselines[i]+= fuel_by_steps[abs(crabs[j] - i)];
            }
        }
        return *min_element(pos_baselines.begin(), pos_baselines.end());
    }

    void start(){
        ifstream file;
        file.open("../Text Files/day7_input.txt");
        int num;
        file >> num;
        struct AssembleCrabs assembly;
        assembly.AddCrab(num);
        char c;
        while(file >> c >> num && c == ','){
            assembly.AddCrab(num);
        }
        printf("%d\n", assembly.fuel_by_steps[assembly.pos_baselines.size()-1]);
        printf("%d", assembly.FindRightPositions());
    }
}

int main(){
    Day7::start();
}