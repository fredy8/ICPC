/*
10 10
7 7 3 3 5 9 9 8 1 8 
QUERY 6 6 
UPDATE 3 4 
QUERY 0 1 
QUERY 0 5 
QUERY 4 7 
QUERY 3 5 
QUERY 0 2 
QUERY 4 6 
UPDATE 6 10 
QUERY 0 9
10 10
7 7 3 3 5 9 9 8 1 8 
QUERY 6 6 
UPDATE 3 4 
QUERY 0 1 
QUERY 0 5 
QUERY 4 7 
QUERY 3 5 
QUERY 0 2 
QUERY 4 6 
UPDATE 6 10 
QUERY 0 9
*/
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <ctime>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> vi;

struct node{
    ii left, right, max;
};

int size(ii a) {
    return a.second - a.first + 1;
}

ii max(ii a, ii b) {
    return size(a) > size(b) ? a : b;
}

#define OP ==

class SegmentTree {         // the segment tree is stored like a heap array
private: vi A;            // recall that vi is: typedef vector<int> vi;
  vector<node> st;
  int n;
  int left (int p) { return p << 1; }     // same as binary heap operations
  int right(int p) { return (p << 1) + 1; }

  void build(int p, int L, int R) {                           // O(n log n)
    if (L == R) {                            // as L == R, either one is fine 
      st[p] = node();                                         // store the index
      st[p].max = st[p].left = st[p].right = ii(L, R);
    } else {                                // recursively compute the values
      build(left(p) , L              , (L + R) / 2);
      build(right(p), (L + R) / 2 + 1, R          );
      node p1 = st[left(p)], p2 = st[right(p)];
      st[p] = node();
      st[p].max = max(p1.max, p2.max);
      if(p1.right.second + 1 == p2.left.first && A[p1.right.second] OP A[p2.left.first]) {
        st[p].max = max(st[p].max, ii(p1.right.first, p2.left.second));
      }

      st[p].left = p1.left;
      if(p2.left.first == p1.left.second + 1 && A[p1.left.second] OP A[p2.left.first])
        st[p].left = ii(p1.left.first, p2.left.second);

      st[p].right = p2.right;
      if(p2.right.first == p1.right.second + 1 && A[p1.right.second] OP A[p2.right.first])
        st[p].right = ii(p1.right.first, p2.right.second);
  } }

  node rmq(int p, int L, int R, int i, int j) {                  // O(log n)
    node nullnode;
    nullnode.max = ii(-1, -1);
    if (i >  R || j <  L) return nullnode; // current segment outside query range
    if (L >= i && R <= j) return st[p];               // inside query range
    //i, L, R, j

     // compute the min position in the left and right part of the interval
    node p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
    node p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

    if (p1.max == ii(-1, -1)) return p2;   // if we try to access segment outside query
    if (p2.max == ii(-1, -1)) return p1;                               // same as above

    node ret;

    ret.max = max(p1.max, p2.max);
      if(p1.right.second + 1 == p2.left.first && A[p1.right.second] OP A[p2.left.first]) {
        ret.max = max(ret.max, ii(p1.right.first, p2.left.second));
      }

    ret.left = p1.left;
    if(p2.left.first == p1.left.second + 1 && A[p1.left.second] OP A[p2.left.first])
      ret.left = ii(p1.left.first, p2.left.second);

    ret.right = p2.right;
    if(p2.right.first == p1.right.second + 1 && A[p1.right.second] OP A[p2.right.first])
      ret.right = ii(p1.right.first, p2.right.second);

    return ret;
  }          // as as in build routine

  void update_point(int p, int L, int R, int idx, int new_value) {
    // this update code is still preliminary, i == j
    // must be able to update range in the future!
    int i = idx, j = idx;

    // if the current interval does not intersect 
    // the update interval, return this st node value!
    if (i > R || j < L)
      return;

    // if the current interval is included in the update range,
    // update that st[node]
    if (L == i && R == j) {
      A[i] = new_value; // update the underlying array
      return; // this index
    }

    // compute the minimum pition in the 
    // left and right part of the interval
    
    update_point(left(p) , L              , (L + R) / 2, idx, new_value);
    update_point(right(p), (L + R) / 2 + 1, R          , idx, new_value);
    node p1 = st[left(p)], p2 = st[right(p)];

    st[p].max = max(p1.max, p2.max);
      if(p1.right.second + 1 == p2.left.first && A[p1.right.second] OP A[p2.left.first]) {
        st[p].max = max(st[p].max, ii(p1.right.first, p2.left.second));
      }

    // return the pition where the overall minimum is
    st[p].left = p1.left;
    if(p2.left.first == p1.left.second + 1 && A[p1.left.second] OP A[p2.left.first])
      st[p].left = ii(p1.left.first, p2.left.second);

    st[p].right = p2.right;
    if(p2.right.first == p1.right.second + 1 && A[p1.right.second] OP A[p2.right.first])
      st[p].right = ii(p1.right.first, p2.right.second);
  }

public:
  SegmentTree(const vi &_A) {
    A = _A; n = (int)A.size();              // copy content for local usage
    st.assign(4 * n, node());            // create large enough vector of zeroes
    build(1, 0, n - 1);                                  // recursive build
  }

  int rmq(int i, int j) {
    return size(rmq(1, 0, n - 1, i, j).max);
  }   // overloading

  void update_point(int idx, int new_value) {
    return update_point(1, 0, n - 1, idx, new_value); }
};

int MAX_NUM = 100000;

vi randomNums(int N) {
    srand(time(NULL));
    vi ret;
    FOR(i, 0, N)
        ret.pb(rand() % MAX_NUM);
    return ret;
}
  

int main() {
    int N, Q;
    while(cin >> N >> Q) {
        vi A;
        FOR(i, 0, N) {
            int k; cin >> k;
            A.pb(k);
        }
        SegmentTree st(A);

        FOR(i, 0, Q) {
            string type;
            int a, b;
            cin /*>> type*/ >> a >> b;
            /*if(type == "QUERY") {*/
                cout << st.rmq(a - 1, b - 1) << endl;
            /*} else {
                st.update_point(a, b);
            }*/
        }
    }
}
