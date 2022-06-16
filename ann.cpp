#include <iostream>
#include "neuralnetwork.h"
#include <vector>
using namespace std;


int main()
{
    // creating neural network
    // 2 input neurons, 3 hidden neurons and 1 output neuron 
    vector<uint32_t> topology = {2,3,1};
    SimpleNeuralNetwork nn(topology, 0.1);
    
    //sample dataset
    vector<vector<float>> targetInputs = {  
        {0.0f, 0.0f},  
        {1.0f, 1.0f},
        {1.0f, 0.0f},
        {0.0f, 1.0f}
    }; 
    vector<vector<float>> targetOutputs = {
        {0.0f},
        {1.0f},
        {0.0f},
        {0.0f}
    };

    uint32_t iterations = 100000;
    
    //training the neural network with randomized data
    cout << "training started \n";

    for(uint32_t i = 0; i < iterations; i++)
    {   // 0 1 2 3 
        uint32_t index = rand() % 4;
        nn.feedForword(targetInputs[index]);
        nn.backPropagate(targetOutputs[index]);
    }

    cout << "training complete\n";


    //testing the neural network
   for(vector<float> input : targetInputs) //
    {
        nn.feedForword(input);
        vector<float> preds = nn.getPredictions();
        cout << input[0] << "," << input[1] <<" => " << preds[0] <<endl;   //  input=(0.0,0.0)  //  input=(1.1,1.1)

    }

    return 0;
}