"""Combine fixed-set profiles into all-set and maximal-set orbit counts."""
import json
from pathlib import Path

root = Path(__file__).resolve().parent.parent
for n in range(1,10):
    lines = [json.loads(line) for line in (root / f'verification/logs/fixed-n{n}.jsonl').read_text().splitlines()]
    if n >= 8:
        source = [json.loads(line) for line in (root / f'data/fixed-n{n}.jsonl').read_text().splitlines()]
        assert len(source) == len(lines) == 7
        for a,b in zip(lines,source):
            assert all(a[key] == b[key] for key in ('n','symmetry','profile','maximal_profile'))
        lines.insert(0, json.loads((root / f'data/n{n}.json').read_text()))
    assert len(lines) == 8
    counts = []
    for key in ('profile', 'maximal_profile'):
        sums = [sum(row[key][k] for row in lines) for k in range(2*n+1)]
        assert all(x % 8 == 0 for x in sums)
        counts.append(sum(sums)//8)
    print(f'n={n} all={counts[0]} maximal={counts[1]}')
