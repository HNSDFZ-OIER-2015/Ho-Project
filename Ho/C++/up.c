#include <stdio.h>
#include <stdlib.h>

#define WAR "\033[1;33m[*]Warning:\033[0m" 
#define EOR "\033[1;31m[x]ERROR:\033[0m"
#define NICE "\033[1;32m[√]Nice:\033[0m"

void finish()
{
	int flag;

	printf("正在尝试覆盖本地系统hosts...\n");

	flag=system("cp hosts /etc/");
	if(flag!=0)
	{
		printf(EOR"覆盖失败！请以root权限运行本程序！\n");
		exit(2);
	}

	printf(NICE"覆盖成功！\n越过长城，走向世界！\n\n");

	exit(0);
	
}

void test(char* c)
{
	char x[1000];
	int flag;

	sprintf(x,"wget -q %s -O hosts -T 10",c);

	flag=system(x);

	if(flag!=0)
	{
		printf(EOR"此源无效！\n");
		return;
	}

	printf(NICE"此源有效！\n");
	finish();
}

main()
{	
	int n,i,flag=0;
	char a[1000];

	flag=system("wget -q http://ruanxingzhi.github.io/list.txt -O list.tmp -T 10");

	if(flag!=0) printf(WAR"没有找到在线源列表。将使用本地列表。 \n");

	else
	{
		printf(NICE"成功更新在线源列表。\n");
		system("mv list.tmp list.txt");
	}

	freopen("list.txt","r",stdin);

	if(scanf("%d",&n)==EOF)
	{
		printf(EOR"源列表为空！请联系ruanxingzhi@gmail.com!\n");
		exit(1);
	}

	printf(NICE"找到%d个链接。\n",n);

	for(i=0;i<n;i++)
	{
		printf("正在尝试源[%d]......\n",i);
		scanf("%s",a);
		test(a);
	}

	printf(EOR"所有源全部失效！请联系ruanxingzhi@gmail.com!\n");
	exit(4);

}