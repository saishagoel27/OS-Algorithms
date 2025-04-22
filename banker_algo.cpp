#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool isSafeState(vector<vector<int>>& allocation,vector<vector<int>>& max,vector<int>& available, int n, int m){
    vector<int> work = available;
    vector<bool> finish(n, false);
    vector<int> safeSequence;
    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < m; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        canFinish = false;
                        break;}}
                if (canFinish) {
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[i][k];}
                    finish[i] = true;
                    safeSequence.push_back(i);
                    count++;
                    found = true;}}}
        if (!found) {return false;}}
    cout << "Safe Sequence: ";
    for (int i = 0; i < safeSequence.size(); i++) {
        cout << "P" << safeSequence[i] << " ";}
    cout << endl;
    return true;}
bool requestResources(vector<vector<int>>& allocation, vector<vector<int>>& max,vector<int>& available, int n, int m, int processID,vector<int>& request){
    for (int i = 0; i < m; i++) {
        if (request[i] > max[processID][i] - allocation[processID][i]) {
            cout << "Error: Process has exceeded maximum claim." << endl;
            return false;}}
    for (int i = 0; i < m; i++) {
        if (request[i] > available[i]) { cout << "Error: Not enough resources available." << endl;
            return false;}}
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[processID][i] += request[i];}
    if (isSafeState(allocation, max, available, n, m)) {
        return true;
    } else {
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[processID][i] -= request[i];}
        cout << "Error: Request leads to unsafe state." << endl;
        return false;}}
int main() { int n, m;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;
    vector<vector<int>> max(n, vector<int>(m)); 
    vector<vector<int>> allocation(n, vector<int>(m)); 
    vector<int> available(m); 
    cout << "Enter the Maximum Demand Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) { cin >> max[i][j];}}
    cout << "Enter the Allocation Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) { cin >> allocation[i][j];}}
    cout << "Enter the Available Resources:" << endl;
    for (int i = 0; i < m; i++) {cin >> available[i];}
    if (!isSafeState(allocation, max, available, n, m)) {cout << "The system is not in a safe state." << endl;}
    int processID;
    cout << "\nEnter the process ID for resource request: ";
    cin >> processID;
    vector<int> request(m);
    cout << "Enter the request vector for process " << processID << ": ";
    for (int i = 0; i < m; i++) {cin >> request[i];}
    if (requestResources(allocation, max, available, n, m, processID, request)) {
        cout << "Request can be granted." << endl;
    } else { cout << "Request cannot be granted." << endl;}
    return 0;}
