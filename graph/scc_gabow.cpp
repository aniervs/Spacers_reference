/*
	Gabow's strongly connected component

	Complexity: O(n + m)
*/

struct graph
{
	int n;
	vector<vector<int>> adj;

	graph(int n) : n(n), adj(n) {}

	void add_edge(int src, int dst)
	{
		adj[src].push_back(dst);
	}

	vector<vector<int>> strongly_connected_components()
	{
		vector<vector<int>> scc;
		vector<int> S, B, I(n);
		function<void(int)> dfs = [&](int u)
		{
			B.push_back(I[u] = S.size());
			S.push_back(u);
			for (int v : adj[u])
			{
				if (!I[v]) dfs(v);
				else while (I[v] < B.back()) B.pop_back();
			}
			if (I[u] == B.back())
			{
				scc.push_back({});
				B.pop_back();
				for (; I[u] < S.size(); S.pop_back())
				{
					scc.back().push_back(S.back());
					I[S.back()] = n + scc.size();
				}
			}
		};
		for (int u = 0; u < n; ++u)
			if (!I[u]) dfs(u);
		return scc; // I[u] - n is the index of u
	}
};
