# Secretary Problem (Optimal Stopping)

## Problem

`n` candidates arrive one at a time, in random order. After seeing each
candidate, you must immediately accept (stop) or reject (move on) — you can
never go back to a previously rejected candidate. You only observe each
candidate's *relative rank* compared to those seen so far, not their true
rank among all `n`. What strategy maximizes the probability of selecting the
single best candidate overall, and what is that maximum probability?

## Strategy family

The optimal strategy has a clean structure: **reject the first `r`
candidates outright (used only to set a benchmark), then accept the first
subsequent candidate who is better than everyone seen so far** (i.e., a new
"record"). The only free parameter is `r` — the problem reduces to choosing
`r` to maximize the success probability.

## Deriving the success probability for a fixed r

Fix the cutoff `r`. The strategy succeeds if and only if:
1. The overall best candidate is at some position `i > r` (otherwise they're
   in the rejected group and can never be selected), **and**
2. No candidate better than the best-of-first-`r` appears between position
   `r+1` and position `i-1` — otherwise that earlier candidate would already
   have been accepted, before the true best is even reached.

For the true best to be at position `i`, and for the strategy to correctly
reach and select them, the *second-best candidate among the first `i-1`*
must be among the first `r` (so no false "record" triggers early). By
symmetry over the random arrival order, this happens with probability
`r / (i-1)`.

Summing over all possible positions `i` of the true best candidate:

```
P(success | r) = (1/n) · Σ (i = r+1 to n) [ r / (i-1) ]
               = (r/n) · Σ (i = r+1 to n) 1/(i-1)
```

## Taking the n → ∞ limit

Let `x = r/n` (the fraction of candidates skipped). As `n → ∞`, the sum
`Σ 1/(i-1)` from `i = r+1` to `n` approaches the integral:

```
∫ (from x to 1) (1/t) dt = -ln(x) = ln(1/x)
```

So the success probability becomes:

```
P(x) ≈ x · ln(1/x) = -x·ln(x)
```

**Maximizing over x**: differentiate and set to zero.

```
d/dx [ -x·ln(x) ] = -ln(x) - 1 = 0
ln(x) = -1
x = 1/e
```

So the optimal cutoff is to reject the first `n/e` candidates (about 36.8%
of them), then take the next record-setter. Plugging `x = 1/e` back into
`P(x) = -x·ln(x)`:

```
P(success) = -(1/e)·ln(1/e) = -(1/e)·(-1) = 1/e ≈ 0.36788
```

**Result:** the optimal strategy succeeds with probability `1/e ≈ 0.36788`,
independent of `n` (in the large-`n` limit) — a famously clean closed form
for a problem that looks like it should depend heavily on the specific
group size.

## Simulated result

Simulating the reject-first-`r`-then-take-next-record strategy (with `r`
set at the optimal `n/e` cutoff) across many independent random orderings
and tracking the success rate:

```
Simulated: 0.37086
Analytic:  0.36788   (1/e)
```

The gap here (~0.8%) is wider than the sub-0.1% agreement observed in
puzzles 1–3. Possible causes include: `n` not large enough for the
asymptotic `1/e` limit to apply (finite-`n` corrections are `O(1/n)`), the
discrete cutoff `r = round(n/e)` not landing exactly on the continuous
optimum, or a smaller trial count than used in puzzles 1–3. Increasing both
`n` and the trial count would be expected to tighten this gap if it results
from finite-sample effects.
