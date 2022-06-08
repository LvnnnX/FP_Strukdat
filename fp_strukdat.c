#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define pass (void)0
#define EACH(x, a) for (auto& x: a)
#define iread(x) scanf("%d",&x)
struct data{
    int nil[9];
};
struct data node[9],copynode[9]; //node = total kotak
struct put{
	int nil;
	struct put *next;
};
struct put *maybe,*baru;
/* input = 
+-----+-----+-----+
|0 0 0|0 0 0|0 0 0|
|0 0 0|0 0 0|0 0 0|
|0 0 0|0 0 0|0 0 0|
|-----+-----+-----|
|0 0 0|0 0 0|0 0 0|
|0 0 0|0 0 0|0 0 0|
|0 0 0|0 0 0|0 0 0|
|-----+-----+-----|
|0 0 0|0 0 0|0 0 0|
|0 0 0|0 0 0|0 0 0|
|0 0 0|0 0 0|0 0 0|
+-----+-----+-----+
*/
void view()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf(" %d ",node[i].nil[j]);
        }
        printf("\n");
    }
    
}
int cekpos(int b,int k,int n) //bisa ditaruh angka atau tidak
{
	int x = (b / 3) * 3, y = (k / 3) * 3;
    if(node[b].nil[k]==n) return 0;
	for(int i=0;i<9;i++)
	{
		if(node[b].nil[i]==n)return 0;
		if(node[i].nil[k]==n)return 0;
		if(node[x + i / 3].nil[y + i % 3]==n)return 0;
		
	}
	return 1;
}
void getnum(int b, int k) //angka apa aja yang bisa dimasukin
{
	free(maybe);
    maybe = NULL;
	for(int i=1;i<=9;i++)
	{
		if (cekpos(b,k,i)==1)
		{
            baru = malloc(sizeof(struct put));
            baru->nil = i;
            baru->next = NULL;
			if(maybe==NULL)
			{
                maybe = baru;
			}else
			{
				struct put *find;
				find = maybe;
				while(find->next!=NULL)find=find->next;
				find->next=baru;
			}
		}
	}
}
int nextnum(int b, int k) //ke kolom & baris selanjutnya yang 0
{
    for (int i = (b * 9) + k + 1; i < 9 * 9 ; i++)
    {
        if(node[i / 9].nil[i % 9]==0) return i;
    }
    return 9 * 9 + 1;
}
void setzerocpy()
{
    for (int i = 0; i < 9; i++)
    {
        memset(copynode[i].nil,0,9*sizeof(int));
    }
}
void setzero()
{
    for (int i = 0; i < 9; i++)
    {
        memset(node[i].nil,0,9*sizeof(int));
    }
    
}
void copy() //copy dari node ke copynode
{
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            copynode[i].nil[j] = node[i].nil[j];
        }
    }
    printf("\ncopy()\n");
}
void copyback() //copy dari copynode ke node
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            node[i].nil[j] = copynode[i].nil[j];
        }
        
    }
    
}
int solve(int b, int k) // solving
{
    if(b>8) return 1;
    int cek;
    if(node[b].nil[k]!=0)
    {
        printf("Cek : %d\n",node[b].nil[k]);
        cek = nextnum(b,k);
        return solve(cek/9,cek%9);
    }
    printf("Cek : %d b %d k %d",node[b].nil[k],b+1,k+1);
    getnum(b,k);
    int c=0,ok=0;
    struct put *find;
    find = maybe;
    while(find!=NULL){printf("%d ",find->nil);find=find->next;c++;}
    find = maybe;
    printf("\n");
    if(c==0)return 0;
    for (int i = 0; i < c; i++)
    {
        setzerocpy();
        copy();
        printf("%d find nil\n", find->nil);
        int nil = find->nil;
        copynode[b].nil[k] = nil;
        cek = nextnum(b,k);
        if(solve(cek/9,cek%9)==1)
        {
            setzero();
            copyback();
            ok = 1;
            break;
        }
        find = find->next;
    }
    return ok;
}
int main(){
    int t;
    int x[9];
    for (int i = 0; i < 9; i++)
    {
        scanf("%d %d %d %d %d %d %d %d %d",&x[0],&x[1],&x[2],&x[3],&x[4],&x[5],&x[6],&x[7],&x[8]);
        for (int j = 0; j < 9; j++)
        {
            node[i].nil[j] = x[j];
        }
    }
    if(solve(0,0)==1){view();}
    return 0;
}