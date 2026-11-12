# OEIS candidate (no A-number yet): no-three-in-line subsets up to symmetry

<!-- oeis-status:begin -->
**OEIS status: not submitted; no A-number yet** (lab registry, 13 Nov 2026).

- A______, no-three-in-line subsets of the n X n grid up to the symmetries of the square: **candidate** (2026-11-13: repository built (core c3)). Certificate: partial.

Rules and the full registry: [athanor-oeis](https://github.com/iwasborninbali/athanor-oeis/blob/main/REGISTRY.md).
<!-- oeis-status:end -->

## Definition

For n >= 1, a(n) counts subsets of {0,...,n-1}² with no three distinct points collinear, modulo the eight rotations and reflections of the square. The offset is 1. The empty set is included; for n=1 the group acts trivially and the empty set and singleton give two classes.

## Terms / result

| n | a(n) |
|---|---:|
| 1 | 2 |
| 2 | 6 |
| 3 | 46 |
| 4 | 667 |
| 5 | 14066 |
| 6 | 451720 |
| 7 | 12713128 |
| 8 | 514304337 |
| 9 | 20987026978 (partly based on a historical full count) |

## How it was obtained

For each square symmetry, the enumerator constructs its point cycles and enumerates safe unions of those cycles. It tests collinearity by integer determinants, and counts fixed sets by size. Burnside's lemma divides the sum of the eight fixed-set counts by eight. At n=9 the identity fixed count is taken from the lab's existing full enumeration; the other seven profiles were replayed here. At n=8 the full eight-element run was replayed here, and its identity profile also agrees with two other programs in the companion size-profile repository.

## Verification

A separately written program enumerates safe labelled sets and canonicalizes each under all eight transformations for n=1..5. It agrees with Burnside in every case. Fixed profiles at n=6..9 have not been independently canonicalized; n=9 uses a historical identity count. See [CERTIFICATE.md](CERTIFICATE.md).

## Prior art and credit

[A398172](https://oeis.org/A398172) counts labelled safe sets, while [A000769](https://oeis.org/A000769) concerns only maximum 2n-point sets up to symmetry. The laboratory previously computed the n=8 and n=9 fixed-set profiles. See [PRIOR-ART.md](PRIOR-ART.md).

## Reproduce

Requires a compiler supporting `unsigned __int128` (Clang or GCC) and Python 3. For n<=7 the full fixed-set replay takes a few seconds; canonicalization through n=5 takes a few seconds. Each nonidentity replay takes less than a second on the test machine; the full n=8 run takes about 95 seconds.

```sh
cc -O3 -std=c11 programs/fixed_profiles.c -o /tmp/c3_fixed
for n in 1 2 3 4 5 6 7; do /tmp/c3_fixed "$n" > "verification/logs/fixed-n$n.jsonl" 2> "verification/logs/fixed-n$n.stderr"; done
for n in 8 9; do /tmp/c3_fixed "$n" --nonidentity > "verification/logs/fixed-n$n.jsonl" 2> "verification/logs/fixed-n$n.stderr"; done
python3 programs/burnside.py
python3 verification/canonical.py
/tmp/c3_fixed 8 > /tmp/c3-full-fixed-n8.jsonl
```

The expected output is in `verification/logs/burnside.txt` and `verification/logs/canonical.txt`. Replaying into the tracked log files changes timing fields; discard those changes before committing. `burnside.py` combines the replayed nonidentity profiles with the saved source identity profiles for n=8,9.

## Provenance

Adapted from `athanor-foundation/instruments/hammer`, commit `204d667842829e1c15ca2ee23210e86f99835e2d`: `hammer/core/workspace/oeis-row8/fixed_profiles.c`, `fixed-n8.jsonl`, `fixed-n9.jsonl`, `n8.json` and `n9.json` under the same workspace folder. The fixed-profile code was changed to include the identity and provide `--nonidentity`; the independent canonical checker and Burnside combination were written for this repository. No archive DOI has been established for these specific files.

## Author, licence

Aleksei Kudriashov (ORCID 0009-0006-8885-5338), Athanor lab, with AI assistance (OpenAI Codex cores; Claude Code as the lab's guide). Code: MIT; data and text: CC BY 4.0 (see LICENSE.md).
