#pragma once
#include<sstream>
#include"02_main.h"
std::vector<int> gcdProcessInput(std::string il)
{
	std::vector<int>result;
	std::string tmp;
	int i=0,n=0;
	bool ind=0;
	while(i<=il.size())
	{
		if(i==il.size()||il[i]==' ')
		{
			if(!tmp.empty())
			{
				try
				{
					n=std::stoi(tmp);
				}
				catch(std::invalid_argument&e)
				{
					ind=1;
				}
				catch(std::out_of_range&e)
				{
					ind=1;
				}
				if(!ind)
				result.push_back(n);
				tmp.clear();
				ind=0;
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
std::vector<int> safeMatrixRead_bunshi(std::string il)//分子は「ぶんし」です、分母は「ぶんぼ」です。
{
    std::vector<int> result;
    std::string tmp;
    int i = 0;
    bool afterSlash = false; // 标记是否在斜杠之后（分母部分）
    
    while (i <= il.size())
    {
        if (i == il.size() || il[i] == ' ') // 遇到空格或字符串结束
        {
            if (!tmp.empty() && !afterSlash) // 只处理分子部分
            {
                result.push_back(stoi(tmp)); // 忽略符号，直接取数值
            }
            tmp.clear();
            afterSlash = false; // 重置斜杠标记
            i++;
        }
        else if (il[i] == '/') // 遇到分数分隔符
        {
            if (!tmp.empty() && !afterSlash) // 处理分子部分
            {
                result.push_back(stoi(tmp)); // 忽略符号，直接取数值
            }
            tmp.clear();
            afterSlash = true; // 标记进入分母部分
            i++;
        }
        else if (il[i] == '-') // 遇到负号，直接跳过
        {
            i++;
        }
        else if (il[i] >= '0' && il[i] <= '9') // 数字
        {
            tmp += il[i];
            i++;
        }
        else // 非法字符
        {
            return {};
        }
    }
    
    return result;
}
std::vector<int> safeMatrixRead_bunbo(std::string il)//分子は「ぶんし」です、分母は「ぶんぼ」です。
{
    std::vector<int> result;
    std::string tmp;
    int i = 0;
    bool inFraction = false;  // 标记是否在分数部分
    
    while (i <= il.size())
    {
        if (i == il.size() || il[i] == ' ') // 遇到空格或字符串结束
        {
            if (!tmp.empty())
            {
                if (inFraction) 
                {
                    // 分数情况：只放入分母（不考虑符号）
                    result.push_back(stoi(tmp));
                    inFraction = false;
                }
                else 
                {
                    // 整数情况：都变成1（忽略符号）
                    result.push_back(1);
                }
                tmp.clear();
            }
            i++;
        }
        else if (il[i] == '/') // 遇到分数分隔符
        {
            if (tmp.empty() || inFraction) 
            {
                // 无效的分数格式：连续两个"/"或者"/"前面没有数字
                return {};
            }
            // 分子部分处理完毕，不放入结果，只清空准备处理分母
            tmp.clear();
            inFraction = true;
            i++;
        }
        else if (il[i] == '-') // 遇到负号，直接跳过
        {
            i++;
        }
        else if (il[i] >= '0' && il[i] <= '9') // 数字
        {
            tmp += il[i];
            i++;
        }
        else // 非法字符
        {
            return {};
        }
    }
    
    return result;
}
std::vector<bool> safeMatrixRead_isNegative(std::string il)//符号を読み取る
{
    std::vector<bool> result;
    std::string tmp;
    int i = 0;
    bool hasNegative = false;
    bool inFraction = false;  // 标记是否在分数部分
    bool isNumber = false;    // 标记当前是否有数字
    
    while (i <= il.size())
    {
        if (i == il.size() || il[i] == ' ') // 遇到空格或字符串结束
        {
            if (isNumber && !inFraction) // 只有分子部分的数字才记录符号
            {
                result.push_back(hasNegative);
            }
            tmp.clear();
            hasNegative = false;
            inFraction = false;
            isNumber = false;
            i++;
        }
        else if (il[i] == '/') // 遇到分数分隔符
        {
            if (isNumber && !inFraction) // 分子部分结束，记录符号
            {
                result.push_back(hasNegative);
            }
            tmp.clear();
            hasNegative = false;
            inFraction = true;  // 进入分母部分
            isNumber = false;
            i++;
        }
        else if (il[i] == '-') // 遇到负号
        {
            if (!tmp.empty() || hasNegative) 
            {
                // 负号不在数字开头或者已经有负号了，格式错误
                return {};
            }
            hasNegative = true;
            i++;
        }
        else if (il[i] >= '0' && il[i] <= '9') // 数字
        {
            tmp += il[i];
            isNumber = true;
            i++;
        }
        else // 非法字符
        {
            return {};
        }
    }
    
    return result;
}
std::string formatNumber(int bunshi, int bunbo, bool isNegative)
{
    std::stringstream ss;
    std::string result;
    
    if (isNegative && bunshi != 0) {
        ss << "-";
    }
    
    // 如果分子为0，直接输出0，忽略分母
    if (bunshi == 0) {
        ss << "0";
    } else {
        ss << bunshi;
        if (bunbo != 1) {
            ss << "/" << bunbo;
        }
    }
    
    result = ss.str();
    if (result.size() < 10) {
        result.insert(0, 10 - result.size(), ' ');
    }
    return result;
}
void printManualMatrix(const std::vector<std::vector<int>>& bunshi_left, const std::vector<std::vector<int>>& bunbo_left, 
                      const std::vector<std::vector<bool>>& sign_left,
                      const std::vector<std::vector<int>>& bunshi_right, const std::vector<std::vector<int>>& bunbo_right,
                      const std::vector<std::vector<bool>>& sign_right, int step) {
    std::cout << "manual: Step " << step << " is:" << std::endl;
    
    int n = bunshi_left.size();
    
    for (int i = 0; i < n; i++) {
        std::string line;
        // 打印原矩阵部分
        for (int j = 0; j < n; j++) {
            line += formatNumber(bunshi_left[i][j], bunbo_left[i][j], sign_left[i][j]);
        }
        line += "    |    "; // 分隔符
        // 打印单位矩阵部分
        for (int j = 0; j < n; j++) {
            line += formatNumber(bunshi_right[i][j], bunbo_right[i][j], sign_right[i][j]);
        }
        std::cout << i << "~(" << line << ')' << std::endl;
    }
}
int gcd(int a, int b) 
{
	while(b!=0)
	{
		int temp=b;
    	b=a%b;
    	a=temp;
	}
	return a;
}
void autogcdSquareMatrix(std::vector<std::vector<int>>&bunshi,std::vector<std::vector<int>>&bunbo)//需保证输入的是方阵，否则程序出错。
{
	int n=bunshi.size(),gcdnum=0;
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	{
		// 如果分子为0，设置分母为1
		if(bunshi[i][j] == 0) {
			bunbo[i][j] = 1;
			continue; // 跳过gcd计算
		}
		gcdnum=gcd(bunshi[i][j],bunbo[i][j]);
		if(gcdnum != 0) {
			bunshi[i][j]/=gcdnum;
			bunbo[i][j]/=gcdnum;
		}
	}
}
int manualInverseMode()
{
    std::vector<std::vector<int>> matrixBunshi, matrixBunbo;
    std::vector<std::vector<bool>> matrixSign;
    std::vector<int> gyo1, gyo2;
    std::vector<bool> sign;
    std::string nums;
    
    std::cout << "manual: Please input your square matrix (one row per line):" << std::endl;
    
    // 读取第一行来确定矩阵大小
    getline(std::cin, nums);
    gyo1 = safeMatrixRead_bunshi(nums);
    gyo2 = safeMatrixRead_bunbo(nums);
    sign = safeMatrixRead_isNegative(nums);
    
    if (gyo1.empty() || gyo2.empty() || sign.empty()) {
        std::cout << "manual: Invalid input!" << std::endl;
        return 1;
    }
    
    int n = gyo1.size();
    matrixBunshi.push_back(gyo1);
    matrixBunbo.push_back(gyo2);
    matrixSign.push_back(sign);
    
    // 读取剩余行
    for (int i = 1; i < n; i++) {
        getline(std::cin, nums);
        gyo1 = safeMatrixRead_bunshi(nums);
        gyo2 = safeMatrixRead_bunbo(nums);
        sign = safeMatrixRead_isNegative(nums);
        
        if (gyo1.empty() || gyo2.empty() || sign.empty() || gyo1.size() != n) {
            std::cout << "manual: Invalid input!" << std::endl;
            return 1;
        }
        
        matrixBunshi.push_back(gyo1);
        matrixBunbo.push_back(gyo2);
        matrixSign.push_back(sign);
    }
    
    // 创建单位矩阵（右侧）
    std::vector<std::vector<int>> identityBunshi(n, std::vector<int>(n, 0));
    std::vector<std::vector<int>> identityBunbo(n, std::vector<int>(n, 1));
    std::vector<std::vector<bool>> identitySign(n, std::vector<bool>(n, false));
    
    for (int i = 0; i < n; i++) {
        identityBunshi[i][i] = 1;
    }
    
    autogcdSquareMatrix(matrixBunshi, matrixBunbo);
    autogcdSquareMatrix(identityBunshi, identityBunbo);
    
    int step = 0;
    printManualMatrix(matrixBunshi, matrixBunbo, matrixSign, 
                     identityBunshi, identityBunbo, identitySign, step);
    
    std::string manualInput;
    std::cout << ":: ";
    getline(std::cin, manualInput);
    
    while (manualInput != "quit" && manualInput != "exit") {
        std::vector<std::string> manualCmd = processCmd(manualInput);
        std::string operation = manualCmd[0];
        
        if (manualCmd.size() < 2) {
            std::cout << "manual: Invalid command format!" << std::endl;
            goto Reinput;
        }
        
        
        if (operation == "neg") {
            if (manualCmd.size() != 2) {
                std::cout << "manual: Usage: neg row" << std::endl;
                goto Reinput;
            }
            
            int row = safestoi(manualCmd[1]);
            if (row < 0 || row >= n) {
                std::cout << "manual: Invalid row index!" << std::endl;
                goto Reinput;
            }
            
            // 对原矩阵行取负
            for (int j = 0; j < n; j++) {
                matrixSign[row][j] = !matrixSign[row][j];
            }
            // 对单位矩阵行取负
            for (int j = 0; j < n; j++) {
                identitySign[row][j] = !identitySign[row][j];
            }
            
        } else if (operation == "mul" || operation == "div") {
            if (manualCmd.size() != 3) {
                std::cout << "manual: Usage: " << operation << " row factor" << std::endl;
                goto Reinput;
            }
            
            int row = safestoi(manualCmd[1]);
            int factor = safestoi(manualCmd[2]);
            
            if (row < 0 || row >= n) {
                std::cout << "manual: Invalid row index!" << std::endl;
                goto Reinput;
            }
            if (factor == 0) {
                std::cout << "manual: Factor cannot be zero!" << std::endl;
                goto Reinput;
            }
            
            if (operation == "mul") {
                // 对原矩阵行乘因子
                for (int j = 0; j < n; j++) {
                    matrixBunshi[row][j] *= factor;
                }
                // 对单位矩阵行乘因子
                for (int j = 0; j < n; j++) {
                    identityBunshi[row][j] *= factor;
                }
            } else { // div
                // 对原矩阵行除因子（实际上是分母乘因子）
                for (int j = 0; j < n; j++) {
                    matrixBunbo[row][j] *= factor;
                }
                // 对单位矩阵行除因子
                for (int j = 0; j < n; j++) {
                    identityBunbo[row][j] *= factor;
                }
            }
            
        } else if (operation == "add" || operation == "sub") {
            if (manualCmd.size() != 3) {
                std::cout << "manual: Usage: " << operation << " source_row target_row" << std::endl;
                goto Reinput;
            }
            
            int srcRow = safestoi(manualCmd[1]);
            int tgtRow = safestoi(manualCmd[2]);
            
            if (srcRow < 0 || srcRow >= n || tgtRow < 0 || tgtRow >= n) {
                std::cout << "manual: Invalid row index!" << std::endl;
                goto Reinput;
            }
            if (srcRow == tgtRow) {
                std::cout << "manual: Source and target rows cannot be the same!" << std::endl;
                goto Reinput;
            }
            
            int sign = (operation == "add") ? 1 : -1;
            
            // 对原矩阵进行操作
            for (int j = 0; j < n; j++) {
                // 这里需要实现分数加法，简化处理：直接分子相加，分母取公倍数
                // 实际应该实现完整的分数运算，这里简化处理
                int commonBunbo = matrixBunbo[srcRow][j] * matrixBunbo[tgtRow][j];
                int srcBunshi = matrixBunshi[srcRow][j] * matrixBunbo[tgtRow][j];
                int tgtBunshi = matrixBunshi[tgtRow][j] * matrixBunbo[srcRow][j];
                
                if (matrixSign[srcRow][j]) srcBunshi = -srcBunshi;
                if (matrixSign[tgtRow][j]) tgtBunshi = -tgtBunshi;
                
                int newBunshi = tgtBunshi + sign * srcBunshi;
                matrixBunshi[tgtRow][j] = abs(newBunshi);
                matrixBunbo[tgtRow][j] = commonBunbo;
                matrixSign[tgtRow][j] = (newBunshi < 0);
            }
            
            // 对单位矩阵进行相同操作
            for (int j = 0; j < n; j++) {
                int commonBunbo = identityBunbo[srcRow][j] * identityBunbo[tgtRow][j];
                int srcBunshi = identityBunshi[srcRow][j] * identityBunbo[tgtRow][j];
                int tgtBunshi = identityBunshi[tgtRow][j] * identityBunbo[srcRow][j];
                
                if (identitySign[srcRow][j]) srcBunshi = -srcBunshi;
                if (identitySign[tgtRow][j]) tgtBunshi = -tgtBunshi;
                
                int newBunshi = tgtBunshi + sign * srcBunshi;
                identityBunshi[tgtRow][j] = abs(newBunshi);
                identityBunbo[tgtRow][j] = commonBunbo;
                identitySign[tgtRow][j] = (newBunshi < 0);
            }
            
        } else {
            std::cout << "manual: Unknown command! Available: mul, div, add, sub, neg" << std::endl;
            goto Reinput;
        }
        
        // 简化分数
        autogcdSquareMatrix(matrixBunshi, matrixBunbo);
        autogcdSquareMatrix(identityBunshi, identityBunbo);
        
        step++;
        printManualMatrix(matrixBunshi, matrixBunbo, matrixSign, 
                         identityBunshi, identityBunbo, identitySign, step);
        
        Reinput:
        std::cout << ":: ";
        getline(std::cin, manualInput);
    }
    
    std::cout << "manual: Exit." << std::endl;
    return 0;
}
int printGcd(std::vector<std::string>&cmd)
{
    std::vector<int> data;
    std::string nums;
    data.clear();
    if(cmd.size()==1)
    goto InputNums;
    if(cmd.size()>=2)
    {
        for(int i=1;i<cmd.size();i++)
        data.push_back(safestoi(cmd[i]));
        for(int i=0;i<data.size();i++)
        if(data[i]<1)
        {
            data.erase(data.begin()+i);
            i--;
        }
        if(data.size()==0)
        return 1;
        process:
        if(data.size()>1)
        {
            while(data.size()>1)
            {
                data.push_back(gcd(data[0],data[1]));
                data.erase(data.begin());
                data.erase(data.begin());
            }
            std::cout<<"gcd: The result is "<<data[0]<<std::endl;
            data.clear();
        }
        if(data.size()==1)
        {
            InputNums:
            std::vector<int> newInput;
            newInput.clear();
            std::cout<<"gcd: Input more numbers."<<std::endl;
            getline(std::cin,nums);
            newInput=gcdProcessInput(nums);
            data.insert(data.end(),newInput.begin(),newInput.end());
            newInput.clear();
            if(data.size()<2)
            {
                std::cout<<"gcd: Input is not enough."<<std::endl;
                return 1;
            }
            else
            goto process;
        }
    }
    return 0;
}