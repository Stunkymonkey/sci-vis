#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm


def main():
    x, y, z = np.genfromtxt("./Data", unpack=True)
    index = np.argmax(z)
    print("Result:", "x:", x[index], "y:", y[index], "z:", z[index])

    fig = plt.figure()
    ax = plt.axes(projection='3d')

    ax.scatter(x, y, z, c=z, cmap="viridis", linewidth=0.5)
    plt.contour(x.reshape(24, 24), y.reshape(24, 24), z.reshape(24, 24), zdir='x',
                offset=0, colors="black", levels=24, linestyles='dotted')
    plt.contour(x.reshape(24, 24), y.reshape(24, 24), z.reshape(24, 24), zdir='y',
                offset=5.75, colors="black", levels=24, linestyles='dotted')

    ax.set_xlabel('X')
    ax.set_xlim(0, 5.75)
    ax.set_ylabel('Y')
    ax.set_ylim(0, 5.75)
    ax.set_zlabel('Z')
    ax.set_zlim(0, 1)

    plt.show()


if __name__ == '__main__':
    main()
