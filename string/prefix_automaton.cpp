// prefix automaton O(kn) k = |ALPHA|
// lowercase

vector<vector<int>> prefix_automaton(const string &s, const vector<int> &p) {
  assert((int) s.size() == (int) p.size());
  int n = (int) s.size();
  vector<vector<int>> aut(n, vector<int>(26));
  for (int i = 0; i < n; i++) {
    for (int c = 0; c < 26; c++) {
      if (i > 0 && c + 'a' != s[i]) {
        aut[i][c] = aut[p[i - 1]][c];
      } else {
        aut[i][c] = i + (c + 'a' == s[i]);
      }
    }
  }
  return aut;
}
