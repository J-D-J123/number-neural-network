/**
 * Author:          Joseph Johnson 
 * File:            connection.h 
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

} Neuron; 

typedef struct Layer {

    int num_neurons; 
    Neuron * neurons; 

} Layer; 

typedef struct Connection {

    float weight; 

    Neuron * previous; 
    Neuron * next;   

} Connection; 

typedef struct Network {

    int num_layers; 
    Layer * layers; 
    Connection * connections; 

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