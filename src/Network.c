/**
 * Author:          Joseph Johnson 
 * File:            Network.c 
 * Des:             sets up the network with the defined constraints. 
 *                  this is going to be long...
 */

#include "../structs/network.h"


// [784] [256] [128] [10] 
/**
 * Function setup_network(int * neurons_per_layer, int num_of_layers) 
 * sets up a neural network based on it's prams 
 * @param neurons_per_layer is an integer array that represents numbers of the total number of neurons per layer 
 * @param num_of_layers is an integer that represents the total number of layers
 * @returns a Network struct 
 */
Network setup_network(int * neurons_per_layer, int num_of_layers) {

    Network network; 
    network.num_layers = num_of_layers; 

    // malloc space for each seperate layer 
    network.layers = malloc(sizeof(Layer) * num_of_layers); 

    // first go through neurons_per_layer array and [0] = input layer, [1] = middle layer ... last element is output layer
    for (int i = 0; i < num_of_layers; i++) {

        // set size of neurons per layer for input - middle - output
        network.layers[i].num_neurons = neurons_per_layer[i]; 

        // now to malloc neurons for each layer
        network.layers[i].neurons = malloc(sizeof(Neuron) * neurons_per_layer[i]);

        // initialize the neurons 
        for (int j = 0; j < neurons_per_layer[i]; j++) {

            // set them all to 0; 
            network.layers[i].neurons[j].activation = 0.0f; 
            network.layers[i].neurons[j].bias = 0.0f; 
        }
    }

    // create the connections now from each neuron
    int connection_index = 0; 

    // count when each pair gets connected (do not do the last layer) 
    // loops through each layer aka total num of layers
    for (int i = 0; i < num_of_layers - 1; i++) {

        // get current layer & next layer
        // store pointer to the current Layer and then the next Layer after the current
        Layer * current = &network.layers[i]; 
        Layer * next = &network.layers[i + 1]; 

        // go through every neruon in the current layer 
        // each neuron needs to connect to each neuron in the next layer
        for (int j = 0; j < current->num_neurons; j++) {

            // connects with the next layer via a loop 
            // go through each neuron in the next layer
            // fully creates a "Road" where each neuron truly points to each other
            for (int k = 0; k < next->num_neurons; k++) {

                // input layer neuron connects to middle layer neuron 
                network.connections[connection_index].previous = &current->neurons[j]; 

                // middle layer neuron connects to input layer neuron
                network.connections[connection_index].next = &current->neurons[k]; 

                // initialize the weights of each Connection
                network.connections[connection_index].weight = 0.0f; 

                connection_index++; 
            }
        }
    }

    return network; 
}