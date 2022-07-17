#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
//家谱结构体
typedef struct treeNode {
	char Name[20];//名字
	int Num;//孩子数目
	char Kind;//性别  g G 女 b B 男
	struct treeNode *Parent;//记录这个节点的父节点，指向父辈的指针
	struct treeNode *NextNode[20];//孩子和配偶 第一个是配偶 后面的是孩子
}TreeNode;//结构体变量
int MATEFLAG = 0;//用于区分找到的成员的身份是家族成员还是家族成员的配偶
//函数声明部分
void MainMenue(TreeNode *tree);//主界面
TreeNode* SearchTree(TreeNode *tree, char name[], int length);//查找（从哪个树查找，查找名字、长度）
void OutPutMessage(TreeNode * tree, char name[], int length);//输出
void AddNew(TreeNode *tree);//添加成员（往哪棵树进行添加）
void Change(TreeNode *tree);//修改信息（修改的树）
void SubMenue1(TreeNode *tree);//查找并添加(子界面)
void SubMenue2(TreeNode *tree);//查找并添加(子界面)
void OutPutAll(TreeNode *tree);//输出所有家谱信息
void CreateTree(TreeNode *tree);//建立树
void Loadsystem();//加载
void quit();//退出
//主函数
void main()
{
    Loadsystem();//加载界面函数
	TreeNode *tree;
	tree = (TreeNode*)malloc(sizeof(TreeNode));//申请一个节点空间
	//初始化根节点
	tree->Parent = NULL;//树的根节点的父节点是NULL
	strcpy(tree->Name,"0");//初始化节点的名称是0
	MainMenue(tree);//将根节点传入到主菜单中进行创建配偶子节点操作
}
//tree为根节点（祖先）
//主界面
void MainMenue(TreeNode *tree) {
	char c;//用户键盘录入的字符存储
	TreeNode *NewNode;
	char name[20];
	while(1)
	{
		system("cls");//清屏操作
		printf("\t---*-*-*-*-*----请输入你的操作---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---A.输入家谱信息并建立多叉树---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---B.查找某人并输出信息---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---C.添加新成员---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---D.输出整个家谱信息---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---E.修改信息---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---F.退出程序---*-*-*-*-*---\n");
		c = getchar();//获取从键盘输入的字符，利用循环监听循环输入的菜单
		switch (c)
		{
			case 'a':
			case 'A':
				//创建家谱
				//创建一个节点
				TreeNode *NewNode;
				NewNode = (TreeNode*)malloc(sizeof(TreeNode));//申请一个存储空间
				NewNode->Parent = NULL;//初始化节点
				strcpy(NewNode->Name, "0");//初始化节点的名称为0
				//创建一个节点
				//根节点的信息录入
				//开始时建立的是根节点，为当前根节点取名跟录入性别等信息
				//输入姓名
				printf("请输入姓名: \n");
				scanf("%s", tree->Name);//由于tree中的Name是一个字符数组，直接写数组名，是获取数组的地址，故此处不需要加&符号来进行录入
				//输入性别
				printf("请输入性别 (男 b 、女 g ): \n");
				getchar();//取出缓存区的回车
				scanf("%c", &(tree->Kind));//Kind是一个字符类型，必须接上&符号地址才能进行录入
				tree->Parent = NULL;//根节点，为NULL，无父节点
				//根节点的信息录入
				//递归建立树，为tree根节点创立配偶节点跟子节点
				CreateTree(tree);
				break;
			case 'b':
			case 'B':
				//判断家族有没有建立
				if (strcmp(tree->Name, "0") == 0)
				{
					printf("还没有建立家谱，请先建立家谱! \n");
					system("pause");//暂停显示
					getchar();
					break;
				}
				//查询家族
				printf("\t请输入你要查找的人的姓名:\n"); 
				scanf("%s",name);
				OutPutMessage(SearchTree(tree, name, 20), name, 20);
				getchar();//取出缓存区的回车
				break;
			case 'c':
			case 'C':
				if (strcmp(tree->Name, "0") == 0)
				{
					printf("还没有建立家谱，请先建立家谱! \n");
					system("pause");//暂停显示
					return MainMenue(tree);//返回主界面
				}
				AddNew(tree);
				fflush(stdin);//清除字符缓冲区
				getchar();//取出缓存区的回车
				break;
			case 'd':
			case 'D':
				if (strcmp(tree->Name, "0") == 0)
				{
					printf("还没有建立家谱，请先建立家谱! \n");
					return MainMenue(tree);
				}
				OutPutAll(tree);//输出整个家族信息
				system("pause");//暂停显示
				fflush(stdin);//清除字符缓冲区
				getchar();//取出缓存区的回车
				break;
			case 'e':
			case 'E':
				if (strcmp(tree->Name, "0") == 0)
				{
					printf("还没有建立家谱，请先建立家谱! \n");
					Sleep(1000);//延迟
					break;
				}
				Change(tree);//修改
				fflush(stdin);//清除字符缓冲区
				getchar();//取出缓存区的回车
				break;
			case 'f':
			case 'F':
				//退出函数
				quit();
				break;   
		}
	}
}
TreeNode* SearchTree(TreeNode *tree, char name[], int length) {
	//判断名字和节点名字是否相同
	int i;//循环控制变量
	TreeNode *NewNode;
	//判断根节点（祖先）名字和输入的名字是否相同
	if (strcmp(tree->Name, name) == 0)
	{
		if (length == 0) MATEFLAG = 1;//0:表示本身成员，1:表示此节点为成员配偶节点（配偶节点）（媳妇，儿媳等，配偶节点）
		else MATEFLAG = 0;//0:表示此节点为成员节点（如孙子，孙女，儿子，成员节点）
		return tree;
	}
	//判断是否有配偶子女 如果没有返回NULL（如果没有配偶就不需要考虑孩子节点了，所以直接return）
	if (tree->NextNode[0] == NULL || strcmp(tree->NextNode[0]->Name, "0") == 0)
	{
		return NULL;
	}
	//查找子女和配偶及其子树中是否有名字匹配
	for (i = 0; i <= tree->Num; i++)
	{
		if (i == 0)
		{
			//配偶信息的查找（第一个位置存放的是配偶）
			NewNode = SearchTree(tree->NextNode[i], name, 0);
		}
		else
		{
			NewNode = SearchTree(tree->NextNode[i], name, 20);//length不为0时，查找的是子女的信息
		}
		if (NewNode != NULL) return NewNode;
	}
	return NULL;
}
void OutPutMessage(TreeNode * tree, char name[], int length) 
{
	int flag = 0;//flag 标记性别 
	int i;
	TreeNode *NewNode;
	if(tree == NULL)
	{
		printf(" 该家谱图中没有%s这个人！ \n", name);
		return;
	}
	//输出查找的人的自身信息
	printf("\t您找的人信息如下: \n");
	printf("\t姓名 %s", name);
	if (tree->Kind == 'G' || tree->Kind == 'g')
	{
		flag = 1;                                         //标记的性别    
		printf("\t性别 女\n");
	}
	else
	{
		printf("\t性别 男\n");
	}
	NewNode = tree->Parent;// 父母信息放到节点NewNode里 
	if (MATEFLAG == 1)//此人非直系亲属，要么嫁入要么入赘
	{
		if (flag == 1)// 性别为女
		{
			printf(" 她是嫁入这家的，所以父母信息不在家谱内包括！ \n");
			printf(" 丈夫的姓名:%s \n", NewNode->Name);
		}
		else   // 性别为男
		{
			printf(" 他是入赘这家的所以父母信息不在家谱内包括！ \n");
			printf("\t妻子的姓名:%s \n", NewNode->Name);
		}
		if ((NewNode->Num) > 0)   //判断他 (她)是否有孩子    
		{
			printf("\t孩子的信息如下 :\n"); 	// 输出他 (她)的孩子的信息 
			for (i = 1; i <= NewNode->Num; i++)
			{
				printf("\t%s 姓名 :", NewNode->NextNode[i]->Name);
				if (NewNode->NextNode[i]->Kind == 'G' || NewNode->NextNode[i]->Kind == 'g')
				{
					printf("\t性别 女 \n");
				}
				else
				{
					printf("\t性别 男 \n");
				}
			}
		}
		system("pause");//延迟
		return;
	}
	if (NewNode == NULL)         // 判断它是不是根节点如果是的话就没有父母兄弟信息 
		printf("\t%s是这个家谱图里最顶端的人!\n", name);
	else
	{
		if (NewNode->Kind == 'G' || NewNode->Kind == 'g')      // 判断父亲节点是父亲还是母亲
		{   //输出他（她）的父母亲的信息 
			printf("\t母亲的姓名 :%s\n", NewNode->Name);
			printf("\t父亲的姓名 :%s\n", NewNode->NextNode[0]->Name);
		}
		else
		{
			printf("\t母亲的姓名 :%s\n", NewNode->NextNode[0]->Name);
			printf("\t父亲的姓名 :%s\n", NewNode->Name);
		}
		if (NewNode->Num > 1)      //判断他 (她)是否有兄弟姐妹
		{            //输出他 (她 )的兄弟姐妹的信息
			printf("\t%s的兄弟姐妹信息如下 :\n",name); 
			for (i = 1; i <= NewNode->Num; i++)
			{
				if (NewNode->NextNode[i])
					printf("\t姓名 : %s", NewNode->NextNode[i]->Name);
				if (NewNode->NextNode[i]->Kind == 'G' || NewNode->NextNode[i]->Kind == 'g')
				{
					printf("\t性别 女\n");
				}
				else
				{
					printf("\t性别 男\n");
				}
			}
		}
		else
		{
			printf("\t%s没有兄弟姐妹! \n", tree->Name);
		}
	}
	if (tree->NextNode[0] != NULL && strcmp(tree->NextNode[0]->Name,"0")!=0)       // 判断他 (她 )是否有配偶   
	{                                                //输出他(她)的配偶的信息
		if (flag == 1)
			printf("\t丈夫的姓名:%s \n", tree->NextNode[0]->Name);
		else
			printf("\t妻子的姓名:%s \n", tree->NextNode[0]->Name);
		if (tree->Num > 0)                             //判断他 (她 )是否有孩子
		{
			printf("\t孩子的信息如下: \n");       // 输出他 (她)的孩子的信息     
			for (i = 1; i <= tree->Num; i++)
			{
				printf("\t姓名 %s", tree->NextNode[i]->Name);
				if (tree->NextNode[i]->Kind == 'G' || tree->NextNode[i]->Kind == 'g')
				{
					printf("\t性别 女\n");
				}
				else
				{
					printf("\t性别 男\n");
				}
			}
		}
		else
		{
			printf("\t%s目前还没有孩子！ \n", name);
		}
	}
	else
	{
		printf("\t%s至今还没有配偶和孩子! \n", tree->Name);
	}
	system("pause");//延时
}
void AddNew(TreeNode *tree) {
	SubMenue2(tree);//子界面实现添加成员信息的功能
}
void Change(TreeNode *tree) {
	//输入要查找的人员姓名
	char name[20];
	TreeNode *stree;
	printf("\t请输入要修改的人员信息: \n");
	scanf("%s", name);
	stree = SearchTree(tree, name, 20);
	if (stree == NULL)
	{
		printf("\t\t\t该家谱图中没有%s这个人的信息请确认是否输入错误\n", name);
		return;
	}
	else
	{
		SubMenue1(stree);
	}
}
//修改信息函数（子界面）
void SubMenue1(TreeNode *tree) {
	char c;
	int  flag, i;
	char name[20];//用于存放查找到的名字
	char Parent[2][20];//用于存放父母的信息
	TreeNode * NewNode;
	getchar();//取出缓存区的回车
	while (1)
	{
		system("cls");
		printf("\n\t\t\t===========请选择你的操作==========\n");
		printf("\t\t\t----------A:修改个人的信息----------\n");
		printf("\t\t\t----------B:修改父母的信息----------\n");
		printf("\t\t\t----------C:修改兄弟姐妹的信息----------\n");
		printf("\t\t\t----------D:修改子女的信息----------\n");
		printf("\t\t\t----------E:修改配偶的信息----------\n");
		printf("\t\t\t----------F:退出----------\n");
		c = getchar();//接收从键盘输入的字符
		switch (c)
		{
		case 'A':
		case 'a':
			printf("\n\t\t\t请输入修改的姓名:");
			scanf("%s", name);
			if (strcmp(name, "0") != 0)
			{
				strcpy(tree->Name, name);
			}
			printf("\t\t\t如需修改性别输入1，无需修改输入0\n\t\t\t");
			scanf("%d", &flag);
			if (flag == 1)
			{
				if (tree->Kind == 'G' || tree->Kind == 'g')
					tree->Kind = 'B';
				else tree->Kind = 'G';
			}
			printf("\t\t\t个人信息修改成功!\n");
			system("pause");//延迟
			break;
		case 'B':
		case 'b':
			if (tree->Parent == NULL)    //判断是不是头节点
			{
				printf("\t\t\t是这个家谱图里最顶端的人没有父母信息!\n", name);
				Sleep(1000);//延迟
				break;
			}
			if (MATEFLAG == 1)            //判断是不是入赘或嫁入此间的
			{
				if (tree->Kind == 'g' || tree->Kind == 'G')
				{
					printf("\t\t\t她是嫁入此间的所以父母信息不在家谱内包括\n");
					Sleep(1000);//延迟
				}
				else
				{
					printf("\t\t\t他是入赘此间的所以父母信息不在家谱内包括\n");
					Sleep(1000);//延迟
				}
				break;
			}
			//判别父母的性别
			if (tree->Parent->Kind == 'G' || tree->Parent->Kind == 'g')
			{
				strcpy(Parent[0], "母亲");
				strcpy(Parent[1], "父亲");
			}
			else
			{
				strcpy(Parent[0], "父亲");
				strcpy(Parent[1], "母亲");
			}
			printf("\t\t\t请输入%s要修改的姓名(如果不需要修改就输入0):", Parent[0]);
			scanf("%s", name);
			if (strcmp(name, "0") != 0)
				strcpy(tree->Parent->Name, name);
			printf("\t\t\t请输入%s要修改的姓名(如果不需要修改就输入0):", Parent[1]);
			scanf("%s", name);
			if (strcmp(name, "0") != 0)
				strcpy(tree->Parent->NextNode[0]->Name, name);
			printf("\t\t\t父母的信息修改成功!\n");
			break;
		case 'C':
		case 'c':
			NewNode = tree->Parent;
			if (NewNode == NULL)           //判断是不是头节点
			{
				printf("\t\t\t是这个家谱图里最顶端的人没有兄弟姐妹信息!\n", name);
				Sleep(1000);//延迟
				break;
			}
			if (MATEFLAG == 1)            //判断是不是入赘或嫁入此间的
			{
				if (tree->Kind == 'G' || tree->Kind == 'g')
				{
					printf("\t\t\t她是嫁入此间的所以兄弟姐妹信息不在家谱内包括\n");
					Sleep(1000);//延迟
				}
				else
				{
					printf("\t\t\t他是入赘此间的所以兄弟姐妹信息不在家谱内包括\n");
					Sleep(1000);//延迟
				}
				break;
			}
			if (NewNode->Num == 1)
			{
				printf("\t\t\t没有兄弟姐妹! \n");
				break;
			}
			else
			{
				for (i = 1; i <= NewNode->Num; i++)
				{
					if (NewNode->NextNode[i]->Name != tree->Name)
					{
						printf("\t请输入%s修改的姓名(如果不需要修改就输入0):\n", NewNode->NextNode[i]->Name);
						scanf("%s", name);
						if (strcmp(name, "0") != 0)
						{
							strcpy(NewNode->NextNode[i]->Name, name);
						}
						printf("如需修改性别输入1，无需修改输入0:");
						scanf("%d", &flag);
						if (flag == 1)
						{
							if (NewNode->NextNode[i]->Kind == 'G' || NewNode->NextNode[i]->Kind == 'g')
							{
								NewNode->NextNode[i]->Kind = 'B';
							}
							else NewNode->NextNode[i]->Kind = 'G';
						}
					}
				}
			}
			printf("\t\t\t兄弟姐妹的信息修改成功！\n");
			break;
		case 'D':
		case 'd':
			if (tree->Num == 0)
			{
				printf("\t\t\t目前还没有子女！\n");
				Sleep(1000);//延迟
				break;
			}
			if (tree->Parent != NULL)
				if (strcmp(tree->Name, tree->Parent->NextNode[0]->Name) == 0) //如果他是入赘或者是嫁入的就需用配偶节点完成修改
				{
					tree = tree->Parent;
				}
			for (i = 1; i <= tree->Num; i++)
			{
				printf("\t\t\t请输入%s修改的姓名(如果不需要修改就输入0): \n", tree->NextNode[i]->Name);
				scanf("%s", name);
				if (strcmp(name, "0") != 0)
					strcpy(tree->NextNode[i]->Name, name);
				printf("\t\t\t如需修改性别输入1，无需修改输入0: \n");
				scanf("%d", &flag);
				if (flag == 1)
				{
					if (tree->NextNode[i]->Kind == 'g' || tree->NextNode[i]->Kind == 'G')
					{
						tree->NextNode[i]->Kind = 'B';
					}
					else
					{
						tree->NextNode[i]->Kind = 'G';
					}
				}
			}
			printf("\n\t\t\t子女的信息修改成功！\n");
			system("pause");//延时
			break;
		case 'E':
		case 'e':
			if (tree->Parent != NULL)
			{
				if
					(tree->NextNode[0] == NULL && strcmp(tree->Name, tree->Parent->NextNode[0]->Name) != 0)
				{
					printf("\t\t\t目前还没有配偶！\n");
					Sleep(1000);//延迟
					break;
				}
				if (strcmp(tree->Name, tree->Parent->NextNode[0]->Name) == 0)
				{
					printf("\n\n\t\t\t请输入%s修改的姓名(如果不需要修改就输入0):", tree->Parent->Name);
					scanf("%s", name);
					if (strcmp(name, "0") != 0)
						strcpy(tree->Parent->Name, name);
				}
				else
				{
					printf("\n\n\t\t\t请输入%s修改的姓名(如果不需要修改就输入0):", tree->NextNode[0]->Name);
					scanf("%s", name);
					if (strcmp(name, "0") != 0)
						strcpy(tree->NextNode[0]->Name, name);
				}
			}
			else
			{
				if (tree->NextNode[0] == NULL)
					printf("\t\t\t至今还没有配偶! \n");
				else
				{
					printf("\n\n\t\t\t请输入%s修改的姓名(如果不需要修改就输入0):", tree->NextNode[0]->Name);
					scanf("%s", name);
					if (strcmp(name, "0") != 0)
					{
						strcpy(tree->NextNode[0]->Name, name);
					}
				}
			}
			printf("\t\t\t配偶的信息修改成功! \n");
			system("pause");//延时
			break;
		case 'F':
		case 'f':
			printf("\t\t\t--------本项服务到此结束!-------- \n");
			system("pause");//延时
			return;
		}
	}
}
//添加信息函数（子界面）
void SubMenue2(TreeNode *tree){
	char c;
	TreeNode *NewNode;
	TreeNode *Btree = tree;
	char name[20];
	fflush(stdin);//清除字符缓冲区
	int num;
	while(1)
	{
		system("cls");//清屏操作
		printf("\t---*-*-*-*-*---请输入你的操作---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---A.添加某人子女信息---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---B.添加某人配偶信息---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---C.退出---*-*-*-*-*---\n");
		c = getchar();//获取从键盘输入的字符，利用循环监听循环输入的菜单
		switch (c)
		{
			case 'a':
			case 'A':
				//输入查找名字
				printf("\t请输入那个人的姓名: \n");
				scanf("%s", name);
				tree = SearchTree(tree, name, 20);//在家谱里查找这个人
				//判断有没有找到
				if (tree == NULL)
				{
					tree = Btree;
					printf("\t没有找到这个人，请检查输入是否正确! \n");
					system("pause");//延时
					break;
				}
				//成员 NextNode[i]、配偶 ->配偶对应成员Parent->NextNode[i]
				if(MATEFLAG == 0 && tree->NextNode[0] == NULL||MATEFLAG == 0 &&strcmp(tree->NextNode[0]->Name,"0") == 0)
				{
					printf("\t%s还没有配偶，请先添加配偶! \n", tree->Name);
					system("pause");
					break;
				}
				if (tree->Parent == NULL && tree->Num < 0 || tree->Num>20)
				{
					tree->Num = 0;
				}
				//如果本身为配偶成员 要添加孩子就要添加他的配偶上面，他的配偶就是他的Parernt
				if (MATEFLAG == 1) tree = tree->Parent;
				//输入要添加的子女姓名
				NewNode = (TreeNode*)malloc(sizeof(TreeNode));//申请一个节点空间
				printf("\t请输入要添加的子女姓名: \n");
				scanf("%s", NewNode->Name);
				//输入要添加的子女性别
				getchar();//取出缓存区的回车
				printf("\t请输入要添加的子女性别: \n");
				scanf("%c",&(NewNode->Kind));
				//将子女节点和父辈连接关系
				num = tree->Num;
				//孩子节点初始化
				NewNode->NextNode[0] = NULL;
				NewNode->Num = 0;
				tree->NextNode[num+1]=NewNode;
				NewNode->Parent = tree;
				tree->Num = tree->Num + 1;//孩子数目加1
				printf("--------添加子女成功!--------\n");
				system("pause");//延时
				break;
			case 'b':
			case 'B':
				//输入查找名字
				system("cls");//清屏
				printf("\n\t\t\t添加某人配偶信息\n\n");
				printf("\t\t\t请输入那个人的姓名：");
				scanf("%s", name);
				tree = SearchTree(tree, name, 20);
				//判断有没有找到
				if (tree == NULL)
				{
					printf("\n\t\t\t没有找到这个人，请检查输入是否正确！\n");
					fflush(stdin);//清空字符缓冲区
					getchar();//等待
					Sleep(1000);//延迟
					break;
				}
				if (MATEFLAG == 1)
				{
					printf("\n\t\t\t此人不是家族直系，请检查输入是否正确！\n");
					fflush(stdin);//清空字符缓冲区
					getchar();//取出缓存区的回车
					Sleep(1000);//延迟
					break;
				}
				//添加配偶姓名
				NewNode = (TreeNode*)malloc(sizeof(TreeNode));
				printf("\n\t\t\t请输入要添加到的配偶的姓名：");
				scanf("%s", NewNode->Name);
				//添加配偶性别
				if (tree->Kind == 'B' || tree->Kind == 'b')
				{
					NewNode->Kind = 'G';
				}
				else
				{
					NewNode->Kind = 'B';
				}
				//确定配偶与父节点的关系
				NewNode->NextNode[0] = NULL;
				NewNode->Num = 0;
				tree->NextNode[0] = NewNode;
				NewNode->Parent = tree;
				printf("\n\t\t\t添加配偶成功！\n");
				fflush(stdin);//清空字符缓冲区
				getchar();//等待
				Sleep(1000);//延时
				break;			
			case 'c':
			case 'C':
				printf("\t--------本服务已经结束!--------\n");
				system("pause");//延迟
				break;
		}
		if (c == 'c' || c == 'C')
		{
			break;
		}
	}
}
//输出所有家谱信息函数
void OutPutAll(TreeNode *tree) {
    //输出祖先姓名、性别
	int flag = 0;//初始化默认为是男的，若是女的值改为1
	int i = 0;//控制循环输出祖先孩子信息
	printf("姓名: %s 性别: ", tree->Name);
	if (tree->Kind == 'G' || tree->Kind == 'g')
	{
		printf("女\n");
		flag = 1;//祖先性别为女
	}
	else
	{
		printf("男\n");//否则为男
	}
//输出祖先配偶姓名、性别等个人信息
	if (!(tree->NextNode[0]) || strcmp(tree->NextNode[0]->Name, "0") == 0)
	{
		printf("该成员没有配偶和子女!\n");//默认没有配偶就没有子女
		return;
	}
	if (flag == 1)//此时性别为女
	{
		printf("丈夫的姓名是: %s \n", tree->NextNode[0]->Name);
	}
	else
	{
		printf("妻子的姓名是: %s \n", tree->NextNode[0]->Name);
	}
//循环输出祖先孩子姓名、性别等信息
	for (i = 1; i <= tree->Num; i++)
	{
		printf("%s的第%d个孩子的名字是: %s 性别是: ", tree->Name, i, tree->NextNode[i]->Name);
		if (tree->NextNode[i]->Kind == 'G' || tree->NextNode[i]->Kind == 'g')
		{
			printf("女\n");
		}
		else
		{
			printf("男\n");
		}
	}
//递归输出孩子节点信息
	for (i = 1; i <= tree->Num; i++)
	{
		OutPutAll(tree->NextNode[i]);
	}
}
//递归建立树
//tree为当前操作的节点，可以理解为是当前的根节点（第一次执行的时候,是从根节点出发的）
void CreateTree(TreeNode *tree) {
	//生成一个配偶节点，为当前节点生成一个配偶节点
	TreeNode *NewNode;//配偶节点
	NewNode = (TreeNode*)malloc(sizeof(TreeNode));//申请一个存储空间
	tree->NextNode[0] = NewNode;//NextNode的第一个位置存储配偶，其余位置为孩子节点
	//输入配偶姓名
	printf("请输入配偶姓名: \n");
	scanf("%s", NewNode->Name);
	//输入当前操作的节点的孩子数目
	printf("请输入孩子数目: \n");
	scanf("%d", &(tree->Num));//因为Num是int类型，需要用&地址符进行赋值
	//判断配偶姓名（如果是0，则是一个叶子节点--无子女、无孩子）并且当前节点的孩子数量为0
	if (strcmp(NewNode->Name, "0") == 0 && tree->Num == 0)
		return;
	//配偶节点处理
	if (tree->Kind == 'g' || tree->Kind == 'G')
	{
		NewNode->Kind = 'B';//因当前节点如果是G（女），那么他的配偶就是B（男）
	}
	else
	{
		NewNode->Kind = 'G';
	}
	NewNode->Num = 0;//不需要为配偶打印子孩子（子孩子打印的过程在其丈夫的节点中打印），因此，默认情况下，孩子不在当前配偶下（在直系亲属中）
	NewNode->NextNode[0] = NULL;//新的孩子节点无配偶
	tree->NextNode[0] = NewNode;//将配偶节点指定给当前的tree节点，NextNode的第一个位置存储配偶，其余位置为孩子
	tree->NextNode[0]->Parent = tree;//指定配偶节点的父节点为当前操作的节点
	//配偶节点处理
	//循环递归的建立孩子节点
	int i;//控制循环的变量
	for (i = 1; i <= tree->Num; i++)
	{
		//建立一个孩子节点
		TreeNode *ChildNode;//孩子节点
		ChildNode = (TreeNode*)malloc(sizeof(TreeNode));//申请一个节点空间
		//输入孩子节点姓名
		printf("请输入%s的第%d个孩子姓名: \n", tree->Name, i);
		scanf("%s",ChildNode->Name);
		//输入孩子节点性别
		printf("请输入%s的第%d个孩子性别: \n", tree->Name, i);
		getchar();//取出缓存区的回车
		scanf("%c", &(ChildNode->Kind));
		//处理孩子节点和父节点关系
		ChildNode->Num = 0;
		ChildNode->Parent = tree;
		tree->NextNode[i] = ChildNode;
		//循环递归建立孩子节点
		CreateTree(tree->NextNode[i]);
		printf("********家谱图已经建立成功!********\n");
		system("pause");//延时
		break;
	}
}
//加载界面函数
void Loadsystem(){
    int m;
	for (m = 0; m <= 100; m++)
	{
		printf("\n\n\n\t\t\t欢迎使用家谱系统\n");
		printf("\t\t\t正在进入界面，请稍等\n");
		printf("\t\t\tLoading------%d%%------", m);
		system("cls");//清屏处理
	}
}
//退出系统函数
void quit()
{
		system("cls");//清屏处理
		printf("\n\n\n\t\t\t家谱系统正在为您服务");
		printf("\n\n\n\t\t\t欢迎下次使用，谢谢!\n");
		printf("\n\n\n\t\t\t正在退出,请稍等...... \n");
		system("pause");
		exit(0);//退出系统函数，包含在头文件stdlib中
		return;
}

