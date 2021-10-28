#pragma once
#include <iostream>
#include <cstdio>
#include <string>
#include "familyTreeNode.h"
using namespace std;

void input(familyMember *member)
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
    scanf("%d/%d/%d", &member->yearBirth, &member->monthBirth, &member->yearBirth);
    cout << "是否结婚？（0为否，1为是）";
    cin >> member->married;
    cout << "是否健在？（0为否，1为是）";
    cin >> member->live;
    if(member->live == false)
    {
        cout << "死亡日期（年/月/日）：";
        scanf("%d/%d/%d", &member->yearDeath, &member->monthDeath, &member->yearDeath);
    }
    else
    {
        member->yearDeath = 0;
        member->monthDeath = 0;
        member->dayDeath = 0;   
    }
}
