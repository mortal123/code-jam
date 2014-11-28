#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 510000, inf = 21000000;

class SplayTree
{
	private:
		struct node
		{
			node *Child[2], *Father;
			int val, tagv, rev, sum, MaxL, MaxR, MaxMid, Size;
			int isRc()
			{
				return this == Father->Child[1];
			}
			void SetChild(node *tmp, int dir)
			{
				tmp->Father = this;
				Child[dir] = tmp;
			}
			void Rev()
			{
				if (Child[1] == NULL) 
					return;
				rev ^= 1;
				swap(Child[0], Child[1]);
				swap(MaxL, MaxR);
			}
			void Eval(int eval)
			{
				if (Child[1] == NULL)
					return;
				tagv = val = eval;
				sum = eval * Size;
				MaxL = MaxR = MaxMid = max(0, sum);
			}
			void Update()
			{
				sum = Child[0]->sum + Child[1]->sum + val;
				Size = Child[0]->Size + Child[1]->Size + 1;
				MaxL = max(Child[0]->MaxL, Child[0]->sum + val + Child[1]->MaxL);
				MaxR = max(Child[1]->MaxR, Child[1]->sum + val + Child[0]->MaxR);
				MaxMid = max(Child[0]->MaxMid, Child[1]->MaxMid);
				MaxMid = max(MaxMid, Child[0]->MaxR + val + Child[1]->MaxL);
			}
			void PushDown()
			{
				if (tagv != -inf)
				{
					Child[0]->Eval(tagv);
					Child[1]->Eval(tagv);
					tagv = -inf;
				}
				if (rev)
				{
					Child[0]->Rev();
					Child[1]->Rev();
					rev = 0;
				}
			}
		};
		typedef node *Node;
		Node Head, Null;
		Node NewNode(int val = 0)
		{
			Node Root = new node;
			Root->val = Root->sum = val;
			Root->MaxL = Root->MaxR = Root->MaxMid = max(0, val);
			Root->Child[0] = Root->Child[1] = Root->Father = Null;
			Root->tagv = -inf, Root->rev = 0;
			Root->Size = 1;
			return Root;
		}
		void Rotate(Node Root)
		{
			Node Father = Root->Father;
			int Dir = Root->isRc();
			Father->PushDown();
			Root->PushDown();
			Father->SetChild(Root->Child[!Dir], Dir);
			Father->Father->SetChild(Root, Father->isRc());
			Root->SetChild(Father, !Dir);
			if (Father == Head)
				Head = Root;
			Father->Update();
		}
		void Splay(Node Root, Node Target)
		{
			for(Root->PushDown(); Root->Father != Target; )
			{
				if (Root->Father->Father == Target)
					Rotate(Root);
				else
					(Root->Father->isRc() == Root->isRc()) ?
						(Rotate(Root->Father), Rotate(Root)) : (Rotate(Root), Rotate(Root));
			}
			Root->Update();
		}
		Node Find(int Rank)
		{
			Node Root = Head;
			while(Root->Child[0]->Size + 1 != Rank)
			{
				Root->PushDown();
				if (Root->Child[0]->Size + 1 < Rank)
				{
					Rank -= Root->Child[0]->Size + 1;
					Root = Root->Child[1];
				} else
					Root = Root->Child[0];
			}
			Root->Update();
			return Root;
		}
 		void Splay(int L, int R)
		{
			Splay(Find(R), Null);
			Splay(Find(L), Head);
		}
	public:
		SplayTree()
		{
			Null = NewNode(); Null->Child[0] = Null->Child[1] = NULL;
			Null->Size = 0;
			Head = NewNode(-inf);
			Node Tail = NewNode(-inf);
			Head->SetChild(Tail, 1);
			Splay(Tail, Null);
		}
		void Insert(int pos, int n, int num[])
		{
			Splay(pos + 1, pos + 2);
			Node Root = Head->Child[0], Ext;
			for(int i = 1; i <= n; i++)
			{
				Ext = NewNode(num[i]);
				Root->SetChild(Ext, 1);
				Root = Ext;
			}
			Splay(Root, Null);
		}
		void Delete(Node &Root)
		{
			if (Root == Null)
				return ;
			if (Root->Child[0] != Null)
				Delete(Root->Child[0]);
			if (Root->Child[1] != Null)
				Delete(Root->Child[1]);
			delete(Root);
			Root = Null;
		}
		void Delete(int pos, int n)
		{
			Splay(pos, pos + n + 1);
			Delete(Head->Child[0]->Child[1]);
			Splay(Head->Child[0], Null);
		}
		void MakeSame(int pos, int n, int c)
		{
			Splay(pos, pos + n + 1);
			Head->Child[0]->Child[1]->Eval(c);
			Splay(Head->Child[0]->Child[1], Null);
		}
		void Reverse(int pos, int n)
		{
			Splay(pos, pos + n + 1);
			Head->Child[0]->Child[1]->Rev();
			Splay(Head->Child[0]->Child[1], Null);
		}
		int GetSum(int pos, int n)
		{
			Splay(pos, pos + n + 1);
			//printf("%d %d\n", Head->val, Head->Child[0]->val);
			return Head->Child[0]->Child[1]->sum;
		}
		int MaxSum()
		{
			return Head->MaxMid;
		}
		int Size()
		{
			return Head->Size;
		}
};

int n, m, num[MAXN];
SplayTree T;
char str[MAXN];

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	scanf("%d %d", &n, &m);
	
	for(int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
	scanf("\n");
	T.Insert(0, n, num);
	for(int i = 1; i <= m; i++)
	{
		if (i == 17)
		{
			int a = 0;
		}
		scanf("%s", str + 1);
		if (str[1] == 'I') // INSERT
		{
			int pos;
			scanf("%d %d", &pos, &n);
			for(int i = 1; i <= n; i++)
				scanf("%d", &num[i]);
			T.Insert(pos, n, num);
		} else
		if (str[1] == 'D') // DELETE
		{
			int pos, tot;
			scanf("%d %d", &pos, &tot);
			T.Delete(pos, tot);
		} else
		if (str[1] == 'M' && str[3] == 'K') // MAKE-SAME
		{
			int pos, tot, c;
			scanf("%d %d %d", &pos, &tot, &c);
			T.MakeSame(pos, tot, c);
		} else
		if (str[1] == 'R') // REVERSE
		{
			int pos, tot;
			scanf("%d %d", &pos, &tot);
			T.Reverse(pos, tot);
		} else
		if (str[1] == 'G') // GETSUM
		{
			int pos, tot;
			scanf("%d %d", &pos, &tot);
			printf("%d\n", T.GetSum(pos, tot));
		} else
		{
			printf("%d\n", T.MaxSum());
		}
		//printf("size : %d\n", T.Size());
		scanf("\n");
	}
	return 0;
}
