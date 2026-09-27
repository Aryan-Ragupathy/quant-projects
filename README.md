# Quantitative Finance & Probability Projects

A collection of probability experiments and quantitative-finance projects built while learning mathematical modelling, simulation, and C++.

The projects combine mathematical derivations, Monte Carlo simulations, and Python visualizations. The aim is to understand the reasoning behind each model and then compare theoretical results with simulated outcomes.

## Projects

### 1. Auction Winner's Curse
Explore the winner's curse in auctions through simulation and compare outcomes under different assumptions.

- **Code:** [`auction-winners-curse/src/`](auction-winners-curse/src/)
- **Derivation and notes:** [`DERIVATION.md`](auction-winners-curse/DERIVATION.md)
- **Results and visualization:** [`output/`](auction-winners-curse/output/)
- **Project README:** [`README.md`](auction-winners-curse/README.md)

### 2. Kelly Criterion
Study how the fraction of bankroll wagered affects long-run growth. The project compares simulated wealth paths for different betting fractions with the theoretical expected log-growth function.

- **Code:** [`kelly-criterion/src/`](kelly-criterion/src/)
- **Derivation and notes:** [`DERIVATION.md`](kelly-criterion/DERIVATION.md)
- **Results and visualization:** [`output/`](kelly-criterion/output/)
- **Project README:** [`README.md`](kelly-criterion/README.md)

### 3. Monte Carlo Options Pricer
Use Monte Carlo simulation to estimate an option price and examine how the estimate changes as the number of simulated paths increases.

- **Code:** [`montecarlo-options-pricer/src/`](montecarlo-options-pricer/src/)
- **Derivation and notes:** [`DERIVATION.md`](montecarlo-options-pricer/DERIVATION.md)
- **Results and visualization:** [`output/`](montecarlo-options-pricer/output/)
- **Project README:** [`README.md`](montecarlo-options-pricer/README.md)

### 4. Probability Puzzles
A collection of probability problems approached with mathematical derivations and C++ simulations.

| Problem | Materials |
|---|---|
| Coupon Collector | [Derivation](puzzles/01-coupon-collector/derivation.md) · [C++ simulation](puzzles/01-coupon-collector/simulate.cpp) |
| Cards to First Ace | [Derivation](puzzles/02-cards-to-first-ace/derivation.md) · [C++ simulation](puzzles/02-cards-to-first-ace/simulate.cpp) |
| Gambler's Ruin | [Derivation](puzzles/03-gamblers-ruin/derivation.md) · [C++ simulation](puzzles/03-gamblers-ruin/simulate.cpp) |
| Secretary Problem | [Derivation](puzzles/04-secretary-problem/derivation.md) · [C++ simulation](puzzles/04-secretary-problem/simulate.cpp) |
| Birthday Problem | [Derivation](puzzles/05-birthday-problem/derivation.md) · [C++ simulation](puzzles/05-birthday-problem/simulate.cpp) |
| Monty Hall | [Derivation](puzzles/06-monty-hall/derivation.md) · [C++ simulation](puzzles/06-monty-hall/simulate.cpp) |

See the [puzzles overview](puzzles/README.md) for the collection.

## Tools

- **C++** for simulations
- **Python** for data analysis and plots
- **pandas, NumPy, Matplotlib** for working with simulation output and visualizing results

## Repository Structure

```text
quant-projects/
├── auction-winners-curse/
├── kelly-criterion/
├── montecarlo-options-pricer/
└── puzzles/
```

Each main project has its own README and derivation notes. Source code and generated outputs are kept alongside the relevant project.

## Running the Projects

Each project has its own source file and may have its own compilation or input requirements. Check the README inside that project before running it. Python plotting scripts are located in the relevant `output/` directory.

---

This repository is a learning portfolio: derivations, simulations, and visualizations are included so the reasoning can be followed alongside the code.
