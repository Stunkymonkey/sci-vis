#!/usr/bin/env python2

import sys
import numpy as np
import matplotlib.pyplot as plt

''' Create 2D visualization '''
fig, ax = plt.subplots()

''' Set vertices, creating lines forming the triangles '''
vertices = np.array([[1, 9], [3, 5], [4, 1], [13, 19], [14, 15], [16, 11]])
triangles = np.array(eval(sys.argv[1]))

''' Plot line segments for each triangle '''
for i in range(0, triangles.shape[0], 3):
    triangle = np.vstack((triangles[i:i+3, :], triangles[i, :]))
    ax.plot(triangle[:, 0], triangle[:, 1], color='b')

''' Plot points '''
ax.plot(vertices[:, 0], vertices[:, 1], 'rx')

''' Set axes' information '''
ax.set_xlim(0, 17)
ax.set_xticks(np.arange(0, 17, 1))

ax.set_ylim(0, 20)
ax.set_yticks(np.arange(0, 20, 1))

''' Set aspect ratio and draw a grid '''
ax.set_aspect(1)
plt.grid()

''' Show figure '''
plt.show()