# Minor Project 1

# **Image Segmentation**

Here we implement the four different image segementation algorithms and compare their results with each other on different grey scale images.
1. K-mean clustering
   
2. Otsu Thresholding
   
   Otsu algorithm is a thresholding based segmentation algorithm. Image thresholding is a technique in which the image is binarized based on pixel intensities. The Otsu Algorithm    converts a grey scale image (input) to a binary image (output). It is a global image thresholding algorithm as a single threshold is used globally for the complete image. This    algorithm basically comprises of 4 steps:-
   Step 1. The input image is processed.
   Step 2. Image histogram is obtained by distribution of pixels.
   Step 3. Compute the threshold value T. The threshold value(T) is determined using midpoint method. 
   Step 4. Image pixels are replaced into white in those areas where the saturation is greater than the threshold value(T), and black in those areas where the saturation is lower            than the threshold value(T).
   
   A bimodal image (an image having two distinct image values) is considered, and the histogram generated contains two peaks. A generic condition would be to choose a threshold      value that lies in the middle of both the histogram peak values.
   






5. Edge based Detection
6. Region based Detection
