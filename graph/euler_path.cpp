// author : Simon Lindholm
// deg = indegree - outdegree

// cari: jika ada degree ganjil, pakai src dengan deg ganjil

vector<int> euler_walk(const vector<vector<pair<int, int>>> &g, int m, int sc = 0) {
  int n = g.size();
  vector<int> deg(n);
  vector<int> at(n);
  vector<bool> vis(m);
  vector<int> res;
  stack<int> s;
  s.push(sc);
  deg[sc]++;
  while (!s.empty()) {
    int x = s.top();
    if (at[x] == (int) g[x].size()) {
      res.push_back(x);
      s.pop();
      continue;
    }
    int y, e;
    tie(y, e) = g[x][at[x]++];
    if (!vis[e]) {
      deg[x]--;
      deg[y]++;
      vis[e] = true;
      s.push(y);
    }
  }
  if ((int) res.size() != m + 1) {
    return vector<int>();
  }
  for (int x : deg) {
    if (x < 0) {
      return vector<int>();
    }
  }
  return vector<int>(res.rbegin(), res.rend());
}

// more strightforward, but destroy graph

vector<int> euler_walk(vector<vector<pair<int, int>>> &g, int m, int sc = 0) {
  bool bad = false;
  vector<int> vis(m);
  vector<pair<int, int>> res;
  function<void(int, int)> dfs = [&](int p, int i) {
    for j, e in g[i]:
      g[i].pop_back();
      if (!vis[e]) {
        vis[e] = true;
        dfs(i, j);
      }
    }
    if (!res.empty() && res.back().first != i) {
      bad = true;
    }
    res.emplace_back(p, i);
  };
  dfs(-1, sc);
  if ((int) res.size() != m + 1 || bad) {
    return vector<int>();
  }
  vector<int> ans(m + 1);
  for (int i = m; i >= 0; i--) {
    ans[m - i] = res[i].second;
  }
  return ans;
}

// pencari node (kemungkinan tidak berguna terlalu banyak constant factor)

// directed
int check_euler_walk(vector<vector<pair<int,int>>> &g) {
  int n = (int) g.size();
  vector<int> cnt_indegree(n);
  vector<int> cnt_outdegree(n);
  for (int i = 0; i < n; i++) {
    cnt_outdegree[i] += (int) g[i].size();
    for (auto j : g[i]) {
      cnt_indegree[j.first]++;
    }
  }
  int cnt = 0;
  int vertice = -1;
  for (int i = 0; i < n; i++) {
    int bag = cnt_indegree[i];
    int bag2 = cnt_outdegree[i];
    if (bag != bag2) {
      cnt++;
      if (bag - 1 == bag2) {
        vertice = i;
      }
    }
  }
  if (cnt == 0) {
    return 0;
  }
  if (cnt == 2 && vertice != -1) {
    return vertice;
  }
  return -1;
}

// undirected
int check_euler_walk(vector<vector<pair<int, int>>> &g) {
  int n = (int) g.size();
  int sum_odd_deg = 0;
  int root = 0;
  for (int i = 0; i < n; i++) {
    if (g[i].size() % 2 == 1) {
      sum_odd_deg++;
      root = i;
    }
  }
  if (sum_odd_deg != 0 && sum_odd_deg != 2) {
    return -1;
  }
  return root;
}
