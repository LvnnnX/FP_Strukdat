#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define pass (void)0
#define EACH(x, a) for (auto& x: a)
#define iread(x) scanf("%d",&x)
 struct data{
    int nil[9];
}; //node = total kotak
 struct put{
	int nil;
	struct put *next;
};
struct put *maybe,*baru;
/* output = 
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
void view(struct data node[])
{
    printf("+-----+-----+-----+")
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if(j%2==1) printf(" %d ",node[i].nil[j]);
            
        }
        printf("\n");
    }
    
}
int cekpos(struct data node[],int b,int k,int n) //bisa ditaruh angka atau tidak
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
void getnum(struct data node[],int b, int k) //angka apa aja yang bisa dimasukin
{
	
    maybe = NULL;
    struct put *find;
	for(int i=1;i<=9;i++)
	{
		if (cekpos(node,b,k,i)==1)
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
int nextnum(struct data node[],int b, int k) //ke kolom & baris selanjutnya yang 0
{
    for (int i = (b * 9) + k + 1; i < 9 * 9 ; i++)
    {
        if(node[i / 9].nil[i % 9]==0) return i;
    }
    return 9 * 9 + 1;
}
void copy(struct data node[], struct data *copy) //copy dari node ke copynode
{
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            copy[i].nil[j] = node[i].nil[j];
        }
    }
}
int solve(struct data tile[],int b, int k) // solving
{
    if(b>8) return 1;
    int cek;
    if(tile[b].nil[k]!=0)
    {
        
        cek = nextnum(tile,b,k);
        return solve(tile,cek/9,cek%9);
    }
    
    getnum(tile,b,k);
    int c=0,ok=0;
    struct put *find;
    find = maybe;
    while(find!=NULL){find=find->next;c++;}
    if(c==0)return 0;
    find = maybe;
    while(find!=NULL)
    {
        struct data copynode[9];
        copy(tile,copynode);
        copynode[b].nil[k] = find->nil;
        cek = nextnum(tile,b,k);
        if(solve(copynode,cek/9,cek%9)==1)
        {
            copy(copynode,tile);
            ok = 1;
            break;
        }
        find = find->next;
    }
    return ok;
}
int main(){
    int x[9];
    struct data node[9];
    for (int i = 0; i < 9; i++)
    {
        scanf("%d %d %d %d %d %d %d %d %d",&x[0],&x[1],&x[2],&x[3],&x[4],&x[5],&x[6],&x[7],&x[8]);
        for (int j = 0; j < 9; j++)
        {
            node[i].nil[j] = x[j];
        }
    }
    int t = solve(node,0,0);
    view(node);
    free(maybe);
    return 0;
}