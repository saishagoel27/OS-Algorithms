#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
struct Process {
    int id, arrival_time,burst_time,remaining_burst_time, priority,start_time,completion_time,waiting_time, turnaround_time;};
void priorityScheduling(vector<Process>& processes, int n) {
    int current_time = 0;
    int completed_processes = 0;
    vector<int> gantt_chart;  
    sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
        if (p1.arrival_time == p2.arrival_time) {
            return p1.priority < p2.priority;}
        return p1.arrival_time < p2.arrival_time;});
    vector<bool> completed(n, false);
    vector<int> remaining_burst_times(n);
    for (int i = 0; i < n; ++i) {
        remaining_burst_times[i] = processes[i].burst_time;}
    while (completed_processes < n) {
        int idx = -1;
        int highest_priority = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].arrival_time <= current_time && remaining_burst_times[i] > 0) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    idx = i;}}}
        if (idx == -1) {
            current_time++;
            continue; }
    gantt_chart.push_back(processes[idx].id);
        remaining_burst_times[idx]--;
        current_time++;
        if (remaining_burst_times[idx] == 0) {
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            completed[idx] = true;
            completed_processes++;}}
    cout << "Process ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tCompletion Time" << endl;
    for (int i = 0; i < n; ++i) {
        cout << processes[i].id << "\t\t"
             << processes[i].arrival_time << "\t\t"
             << processes[i].burst_time << "\t\t"
             << processes[i].priority << "\t\t"
             << processes[i].waiting_time << "\t\t"
             << processes[i].turnaround_time << "\t\t"
             << processes[i].completion_time << endl;}
    cout << "\nGantt Chart: ";
    for (int i = 0; i < gantt_chart.size(); ++i) {
        cout << "P" << gantt_chart[i] << " ";}
    cout << endl;
    double avg_waiting_time = 0;
    double avg_turnaround_time = 0;
    for (int i = 0; i < n; ++i) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;}
    cout << "\nAverage Waiting Time: " << avg_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time / n << endl;}
int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i; 
        cout << "\nEnter details for Process " << i << " (Arrival Time, Burst Time, Priority): ";
        cin >> processes[i].arrival_time >> processes[i].burst_time >> processes[i].priority;
        processes[i].start_time = -1;  
        processes[i].remaining_burst_time = processes[i].burst_time;}
    priorityScheduling(processes, n);
    return 0;}
