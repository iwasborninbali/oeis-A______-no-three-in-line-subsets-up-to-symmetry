# Prior art

OEIS searches on 2026-11-13, `https://oeis.org/search` with `fmt=json`:

| Exact query | Results |
|---|---:|
| `2,6,46,667,14066` | 0 |
| `6,46,667,14066` | 0 |
| `46,667,14066` | 0 |
| `no three collinear subsets square symmetries` | 0 |

The shifted searches omit the first one or two terms. These searches are not proof of novelty. [A398172](https://oeis.org/A398172) is the number of labelled no-three-collinear subsets, including the empty set; [A398184](https://oeis.org/A398184) is the labelled inclusion-maximal count. [A000769](https://oeis.org/A000769) concerns inequivalent solutions of the 2n-point placement problem rather than sets of every size. None has the definition used here.

The source workspace `oeis-row8` contains seven nonidentity symmetry fixed-set profiles for each of n=8 and 9, together with the labelled identity profiles and Burnside-by-size checks. Its reports cite the endpoint counts at n=8 and 9 as agreeing with A000769. Those earlier computations belong to the lab and do not by themselves give a separate independent check of every fixed-set profile here.
