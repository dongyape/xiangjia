#include <iostream>
#include <vector>
#include <queue>

// ������ݽṹ��
struct Elevator {
    int id;
    std::vector<int> servicedFloors;
    int maxPassengers;
    int maxLoad;
    std::queue<int> destinationQueue;
    int currentFloor;
    // ���캯��
    Elevator(int elevatorId, std::vector<int> floors, int passengers, int load) {
        id = elevatorId;
        servicedFloors = floors;
        maxPassengers = passengers;
        maxLoad = load;
    }

    // ���Ŀ�ĵص�Ŀ�����
    void addDestination(int floor) {
        destinationQueue.push(floor);
    }

    // ִ�е�������
    void run() {
        while (!destinationQueue.empty()) {
            int currentFloor = destinationQueue.front();
            destinationQueue.pop();
            std::cout << "Elevator " << id << " is moving to floor " << currentFloor << std::endl;
            // ģ�����ͣ��һ��ʱ��
            // do something
            std::cout << "Elevator " << id << " has arrived at floor " << currentFloor << std::endl;
            // do something
        }
    }
};

// ���ݿ���ϵͳ
class ElevatorControlSystem {
private:
    std::vector<Elevator> elevators;

public:
    // ���캯��
    ElevatorControlSystem() {
        // ��ʼ������
        Elevator elevator1(1, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }, 10, 800);
        Elevator elevator2(2, { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 }, 10, 800);
        Elevator elevator3(3, { 0, 2, 4, 6, 8, 10 , 12, 14, 16, 18, 20}, 10, 800);
        Elevator elevator4(4, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }, 20, 2000);

        // ��������ӵ�����ϵͳ��
        elevators.push_back(elevator1);
        elevators.push_back(elevator2);
        elevators.push_back(elevator3);
        elevators.push_back(elevator4);
    }

    // ѡ������ʵĵ��ݲ����Ŀ�ĵ�
    void requestElevator(int floor, int passengers, int load) {
        int bestElevator = -1;
        int minWaitTime = INT_MAX;

        // �������ݣ�ѡ������ʵĵ���
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
            // �ҵ�����ʵĵ��ݣ����Ŀ�ĵ�
            elevators[bestElevator - 1].addDestination(floor);
            std::cout << "Elevator " << bestElevator << " has been assigned to floor " << floor << std::endl;
        }
        else {
            std::cout << "No available elevator for floor " << floor << std::endl;
        }
    }

    // ����ȴ�ʱ��
    int calculateWaitTime(const Elevator& elevator, int floor) {
        // ������Ը���ʵ���������ȴ�ʱ�䣬���統ǰ����λ����Ŀ��¥��ľ����
        return abs(floor - elevator.currentFloor);
    }
};

int main() {
    ElevatorControlSystem controlSystem;

    // �û�����Ŀ����Ϣ
    int floor, passengers, load;
    std::cout << "������Ŀ��¥�㣺";
    std::cin >> floor;
    std::cout << "������˿�������";
    std::cin >> passengers;
    std::cout << "�������ܸ��أ���ǧ��Ϊ��λ����";
    std::cin >> load;

    // �������
    controlSystem.requestElevator(floor, passengers, load);
    return 0;
}