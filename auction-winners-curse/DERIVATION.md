# Auctions and the Winner's Curse — Derivation

## Problem

A common-value item is worth `V = 100`. `N` bidders each observe an
independent noisy estimate `X_j = V + ε_j`, `ε_j ~ Normal(0, σ²)`. Bidders
bid, the highest bidder wins. How does the payment rule (first-price vs.
second-price) affect the winner's expected overpayment, and can a bidder
correct for it?

## Why the winner overpays (first-price, naive)

The winner is whoever has the largest `X_j`, i.e. the largest of `N` iid
noisy draws. Since noise is symmetric around 0, an individual draw is
equally likely to be above or below the true value — but the *maximum* of
`N` such draws is systematically above the true value, because winning
selects specifically for the largest realization. This is the winner's
curse: winning is itself evidence the winner's estimate was inflated.

## Shading correction

Define `c(n) = E[max(ε_1,...,ε_n)]`, the expected amount by which the
largest of `n` noise draws exceeds 0. This has no simple closed form for
general `n` under a Gaussian noise model (unlike, e.g., max of uniforms),
so it is estimated numerically: simulate `n` noise draws many times,
average the maximum.

A shaded bidder bids `X_j - c(n)` instead of `X_j`. Since every bidder
shades by the same constant, the *ranking* of bids is unchanged (the winner
is still whoever had the largest raw estimate) — only the price paid
changes. Under first-price:

```
naive overpayment   = E[max(ε_1,...,ε_n)]        = c(n)
shaded overpayment  = E[max(ε_1,...,ε_n)] - c(n)  ≈ 0
```

The naive overpayment and `c(n)` are the same quantity by construction
(the winner's bid *is* the max draw), so shading by the correctly-estimated
`c(n)` drives expected overpayment to zero.

## Second-price payment rule

Under second-price, the winner still has the largest `X_j`, but pays the
**second-highest** bid rather than their own. Since a constant shift applied
to every bid changes neither the winner nor the gap between the top two
bids, shading has no effect on what the winner pays under second-price:

```
second-price payment = second-highest of (X_1,...,X_n)
second-price overpayment = E[2nd-highest of (ε_1,...,ε_n)]
```

This is a genuinely different order statistic from `c(n)` (which uses the
*maximum*), and it is smaller in expectation, because the second-highest of
`n` draws is less extreme than the maximum. This means **second-price
auctions partially self-correct the winner's curse through the payment rule
itself**, without requiring any strategic shading — though the correction is
partial, not complete: the second-highest of a growing crowd still trends
upward with `n`, just more slowly than the maximum does.

## Simulated results

`n = 2` to `20`, `σ = 10`, 1,000,000 trials for `c(n)` and second-price
overpayment, 1,000 independent trials for the naive first-price estimate
(see `output/auction_results.csv` for full data):

| n | c(n) | first-price naive | first-price shaded | second-price |
|---|---|---|---|---|
| 2 | 5.64 | 5.46 | -0.17 | -5.63 |
| 6 | 12.67 | 12.64 | -0.03 | 6.42 |
| 10 | ~15.9 | ~15.9 | ~0.0 | ~10.0 |
| 20 | ~18.1 | ~18.1 | ~0.0 | ~14.1 |

(Full 19-row sweep in the CSV.) Shaded first-price overpayment stays near
zero across all `n`, as expected. Second-price overpayment sits between
naive and shaded — substantially better than naive, but not flat — since
the second-order statistic itself grows with `n`, just more slowly than the
maximum.

## Note on revenue equivalence

Classical auction theory's revenue equivalence result (first-price and
second-price yield the same expected seller revenue) is typically stated
under **private-value** assumptions (each bidder has their own independent
value for the item). This setup is **common-value** (one true value, noisy
shared estimates), which is exactly the case where the classical theorem's
assumptions do not directly apply — consistent with the visibly different
overpayment curves observed here for the two payment rules under common
values.
