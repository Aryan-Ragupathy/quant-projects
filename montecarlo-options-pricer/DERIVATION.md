# Monte Carlo Option Pricer — Derivation

## Problem

Price a European call option: the right (not obligation) to buy a stock at
strike `K` at expiry time `T`. Payoff at expiry is `max(S_T - K, 0)`. The
option's price today is the discounted expected payoff:

```
Price = e^(-rT) · E[max(S_T - K, 0)]
```

where `r` is the risk-free rate. The difficulty is entirely in the
distribution of `S_T`, the future stock price.

## Modeling the stock price: Geometric Brownian Motion

Under the standard risk-neutral GBM assumption, the future price is:

```
S_T = S_0 · exp( (r - σ²/2)T + σ√T · Z )
```

where `S_0` is today's price, `σ` is volatility, and `Z ~ Normal(0,1)` is
the only random component. This result follows from the stochastic
differential equation defining GBM (used here as a known result, not
re-derived from the underlying SDE).

## Monte Carlo estimator

For each of `trials` independent simulations: draw `Z`, compute `S_T`,
compute the payoff `max(S_T - K, 0)`. Average the payoffs across all trials,
then discount by `e^(-rT)`:

```
MC price = e^(-rT) · (1/trials) · Σ max(S_T^(i) - K, 0)
```

This is an unbiased estimator of the true price; its variance decreases as
`1/trials`, so the standard error shrinks proportionally to `1/√trials` —
explaining why the MC estimate swings widely at low trial counts and
tightens slowly (not linearly) as trials increase.

## Closed-form validation: Black-Scholes

The same expectation has a known closed form (derived by solving the
Black-Scholes partial differential equation, used here as a known result):

```
Call price = S_0 · N(d1) - K · e^(-rT) · N(d2)

d1 = [ln(S_0/K) + (r + σ²/2)T] / (σ√T)
d2 = d1 - σ√T
```

`N(x)` is the standard normal CDF, computed via the error function:
`N(x) = 0.5 · (1 + erf(x/√2))`.

## Parameters used

`S_0 = 100, K = 100, r = 0.05, σ = 0.2, T = 1.0` — standard textbook values
(at-the-money, 1-year expiry, 20% volatility, 5% risk-free rate).

## Results

```
Black-Scholes (exact):  10.4506
```

This matches the commonly cited textbook value for this exact parameter
set, confirming the closed-form implementation is correct.

Monte Carlo estimate at increasing trial counts (100 log-spaced points from
100 to 1,000,000 — full data in `output/convergence.csv`):

| Trials | MC estimate | Gap from Black-Scholes |
|---|---|---|
| 100 | 9.712 | -7.06% |
| 1,024 | 10.476 | +0.24% |
| 9,545 | 10.528 | +0.74% |
| 97,701 | 10.419 | -0.31% |
| 1,000,000 | 10.467 | +0.15% |

The estimate swings widely below ~1,000 trials — as low as 9.02 and as high
as 13.16 — then narrows steadily, settling into a band within roughly ±0.3%
of the exact value beyond ~100,000 trials. The dense 100-point log-spaced
sweep makes the funnel shape of this convergence clearly visible: variance
shrinks as `1/trials`, so the standard error shrinks as `1/√trials`,
explaining why the band narrows quickly at first and then only very
gradually at high trial counts.
