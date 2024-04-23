#include <iostream>
#include <vector>
#include <queue>

// 定义电梯结构体
struct Elevator {
    int id;
    std::vector<int> servicedFloors;
    int maxPassengers;
    int maxLoad;
    std::queue<int> destinationQueue;
    int currentFloor;
    // 构造函数
    Elevator(int elevatorId, std::vector<int> floors, int passengers, int load) {
        id = elevatorId;
        servicedFloors = floors;
        maxPassengers = passengers;
        maxLoad = load;
    }

    // 添加目的地到目标队列
    void addDestination(int floor) {
        destinationQueue.push(floor);
    }

    // 执行电梯运行
    void run() {
        while (!destinationQueue.empty()) {
            int currentFloor = destinationQueue.front();
            destinationQueue.pop();
            std::cout << "Elevator " << id << " is moving to floor " << currentFloor << std::endl;
            // 模拟电梯停留一段时间
            // do something
            std::cout << "Elevator " << id << " has arrived at floor " << currentFloor << std::endl;
            // do something
        }
    }
};

// 电梯控制系统
class ElevatorControlSystem {
private:
    std::vector<Elevator> elevators;

public:
    // 构造函数
    ElevatorControlSystem() {
        // 初始化电梯
        Elevator elevator1(1, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }, 10, 800);
        Elevator elevator2(2, { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 }, 10, 800);
        Elevator elevator3(3, { 0, 2, 4, 6, 8, 10 , 12, 14, 16, 18, 20}, 10, 800);
        Elevator elevator4(4, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }, 20, 2000);

        // 将电梯添加到控制系统中
        elevators.push_back(elevator1);
        elevators.push_back(elevator2);
        elevators.push_back(elevator3);
        elevators.push_back(elevator4);
    }

    // 选择最合适的电梯并添加目的地
    void requestElevator(int floor, int passengers, int load) {
        int bestElevator = -1;
        int minWaitTime = INT_MAX;

        // 遍历电梯，选择最合适的电梯
        for (const auto& elevator : elevators) {
            if (std::find(elevator.servicedFloors.begin(), elevator.servicedFloors.end(), floor) != elevator.servicedFloors.end()) {
                int waitTime = calculateWaitTime(elevator, floor);
                if (waitTime < minWaitTime) {
                    minWaitTime = waitTime;
                    bestElevator = elevator.id;
                }
            }
        }

        if (bestElevator != -1) {
            // 找到最合适的电梯，添加目的地
            elevators[bestElevator - 1].addDestination(floor);
            std::cout << "Elevator " << bestElevator << " has been assigned to floor " << floor << std::endl;
        }
        else {
            std::cout << "No available elevator for floor " << floor << std::endl;
        }
    }

    // 计算等待时间
    int calculateWaitTime(const Elevator& elevator, int floor) {
        // 这里可以根据实际情况计算等待时间，例如当前电梯位置与目标楼层的距离等
        return abs(floor - elevator.currentFloor);
    }
};

int main() {
    ElevatorControlSystem controlSystem;

    // 用户输入目标信息
    int floor, passengers, load;
    std::cout << "请输入目标楼层：";
    std::cin >> floor;
    std::cout << "请输入乘客数量：";
    std::cin >> passengers;
    std::cout << "请输入总负载（以千克为单位）：";
    std::cin >> load;

    // 请求电梯
    controlSystem.requestElevator(floor, passengers, load);
    return 0;
}