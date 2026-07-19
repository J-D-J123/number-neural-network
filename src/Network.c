/**
 * Author:          Joseph Johnson 
 * File:            Network.c 
 * Des:             sets up the network with the defined constraints. 
 *                  this is going to be long...
 */

#include "../structs/network.h"

// example for per layer neuron count
// [784] [256] [128] [10] 
/**
 * Function setup_network(int * neurons_per_layer, int num_of_layers) 
 * sets up a neural network based on it's prams 
 * 
 * @param neurons_per_layer is an integer array that represents numbers of the total number of neurons per layer 
 * @param num_of_layers is an integer that represents the total number of layers
 * @returns a Network struct fully setup from input -> hidden -> output via connections
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

                // initialize the weights randomly and not just 0.0f of each Connection
                // network.connections[connection_index].weight = 0.0f; 
                // generate weight with value from [-1.0, 1.0]
                network.connections[connection_index].weight = ((float) rand() / RAND_MAX) * 2.0f - 1.0f; 

                connection_index++; 
            }
        }
    }

    return network; 
}

/**
 * this forward_backpropagation_algorithm(...) is the method for the network to learn 
 * 
 * @param network is the set up connected network from the function setup_network(...)
 * @param input_pngs is an array of input images used to train the network for multiple images 
 * @returns network which is the modified network after the new "training"
 */
Network train_network(Network network, png * input_pngs, int num_of_pngs) { 

    // Learning alorithm... TODO; 
    /**
     *  Forward pass, compute activations layer by layer by adjusting the biases
     * 
     *  Loss compare the 10 outputs aka what number it is to the true number value, look into
     *          softmax on the output layer + cross-entropy loss (whatever that is)
     * 
     *  Backpropagation compute how much each weight/bias contributed to the error aka the gradient
     * 
     *  Gradient descent - stochastic gradient descent (SGD) in mini batches
     *  Adam is a fancier optimizer i can add later. nudge every weight/bias in the direction that reduces loss. 
     */

}

void forward_pass(Network * network, png * image) {

    // each neuron (z)
    // z = SUM (inputs x weights) + bias
    // then use an activation function f(z)

    // activation is just a sum of all the neurons to the next layer aka 
    // if the sum = 0.56
    // sigmoid(0.56) = 0.636



}

void backpropagation(Network * network, int label) {


}

void update_parameters(Network * network, double learning_rate) {


}

double compute_loss(Network * network, int label) {


}


/**
 * compute_ReLU(double num) applies the ReLU activation function 
 * https://en.wikipedia.org/wiki/Rectified_linear_unit
 * 
 * ReLU(x) = max(0, x) 
 * 
 * @param num is the x variable value input into the equasion 
 */
double compute_ReLU(double num) {

    if (num > 0) {

        return num; 
    }

    return 0.0; 
}

/**
 * compute_ReLU(double num) applies the ReLU activation function for backpropagation 
 * https://en.wikipedia.org/wiki/Rectified_linear_unit
 * 
 * ReLU(x) = max(0, x) {1, x > 0} {0, x <= 0}
 * 
 * @param num is the x variable value input into the equasion 
 */
double compute_ReLU_derivative(double num) {

    if (num > 0) {

        return 1.0; 
    }

    return 0.0; 
}


/**
 * compute_softplus(double num) applies the softplus activaton function 
 * Softplus is a smooth approximation of ReLU 
 * 
 * softplus(x) = log(1 + exp(x))
 * 
 * @param num is the value estimated 
 * @returns a double value of estimated value
 */
double compute_softplus(double num) {

    return log(1 + exp(num)); 
}

// /**
//  * // commeted out because i guess it is not useful and sort of outdated :( used ReLu instead
//  * compute_sigmoid(double num) returns the value of the func 
//  *
//  * @param num 
//  * @returns double
//  */
// double compute_sigmoid(double num) {

//     return (1.0 / (1.0 + exp(-num)));
// }