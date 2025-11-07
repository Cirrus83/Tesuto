#pragma once
#include<iostream>
#include<vector>
#include<random>
static std::random_device rd;
static std::mt19937 mersenne(rd());
static std::minstd_rand0 lcg(rd());
static std::ranlux24_base ranlux(rd());
int randomize(int a)// 不同的随机数引擎
{
    std::uniform_int_distribution<int> dist(1, 2222);
    if(a==1)
	return dist(lcg);
    if(a==2)
	return dist(ranlux);
	return dist(mersenne);
}
int kurikaesu(std::vector<std::string>&cmd)
{
	std::string line;
    int n=0;
    if(cmd.size()>=2)
    line=cmd[1];
    else
    {
        std::cout<<"kurikaesu: Input a line:"<<std::endl;
        std::getline(std::cin,line);
    }
    if(cmd.size()>=3)
    {
        try
        {
            n=stoi(cmd[2]);
        }
        catch(std::invalid_argument&e)
        {
            n=randomize(0);
        }
        catch(std::out_of_range&e)
        {
            n=randomize(0);
        }
    }
    else
    n=randomize(0);
    for(int i=0;i<n;i++)
    std::cout<<line;
    std::cout<<std::endl;
    return 0;
}