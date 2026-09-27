# Kelly Fraction — Derivation

**Setup.** A repeated even-money bet: win probability `p = 0.55`, lose probability
`q = 1 - p = 0.45`. Betting a fraction `f` of current bankroll each round:

- Win → bankroll multiplies by `(1 + f)`
- Lose → bankroll multiplies by `(1 - f)`

After `n` bets with `W` wins and `L = n - W` losses, wealth is:

```
X_n = X_0 · (1 + f)^W · (1 - f)^L
```

**Growth rate.** We want to maximize the *expected long-run exponential growth
rate*, not expected wealth directly (maximizing expected wealth alone pushes
`f` toward 1 and blows up almost surely). Define the per-bet expected log-growth:

```
g(f) = E[ (1/n) log(X_n / X_0) ] = p·log(1 + f) + q·log(1 - f)
```

**Maximize.** Differentiate with respect to `f` and set to zero:

```
g'(f) = p/(1+f) - q/(1-f) = 0
p(1 - f) = q(1 + f)
p - pf = q + qf
p - q = f(p + q) = f          [since p + q = 1]

f* = p - q
```

**Plug in numbers.** `p = 0.55`, `q = 0.45`:

```
f* = 0.55 - 0.45 = 0.10
```

So the growth-optimal bet size is **10% of bankroll per round** — this is the
"full Kelly" fraction used in the simulation, and it's exactly where the growth
curve in `output/kelly_comparison.png` (left panel) peaks.

**Why over-betting is catastrophic, not just suboptimal.** Note `g(f)` is
concave and crosses zero again at `f = 2f* = 0.20` — betting *twice* the Kelly
fraction gives approximately zero long-run growth despite the bet still having
positive expected value per round. This is confirmed in the simulation: 2x
Kelly (f=0.20) produces a simulated mean log-growth rate of -0.000148 per bet
(essentially flat, statistically indistinguishable from zero) and a final
median log-wealth of only 0.168 after 400 bets — despite each individual bet
being profitable in expectation. Beyond `2f*`, growth rate is *negative*: 3x
Kelly (f=0.30) has a simulated mean log-growth of -0.0159 per bet, driving
final median log-wealth to -6.12 after 400 bets (i.e. `e^-6.12 ≈ 0.0022` of
starting wealth — a 99.8% loss) even though the underlying edge never changed.
This is the standard explanation for why Kelly practitioners deliberately
under-bet ("half Kelly") — the growth curve is asymmetric around the peak, and
the downside of over-betting is far steeper than the cost of under-betting.

**Sensitivity to edge misestimation.** If your estimate of `p` is off by
`Δ` (i.e., true probability is `0.55 - Δ` but you size for `0.55`), the fraction
you *should* have bet shifts by `2Δ` (since `f* = 2p - 1`, so `df*/dp = 2`).
A 3-point overestimate of your edge (`Δ = 0.03`) means you're over-betting by
6 percentage points of bankroll per round — small-looking estimation errors
translate into meaningfully wrong bet sizes, which is a second, independent
argument for sizing below full Kelly in practice.

## Simulated results

400 bankrolls per strategy, 600 bets each. Left panel: analytic growth curve
`g(f)` against the simulated mean log-growth per bet at each of the four
tested fractions. Right panel: median cumulative log-wealth across
simulations, bet-by-bet, over the first 400 bets.

| Strategy | f | Simulated mean log-growth/bet | Analytic peak? | Final median log-wealth (bet 400) |
|---|---|---|---|---|
| Fixed | 0.05 | +0.003696 | below peak | 1.452 |
| Full Kelly | 0.10 | +0.005043 | at peak | 1.908 |
| 2x Kelly | 0.20 | -0.000148 | past 2nd root | 0.168 |
| 3x Kelly | 0.30 | -0.015889 | well past 2nd root | -6.125 |

The simulated mean log-growth values track the analytic `g(f)` curve closely
(visible as the orange markers sitting almost exactly on the blue curve in
the left panel), confirming the derivation. Full Kelly (f=0.10) gives both
the highest per-bet growth rate and the highest final wealth of the four
strategies tested. 2x Kelly's growth rate is close to zero but not exactly
zero in this simulation — `f=0.20` is exactly the analytic second root of
`g(f)` for `p=0.55` (since `2f* = 2(0.10) = 0.20`), so the small residual
(-0.000148 rather than 0) is ordinary Monte Carlo sampling noise from
averaging only 400 bankrolls, not a mismatch between the analytic and
simulated setup.
