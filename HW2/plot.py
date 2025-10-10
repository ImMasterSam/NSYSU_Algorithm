import argparse
from os import system
import matplotlib.pyplot as plt

# Arguments Parsing
parser = argparse.ArgumentParser()
parser.add_argument("-f", "--file",
                    type=str,
                    help="File name")
parser.add_argument("-d", "--data",
                    type=str,
                    help="Point data file path")
parser.add_argument("-n", "--name",
                    type=str,
                    help="The name of the test case")

# Test cases
# Test = [("Test Case 1", "data/dt1/point.txt", "ans/ans_dt1.txt", "images/ans_dt1.png"),
#         ("Test Case 2", "data/dt2/point.txt", "ans/ans_dt2.txt", "images/ans_dt2.png"),
#         ("Test Case 3", "data/dt3/point.txt", "ans/ans_dt3.txt", "images/ans_dt3.png")]

def read_points(point_path: str, ans_path: str) -> list[tuple[float, float]]:
    """
    Read the city order from ans_path
    Then read the points from point_path according to the city order
    Return the list of points in the order of city_order
    """

    city_order = []
    with open(ans_path, 'r') as f:
        city_order = [int(line.strip()) for line in f.readlines()[1:]]
    
    paths = []
    with open(point_path, 'r') as f:
        points = {}
        for line in f.readlines():
            id, x, y = map(float, line.strip().split())
            points[int(id)] = (x, y)

        paths = [points[id] for id in city_order]

    return paths

def plot_path(name: str, paths: list[tuple[float, float]], out_path: str):
    """
    Plot the path and save it to out_path
    """
    plt.figure()
    plt.title(name)
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.axis('equal')
    plt.scatter(*zip(*paths), color='navy', label='Cities', zorder=1)
    plt.plot(*zip(*paths, paths[0]), color='dodgerblue', linestyle='--', label='Path', zorder=0)
    plt.legend()
    plt.savefig(out_path)
    plt.close()

if __name__ == "__main__":

    args = parser.parse_args()
        
    paths = read_points(args.data, f"ans/{args.file}.txt")
    plot_path(args.name, paths, f"images/{args.file}.png")

    print(f"[{args.name}] Plot saved to images/{args.file}.png")