#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
//���׽ṹ��
typedef struct treeNode {
	char Name[20];//����
	int Num;//������Ŀ
	char Kind;//�Ա�  g G Ů b B ��
	struct treeNode *Parent;//��¼����ڵ�ĸ��ڵ㣬ָ�򸸱���ָ��
	struct treeNode *NextNode[20];//���Ӻ���ż ��һ������ż ������Ǻ���
}TreeNode;//�ṹ�����
int MATEFLAG = 0;//���������ҵ��ĳ�Ա������Ǽ����Ա���Ǽ����Ա����ż
//������������
void MainMenue(TreeNode *tree);//������
TreeNode* SearchTree(TreeNode *tree, char name[], int length);//���ң����ĸ������ң��������֡����ȣ�
void OutPutMessage(TreeNode * tree, char name[], int length);//���
void AddNew(TreeNode *tree);//��ӳ�Ա�����Ŀ���������ӣ�
void Change(TreeNode *tree);//�޸���Ϣ���޸ĵ�����
void SubMenue1(TreeNode *tree);//���Ҳ����(�ӽ���)
void SubMenue2(TreeNode *tree);//���Ҳ����(�ӽ���)
void OutPutAll(TreeNode *tree);//������м�����Ϣ
void CreateTree(TreeNode *tree);//������
void Loadsystem();//����
void quit();//�˳�
//������
void main()
{
    Loadsystem();//���ؽ��溯��
	TreeNode *tree;
	tree = (TreeNode*)malloc(sizeof(TreeNode));//����һ���ڵ�ռ�
	//��ʼ�����ڵ�
	tree->Parent = NULL;//���ĸ��ڵ�ĸ��ڵ���NULL
	strcpy(tree->Name,"0");//��ʼ���ڵ��������0
	MainMenue(tree);//�����ڵ㴫�뵽���˵��н��д�����ż�ӽڵ����
}
//treeΪ���ڵ㣨���ȣ�
//������
void MainMenue(TreeNode *tree) {
	char c;//�û�����¼����ַ��洢
	TreeNode *NewNode;
	char name[20];
	while(1)
	{
		system("cls");//��������
		printf("\t---*-*-*-*-*----��������Ĳ���---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---A.���������Ϣ�����������---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---B.����ĳ�˲������Ϣ---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---C.����³�Ա---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---D.�������������Ϣ---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---E.�޸���Ϣ---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---F.�˳�����---*-*-*-*-*---\n");
		c = getchar();//��ȡ�Ӽ���������ַ�������ѭ������ѭ������Ĳ˵�
		switch (c)
		{
			case 'a':
			case 'A':
				//��������
				//����һ���ڵ�
				TreeNode *NewNode;
				NewNode = (TreeNode*)malloc(sizeof(TreeNode));//����һ���洢�ռ�
				NewNode->Parent = NULL;//��ʼ���ڵ�
				strcpy(NewNode->Name, "0");//��ʼ���ڵ������Ϊ0
				//����һ���ڵ�
				//���ڵ����Ϣ¼��
				//��ʼʱ�������Ǹ��ڵ㣬Ϊ��ǰ���ڵ�ȡ����¼���Ա����Ϣ
				//��������
				printf("����������: \n");
				scanf("%s", tree->Name);//����tree�е�Name��һ���ַ����飬ֱ��д���������ǻ�ȡ����ĵ�ַ���ʴ˴�����Ҫ��&����������¼��
				//�����Ա�
				printf("�������Ա� (�� b ��Ů g ): \n");
				getchar();//ȡ���������Ļس�
				scanf("%c", &(tree->Kind));//Kind��һ���ַ����ͣ��������&���ŵ�ַ���ܽ���¼��
				tree->Parent = NULL;//���ڵ㣬ΪNULL���޸��ڵ�
				//���ڵ����Ϣ¼��
				//�ݹ齨������Ϊtree���ڵ㴴����ż�ڵ���ӽڵ�
				CreateTree(tree);
				break;
			case 'b':
			case 'B':
				//�жϼ�����û�н���
				if (strcmp(tree->Name, "0") == 0)
				{
					printf("��û�н������ף����Ƚ�������! \n");
					system("pause");//��ͣ��ʾ
					getchar();
					break;
				}
				//��ѯ����
				printf("\t��������Ҫ���ҵ��˵�����:\n"); 
				scanf("%s",name);
				OutPutMessage(SearchTree(tree, name, 20), name, 20);
				getchar();//ȡ���������Ļس�
				break;
			case 'c':
			case 'C':
				if (strcmp(tree->Name, "0") == 0)
				{
					printf("��û�н������ף����Ƚ�������! \n");
					system("pause");//��ͣ��ʾ
					return MainMenue(tree);//����������
				}
				AddNew(tree);
				fflush(stdin);//����ַ�������
				getchar();//ȡ���������Ļس�
				break;
			case 'd':
			case 'D':
				if (strcmp(tree->Name, "0") == 0)
				{
					printf("��û�н������ף����Ƚ�������! \n");
					return MainMenue(tree);
				}
				OutPutAll(tree);//�������������Ϣ
				system("pause");//��ͣ��ʾ
				fflush(stdin);//����ַ�������
				getchar();//ȡ���������Ļس�
				break;
			case 'e':
			case 'E':
				if (strcmp(tree->Name, "0") == 0)
				{
					printf("��û�н������ף����Ƚ�������! \n");
					Sleep(1000);//�ӳ�
					break;
				}
				Change(tree);//�޸�
				fflush(stdin);//����ַ�������
				getchar();//ȡ���������Ļس�
				break;
			case 'f':
			case 'F':
				//�˳�����
				quit();
				break;   
		}
	}
}
TreeNode* SearchTree(TreeNode *tree, char name[], int length) {
	//�ж����ֺͽڵ������Ƿ���ͬ
	int i;//ѭ�����Ʊ���
	TreeNode *NewNode;
	//�жϸ��ڵ㣨���ȣ����ֺ�����������Ƿ���ͬ
	if (strcmp(tree->Name, name) == 0)
	{
		if (length == 0) MATEFLAG = 1;//0:��ʾ�����Ա��1:��ʾ�˽ڵ�Ϊ��Ա��ż�ڵ㣨��ż�ڵ㣩��ϱ������ϱ�ȣ���ż�ڵ㣩
		else MATEFLAG = 0;//0:��ʾ�˽ڵ�Ϊ��Ա�ڵ㣨�����ӣ���Ů�����ӣ���Ա�ڵ㣩
		return tree;
	}
	//�ж��Ƿ�����ż��Ů ���û�з���NULL�����û����ż�Ͳ���Ҫ���Ǻ��ӽڵ��ˣ�����ֱ��return��
	if (tree->NextNode[0] == NULL || strcmp(tree->NextNode[0]->Name, "0") == 0)
	{
		return NULL;
	}
	//������Ů����ż�����������Ƿ�������ƥ��
	for (i = 0; i <= tree->Num; i++)
	{
		if (i == 0)
		{
			//��ż��Ϣ�Ĳ��ң���һ��λ�ô�ŵ�����ż��
			NewNode = SearchTree(tree->NextNode[i], name, 0);
		}
		else
		{
			NewNode = SearchTree(tree->NextNode[i], name, 20);//length��Ϊ0ʱ�����ҵ�����Ů����Ϣ
		}
		if (NewNode != NULL) return NewNode;
	}
	return NULL;
}
void OutPutMessage(TreeNode * tree, char name[], int length) 
{
	int flag = 0;//flag ����Ա� 
	int i;
	TreeNode *NewNode;
	if(tree == NULL)
	{
		printf(" �ü���ͼ��û��%s����ˣ� \n", name);
		return;
	}
	//������ҵ��˵�������Ϣ
	printf("\t���ҵ�����Ϣ����: \n");
	printf("\t���� %s", name);
	if (tree->Kind == 'G' || tree->Kind == 'g')
	{
		flag = 1;                                         //��ǵ��Ա�    
		printf("\t�Ա� Ů\n");
	}
	else
	{
		printf("\t�Ա� ��\n");
	}
	NewNode = tree->Parent;// ��ĸ��Ϣ�ŵ��ڵ�NewNode�� 
	if (MATEFLAG == 1)//���˷�ֱϵ������Ҫô����Ҫô��׸
	{
		if (flag == 1)// �Ա�ΪŮ
		{
			printf(" ���Ǽ�����ҵģ����Ը�ĸ��Ϣ���ڼ����ڰ����� \n");
			printf(" �ɷ������:%s \n", NewNode->Name);
		}
		else   // �Ա�Ϊ��
		{
			printf(" ������׸��ҵ����Ը�ĸ��Ϣ���ڼ����ڰ����� \n");
			printf("\t���ӵ�����:%s \n", NewNode->Name);
		}
		if ((NewNode->Num) > 0)   //�ж��� (��)�Ƿ��к���    
		{
			printf("\t���ӵ���Ϣ���� :\n"); 	// ����� (��)�ĺ��ӵ���Ϣ 
			for (i = 1; i <= NewNode->Num; i++)
			{
				printf("\t%s ���� :", NewNode->NextNode[i]->Name);
				if (NewNode->NextNode[i]->Kind == 'G' || NewNode->NextNode[i]->Kind == 'g')
				{
					printf("\t�Ա� Ů \n");
				}
				else
				{
					printf("\t�Ա� �� \n");
				}
			}
		}
		system("pause");//�ӳ�
		return;
	}
	if (NewNode == NULL)         // �ж����ǲ��Ǹ��ڵ�����ǵĻ���û�и�ĸ�ֵ���Ϣ 
		printf("\t%s���������ͼ����˵���!\n", name);
	else
	{
		if (NewNode->Kind == 'G' || NewNode->Kind == 'g')      // �жϸ��׽ڵ��Ǹ��׻���ĸ��
		{   //������������ĸ�ĸ�׵���Ϣ 
			printf("\tĸ�׵����� :%s\n", NewNode->Name);
			printf("\t���׵����� :%s\n", NewNode->NextNode[0]->Name);
		}
		else
		{
			printf("\tĸ�׵����� :%s\n", NewNode->NextNode[0]->Name);
			printf("\t���׵����� :%s\n", NewNode->Name);
		}
		if (NewNode->Num > 1)      //�ж��� (��)�Ƿ����ֵܽ���
		{            //����� (�� )���ֵܽ��õ���Ϣ
			printf("\t%s���ֵܽ�����Ϣ���� :\n",name); 
			for (i = 1; i <= NewNode->Num; i++)
			{
				if (NewNode->NextNode[i])
					printf("\t���� : %s", NewNode->NextNode[i]->Name);
				if (NewNode->NextNode[i]->Kind == 'G' || NewNode->NextNode[i]->Kind == 'g')
				{
					printf("\t�Ա� Ů\n");
				}
				else
				{
					printf("\t�Ա� ��\n");
				}
			}
		}
		else
		{
			printf("\t%sû���ֵܽ���! \n", tree->Name);
		}
	}
	if (tree->NextNode[0] != NULL && strcmp(tree->NextNode[0]->Name,"0")!=0)       // �ж��� (�� )�Ƿ�����ż   
	{                                                //�����(��)����ż����Ϣ
		if (flag == 1)
			printf("\t�ɷ������:%s \n", tree->NextNode[0]->Name);
		else
			printf("\t���ӵ�����:%s \n", tree->NextNode[0]->Name);
		if (tree->Num > 0)                             //�ж��� (�� )�Ƿ��к���
		{
			printf("\t���ӵ���Ϣ����: \n");       // ����� (��)�ĺ��ӵ���Ϣ     
			for (i = 1; i <= tree->Num; i++)
			{
				printf("\t���� %s", tree->NextNode[i]->Name);
				if (tree->NextNode[i]->Kind == 'G' || tree->NextNode[i]->Kind == 'g')
				{
					printf("\t�Ա� Ů\n");
				}
				else
				{
					printf("\t�Ա� ��\n");
				}
			}
		}
		else
		{
			printf("\t%sĿǰ��û�к��ӣ� \n", name);
		}
	}
	else
	{
		printf("\t%s����û����ż�ͺ���! \n", tree->Name);
	}
	system("pause");//��ʱ
}
void AddNew(TreeNode *tree) {
	SubMenue2(tree);//�ӽ���ʵ����ӳ�Ա��Ϣ�Ĺ���
}
void Change(TreeNode *tree) {
	//����Ҫ���ҵ���Ա����
	char name[20];
	TreeNode *stree;
	printf("\t������Ҫ�޸ĵ���Ա��Ϣ: \n");
	scanf("%s", name);
	stree = SearchTree(tree, name, 20);
	if (stree == NULL)
	{
		printf("\t\t\t�ü���ͼ��û��%s����˵���Ϣ��ȷ���Ƿ��������\n", name);
		return;
	}
	else
	{
		SubMenue1(stree);
	}
}
//�޸���Ϣ�������ӽ��棩
void SubMenue1(TreeNode *tree) {
	char c;
	int  flag, i;
	char name[20];//���ڴ�Ų��ҵ�������
	char Parent[2][20];//���ڴ�Ÿ�ĸ����Ϣ
	TreeNode * NewNode;
	getchar();//ȡ���������Ļس�
	while (1)
	{
		system("cls");
		printf("\n\t\t\t===========��ѡ����Ĳ���==========\n");
		printf("\t\t\t----------A:�޸ĸ��˵���Ϣ----------\n");
		printf("\t\t\t----------B:�޸ĸ�ĸ����Ϣ----------\n");
		printf("\t\t\t----------C:�޸��ֵܽ��õ���Ϣ----------\n");
		printf("\t\t\t----------D:�޸���Ů����Ϣ----------\n");
		printf("\t\t\t----------E:�޸���ż����Ϣ----------\n");
		printf("\t\t\t----------F:�˳�----------\n");
		c = getchar();//���մӼ���������ַ�
		switch (c)
		{
		case 'A':
		case 'a':
			printf("\n\t\t\t�������޸ĵ�����:");
			scanf("%s", name);
			if (strcmp(name, "0") != 0)
			{
				strcpy(tree->Name, name);
			}
			printf("\t\t\t�����޸��Ա�����1�������޸�����0\n\t\t\t");
			scanf("%d", &flag);
			if (flag == 1)
			{
				if (tree->Kind == 'G' || tree->Kind == 'g')
					tree->Kind = 'B';
				else tree->Kind = 'G';
			}
			printf("\t\t\t������Ϣ�޸ĳɹ�!\n");
			system("pause");//�ӳ�
			break;
		case 'B':
		case 'b':
			if (tree->Parent == NULL)    //�ж��ǲ���ͷ�ڵ�
			{
				printf("\t\t\t���������ͼ����˵���û�и�ĸ��Ϣ!\n", name);
				Sleep(1000);//�ӳ�
				break;
			}
			if (MATEFLAG == 1)            //�ж��ǲ�����׸�����˼��
			{
				if (tree->Kind == 'g' || tree->Kind == 'G')
				{
					printf("\t\t\t���Ǽ���˼�����Ը�ĸ��Ϣ���ڼ����ڰ���\n");
					Sleep(1000);//�ӳ�
				}
				else
				{
					printf("\t\t\t������׸�˼�����Ը�ĸ��Ϣ���ڼ����ڰ���\n");
					Sleep(1000);//�ӳ�
				}
				break;
			}
			//�б�ĸ���Ա�
			if (tree->Parent->Kind == 'G' || tree->Parent->Kind == 'g')
			{
				strcpy(Parent[0], "ĸ��");
				strcpy(Parent[1], "����");
			}
			else
			{
				strcpy(Parent[0], "����");
				strcpy(Parent[1], "ĸ��");
			}
			printf("\t\t\t������%sҪ�޸ĵ�����(�������Ҫ�޸ľ�����0):", Parent[0]);
			scanf("%s", name);
			if (strcmp(name, "0") != 0)
				strcpy(tree->Parent->Name, name);
			printf("\t\t\t������%sҪ�޸ĵ�����(�������Ҫ�޸ľ�����0):", Parent[1]);
			scanf("%s", name);
			if (strcmp(name, "0") != 0)
				strcpy(tree->Parent->NextNode[0]->Name, name);
			printf("\t\t\t��ĸ����Ϣ�޸ĳɹ�!\n");
			break;
		case 'C':
		case 'c':
			NewNode = tree->Parent;
			if (NewNode == NULL)           //�ж��ǲ���ͷ�ڵ�
			{
				printf("\t\t\t���������ͼ����˵���û���ֵܽ�����Ϣ!\n", name);
				Sleep(1000);//�ӳ�
				break;
			}
			if (MATEFLAG == 1)            //�ж��ǲ�����׸�����˼��
			{
				if (tree->Kind == 'G' || tree->Kind == 'g')
				{
					printf("\t\t\t���Ǽ���˼�������ֵܽ�����Ϣ���ڼ����ڰ���\n");
					Sleep(1000);//�ӳ�
				}
				else
				{
					printf("\t\t\t������׸�˼�������ֵܽ�����Ϣ���ڼ����ڰ���\n");
					Sleep(1000);//�ӳ�
				}
				break;
			}
			if (NewNode->Num == 1)
			{
				printf("\t\t\tû���ֵܽ���! \n");
				break;
			}
			else
			{
				for (i = 1; i <= NewNode->Num; i++)
				{
					if (NewNode->NextNode[i]->Name != tree->Name)
					{
						printf("\t������%s�޸ĵ�����(�������Ҫ�޸ľ�����0):\n", NewNode->NextNode[i]->Name);
						scanf("%s", name);
						if (strcmp(name, "0") != 0)
						{
							strcpy(NewNode->NextNode[i]->Name, name);
						}
						printf("�����޸��Ա�����1�������޸�����0:");
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
			printf("\t\t\t�ֵܽ��õ���Ϣ�޸ĳɹ���\n");
			break;
		case 'D':
		case 'd':
			if (tree->Num == 0)
			{
				printf("\t\t\tĿǰ��û����Ů��\n");
				Sleep(1000);//�ӳ�
				break;
			}
			if (tree->Parent != NULL)
				if (strcmp(tree->Name, tree->Parent->NextNode[0]->Name) == 0) //���������׸�����Ǽ���ľ�������ż�ڵ�����޸�
				{
					tree = tree->Parent;
				}
			for (i = 1; i <= tree->Num; i++)
			{
				printf("\t\t\t������%s�޸ĵ�����(�������Ҫ�޸ľ�����0): \n", tree->NextNode[i]->Name);
				scanf("%s", name);
				if (strcmp(name, "0") != 0)
					strcpy(tree->NextNode[i]->Name, name);
				printf("\t\t\t�����޸��Ա�����1�������޸�����0: \n");
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
			printf("\n\t\t\t��Ů����Ϣ�޸ĳɹ���\n");
			system("pause");//��ʱ
			break;
		case 'E':
		case 'e':
			if (tree->Parent != NULL)
			{
				if
					(tree->NextNode[0] == NULL && strcmp(tree->Name, tree->Parent->NextNode[0]->Name) != 0)
				{
					printf("\t\t\tĿǰ��û����ż��\n");
					Sleep(1000);//�ӳ�
					break;
				}
				if (strcmp(tree->Name, tree->Parent->NextNode[0]->Name) == 0)
				{
					printf("\n\n\t\t\t������%s�޸ĵ�����(�������Ҫ�޸ľ�����0):", tree->Parent->Name);
					scanf("%s", name);
					if (strcmp(name, "0") != 0)
						strcpy(tree->Parent->Name, name);
				}
				else
				{
					printf("\n\n\t\t\t������%s�޸ĵ�����(�������Ҫ�޸ľ�����0):", tree->NextNode[0]->Name);
					scanf("%s", name);
					if (strcmp(name, "0") != 0)
						strcpy(tree->NextNode[0]->Name, name);
				}
			}
			else
			{
				if (tree->NextNode[0] == NULL)
					printf("\t\t\t����û����ż! \n");
				else
				{
					printf("\n\n\t\t\t������%s�޸ĵ�����(�������Ҫ�޸ľ�����0):", tree->NextNode[0]->Name);
					scanf("%s", name);
					if (strcmp(name, "0") != 0)
					{
						strcpy(tree->NextNode[0]->Name, name);
					}
				}
			}
			printf("\t\t\t��ż����Ϣ�޸ĳɹ�! \n");
			system("pause");//��ʱ
			break;
		case 'F':
		case 'f':
			printf("\t\t\t--------������񵽴˽���!-------- \n");
			system("pause");//��ʱ
			return;
		}
	}
}
//�����Ϣ�������ӽ��棩
void SubMenue2(TreeNode *tree){
	char c;
	TreeNode *NewNode;
	TreeNode *Btree = tree;
	char name[20];
	fflush(stdin);//����ַ�������
	int num;
	while(1)
	{
		system("cls");//��������
		printf("\t---*-*-*-*-*---��������Ĳ���---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---A.���ĳ����Ů��Ϣ---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---B.���ĳ����ż��Ϣ---*-*-*-*-*---");
		printf("\n\t---*-*-*-*-*---C.�˳�---*-*-*-*-*---\n");
		c = getchar();//��ȡ�Ӽ���������ַ�������ѭ������ѭ������Ĳ˵�
		switch (c)
		{
			case 'a':
			case 'A':
				//�����������
				printf("\t�������Ǹ��˵�����: \n");
				scanf("%s", name);
				tree = SearchTree(tree, name, 20);//�ڼ�������������
				//�ж���û���ҵ�
				if (tree == NULL)
				{
					tree = Btree;
					printf("\tû���ҵ�����ˣ����������Ƿ���ȷ! \n");
					system("pause");//��ʱ
					break;
				}
				//��Ա NextNode[i]����ż ->��ż��Ӧ��ԱParent->NextNode[i]
				if(MATEFLAG == 0 && tree->NextNode[0] == NULL||MATEFLAG == 0 &&strcmp(tree->NextNode[0]->Name,"0") == 0)
				{
					printf("\t%s��û����ż�����������ż! \n", tree->Name);
					system("pause");
					break;
				}
				if (tree->Parent == NULL && tree->Num < 0 || tree->Num>20)
				{
					tree->Num = 0;
				}
				//�������Ϊ��ż��Ա Ҫ��Ӻ��Ӿ�Ҫ���������ż���棬������ż��������Parernt
				if (MATEFLAG == 1) tree = tree->Parent;
				//����Ҫ��ӵ���Ů����
				NewNode = (TreeNode*)malloc(sizeof(TreeNode));//����һ���ڵ�ռ�
				printf("\t������Ҫ��ӵ���Ů����: \n");
				scanf("%s", NewNode->Name);
				//����Ҫ��ӵ���Ů�Ա�
				getchar();//ȡ���������Ļس�
				printf("\t������Ҫ��ӵ���Ů�Ա�: \n");
				scanf("%c",&(NewNode->Kind));
				//����Ů�ڵ�͸������ӹ�ϵ
				num = tree->Num;
				//���ӽڵ��ʼ��
				NewNode->NextNode[0] = NULL;
				NewNode->Num = 0;
				tree->NextNode[num+1]=NewNode;
				NewNode->Parent = tree;
				tree->Num = tree->Num + 1;//������Ŀ��1
				printf("--------�����Ů�ɹ�!--------\n");
				system("pause");//��ʱ
				break;
			case 'b':
			case 'B':
				//�����������
				system("cls");//����
				printf("\n\t\t\t���ĳ����ż��Ϣ\n\n");
				printf("\t\t\t�������Ǹ��˵�������");
				scanf("%s", name);
				tree = SearchTree(tree, name, 20);
				//�ж���û���ҵ�
				if (tree == NULL)
				{
					printf("\n\t\t\tû���ҵ�����ˣ����������Ƿ���ȷ��\n");
					fflush(stdin);//����ַ�������
					getchar();//�ȴ�
					Sleep(1000);//�ӳ�
					break;
				}
				if (MATEFLAG == 1)
				{
					printf("\n\t\t\t���˲��Ǽ���ֱϵ�����������Ƿ���ȷ��\n");
					fflush(stdin);//����ַ�������
					getchar();//ȡ���������Ļس�
					Sleep(1000);//�ӳ�
					break;
				}
				//�����ż����
				NewNode = (TreeNode*)malloc(sizeof(TreeNode));
				printf("\n\t\t\t������Ҫ��ӵ�����ż��������");
				scanf("%s", NewNode->Name);
				//�����ż�Ա�
				if (tree->Kind == 'B' || tree->Kind == 'b')
				{
					NewNode->Kind = 'G';
				}
				else
				{
					NewNode->Kind = 'B';
				}
				//ȷ����ż�븸�ڵ�Ĺ�ϵ
				NewNode->NextNode[0] = NULL;
				NewNode->Num = 0;
				tree->NextNode[0] = NewNode;
				NewNode->Parent = tree;
				printf("\n\t\t\t�����ż�ɹ���\n");
				fflush(stdin);//����ַ�������
				getchar();//�ȴ�
				Sleep(1000);//��ʱ
				break;			
			case 'c':
			case 'C':
				printf("\t--------�������Ѿ�����!--------\n");
				system("pause");//�ӳ�
				break;
		}
		if (c == 'c' || c == 'C')
		{
			break;
		}
	}
}
//������м�����Ϣ����
void OutPutAll(TreeNode *tree) {
    //��������������Ա�
	int flag = 0;//��ʼ��Ĭ��Ϊ���еģ�����Ů��ֵ��Ϊ1
	int i = 0;//����ѭ��������Ⱥ�����Ϣ
	printf("����: %s �Ա�: ", tree->Name);
	if (tree->Kind == 'G' || tree->Kind == 'g')
	{
		printf("Ů\n");
		flag = 1;//�����Ա�ΪŮ
	}
	else
	{
		printf("��\n");//����Ϊ��
	}
//���������ż�������Ա�ȸ�����Ϣ
	if (!(tree->NextNode[0]) || strcmp(tree->NextNode[0]->Name, "0") == 0)
	{
		printf("�ó�Աû����ż����Ů!\n");//Ĭ��û����ż��û����Ů
		return;
	}
	if (flag == 1)//��ʱ�Ա�ΪŮ
	{
		printf("�ɷ��������: %s \n", tree->NextNode[0]->Name);
	}
	else
	{
		printf("���ӵ�������: %s \n", tree->NextNode[0]->Name);
	}
//ѭ��������Ⱥ����������Ա����Ϣ
	for (i = 1; i <= tree->Num; i++)
	{
		printf("%s�ĵ�%d�����ӵ�������: %s �Ա���: ", tree->Name, i, tree->NextNode[i]->Name);
		if (tree->NextNode[i]->Kind == 'G' || tree->NextNode[i]->Kind == 'g')
		{
			printf("Ů\n");
		}
		else
		{
			printf("��\n");
		}
	}
//�ݹ�������ӽڵ���Ϣ
	for (i = 1; i <= tree->Num; i++)
	{
		OutPutAll(tree->NextNode[i]);
	}
}
//�ݹ齨����
//treeΪ��ǰ�����Ľڵ㣬�������Ϊ�ǵ�ǰ�ĸ��ڵ㣨��һ��ִ�е�ʱ��,�ǴӸ��ڵ�����ģ�
void CreateTree(TreeNode *tree) {
	//����һ����ż�ڵ㣬Ϊ��ǰ�ڵ�����һ����ż�ڵ�
	TreeNode *NewNode;//��ż�ڵ�
	NewNode = (TreeNode*)malloc(sizeof(TreeNode));//����һ���洢�ռ�
	tree->NextNode[0] = NewNode;//NextNode�ĵ�һ��λ�ô洢��ż������λ��Ϊ���ӽڵ�
	//������ż����
	printf("��������ż����: \n");
	scanf("%s", NewNode->Name);
	//���뵱ǰ�����Ľڵ�ĺ�����Ŀ
	printf("�����뺢����Ŀ: \n");
	scanf("%d", &(tree->Num));//��ΪNum��int���ͣ���Ҫ��&��ַ�����и�ֵ
	//�ж���ż�����������0������һ��Ҷ�ӽڵ�--����Ů���޺��ӣ����ҵ�ǰ�ڵ�ĺ�������Ϊ0
	if (strcmp(NewNode->Name, "0") == 0 && tree->Num == 0)
		return;
	//��ż�ڵ㴦��
	if (tree->Kind == 'g' || tree->Kind == 'G')
	{
		NewNode->Kind = 'B';//��ǰ�ڵ������G��Ů������ô������ż����B���У�
	}
	else
	{
		NewNode->Kind = 'G';
	}
	NewNode->Num = 0;//����ҪΪ��ż��ӡ�Ӻ��ӣ��Ӻ��Ӵ�ӡ�Ĺ��������ɷ�Ľڵ��д�ӡ������ˣ�Ĭ������£����Ӳ��ڵ�ǰ��ż�£���ֱϵ�����У�
	NewNode->NextNode[0] = NULL;//�µĺ��ӽڵ�����ż
	tree->NextNode[0] = NewNode;//����ż�ڵ�ָ������ǰ��tree�ڵ㣬NextNode�ĵ�һ��λ�ô洢��ż������λ��Ϊ����
	tree->NextNode[0]->Parent = tree;//ָ����ż�ڵ�ĸ��ڵ�Ϊ��ǰ�����Ľڵ�
	//��ż�ڵ㴦��
	//ѭ���ݹ�Ľ������ӽڵ�
	int i;//����ѭ���ı���
	for (i = 1; i <= tree->Num; i++)
	{
		//����һ�����ӽڵ�
		TreeNode *ChildNode;//���ӽڵ�
		ChildNode = (TreeNode*)malloc(sizeof(TreeNode));//����һ���ڵ�ռ�
		//���뺢�ӽڵ�����
		printf("������%s�ĵ�%d����������: \n", tree->Name, i);
		scanf("%s",ChildNode->Name);
		//���뺢�ӽڵ��Ա�
		printf("������%s�ĵ�%d�������Ա�: \n", tree->Name, i);
		getchar();//ȡ���������Ļس�
		scanf("%c", &(ChildNode->Kind));
		//�����ӽڵ�͸��ڵ��ϵ
		ChildNode->Num = 0;
		ChildNode->Parent = tree;
		tree->NextNode[i] = ChildNode;
		//ѭ���ݹ齨�����ӽڵ�
		CreateTree(tree->NextNode[i]);
		printf("********����ͼ�Ѿ������ɹ�!********\n");
		system("pause");//��ʱ
		break;
	}
}
//���ؽ��溯��
void Loadsystem(){
    int m;
	for (m = 0; m <= 100; m++)
	{
		printf("\n\n\n\t\t\t��ӭʹ�ü���ϵͳ\n");
		printf("\t\t\t���ڽ�����棬���Ե�\n");
		printf("\t\t\tLoading------%d%%------", m);
		system("cls");//��������
	}
}
//�˳�ϵͳ����
void quit()
{
		system("cls");//��������
		printf("\n\n\n\t\t\t����ϵͳ����Ϊ������");
		printf("\n\n\n\t\t\t��ӭ�´�ʹ�ã�лл!\n");
		printf("\n\n\n\t\t\t�����˳�,���Ե�...... \n");
		system("pause");
		exit(0);//�˳�ϵͳ������������ͷ�ļ�stdlib��
		return;
}

