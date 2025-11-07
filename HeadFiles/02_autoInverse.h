#pragma once
#include"02_main.h"
#include<iomanip>
std::vector<std::vector<double>>inverseMatrix(const std::vector<std::vector<double>>&matrix)
{
    // 检查矩阵是否为空
    if(matrix.empty()||matrix[0].empty())
	{
        return {};
    }
    int n=matrix.size();
    // 检查是否为方阵
    for(const auto&row:matrix)
	{
        if(row.size()!=n)
		{
            return {};
        }
    }
    // 创建增广矩阵 [A|I]
    std::vector<std::vector<double>>augmented(n,std::vector<double>(2*n,0.0));
    // 初始化增广矩阵
    for(int i=0;i<n;i++)
	{
        // 复制原矩阵
        for (int j=0;j<n;j++)
		{
            augmented[i][j] = matrix[i][j];
        }
        // 添加单位矩阵
        augmented[i][i+n]=1.0;
    }
    // 高斯-约当消元法
    for(int i=0;i<n;i++)
	{
        // 寻找主元（列主元）
        int pivotRow=i;
        for(int j=i+1;j<n;j++)
		{
            if(abs(augmented[j][i])>abs(augmented[pivotRow][i]))
			{
                pivotRow=j;
            }
        }

        // 如果主元为0，矩阵不可逆
        if(abs(augmented[pivotRow][i])<1e-10)
		{
            return {};
        }
        
        // 交换行（如果需要）
        if(pivotRow!=i)
		{
            swap(augmented[i],augmented[pivotRow]);
        }
        
        // 归一化主元行
        double pivot=augmented[i][i];
        for(int j=0;j<2*n;j++)
		{
            augmented[i][j]/=pivot;
        }

        // 消元
        for(int j=0;j<n;j++)
		{
            if(j!=i)
			{
                double factor=augmented[j][i];
                for(int k=0;k<2*n;k++)
				{
                    augmented[j][k]-=factor*augmented[i][k];
                }
            }
        }
    }

    // 提取逆矩阵部分
    std::vector<std::vector<double>>result(n,std::vector<double>(n,0.0));
    for(int i=0;i<n;i++)
	{
        for(int j=0;j<n;j++)
		{
            result[i][j]=augmented[i][j+n];
        }
    }
    
    return result;
}
int inverse(std::vector<std::string>&cmd)
{
    std::vector<std::vector<double>>input;
    std::vector<double>inputgyo;
    double k=0;
    int n=0,i=0,j=0;
    std::string line;
    if(cmd.size()>1)
    n=safestoi(cmd[1]);
    else
    {
        std::cout<<"inverse: How many row(s)/line(s)?";
        std::cin>>line;
        n=safestoi(line);
    }
    if(n<1)return 1;
    else
    {
        std::cout<<"inverse: Input your matrix."<<std::endl;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {        
                for(;;)
                {
                    if(std::cin>>k)
                    break;
                    std::cout<<"inverse: Invalid input."<<std::endl;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    return 1;
                }
                inputgyo.push_back(k);
            }
            input.push_back(inputgyo);
            inputgyo.clear();
        }
        input=inverseMatrix(input);
        if(!input.empty())
        {
            std::cout<<"inverse: The result is:"<<std::endl;
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    std::cout<<std::setw(8)<<input[i][j]<<'\t';
                }
                std::cout<<std::endl;
            }
        }
        else
        {
            std::cout<<"inverse: Unable to inverse."<<std::endl;
        }
    }
    return 0;
}