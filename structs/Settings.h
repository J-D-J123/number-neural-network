/**
 * Author:          Joseph Johnson 
 * File:            settings.h 
 * Des:             sets the settings of the network 
 *                  how many neurons, layers, etc... 
 */

    struct _settings {

        // set input layer neruon count 
        // 28 * 28 layer pixel images so input should be each pixel 
        int input_layer = 784; 

        // 784 input neruons 2 = 1568 per layer
        int hidden_layer = 1568; 
        int amount_of_hidden_layers = 2; // so 3136 neurons in total hidden layer

        // either number 0 - 10
        int output_layer = 10;

        // total neurons = 
        // 784 + 3136 + 10 = 3930 neurons 

    } typedef settings; 