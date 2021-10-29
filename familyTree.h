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
        //创建一个节点
        bool create(familyTreeNode **person)
        {
            int tag;
	        cout << "输入一个数（输入0表示该节点为空）:" << endl;
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
                    if(secondChild == false)
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
            return true;
        }
        //找到与p节点相连的前一个节点
        familyTreeNode* findParent(familyTreeNode *person)
        {
            if(person)
            {
                familyTreeNode *temp;
                temp = person->parent;
                if(temp)
                {
                    cout << "查询不到父节点信息" <<endl;
                    return NULL;
                }
                else
                {
                    return temp;
                }
            }
            else 
            {
                return NULL;
            }
        }
        //查询节点信息
        familyTreeNode* searchNode(familyTreeNode* person, const string name)
        {
            if(person)
            {
                familyTreeNode* temp;
                if(person->information.name == name)
                {
                    return person;
                }
                //递归查找
                else
                {
                    //查找左子节点
                    temp = searchNode(person->lchild, name);
                    if(temp)
                        return temp;
                    //查找右子节点
                    temp = searchNode(person->rchild, name);
                    if(temp)
                        return temp;
                    return NULL;
                }
            }
            return NULL;
        }
        //删除节点信息
        bool deleteNode(familyTreeNode* person, const string name)
        {
            if(person)
            {
                familyTreeNode* target;  //目标节点
                familyTreeNode* parent;  //目标节点父节点
                target = searchNode(person, name);
                if(target)
                {
                    cout << "已查到该节点" << endl;
                    if(target->lchild || target->rchild)
                    {
                        cout << "该节点不能删除" << endl;
                        return false;
                    }
                    else
                    {
                        parent = findParent(target);
                        //如果父节点存在,则设置左子节点或右子节点指针为NULL
                        if(parent)
                        {
                            //左子节点
                            if(parent->lchild == target)
                                parent->lchild = NULL;
                            //右子节点
                            else if(parent->rchild == target)
                                parent->rchild = NULL;
                        }
                        free(target);  //删除
                        return true;
                    }
                    cout << "未找到名为" << name << "的信息" << endl;
                    return false;
                }
            }
            return false;
        }
        //显示家谱信息:二叉树的层次遍历
        void dispFamily(familyTreeNode* person)
        {
            
        }
};
