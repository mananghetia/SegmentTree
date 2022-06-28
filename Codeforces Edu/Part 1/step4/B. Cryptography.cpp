/*https://codeforces.com/edu/course/2/lesson/4/4/practice/contest/274684/problem/B*/
/*Array is faster than vector*/
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

int n,m,mod;
struct segNode
{
    int val[2][2];
    int l,r;
    segNode()//default value of Segment tree main node
    {
        val[0][0]=val[1][1]=1;
        val[0][1]=val[1][0]=0;
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
        // vector<vector<vector<int>>> a(N,seg[0].val);//check this
        // build(a,0,N,0);
    }
    segTree(vector<vector<vector<int>>> &a)
    {
        N=a.size();
        seg.resize(4*N+5);
        lazy.resize(4*N+5);
        build(a,0,N,0);
    }
    void merge(segNode &cur,segNode &left,segNode &right)//change this function
    {
        assert(cur.l==left.l&&cur.r==right.r);
        for(int i=0;i<2;i++)
        {
            for(int j=0;j<2;j++)
            {
                cur.val[i][j]=0;
                for(int k=0;k<2;k++)
                {
                    cur.val[i][j]=(cur.val[i][j]+(left.val[i][k]*right.val[k][j])%mod)%mod;
                }
            }
        }
    }
    void propogate(int id)//change this function
    {
        return;
        // int l=seg[id].l,r=seg[id].r;
        // seg[id].val+=lazy[id].val;
        // if(l+1!=r)
        // {
        //     int mid=(l+r)>>1LL,left=2*id+1,right=2*id+2;
        //     lazy[left].val+=lazy[id].val;
        //     lazy[right].val+=lazy[id].val;
        // }
        // lazy[id].val=0;
    }
    void build(vector<vector<vector<int>>> &a,int l,int r,int id)
    {
        seg[id].l=l;
        seg[id].r=r;
        if(l+1==r)//check this block
        {
            for(int i=0;i<2;i++)for(int j=0;j<2;j++)
            seg[id].val[i][j]=a[l][i][j];
            return;
        }
        int mid=(l+r)>>1LL,left=2*id+1,right=2*id+2;
        build(a,l,mid,left);
        build(a,mid,r,right);
        merge(seg[id],seg[left],seg[right]);
    }
    // void update(int ql,int qr,int val,int id=0)
    // {
    //     propogate(id);
    //     int l=seg[id].l;
    //     int r=seg[id].r;
    //     if(ql>=r||l>=qr)
    //         return;
    //     if(ql<=l&&r<=qr)//check this block
    //     {
    //         lazy[id].val=val;
    //         propogate(id);
    //         return;
    //     }
    //     int mid=(l+r)>>1LL,left=2*id+1,right=2*id+2;
    //     update(ql,qr,val,left);
    //     update(ql,qr,val,right);
    //     merge(seg[id],seg[left],seg[right]);
    // }
    void query(int a[2][2],int ql,int qr,int id=0)
    {
        int l=seg[id].l;
        int r=seg[id].r;
        if(ql>=r){
            for(int i=0;i<2;i++)for(int j=0;j<2;j++)a[i][j]=0;
            a[0][0]=a[1][1]=1%mod;
            return;
        }
        if(l>=qr){
            for(int i=0;i<2;i++)for(int j=0;j<2;j++)a[i][j]=0;
            a[0][0]=a[1][1]=1%mod;
            return;
        }
        if(ql<=l&&r<=qr){
            for(int i=0;i<2;i++)for(int j=0;j<2;j++)a[i][j]=seg[id].val[i][j];
            return ;
        }
        int mid=(l+r)>>1LL,left=2*id+1,right=2*id+2;
        int ansl[2][2],ansr[2][2];
        query(ansl,ql,qr,left);
        query(ansr,ql,qr,right);
        // merge(ans,ansl,ansr);
        for(int i=0;i<2;i++)for(int j=0;j<2;j++){
            a[i][j]=0;
            for(int k=0;k<2;k++)
            {
                a[i][j]=(a[i][j]+(ansl[i][k]*ansr[k][j])%mod)%mod;
            }
        }
    }
};

void init()
{}
    
void solve()
{
    cin>>mod>>n>>m;
    vector<vector<vector<int>>> a(n,vector<vector<int>>(2,vector<int>(2)));
    for(int k=0;k<n;k++)
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)cin>>a[k][i][j];
    segTree s(a);
    while(m--)
    {
        int l,r;
        cin>>l>>r;
        l--;
        int ans[2][2];
        ans[0][0]=ans[1][1]=1%mod;
        s.query(ans,l,r);
        for(int i=0;i<2;i++)for(int j=0;j<2;j++)cout<<ans[i][j]<<" \n"[j==1];cout<<endl;
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
