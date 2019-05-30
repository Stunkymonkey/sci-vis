#!/usr/bin/env python
# coding: utf-8

import numpy as np
import matplotlib.pyplot as plt


f = lambda x,y: (np.square(x - 0.5) - np.square(y))

x = np.arange(-1.5, 1.5, 0.0005)
y = np.arange(-1.5, 1.5, 0.0005)

X, Y = np.meshgrid(x,y)

Z = f(X,Y)


plt.grid()
plt.contour(X,Y,Z)
plt.savefig('analytical', dpi=600)
plt.show()





