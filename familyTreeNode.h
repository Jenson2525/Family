#pragma once
#include <iostream>
#include <string>
using namespace std;

//家庭成员的基本信息
struct familyMember
{
    //基本信息
    string name;  //姓名
    string sex;  //性别
    string address;  //地址
    int age;  //年龄
    int yearBirth, monthBirth, dayBirth;  //出生日期
    int yearDeath, monthDeath, dayDeath;  //死亡日期
    bool married;  //婚否
    bool live;  //健在否
};

//结点的信息
struct familyTreeNode
{
    familyMember information;
    familyMember mate;
    familyTreeNode *parent;
    familyTreeNode *lchild;
    familyTreeNode *rchild;
};
