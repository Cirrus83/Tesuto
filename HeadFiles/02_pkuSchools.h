#pragma once
#include"02_jigai.h"
int xk(std::vector<std::string>&cmd)
{
	using namespace std;
	if(cmd.size()==1)
	cout<<"xk: 暂时不能给你明确的答复。这需要你自己衡量。"<<endl;
	else if(cmd[1]=="0")
	{
		cout<<"xk:"<<endl;
		return openTxt("02_xk_00");
	}
	else if(cmd[1]=="1")
	{
		cout<<"xk:"<<endl;
		return openTxt("02_xk_01");
	}
	return 0;
}