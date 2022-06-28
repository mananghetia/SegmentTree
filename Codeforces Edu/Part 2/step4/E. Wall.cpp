/*https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/E*/
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
//#define int ll

struct segNode
{
    int mx,mn;
    int l,r;
    segNode()//default value of Segment tree main node
    {
        mx=0;
        mn=INT_MAX;
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
        vector<int> a(N,0);//check this
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
    }
    void propogate(int id)//change this function
    {
        int l=seg[id].l,r=seg[id].r;
        if(l+1!=r)
        {
            int left=2*id+1,right=2*id+2;
            seg[left].mn=min(seg[left].mn,seg[id].mn);
            seg[left].mn=max(seg[left].mn,seg[id].mx);
            seg[left].mx=max(seg[left].mx,seg[id].mx);
            seg[left].mx=min(seg[left].mx,seg[id].mn);
            seg[right].mn=min(seg[right].mn,seg[id].mn);
            seg[right].mn=max(seg[right].mn,seg[id].mx);
            seg[right].mx=max(seg[right].mx,seg[id].mx);
            seg[right].mx=min(seg[right].mx,seg[id].mn);
            seg[id].mx=0;
            seg[id].mn=INT_MAX;
        }
    }
    void build(vector<int> &a,int l,int r,int id)
    {
        seg[id].l=l;
        seg[id].r=r;
        seg[id].mn=a[l];
        seg[id].mx=a[l];
        if(l+1==r)//check this block
        {
            return;
        }
        int mid=(l+r)>>1LL,left=2*id+1,right=2*id+2;
        build(a,l,mid,left);
        build(a,mid,r,right);
    }
    void update(int ql,int qr,int val,int type,int id=0)
    {
        propogate(id);
        int l=seg[id].l;
        int r=seg[id].r;
        if(ql>=r||l>=qr)
            return;
        if(ql<=l&&r<=qr)//check this block
        {
            if(type==1)
            {
                seg[id].mn=max(seg[id].mn,val);
                seg[id].mx=max(seg[id].mx,val);
            }
            else 
            {
                seg[id].mn=min(seg[id].mn,val);
                seg[id].mx=min(seg[id].mx,val);        
            }
            return;
        }
        int mid=(l+r)>>1LL,left=2*id+1,right=2*id+2;
        update(ql,qr,val,type,left);
        update(ql,qr,val,type,right);
    }
    segNode query(int ql,int id=0)
    {
        propogate(id);
        int l=seg[id].l;
        int r=seg[id].r;
        if(ql==l&&l+1==r)
            return seg[id];
        int mid=(l+r)>>1LL,left=2*id+1,right=2*id+2;
        if(ql<mid)
            return query(ql,left);
        else 
            return query(ql,right);
    }
};

void init()
{}
    
void solve()
{
    int n,q;
    cin>>n>>q;
    segTree s(n);
    while(q--)
    {
        int l,r,h,t;
        cin>>t>>l>>r>>h;
        r++;
        s.update(l,r,h,t);
    }
    for(int i=0;i<n;i++)
    {
        auto ans=s.query(i);
        cout<<min(ans.mn,ans.mx)<<"\n";
    }
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
