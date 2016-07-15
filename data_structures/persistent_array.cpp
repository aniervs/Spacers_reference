struct persistent_array{
	struct node{
		int val, l, r;
	};

	vector<node> data;
	int total, N;

	int newNode(){
		data.push_back(node());
		return total++;
	}

	int clone(int v){
		int k = newNode();
		data[k].val = data[v].val;
		data[k].l = data[v].l;
		data[k].r = data[v].r;
		return k;
	}

	persistent_array(int n, int d = 0){
		// d -> default value of the array
		total = 0;
		int root = newNode();
		N = n;
		build(root, 0, N, d);
	}

	void build(int r, int b, int e, int d){
		if (b + 1 == e) data[r].val = d;
		else{
			int m = (b + e) >> 1;

			int v = newNode();
			data[r].l = v;
			build(v, b, m, d);

			v = newNode();
			data[r].r = v;
			build(v, m, e, d);
		}
	}

	int get(int r, int b, int e, int x){
		if (b + 1 == e) return data[r].val;
		int m = (b + e) >> 1;
		if (x < m) return get(data[r].l, b, m, x);
		return get(data[r].r, m, e, x);
	}

	int set(int r, int b, int e, int x, int v){
		r = clone(r);
		if (b + 1 == e) data[r].val = v;
		else{
			int m = (b + e) >> 1, t;
			if (x < m){
				t = set(data[r].l, b, m, x, v);
				data[r].l = t;
			}
			else {
				t = set(data[r].r, m, e, x, v);
				data[r].r = t;
			}
		}
		return r;
	}

	int get(int r, int x){
		return get(r, 0, N, x);
	}

	int set(int r, int x, int v){
		return set(r, 0, N, x, v);
	}
};

// Disjoint set

int root(int a, int r, persistent_array &ds){
	// no path compression
	while (true){
		int v = ds.get(r, a);
		if (v >= 0) a = v;
		else return a;
	}
	return -1;
}

int join(int a, int b, int r, persistent_array &ds){
	a = root(a, r, ds);
	b = root(b, r, ds);
	if (a == b) return r;
	int ta = -ds.get(r, a);
	int tb = -ds.get(r, b);

	if (ta > tb){
		swap(ta, tb);
		swap(a, b);
	}

	r = ds.set(r, a, b);
	r = ds.set(r, b, -ta - tb);

	return r;
}