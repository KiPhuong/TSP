import numpy as np
import random
import time

class AntColonyOptimization:
    def __init__(self, distances, n_ants, n_best, n_iterations, decay, alpha=1, beta=1):
        self.distances = distances
        self.n_ants = n_ants
        self.n_best = n_best
        self.n_iterations = n_iterations
        self.decay = decay
        self.alpha = alpha  # pheromone importance
        self.beta = beta    # distance importance
        self.n_cities = len(distances)
        self.pheromone = np.ones(self.distances.shape) / self.n_cities

    def run(self):
        best_route = None
        best_distance = float('inf')
        all_time_best_route = None
        all_time_best_distance = float('inf')

        for iteration in range(self.n_iterations):
            all_routes = self.gen_all_routes()
            self.spread_pheromone(all_routes, self.n_best, best_distance=best_distance)
            best_route, best_distance = min(all_routes, key=lambda x: x[1])

            if best_distance < all_time_best_distance:
                all_time_best_route = best_route
                all_time_best_distance = best_distance

            self.pheromone *= self.decay

            print(f"Iteration {iteration+1}/{self.n_iterations}, Best distance: {best_distance}")
            print(f"Route chosen: {Convert_to_int(best_route)}")
            #print(f"Pheromone: \n{self.pheromone}")

        return all_time_best_route, all_time_best_distance

    def gen_route(self, start):
        route = [start]
        visited = set()
        visited.add(start)
        prev = start
        for _ in range(self.n_cities - 1):
            move = self.pick_move(self.pheromone[prev], self.distances[prev], visited)
            route.append(move)
            visited.add(move)
            prev = move
        return route

    def gen_all_routes(self):
        all_routes = []
        for ant in range(self.n_ants):
            start = random.randint(0, self.n_cities - 1)
            route = self.gen_route(start)
            distance = self.route_distance(route)
            all_routes.append((route, distance))
        return all_routes

    def route_distance(self, route):
        total_distance = 0
        for i in range(len(route)):
            total_distance += self.distances[route[i-1]][route[i]]
        return total_distance

    def spread_pheromone(self, all_routes, n_best, best_distance):
        sorted_routes = sorted(all_routes, key=lambda x: x[1])
        for route, distance in sorted_routes[:n_best]:
            for move in range(len(route)):
                self.pheromone[route[move-1]][route[move]] += 1.0 / distance

    def pick_move(self, pheromone, distance, visited):
        pheromone = np.copy(pheromone)
        pheromone[list(visited)] = 0
        prob = pheromone ** self.alpha * ((1.0 / distance) ** self.beta)
        prob = prob / prob.sum()
        move = np.random.choice(len(self.distances), 1, p=prob)[0]
        return move

# Nhập dữ liệu ma trận khoảng cách từ người dùng
def user_input_matrix():
    n_cities = int(input("Nhập số lượng thành phố: "))
    distances = np.zeros((n_cities, n_cities))
    print("Nhập ma trận khoảng cách giữa các thành phố (hàng cách nhau bằng khoảng trắng):")
    for i in range(n_cities):
        distances[i] = list(map(float, input(f"Nhập khoảng cách từ thành phố {i+1} đến các thành phố khác: ").split()))
    return distances


def Convert_to_int(best_route):
    best_route = [int(city) for city in best_route]
    return best_route

if __name__ == "__main__":
    start_time = time.time()
    distances = user_input_matrix()
    #print(distances)
    aco = AntColonyOptimization(distances, n_ants=10, n_best=5, n_iterations=200, decay=0.95, alpha=1, beta=2)
    best_route, best_distance = aco.run()

    best_route = [int(city) for city in best_route]

    print("Final!!")
    print(f"Best Route: {best_route}, Best Distance: {best_distance}")
    print("Time: ", time.time()-start_time, "seconds!!")

