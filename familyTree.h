#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <stack>
#include <cstdlib>
#include "familyTreeNode.h"
#include "functionIO.h"
using namespace std;

class familyTree
{
    private:
        familyTreeNode* root;  //老祖宗
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
        void setRoot(familyTreeNode* root)
        {
            this->root = root;
        }
        //创建节点信息
        bool createNode(familyTreeNode** person)
        {
            int tag;
	        cout << "输入一个数（输入0表示该节点为空）:";
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
                inputInformationOfFamilyMember(&((*person)->information));
                
                //有配偶才有孩子
                if((*person)->information.married)
                {
                    cout << "=====================配偶信息录入=====================" << endl;
                    inputInformationOfFamilyMember(&((*person)->mate));

                    bool firstChild;  //判断是否有孩子
                    cout << "是否有孩子？（0为否，1为是）：";
                    cin >> firstChild;
                    
                    if(firstChild == true)
                    {
                        cout << "=====================孩子信息录入=====================" << endl;
                        createNode(&((*person)->lchild));
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
                            cout << "=====================二胎信息录入=====================" << endl;
                            createNode(&((*person)->rchild));
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
                else
                {
                    (*person)->lchild = NULL;
                }
            }
            return true;
        }
        //找到与p节点相连的前一个节点
        familyTreeNode* findParent(familyTreeNode* person)
        {
            if(person)
            {
                familyTreeNode* temp;
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
        //按姓名搜索节点
        familyTreeNode* searchNodeByName(familyTreeNode* person, const string name)
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
                    temp = searchNodeByName(person->lchild, name);
                    if(temp)
                        return temp;
                    //查找右子节点
                    temp = searchNodeByName(person->rchild, name);
                    if(temp)
                        return temp;
                    return NULL;
                }
            }
            return NULL;
        }
        //按出生日期搜索节点
        familyTreeNode* searchNodeByDate(familyTreeNode* person, int year, int month, int day)
        {
            if(person)
            {
                familyTreeNode* temp;
                if(person->information.yearBirth == year && 
                   person->information.monthBirth == month &&
                   person->information.dayBirth == day)
                {
                    return person;
                }
                //递归查找
                else
                {
                    //查找左子节点
                    temp = searchNodeByDate(person->lchild, year, month, day);
                    if(temp)
                        return temp;
                    //查找右子节点
                    temp = searchNodeByDate(person->rchild, year, month, day);
                    if(temp)
                        return temp;
                    return NULL;
                }
            }
            return NULL;
        }
        //新增节点信息:在父节点处增加子节点
        bool addNode(const string fatherName)
        {
            familyTreeNode* temp;
            temp = searchNodeByName(root, fatherName);
            if(temp)
            {
                cout << "已查到父亲信息" << endl;
                cout << "请输入新增子节点的信息" << endl;
                familyTreeNode* sonNode = NULL;
                createNode(&sonNode);
                sonNode->parent = temp;

                if(!(temp->lchild))
                {
                    temp->lchild = sonNode;
                }
                else if(!(temp->rchild))
                {
                    temp->rchild = sonNode;
                }

                return true;
            }
            else
            {
                cout << "未查找父亲信息" << endl;
                return false;
            }
        }
        //删除节点信息
        bool deleteNode(familyTreeNode* person, const string name)
        {
            if(person)
            {
                familyTreeNode* target;  //目标节点
                familyTreeNode* parent;  //目标节点父节点
                target = searchNodeByName(person, name);
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
        //按姓名查找成员信息
        void dispNodeByName(const string name)
        {
            familyTreeNode* temp;
            temp = searchNodeByName(root, name);
            if(temp)
            {
                cout << "已找到成员" << name << "的有关信息" << endl;
                dispInformationOfFamilyMember(temp);
                if(temp->parent)
                {
                    cout << "======================================================" << endl;
                    cout << "成员" << name << "的父亲的有关信息" << endl;
                    cout << "======================================================" << endl;
                    dispInformationOfFamilyMember(temp->parent);
                }
                if(temp->lchild)
                {
                    cout << "======================================================" << endl;
                    cout << "成员" << name << "的第一个孩子的有关信息" << endl;
                    cout << "======================================================" << endl;
                    dispInformationOfFamilyMember(temp->lchild);
                    if(temp->rchild)
                    {
                        cout << "======================================================" << endl;
                        cout << "成员" << name << "的第二个孩子的有关信息" << endl;
                        cout << "======================================================" << endl;
                        dispInformationOfFamilyMember(temp->rchild);
                    }
                }
            }
            else
            {
                cout << "======================================================" << endl;
                cout << "未能查询到成员" << name << "的信息" << endl;
                cout << "======================================================" << endl;
            }
        }
        //按出生日期查找成员信息
        void dispNodeByDate(int year, int month, int day)
        {
            familyTreeNode* temp;
            temp = searchNodeByDate(root, year, month, day);
            if(temp)
            {
                cout << "======================================================" << endl;
                cout << "出生日期为" << year << "年" << month << "月" << day << "日" << "的家庭成员的有关信息" << endl;
                cout << "======================================================" << endl;
                dispInformationOfFamilyMember(temp);
            }
            else
            {
                cout << "======================================================" << endl;
                cout << "未能查询到成员信息" << endl;
                cout << "======================================================" << endl;
            }
        }
        //显示家谱信息:二叉树的层次遍历
        void dispFamily()
        {
            queue<familyTreeNode*> que;
            if (root == NULL)
            {
                return;
            }
            que.push(root);  //根节点入队
            int currentLevelCount = 1;  //当前层次的节点数，初始值为1
            int nextLevelCount = 0;  //下一层次的节点数
            while(!que.empty())
            {
                //出队并访问节点
                familyTreeNode* front = que.front();
                cout << front->information.name << " ";
                que.pop();
                currentLevelCount--;
                //左子节点入队
                if(front->lchild)
                {
                    que.push(front->lchild);
                    nextLevelCount++;
                }
                //右子节点入队
                if(front->rchild)
                {
                    que.push(front->rchild);
                    nextLevelCount++;
                }
                //当前层次的节点数为0时，换行
                if(currentLevelCount == 0)
                {
                    cout << endl;
                    currentLevelCount = nextLevelCount;
                    nextLevelCount = 0;
                }   
            }
        }
        //修改家谱成员信息
        bool changeFamily(const string name)
        {
            familyTreeNode* temp;
            temp = searchNodeByName(root, name);
            bool flagSonMenu7 = false;  //子菜单返回主菜单的标志变量

            if(temp)
            {   
                cout <<"======================================================" << endl;
                cout << "已找到成员" << name << "的有关信息" << endl;
                cout << "======================================================" << endl;
                dispInformationOfFamilyMember(temp);  //显示基本信息

                bool FLAG = true;
                while(FLAG)
                {
                    cout <<"=======================================================" << endl;
                    cout << "成员" << name << "的以下信息可以修改：" << endl;
                    cout << "1、姓名" << endl;
                    cout << "2、性别" << endl;
                    cout << "3、年龄" << endl;
                    cout << "4、地址" << endl;
                    cout << "5、出生日期" << endl;
                    cout << "6、健在否" << endl;
                    cout << "7、修改配偶信息" << endl;
                    cout << "8、返回主菜单" << endl;
                    cout << "======================================================" << endl;

                    int choice;
                    cout << "请输入选项：";
                    cin >> choice;

                    //修改成员信息
                    switch(choice)
                    {
                        //修改姓名
                        case 1:
                        {
                            string nameChanged;
                            bool confirm;
                            cout << "修改前的姓名为：" << temp->information.name << endl;
                            cout << "请输入修改后的姓名：";
                            cin >> nameChanged;
                            cout << "是否确认修改？（0为否，1为是）：" ;
                            cin >> confirm;
                            if(confirm == true)
                            {
                                cout << "修改成功" << endl;
                                temp->information.name = nameChanged;
                            }
                            else
                            {
                                cout << "修改已取消" << endl;
                            }
                            break;
                        }
                        //修改性别
                        case 2:
                        {
                            string sexChanged;
                            bool confirm;
                            cout << "修改前的性别为：" << temp->information.sex << endl;
                            cout << "请输入修改后的性别：";
                            cin >> sexChanged;
                            cout << "是否确认修改？（0为否，1为是）：" ;
                            cin >> confirm;
                            if(confirm == true)
                            {
                                cout << "修改成功" << endl;
                                temp->information.sex = sexChanged;
                            }
                            else
                            {
                                cout << "修改已取消" << endl;
                            }
                            break;
                        }
                        //修改年龄
                        case 3:
                        {
                            int ageChanged;
                            bool confirm;
                            cout << "修改前的年龄为：" << temp->information.age << endl;
                            cout << "请输入修改后的年龄：";
                            cin >> ageChanged;
                            cout << "是否确认修改？（0为否，1为是）：" ;
                            cin >> confirm;
                            if(confirm == true)
                            {
                                cout << "修改成功" << endl;
                                temp->information.age = ageChanged;
                            }
                            else
                            {
                                cout << "修改已取消" << endl;
                            }
                            break;
                        }
                        //修改地址
                        case 4:
                        {
                            string addressChanged;
                            bool confirm;
                            cout << "修改前的地址为：" << temp->information.address << endl;
                            cout << "请输入修改后的地址：";
                            cin >> addressChanged;
                            cout << "是否确认修改？（0为否，1为是）：" ;
                            cin >> confirm;
                            if(confirm == true)
                            {
                                cout << "修改成功" << endl;
                                temp->information.address = addressChanged;
                            }
                            else
                            {
                                cout << "修改已取消" << endl;
                            }
                            break;
                        }
                        //修改出生日期
                        case 5:
                        {
                            int yearBirthChanged, monthBirthChanged, dayBirthChanged;
                            bool confirm;
                            cout << "修改前的出生日期为：" << temp->information.yearBirth << "/" 
                                << temp->information.monthBirth << "/" << temp->information.dayBirth << endl;
                            cout << "请输入修改后的出生日期（年/月/日）：";
                            scanf("%d/%d/%d", &yearBirthChanged, &monthBirthChanged, &dayBirthChanged);
                            cout << "是否确认修改？（0为否，1为是）：" ;
                            cin >> confirm;
                            if(confirm == true)
                            {
                                temp->information.yearBirth = yearBirthChanged;
                                temp->information.monthBirth = monthBirthChanged;
                                temp->information.dayBirth = dayBirthChanged;
                                cout << "修改成功" << endl;
                                
                            }
                            else
                            {
                                cout << "修改已取消" << endl;
                            }
                            break;
                        }
                        //修改健在情况
                        case 6:
                        {
                            cout << "修改前的健在情况：";
                            if(temp->information.live == true)
                            {
                                cout << "健在" << endl;
                            }
                            else
                            {
                                cout << "已逝" << endl;
                            }

                            bool liveChanged;
                            cout << "请输入修改后的健在情况（0为否，1为是）:";
                            cin >> liveChanged;
                            temp->information.live = liveChanged;

                            //家庭成员去世，输入死亡日期
                            if(liveChanged == false)
                            {
                                int yearDeathChanged, monthDeathChanged, dayDeathChanged;
                                bool confirm;
                                cout << "请输入死亡日期（年/月/日）：";
                                scanf("%d/%d/%d", &yearDeathChanged, &monthDeathChanged, &dayDeathChanged);
                                cout << "是否确认修改？（0为否，1为是）：";
                                cin >> confirm;
                                if(confirm == true)
                                {
                                    temp->information.yearDeath = yearDeathChanged;
                                    temp->information.monthDeath = monthDeathChanged;
                                    temp->information.dayDeath = dayDeathChanged;
                                    cout << "修改成功" << endl;
                                }
                                else
                                {
                                    cout << "修改已取消" << endl;
                                }
                            }
                            //未去世，死亡日期归零
                            else
                            {
                                bool confirm;
                                cout << "是否确认修改？（0为否，1为是）：";
                                cin >> confirm;
                                if(confirm == true)
                                {
                                    temp->information.yearDeath = 0;
                                    temp->information.monthDeath = 0;
                                    temp->information.dayDeath = 0;
                                    cout << "修改成功" << endl;
                                }
                                else
                                {
                                    cout << "修改已取消" << endl;
                                }
                            }
                            break;
                        }
                        //修改配偶信息
                        case 7:
                        {
                            bool flag = true;
                            while(flag)
                            {
                                cout << "=====================配偶信息修改=====================" << endl;
                                cout << "配偶" << temp->mate.name << "的以下信息可以修改：" << endl;
                                cout << "1、姓名" << endl;
                                cout << "2、年龄" << endl;
                                cout << "3、地址" << endl;
                                cout << "4、出生日期" << endl;
                                cout << "5、健在否" << endl;
                                cout << "======================================================" << endl;

                                int choiceMate;
                                cout << "请输入要修改的选项标号：";
                                cin >> choiceMate;

                                switch (choiceMate)
                                {
                                    //修改姓名
                                    case 1:
                                    {
                                        string nameChanged;
                                        bool confirm;
                                        cout << "修改前的配偶姓名为：" << temp->mate.name << endl;
                                        cout << "请输入修改后的配偶姓名：";
                                        cin >> nameChanged;
                                        cout << "是否确认修改？（0为否，1为是）：" ;
                                        cin >> confirm;
                                        if(confirm == true)
                                        {
                                            cout << "修改成功" << endl;
                                            temp->mate.name = nameChanged;
                                        }
                                        else
                                        {
                                            cout << "修改已取消" << endl;
                                        }
                                        break;
                                    }
                                    //修改年龄
                                    case 2:
                                    {
                                        int ageChanged;
                                        bool confirm;
                                        cout << "修改前配偶的年龄为：" << temp->mate.age << endl;
                                        cout << "请输入修改后配偶的年龄：";
                                        cin >> ageChanged;
                                        cout << "是否确认修改？（0为否，1为是）：" ;
                                        cin >> confirm;
                                        if(confirm == true)
                                        {
                                            cout << "修改成功" << endl;
                                            temp->mate.age = ageChanged;
                                        }
                                        else
                                        {
                                            cout << "修改已取消" << endl;
                                        }
                                        break;
                                    }
                                    //修改地址
                                    case 3:
                                    {
                                        string addressChanged;
                                        bool confirm;
                                        cout << "修改前配偶的地址为：" << temp->mate.address << endl;
                                        cout << "请输入修改后配偶的地址：";
                                        cin >> addressChanged;
                                        cout << "是否确认修改？（0为否，1为是）：" ;
                                        cin >> confirm;
                                        if(confirm == true)
                                        {
                                            cout << "修改成功" << endl;
                                            temp->mate.address = addressChanged;
                                        }
                                        else
                                        {
                                            cout << "修改已取消" << endl;
                                        }
                                        break;
                                    }
                                    //修改出生日期
                                    case 4:
                                    {
                                        int yearBirthChanged, monthBirthChanged, dayBirthChanged;
                                        bool confirm;
                                        cout << "修改前配偶的出生日期为：" << temp->mate.yearBirth << "/" 
                                             << temp->mate.monthDeath << "/" << temp->mate.dayBirth << endl;
                                        cout << "请输入修改后配偶的出生日期（年/月/日）：";
                                        scanf("%d/%d/%d", &yearBirthChanged, &monthBirthChanged, &dayBirthChanged);
                                        cout << "是否确认修改？（0为否，1为是）：" ;
                                        cin >> confirm;
                                        if(confirm == true)
                                        {
                                            temp->mate.yearBirth = yearBirthChanged;
                                            temp->mate.monthBirth = monthBirthChanged;
                                            temp->mate.dayBirth = dayBirthChanged;
                                            cout << "修改成功" << endl;
                                    
                                        }
                                        else
                                        {
                                            cout << "修改已取消" << endl;
                                        }
                                        break;
                                    }
                                    //修改健在情况
                                    case 5:
                                    {
                                        cout << "修改前的配偶健在情况：";
                                        if(temp->mate.live == true)
                                        {
                                            cout << "健在" << endl;
                                        }
                                        else
                                        {
                                            cout << "已逝" << endl;
                                        }

                                        bool liveChanged;
                                        cout << "请输入修改后的配偶健在情况（0为否，1为是）:";
                                        cin >> liveChanged;

                                        if(liveChanged == false)
                                        {
                                            int yearDeathChanged, monthDeathChanged, dayDeathChanged;
                                            bool confirm;
                                            cout << "请输入配偶的死亡日期（年/月/日）：";
                                            scanf("%d/%d/%d", &yearDeathChanged, &monthDeathChanged, &dayDeathChanged);
                                            cout << "是否确认修改？（0为否，1为是）：";
                                            cin >> confirm;
                                            if(confirm == true)
                                            {
                                                temp->mate.yearDeath = yearDeathChanged;
                                                temp->mate.monthDeath = monthDeathChanged;
                                                temp->mate.dayDeath = dayDeathChanged;
                                                cout << "修改成功" << endl;
                                            }
                                            else
                                            {
                                                cout << "修改已取消" << endl;
                                            }
                                        }
                                        break;
                                    }
                                    default:
                                    {
                                        cout << "错误的选项输入" << endl;
                                        break;
                                    }
                                }

                                cout << "是否继续修改？（0为否，1为是）：";
                                cin >> flag;
                                
                                if(flag == true)
                                {
                                    cout << "修改成功" << endl;
                                    //system("cls");
                                }
                                else
                                {
                                    flagSonMenu7 = true;
                                    cout << "返回上一级菜单" << endl;
                                    //system("cls");
                                } 
                            } 
                            break;        
                        }
                        //返回主菜单
                        case 8:
                        {
                            return true;
                        }
                        default:
                        {
                            cout << "错误的选项输入" << endl;
                            break;
                        }
                    }

                    //选项7：从子菜单返回主菜单
                    if(flagSonMenu7 == true)
                    {
                        FLAG = true;
                        flagSonMenu7 = false;
                    }
                    else
                    {
                        cout << "是否继续修改？（0为否，1为是）：";
                        cin >> FLAG;
                    }
                    
                    if(FLAG == false)
                    {
                        cout << "======================================================" << endl;
                        cout << "修改成功，返回主菜单" << endl;
                        cout << "======================================================" << endl;
                        //system("cls");
                        return true;
                    }
                }
            }
            else
            {
                cout << "======================================================" << endl;
                cout << "未能查询到成员" << name << "的信息" << endl;
                cout << "======================================================" << endl;
                return false;
            }
        }
        //设定排序规则
        static bool compareFamily(familyMember a, familyMember b)
        {
            if(a.yearBirth != b.yearBirth)
            {
                return a.yearBirth < b.yearBirth;
            }
            else if(a.monthBirth != b.monthBirth)
            {
                return a.monthBirth < b.monthBirth;
            }
            else if(a.dayBirth != b.dayBirth)
            {
                return a.dayBirth < b.dayBirth;
            }
        }
        //对家庭成员按照出生日期排序
        void sortFamily()
        {
            vector<familyMember> familyVector;  //创建一个向量存储容器
            stack<familyTreeNode*> familyStack;  //创建一个堆栈
            if(root == NULL)
            {
                return;
            }

            //迭代实现二叉树的先序遍历
            familyStack.push(root);
            while(!familyStack.empty())
            {
                familyTreeNode* node = familyStack.top();  //获取栈顶元素
                familyStack.pop();  //出栈
                familyVector.push_back(node->information);

                //访问右子树
                if(node->rchild)
                {
                    familyStack.push(node->rchild);
                }
                //访问左子树
                if(node->lchild)
                {
                    familyStack.push(node->lchild);
                }
            }
            
            //排序
            sort(familyVector.begin(), familyVector.end(), compareFamily);  

            //输出
            int len = familyVector.size();  //获取元素个数
            cout << "家庭成员按出生日期排序"  << endl;
            for(int i = 0; i < len; i++)
            {
                cout << i + 1 << " ";
                cout << familyVector[i].name << " ";
                cout << familyVector[i].yearBirth << "年";
                cout << familyVector[i].monthBirth << "月";
                cout << familyVector[i].dayBirth << "日" << endl;
            }
        }
        //按出生日期搜索节点
        void searchNodeBirthday(familyTreeNode* person, int month, int day)
        {
            if(person)
            {
                if(person->information.monthBirth == month &&
                   person->information.dayBirth == day && person->information.live == true)
                {
                    cout << person->information.name << " " << endl;
                }
                //递归查找
                //查找左子节点
                searchNodeBirthday(person->lchild, month, day);
                //查找右子节点
                searchNodeBirthday(person->rchild, month, day);
            }
        }
};
