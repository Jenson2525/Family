#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include "familyTreeNode.h"
#include "function.h"
using namespace std;

class familyTree
{
    private:
        familyTreeNode *root;  //老祖宗
    public:
        //构造函数
        familyTree()
        {
            this->root = NULL;
        }
        //获取祖先信息
        familyTreeNode* getRoot()
        {
            return root;
        }
        //设置祖先信息
        void setRoot(familyTreeNode *root)
        {
            this->root = root;
        }
        //创建一个结点
        bool create(familyTreeNode **person)
        {
            int tag;
	        cout << "输入一个数（输入0表示该结点为空）:" << endl;
	        cin >> tag;
	        if (!tag)
	        {
		        *person =  NULL;
	        }
            else
            {
                *person = new familyTreeNode;
                if(!(*person))
                {
                    return false;
                }
                (*person)->parent = NULL;
                //输入信息
                cout << "请输入相关信息" << endl;
                input(&((*person)->information));
                //有配偶才能有孩子
                if((*person)->information.married)
                {
                    cout << "请输入配偶信息" << endl;
                    input(&((*person)->mate));
                    create(&((*person)->lchild));
                    if((*person)->lchild)
                    {
                        (*person)->lchild->parent = *person;
                    }
                    //是否有二胎
                    bool secondChild;  
                    cout << "是否有二胎？（0为否，1为是）";
                    cin >> secondChild;
                    if(secondChild == 0)
                    {
                        (*person)->rchild = NULL;  //没有二胎，设为空指针
                    }
                    else
                    {
                        create(&((*person)->rchild));
                        if((*person)->rchild)
                        {
                            (*person)->rchild->parent = *person;
                        }
                    }
                }
                else
                {
                    (*person)->lchild = NULL;
                }
            }
        }
};
