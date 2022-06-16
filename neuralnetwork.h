
#include "matrix_evaluation.h"
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;


    //simple activation function
    inline float Sigmoid(float x)
    {
        return 1.0f / (1 + exp(-x));
    }

    //derivative of activation function
    // x = sigmoid(input);
    inline float DSigmoid(float x)
    {
        return (x * (1 - x));
    }

    // calss representing a simple densely connected neural network
    // i.e. every neuron  is connected to every neuron of next layer
    class SimpleNeuralNetwork
    {
        public:
        vector<uint32_t> _topology;
        vector<Matrix2D> _weightMatrices;
        vector<Matrix2D> _valueMatrices;
        vector<Matrix2D> _biasMatrices; 
            float _learningRate;
        public:
            
            // topology defines the no.of neurons for each layer
            // learning rate defines how much modification should be done in each backwords propagation i.e. training
            SimpleNeuralNetwork(vector<uint32_t> topology,float learningRate = 0.1f)
                :_topology(topology),
                _weightMatrices({}),
                _valueMatrices({}),
                _biasMatrices({}),
                _learningRate(learningRate)
            {
                // initializing weight and bias matrices with random weights , weight matrices ka size is one less than the size of topology
                for(uint32_t i = 0; i < topology.size() - 1; i++)           
                {
                    Matrix2D weightMatrix(topology[i + 1], topology[i]); 
                    weightMatrix = weightMatrix.applyFunction([](const float &f){
                        return (float)rand() / RAND_MAX;
                    });
                    _weightMatrices.push_back(weightMatrix);
                    
                    Matrix2D biasMatrix(topology[i + 1], 1);
                    biasMatrix = biasMatrix.applyFunction([](const float &f){
                        return (float)rand() / RAND_MAX;
                    });
                    _biasMatrices.push_back(biasMatrix);
   
                }
                _valueMatrices.resize(topology.size());
            }

            // function to generate output from given input vector
            bool feedForword(vector<float> input) 
            {
                if(input.size() != _topology[0])
                    return false;
                // creating input matrix 
                Matrix2D values(input.size(), 1);
                for(uint32_t i = 0; i < input.size(); i++)
                    values._vals[i] = input[i]; 
                
                //forwording inputs to next layers
                for(uint32_t i = 0; i < _weightMatrices.size(); i++)  // 0 1 2 
                {
                    // y = activationFunc( x1 * w1 + x2 * w2 + ... + b)   //weight value input  
                    _valueMatrices[i] = values;
                    values = values.multiply(_weightMatrices[i]);  
                    values = values.add(_biasMatrices[i]);
                    values = values.applyFunction(Sigmoid);
                }
                _valueMatrices[_weightMatrices.size()] = values;
                return true;
            }


            // function to train with given output vector
            bool backPropagate(std::vector<float> targetOutput)
            {
                if(targetOutput.size() != _topology.back()) // jo output we are expecting uska size topology vector ke last element ke equal hona chaiye becoz last element hi ouput layer hai 
                    return false;

                // determine the simple error
                // error = target - output
                Matrix2D errors(targetOutput.size(), 1);
                errors._vals = targetOutput;
                Matrix2D sub=_valueMatrices.back().negetive();
                errors = errors.add(sub);
                

                // back propagating the error from output layer to input layer
                // and adjusting weights of weight matrices and bias matrics
                for(int i = _weightMatrices.size() - 1; i >= 0; i--)
                {
                    
                    //calculating errrors for previous layer
                    Matrix2D trans=_weightMatrices[i].transpose();
                    Matrix2D prevErrors = errors.multiply(trans);

                    //calculating gradient i.e. delta weight (dw)
                    //dw = lr * error * d/dx(activated value)
                    Matrix2D dOutputs = _valueMatrices[i + 1].applyFunction(DSigmoid);
                    Matrix2D gradients = errors.multiplyElements(dOutputs);
                    gradients = gradients.multiplyScaler(_learningRate);
                    Matrix2D weightGradients = _valueMatrices[i].transpose().multiply(gradients);
                    
                    //adjusting bias and weight
                    _biasMatrices[i] = _biasMatrices[i].add(gradients);
                    _weightMatrices[i] = _weightMatrices[i].add(weightGradients);
                    errors = prevErrors;
                }
                
                return true;
            }
            
            // function to retrive final output
            vector<float> getPredictions()
            {
                return _valueMatrices.back()._vals;
            }

    }; // class SimpleNeuralNetwork


