#pragma once
#include<iostream>
#include<cmath>
#include<iomanip>
int gpaRescuer()
{
	double a=0;
	char y;
	int n=0;
	std::cout<<"gpaRescuer: 规则：每捞一次，分数开平方根再乘10。"<<std::endl;
	tryagain:
	std::cout<<"gpaRescuer: 多少分？捞几次？"<<std::endl;
	if(!(std::cin>>a>>n)||a<0||a>100||n<1)
	{
		std::cout<<"gpaRescuer: 这不对吧？"<<std::endl;
		std::cin.clear();
		std::cin.ignore(10000,'\n');
		return 1;
	}
	else
	{
		for(int i=0;i<n;i++)
		{
			a=10*sqrt(a);
			if(a==100)
			break;
		}
		std::cout<<"gpaRescuer: 捞完后："<<std::fixed<<std::setprecision(6)<<a<<"分"<<std::endl;
		if(a>=60)
		std::cout<<"gpaRescuer: 捞好了o(^▽^)o"<<std::endl;
		else
		{
			std::cout<<"gpaRescuer: 再捞捞？(y/n)";
			std::cin>>y;
			std::cin.ignore(10000,'\n');
			if(y=='y'||y=='Y')
			goto tryagain;
		}
	}
	return 0;
}