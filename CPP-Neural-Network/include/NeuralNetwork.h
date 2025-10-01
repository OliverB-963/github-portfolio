#pragma once

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Layer.h"
#include <vector>
#include <string>

class NeuralNetwork {
	std::vector<Layer> layers;
	size_t size;
	double learningRate;

public:
	NeuralNetwork(std::vector<int> shape, double learningRate);

	void train(const std::vector<std::vector<double>>& data, const std::vector<int>& expectedOutputs, int batchSize, double trainingSplit);

	std::vector<Layer>& getLayers();

	void setLayerValues(const std::string &filePath);

private:
	std::vector<double> calculateOutputs(std::vector<double> inputs) const;

	std::vector<std::vector<double>> classify(const std::vector<std::vector<double>> &inputs) const;

	double loss(const std::vector<std::vector<double>>& trainingData, const std::vector<int>& expectedOutputs) const;

	double cost(const std::vector<std::vector<double> > &trainingData, const std::vector<int> &expectedOutputs) const;

	void learn(const std::vector<std::vector<double>>& trainingData, const std::vector<int> &expectedOutputs);

	void threadExample(bool& stopped);
};

#endif // !NEURALNETWORK_H
