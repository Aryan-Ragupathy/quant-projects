# Birthday Problem — Expected Number of People Until a Shared Birthday

## Problem

People enter a room one at a time, birthdays independent and uniform over
365 days (leap years ignored). What is the expected number of people present
at the moment the first birthday collision occurs?

This differs from the classic "birthday paradox" probability question (which
asks for `P(at least one collision)` among a *fixed* group of `n` people).
Here the group size itself is random — the quantity of interest is an
expected stopping time.

## Setup

Let `T` = the number of people present at the moment of the first collision.
Let `P(T > k)` = probability that the first `k` people all have distinct
birthdays (no collision has occurred yet among them):

```
P(T > k) = (365/365) × (364/365) × (363/365) × ... × ((365-k+1)/365)
         = ∏ (i=0 to k-1) (365-i)/365
```

for `0 ≤ k ≤ 365`, and `P(T > k) = 0` for `k > 365` (by the pigeonhole
principle, a collision is guaranteed once 366 people have entered).

## From P(T > k) to E[T]

For a non-negative integer-valued random variable, the expectation can be
computed as a sum over survival probabilities rather than a sum over exact
stopping probabilities:

```
E[T] = Σ (k=0 to 365) P(T > k)
```

This is a standard identity (following from summation by parts on
`Σ k · P(T=k)`), and avoids working with `P(T = k)` directly, which is
harder to write in closed form here.

## Exact value and asymptotic approximation

The exact value is obtained by numerically summing the 366-term series above
using the product formula for each `P(T > k)`. There is also a well-known
closed-form asymptotic approximation, valid for large `n` (365 qualifies):

```
E[T] ≈ √(πn/2) + 2/3
```

For `n = 365`:

```
E[T] ≈ √(π × 365 / 2) + 2/3 ≈ √573.4 + 0.667 ≈ 23.94 + 0.667 ≈ 24.6
```

The exact numerical sum (computing the 366-term product series directly)
gives `E[T] ≈ 24.617`, consistent with the asymptotic approximation.

## Simulated result

`sim()`: assign each entering person a uniformly random birthday
(`std::uniform_int_distribution<int>(0, 364)`), track which days have been
seen, and stop the moment a repeat occurs, returning the number of people
present at that point. Averaging over many independent trials estimates
`E[T]` directly.

*(Simulated output pending — insert the actual value printed by `sim()`
here once available, for comparison against the analytic ≈24.6 figure.)*
