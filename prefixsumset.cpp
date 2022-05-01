/*
  Insert and remove elments from multiset.
  If calls to .sum(...) do not differ
  much on consecutive calls then this 
  is fast.
*/

struct PrefixSumSet {
  multiset<int> in;
  multiset<int> out;
  int prefix = 1;
  int insum = 0;

  void rebalance() {
    while (in.size() && out.size() && *in.rbegin() > *out.begin()) {
      int u = *in.rbegin();
      int v = *out.begin();
      insum -= u;
      insum += v;
      in.erase(in.find(u));
      out.erase(out.find(v));
      in.insert(v);
      out.insert(u);
    }
    while (in.size() > prefix) {
      int delta = *in.rbegin();
      insum -= delta;
      in.erase(in.find(delta));
      out.insert(delta);
    }
    while (in.size() < prefix && out.size()) {
      insum += *out.begin();
      in.insert(*out.begin());
      out.erase(out.begin());
    }
  }

  void add(int elem) {
    in.insert(elem);
    insum += elem;
    rebalance();
  }

  void erase(int elem) {
    if (in.find(elem) != in.end()) {
      insum -= elem;
      in.erase(in.find(elem));
    } else {
      out.erase(out.find(elem));
    }
    rebalance();
  }

  int sum(int num) {
    prefix = num;
    rebalance();
    return insum;
  }
};