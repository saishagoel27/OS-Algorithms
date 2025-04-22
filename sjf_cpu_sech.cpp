#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
struct Process {
    int id;           
    int arrivalTime;  
    int burstTime;    
    int waitingTime;  
    int turnAroundTime; 
    int startTime;    
    int endTime;};
void calculateWaitingTime(vector<Process>& processes) {
    processes[0].waitingTime = 0;  
    for (int i = 1; i < processes.size(); i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;}}
void calculateTurnAroundTime(vector<Process>& processes) {
    for (int i = 0; i < processes.size(); i++) {
        processes[i].turnAroundTime = processes[i].burstTime + processes[i].waitingTime;}}
void calculateStartEndTime(vector<Process>& processes) {
    int currentTime = 0;
    for (int i = 0; i < processes.size(); i++) {
        processes[i].startTime = currentTime;
        processes[i].endTime = currentTime + processes[i].burstTime;
        currentTime = processes[i].endTime;}}
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
        cout << setw(2) << processes[i].startTime << "    ";}
    cout << setw(2) << processes[processes.size() - 1].endTime << endl; 
    cout << "--------------------------------------------------------------" << endl;}
void sjfScheduling(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
        if (p1.arrivalTime == p2.arrivalTime)
            return p1.burstTime < p2.burstTime;
        return p1.arrivalTime < p2.arrivalTime;});
    calculateWaitingTime(processes);
    calculateTurnAroundTime(processes);
    calculateStartEndTime(processes);}
int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;}
    sjfScheduling(processes);
    printResults(processes);
    printGanttChart(processes);
    findAverageTime(processes);
    return 0;}
// This code implements the Shortest Job First (Non-Premptive) (SJF) CPU scheduling algorithm. It calculates waiting time, turnaround time, start time, and end time for each process, and prints the results along with a Gantt chart and average times.
