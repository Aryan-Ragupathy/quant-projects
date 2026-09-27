# Monty Hall Problem

## Problem

Three doors: one hides a car, two hide goats. The contestant picks a door.
The host, who knows what is behind every door, then opens one of the two
remaining doors, always revealing a goat (never the car, and never the
contestant's already-chosen door). The contestant is offered the choice to
switch to the other unopened door or stay with their original pick. What is
the probability of winning the car under each strategy?

## Setup

Let the contestant's initial pick be door A, with the car placed uniformly
at random behind one of the three doors before any choice is made.

## Strategy: stay

If the contestant stays, they win if and only if their original pick was
correct. Since the car was placed uniformly at random among 3 doors before
any information was revealed:

```
P(win | stay) = 1/3
```

Critically, the host's action of revealing a goat door does not change this
probability, because the host's reveal is not random with respect to the
contestant's original pick — the host always successfully avoids revealing
the car, regardless of where it is. No new information is provided about
whether the *contestant's own original door* was correct.

## Strategy: switch

The contestant wins by switching if and only if their **original pick was
wrong** (since, if the original pick was wrong, the host is forced to reveal
the other goat door, leaving only the car door left to switch to).

```
P(original pick wrong) = 2/3
```

so:

```
P(win | switch) = 2/3
```

## Why this feels counterintuitive

The apparent paradox comes from treating the host's reveal as though it
provides symmetric information about the two remaining doors. It does not:
the host's action is constrained (must avoid both the car and the
contestant's door), which means the reveal carries information specifically
about the *unchosen* doors as a group, not about the contestant's own door.
Switching effectively lets the contestant claim "the car is behind one of
the two doors I didn't pick" (a 2/3 probability event at the outset), now
narrowed down to a single specific door by the host's forced reveal.

## Verification by direct case enumeration

There are exactly 3 equally likely placements of the car (behind door A, B,
or C), and the contestant is assumed to always initially pick door A without
loss of generality (by symmetry):

| Car location | Host opens | Stay wins? | Switch wins? |
|---|---|---|---|
| A | B or C (goat) | Yes | No |
| B | C (forced, only remaining goat door) | No | Yes |
| C | B (forced, only remaining goat door) | No | Yes |

Switching wins in 2 out of 3 equally likely cases; staying wins in 1 out of 3.

## Simulated result

`sim()`: randomly place the car behind one of 3 doors, fix the contestant's
initial pick, have the host open a goat door among the remaining two
(choosing randomly between them when both are goats, i.e. when the
contestant's initial pick was already correct), then check whether switching
would have won. Averaging over many independent trials estimates
`P(win | switch)` directly.

*(Simulated output pending — insert the actual value printed by `sim()`
here once available, for comparison against the analytic 2/3 ≈ 0.6667.)*
