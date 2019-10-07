import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import numpy as np
import os, sys 

# Checks the number of arguments that are given. If not given the right number, 
# then a usage statment is outputted and the program exits. 
if len(sys.argv) < 3:
    print("Usage:")
    print("$ python3 postprocess.py <input file> <solution file>")
    sys.exit(0)

# Reads the input file and saves the length, width and h. 
with open(sys.argv[1], 'r') as f:
	readData = f.readline()
	readData = [float(x) for x in readData.split(' ')]
	length = readData[0]
	width = readData[1]
	h = readData[2]

# Loads in the solution file and stores the temperatures in an array.
temperatures = np.loadtxt(sys.argv[2])

# Calcultes the mean temperature of the solution file. 
meanTemp = np.mean(temperatures)

# Prints out input file name and mean temperature into console. 
print ("Input file processed: {}".format(sys.argv[1]))
print ("Mean Temperature: {:.4f}".format(meanTemp))

# Creates the pseudocolor plot. 
X = np.arange(0, length+h, h)
Y = np.arange(0, width+h, h)
Z = temperatures.reshape(Y.shape[0],X.shape[0])
X, Y = np.meshgrid(X, Y)
plt.figure(1)
plt.pcolor(X,Y,Z, cmap='jet')
plt.colorbar()
plt.axis([0, length, width - 2*width, width+width])

# This overlays the mean temperature isoline on the pseudocolor plot. 
plt.contour(X,Y,Z, levels = [meanTemp])

# Output plots and also saves it as a .png file. 
plt.savefig(os.path.splitext(sys.argv[1])[0] + "_" 
	+ os.path.splitext(sys.argv[2])[0])
plt.show()