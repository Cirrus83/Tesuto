#include"HeadFiles.h"
using namespace std;
int main()
{
	vector<string> cmd;
	string inputLine;
	cout<<"\u{001B}[2J\u{001B}[H"<<endl<<"main: Launched."<<endl<<"~~ ";
	getline(cin,inputLine);
	for(;;)
	{
		if(!inputLine.empty())
		{
			cmd=processCmd(inputLine);
			if(cmd.empty())goto inputCmd_02;
			else if(cmd[0]=="alarm")cout<<"alarm: Sorry, under development."<<endl<<"~~ ";
			else if(cmd[0]=="clear")cout<<"\u{001B}[2J\u{001B}[H"<<endl<<"~~ ";
			else if(cmd[0]=="exit"||cmd[0]=="quit")break;
			else if(cmd[0]=="gcd")exec(printGcd(cmd));
			else if(cmd[0]=="gparescuer")exec(gpaRescuer());
			else if(cmd[0]=="hello")cout<<"hello: Hello World!"<<endl<<"~~ ";
			else if(cmd[0]=="help")exec(printHelp());
			else if(cmd[0]=="inverse")exec(inverse(cmd));
			else if(cmd[0]=="ipv6prob")exec(ipv6prob(cmd));
			else if(cmd[0]=="kurikaesu")exec(kurikaesu(cmd));
			else if(cmd[0]=="manual")exec(manualInverseMode());
			else if(cmd[0]=="version")exec(printVer());
			else cout<<"main: Undefined command "<<"\""<<cmd[0]<<"\""<<endl<<"~~ ";
		}
		else
		inputCmd_02:
		cout<<"~~ ";
		getline(cin,inputLine);
	}
	cout<<"main: Ended.";
	return 0;
}