# Handwritten-Digit-Classifier
Bult a neural network from scratch in C to classify handwritten digits (MNIST), without ML frameworks. 

## Why? 
A lot of code is written by AI and plenty of people and even students can not explain what the AI wrote or how their program works. For that exact reason, that is why I decided to learn the foundations of neural networks (NN) by myself with little to zero use of AI. I

This project has brought together what I have learned in class from writing comments that explain each line to structs, to pointers that point to the next layer in the network. It is hard knowing that every little function I am writing like the ReLU function is just a easy python library waiting to be called.  

This project is using the MNIST dataset to develop and train a neural network with little to no help from any AI model/ agent. This is to help teach the foundations of neural networks in a challenging language aka C. 

## How it Works
Each PNG image is a 28 * 28 image transformed to a greyscale pixel array with 784 total pixels per PNG. 

Input layer has 784 neurons (per pixel)
Middle has two seperate layers first one is 256 -> 128 
Output is 10 (digits 1, 10)

![Alternative text for accessibility](https://github.com/J-D-J123/number-neural-network/blob/main/greyscale_0-255.JPG)
