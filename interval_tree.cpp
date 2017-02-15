#include<iostream>
#include<algorithm>
#include<math.h>
#include<cstring>
#include<iomanip>
#include<stdio.h>
#include<limits>
#include<unordered_map>
#include<set>
#include<list>
#include<vector>
#include<stack>
#define gcd __gcd
#define pb(x) push_back(x)
#define ll long long
#define in(x) scanf("%d",&x)
#define mod 1000000007
#define sz(x) x.size()
#define mst(x,a) memset(x,a,sizeof(x))
#define pii pair<int,int>
#define F first
#define S second
#define m_p make_pair
#define all(v) (v.begin(),v.end())
using namespace std;
pair<pair<int,int>,int> intree[1000006];//the interval tree
//each node is of the form node.F.F=>low,node.F.S=:high;
//node.S=>max value of high in the subtree routed at node;
bool visited[1000006];
//whether the ith index node is present in the interval tree or not
bool done;
void insert_interval(pair<int,int> p,int i)
{
    if(!visited[i])
    {
        intree[i]=make_pair(p,p.S);
        visited[i]=1;
        return;
    }
    intree[i].S=max(intree[i].S,p.S);
    if(p.F<intree[i].F.F)
        insert_interval(p,2*i+1);
    else
        insert_interval(p,2*i+2);
}
void find_interval(pair<int,int> p,int i)
{
    int l=max(intree[i].F.F,p.F),r=min(intree[i].F.S,p.S);
    if(l<=r)
    {
        cout<<"given interval overlaps with range ("<<intree[i].F.F<<" "<<intree[i].F.S<<") :)\n";
        done=1;
        return;
    }
    if(visited[2*i+1])
    {
        if(intree[2*i+1].S>=p.F)
            find_interval(p,2*i+1);
    }
    else
        find_interval(p,2*i+2);
}
int main()
{
    ios::sync_with_stdio(0);
    cout<<"enter the number of nodes in the interval tree\n";
    int n;
    cin>>n;
    pair<int,int>node;
    cout<<"enter the "<<n<<" nodes\n";
    for(int i=0;i<n;i++)
    {
        cin>>node.F>>node.S;
        insert_interval(node,0);
    }
    cout<<"enter the number of searches you want\n";
    int q;
    cin>>q;
    while(q--)
    {
        cout<<"enter the node with spaces\n";
        cin>>node.F>>node.S;
        done=0;
        find_interval(node,0);
        if(!done)
            cout<<"sorry the interval not found :(\n";
    }
    return 0;
}


