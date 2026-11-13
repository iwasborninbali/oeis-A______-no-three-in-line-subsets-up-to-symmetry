// Guide's independent count (13 Nov 2026): no-three-in-line subsets of the n x n grid (n <= 8), all and inclusion-maximal,
// labelled and up to the 8 symmetries of the square, by direct enumeration and canonical forms (no Burnside).
// Masks are 128-bit, so n <= 11.
// A set is counted as an orbit representative iff its bitmask is the minimum of its 8 images.
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef unsigned __int128 u64;   /* 128-bit masks (n <= 11) */
static inline int ctz128(u64 m) { unsigned long long lo = (unsigned long long)m; return lo ? __builtin_ctzll(lo) : 64 + __builtin_ctzll((unsigned long long)(m >> 64)); }
static int n, P, img[8][128];
static u64 line[128][128];            // cells on the line through a and b (excluding nothing; includes a,b)
static unsigned long long all, allorb, mx, mxorb;
static int ch[128];
static u64 tr(int g, u64 m) { u64 r = 0; while (m) { int c = ctz128(m); m &= m - 1; r |= (u64)1 << img[g][c]; } return r; }
static int isrep(u64 m) { for (int g = 1; g < 8; g++) if (tr(g, m) < m) return 0; return 1; }
static void visit(u64 set, u64 forb) {
  all++; int rep = isrep(set); allorb += rep;
  u64 full = P == 128 ? ~(u64)0 : (((u64)1 << P) - 1);
  if ((set | forb) == full) { mx++; mxorb += rep; }
}
static void dfs(int k, int next, u64 set, u64 forb) {
  visit(set, forb);
  for (int p = next; p < P; p++) {
    if ((forb >> p & 1) || (set >> p & 1)) continue;
    u64 f = forb;
    for (int i = 0; i < k; i++) f |= line[ch[i]][p];
    ch[k] = p;
    dfs(k + 1, p + 1, set | (u64)1 << p, f & ~(set | (u64)1 << p));
  }
}
int main(int argc, char **argv) {
  n = atoi(argv[1]); P = n * n; if (P > 128) return 2;
  for (int c = 0; c < P; c++) { int x = c % n, y = c / n, m = n - 1;
    int X[8] = {x, m - y, m - x, y, m - x, x, y, m - y}, Y[8] = {y, x, m - y, m - x, y, m - y, x, m - x};
    for (int g = 0; g < 8; g++) img[g][c] = Y[g] * n + X[g]; }
  for (int a = 0; a < P; a++) for (int b = 0; b < P; b++) { u64 m = 0; if (a != b)
      for (int c = 0; c < P; c++) { long cr = (long)(b % n - a % n) * (c / n - a / n) - (long)(b / n - a / n) * (c % n - a % n); if (cr == 0) m |= (u64)1 << c; }
    line[a][b] = m; }
  dfs(0, 0, 0, 0);
  printf("n=%d all=%llu all_orbits=%llu maximal=%llu maximal_orbits=%llu\n", n, all, allorb, mx, mxorb);
  return 0;
}
