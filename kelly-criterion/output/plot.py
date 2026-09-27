import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data_005 = pd.read_csv("path005.csv", header=None)
data_010 = pd.read_csv("path010.csv", header=None)
data_020 = pd.read_csv("path020.csv", header=None)
data_030 = pd.read_csv("path030.csv", header=None)

median_005 = np.log(data_005.median(axis=0))
median_010 = np.log(data_010.median(axis=0))
median_020 = np.log(data_020.median(axis=0))
median_030 = np.log(data_030.median(axis=0))

f_values = np.linspace(0, 0.5, 500)
g_values = .55*np.log(1+f_values) + .45*np.log(1-f_values)
g_max = 0.55 * np.log(1 + 0.10) + 0.45 * np.log(1 - 0.10)
mean_005 = (np.log(data_005.iloc[:, -1]) / 400).mean()
mean_010 = (np.log(data_010.iloc[:, -1]) / 400).mean()
mean_020 = (np.log(data_020.iloc[:, -1]) / 400).mean()
mean_030 = (np.log(data_030.iloc[:, -1]) / 400).mean()

plt.subplot(1, 2, 1)
plt.plot(f_values,g_values)


plt.axvline(0.10, linestyle="--", label="Kelly fraction = 0.10")
plt.axhline(g_max, linestyle="--")
plt.xlabel("Betting Fraction (f)")
plt.ylabel("Expected Log Growth per Bet, g(f)")
plt.title("Expected Log Growth vs Betting Fraction")
plt.plot([0.05, 0.10, 0.20, 0.30],
         [mean_005, mean_010, mean_020, mean_030],
         'o-',
         label="Simulated Mean Log Growth")
plt.legend()

plt.subplot(1, 2, 2)

plt.plot(median_005, label="f = 0.05")
plt.plot(median_010, label="f = 0.10")
plt.plot(median_020, label="f = 0.20")
plt.plot(median_030, label="f = 0.30")


plt.xlabel("Bet")
plt.ylabel("Median Wealth")
plt.title("Median Wealth Across Simulations")
plt.legend()


plt.show()