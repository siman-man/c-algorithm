struct DoubleEndPQ {
  multiset<int> s;

  int size() {
    return s.size();
  }

  bool empty() {
    return size() == 0;
  }

  void insert(int v) {
    s.insert(v);
  }

  int min() {
    return *s.begin();
  }

  int max() {
    return *s.rbegin();
  }

  void deleteMin() {
    if (empty()) return;

    s.erase(s.begin());
  }

  void deleteMax() {
    if (empty()) return;

    auto it = s.end();
    --it;
    s.erase(it);
  }
};