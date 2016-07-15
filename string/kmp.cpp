/*
	Tested: SPOJ NHAY
	Complexity: O(n + m)
*/

vector<int> prefix_function(const string &s)
{
	int n = s.length();
	vector<int> pi(n + 1);

	for (int i = 0, j = pi[0] = -1; i < n; pi[++i] = ++j)
		while (j >= 0 && s[i] != s[j]) j = pi[j];

	return pi;
}

vector<int> kmp(const string &s, const string &p)
{
	auto pi = prefix_function(p);
	int n = s.length(), m = p.length();

	vector<int> ans;

	for (int i = 0, j = 0; i < n; ++i)
	{
		while (j >= 0 && s[i] != p[j])
			j = pi[j];

		if (++j == m)
			ans.push_back(i - m + 1);
	}

	return ans;
}
