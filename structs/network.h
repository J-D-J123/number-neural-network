/**
 * Author:          Joseph Johnson 
 * File:            network.h 
 * Des:             connects each neuron with the next layer 
 *                  also called the "Weight" of the connection used for reinforcement learning 
 */

#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>  
#include <time.h> 

#include "../structs/png.h"

typedef struct Neuron {

    float activation; 
    float bias; 

    float z; 
    float delta; 

} Neuron; 

typedef struct Layer {

    int num_neurons; 
    Neuron * neurons; 

    // matrix of weights per layer to next 
    // [0.5, 0.2, 0.1] hidden layer 1
    // [0.2, 0.4, 0.7] hidden layer 2
    // and so on...
    float ** weights; 

} Layer; 

typedef struct Network {

    int num_layers; 

    Layer * layers; 

} Network; 

// --------- FUNCTIONS ----------
Network setup_network(int * neurons_per_layer, int num_of_layers); 

// training the network...
Network train_network(Network network, png * input_pngs, int num_of_pngs);
void forward_pass(Network * network, png * image);
void backpropagation(Network * network, int label);
void update_parameters(Network * network, double learning_rate); 
double compute_loss(Network * network, int label);

// computing functions 
double compute_ReLU(double num); 
double compute_ReLU_derivative(double num);
double compute_softplus(double num); 

#endif