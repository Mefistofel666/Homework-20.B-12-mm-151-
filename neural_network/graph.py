import csv
import matplotlib.pyplot as plt

path1 = "NETWORK/network_iris.csv" 
path2 = "NETWORK/network_mnist.csv"
path3 = "KMEANS/kmeans_iris.csv"
path4 = "KMEANS/kmeans_mnist.csv"
path5 = "KNN/knn_table_iris.csv"
path6 = "KNN/knn_table_mnist.csv"
path7 = "BAYES/bayes_iris.csv"
path8 = "BAYES/bayes_mnist.csv" # тут все плохо

def read_data(path):
    header = []
    sizes = []
    times = []
    performances = []
    with open(path) as f:
        reader = csv.reader(f)
        for row in reader:
            if row[1] == 'Time':
                for item in row:
                    header.append(item)
            else:
                sizes.append(row[0])
                times.append(row[1])
                performances.append(row[2])
    sizes = [float(x) for x in sizes]
    times = [float(x) for x in times]
    performances = [float(x) for x in performances]
    return header,sizes, times, performances

def time_volume(sizes, times):
    fig = plt.figure()
    plt.title('Зависимость времени работы от объема входных данных')
    plt.ylabel('time(sec)')
    plt.xlabel('volume(number)')
    plt.grid(True)
    for i in range(len(sizes)):
        plt.scatter(sizes[i], times[i])
    plt.plot(sizes, times)
    plt.savefig("mnist_bayes_time_volume1.png") # тут надо менять куда сохранять
    plt.show()

def perf_volume(sizes, performances):
    fig = plt.figure()
    plt.title('Зависимость точности модели от объема входных данных')
    plt.ylabel('performance, %')
    plt.xlabel('volume(number)')
    plt.grid(True)
    for i in range(len(sizes)):
        plt.scatter(sizes[i], performances[i])
    plt.plot(sizes, performances)
    plt.savefig("mnist_bayes_perform_volume1.png") # тут надо менять куда сохранять
    plt.show()

header, sizes, times, performances = read_data(path8)
time_volume(sizes, times)
perf_volume(sizes, performances)

print(sizes)
print(times)
print(performances)
print(header)

