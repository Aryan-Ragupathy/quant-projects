# Coupon Collector — Expected Rolls to See All 6 Faces

## Problem

Roll a fair 6-sided die repeatedly. What is the expected number of rolls until
every face (1 through 6) has appeared at least once?

## Setup: breaking the total into stages

Let `S(i)` = the expected number of *additional* rolls to see a new (not yet
seen) face, given that `i` distinct faces have already been seen.

Since the total number of rolls is just the sum of the rolls spent in each
stage — going from 0 distinct faces seen to 1, then 1 to 2, ..., then 5 to 6 —
by **linearity of expectation**:

```
E[total rolls] = S(0) + S(1) + S(2) + S(3) + S(4) + S(5)
```

This holds regardless of how the stages depend on each other, which is the
property that makes linearity of expectation useful here: the stages need
not be reasoned about jointly, only individually.

## Expected length of a single stage

At stage `i`, each roll is a "success" (a new face) with probability
`p = (6-i)/6`, or a "repeat" with probability `q = i/6`. So `S(i)` is the
expectation of a geometric random variable with success probability `p`.

**Deriving `E = 1/p` from scratch** (rather than citing it): condition on the
first roll.

- With probability `p`, it's a success — 1 roll used, done.
- With probability `q`, it's a repeat — 1 roll used, and by memorylessness
  (failing doesn't change the odds going forward) the expected number of
  *additional* rolls needed is still `E`.

This gives the self-referential equation:

```
E = p·(1) + q·(1 + E)
  = p + q + qE
  = 1 + qE                (since p + q = 1)

E(1 - q) = 1
E·p = 1                    (since 1 - q = p)
E = 1/p
```

*(Equivalent, longer route: expand `E = Σ r·q^(r-1)·p` directly, multiply
through by `q`, subtract to collapse the series into `1 + q + q² + ... =
1/(1-q)`, and simplify — same result via the series rather than the recursive
argument.)*

Applying this to stage `i`, where `p = (6-i)/6`:

```
S(i) = 1/p = 6 / (6 - i)
```

## Summing the stages

```
E[total rolls] = Σ (i=0 to 5) 6/(6-i)
               = 6/6 + 6/5 + 6/4 + 6/3 + 6/2 + 6/1
               = 1 + 1.2 + 1.5 + 2 + 3 + 6
               = 14.7
```

This is `6 · H₆`, where `H₆ = 1 + 1/2 + 1/3 + 1/4 + 1/5 + 1/6` is the 6th
harmonic number — the general result for `n` faces is `n · Hₙ`.

## Simulated result

`src/kelly_sim.cpp`-style Monte Carlo (`sim()` in this puzzle's C++ file), run
for 1,000,000 trials:

```
Simulated average: 14.694433
Analytic answer:    14.7
```

The two agree to within ~0.04%, well within expected Monte Carlo sampling
noise for 1M trials — the gap shrinks further with more trials, but never
hits exactly zero at any finite trial count.
