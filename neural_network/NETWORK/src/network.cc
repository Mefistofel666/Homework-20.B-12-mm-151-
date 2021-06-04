#include "network.h"
#include "layer.h"
#include "data_handler.h"
#include <numeric> // double MAX
#include <algorithm> // sqrt

//  Конструктор:
// Инициализируются слои заданных размеров
Network::Network(std::vector<int> neuronsAtLayer, int inputSize, int numClasses, double learningRate)
{
    for(int i = 0; i < neuronsAtLayer.size(); i++)
    {
        if(i == 0)
            layers.push_back(new Layer(inputSize, neuronsAtLayer.at(i))); // инициализация входного слоя
        else 
            layers.push_back(new Layer(layers.at(i-1)->neurons.size(), neuronsAtLayer.at(i))); // инициализация скрытых слоев
    }
    layers.push_back(new Layer(layers.at(layers.size()-1)->neurons.size(),numClasses)); // инициализация выходного слоя
    this->learningRate = learningRate;
}

// Надо пофиксить
Network::~Network(){}

//  просто линейная часть преобразования
double Network::activate(std::vector<double> weights, std::vector<double> input)
{
    double activation = weights.back(); // bias = смещение
    // скалярное произведение вектора весов и входного вектора
    for(int i = 0; i < weights.size() - 1; i++)
    {
        activation += weights[i] * input[i]; 
    }
    return activation;
}

// выходное значение (сигмоидного) нейрона (нелинейное преобразование в отрезок [0; 1])
// можно реализовать ReLu(простая производная), tanh(преобразование в [-1, 1]) и проч.
double Network::transfer(double activation)
{
    return 1.0 / (1.0 + exp(-activation)); // sigmoid
}

// производная сигмоды f'(x) =  f(x)(1-f(x)), где f(x) = 1/(1+exp(-x))
// соответственно для других функций активации будет другая производная
double Network::transferDerivative(double output)
{
    return output * (1 - output); 
}

// прямое распространение - forward propogation
std::vector<double> Network::fprop(Data *data)
{
    std::vector<double> inputs = *data->getNormalizedFeatureVector();
    for(int i = 0; i < layers.size(); i++) // проходим по всем слоям
    {
        Layer *layer = layers.at(i); // взяли i-тый слой
        std::vector<double> newInputs;
        for(Neuron *n : layer->neurons) // проходим по каждому нейрону в i-ом слое
        {
            double activation = this->activate(n->weights, inputs); // скалярное произведение вектора весов и входа в нейрон
            n->output = this->transfer(activation); // выход нейрона
            newInputs.push_back(n->output); // выход слоя (вектор выходов каждого нейрона в слое)
        }
        inputs = newInputs;
    }
    return inputs; // выход с последнего слоя
}
// метод обратного распространения ошибки
void Network::bprop(Data *data)
{
    for(int i = layers.size()-1; i >= 0; i--) // начинаем с последнего слоя
    {
        Layer *layer = layers.at(i); 
        std::vector<double> errors;
        if(i != layers.size()-1)
        {
            for(int j = 0; j < layer->neurons.size(); j++)
            {
                double error = 0.0;
                for(Neuron *n : layers.at(i+1)->neurons) // проходим по всем нейронам слоя
                {
                    // дифференцирование сложной функции
                    error += (n->weights.at(j) * n->delta);
                }
                errors.push_back(error);
            }
        }else // если слой последний
        {
            for(int j = 0; j < layer->neurons.size(); j++)
            {
                Neuron *n = layer->neurons.at(j); // проходим по всем нейронам слоя
                // другими словами это вектор предсказанных значений минус вектор ожидаемых знвчений = вектор ошибок
                errors.push_back((double) data->getClassVector().at(j) - n->output); // ожидаемый класс - актуальный
            }
        }
        for(int j = 0; j < layer->neurons.size(); j++)
        {
            Neuron *n = layer->neurons.at(j);
            // delta_j = (o_j - t_j) * o_j*(1 - o_j) ,  где o_j - выход j-го нейрона, errors.at(j) = (o_j - t_j)
            // для последнего слоя
            n->delta = errors.at(j) * this->transferDerivative(n->output); // gradient / dericative part of backprop
        }
    }
}   

// обновление весов сети
void Network::updateWeights(Data *data)
{
    std::vector<double> inputs = *data->getNormalizedFeatureVector();
    for(int i = 0; i < layers.size();i++)
    {
        if(i!=0)
        {
            for(Neuron *n : layers.at(i-1)->neurons)
            {
                inputs.push_back(n->output);
            }
        }
        for(Neuron *n : layers.at(i)->neurons)
        {
            for(int j = 0; j < inputs.size(); j++)
            {
                n->weights.at(j) += this->learningRate * n->delta * inputs.at(j);
            }
            n->weights.back() += this->learningRate * n->delta;
        }
        inputs.clear();
    }
}

int Network::predict(Data *data)
{
    std::vector<double> outputs = fprop(data);
    // расстояние от начала до максимального элемента
    return std::distance( outputs.begin(), std::max_element(outputs.begin(), outputs.end()) ); 
}

// тренировка нейросети
void Network::train(int numEpochs)
{
    for(int i = 0; i < numEpochs; i++)
    {
        double sumError = 0.0;
        for(Data *data : *this->trainingData)
        {
            std::vector<double> outputs = fprop(data); // текущий выход нейросети после прямого распространения
            std::vector<int> expected = data->getClassVector(); // выход который хотим получить (вектор из нулей и одной единицы)
            double tempErrorSum =  0.0;
            for(int j = 0; j < outputs.size(); j++)
            {
                tempErrorSum += pow((double)expected.at(j) - outputs.at(j), 2); // прибавляем квадрат ошибки

            }
            sumError += tempErrorSum; // общая ошибка на всех тренировочных данных
            bprop(data); // распространяем сигнал в обратную сторону
            updateWeights(data);// корректируем веса

        } 
        printf("Iteration: %d \t Error=%.4f\n", i, sumError);
    }
}

// Оценка точности нейросети на тестовой выборке
double Network::test()
{
    double numCorrect = 0.0;
    double count = 0.0;
    for(Data *data : *this->testData)
    {
        count++;
        int index = predict(data);
        if(data->getClassVector().at(index) == 1) numCorrect++;
    }
    testPerformance = (numCorrect/count);
    return testPerformance;
}

// Тоже самое что и test только можем наблюдать как изменяется точность предсказания(насколько быстро, например)
void Network::validate()
{
    double numCorrect = 0.0;
    double count = 0.0;
    for(Data *data : *this->validationData)
    {
        count++;
        int index = predict(data);
        if(data->getClassVector().at(index) == 1) numCorrect++;
    }
   printf("Validation Performance: %.4f\n", numCorrect / count);
}


int main()
{
    // инициализируем обработчик данных
    DataHandler *dataHandler = new DataHandler();
#ifdef MNIST // если хотим работать с MNIST датасетом, то определяем в Makefile -DMNIST
    dataHandler->readInputData("../train-images-idx3-ubyte"); // читаем картинки
    dataHandler->readLabelData("../train-labels-idx1-ubyte"); // читаем классы картинок
    dataHandler->countClasses(); // подсчитываем количество классов(пригодится для передачи как параметр нейросети)
#else 
    dataHandler->readCsv("...iris.data", ","); // если MNIST не был определен, то работает с набором данных ирисов Фишера
#endif
    dataHandler->splitData(); // разбиваем данные (тут хорошо бы как параметры принимать процентики)
    // задаем архитектуру сети (каждое значение этого вектора определяет количество нейронов в i-ом слое)
    std::vector<int> hiddenLayers = {15}; 
    // передаем параметры в сеть, обучаем ее и выводим результат
    Network *net = new Network(
        hiddenLayers, 
        dataHandler->getTrainingData()->at(0)->getNormalizedFeatureVector()->size(), 
        dataHandler->getClassCounts(),
        0.3);
    net->setTrainingData(dataHandler->getTrainingData());
    net->setTestData(dataHandler->getTestData());
    net->setValidationData(dataHandler->getValidationData());
    net->train(15); // 15 эпох обучения
    net->validate();
    printf("Test Performance: %.3f\n", net->test());

 // the best parameters: hiddenLayers = 15; learningRate = 0.3; epochs = 15;
 // по-хорошему надо скрытый слой делать из 100+ нейронов, но компуктеру больно тяжко
}