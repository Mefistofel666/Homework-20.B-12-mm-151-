import matplotlib.pyplot as plt
import csv

path1 = "NETWORK/network_iris.csv" 
path2 = "NETWORK/network_mnist.csv"
path3 = "KMEANS/kmeans_iris.csv"
path4 = "KMEANS/kmeans_mnist.csv"
path5 = "KNN/knn_table_iris.csv"
path6 = "KNN/knn_table_mnist.csv"
path7 = "BAYES/bayes_iris.csv"
path8 = "BAYES/bayes_mnist.csv" # тут все плохо


def paint(names, values, text, path):
    fig = plt.figure()
    plt.grid(True)
    plt.bar(names, values)
    plt.title(text)
    plt.savefig(path) 
    plt.show()


def read_data(path):
    performances = []
    times = []
    sizes = []
    with open(path) as f:
        reader = csv.reader(f)
        for row in reader:
            if row[1] == 'Time':
                continue
            else:
                times.append(row[1])
                performances.append(row[2])
                sizes.append(row[0])

    sizes = [float(x) for x in sizes]
    performances = [float(x) for x in performances]
    times = [float(x) for x in times]
    return sizes, performances, times

# performances for all models
network_iris = []
network_mnist = []
kmeans_iris = []
kmeans_mnist = []
knn_iris = []
knn_mnist = []
bayes_iris = []
bayes_mnist = []
sizes = []

network_iris_time = []
network_mnist_time = []
kmeans_iris_time = []
kmeans_mnist_time = []
knn_iris_time = []
knn_mnist_time = []
bayes_iris_time = []
bayes_mnist_time = []



sizes, network_iris, network_iris_time = read_data(path1)
sizes, network_mnist, network_mnist_time = read_data(path2)
sizes, kmeans_iris, kmeans_iris_time = read_data(path3)
sizes, kmeans_mnist, kmeans_mnist_time = read_data(path4)
sizes, knn_iris, knn_iris_time = read_data(path5)
sizes, knn_mnist, knn_mnist_time = read_data(path6)
sizes, bayes_iris, bayes_iris_time = read_data(path7)
sizes, bayes_mnist, bayes_mnist_time = read_data(path8)

network_iris = [x*100 for x in network_iris]
network_mnist = [x*100 for x in network_mnist]


names = ["NETWORK", "KMEANS", "KNN", "BAYES"]

# точности при разных объемах входных данных
values_iris1 = [item[0] for item in [network_iris, kmeans_iris, knn_iris, bayes_iris] ]
values_iris2 = [item[1] for item in [network_iris, kmeans_iris, knn_iris, bayes_iris] ]
values_iris3 = [item[2] for item in [network_iris, kmeans_iris, knn_iris, bayes_iris] ]
values_iris4 = [item[3] for item in [network_iris, kmeans_iris, knn_iris, bayes_iris] ]

values_iris1_time = [item[0] for item in [network_iris_time, kmeans_iris_time, knn_iris_time, bayes_iris_time] ]
values_iris2_time = [item[1] for item in [network_iris_time, kmeans_iris_time, knn_iris_time, bayes_iris_time] ]
values_iris3_time = [item[2] for item in [network_iris_time, kmeans_iris_time, knn_iris_time, bayes_iris_time] ]
values_iris4_time = [item[3] for item in [network_iris_time, kmeans_iris_time, knn_iris_time, bayes_iris_time] ]


print(values_iris1_time)

# plots of performance
paint(names, values_iris1, f"Performance,Volume = {sizes[0]}", "iris_perf1")
paint(names, values_iris2, f"Performance,Volume = {sizes[1]}", "iris_perf2")
paint(names, values_iris3, f"Performance,Volume = {sizes[2]}", "iris_perf3")
paint(names, values_iris4, f"Performance,Volume = {sizes[3]}", "iris_perf4")

# plots of times

paint(names, values_iris1_time, f"Times,Volume = {sizes[0]}", "iris_time1")
paint(names, values_iris2_time, f"Times,Volume = {sizes[1]}", "iris_time2")
paint(names, values_iris3_time, f"Times,Volume = {sizes[2]}", "iris_time3")
paint(names, values_iris4_time, f"Times,Volume = {sizes[3]}", "iris_time4")





