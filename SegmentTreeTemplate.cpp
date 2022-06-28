/*Multi purpose Segment Tree Template*/
/*range are half-open i.e [l,r)*/
/*By default it will perform range increment update and calculate range sum*/
struct segNode
{
    int val;
    int l, r;
    segNode() // default value of Segment tree main node
    {
        val = 0;
        l = -1, r = -1;
    }
};
struct lazyNode
{
    int val;
    lazyNode() // default value of Segment tree lazy node
    {
        val = 0;
    }
};
struct segTree
{
    int N;
    vector<segNode> seg;
    vector<lazyNode> lazy;
    segTree(int n) // Default Segment Tree
    {
        N = n;
        seg.resize(4 * N + 5);
        lazy.resize(4 * N + 5);
        vector<int> a(N, seg[0].val); // check this
        build(a, 0, N, 0);
    }
    segTree(vector<int> &a) // Pre-Computed Segment Tree
    {
        N = a.size();
        seg.resize(4 * N + 5);
        lazy.resize(4 * N + 5);
        build(a, 0, N, 0);
    }
    void merge(segNode &cur, segNode &left, segNode &right) // change this function
    {
        assert(cur.l == left.l && cur.r == right.r);

        cur.val = left.val + right.val;
    }
    void propogate(int id) // change this function
    {
        int l = seg[id].l, r = seg[id].r;
        seg[id].val += lazy[id].val;
        if (l + 1 != r)
        {
            int mid = (l + r) >> 1LL, left = 2 * id + 1, right = 2 * id + 2;
            lazy[left].val += lazy[id].val;
            lazy[right].val += lazy[id].val;
        }
        lazy[id].val = 0;
    }
    void build(vector<int> &a, int l, int r, int id)
    {
        seg[id].l = l;
        seg[id].r = r;
        if (l + 1 == r) // check this block
        {
            seg[id].val = a[l];
            return;
        }
        int mid = (l + r) >> 1LL, left = 2 * id + 1, right = 2 * id + 2;
        build(a, l, mid, left);
        build(a, mid, r, right);
        merge(seg[id], seg[left], seg[right]);
    }
    void update(int ql, int qr, int val, int id = 0)
    {
        propogate(id);
        int l = seg[id].l;
        int r = seg[id].r;
        if (ql >= r || l >= qr)
            return;
        if (ql <= l && r <= qr) // check this block
        {
            lazy[id].val = val;
            propogate(id);
            return;
        }
        int mid = (l + r) >> 1LL, left = 2 * id + 1, right = 2 * id + 2;
        update(ql, qr, val, left);
        update(ql, qr, val, right);
        merge(seg[id], seg[left], seg[right]);
    }
    segNode query(int ql, int qr, int id = 0)
    {
        propogate(id);
        segNode ans;
        int l = seg[id].l;
        int r = seg[id].r;
        if (ql >= r)
        {
            ans.l = ans.r = ql;
            return ans;
        }
        if (l >= qr)
        {
            ans.l = ans.r = qr;
            return ans;
        }
        if (ql <= l && r <= qr)
            return seg[id];
        int mid = (l + r) >> 1LL, left = 2 * id + 1, right = 2 * id + 2;
        segNode ansl = query(ql, qr, left);
        segNode ansr = query(ql, qr, right);
        ans.l = ansl.l;
        ans.r = ansr.r;
        merge(ans, ansl, ansr);
        return ans;
    }
};