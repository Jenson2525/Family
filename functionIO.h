#pragma once
#include <iostream>
#include <cstdio>
#include <string>
#include "familyTreeNode.h"
using namespace std;

//输入信息
void inputInformationOfFamilyMember(familyMember *member)
{
    cout << "姓名：";
    cin >> member->name;
    cout << "性别：";
    cin >> member->sex;
    cout << "地址：";
    cin >> member->address;
    cout << "年龄：";
    cin >> member->age;
    cout << "出生日期（年/月/日）：";
    scanf("%d/%d/%d", &member->yearBirth, &member->monthBirth, &member->dayBirth);
    cout << "是否结婚？（0为否，1为是）：";
    cin >> member->married;
    cout << "是否健在？（0为否，1为是）：";
    cin >> member->live;
    if(member->live == false)
    {
        cout << "死亡日期（年/月/日）：";
        scanf("%d/%d/%d", &member->yearDeath, &member->monthDeath, &member->dayDeath);
    }
    else
    {
        member->yearDeath = 0;
        member->monthDeath = 0;
        member->dayDeath = 0;   
    }
}

//输出信息
void dispInformationOfFamilyMember(familyTreeNode* person)
{
    cout << "=====================成员基本信息=====================" << endl;
    cout << "姓名：" << person->information.name << endl;
    cout << "性别：" << person->information.sex << endl;
    cout << "年龄：" << person->information.age << endl;
    cout << "地址：" << person->information.address << endl;
    cout << "出生日期：" << person->information.yearBirth << "/" << person->information.monthBirth 
         << "/" << person->information.dayBirth << endl;

    cout << "健在否：";
    if(person->information.live == true)
    {
        cout << "健在" << endl;
    }
    else
    {
        cout << "已逝" << endl;
        cout << "死亡日期：" << person->information.yearDeath << "/" << person->information.monthDeath 
             << "/" << person->information.dayDeath << endl;
    }

    cout << "婚否：";
    if(person->information.married == true)
    {
        cout << "已婚" << endl;
        cout << "---------------------配偶信息---------------------" << endl;
        cout << "姓名：" << person->mate.name << endl;
        cout << "性别：" << person->mate.sex << endl;
        cout << "年龄：" << person->mate.age << endl;
        cout << "地址：" << person->mate.address << endl;
        cout << "出生日期：" << person->mate.yearBirth << "/" << person->mate.monthBirth 
             << "/" << person->mate.dayBirth << endl;

        cout << "健在否：";
        if(person->mate.live == true)
        {
            cout << "健在" << endl;
        }
        else
        {
            cout << "已逝" << endl;
            cout << "死亡日期：" << person->mate.yearDeath << "/" << person->mate.monthDeath 
                 << "/" << person->mate.dayDeath << endl;
        }
    }
    else
    {
        cout << "未婚" << endl;
    }
    cout << "======================================================" << endl;
    cout << endl;
}
//显示第n代所有人信息
void dispInformationOfNthLevel(familyTreeNode* person, int n)
{
    static int depth = 0;
    depth++;
    if(person)
    {
        if(depth == n)
        {
            dispInformationOfFamilyMember(person);
        }
        dispInformationOfNthLevel(person->lchild, n);
        dispInformationOfNthLevel(person->rchild, n);
    }
    depth--;
}
