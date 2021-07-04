#include<stdio.h> 
#include<stdlib.h>  
#include<string.h>
struct workers{
	char jobNo[15];       //ID��
	char name[15];        //����
	int miniWage;       //��������
	int jobPay;         //ְ����
	int subsidize;    //����
	int medicalInsurance;      //ҽ�Ʊ���
	int providentFund;    //������
	int grossWage;      //�ܹ���
}em[100];

//���������
void menu();
void input();
void save(int);
void display();
void del();
void add();
void search();
void search_jobNo();
void search_name();
void modify();
void sta();
void start();

void start() //��ʼ����
{
 printf("********************************************************************************");
	printf("*****************************��ӭʹ�ù��ʹ���ϵͳ*****************************");
 printf("*********************************************************************************\n\n\n\n\n");
	printf("\t\t\t\t     ����: \n");
	printf("\t\t\t\t        2021��6��\n\n\n\n");
	printf("\t\t\t    ***�����������***\n");
}

void menu() //�˵�����
{
	printf("***�˵�***\n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  1  ����  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  2  ��ʾ  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  3  ����  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  4  ɾ��  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  5  ���  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  6  �޸�  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  7  ͳ��  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  8  �˳�  \n\n");
	printf("˵����*���״�ʹ�� ��δ�������� ������������ \n      *��������ݽ��Զ����� \n      *�ٴ�ѡ�����빦��ʱԭ���ݽ�������\n\n");
}

//¼�뺯��     
void input()
{
	int i,m;
	printf("¼���ְ��������1--100����\n");
	scanf("%d",&m);
	for (i = 0; i < m; i++) {
		printf("������ID�ţ�");
		scanf("%s",&em[i].jobNo);
		getchar();
		printf("������������");
		scanf("%s",&em[i].name);
		getchar();
		printf("������������ʣ�");
		scanf("%d",&em[i].miniWage);
		printf("������ְ���ʣ�");
		scanf("%d",&em[i].jobPay);
		printf("�����������");
		scanf("%d", &em[i].subsidize);
		printf("������ҽ�Ʊ��գ�");
		scanf("%d",&em[i].medicalInsurance);
		printf("�����빫����");
		scanf("%d",&em[i].providentFund);
		em[i].grossWage = (em[i].miniWage + em[i].jobPay + em[i].subsidize - em[i].medicalInsurance - em[i].providentFund);
		printf("\n");//�����ܹ���
	}
	printf("/n������ϣ�/n");
	save(m);//����ְ������m
}

//��ְ����Ϣ���浽�ļ���
void save(int m){
	int i;
	FILE*fp;
	if ((fp=fopen("workers.txt", "wb"))==NULL) {
		printf("��ʧ��\n");
		exit(0);
	}
	for (i=0; i<m; i++) {
		if (fwrite(&em[i], sizeof(struct workers), 1, fp) != 1) {
			printf("�ļ���д����\n");
		}
	}
	fclose(fp);
}

//���뺯��
int load(){
	FILE*fp;
	int i = 0;
	if((fp=fopen("workers.txt","rb"))==NULL){
			printf ("cannot open file\n");
			exit(0);
	}
	else{
		do {
			fread(&em[i], sizeof(struct workers), 1, fp);//��ȡ
			i++;
		} 
		while (feof(fp)==0);//��������ļ�������
	}
	fclose(fp);
	return(i-1);
}

//�������
void display(){
	int i;
	float sum=0,s1=0,s2=0,s3=0,s4=0,s5=0;
	int m=load();
	printf("\nID��\t����\t�������� ְ���� ���� ҽ�Ʊ��� ������ �ܹ��� \n");
	for(i=0;i<m;i++) /*mΪ���벿�ֵ�ְ������*/
	{printf("\n%s\t%s\t%d\t %d\t  %d\t %d\t %d\t %d\n  ",em[i].jobNo,em[i].name,em[i].miniWage,em[i].jobPay,em[i].subsidize,em[i].medicalInsurance,em[i].providentFund,em[i].grossWage);
		//�������ƽ������
		s1+=em[i].miniWage;
		s2+=em[i].jobPay;
		s3+=em[i].subsidize;
		s4+=em[i].medicalInsurance;
		s5+=em[i].providentFund;
		sum+=em[i].grossWage;//����Ա���ܹ���֮��
	}
	printf("\n\n����ƽ�����ʣ�%.1f\t%.1f\t%.1f\t%.1f\t%.1f\tְ��ƽ������Ϊ��%.1f \n",s1/m,s2/m,s3/m,s4/m,s5/m,sum/m);
}

void del()   /*ɾ������ */{
	int m=load();
	int i,j,n,t,button;
	char name[20];
	printf("\n ԭ����ְ����Ϣ:\n");
	display(); //��ʾɾ��ǰ��Ա����Ϣ
	printf("\n");
	printf("������ɾ��:\n");
	scanf("%s",name);
	for(button=1,i=0;button&&i<m;i++)//��������ȷ��button==1ʱ�������ſ��Ա�����
	{
		if(strcmp(em[i].name,name)==0)//��Ա���������ҵ�ĳԱ�� ������������
		{
			printf("\n����ԭʼ��¼Ϊ:\n");//��ʾѡ��Ա������Ϣ
			printf("\nID��\t����\t�������� ְ���� ���� ҽ�Ʊ��� ������ �ܹ��� \n");
			printf("\n%s\t%s\t%d\t %d\t  %d\t %d\t %d\t %d\n  ",em[i].jobNo,em[i].name,em[i].miniWage,em[i].jobPay,em[i].subsidize,em[i].medicalInsurance,em[i].providentFund,em[i].grossWage);
			printf("\nȷ��ɾ�� �밴1,��ɾ���밴0\n");
			scanf("%d",&n);
			if(n==1){
					for(j=i;j<m-1;j++)//�ӵ�i�ʼ ����һ��ĸ���Ա��ֵ����ǰһ�����Ӧ�ĳ�Ա ��ɶԵ�i���ɾ��
					{
						strcpy(em[j].name,em[j+1].name);
						strcpy(em[j].jobNo,em[j+1].jobNo);
						em[j].miniWage=em[j+1].miniWage;
						em[j].jobPay=em[j+1].jobPay;
						em[j].subsidize=em[j+1].subsidize;
						em[j].medicalInsurance=em[j+1].medicalInsurance;
						em[j].providentFund=em[j+1].providentFund;
						em[j].grossWage=em[j+1].grossWage;
					}
					button=0;
				}
		}
	}
	if(!button)//button==0����ɾ�������
	m=m-1;//��Ա��������һ��
	else{
		printf("\n���޴���!\n");
	}
	printf("\n ɾ���������ְ����Ϣ:\n");
	save(m);     //���ñ��溯��
	display();  //�����������
	printf("\n����ɾ���밴1,����ɾ���밴0\n");
	scanf("%d",&t);
	switch(t){
		case 1:del();break;
		case 0:break;
		default :break;
	}
}

//��Ӻ���
void add(){
	FILE*fp;
	int n;
	int count=0;
	int i;
	int m=load();
	printf("\n ԭ����ְ����Ϣ:\n");
	display();
	printf("\n");
	fp=fopen("emploee_list","a");
	printf("�����������ӵ�ְ����:\n");//ȷ��Ҫ�����ְ����n
	scanf("%d",&n);
	for (i=m;i<(m+n);i++)//���n��Ա������Ϣ
	{
		printf("\n ������������ְ������Ϣ:\n");
		printf("������ְ����:  ");
		scanf("%s",&em[i].jobNo);
		getchar();
		printf("\n");
		printf("����������:  ");
		scanf("%s",em[i].name);
		getchar();
		printf("�������������:  ");
		scanf("\t%d",&em[i].miniWage);
		printf("������ְ����:  ");
		scanf("%d",&em[i].jobPay);
		printf("���������:  ");
		scanf("%d",&em[i].subsidize);
		printf("������ҽ�Ʊ���:  ");
		scanf("\t%d",&em[i].medicalInsurance);
		printf("�����빫����:  ");
		scanf("%d",&em[i].providentFund);
		em[i].grossWage = (em[i].miniWage + em[i].jobPay + em[i].subsidize - em[i].medicalInsurance - em[i].providentFund);//�����Ա�����ܹ���		
		printf("\n");
		count=count+1;
		printf("�����ӵ�����:\n");
		printf("%d\n",count);
	}
	printf("\n��ӳɹ�\n");
	m=m+count;//�������Ա���������ӵ���Ա��������
	printf("\n���Ӻ������ְ����Ϣ:\n");
	printf("\n");
	save(m);
	display();//��ʾ��Ӻ����Ϣ
	fclose(fp);
}

//��ѯ����
void search()
{
	int t,button;	
	do{
		printf("\n��1 �����Ų�ѯ\n��2 ��������ѯ\n��3 �����˵�\n");
		scanf("%d",&t);
		if(t>=1&&t<=3){
			button=1;
			break;
		}
		else{
			button=0;
			printf("�������");
		}
	}
	while(button==0);//�ص���ѯѡ����
	while(button==1){
		switch(t)//ѡ���ѯ��ʽ
		{
			case 1:printf("�����Ų�ѯ\n");
				search_jobNo();
				break;
			case 2:printf("��������ѯ\n");
				search_name();
				break;
			case 3:int main();
				break;
			default:break;
		}
	}
}

//��ID�Ų�ѯ
void search_jobNo(){
	char jobNo[15];
	int i,t;
	int m=load();
	printf("������ID��:\n");
	scanf("%s",jobNo);
	for(i=0;i<m;i++)
		if(strcmp(em[i].jobNo,jobNo)==0)
			{
				printf("\nID��\t����\t�������� ְ���� ���� ҽ�Ʊ��� ������ �ܹ��� \n");
				printf("\n%s\t%s\t%d\t %d\t  %d\t %d\t %d\t %d\n  ",em[i].jobNo,em[i].name,em[i].miniWage,em[i].jobPay,em[i].subsidize,em[i].medicalInsurance,em[i].providentFund,em[i].grossWage);		
				break;
			}
	if(i==m){
	printf("\n�Բ���,���޴���\n");
	}
	printf("\n");
	printf("���ز�ѯ�����밴1,������ѯְ�����밴2\n");
	scanf("%d",&t);
	switch(t)
	{
		case 1:search();
			break;
		case 2:break;
		default:break;
	}
}

//��������ѯ
void search_name()
{
	char name[30];	
	int i,t;
	int m=load();
	printf("����������:\n");
	scanf("%s",name);
	for(i=0;i<m;i++)
		if(strcmp(em[i].name,name)==0){
				printf("\n���ҵ�,���¼Ϊ:\n");
				printf("\nID��\t����\t�������� ְ���� ���� ҽ�Ʊ��� ������ �ܹ��� \n");
				printf("\n%s\t%s\t%d\t %d\t  %d\t %d\t %d\t %d\n  ",em[i].jobNo,em[i].name,em[i].miniWage,em[i].jobPay,em[i].subsidize,em[i].medicalInsurance,em[i].providentFund,em[i].grossWage);
			}
	if(i==m)
	printf("\n\n");
	printf("\n");
	printf("���ز�ѯ�˵��밴1,������ѯ�����밴2\n");
	scanf("%d",&t);
	switch(t)
	{
		case 1:search();
			break;
		case 2:break;
		default :break;
	}
}

void modify() /*�޸ĺ���*/
{
	char jobNo[15];       //ID��
	char name[15];        //����
	int miniWage;       //��������
	int jobPay;         //ְ����
	int subsidize;    //����
	int medicalInsurance;      //ҽ�Ʊ���
	int providentFund;    //������
	int grossWage;      //�ܹ���
	int b,c,i,n,t,button;
	int m=load();
	printf("\n ԭ����ְ����Ϣ:\n");
	display();
	printf("\n");
	printf("������Ҫ�޸ĵ�ְ��������:\n");
	scanf("%s",name);
	for(button=1,i=0;button&&i<m;i++)
		{
			if(strcmp(em[i].name,name)==0){
				printf("\n����ԭʼ��¼Ϊ:\n");
				printf("ID��\t����\t��������\tְ����\t����\tҽ�Ʊ���\t������\t�ܹ��� \n");
				printf("\n%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n  ",em[i].jobNo,em[i].name,em[i].miniWage,em[i].jobPay,em[i].subsidize,em[i].medicalInsurance,em[i].providentFund,em[i].grossWage);
					printf("\nȷ�� ��1 ; ���޸��밴0\n");
					scanf("%d",&n);
					if(n==1){
							printf("\n��Ҫ�����޸ĵ�ѡ��\n 1.ְ���� 2.���� 3.�������� 4.ְ���� 5.���� 6.ҽ�Ʊ��� 7.������ 8.�����ϲ�\n");
							printf("��ѡ�����1-8:\n");
							scanf("%d",&c);
							if(c>8||c<1)
								printf("\nѡ�����,������ѡ��!\n");
						}
					button=0;
				}
		}
	if(button==1)
		printf("\n���޴���\n");
	do{			
		switch(c)      /*��Ϊ���ҵ���i��ְ��ʱ,for����i�Լ���1,���������Ӧ�ðѸĺ����Ϣ��ֵ����i-1����*/
			{
				case 1:printf("ְ���Ÿ�Ϊ: ");
					scanf("%s",jobNo);
					strcpy(em[i-1].jobNo,jobNo);
					break;
				case 2:printf("������Ϊ: ");
					scanf("%s",name);
					strcpy(em[i-1].name,name);
					break;
				case 3:printf("�������ʸ�Ϊ: ");
					getchar();
					scanf("%d",&miniWage);
					em[i-1].miniWage=miniWage;
					em[i-1].grossWage=( em[i-1].miniWage+ em[i-1].jobPay+ em[i-1].subsidize- em[i-1].medicalInsurance- em[i-1].providentFund);
					break;
				case 4:printf("ְ���ʸ�Ϊ: ");
					scanf("%d",&jobPay);
					em[i-1].jobPay=jobPay;
					em[i-1].grossWage=( em[i-1].miniWage+ em[i-1].jobPay+ em[i-1].subsidize- em[i-1].medicalInsurance- em[i-1].providentFund);
					break;
				case 5:printf("������Ϊ: ");
					scanf("%d",&subsidize);
					em[i-1].subsidize=subsidize;
					em[i-1].grossWage=( em[i-1].miniWage+ em[i-1].jobPay+ em[i-1].subsidize- em[i-1].medicalInsurance- em[i-1].providentFund);
					break;
				case 6:printf("ҽ�Ʊ��ո�Ϊ: ");
					scanf("%d",&medicalInsurance);
					em[i-1].medicalInsurance=medicalInsurance;
					em[i-1].grossWage=( em[i-1].miniWage+ em[i-1].jobPay+ em[i-1].subsidize- em[i-1].medicalInsurance- em[i-1].providentFund);
					break;
				case 7:printf("�������Ϊ: ");
					scanf("%d",&providentFund);
					em[i-1].providentFund=providentFund;
					em[i-1].grossWage=( em[i-1].miniWage+ em[i-1].jobPay+ em[i-1].subsidize- em[i-1].medicalInsurance- em[i-1].providentFund);
					break;
				case 8:modify();
					break;
			}
			printf("\n");
			printf("\n\n ȷ���޸� �밴1 ; �����޸� �밴2:  \n");
			scanf("%d",&b);
		}
	while(b==2);
	printf("\n�޸ĺ������ְ����Ϣ:\n");
	printf("\n");
	save(m);
	display();
	printf("\n��1 �����޸� ,�����޸��밴0\n");
	scanf("%d",&t);
	switch(t)
	{
		case 1:modify();
			break;
		case 0:break;
		default :break;
	}
}

void sta()//ͳ�ƺ���
{
	int i,j,t1,t4,t5,t6,t7,t8,m;
	char t2[20],t3[20];
	printf("ǰ����Ա�����ܹ�������");
	scanf("%d",&m);	
	for(i=0;i<m;i++){
		for(j=0;j<m-i;j++){
			if(em[j].grossWage<em[j+1].grossWage){
				t1=em[j].grossWage;
				em[j].grossWage=em[j+1].grossWage;
				em[j+1].grossWage=t1;
				strcpy(t2,em[j].jobNo);
				strcpy(em[j].jobNo,em[j+1].jobNo);
				strcpy(em[j+1].jobNo,t2);
				strcpy(t3,em[j].name);
				strcpy(em[j].name,em[j+1].name);
				strcpy(em[j+1].name,t3);
				t4=em[j].miniWage;
				em[j].miniWage=em[j+1].miniWage;
				em[j+1].miniWage=t4;
				t5=em[j].jobPay;
				em[j].jobPay=em[j+1].jobPay;
				em[j+1].jobPay=t5;
				t6=em[j].subsidize;
				em[j].subsidize=em[j+1].subsidize;
				em[j+1].subsidize=t6;
				t7=em[j].medicalInsurance;
				em[j].medicalInsurance=em[j+1].medicalInsurance;
				em[j+1].medicalInsurance=t7;
				t8=em[j].providentFund;
				em[j].providentFund=em[j+1].providentFund;
				em[j+1].providentFund=t8;
			}
		}
	}
	printf("\nID��\t����\t�������� ְ���� ���� ҽ�Ʊ��� ������ �ܹ��� \n");
	for(i=0;i<m;i++){
	printf("\n%s\t%s\t%d\t %d\t  %d\t %d\t %d\t %d\n  ",em[i].jobNo,em[i].name,em[i].miniWage,em[i].jobPay,em[i].subsidize,em[i].medicalInsurance,em[i].providentFund,em[i].grossWage);
	}
}

int main()//������
{
	int n,button;
	char a;
	start();
	menu();
	do{
		printf("����ѡ��(1--8):\n");
		scanf("%d",&n);
		if(n>=1&&n<=7){
			button=1;
			break;
		}
		else{
			button=0;
			printf("����������,������ѡ��!");
		}
	}
	while(button==0);
	while(button==1){
		switch(n){
			case 1: input();
				break;
			case 2: display();
				break;
			case 3: search();
				break;
			case 4:del();
				break;
			case 5: add();
				break;
			case 6:modify();
				break;
			case 7:sta();
				break;
			case 8:exit(0);
				break;
			default :break;
			}
		getchar();
		printf("\n");
		printf("�����������\n");
		menu(); /*���ò˵�����*/
		printf("����ѡ��(1--8):\n");
		scanf("%d",&n);
		printf("\n");
	}	
}

