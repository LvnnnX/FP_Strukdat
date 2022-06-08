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
int nb,nk;
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
void nextnum(int b, int k) //ke kolom & baris selanjutnya yang 0
{
    int index = 9 * 9 + 1;
    for (int i = (b * 9) + (k * 9) + 1; i < 9 * 9 ; i++)
    {
        if(node[i / 9].nil[i % 9]==0)
        {
            index = i;
            break;
        }
    }
    nb = index / 9;
    nk = index % 9;
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
int solve(int b, int k) // solving
{
    if(b>8) return 1;
    if(node[b].nil[k]!=0)
    {
        nextnum(b,k);
        return solve(nb,nk);
    }
    getnum(b,k);
    int c=0,ok=0;
    struct put *find;
    find = maybe;
    while(find!=NULL){find=find->next;c++;}
    find = maybe;
    if(c==0)return 0;
    for (int i = 0; i < c; i++)
    {
        copy();
        copynode[b].nil[k] = find->nil;
        nextnum(b,k);
        if(solve(nb,nk))
        {
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
    solve(0,0);
    view();
    return 0;
}