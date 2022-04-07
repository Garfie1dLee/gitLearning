#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<math.h>


#define LIST_INIT_SIZE 256 //线性表存储空间的初始分配量
static int count[LIST_INIT_SIZE];

struct HNode {
	int *Data;         /* 存储元素的数组 */
	int Size;          /* 当前元素个数 */
	int Capacity;      /* 堆的最大容量 */
};
typedef struct HNode *Heap;

Heap CreateMinHeap(int MaxSize)
{
	Heap H = (Heap)malloc(sizeof(struct HNode));
	H->Data = (int *)malloc((MaxSize + 1) * sizeof(int));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Data[0] = -1;
	return H;
}
bool IsFull(Heap H)
{
	return (H->Size == H->Capacity);
}
bool IsEmpty(Heap H)
{
	return (H->Size == 0);
}

bool Insert(Heap &H, int X)
{
	int i;
	if (IsFull(H)) {
		printf("最小堆已满");
		return false;
	}
	i = ++H->Size;
	for (; H->Data[i / 2] > X; i /= 2)
		H->Data[i] = H->Data[i / 2];
	H->Data[i] = X;
	return true;
}
int ERROR=-1;
int Deletemin(Heap &H)
{
	int Parent, Child;
	int MinItem, X;

	if (IsEmpty(H)) {
		printf("最小堆已为空");
		return ERROR;
	}

	MinItem = H->Data[1];

	X = H->Data[H->Size--];
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;
		if ((Child != H->Size) && (H->Data[Child]>H->Data[Child + 1]))
			Child++;
		if (X <= H->Data[Child]) break;
		else
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = X;
	return MinItem;
}
void listprint(Heap H)
{
    for(int i=1;i<=H->Size;i++)
        printf("%d  ",H->Data[i]);
}


int ReadFile(char filename[])
{
    char buff[1024];
    FILE* fp;
    int len;
    int typecount=0;
    if ((fp = fopen(filename,"r")) == NULL)
	{
		perror("fail to read the file");
		exit(1);
	}
    while(fgets(buff,1024,fp))
    {
        len=strlen(buff);
        for(int i=0;i<len;i++)
        {
            if(buff[i]>256) printf("含有非法字符");
            count[buff[i]]++;
        }
    }
    for(int j=0;j<256;j++)
            if(count[j]!=0)
            typecount++;
    fclose(fp);
        return typecount;

}


typedef struct ElemType{
    int value;
    char name;
};

typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}SqList;

int InitSqList(SqList &L)
{
    L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    L.length=0; //当前长度
    L.listsize=LIST_INIT_SIZE; //当前分配量
    return 0;
}

int ListInsert(SqList &L,ElemType e)
{
    L.elem[L.length]=e;
    L.length++;
    return 0;
}


ElemType ListPeek(SqList L)
{
    return L.elem[0];
}

void ListSort(SqList &L)
{
     for (int i=0;i<L.length-1;i++)
        for (int j=0;j<L.length-i-1;j++)
        {
            if (L.elem[j].value>L.elem[j+1].value) {
                ElemType temp=L.elem[j];
                L.elem[j]=L.elem[j+1];
                L.elem[j+1]=temp;
            }
        }
}

void ListPrint(SqList L)
{
    for(int i=0;i<L.length;i++)
        if(L.elem[i].name=='\n')
        printf("name=换行,value=%d\n",L.elem[i].value);
        else printf("name=%c,value=%d\n",L.elem[i].name,L.elem[i].value);
    printf("------------------------\n");
}

void JoinElemTypeNode(SqList &L)
{
     for(int i=0;i<LIST_INIT_SIZE;i++)
        if(count[i]!=0)
    {
       ElemType newone={count[i],(char)i};
       ListInsert(L,newone);
    }
    ListSort(L);
    ListPrint(L);
}



typedef struct
{
    int value;
    char name;
    int parent, lchild, rchild;
}HTNode,*HuffmanTree;
typedef char * *HuffmanCode;

int min(HuffmanTree ht,int n){
	int i,ret;
	int temp=INT_MAX;
	for(i=1;i<=n;i++)
		if(ht[i].value<temp&&ht[i].parent==0){
			temp=ht[i].value;
			ret=i;
		}
	ht[ret].parent=1;
	return ret;
}
int newSearch(HuffmanTree HT,int n,int e)
{
    for(int i=1;i<=n;i++)
		if(HT[i].value==e&&HT[i].parent==0){
			HT[i].parent=1;
			return i;
		}
}
void Select(HuffmanTree HT,int n,int &s1,int &s2){
	s1=min(HT,n);
	s2=min(HT,n);
}

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, SqList L, int n)
{
	int i,s1,s2,m,c,start,f;
	HuffmanTree p;
	char *cd;
	m=2*n-1;
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
for(p=HT+1,i=1; i<=n; ++i,++p){
	p->value=L.elem[i-1].value;
	p->name=L.elem[i-1].name;
	p->parent=0;
	p->lchild=0;
	p->rchild=0;
}
for(;i<=m; ++i,++p){
	p->value=0;
	p->name={};
	p->parent=0;
	p->lchild=0;
	p->rchild=0;
}  //对叶子之后的存储单元清零

Heap H=CreateMinHeap(m);
   for(int i=1;i<=n;i++)
    Insert(H,L.elem[i-1].value);
    listprint(H);
    printf("\n");

for(i=n+1;i<=m; ++i){ //建Huffman树
	//Select(HT, i-1, s1, s2);
	int e1=Deletemin(H);int e2=Deletemin(H);
	s1=newSearch(HT,i-1,e1);
	s2=newSearch(HT,i-1,e2);
	//在HT[1…i-1]选择parent为0且weight最小的两个结点，其序号分别为
	//s1和s2
	HT[s1].parent=i; HT[s2].parent=i;
	HT[i].lchild=s1; HT[i].rchild=s2; //s1、s2分别作为i的左右孩子
	HT[i].value=HT[s1].value+ HT[s2].value;
	Insert(H,HT[i].value);
}


	HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
	//分配n个字符编码的头指针向量
	cd=(char*) malloc(n*sizeof(char)); //分配求编码的工作空间
	cd[n-1]='\0'; //编码结束符（从cd[0]~cd[n-1]为合法空间）
for(i=1;i<=n;++i){ //逐个字符求Huffman编码
	start=n-1; //编码结束符位置
	for(c=i,f=HT[i].parent; f!=0; c=f, f=HT[f].parent)
	//从叶子到根逆向求编码
	if(HT[f].lchild==c) cd[--start]='0';
	else cd[--start]='1';
	HC[i]=(char*)malloc((n-start)*sizeof(char));
	//为第i个字符编码分配空间
	strcpy(HC[i],&cd[start]); //从cd复制编码串到HC
	}
	free(cd); //释放工作空间
}

void WriteCode(char filename[],HuffmanCode HC,HuffmanTree HT,int n)
{
    FILE *fp = NULL;
    fp = fopen(filename, "w+");
    for(int i=1;i<=n;i++)
    {
        char w[30]={HT[i].name};
        strcat(w,HC[i]);
        strcat(w,"\n");
        fputs(w, fp);
    //puts(w);
    }
	fclose(fp);
}

void PrintHuffmanCode(HuffmanTree HT,int n)
{
    for(int i=1;i<=2*n-1;i++)
        printf("%d \n",HT[i].value);
}
void ReadandCompressFile2(char filename[],char ALL[],char OUT[],int n,HuffmanCode HC,HuffmanTree HT,char outfilename[])
{
    char buff[1024];
    FILE* fp;
    if ((fp = fopen(filename,"r")) == NULL)
	{
		perror("fail to read the file");
		exit(1);
	}
    while(fgets(buff,1024,fp))
    {
        strcat(ALL,buff);
    }
    //puts(ALL);
    //printf("lengthjhshdhs=%d",strlen(ALL));


    int length=strlen(ALL);
    for(int i=0;i<length;i++)
        for(int j=1;j<=n;j++)
            if(ALL[i]==HT[j].name)
            strcat(OUT,HC[j]);
    fp = fopen(outfilename, "wb+");
    puts(OUT);
    printf("\nlengthjhshdhs=%d\n",strlen(OUT));
    int totalcount=0;

    //compresss
    for(int i=7;i<strlen(OUT);i+=8){
        int temp=0;
        for (int j=i;i-j<8;j--)
        temp+=(OUT[j]-48)*(pow(2,(i-j)));
       // if(temp==0)printf("-----------------------------------------------------------------------------------may error");
        //if(temp==26){temp=0;}
        fputc(temp,fp);
        printf("%d ",temp);
        totalcount++;
    }
    fclose(fp);
    printf("\ntotalcount%d\n",totalcount);
}
typedef struct HFCode{
    char name;
    char c[1024];
};
void del_char(char a[],char c)
{
    int i,j;
    for(i=0,j=0; *(a+i)!='\0'; i++)
    {
        if(*(a+i)==c)
             continue;
         else
         {
             *(a+j)=*(a+i);
             j++;
         }
     }
     *(a+j)='\0';
 }
void Getmessage(char filename[],HFCode IN[])
{
    char buff[1024];
    FILE* fp;
    if ((fp = fopen(filename,"r")) == NULL)
	{
		perror("fail to read the file");
		exit(1);
	}
	int count1=1;
	IN[0].name='a';
	strcat(IN[0].c,"a");
	while(fgets(buff,1024,fp))
    {
        if(buff[0]=='\n')
        {
            IN[count1].name='\n';
             fgets(buff,1024,fp);
             strtok(buff, "\n");
             strcpy(IN[count1].c,buff);
             count1++;
        }
        else
        {
        del_char(buff,'\n');
        IN[count1].name=buff[0];
        strcpy(IN[count1].c,buff+1);
        count1++;
        }
    }

    fclose(fp);

}
void fun(char*s)
{
   int i,j=0,n;
   char temp;
   n=strlen(s);
    for(i=0;i<n/2;i++){
        temp = s[i];
        s[i] = s[n-1-i];
        s[n-1-i] = temp;
    }
}
void substring(char a[],char b[],int start,int last)
{
    int i;
    for(i=0;i<last-start;i++)
    {
        b[i]=a[start+i];
    }
    b[++i]='\0';
}
void DeCompressFile(char filename[],HFCode USE[],char outfile[])
{
    FILE* fp;
    if ((fp = fopen(filename,"rb")) == NULL)
	{
		perror("fail to read the file");
		exit(1);
	}
    char laststr[50000]={};
    int e;
    while((e=fgetc(fp))!=EOF)
    {
            printf("%d  ",e);
            char str[50]={};
            int temp=0;
            //if(e==0)
           //    temp=26;
           // else
               temp=e;
            for(int j=0;j<8;j++)
            {
                int compare=abs(temp%2);
                if(compare==1)
                    strcat(str,"1");
                else
                    strcat(str,"0");
                temp=temp/2;
            }
            fun(str);
            strcat(laststr,str);
    }
    puts("---------------------------------------------------------");
    puts(laststr);

    int uselen;
    fp = fopen(outfile, "w+");
    for(int i=0;USE[i].name!=NULL;i++)
        uselen=i;
    printf("%d\n",uselen);
    printf("%d",strlen(laststr));


    for(int i=0;i<strlen(laststr);i++)
      for(int j=i;j<strlen(laststr);j++){
           char strin[50000]={};substring(laststr,strin,i,j);
           for(int k=1;k<=uselen;k++)
            if(strcmp(strin,USE[k].c)==0)
            {
                i=j;fputc(USE[k].name,fp);
                break;
            }
            }

    fclose(fp);




}
int main()
{
    printf("输入1 进行文件压缩        输入2进行文件解压缩\n");
    char ch=getchar();
    char filename2[]="huffmancode.txt";
    char outfilename[]="code.dat";
    if(ch=='1')
    {
    printf("请确认文件source.txt在同一目录内，如果无反应则文件内包含非ASCII字符，确认后输入回车\n");
    getchar();
    getchar();
    char filename[]="source.txt";
    int typecount=ReadFile(filename);
    printf("共%d种字符\n",typecount);
    SqList L;
    InitSqList(L);
    JoinElemTypeNode(L);
    HuffmanCode HC;
    HuffmanTree HT;
    HuffmanCoding(HT,HC,L,typecount);
    WriteCode(filename2,HC,HT,typecount);
    char OUT[500000]="\0";
    char ALL[500000]="\0";
    ReadandCompressFile2(filename,ALL,OUT,typecount,HC,HT,outfilename);
    }
    if(ch=='2')
    {
    printf("请输入输出文件名称,保证哈夫曼编码文件huffmancode.txt与输出文件code.dat在同一目录内\n");
    char orfile[30];
    scanf("%s",orfile);
    HFCode *Co=(HFCode*)malloc((256)*sizeof(HFCode));
    Getmessage(filename2,Co);
    //for(int i=1;i<=typecount;i++)
     //  printf("name=%c,len=%d,code=%s \n",Co[i].name,strlen(Co[i].c),(Co[i].c));
   //for(int i=0;i<strlen(Co[0].c);i++)
        //printf("%c",Co[0].c[0]);
    DeCompressFile(outfilename,Co,orfile);
    }






    return 0;
}
