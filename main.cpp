#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <time.h>
#include <windows.h>
#include "userLogin.h"
#include "familyTree.h"
#include "functionIO.h"
#include "familyTreeNode.h"
using namespace std;

int main()
{
    familyTree tree;
    familyTreeNode *root = NULL;
    familyTreeNode *temp;
    string name;  //搜索时用姓名
    int year, month, day;  //搜索时用日期

    //获取本地日期
    SYSTEMTIME sys;
    GetLocalTime(&sys);
    int yearLocal = sys.wYear;
    int monthLocal = sys.wMonth;
    int dayLocal = sys.wDay;

    login: if(login())
    {
        int choice;
        while(true)
        {
            cout << "=================家谱管理系统管理界面=================" << endl;
			cout << "1、新建族谱" << endl;
			cout << "2、删除族谱" << endl;
			cout << "3、搜索成员信息" << endl;
			cout << "4、查看族谱" << endl;
			cout << "5、修改成员数据" << endl;
			cout << "6、添加家族成员" << endl;
            cout << "7、家庭成员按出生日期排序" << endl;
            cout << "8、显示第n代所有人的信息" << endl;
            cout << "9、切换用户" << endl;
			cout << "10、退出" << endl;
            cout << "======================================================" << endl;

			cout << "输入你的选择："<<endl;
			cin >> choice;

            switch(choice)
            {
                case 1:
                {
                    if(tree.createNode(&root))
                    {
                        tree.setRoot(root);
                        cout << "创建成功" << endl;
                    }
                    else
                    {
                        cout << "创建失败" << endl;
                    }
                    break;
                }
                case 2:
                {
                    cout << "输入你想要删除的人的名字：" << endl;
				    cin >> name;

				    temp = tree.getRoot();  //获取根节点
				    if(tree.deleteNode(temp, name))
                    {
                        cout << "删除成功" << endl;
                        cout << "======================================================" << endl;
                    }
				    else
                    {
                        cout << "删除失败" << endl;
                        cout << "======================================================" << endl;
                    }
				    break;
                }
                case 3:
                {
                    int choiceSearch;
                    cout << "======================================================" << endl;
                    cout << "1、按姓名查找" << endl;
                    cout << "2、按出生日期查找" << endl;
                    cout << "======================================================" << endl;
                    cout << "请输入选项：";
                    cin >> choiceSearch;
                    switch (choiceSearch)
                    {
                        case 1:
                        {
                            temp = tree.getRoot();
                            cout << "请输入姓名：";
                            cin >> name;
                            tree.dispNodeByName(name);
                            break;
                        }
                        case 2:
                        {
                            temp = tree.getRoot();
                            cout << "请输入出生日期（年/月/日）：";
                            scanf("%d/%d/%d", &year, &month, &day);
                            tree.dispNodeByDate(year, month, day);
                            break;
                        }
                    }
                    break;
                }
                case 4:
                {
                    cout << "=======================家谱信息=======================" << endl;
                    tree.dispFamily();
                    cout << "======================================================" << endl;
                    temp = tree.getRoot();
                    cout << "今天是" << yearLocal << "年" << monthLocal << "月" << dayLocal << "日" << endl;
                    cout << "今天过生日的家庭成员有：";
                    tree.searchNodeBirthday(temp, monthLocal, dayLocal);
                    cout << "======================================================" << endl;
                    break;
                }
                case 5:
                {
                    cout << "请输入需要修改信息的家庭成员姓名：";
                    cin >> name;
                    tree.changeFamily(name);
                    break;
                }
                case 6:
                {
                    cout << "请输入需要新增的家庭成员的父亲姓名：";
                    cin >> name;
                    if(tree.addNode(name))
                    {
                        cout << "添加成功" << endl;
                        cout << "======================================================" << endl;
                    }
                    else
                    {
                        cout << "添加失败" << endl;
                        cout << "======================================================" << endl;
                    }
                    break;
                }
                case 7:
                {
                    tree.sortFamily();
                    break;
                }
                case 8:
                {
                    temp = tree.getRoot();
                    int n;
                    cout << "输入代数：";
                    cin >> n;
                    dispInformationOfNthLevel(temp, n);
                    break;
                }
                case 9:
                {
                    goto login;
                    break;
                }
                case 10:
                {
                    cout << "已退出" << endl;
                    exit(0);
                    break;
                }
            }
        }
    }
    else
    {
        int choice;
        while(true)
        {
            cout << "===================家谱管理系统界面===================" << endl;
            cout << "1、搜索成员信息" << endl;
			cout << "2、查看族谱" << endl; 
            cout << "3、搜索成员信息" << endl;
            cout << "4、家庭成员按出生日期排序" << endl;
            cout << "5、切换用户" << endl;
            cout << "6、退出" << endl;
            cout << "======================================================" << endl;

            cout << "输入你的选择：" << endl;
			cin >> choice;

            switch(choice)
            {
                case 1:
                {
                    temp = tree.getRoot();
                    cout << "请输入姓名：";
                    cin >> name;
                    tree.dispNodeByName(name);
                    break;
                }
                case 2:
                {
                    cout << "=======================家谱信息=======================" << endl;
                    tree.dispFamily();
                    cout << "======================================================" << endl;
                    temp = tree.getRoot();
                    cout << "今天是" << yearLocal << "年" << monthLocal << "月" << dayLocal << "日" << endl;
                    cout << "今天过生日的家庭成员有：";
                    tree.searchNodeBirthday(temp, monthLocal, dayLocal);
                    cout << "======================================================" << endl;
                    break;
                }
                case 3:
                {
                    int choiceSearch;
                    cout << "======================================================" << endl;
                    cout << "1、按姓名查找" << endl;
                    cout << "2、按出生日期查找" << endl;
                    cout << "======================================================" << endl;
                    cout << "请输入选项：";
                    cin >> choiceSearch;
                    switch (choiceSearch)
                    {
                        case 1:
                        {
                            temp = tree.getRoot();
                            cout << "请输入姓名：";
                            cin >> name;
                            tree.dispNodeByName(name);
                            break;
                        }
                        case 2:
                        {
                            temp = tree.getRoot();
                            cout << "请输入出生日期（年/月/日）：";
                            scanf("%d/%d/%d", &year, &month, &day);
                            tree.dispNodeByDate(year, month, day);
                            break;
                        }
                    }
                    break;
                }
                case 4:
                {
                    tree.sortFamily();
                    break;
                }
                case 5:
                {
                    goto login;
                    break;
                }
                case 6:
                {
                    cout << "已退出" << endl;
                    exit(0);
                    break;
                }
            }
        }
    }
    return 0;
}
