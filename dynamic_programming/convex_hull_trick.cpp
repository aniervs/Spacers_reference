/*
	Tested: http://www.infoarena.ro/problema/euro
*/

typedef long long ll;

const ll oo = 0x3f3f3f3f3f3f3f3f;

// upper hull
struct convex_hull_trick
{
	convex_hull_trick(int sz = 50) : h(sz) {}

	void add(ll a, ll b)
	{
		hull cur = hull(a, b);
		int i;
		for (i = 1; !h[i].isEmpty(); ++i)
		{
			cur = merge(cur, h[i]);
			h[i].setEmpty();
		}
		h[i] = cur;
	}

	ll get_max(ll x)
	{
		ll ans = -oo;
		for (size_t i = 1; i < h.size(); ++i)
			if (!h[i].isEmpty())
				ans = max(ans, h[i].get(x));
		return ans;
	}

private:
	struct hull
	{
		vector<pair<ll, ll>> v;

		hull() { }

		hull(ll a, ll b)
		{
			v.clear();
			v.push_back(make_pair(a, b));
		}

		void add(ll a, ll b)
		{
			while (v.size() >= 1 && v.back().first == a 
				&& v.back().second < b)
				v.pop_back();
			if (!v.empty() && v.back().first == a)
				return;
			while (v.size() >= 2)
			{
				ll a1, a2, b1, b2;
				a1 = v[(int) v.size() - 2].first;
				a2 = v[(int) v.size() - 1].first;
				b1 = v[(int) v.size() - 2].second;
				b2 = v[(int) v.size() - 1].second;
				if ((b1 - b2) * (a - a1) > (b1 - b) * (a2 - a1))
					v.pop_back();
				else
					break;
			}
			v.push_back(make_pair(a, b));
		}

		bool isEmpty()
		{
			return v.empty();
		}

		void setEmpty()
		{
			v.clear();
		}

		ll get(ll x)
		{
			int lo = 0, hi = (int) v.size() - 1;
			while (lo < hi)
			{
				int mid = (lo + hi) >> 1;
				if (f(v[mid].first, v[mid].second, x)
					<= f(v[mid + 1].first, v[mid + 1].second, x))
					lo = mid + 1;
				else
					hi = mid;
			}
			return f(v[lo].first, v[lo].second, x);
		}

		ll f(ll a, ll b, ll x)
		{
			return a * x + b;
		}
	};

	hull merge(const hull &a, const hull &b)
	{
		size_t i, j;
		i = j = 0;
		hull ans;
		while (i < a.v.size() && j < b.v.size())
		{
			if (a.v[i].first < b.v[j].first)
				ans.add(a.v[i].first, a.v[i].second), ++i;
			else
				ans.add(b.v[j].first, b.v[j].second), ++j;
		}
		while (i < a.v.size())
			ans.add(a.v[i].first, a.v[i].second), ++i;
		while (j < b.v.size())
			ans.add(b.v[j].first, b.v[j].second), ++j;
		return ans;
	}

	vector<hull> h;
};
