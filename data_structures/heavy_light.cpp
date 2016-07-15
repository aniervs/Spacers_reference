#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef vector<int> vi;
typedef pair<int,int64> pii;

struct segment_tree{
	int n;
	vector<int> st;

	segment_tree(int n=1) : n(n){
		st = vector<int>(4 * n);
		build(1, 0, n);
	}

	void build(int p, int b, int e){
		if (b + 1 == e) st[p] = 1;
		else{
			int m = (b + e) >> 1;
			int l = p << 1, r = l | 1;
			build(l, b, m); build(r, m, e);
			st[p] = st[l] + st[r];
		}
	}

	void update(int p, int b, int e, int x, int v){
		if (b + 1 == e){
			st[p] += v;
		}
		else{
			int m = (b + e) >> 1;
			int l = p << 1, r = l | 1;
			if (x < m) update(l, b, m, x, v);
			if (m <= x) update(r, m, e, x, v);
			st[p] = st[l] + st[r];
		}
	}

	int query(int p, int b, int e, int x, int y){
		if (x <= b && e <= y) return st[p];
		int m = (b + e) >> 1;
		int l = p << 1, r = l | 1;
		int ans = 0;
		if (x < m) ans += query(l, b, m, x, y);
		if (m < y) ans += query(r, m, e, x, y);
		return ans;
	}
};

struct heavy_light{
	int n;
	vector<vi> adj;
	vi father, heavy, height, children, id;

	heavy_light(int n) : n(n){
		adj = vector<vi>(n);
		id = father = heavy = height = children = vi(n);
	}

	void add_edge(int u, int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void go(int root = 0){
		father[root] = -1;
		dfs(root, -1);

		int counter = 0;
		heavy[root] = root;
		hdfs(root, -1, counter);
	}

	void dfs(int s, int f){
		children[s] = 1;
		for (auto u : adj[s]) {
			if (u == f) continue;
			height[u] = height[s] + 1;
			father[u] = s;
			dfs(u, s);
			children[s] += children[u];
		}
	}

	void hdfs(int s, int f, int &counter){
		id[s] = counter++;
		int b = -1;
		for (auto u : adj[s]){
			if (u == f) continue;
			if (b == -1 || children[u] > children[b])
				b = u;
		}

		if (b != -1){
			heavy[b] = heavy[s];
			hdfs(b, s, counter);
		}

		for (auto u : adj[s]){
			if (u != f && u != b){
				heavy[u] = u;
				hdfs(u, s, counter);
			}
		}
	}

	int lca(int u, int v){
		int ans = 0;

		while (heavy[u] != heavy[v]){
			if (height[heavy[u]] < height[heavy[v]])
				swap(u, v);

            // operation on (id[heavy[u]], id[u]) Closed interval

			u = father[heavy[u]];
		}

		if (height[u] < height[v]) swap(u, v);

        // operation on (id[v], id[u]) Closed interval

        // v is the lca
		return v;
	}
};