import matplotlib
matplotlib.use('TkAgg')
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import os, sys  

# Checks the number of arguments that are given. If not given the right number, 
# then a usage statment is outputted and the program exits. 
if len(sys.argv) < 3:
    print("Usage:")
    print("$ python3 postprocess.py <input file> <solutions file folder>")
    sys.exit(0)

# Reads the input file and saves each value as a variable
with open(sys.argv[1], 'r') as f:
	firstLine = f.readline()
	secondLine = f.readline()
	firstLine = [float(x) for x in firstLine.split(' ')]
	secondLine = [float(x) for x in secondLine.split(' ')]
	length = firstLine[0]
	width = firstLine[1]
	h = firstLine[2]
	coldTemp = secondLine[0]
	hotTemp = secondLine[1]

# This is the same for every pseudo color plot. 
figure = plt.figure()
image = []
X = np.arange(0, length+h, h)
Y = np.arange(0, width+h, h)
Xmesh, Ymesh = np.meshgrid(X, Y)

# Takes in a directory of all of the solutions and processes them and creates plots
# for each solution file. 
directory = sys.argv[2]
pathway = os.listdir(directory)
for infile in pathway:
	Z = np.loadtxt(os.path.join(directory,infile)).reshape(Y.shape[0],X.shape[0])
	image.append((plt.pcolor(Xmesh,Ymesh,Z, norm=plt.Normalize(coldTemp, hotTemp), cmap = 'jet'),))
plt.colorbar()

# Helps write the animation to a video file. 
Writer = animation.writers['ffmpeg']
writerHelp = Writer(fps=15, metadata=dict(artist='Me'), bitrate=1800)

# This takes all of the plots and creates an animation of them and saves it. 
imageAnimation = animation.ArtistAnimation(figure, image, interval=300, repeat_delay=2000,
    blit=True)
inputName = os.path.splitext(sys.argv[1])[0] 
imageAnimation.save(inputName + '.mp4', writer=writerHelp)
plt.show()
