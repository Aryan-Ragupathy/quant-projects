# Gambler's Ruin (Unequal Odds)

## Problem

Start with `i` rupees out of a total `N` rupees in play (opponent starts with
`N - i`). Repeatedly bet ₹1 on a coin with win probability `p` (not
necessarily 0.5). Stop when you reach `N` (you win everything) or hit `0`
(ruin). What is the probability `q(i)` of eventually reaching `N`?

## Setting up the recurrence

Let `q(i)` = probability of eventually reaching `N`, starting from fortune `i`.

**Boundary conditions**, which must hold regardless of `p`:
```
q(0) = 0      (already ruined)
q(N) = 1      (already won)
```

**Recurrence.** After one bet, fortune moves to `i+1` with probability `p` or
`i-1` with probability `1-p`. Conditioning on the outcome of that first bet:

```
q(i) = p · q(i+1) + (1-p) · q(i-1)          for 1 ≤ i ≤ N-1
```

This can't be evaluated by direct substitution (each `q(i)` depends on both a
higher and lower neighbor, with no immediate base case to bottom out on) — it
needs to be solved as a linear recurrence relation holding simultaneously
across all `i`.

## Solving via the characteristic equation

Guess a solution of the form `q(i) = r^i`. Substituting into the recurrence
(shifted to `p·r^(i+1) - r^i + (1-p)·r^(i-1) = 0` and dividing through by
`r^(i-1)`):

```
p·r² - r + (1-p) = 0        (characteristic equation)
```

Solving the quadratic:

```
r = [1 ± (2p-1)] / (2p)
```

which gives two roots:

```
r₁ = 1
r₂ = (1-p)/p
```

**General solution** (valid when `p ≠ 0.5`, so the two roots are distinct):

```
q(i) = A + B·r₂^i
```

**Applying boundary conditions:**
```
q(0) = A + B = 0            →  A = -B
q(N) = A + B·r₂^N = 1       →  B(r₂^N - 1) = 1   →   B = 1/(r₂^N - 1)
```

So `A = -1/(r₂^N - 1)`, and:

```
q(i) = A + B·r₂^i = B(r₂^i - 1) = (r₂^i - 1) / (r₂^N - 1)
```

where `r₂ = (1-p)/p`.

## The p = 0.5 special case

At `p = 0.5`, `r₂ = (1-p)/p = 1`, so the two characteristic roots collapse
into a single repeated root `r = 1`. The general solution form above assumed
two *distinct* roots and breaks down here (it would give the indeterminate
`0/0`). For a repeated root, the correct general solution is instead
`q(i) = A + B·i` (linear in `i`), and applying the same boundary conditions
gives the well-known fair-coin result:

```
q(i) = i / N          (p = 0.5 only)
```

This is a genuinely different functional form from the `p ≠ 0.5` case, not
just a limit that happens to simplify, and must be handled as a separate
branch in code rather than substituted directly into the general formula.

## Simulated result

`sim()` starts a fortune at `i`, flips a `p`-weighted coin each round, moves
`i` up or down by 1, and returns `1` on reaching `N` or `0` on ruin. Averaging
over many independent trials estimates `q(i)` directly, since the return
value is itself the win/loss indicator for that trial.

**Test case:** `N = 20`, `i = 10`, `p = 0.4` (unfavorable game — deliberately
chosen away from `p = 0.5` to test the unequal-odds formula, not just the
symmetric case).

```
Analytic:   q(10) = (1.5^10 - 1) / (1.5^20 - 1) ≈ 0.017046
Simulated (1,000,000 trials): 0.017049
```

Agreement to within ~0.02%, consistent with expected Monte Carlo sampling
noise. The probability itself is small: starting at the midpoint with only a
40% per-bet edge, the chance of reaching `N` before ruin is under 2%,
illustrating how unfavorable odds compound over a long sequence of bets.
