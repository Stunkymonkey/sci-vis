import matplotlib.pyplot as plt
import numpy as np
import math

files = ["Data" + str(i) + ".csv" for i in range(1, 5)]

for file in files:
    data = np.genfromtxt(file, delimiter='\t', skip_header=1, dtype=float)

    meanx, meany = np.mean(data, axis=0)

    varx, vary = np.var(data, axis=0)

    covXY = 0
    for xn, yn in data:
        covXY += (yn - meany) * (xn - meanx)
    covXY /= len(data)

    corrXY = covXY / (math.sqrt(varx) * math.sqrt(vary))

    beta2 = covXY / varx
    beta1 = meany - beta2 * meanx

    xvalues = data[:, 0]
    startEnd = np.array([min(xvalues), max(xvalues)])

    plt.clf()
    plt.scatter(data[:, 0], data[:, 1], label="Data", color="red")

    plt.plot(startEnd, beta2 * startEnd + beta1, label="linear Regression")
    plt.plot(startEnd, np.array([meany, meany]), label="Mean: {:,.2f}".format(meany), linestyle='--')
    plt.plot(startEnd, np.array([vary, vary]), label="Variancen: {:,.2f}".format(vary), linestyle='-.')
    plt.plot(startEnd, np.array([corrXY, corrXY]), label="Correlation: {:,.2f}".format(corrXY), linestyle=':')

    plt.ylabel('y')
    plt.xlabel('x')
    plt.title(file.replace(".csv", ""))
    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3,
               ncol=2, mode="expand", borderaxespad=0.)

    plt.subplots_adjust(top=0.8)
    plt.savefig(file.replace("csv", "png"))
    #plt.show()
