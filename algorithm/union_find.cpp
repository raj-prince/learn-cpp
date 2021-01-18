class UnionFind {
public:
    UnionFind(int n = 0) {
        r.resize(n, 0);
        p.resize(n, 0);
        iota(p.begin(), p.end(), 0);
        sz.resize(n, 1);
    }
    
    int FindSet(int x) {
        if (p[x] != x) {
            p[x] = FindSet(p[x]); // path compression heuristic.
        }
        return p[x];
    }
    
    /* true: means both x and y were in different set and now merged. */
    bool UnionSet(int x, int y) {
    
        if (IsInSameSet(x, y))
            return false;
            
        int px = FindSet(x);
        int py = FindSet(y);
        
        /* Rank heuristic: Append in the tree of higher rank. */
        /* Think px as the owner of tree with higher rank. */
        if (r[px] < r[py]) {
            swap(px, py);
        }
        
        p[py] = px;
        sz[px] += sz[py];
        
        if (r[px] == r[py]) {
            r[px]++;
        }
        
        return true;
    }
    
    int GetNumberOfDisjointSet() {
        int n = static_cast<int>(p.size());
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            
            if (p[i] == i)
                cnt++;
        }
        
        return cnt;
    }
    
    /* Get size of set in which x belongs to.*/
    int GetSizeOfSet(int x) {
        int px = FindSet(x);
        return sz[px];
    }
    
private:
    bool IsInSameSet(int x, int y) {
        return FindSet(x) == FindSet(y);
    }
    
    vector<int> p, r, sz; // parent, rank and size.
};
