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
    struct put *find;
	for(int i=1;i<=9;i++)
	{
		if (cekpos(b,k,i)==1)
		{
            baru = (struct put*)malloc(sizeof(struct put));
            baru->nil = i;
            baru->next = NULL;
			if(maybe==NULL)
			{
                maybe = baru;
                find = maybe;
			}else
			{
				find->next = baru;
                find = baru;
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
void copy() //copy dari node ke copynode
{
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            copynode[i].nil[j] = node[i].nil[j];
        }
    }
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
int solve(struct data tile[9],int b, int k) // solving
{
    if(b>8) return 1;
    int cek;
    if(tile[b].nil[k]!=0)
    {
        
        cek = nextnum(b,k);
        return solve(tile,cek/9,cek%9);
    }
    
    getnum(b,k);
    int c=0,ok=0;
    struct put *find;
    find = maybe;
    while(find!=NULL){find=find->next;c++;}
    if(c==0)return 0;
    while(maybe!=NULL)
    {
        copy();
        copynode[b].nil[k] = maybe->nil;
        cek = nextnum(b,k);
        if(solve(copynode,cek/9,cek%9)==1)
        {
            copyback();
            ok = 1;
            break;
        }
        maybe = maybe->next;
    }
    return ok;
}
int countzero()
{
    int c=0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if(node[i].nil[j]==0)c++;
        }
    }
    return c;
}
int main(){
    int x[9];
    for (int i = 0; i < 9; i++)
    {
        scanf("%d %d %d %d %d %d %d %d %d",&x[0],&x[1],&x[2],&x[3],&x[4],&x[5],&x[6],&x[7],&x[8]);
        for (int j = 0; j < 9; j++)
        {
            node[i].nil[j] = x[j];
        }
    }
    int t= countzero();
    while(t!=0)
    {
        int cek = solve(node,0,0);
        t = countzero();
    }
    view();
    return 0;
}