class SegmentTree {

public:
    struct node {
        LL sum = 0;
        LL lazy = 0;
        
        // apply lazy on the node.
        void apply(int l, int r, LL v) {
            sum += ((LL) (r - l + 1) * (LL) v);
            lazy += v;
        }
    };
    
    SegmentTree(int _n) : n(_n){
        tree.resize(2 * n - 1);
        build(0, 0, n - 1);
    }

    SegmentTree(const vector<node>& v) {
        n = v.size();
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, v);
    }
    
    inline node query(int ll, int rr) {
        return query(0, 0, n - 1, ll, rr);
    }

    template <typename... M>
    inline void modify(int ll, int rr, const M&... val) {
        modify(0, 0, n - 1, ll, rr, val...);
    }
    
    void print(int x, int l, int r) {
        dbg(x, l, r, tree[x].sum, tree[x].lazy);
        if (l == r) {
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        print(x + 1, l, y);
        print(z, y + 1, r);
    }
    
private:
    inline void push(int x, int l, int r) {
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1 );
        if (tree[x].lazy != 0) {
            tree[x + 1].apply(l, y, tree[x].lazy);
            tree[z].apply(y + 1, r, tree[x].lazy);
            tree[x].lazy = 0;
        }
    }
    
    inline void pull(int x, int z) {
        assert(tree[x].lazy == 0);
        tree[x] = unite(tree[x + 1], tree[z]);
    }
    
    inline node unite(const node& a, const node& b) {
        node res;
        res.sum = a.sum + b.sum;
        return res;
    }
    
    void build(int x, int l, int r) {
        if (l == r) {
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y);
        build(z, y + 1, r);
        pull(x, z);
    }
    
    void build(int x, int l, int r, const vector<node>& v) {
        if (l == r) {
            tree[x] = v[l];
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y, v);
        build(z, y + 1, r, v);
        pull(x, z);
    }
    
    node query(int x, int l, int r, int ll, int rr) {
        if (l >= ll && r <= rr) {
            return tree[x];
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r); // push lazy to child before visit.
        node res = {};
        if (rr <= y) {
            res = query(x + 1, l, y, ll, rr);
        } else {
            if (ll > y) {
                res = query(z, y + 1, r, ll, rr);
            } else {
                res = unite(query(x + 1, l, y, ll, rr), query(z, y + 1, r, ll, rr));
            }
        }
        pull(x, z); // collect data from child.
        return res;
    }
    
    template <typename... M>
    void modify(int x, int l, int r, int ll, int rr, const M&... val) {
        if (l >= ll && r <= rr) {
            tree[x].apply(l, r, val...);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        if (ll <= y) {
            modify(x + 1, l, y, ll, rr, val...);
        }
        if (rr > y) {
            modify(z, y + 1, r, ll, rr, val...);
        }
        pull(x, z);
    }
    
    vector<node> tree;
    int n;
};
