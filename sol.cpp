struct HLD {
	int N; vector<int> adj[MAX_N];
	int par[MAX_N], root[MAX_N], depth[MAX_N], sz[MAX_N], ti;
	int pos[MAX_N]; vector<int> rpos; 
	map<int,int> all_of_col[MAX_N];
    unordered_map<int,int> first_cols[MAX_N];

	void dfsSz(int x) {
		sz[x] = 1;
		for(auto y : adj[x]) {
			par[y] = x; depth[y] = depth[x]+1;
			adj[y].erase(find(all(adj[y]),x)); 
			dfsSz(y); sz[x] += sz[y];
			if (sz[y] > sz[adj[x][0]]) swap(y,adj[x][0]);
		}
	}
	void dfsHld(int x) {
		pos[x] = ti++; rpos.pb(x);
		all_of_col[T[x]][pos[x]] = depth[x];
		if (!first_cols[root[x]].count(T[x]))
			first_cols[root[x]][T[x]] = depth[x];
		for(auto y : adj[x]) {
			root[y] = (y == adj[x][0] ? root[x] : y);
			dfsHld(y); }
	}
	void init(int _N, int R = 0) { N = _N;
		par[R] = depth[R] = ti = 0; dfsSz(R);
		root[R] = R; dfsHld(R);
	}
	int lca(int x, int y) {
		for (; root[x] != root[y]; y = par[root[y]])
			if (depth[root[x]] > depth[root[y]]) swap(x,y);
		return depth[x] < depth[y] ? x : y;
	}

	int closest_anc(int x, int col) { 
		while (x) {
			auto it = first_cols[root[x]].find(col);

			if (it != end(first_cols[root[x]]) && it->second <= depth[x])
				return prev(all_of_col[col].upper_bound(pos[x]))->second;

			x = par[root[x]];
		}
		return -1;
	}
	bool exists(int x, int y, int col) {
		return closest_anc(x,col) >= depth[y];
	}
};
