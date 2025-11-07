#pragma once
#include"02_main.h"
std::string compress(std::string ori)
{
	using namespace std;
	bool zr=1;
	int i=0,cnt=0;
	vector<string>templates{"0000:0000:0000:0000:0000:0000:0000:0000","0000:0000:0000:0000:0000:0000:0000","0000:0000:0000:0000:0000:0000","0000:0000:0000:0000:0000","0000:0000:0000:0000","0000:0000:0000","0000:0000","0000"};
	for(i=0;i<8;i++)
	if(ori.find(templates[i])!=string::npos)break;
	if(ori.find(templates[i])!=string::npos)
	ori.erase(ori.find(templates[i]),templates[i].size());
	if(ori.size()==0)
	return "::";
	else if(ori[0]==':')
	ori.insert(ori.begin(),':');
	else if(ori[ori.size()-1]==':')
	ori+=':';
	for(i=0;i<ori.size();i++)
	{
		if(i>=ori.size());
		else if(ori[i]==':')
		zr=1;
		else if(ori[i]>='1'&&ori[i]<='9'||ori[i]>='a'&&ori[i]<='f'||cnt==3)
		{
			zr=0;
			cnt=0;
		}
		else if(ori[i]=='0'&&zr)
		{
			ori.erase(i,1);
			i--;
			cnt++;
		}
		else
		{
			cout<<"ipv6prob: Invalid input!"<<endl;
			return {};
		}
	}
	return ori;
}
int ipv6prob(std::vector<std::string>&cmd)
{
	using namespace std;
	string in;
	vector<string>result;
	if(cmd.size()>1&&safestoi(cmd[1])>0)
	{
		int n=safestoi(cmd[1]),i=0;
		for(i=0;i<n;i++)
		{
			cin>>in;
			if(in.size()!=39)
			goto ipv6error;
			else
			result.push_back(compress(in));
		}
		for(i=0;i<result.size();i++)
		cout<<"ipv6prob: The result is "<<result[i]<<endl;
	}
	else
	getline(cin,in);
	if(in.size()!=39)
	goto ipv6error;
	else
	{
		cout<<"ipv6prob: The result is "<<compress(in)<<endl;
		return 0;
	}
	ipv6error:
	cout<<"ipv6prob: Invalid input!"<<endl;
	return 1;
}