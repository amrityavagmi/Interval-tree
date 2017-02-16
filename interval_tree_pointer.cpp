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
#define red 0
#define black 1
using namespace std;
bool hollow=0;
struct node
{
    pair<int,int> p;//contains the range
    int maxi;//maximum high of all subtree routed at node
    bool clr;//color of the node
    node *left,*right,*papa;//the left child, right child and the parent nodes
};
node *insert_node(node *root,node *curr)//inserting the node
{
    if(root==NULL)
        return curr;

    root->maxi=max(root->maxi,curr->maxi);
    if(curr->p.F<root->p.F)
    {
        root->left=insert_node(root->left,curr);
        root->left->papa=root;
    }
    else
    {
        root->right=insert_node(root->right,curr);
        root->right->papa=root;
    }
    return root;

}
void rleft(node *&curr,node *&root)//left rotation
{
    node *right=curr->right;
    curr->right=right->left;

    if(curr->right!=NULL)
        curr->right->papa=curr;
    right->papa=curr->papa;
    if(curr->papa==NULL)
        root=right;
    else if(curr==curr->papa->left)
        curr->papa->left=right;
    else
        curr->papa->right=right;
    right->left=curr;
    curr->papa=right;
}
void rright(node *&curr,node *&root)//right rotation
{
    node *left=curr->left;
    curr->left=left->right;
    if(curr->left!=NULL)
        curr->left->papa=curr;
    left->papa=curr->papa;
    if(curr->papa==NULL)
        root=left;
    else if(curr==curr->papa->left)
        curr->papa->left=left;
    else
        curr->papa->right=left;
    left->right=curr;
    curr->papa=left;
}
void refresh(node *&root,node *&curr)//removing the discrepancy
{
    node *papa=NULL;
    node *dada=NULL;
    while(curr!=root&&curr->clr==red&&curr->papa->clr==red)
    {
        papa=curr->papa;
        dada=curr->papa->papa;
        if(dada->left==papa)
        {
            node *kaka=dada->right;
            if(kaka!=NULL&&kaka->clr==red)
            {
                dada->clr=red;
                papa->clr=black;
                kaka->clr=black;
                curr=dada;
            }
            else
            {
                if(curr==papa->right)
                {
                    rleft(curr,root);
                    curr=papa;
                    papa=curr->papa;
                }
                rright(dada,root);
                swap(papa->clr,dada->clr);
                curr=papa;
            }
        }
        else
        {
            node *kaka=dada->left;
            if(kaka!=NULL&&kaka->clr!=black)
            {
                dada->clr=red;
                papa->clr=black;
                kaka->clr=black;
                curr=dada;
            }
            else
            {
                if(curr==papa->left)
                {
                    rright(papa,root);
                    curr=papa;
                    papa=curr->papa;
                }
                rleft(dada,root);
                swap(dada->clr,papa->clr);
                curr=papa;
            }
        }
    }
    root->clr=black;

}
void search_interval_tree(node *root,pair<int,int> p)//searching a range
{
    if(root==NULL)
        return;
    int l=max(root->p.F,p.F),r=min(root->p.S,p.S);
    if(l<=r)
    {
        cout<<"the overlapping range is ("<<root->p.F<<" "<<root->p.S<<")"<<endl;
        hollow=1;
        return;
    }
    if(root->left!=NULL&&root->left->maxi>=p.F)
        search_interval_tree(root->left,p);
    else
        search_interval_tree(root->right,p);
}
void print(node *root)//printing the in-order traversal
{
    if(root==NULL)
        return;
    print(root->left);
    cout<<root->p.F<<" "<<root->p.S<<" "<<root->maxi<<" "<<root->clr<<endl;
    print(root->right);
}
int main()
{
    ios::sync_with_stdio(0);
    int n;
    cout<<"enter the number of nodes in the interval tree\n";
    cin>>n;
    cout<<"enter the ranges\n";
    pair<int,int>a;
    node *root=NULL;
    for(int i=0;i<n;i++)
    {
        cin>>a.F>>a.S;
        node *curr=new node;
        curr->clr=red;
        curr->p=a;
        curr->maxi=a.S;
        curr->left=curr->right=curr->papa=NULL;
        root=insert_node(root,curr);
        refresh(root,curr);
    }
    cout<<"the in-order traversal of the tree is\n";
    print(root);
    int q;
    cout<<"enter the number of searches\n";
    cin>>q;
    cout<<"enter your searches\n";
    pair<int,int>p;
    while(q--)
    {
        cin>>p.F>>p.S;
        hollow=0;
        search_interval_tree(root,p);
        if(!hollow)
            cout<<"interval not found"<<endl;
    }
    return 0;
}


