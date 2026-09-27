# Expected Draws to First Ace

## Problem

Draw cards one at a time, without replacement, from a well-shuffled standard
52-card deck (4 aces). What is the expected number of cards drawn before and
including the first ace?

Note this is sampling *without* replacement — unlike a die roll, the
probability of drawing an ace isn't fixed at each draw, since the deck
composition changes as cards are removed. The simple "memoryless geometric"
argument used for the coupon collector problem doesn't directly apply here.

## Method 1 — Symmetry / gaps argument

Instead of thinking about drawing cards sequentially, consider the entire
shuffled deck as one random arrangement of all 52 cards laid out in a line.
By symmetry, every position in the deck is equally likely to hold any
particular card — there's nothing that favors position 1 over position 30
before any card is revealed.

The 4 aces split the 48 non-ace cards into **5 gaps**: before the 1st ace,
between the 1st and 2nd ace, between the 2nd and 3rd, between the 3rd and
4th, and after the 4th ace.

By symmetry, these 5 gaps are *exchangeable* — no gap is structurally
different from any other, so each gap's expected size (in non-ace cards) must
be equal. Since the 48 non-ace cards are split across exactly 5 gaps:

```
E[non-ace cards in any one gap] = 48 / 5
```

In particular, this applies to the "before the first ace" gap. The number of
draws to see the first ace is that many non-ace cards, plus 1 for the ace
itself:

```
E[draws to first ace] = 48/5 + 1 = 53/5 = 10.6
```

This method requires no summation or generating functions — the entire
argument is symmetry plus one division.

## Method 2 — Generating functions

Let `S` be the coefficient of `x^3` in the polynomial:

```
S(x) = 49(1+x)^3 + 48(1+x)^4 + 47(1+x)^5 + ... + 1·(1+x)^51
```

(This arises from setting up the problem via the position-counting / ranks
argument — the coefficients descend 49, 48, ..., 1 as the powers of `(1+x)`
ascend from 3 to 51.)

**Multiply through by `(1+x)`:**

```
S(1+x) = 49(1+x)^4 + 48(1+x)^5 + ... + 1·(1+x)^52
```

**Subtract `S` from `S(1+x)`** — this is a summation-by-parts trick: each
term's coefficient decreases by 1 as the power increases by 1, so subtracting
telescopes the sum down to just the boundary terms:

```
Sx = (1+x)^4 + (1+x)^5 + ... + (1+x)^52  −  49(1+x)^3
```

**Extract the coefficient of `x^4`** on both sides. Multiplying `S` by `x`
shifts every power up by one, so the coefficient of `x^4` in `Sx` equals the
coefficient of `x^3` in `S`, the quantity of interest.

On the right-hand side:
- The `−49(1+x)^3` term is degree 3, so it contributes **0** to the `x^4`
  coefficient.
- The remaining sum `Σ (k=4 to 52) C(k,4)` is exactly the **hockey-stick
  identity**, which collapses to `C(53,5)`.

So:

```
coeff of x^3 in S = C(53,5)
```

**Final division.** The actual expectation is this coefficient divided by
`C(52,4)` (from how the counting argument sets up the problem):

```
E = C(53,5) / C(52,4)
```

Using the identity `C(n,k) / C(n-1,k-1) = n/k`:

```
E = 53/5 = 10.6
```

Both methods agree exactly: **E = 53/5 = 10.6**.

## Simulated result

`sim()` (see `simulate.cpp`): builds a 52-element array marked so the first 4
values represent aces, shuffles it with `std::shuffle` each trial, and scans
from the front counting positions until an ace is found. Run for 1,000,000
trials:

```
Simulated average: 10.597932
Analytic answer:    10.6
```

Agreement to within ~0.02%, consistent with expected Monte Carlo sampling
noise at this trial count.

## Note

Two independent derivations — a short symmetry argument and a longer
generating-function approach — land on the same closed-form answer. The
symmetry argument is the faster route for this specific problem; the
generating-function method is heavier machinery but generalizes to variants
of the problem (e.g., expected position of the k-th ace) where symmetry alone
doesn't immediately give the answer.
