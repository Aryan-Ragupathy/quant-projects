import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("output/auction_results.csv")

plt.figure(figsize=(8, 5))
plt.plot(data["n"], data["fp_naive_overpayment"], marker="o", label="first-price, naive")
plt.plot(data["n"], data["fp_shaded_overpayment"], marker="o", label="first-price, shaded")
plt.plot(data["n"], data["sp_overpayment"], marker="o", label="second-price (pays 2nd-highest)")
plt.axhline(0, color="gray", linewidth=0.5)
plt.xlabel("Number of bidders (n)")
plt.ylabel("Overpayment vs true value (100)")
plt.title("Winner's curse: naive vs. shaded vs. second-price")
plt.legend()
plt.tight_layout()
plt.savefig("output/auction_comparison.png", dpi=150)
print("Saved output/auction_comparison.png")
