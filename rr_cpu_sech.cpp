#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <climits>  
using namespace std;
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;
    int startTime;
    int endTime;};
void findAverageTime(vector<Process>& processes) {
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    int n = processes.size();
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;}
    cout << "\nAverage waiting time: " << (float)totalWaitingTime / n << endl;
    cout << "Average turnaround time: " << (float)totalTurnAroundTime / n << endl;}
void printResults(const vector<Process>& processes) {
    cout << "\nProcess ID | Arrival Time | Burst Time | Waiting Time | Turnaround Time | Start Time | End Time" << endl;
    for (int i = 0; i < processes.size(); i++) {
        cout << "   P" << processes[i].id << "      |     "
             << processes[i].arrivalTime << "      |     "
             << processes[i].burstTime << "      |     "
             << processes[i].waitingTime << "      |       "
             << processes[i].turnAroundTime << "       |      "
             << processes[i].startTime << "       |     "
             << processes[i].endTime << endl;}}
void printGanttChart(const vector<Process>& processes) {
    cout << "\nGantt Chart:" << endl;
    cout << "--------------------------------------------------------------" << endl;
    for (int i = 0; i < processes.size(); i++) {
        cout << "|  P" << processes[i].id << "  ";}
    cout << "|" << endl;
    cout << "--------------------------------------------------------------" << endl;
    for (int i = 0; i < processes.size(); i++) {
        cout << setw(5) << processes[i].startTime << "    ";    }
    cout << setw(5) << processes[processes.size() - 1].endTime << endl;
    cout << "--------------------------------------------------------------" << endl;}
void roundRobinScheduling(vector<Process>& processes, int timeQuantum) {
    int n = processes.size();
    int currentTime = 0;
    queue<int> readyQueue;  
    vector<bool> isProcessAdded(n, false);  
    int completed = 0;
    while (completed < n) {
        bool processAdded = false;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && !isProcessAdded[i]) {
                readyQueue.push(i);  
                isProcessAdded[i] = true;  
                processAdded = true;}}
        if (!readyQueue.empty()) {
            int currentProcessIndex = readyQueue.front();  
            readyQueue.pop();
            Process& currentProcess = processes[currentProcessIndex];
            int timeToExecute = min(timeQuantum, currentProcess.remainingTime);
            if (currentProcess.remainingTime == currentProcess.burstTime) {
                currentProcess.startTime = currentTime;  }
            currentProcess.remainingTime -= timeToExecute;
            currentTime += timeToExecute;
            if (currentProcess.remainingTime == 0) {
                currentProcess.endTime = currentTime;  
                currentProcess.turnAroundTime = currentProcess.endTime - currentProcess.arrivalTime;
                currentProcess.waitingTime = currentProcess.turnAroundTime - currentProcess.burstTime;
                completed++;}
            if (currentProcess.remainingTime > 0) {
                readyQueue.push(currentProcessIndex);}}
        if (readyQueue.empty() && !processAdded) {
            currentTime++;}}}
int main() {
    int n, timeQuantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;
    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime; }
    roundRobinScheduling(processes, timeQuantum);
    printResults(processes);
    printGanttChart(processes);
    findAverageTime(processes);
    return 0;}
