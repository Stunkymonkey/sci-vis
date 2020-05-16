import numpy as np
import matplotlib.pyplot as plt

# The time-varying vector field as a 4D array.
# Axes: [timestep, row(Y), column(X), components(x, y)]
# Be careful with X,Y order: matplotlib plots data as (rows,columns), not as (X,Y).
#
# See also: numpy.swapaxes().

field = np.array([
    [
        [[1, 1], [1, 1], [1, 1], [1, 1]],
        [[1, 0], [1, 0], [1, 1], [1, 1]],
        [[1, 0], [1, 0], [1, 0], [1, 1]],
        [[1, 0], [1, 0], [1, 0], [1, 1]],
    ],
    [
        [[0, 1], [1, 1], [1, 1], [1, 1]],
        [[1, 1], [1, 0], [0, 1], [1, 1]],
        [[1, 0], [1, 1], [1, 0], [1, 0]],
        [[1, 0], [1, 0], [1, 0], [1, 0]],
    ],
    [
        [[1, 1], [1, 0], [1, 0], [1, 1]],
        [[1, 0], [1, 0], [1, 1], [1, 1]],
        [[1, 1], [0, 1], [1, 1], [1, 0]],
        [[0, 1], [0, 1], [0, 1], [1, 0]],
    ],
])

# Generate the domain.
X = np.arange(0, 4, dtype=np.float) + 0.5
Y = np.arange(0, 4, dtype=np.float) + 0.5
xx, yy = np.meshgrid(X, Y)

seedPoints = np.array([
    [0, 0],
    [1, 0]
])

fig = plt.figure()
for f in range(0, field.shape[0]):
    ax = fig.add_subplot(1, 3, f + 1)
    plt.quiver(xx, yy, field[f, :, :, 0], field[f, :, :, 1], units='xy', scale=1)
    ax.set_title("Timestep {}".format(f))

    plt.xlim(0, 5)
    plt.ylim(0, 5)
    plt.xticks(np.arange(0, 5))
    plt.yticks(np.arange(0, 5))
    plt.grid()
    plt.gca().set_aspect('equal', adjustable='box')


plt.show()