#include "header.hpp"

//

const int N = 400;
const int M = 1995;

vector<P> points_;
GraphE graph_;

//

set<int> mstFull() {
  set<int> selected;

  Unionfind uf(N);
  vector<pair<int, int>> edges;
  repeat(i, M) edges.emplace_back(graph_.edges[i].value, i);
  sort(all(edges));
  for (auto p : edges) {
    int ei = p.second;
    auto edge = graph_.edges[ei];
    if (uf.connect(edge.u, edge.v)) {
      // selected.emplace_back(ei);
      selected.insert(ei);
    }
  }
  return selected;
}

set<int> mstPartial(Unionfind continued_uf, int enable_edge_begin) { // クソ雑
  set<int> selected;

  Unionfind uf = continued_uf;
  vector<pair<int, int>> edges;
  iterate(i, enable_edge_begin, M) edges.emplace_back(graph_.edges[i].value, i);
  sort(all(edges));
  for (auto p : edges) {
    int ei = p.second;
    auto edge = graph_.edges[ei];
    if (uf.connect(edge.u, edge.v)) {
      // selected.emplace_back(ei);
      selected.insert(ei);
    }
  }
  return selected;
}

void solve() {
  points_.reserve(N);
  graph_.resize(N);
  graph_.edges.reserve(M);
  repeat(i, N) {
    int x, y;
    scanner >> x >> y;
    points_.emplace_back(y, x);
  }
  repeat(i, M) {
    int a, b;
    scanner >> a >> b;
    auto p1 = points_[a];
    auto p2 = points_[b];
    int l = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    graph_.connect(a, b, l * 3); // 1.7 倍ぐらいを期待値にしておく
  }

  //

  auto selected = mstFull();

  //

  ll ana_total = 0;
  Unionfind uf(N);
  repeat(i, M) {
    int actual_length;
    auto &edge = graph_.edges[i];
    scanner >> actual_length;
    actual_length *= actual_length;

    // update
    edge.value = actual_length;
    selected = mstPartial(uf, i);

    // if (actual_length > edge.value*2) {
    //   // 雑
    //   Unionfind uf2 = uf;
    //   iterate(j, i+1, M) {
    //     auto e = graph_.edges[j];
    //     uf2.connect(e.u, e.v);
    //   }
    //   if (uf2.size(0) == N) {
    //     cout << "0" << endl;
    //   } else {
    //     uf.connect(edge.u, edge.v);
    //     cout << "1" << endl;
    //   }
    // } else {
    //   if (uf.connect(edge.u, edge.v)) {
    //     cout << "1" << endl;
    //   } else {
    //     cout << "0" << endl;
    //   }
    // }
    if (selected.count(i)) {
      ana_total += actual_length;
      uf.connect(edge.u, edge.v);
      cout << "1" << endl;
    } else {
      cout << "0" << endl;
    }
  }
  clog << uf.size(0) << " == " << N << endl;
  clog << ana_total / 1000 << endl;
}

int main() {
  solve();
  return 0;
}
