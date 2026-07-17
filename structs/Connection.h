/**
 * Author:          Joseph Johnson 
 * File:            connection.h 
 * Des:             connects each neuron with the next layer 
 *                  also called the "Weight" of the connection used for reinforcement learning 
 */

struct _connection {

    // weight is a value between 0 to 1 
    float weight; 

    struct Neuron* previous_neuron; 
    struct Neuron* next_neuron; 

} typedef connection; 