#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm


def f(x, y):
    return np.sin((6 * (np.cos(np.sqrt(x**2 + y**2))) + (5 * np.arctan2(y, x))))


def main():
    fig = plt.figure()
    ax = plt.axes(projection='3d')

    X = np.linspace(-1, 1, 100)
    Y = np.linspace(-1, 1, 100)
    X, Y = np.meshgrid(X, Y)
    Z = f(X, Y)

    ax = plt.axes(projection='3d')
    surf = ax.plot_surface(X, Y, Z, edgecolor='none', cmap="winter", alpha=0.7)
    ax.set_xlabel('X')
    ax.set_xlim(-1, 1)
    ax.set_ylabel('Y')
    ax.set_ylim(-1, 1)
    ax.set_zlabel('Z')
    ax.set_zlim(-3, 1)

    plt.contour(X, Y, Z, zdir='z', offset=-3, cmap="winter", levels=10)

    fig.colorbar(surf, shrink=0.7, aspect=10, drawedges=False)

    plt.show()


if __name__ == '__main__':
    main()
