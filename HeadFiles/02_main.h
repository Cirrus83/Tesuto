#pragma once
#include<iostream>
#include<stdexcept>
#include<string>
#include<vector>
int safestoi(std::string input)
{
	int result=0;
    try
	{
        result=std::stoi(input);
        return result;
    }
	catch(std::invalid_argument&e)
	{
        return 0;
    }
	catch(std::out_of_range&e)
	{
        return 0;
    }
}
std::vector<std::string> processCmd(std::string il)
{
	std::vector<std::string>result;
	std::string tmp;
	int i=0;
	while(i<=il.size())
	{
		if(i==il.size()||il[i]==' ')
		{
			if(!tmp.empty())
			{
				result.push_back(tmp);
				tmp.clear();
			}
			i++;
		}
		else
		{
			tmp+=il[i];
			i++;
		}
	}
	return result;
}
void exec(int code)
{
	using namespace std;
	cout<<"main: Program exited with code "<<code<<'.'<<endl<<"~~ ";
}