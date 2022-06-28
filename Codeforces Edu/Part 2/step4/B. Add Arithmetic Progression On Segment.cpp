/*https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/B*/
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
    ll val;
    int l,r;
    segNode()//default value of Segment tree main node
    {
        val=0;
        l=-1,r=-1;
    }
};
struct lazyNode
{
    ll a,d,d_st;
    lazyNode()//default value of Segment tree lazy node
    {
        a=0;
        d=0;
        d_st=0;
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
        vector<ll> a(N,0LL);//check this
        build(a,0,N,0);
    }
    segTree(vector<ll> &a)
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
        ll f=lazy[id].a - lazy[id].d_st + l*lazy[id].d;
        ll s=lazy[id].a - lazy[id].d_st + (r-1)*lazy[id].d;
        seg[id].val += (r-l)*(f+s)/2;
        if(l+1!=r)
        {
            int mid=(l+r)>>1LL,left=2*id+1,right=2*id+2;
            lazy[left].a = lazy[left].a + lazy[id].a;
            lazy[left].d_st = lazy[left].d_st + lazy[id].d_st;
            lazy[left].d = lazy[left].d + lazy[id].d;
            lazy[right].a = lazy[right].a + lazy[id].a;
            lazy[right].d_st = lazy[right].d_st + lazy[id].d_st;
            lazy[right].d = lazy[right].d + lazy[id].d;
        }
        lazy[id].a=0;
        lazy[id].d=0;
        lazy[id].d_st=0;
    }
    void build(vector<ll> &a,int l,int r,int id)
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
    void update(int ql,int qr,int a,int d,int id=0)
    {
        propogate(id);
        int l=seg[id].l;
        int r=seg[id].r;
        if(ql>=r||l>=qr)
            return;
        if(ql<=l&&r<=qr)//check this block
        {
            lazy[id].d_st=1LL*ql*d;
            lazy[id].d=d;
            lazy[id].a=a;
            propogate(id);
            return;
        }
        int mid=(l+r)>>1LL,left=2*id+1,right=2*id+2;
        update(ql,qr,a,d,left);
        update(ql,qr,a,d,right);
        merge(seg[id],seg[left],seg[right]);
    }
    segNode query(int ql,int qr,int id=0)
    {
        propogate(id);
        segNode ans;
        int l=seg[id].l;
        int r=seg[id].r;
        if(ql>=r){
            ans.l=ans.r=ql;
            return ans;
        }
        if(l>=qr){
            ans.l=ans.r=qr;
            return ans;
        }
        if(ql<=l&&r<=qr)
            return seg[id];
        int mid=(l+r)>>1LL,left=2*id+1,right=2*id+2;
        segNode ansl=query(ql,qr,left);
        segNode ansr=query(ql,qr,right);
        ans.l=ansl.l;
        ans.r=ansr.r;
        merge(ans,ansl,ansr);
        return ans;
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
        int t,l;
        cin>>t>>l;
        l--;
        if(t==2)
            cout<<s.query(l,l+1).val<<endl;
        else{
            int r,a,d;
            cin>>r>>a>>d;
            s.update(l,r,a,d);
        }
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
