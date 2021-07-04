#include<stdio.h> 
#include<stdlib.h>  
#include<string.h>
struct workers{
	char jobNo[15];       //ID号
	char name[15];        //姓名
	int miniWage;       //基本工资
	int jobPay;         //职务工资
	int subsidize;    //津贴
	int medicalInsurance;      //医疗保险
	int providentFund;    //公积金
	int grossWage;      //总工资
}em[100];

//定义各函数
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

void start() //开始界面
{
 printf("********************************************************************************");
	printf("*****************************欢迎使用工资管理系统*****************************");
 printf("*********************************************************************************\n\n\n\n\n");
	printf("\t\t\t\t     制作: \n");
	printf("\t\t\t\t        2021年6月\n\n\n\n");
	printf("\t\t\t    ***按任意键进入***\n");
}

void menu() //菜单界面
{
	printf("***菜单***\n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  1  输入  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  2  显示  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  3  查找  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  4  删除  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  5  添加  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  6  修改  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  7  统计  \n\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>  8  退出  \n\n");
	printf("说明：*如首次使用 尚未输入数据 请先输入数据 \n      *输入的数据将自动保存 \n      *再次选择输入功能时原数据将被覆盖\n\n");
}

//录入函数     
void input()
{
	int i,m;
	printf("录入的职工人数（1--100）：\n");
	scanf("%d",&m);
	for (i = 0; i < m; i++) {
		printf("请输入ID号：");
		scanf("%s",&em[i].jobNo);
		getchar();
		printf("请输入姓名：");
		scanf("%s",&em[i].name);
		getchar();
		printf("请输入基本工资：");
		scanf("%d",&em[i].miniWage);
		printf("请输入职务工资：");
		scanf("%d",&em[i].jobPay);
		printf("请输入津贴：");
		scanf("%d", &em[i].subsidize);
		printf("请输入医疗保险：");
		scanf("%d",&em[i].medicalInsurance);
		printf("请输入公积金：");
		scanf("%d",&em[i].providentFund);
		em[i].grossWage = (em[i].miniWage + em[i].jobPay + em[i].subsidize - em[i].medicalInsurance - em[i].providentFund);
		printf("\n");//计算总工资
	}
	printf("/n创建完毕！/n");
	save(m);//保存职工人数m
}

//将职工信息保存到文件中
void save(int m){
	int i;
	FILE*fp;
	if ((fp=fopen("workers.txt", "wb"))==NULL) {
		printf("打开失败\n");
		exit(0);
	}
	for (i=0; i<m; i++) {
		if (fwrite(&em[i], sizeof(struct workers), 1, fp) != 1) {
			printf("文件读写错误\n");
		}
	}
	fclose(fp);
}

//导入函数
int load(){
	FILE*fp;
	int i = 0;
	if((fp=fopen("workers.txt","rb"))==NULL){
			printf ("cannot open file\n");
			exit(0);
	}
	else{
		do {
			fread(&em[i], sizeof(struct workers), 1, fp);//读取
			i++;
		} 
		while (feof(fp)==0);//检测流上文件结束符
	}
	fclose(fp);
	return(i-1);
}

//浏览函数
void display(){
	int i;
	float sum=0,s1=0,s2=0,s3=0,s4=0,s5=0;
	int m=load();
	printf("\nID号\t姓名\t基本工资 职务工资 津贴 医疗保险 公积金 总工资 \n");
	for(i=0;i<m;i++) /*m为输入部分的职工人数*/
	{printf("\n%s\t%s\t%d\t %d\t  %d\t %d\t %d\t %d\n  ",em[i].jobNo,em[i].name,em[i].miniWage,em[i].jobPay,em[i].subsidize,em[i].medicalInsurance,em[i].providentFund,em[i].grossWage);
		//计算各项平均工资
		s1+=em[i].miniWage;
		s2+=em[i].jobPay;
		s3+=em[i].subsidize;
		s4+=em[i].medicalInsurance;
		s5+=em[i].providentFund;
		sum+=em[i].grossWage;//计算员工总工资之和
	}
	printf("\n\n各项平均工资：%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t职工平均工资为：%.1f \n",s1/m,s2/m,s3/m,s4/m,s5/m,sum/m);
}

void del()   /*删除函数 */{
	int m=load();
	int i,j,n,t,button;
	char name[20];
	printf("\n 原来的职工信息:\n");
	display(); //显示删除前的员工信息
	printf("\n");
	printf("按姓名删除:\n");
	scanf("%s",name);
	for(button=1,i=0;button&&i<m;i++)//主函数中确定button==1时各函数才可以被调用
	{
		if(strcmp(em[i].name,name)==0)//按员工姓名查找到某员工 并调出其资料
		{
			printf("\n此人原始记录为:\n");//显示选定员工的信息
			printf("\nID号\t姓名\t基本工资 职务工资 津贴 医疗保险 公积金 总工资 \n");
			printf("\n%s\t%s\t%d\t %d\t  %d\t %d\t %d\t %d\n  ",em[i].jobNo,em[i].name,em[i].miniWage,em[i].jobPay,em[i].subsidize,em[i].medicalInsurance,em[i].providentFund,em[i].grossWage);
			printf("\n确定删除 请按1,不删除请按0\n");
			scanf("%d",&n);
			if(n==1){
					for(j=i;j<m-1;j++)//从第i项开始 将后一项的各成员的值赋给前一项各对应的成员 完成对第i项的删除
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
	if(!button)//button==0表明删除已完成
	m=m-1;//总员工数减少一人
	else{
		printf("\n查无此人!\n");
	}
	printf("\n 删除后的所有职工信息:\n");
	save(m);     //调用保存函数
	display();  //调用浏览函数
	printf("\n继续删除请按1,不再删除请按0\n");
	scanf("%d",&t);
	switch(t){
		case 1:del();break;
		case 0:break;
		default :break;
	}
}

//添加函数
void add(){
	FILE*fp;
	int n;
	int count=0;
	int i;
	int m=load();
	printf("\n 原来的职工信息:\n");
	display();
	printf("\n");
	fp=fopen("emploee_list","a");
	printf("请输入想增加的职工数:\n");//确定要加入的职工数n
	scanf("%d",&n);
	for (i=m;i<(m+n);i++)//添加n名员工的信息
	{
		printf("\n 请输入新增加职工的信息:\n");
		printf("请输入职工号:  ");
		scanf("%s",&em[i].jobNo);
		getchar();
		printf("\n");
		printf("请输入姓名:  ");
		scanf("%s",em[i].name);
		getchar();
		printf("请输入基本工资:  ");
		scanf("\t%d",&em[i].miniWage);
		printf("请输入职务工资:  ");
		scanf("%d",&em[i].jobPay);
		printf("请输入津贴:  ");
		scanf("%d",&em[i].subsidize);
		printf("请输入医疗保险:  ");
		scanf("\t%d",&em[i].medicalInsurance);
		printf("请输入公积金:  ");
		scanf("%d",&em[i].providentFund);
		em[i].grossWage = (em[i].miniWage + em[i].jobPay + em[i].subsidize - em[i].medicalInsurance - em[i].providentFund);//计算该员工的总工资		
		printf("\n");
		count=count+1;
		printf("已增加的人数:\n");
		printf("%d\n",count);
	}
	printf("\n添加成功\n");
	m=m+count;//将新添加员工的人数加到总员工人数中
	printf("\n增加后的所有职工信息:\n");
	printf("\n");
	save(m);
	display();//显示添加后的信息
	fclose(fp);
}

//查询函数
void search()
{
	int t,button;	
	do{
		printf("\n按1 按工号查询\n按2 按姓名查询\n按3 回主菜单\n");
		scanf("%d",&t);
		if(t>=1&&t<=3){
			button=1;
			break;
		}
		else{
			button=0;
			printf("输入错误");
		}
	}
	while(button==0);//回到查询选择项
	while(button==1){
		switch(t)//选择查询方式
		{
			case 1:printf("按工号查询\n");
				search_jobNo();
				break;
			case 2:printf("按姓名查询\n");
				search_name();
				break;
			case 3:int main();
				break;
			default:break;
		}
	}
}

//按ID号查询
void search_jobNo(){
	char jobNo[15];
	int i,t;
	int m=load();
	printf("请输入ID号:\n");
	scanf("%s",jobNo);
	for(i=0;i<m;i++)
		if(strcmp(em[i].jobNo,jobNo)==0)
			{
				printf("\nID号\t姓名\t基本工资 职务工资 津贴 医疗保险 公积金 总工资 \n");
				printf("\n%s\t%s\t%d\t %d\t  %d\t %d\t %d\t %d\n  ",em[i].jobNo,em[i].name,em[i].miniWage,em[i].jobPay,em[i].subsidize,em[i].medicalInsurance,em[i].providentFund,em[i].grossWage);		
				break;
			}
	if(i==m){
	printf("\n对不起,查无此人\n");
	}
	printf("\n");
	printf("返回查询函数请按1,继续查询职工号请按2\n");
	scanf("%d",&t);
	switch(t)
	{
		case 1:search();
			break;
		case 2:break;
		default:break;
	}
}

//按姓名查询
void search_name()
{
	char name[30];	
	int i,t;
	int m=load();
	printf("请输入姓名:\n");
	scanf("%s",name);
	for(i=0;i<m;i++)
		if(strcmp(em[i].name,name)==0){
				printf("\n已找到,其记录为:\n");
				printf("\nID号\t姓名\t基本工资 职务工资 津贴 医疗保险 公积金 总工资 \n");
				printf("\n%s\t%s\t%d\t %d\t  %d\t %d\t %d\t %d\n  ",em[i].jobNo,em[i].name,em[i].miniWage,em[i].jobPay,em[i].subsidize,em[i].medicalInsurance,em[i].providentFund,em[i].grossWage);
			}
	if(i==m)
	printf("\n\n");
	printf("\n");
	printf("返回查询菜单请按1,继续查询姓名请按2\n");
	scanf("%d",&t);
	switch(t)
	{
		case 1:search();
			break;
		case 2:break;
		default :break;
	}
}

void modify() /*修改函数*/
{
	char jobNo[15];       //ID号
	char name[15];        //姓名
	int miniWage;       //基本工资
	int jobPay;         //职务工资
	int subsidize;    //津贴
	int medicalInsurance;      //医疗保险
	int providentFund;    //公积金
	int grossWage;      //总工资
	int b,c,i,n,t,button;
	int m=load();
	printf("\n 原来的职工信息:\n");
	display();
	printf("\n");
	printf("请输入要修改的职工的姓名:\n");
	scanf("%s",name);
	for(button=1,i=0;button&&i<m;i++)
		{
			if(strcmp(em[i].name,name)==0){
				printf("\n此人原始记录为:\n");
				printf("ID号\t姓名\t基本工资\t职务工资\t津贴\t医疗保险\t公积金\t总工资 \n");
				printf("\n%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n  ",em[i].jobNo,em[i].name,em[i].miniWage,em[i].jobPay,em[i].subsidize,em[i].medicalInsurance,em[i].providentFund,em[i].grossWage);
					printf("\n确定 按1 ; 不修改请按0\n");
					scanf("%d",&n);
					if(n==1){
							printf("\n需要进行修改的选项\n 1.职工号 2.姓名 3.基本工资 4.职务工资 5.津贴 6.医疗保险 7.公积金 8.返回上层\n");
							printf("请选择序号1-8:\n");
							scanf("%d",&c);
							if(c>8||c<1)
								printf("\n选择错误,请重新选择!\n");
						}
					button=0;
				}
		}
	if(button==1)
		printf("\n查无此人\n");
	do{			
		switch(c)      /*因为当找到第i个职工时,for语句后i自加了1,所以下面的应该把改后的信息赋值给第i-1个人*/
			{
				case 1:printf("职工号改为: ");
					scanf("%s",jobNo);
					strcpy(em[i-1].jobNo,jobNo);
					break;
				case 2:printf("姓名改为: ");
					scanf("%s",name);
					strcpy(em[i-1].name,name);
					break;
				case 3:printf("基本工资改为: ");
					getchar();
					scanf("%d",&miniWage);
					em[i-1].miniWage=miniWage;
					em[i-1].grossWage=( em[i-1].miniWage+ em[i-1].jobPay+ em[i-1].subsidize- em[i-1].medicalInsurance- em[i-1].providentFund);
					break;
				case 4:printf("职务工资改为: ");
					scanf("%d",&jobPay);
					em[i-1].jobPay=jobPay;
					em[i-1].grossWage=( em[i-1].miniWage+ em[i-1].jobPay+ em[i-1].subsidize- em[i-1].medicalInsurance- em[i-1].providentFund);
					break;
				case 5:printf("津贴改为: ");
					scanf("%d",&subsidize);
					em[i-1].subsidize=subsidize;
					em[i-1].grossWage=( em[i-1].miniWage+ em[i-1].jobPay+ em[i-1].subsidize- em[i-1].medicalInsurance- em[i-1].providentFund);
					break;
				case 6:printf("医疗保险改为: ");
					scanf("%d",&medicalInsurance);
					em[i-1].medicalInsurance=medicalInsurance;
					em[i-1].grossWage=( em[i-1].miniWage+ em[i-1].jobPay+ em[i-1].subsidize- em[i-1].medicalInsurance- em[i-1].providentFund);
					break;
				case 7:printf("公积金改为: ");
					scanf("%d",&providentFund);
					em[i-1].providentFund=providentFund;
					em[i-1].grossWage=( em[i-1].miniWage+ em[i-1].jobPay+ em[i-1].subsidize- em[i-1].medicalInsurance- em[i-1].providentFund);
					break;
				case 8:modify();
					break;
			}
			printf("\n");
			printf("\n\n 确定修改 请按1 ; 重新修改 请按2:  \n");
			scanf("%d",&b);
		}
	while(b==2);
	printf("\n修改后的所有职工信息:\n");
	printf("\n");
	save(m);
	display();
	printf("\n按1 继续修改 ,不再修改请按0\n");
	scanf("%d",&t);
	switch(t)
	{
		case 1:modify();
			break;
		case 0:break;
		default :break;
	}
}

void sta()//统计函数
{
	int i,j,t1,t4,t5,t6,t7,t8,m;
	char t2[20],t3[20];
	printf("前几个员工的总工资排序：");
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
	printf("\nID号\t姓名\t基本工资 职务工资 津贴 医疗保险 公积金 总工资 \n");
	for(i=0;i<m;i++){
	printf("\n%s\t%s\t%d\t %d\t  %d\t %d\t %d\t %d\n  ",em[i].jobNo,em[i].name,em[i].miniWage,em[i].jobPay,em[i].subsidize,em[i].medicalInsurance,em[i].providentFund,em[i].grossWage);
	}
}

int main()//主函数
{
	int n,button;
	char a;
	start();
	menu();
	do{
		printf("功能选择(1--8):\n");
		scanf("%d",&n);
		if(n>=1&&n<=7){
			button=1;
			break;
		}
		else{
			button=0;
			printf("您输入有误,请重新选择!");
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
		printf("按任意键继续\n");
		menu(); /*调用菜单函数*/
		printf("功能选择(1--8):\n");
		scanf("%d",&n);
		printf("\n");
	}	
}

