import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv("results.csv")

for alpha in df['alpha'].unique():
    subset = df[df['alpha'] == alpha]

    n = subset['n']
    eft = subset['EFT_time']
    est = subset['EST_time']
    sd = subset['SD_time']

    # Plot runtime vs n
    plt.figure()
    plt.plot(n, eft, label='EFT')
    plt.plot(n, est, label='EST')
    plt.plot(n, sd, label='SD')
    plt.xlabel("n")
    plt.ylabel("Time (microseconds)")
    plt.title(f"Runtime vs n (alpha={alpha})")
    plt.legend()
    plt.xscale("log")
    plt.yscale("log")
    plt.savefig(f"runtime_alpha_{alpha}.png")

    # Normalized plot
    norm = n * np.log2(n)
    plt.figure()
    plt.plot(n, eft / norm, label='EFT')
    plt.plot(n, est / norm, label='EST')
    plt.plot(n, sd / norm, label='SD')
    plt.xlabel("n")
    plt.ylabel("Time / (n log n)")
    plt.title(f"Normalized Runtime (alpha={alpha})")
    plt.legend()
    plt.savefig(f"normalized_alpha_{alpha}.png")

print("Plots saved!")
