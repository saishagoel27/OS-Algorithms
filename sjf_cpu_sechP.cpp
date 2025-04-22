#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
struct Process {
    int id;                
    int arrival_time;      
    int burst_time;        
    int remaining_time;    
    int completion_time;   
    int waiting_time;      
    int turnaround_time;};
bool compareArrivalTime(Process a, Process b) {
    return a.arrival_time < b.arrival_time;}
bool compareBurstTime(Process a, Process b) {
    return a.remaining_time < b.remaining_time;}
void calculateTimes(vector<Process>& processes, int n) {
    int current_time = 0;
    int completed = 0;
    vector<bool> is_completed(n, false);
    vector<int> gantt_chart;  
    while (completed < n) {
        int idx = -1;
        int min_burst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !is_completed[i] && processes[i].remaining_time < min_burst) {
                min_burst = processes[i].remaining_time;
                idx = i;}}
        if (idx != -1) {
            gantt_chart.push_back(processes[idx].id); 
            processes[idx].remaining_time--;
            current_time++;
            if (processes[idx].remaining_time == 0) {
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                is_completed[idx] = true;
                completed++;}} else {
            gantt_chart.push_back(-1); 
            current_time++;}}
    for (int i = 0; i < gantt_chart.size(); i++) {
        if (gantt_chart[i] == -1) {
            cout << "Idle | ";
        } else {
            cout << "P" << gantt_chart[i] << " | ";}}
    cout << endl;}
void printResults(const vector<Process>& processes, int n) {
    cout << "Process ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "         | " << processes[i].arrival_time << "          | "
             << processes[i].burst_time << "         | " << processes[i].completion_time << "            | "
             << processes[i].waiting_time << "          | " << processes[i].turnaround_time << endl;}}
int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    cout << "Enter the process details (Arrival Time, Burst Time):" << endl;
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;  
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time; }
    sort(processes.begin(), processes.end(), compareArrivalTime);
    calculateTimes(processes, n);
    printResults(processes, n);
    return 0;}
