/**
 * Author:          Joseph Johnson 
 * File:            connection.h 
 * Des:             connects each neuron with the next layer 
 *                  also called the "Weight" of the connection used for reinforcement learning 
 */

#ifndef NETWORK_H
#define NETWORK_H

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

#endif