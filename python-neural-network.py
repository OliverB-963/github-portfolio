import time
import math
import random

import numpy as np
import pygame

import datapoint_reader

class Layer:
    def __init__(self, input_n, output_n):
        self.nodes_in = input_n
        self.nodes_out = output_n

        self.initialise_weights_normalised()
        self.biases = np.zeros((output_n))

        self.loss_gradient_w = np.empty((output_n, input_n))
        self.loss_gradient_b = np.empty((output_n))

    def initialise_weights_normalised(self):
        self.weights = np.random.randn(self.nodes_out, self.nodes_in)

    def initialise_weights_sebway(self):
        # way that is supposed to be better for sigmoid activation
        self.weights = np.random.rand(self.nodes_out, self.nodes_in) * 2 - 1
        self.weights /=  math.sqrt(self.nodes_in)

    def calculate_layer_output(self, inputs, func):
        weighted_inputs = np.empty(self.nodes_out)
        for i in range(self.nodes_out):
            weighted_inputs[i] = np.dot(inputs, self.weights[i]) + self.biases[i]
        # print(self.sigmoid_derivative(weighted_inputs, func))
        # raise Exception
        return func(weighted_inputs)
    
    def apply_gradients(self, L):
        self.weights = np.subtract(self.weights, self.loss_gradient_w * L)
        self.biases = np.subtract(self.biases, self.loss_gradient_b * L)

    @staticmethod
    def node_cost(activation, expected):
        return (activation - expected) ** 2
    
    def sigmoid_derivative(self, inputs, func):
        activated_inputs = func(inputs)
        return activated_inputs * (1 - activated_inputs)
    
    def softmax_derivative(self, inputs, func):
        input_size = inputs.size
        # creates matrix where each column represents the 
        # gradient for the softmax value of each input
        grad_array = np.empty((input_size, input_size))

        # calculates grad matrix
        softmax_values = func(inputs)
        for i in range(input_size):
            for j in range(input_size):
                if i == j:
                    grad_array[i][j] = softmax_values[i] * (1 - softmax_values[j])
                else:
                    grad_array[i][j] = -1 * softmax_values[i] * softmax_values[j]

        # calculate the total gradient for each input value
        grad_sums = np.sum(grad_array, axis=0)


class NeuralNetwork:
    def __init__(self, shape, learn_rate):
        self.layers = []
        self.size = len(shape) - 1
        self.learn_rate = learn_rate

        for i in range(self.size):
            self.layers.append(Layer(shape[i], shape[i + 1]))

    def calculate_outputs(self, inputs):
        '''Runs the input values through the network to calculate the output values'''

        for i in range(self.size - 1):
            inputs = self.layers[i].calculate_layer_output(inputs, self.sigmoid)
        inputs = self.layers[self.size - 1].calculate_layer_output(inputs, self.softmax)
        
        return inputs
    
    def classify(self, inputs):
        '''calculates the output for each input'''

        output_values = np.empty((inputs.shape[0], 2))
        for i in range(inputs.shape[0]):
            output_values[i] = self.calculate_outputs(inputs[i])

        print(output_values)
        return output_values
    
    def loss(self, training_data, expected):
        predicts = self.classify(training_data)
        pred_clipped = np.clip(predicts, 1e-7, 1-1e-7)

        losses = -np.log(pred_clipped[range(predicts.shape[0]), expected-1])
        print(predicts.shape[0], expected)
        mean_loss = np.mean(losses)
        return mean_loss

    # def loss(self, training_data, expected):
    #     predicts = self.classify(training_data)
    #     expected_copy = expected - 1
    #     total_cost = 0
    #     output_layer = self.layers[-1]
    #     for i in range(expected.shape[0]):
    #         total_cost += output_layer.node_cost(predicts[i, 0], expected_copy[i])
    #         total_cost += output_layer.node_cost(predicts[i, 1], expected_copy[i])
        
        # return total_cost / training_data.shape[0] print

    def cost(self, predicts, expected):
        predicts = np.argmax(predicts, 1)
        total_correct = np.sum(np.equal(predicts + 1, expected))

        return total_correct
    
    def apply_all_gradients(self):
        for layer in self.layers:
            layer.apply_gradients(self.learn_rate)
            # print(layer.weights)
            # print(layer.biases)

    def learn(self, training_data, expected):
        H = 0.0001
        original_cost = self.loss(training_data, expected)

        for layer in self.layers:

            for node_in in range(layer.nodes_in):
                for node_out in range(layer.nodes_out):

                    layer.weights[node_out, node_in] += H
                    delta_cost = self.loss(training_data, expected) - original_cost
                    layer.weights[node_out, node_in] -= H
                    layer.loss_gradient_w[node_out, node_in] = delta_cost / H
            
            for bias_index in range(layer.biases.size):

                layer.biases[bias_index] += H
                delta_cost = self.loss(training_data, expected) - original_cost
                layer.biases[bias_index] -= H
                layer.loss_gradient_b[bias_index] = delta_cost / H

        self.apply_all_gradients()
        return original_cost

    def train(self, training_data, expected, runs):
        fuckoff = []
        for y in range(187):
            for x in range(187):
                fuckoff.append([x, y]) 
        array = np.array(fuckoff)
        
        running = True
        draw_display()
        i = 1
        while running:

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
            pygame.event.pump()
            self.learn(training_data, expected)
            
            if i % 1 == 0:
                print(self)
                print(i/100)
                x = self.classify(array)
                choices = np.argmax(x, 1)
                draw_points1(choices)
                draw_points2(training_data, expected)
                time.sleep(5)
            i += 1

            pygame.display.flip()

        pygame.quit()


    @staticmethod
    def sigmoid(inputs):
        '''returns a np array of same size where each value is inputed to a Sigmoid function'''
    
        return 1 / (1 + np.power(np.e, -inputs))
    
    def sigmoid_derivative(self, inputs):
        activated_inputs = self.sigmoid(inputs)
        return activated_inputs * (1 - activated_inputs)
        
    
    @staticmethod
    def softmax(inputs):
        '''returns a np array of same size where each value is inputed to a Softmax function'''

        exp_values = np.exp(inputs)
        norm_base = np.sum(exp_values)
        norm_values = exp_values / norm_base

        return norm_values


def main():
    data = datapoint_reader.DataSet().get_data(filename='test1.csv')

    values = data[0]
    labels = data[1]
    
    n = NeuralNetwork((2, 3, 2), 0.1)
    n.train(values, labels, 1000)
    
def draw_display():
    screen.fill(BLACK)
    pygame.draw.rect(screen, GREY, (0, 0, D_WIDTH, D_HEIGHT), MARGIN)
    pygame.draw.rect(screen, WHITE, (MARGIN, MARGIN, AXIS_WIDTH, D_HEIGHT - MARGIN*2))
    pygame.draw.rect(screen, WHITE, (MARGIN, D_HEIGHT-MARGIN, D_WIDTH - MARGIN*2, AXIS_WIDTH))

def draw_points1(array):
    for y in range(187):
        for x in range(187):
            if array[x + 187*y] == 1:
                colour = (0, 0, 100)
            else:
                colour = (100, 0, 0)
            pygame.draw.rect(screen, colour, (MARGIN+AXIS_WIDTH+POINT_SIZE*x, D_HEIGHT-MARGIN-AXIS_WIDTH-POINT_SIZE*y-POINT_SIZE/2, POINT_SIZE, POINT_SIZE))

def draw_points2(training, expected):
    i = 0
    for x, y in training:
        if expected[i] == 1:
            colour = BLUE
        else:
            colour = RED
        pygame.draw.rect(screen, colour, (MARGIN+AXIS_WIDTH+POINT_SIZE*x, D_HEIGHT-MARGIN-AXIS_WIDTH-POINT_SIZE*y-POINT_SIZE/2, POINT_SIZE, POINT_SIZE))
        i += 1


if __name__ == '__main__':
    D_WIDTH = 800
    D_HEIGHT = 800
    MARGIN = 25
    AXIS_WIDTH = 2
    POINT_SIZE = 4

    # Colours
    BLACK = (0, 0, 0)
    WHITE = (255, 255, 255)
    BLUE = (0, 0, 255)
    RED = (255, 0, 0)
    GREY = (25, 25, 25)

    # multiplier vars
    SPREAD = 10
    MULTIPLIER = 5

    pygame.init()
    screen = pygame.display.set_mode((D_WIDTH, D_HEIGHT)) #(448, 448) = 16x16 pixel ratio
    pygame.display.set_caption("Data Creator")
    main()
        