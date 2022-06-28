/*https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/B*/
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(x) (x).begin(),(x).end()
#define scan(a) for(auto &it:a)cin>>it;
#define print(a) {for(auto it:a)cout<<it<<" ";cout<<"\n";}
#define out(x) cout<<((x)?"YES\n":"NO\n");
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
//#define prime (int)(1e9+7)
//#define prime (int)((1<<23)*7*17+1)
// #define int ll

struct segNode
{
    int val;
    int l,r;
    segNode()//default value of Segment tree main node
    {
        val=1;
        l=-1,r=-1;
    }
};
struct lazyNode
{
    int val;
    lazyNode()//default value of Segment tree lazy node
    {
        val=0;
    }
};
struct segTree
{
    int N;
    vector<segNode> seg;
    vector<lazyNode> lazy;
    segTree(int n)
    {
        N=n;
        seg.resize(4*N+5);
        lazy.resize(4*N+5);
        vector<int> a(N,seg[0].val);//check this
        build(a,0,N,0);
    }
    segTree(vector<int> &a)
    {
        N=a.size();
        seg.resize(4*N+5);
        lazy.resize(4*N+5);
        build(a,0,N,0);
    }
    void merge(segNode &cur,segNode &left,segNode &right)//change this function
    {
        assert(cur.l==left.l&&cur.r==right.r);

        cur.val = left.val + right.val;
    }
    void propogate(int id)//change this function
    {
        int l=seg[id].l,r=seg[id].r;
        seg[id].val+=lazy[id].val;
        if(l+1!=r)
        {
            int mid=(l+r)>>1LL,left=2*id+1,right=2*id+2;
            lazy[left].val+=lazy[id].val;
            lazy[right].val+=lazy[id].val;
        }
        lazy[id].val=0;
    }
    void build(vector<int> &a,int l,int r,int id)
    {
        seg[id].l=l;
        seg[id].r=r;
        if(l+1==r)//check this block
        {
            seg[id].val=a[l];
            return;
        }
        int mid=(l+r)>>1LL,left=2*id+1,right=2*id+2;
        build(a,l,mid,left);
        build(a,mid,r,right);
        merge(seg[id],seg[left],seg[right]);
    }
    void update(int ql,int qr,int val,int id=0)
    {
        propogate(id);
        int l=seg[id].l;
        int r=seg[id].r;
        if(ql>=r||l>=qr)
            return;
        if(ql<=l&&r<=qr)//check this block
        {
            lazy[id].val=val;
            propogate(id);
            return;
        }
        int mid=(l+r)>>1LL,left=2*id+1,right=2*id+2;
        update(ql,qr,val,left);
        update(ql,qr,val,right);
        merge(seg[id],seg[left],seg[right]);
    }
    segNode query(int val,int id=0)
    {
        propogate(id);
        segNode ans;
        int l=seg[id].l;
        int r=seg[id].r;
        if(l+1==r){
            assert(val==0);
            return seg[id];
        }
        int mid=(l+r)>>1LL,left=2*id+1,right=2*id+2;
        if(seg[right].val<=val)
            return query(val-seg[right].val,left);
        else 
            return query(val,right);
    }
};

void init()
{}
    
void solve()
{
    int n;
    cin>>n;
    int a[n];
    scan(a);
    reverse(a,a+n);
    segTree s(n+1);
    s.update(0,1,-1);
    for(int i=0;i<n;i++)
    {
        int t=s.query(a[i]).l;
        a[i]=t;
        s.update(t,t+1,-1);
    }
    reverse(a,a+n);
    print(a);
}
int32_t main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t=1;
    init();
    //cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}
