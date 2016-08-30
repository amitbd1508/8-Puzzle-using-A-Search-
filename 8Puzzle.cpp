#include <bits/stdc++.h>
#include <functional>
using namespace std;

map<vector<vector<int> > , bool> visited;
map<vector<vector<int> > , vector<vector<int> > > parent;
vector<vector<int> > goal(3,vector<int> (3));
vector<vector<vector<int> > >::iterator it;



int manhattenDistance(vector<vector<int> > a , int moves)
{
	int distance=moves;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(a[i][j]!=0)
			{
				for(int k=0;k<3;k++)
				{
					for(int l=0;l<3;l++)
					{
						if(a[i][j]==goal[k][l])
							distance+=abs(i-k)+abs(j-l);
					}
				}
			}
		}
	}

	return distance;
}

bool isGoal(vector<vector<int> > a)
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(a[i][j]!=goal[i][j])
				return false;
		}
	}

return true;
}

bool safe(int i,int j)
{
	if(i>=0 && i<=2 && j>=0 && j<=2)
	return true;
	else
	return false;
}


int dx[]={-1,+1,0,0};
int dy[]={0,0,-1,+1};


vector<vector<vector<int> > > neighbours(vector<vector<int> > a)
{
	pair<int,int> pos;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(a[i][j]==0)
			{
				pos.first=i;
				pos.second=j;
				break;
			}
		}
	}
	vector<vector<vector<int> > > ans;
	for(int k=0;k<4;k++)
	{
		int cx = pos.first;
		int cy = pos.second;
		vector<vector<int> > newnode = a;
		if(safe(cx+dx[k],cy+dy[k]))
		{
			swap(newnode[cx+dx[k]][cy+dy[k]],newnode[cx][cy]);
			ans.push_back(newnode);
		}
	}

return ans;
}

typedef pair<vector<vector<int> > , int> myPair;

struct cmp
{
	bool operator() (myPair &a, myPair &b)
	{
		int am = manhattenDistance(a.first,a.second);
		int bm = manhattenDistance(b.first,b.second);
		return am<bm;
	}
};

void print_path(vector<vector<int> > s)
{
   if(parent.count(s))
     print_path(parent[s]);

   for(int i=0;i<3;i++)
   {
	 for(int j=0;j<3;j++)
	 {
		printf("%d ",s[i][j]);
	 }
	cout<<endl;
   }

   cout<<endl;
 return;
}

void print(vector<vector<int> > s)
{
	for(int i=0;i<3;i++)
   {
	 for(int j=0;j<3;j++)
	 {
		printf("%d ",s[i][j]);
	 }
	cout<<endl;
   }
}

bool visit(vector<vector<int> > a)
{
	if(visited[a]==true)
		return true;
	else
		return false;
}
void A_Star_Search(vector<vector<int> > a, int moves)
 {

	priority_queue<myPair,vector<myPair>,cmp > Q;

	Q.push(myPair(a,moves));

	while(!Q.empty())
	{
		vector<vector<int> > s = Q.top().first;
		Q.pop();

		visited[s]=true;
		cout<<endl;
		print(s);
		cout<<endl;
		if(s==goal)
		{
            printf("Found the goal \n");
			print_path(s);
			break;
		}
		vector<vector<vector<int> > > ns = neighbours(s);



		for(it=ns.begin();it!=ns.end();it++)
		{

			vector<vector<int> > temp = *it;
			if(!visit(temp))
			{
				parent.insert(pair<vector<vector<int> > , vector<vector<int> > >(temp,s));
				Q.push(myPair(temp,moves+1));
			}
			//cout<<moves<<endl;
		}
	}
	return;
 }
void initGoal()
{

    goal[0][0] = 1;
	goal[0][1] = 2;
	goal[0][2] = 3;
	goal[1][0] = 4;
	goal[1][1] = 5;
	goal[1][2] = 6;
	goal[2][0] = 7;
	goal[2][1] = 8;
	goal[2][2] = 0;
}
int main()
{
	vector<vector<int> > a(3,vector<int> (3));


	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cin>>a[i][j];
		}
	}
	cout<<"Solution...\n\n";

	initGoal();
	A_Star_Search(a,0);
}
