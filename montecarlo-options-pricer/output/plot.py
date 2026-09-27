import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("output.csv")

plt.axhline(data["black_scholes_price"][0], color="orange", linestyle="--", label="Black-Scholes (exact)")
plt.plot(data["trials"], data["mc_price"], marker="o", markersize=3,label="Monte Carlo estimate")

plt.xscale("log")
plt.xlabel("Number of simulated paths (log scale)")
plt.ylabel("Option price")
plt.title("Monte Carlo convergence to Black-Scholes")
plt.legend()
#plt.savefig("output/option_convergence.png", dpi=150)
plt.show()