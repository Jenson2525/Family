#pragma once
#include <iostream>
#include <string>
using namespace std;

//密码验证
bool loginManagerConfirm()
{
    string password = "123456";
    string inputPassword;
    cout << "输入密码：";
    cin >> inputPassword;
    if(password == inputPassword)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//登录
bool login()
{
    cout<<"=================家谱管理系统登录界面================="<<endl;
	int choice;
	while(true)
	{
		cout << "1、我是管理员" << endl;
		cout << "2、我不是管理员" << endl;
        cout << "======================================================" << endl;
		cout << "输入你的选择：";
		cin >> choice;
		switch(choice)
		{
            case 1:
                int count;
                if (loginManagerConfirm())
                    return true;
                else
                {
                    cout << "======================================================" << endl;
                    cout << "密码错误，你还有两次机会！" << endl;
                    cout << "======================================================" << endl;
                    for(count = 1;count <= 3;count++)
                    {
                        if (loginManagerConfirm())
                        {
                            return true;
                            break;
                        }
                      
                        cout << "======================================================" << endl;
                        cout << "提示：密码错误！" << endl;
                        cout << "======================================================" << endl;
                      
                    }
                    cout << "======================================================" << endl;
                    cout << "你已经失败三次，自动跳转至普通界面" << endl;
                    cout << "======================================================" << endl;
                    return false;
                }
                break;
            case 2:
            {
                return false;
                break;
            }
            default:
            {
                cout << "======================================================" << endl;
                cout << "没有这个选项！自动为你跳转普通界面" << endl;
                cout << "======================================================" << endl;
                break;
            }
                
                return false;
		}
	}
}
