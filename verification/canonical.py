"""Independent point-set enumeration and D4 canonicalization, n <= 5.

Codex, 2026-11-13. A set is maximal only if no individual point can be added.
"""
import itertools

for n in range(1, 6):
    points = [(x, y) for x in range(n) for y in range(n)]
    N = len(points)
    transforms = []
    for mirror in (False, True):
        for turns in range(4):
            mapping = []
            for x, y in points:
                if mirror:
                    x = n - 1 - x
                for _ in range(turns):
                    x, y = n - 1 - y, x
                mapping.append(x * n + y)
            transforms.append(mapping)
    pairs = [[0]*N for _ in range(N)]
    for a, b in itertools.combinations(range(N), 2):
        x1, y1 = points[a]; x2, y2 = points[b]
        pairs[a][b] = pairs[b][a] = sum(1 << q for q, (x, y) in enumerate(points)
            if q not in (a,b) and (x2-x1)*(y-y1) == (y2-y1)*(x-x1))
    all_classes, maximal_classes = set(), set()
    full = (1 << N)-1
    def canonical(chosen):
        return min(sum(1 << m[i] for i in chosen) for m in transforms)
    def search(start, chosen, selected, forbidden):
        rep = canonical(chosen)
        all_classes.add(rep)
        if selected | forbidden == full:
            maximal_classes.add(rep)
        for q in range(start, N):
            if not forbidden & (1 << q):
                blocked = forbidden
                for p in chosen:
                    blocked |= pairs[p][q]
                search(q+1, chosen+[q], selected | (1 << q), blocked)
    search(0, [], 0, 0)
    print(f'n={n} all={len(all_classes)} maximal={len(maximal_classes)}', flush=True)
