/*https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/F*/
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

struct SegNode
{
    int l,r,sum,maxpre,lazy;
    struct SegNode *left=NULL,*right=NULL;
    SegNode(int ml,int mr,int mlazy)
    {
        l=ml;r=mr;
        lazy=mlazy;
        sum=(r-l)*lazy,maxpre=max(0,sum);
    }
    void extend()
    {
        if(left==NULL&&l+1!=r)
        {
            int mid=(l+r)/2LL;
            assert(lazy!=INT_MIN);
            left = new SegNode(l,mid,lazy);
            right = new SegNode(mid,r,lazy);
        }
    }
    void propogate()
    {
        if(lazy==INT_MIN)
            return;
        extend();
        sum=(r-l)*lazy;
        maxpre=max(0,sum);
        if(l+1!=r)
        {
            left->lazy=lazy;
            right->lazy=lazy;
        }
        lazy=INT_MIN;
    }
    void merge()
    {
        sum = left->sum + right->sum;
        maxpre = max(left->maxpre , left->sum + right->maxpre);
    }
    void update(int ql,int qr,int d)
    {
        propogate();
        if(ql>=r||l>=qr)
            return;
        if(ql<=l&&r<=qr)
        {
            lazy=d;
            propogate();
            return;
        }
        left->update(ql,qr,d);
        right->update(ql,qr,d);
        merge();
    }
    int query(int h)
    {
        propogate();
        if(l+1==r)
            return l;
        left->propogate();
        right->propogate();
        if(left->maxpre>h)
            return left->query(h);
        else 
            return right->query(h-left->sum);
    }
};

void init()
{}
    
void solve()
{
    int n;
    cin>>n;
    SegNode *root= new SegNode(0,n+2,0);
    while(1)
    {
        char c;
        cin>>c;
        if(c=='E')
            break;
        if(c=='Q')
        {
            int h;
            cin>>h;
            cout<<root->query(h)-1<<endl;
        }
        else
        {
            int l,r,d;
            cin>>l>>r>>d;
            r++;
            root->update(l,r,d);
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
