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
            network.layers[i].neurons[j].z = 0.0f; 
            network.layers[i].neurons[j].delta = 0.0f; 

            // random biase value 
            network.layers[i].neurons[j].bias = ((float) rand() / RAND_MAX) * 2.0f - 1.0f; 
        }
    }

    // count when each pair gets connected (do not do the last layer) 
    // loops through each layer aka total num of layers
    for (int i = 0; i < num_of_layers - 1; i++) {

        // get current layer & next layer
        // store pointer to the current Layer and then the next Layer after the current
        Layer * current = &network.layers[i]; 
        Layer * next = &network.layers[i + 1]; 

        current->weights = malloc(sizeof(float *) * next->num_neurons); 

        // go through every neruon in the current layer 
        // each neuron needs to connect to each neuron in the next layer
        for (int j = 0; j < next->num_neurons; j++) {

            current->weights[j] = malloc(sizeof(float) * current->num_neurons); 

            // connects with the next layer via a loop 
            // go through each neuron in the next layer
            // fully creates a "Road" where each neuron truly points to each other
            for (int k = 0; k < current->num_neurons; k++) {

                // input layer neuron connects to middle layer neuron 
                // network.connections[connection_index].previous = &current->neurons[j]; 

                // // middle layer neuron connects to input layer neuron
                // network.connections[connection_index].next = &current->neurons[k]; 

                // // initialize the weights randomly and not just 0.0f of each Connection
                // // network.connections[connection_index].weight = 0.0f; 
                // // generate weight with value from [-1.0, 1.0]
                // network.connections[connection_index].weight = ((float) rand() / RAND_MAX) * 2.0f - 1.0f; 

                // connection_index++; 

                // assign random weight from [-1.0, 1.0] inclusive
                current->weights[j][k] = ((float) rand()/ RAND_MAX) * 2.0f - 1.0f; 
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

/**
 * forward_pass(Network * network, png * iamge) takes in the network goes through each neuron 
 *  and computes the variable z and the activation function f(z) and stores it into the neuron directly
 * 
 * @param network just the old hand-dandy ENTIRE NEURAL NETWORK :) I'm tired
 * @param image is the input image inputed into the input layer neuorns
 */
void forward_pass(Network * network, png * image) {

    // each neuron (z)
    // z = SUM (inputs x weights) + bias
    // then use an activation function f(z)

    // activation is just a sum of all the neurons to the next layer aka 
    // if the sum = 0.56
    // sigmoid(0.56) = 0.636
    
    // load image into input layer 
    Layer * input = &network->layers[0];

    // input PNG pixels into the input layer
    for (int i = 0; i < input->num_neurons; i++) {

        // neuron activation = pixels array 
        input->neurons[i].activation = image->pixels[i].grey / 255.0f;  
    }

    // now go through all calcuations for each layer including the input layer
    for (int j = 0; j < network->num_layers - 1; j++) {

        Layer * current = &network->layers[j]; 
        Layer * next = &network->layers[j + 1]; 

        // cacluate the z value = SUM (inputs x weights) + bias
        for (int k = 0; k < next->num_neurons; k++) {

            float z = next->neurons[k].bias; 

            // loop through the current layer 
            for(int h = 0; h < current->num_neurons; h++) {

                // SUM (inputs x weights) + bias (aka z)
                z += (current->neurons[h].activation * current->weights[k][h]); 
            }

            // ReLU() function call & save z to k.z so it is not 0
            next->neurons[k].z = z; 
            next->neurons[k].activation = compute_ReLU(next->neurons[k].z); 
        }
    }
}

/**
 * backpropagation(Network * network, int label) computes the delta for every neuron in the network. 
 *  delta stands for the amount of error. This algorithm starts backward from the output layer and then 
 *  goes through the hidden layers. 
 * 
 * @param network is the neural network inputed and computed. After a forward pass the activation functions 
 *                      and z values are stored in each neuron 
 * @param label is the correct digit for the image [0.9] inclusive. Represents the output neuron and the correct number to be activated. 
 *                      aka which neuron on the output layer.
 */
void backpropagation(Network * network, int label) {

    // index of output layer 
    // annoying index error since the setup_network takes the actual amount of 
    //  number of layers (Ex. 4 = 4 layers) you need to subtract 1 to 
    //  correctly index the layers backwards
    int num_layers = network->num_layers; 
    int output_layer_index = network->num_layers - 1;

    // loop over every neuron in the output layer
    int num_of_neurons = network->layers[output_layer_index].num_neurons;

    for (int i = 0; i < num_of_neurons; i++) {

        // figure out the "target" value
        // Ex. if 1.0 if i == label else 0.0 
        double target; 

        //  One Hot Encoding in Backpropagation where 1 value is the answer 
        //  since all answers are from [1, 10] inclusive it is easier to have the "One Hot" approach
        if (i == label) {

            target = 1.0; 

        } else {

            target = 0.0; 
        }

        // caculate delta, which is the difference between the expected value vs the guessed value via the network 
        network->layers[output_layer_index].neurons[i].delta = network->layers[output_layer_index].neurons[i].activation - target; 
    }

    for (int n = num_layers - 2; n > 0; n--) { // n is which layer 

        // get a pointer to current layer i and then the next layer 
        Layer * current_layer = &network->layers[n]; 
        Layer * next_layer = &network->layers[n + 1]; // next layer

        // now loop over every neuron in the current layer 
        for (int current_neuron = 0; current_neuron < current_layer->num_neurons; current_neuron++) { 

            // fresh sum value for each neuron caculation
            double sum = 0.0; 

            // loop through each neuron in the next layer
            for (int next_neuron = 0; next_neuron < next_layer->num_neurons; next_neuron++) {

                // sum every neuron k in the next layer
                sum += next_layer->neurons[next_neuron].delta * current_layer->weights[next_neuron][current_neuron]; 
            }

            // now multiply the sum by compute_ReLU_derivative & store result in current layer neuron delta
            current_layer->neurons[current_neuron].delta = sum * compute_ReLU_derivative(current_layer->neurons[current_neuron].z); 
        }
    }
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

    // 1 for num greater than 0 and 0 when num is less than 0
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