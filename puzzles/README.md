# Probability Puzzles, Solved Twice

Classic quant-interview puzzles, each solved on paper first, then confirmed
by an independent Monte Carlo simulation.

## Results

| # | Puzzle | Analytic | Simulated | Gap |
|---|---|---|---|---|
| 1 | Coupon collector (rolls to see all 6 die faces) | 14.700 | 14.694 | 0.04% |
| 2 | Cards drawn until first ace | 10.600 | 10.598 | 0.02% |
| 3 | Gambler's ruin (N=20, i=10, p=0.4) | 0.017046 | 0.017049 | 0.02% |
| 4 | Secretary problem (P(select the best)) | 0.36788 | 0.37086 | 0.8% |
| 5 | Birthday collision (expected people until match) | ~24.6 | pending | — |
| 6 | Monty Hall (P(win \| switch)) | 0.6667 | pending | — |

Full derivations for each puzzle: `0N-puzzle-name/derivation.md`.

## The interesting one

Puzzle #4 (secretary problem) shows a noticeably larger gap (~0.8%) than
puzzles 1-3 (all under 0.05%). The analytic result (`1/e`) is itself an
`n → ∞` asymptotic approximation, so at finite `n` the true optimal-stopping
probability differs slightly from `1/e` — combined with the discrete cutoff
`r = round(n/e)` not landing exactly on the continuous optimum, this likely
accounts for the larger gap rather than indicating a simulation error.

## Structure

```
puzzles/
├── 01-coupon-collector/
├── 02-cards-to-first-ace/
├── 03-gamblers-ruin/
├── 04-secretary-problem/
├── 05-birthday-collision/
├── 06-monty-hall/
└── README.md   (this file)
```

Each folder contains `derivation.md` (paper derivation + simulated result)
and the corresponding C++ simulation source.
