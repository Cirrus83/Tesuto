#pragma once
#include"02_probs.h"
void runTest(std::string num)
{
	using namespace std;
	if(num=="02_0")prob02_0();
}
int openTxt(std::string filename)
{
	using namespace std;
	std::ifstream file;
	if(filename.size()<=3||filename.substr(0,3)!="02_")
	{
		std::cout<<"txt: 请输入绝对路径，包含后缀名："<<endl;
		cin>>filename;
		file.open(filename);
	}
	else
	file.open("Documents/"+filename+".txt");
    std::string line;
    if(file.is_open())
	{
        while(std::getline(file,line))
		std::cout<<line<< std::endl;
        file.close();
		return 0;
    }
	else
	{
		std::cout << "txt: 无法打开文件！请检查文件名，或使用绝对路径。" << std::endl;
		return 1;
	}
}
int txtReader(std::vector<std::string>& cmd)
{
	using namespace std;
	if(cmd.size()<2)
	{
		cout<<"txt: 请指定文件名。"<<endl;
		string namae;
		cin>>namae;
		return openTxt(namae);
	}
	else return openTxt(cmd[1]);
}
int programmingGrid()
{
	using namespace std;
	string num;
	cout<<"grid: 欢迎使用北京大学编程网格！"<<endl<<"grid: 当前题集：";
	gridList:
	if(openTxt("02_ProblemSet"))
	{
		cout<<"grid: 题集打开失败。"<<endl;
		return 1;
	}
	else
	{
		cout<<"grid: 输入序号来选择："<<endl;
		cin>>num;
		if(openTxt(num))
		{
			cout<<"grid: 题目打开失败。"<<endl;
			return 1;
		}
		else
		{
			cout<<"grid: 输入\"back\"返回，输入\"y\"运行示例程序，输入其他退出grid。"<<endl;
			string line;
			cin>>line;
			if(line=="back")
			goto gridList;
			else if(line=="y")
			runTest(num);
		}	
	}
	return 0;
}
