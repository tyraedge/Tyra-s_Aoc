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

namespace Day6
{
    struct FishFamily
    {
        // Vector of Pairs: each # in the pairs rep. the # of fish with the same # days left as the index in the vector
        // first index in pair is the # before the day starts and the second is after the day ends.
        vector<pair<unsigned long long, unsigned long long>> DaysLefttoNumFish;
        int days_left = 256;
        FishFamily()
        {
            for (int i = 0; i <= 8; i++)
            {
                DaysLefttoNumFish.push_back(make_pair(0, 0));
            }
        }
        void AddFish(int days_for_fish);
        void NextDays();
        void ChangeCycle();
        unsigned long long Populate();
        unsigned long long SumFish();
        void PrintFish();
    };

    void FishFamily::AddFish(int days_for_fish)
    {
        DaysLefttoNumFish[days_for_fish].first++;
    }

    void FishFamily::ChangeCycle()
    {
        for (int i = 0; i <= 8; i++)
        {
            DaysLefttoNumFish[i].first = DaysLefttoNumFish[i].second;
            DaysLefttoNumFish[i].second = 0;
        }
    }

    void FishFamily::NextDays()
    {
        int days_til_turnover = -1;
        for (int rem_days = 0; rem_days <= 8; rem_days++)
        {
            unsigned long long num_of_fish_before_day_start = DaysLefttoNumFish[rem_days].first;
            // skip if there are no fish with that number of remaining days
            if (num_of_fish_before_day_start == 0)
            {
                continue;
            }
            // Get the fish with the least amount of days and fast forward to when those fish turnsover
            // unless the days ends before that fish turnsover
            if (days_til_turnover == -1)
            {
                days_til_turnover = rem_days + 1;
                DaysLefttoNumFish[6].second += num_of_fish_before_day_start;
                DaysLefttoNumFish[8].second += num_of_fish_before_day_start;
                continue;
            }
            // printf("before: %d ",DaysLefttoNumFish[rem_days-days_til_turnover].second);
            DaysLefttoNumFish[rem_days - days_til_turnover].second += num_of_fish_before_day_start;
        }
        // printf("min %d ", days_til_turnover);
        ChangeCycle();
        days_left -= days_til_turnover;
    }

    unsigned long long FishFamily::Populate()
    {
        while (days_left > 0)
        {
            NextDays();
            // PrintFish();
        }
        return SumFish();
    }

    unsigned long long FishFamily::SumFish()
    {
        unsigned long long sum = 0;
        for (int i = 0; i <= 8; i++)
        {
            sum += DaysLefttoNumFish[i].first;
        }
        return sum;
    }

    void FishFamily::PrintFish()
    {
        printf("%d: ", 256 - days_left);
        for (int i = 0; i <= 8; i++)
            for (int j = 0; j < DaysLefttoNumFish[i].first; j++)
                printf("%d, ", i);
        printf("\n");
    }

    void start()
    {
        ifstream file;
        file.open("day6_input.txt");
        int num;
        file >> num;
        struct FishFamily family;
        // family.PrintFish();
        family.AddFish(num);
        char c;
        while (file >> c >> num && c == ',')
        {
            family.AddFish(num);
        }
        // family.PrintFish();
        printf("%llu\n", family.Populate());
        // family.PrintFish();
    }
}

int main()
{
    Day6::start();
}