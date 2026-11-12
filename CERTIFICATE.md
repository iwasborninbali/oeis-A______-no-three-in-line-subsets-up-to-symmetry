# Verification certificate

## Claim

- The numbers of square-symmetry classes of all no-three-collinear subsets at n=1..9 are `2, 6, 46, 667, 14066, 451720, 12713128, 514304337, 20987026978`.

## Evidence

| What | Program | Author and date | Coverage | Result |
|---|---|---|---|---|
| Producer | `programs/fixed_profiles.c`, `programs/burnside.py` | Lab fixed-profile enumerator, 2026-11-03; adapted and combined by OpenAI Codex, 2026-11-13 | All eight group elements n<=8; seven nonidentity elements n=9; saved identity profiles n=8,9 | Values above; each size has integral Burnside quotient |
| Independent enumeration | `verification/canonical.py` | OpenAI Codex, 2026-11-13 | n=1..5 | Agrees in each case |

The canonical checker shares no code or input data with the fixed-cycle producer. Both implement the same determinant definition and group action. It directly stores canonical representatives of every admissible subset and therefore does not use Burnside's lemma. At n=8 the saved identity profile was independently replayed by row-based and determinant programs in the companion size-profile repository; at n=9 the saved profile is a historical report of two agreeing traversals.

## Replayed for this repository

2026-11-13, Apple Silicon MacBook Air, Darwin arm64. The C program was compiled with `cc -O3 -std=c11 programs/fixed_profiles.c -o /tmp/c3_fixed`, then invoked for n=1..7, and for n=8,9 with `--nonidentity`, using the commands in the README. `python3 verification/canonical.py` and `python3 programs/burnside.py` were run. Full output and per-symmetry results are under `verification/logs/`. The independent canonical output is `2, 6, 46, 667, 14066`. The replayed seven-element n=8 and n=9 profiles match the stored historical profiles cell by cell. A full eight-element n=8 run was also executed with `/tmp/c3_fixed 8` and agrees with the saved n=8 profile (`verification/logs/full-fixed-n8-check.txt`); the companion triangle repository reran two more identity traversals.

## Not covered

No independent canonicalization was run at n>=6. The symmetry-fixed counts beyond n=5 therefore have only the one fixed-cycle implementation, although conjugacy, integrality, and labelled identity counts provide checks. The n=9 identity enumeration was not replayed here. Historical results are not upgraded into a newly replayed independent verification.

## Guide's independent check

pending

## Verdict

partial — independent class enumeration covers n=1..5; n=6..9 needs independent checking of the symmetry fixed-set counts and n=9 needs replay of the identity traversal.
