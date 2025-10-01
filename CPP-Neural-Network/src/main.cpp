#include <iostream>

#include "NeuralNetwork.h"
#include "CsvReader.h"

#include <vector>

using std::vector;

#include "DataStorage.h"

int main() {
	constexpr int BATCH_SIZE = 50;
	constexpr double TRAINING_SPLIT = 0.8;

	auto bob = NeuralNetwork({ 2, 3, 2 }, 0.00001);

	auto fileInfo = CsvReader("../data/test1.csv");

	const vector<vector<double>> data = fileInfo.getData();
	const vector<int> labels = fileInfo.getLabels();
	// DataStorage::retrieveData(bob, "delete");

	bob.train(data, labels, BATCH_SIZE, TRAINING_SPLIT);
	// DataStorage::saveData(bob, "");

	return 0;
}