#include <bits/stdc++.h>
using namespace std;

class Process {
protected:
    int pid;
    int arrival;
    int burst_time;
    int priority;

public:
    Process(int p = -1) : pid(0), arrival(0), burst_time(0), priority(p){
        cin >> pid >> arrival >> burst_time;
        if (p != -1) {
            cin >> priority;
        }
    }

    int get_pid() const { return pid; } 
    int get_arrival() const { return arrival; }
    int get_burst() const { return burst_time; }
    int get_priority() const { return priority; }
};

bool compare_a(const Process& a, const Process& b) {
    return a.get_arrival() < b.get_arrival();
}

bool compare_p(const Process& a, const Process& b){
    return a.get_priority() < b.get_priority();
}

class FCFS {
private:
    int n;
    vector<Process> vec;
    queue<Process> processQueue;
    vector<int> startTimes;
    vector<int> endTimes;

public:
    void execute() {
        int count = 1;
        int currentTime = 0;
        cout << "\nProcess Execution Order:\n" << endl;

        cout<<"Process ID\t"<<"Start Time\t"<<"End Time";
        cout<<"\n------------------------------------------\n";

        while (!processQueue.empty()) {
            Process currentProcess = processQueue.front();
            processQueue.pop();

            // Wait if the process has not yet arrived
            if (currentProcess.get_arrival() > currentTime) {
                currentTime = currentProcess.get_arrival();
            }
            startTimes.push_back(currentTime);
            endTimes.push_back(currentTime + currentProcess.get_burst());


            cout<<currentProcess.get_pid()<<"\t\t";
            cout<<currentTime<<"\t\t";
            cout<<currentTime + currentProcess.get_burst()<<"\t\t";
            cout<<"\n------------------------------------------"<<endl;
            currentTime += currentProcess.get_burst();
            count++;
        }
    }
    FCFS() {
        cout << "\n\n------FCFS Scheduling------\n\n";
        cout << "Enter the number of Processes: ";
        cin >> n;
        cout<<"\nPID\tArrival Time\tBurst Time\n";

        for (int i = 0; i < n; i++) {
            Process obj;
            vec.emplace_back(obj);
        }

        sort(vec.begin(), vec.end(), compare_a);

        for (const Process& process : vec) {
            processQueue.push(process);
        }

        execute();
    }
};

class SJF {
private:
    int n;
    vector<Process> vec;
    vector<int> startTimes;
    vector<int> endTimes;

public:
    void execute() {
        int currentTime = 0;
        cout << "\nProcess Execution Order:\n" << endl;

        cout << "Process ID\t" << "Start Time\t" << "End Time";
        cout << "\n------------------------------------------\n";

        while (!vec.empty()) {
            // Find the process with the shortest burst time among those that have arrived
            int minIndex = -1;
            int minBurst = INT_MAX;

            for (int i = 0; i < vec.size(); i++) {
                if (vec[i].get_arrival() <= currentTime && vec[i].get_burst() < minBurst) {
                    minBurst = vec[i].get_burst();
                    minIndex = i;
                }
            }

            if (minIndex == -1) { 
                currentTime++;
                continue;
            }

            Process currentProcess = vec[minIndex];
            vec.erase(vec.begin() + minIndex);

            startTimes.push_back(currentTime);
            endTimes.push_back(currentTime + currentProcess.get_burst());

            cout << currentProcess.get_pid() << "\t\t";
            cout << currentTime << "\t\t";
            cout << currentTime + currentProcess.get_burst() << "\t\t";
            cout << "\n------------------------------------------" << endl;

            currentTime += currentProcess.get_burst();
        }
    }

    SJF() {
        cout << "\n\n------SJF Scheduling------\n\n";
        cout << "Enter the number of Processes: ";
        cin >> n;
        cout << "\nPID\tArrival Time\tBurst Time\n";

        for (int i = 0; i < n; i++) {
            Process obj;
            vec.emplace_back(obj);
        }

        // Sort by arrival time initially, will sort by burst time during execution
        sort(vec.begin(), vec.end(), compare_a);

        execute();
    }
};

class SRT {
private:
    int n;
    vector<Process> vec;
    vector<int> remainingBurstTimes;
    vector<int> startTimes;
    vector<int> finishTimes;
    vector<bool> hasStarted; // To track whether a process has started execution

public:
    void execute() {
        int currentTime = 0;
        int completed = 0;
        int minRemainingTime;
        int shortestProcess = -1;
        bool foundProcess;
        int lastProcess = -1;

        cout << "\nProcess Execution Order:\n" << endl;
        cout << "Process ID\tStart Time\tEnd Time" << endl;
        cout << "------------------------------------------" << endl;

        while (completed < n) {
            minRemainingTime = INT_MAX;
            foundProcess = false;

            // Find the process with the smallest remaining time that has arrived
            for (int i = 0; i < n; i++) {
                if (vec[i].get_arrival() <= currentTime && remainingBurstTimes[i] > 0 && remainingBurstTimes[i] < minRemainingTime) {
                    minRemainingTime = remainingBurstTimes[i];
                    shortestProcess = i;
                    foundProcess = true;
                }
            }

            // If no process is ready, increment time
            if (!foundProcess) {
                currentTime++;
                continue;
            }

            // Handle context switch: if a different process is selected, print the end time for the last process
            if (lastProcess != -1 && lastProcess != shortestProcess) {
                finishTimes[lastProcess] = currentTime;
                cout << "P" << vec[lastProcess].get_pid() << "\t\t"
                     << startTimes[lastProcess] << "\t\t"
                     << finishTimes[lastProcess] << endl;
                cout << "------------------------------------------" << endl;
            }

            // If this is the first time the process is executing, record its start time
            if (!hasStarted[shortestProcess]) {
                startTimes[shortestProcess] = currentTime;
                hasStarted[shortestProcess] = true;
            }

            // Execute the process for one unit of time
            remainingBurstTimes[shortestProcess]--;

            // If the process completes, print its final execution segment
            if (remainingBurstTimes[shortestProcess] == 0) {
                completed++;
                finishTimes[shortestProcess] = currentTime + 1;
                cout << "P" << vec[shortestProcess].get_pid() << "\t\t"
                     << startTimes[shortestProcess] << "\t\t"
                     << finishTimes[shortestProcess] << endl;
                cout << "------------------------------------------" << endl;
                lastProcess = -1; // No active process after this one completes
            } else {
                // If the process is preempted, update its start time
                if (lastProcess != shortestProcess) {
                    startTimes[shortestProcess] = currentTime;
                }
                lastProcess = shortestProcess; // Mark this as the last executed process
            }

            currentTime++;
        }

        // Print the final state of the last process if needed
        if (lastProcess != -1 && remainingBurstTimes[lastProcess] > 0) {
            finishTimes[lastProcess] = currentTime;
            cout << "P" << vec[lastProcess].get_pid() << "\t\t"
                 << startTimes[lastProcess] << "\t\t"
                 << finishTimes[lastProcess] << endl;
            cout << "------------------------------------------" << endl;
        }
    }

    SRT() {
        cout << "\n\n------SRT Scheduling------\n\n";
        cout << "Enter the number of Processes: ";
        cin >> n;
        cout << "\nPID\tArrival Time\tBurst Time\n";

        for (int i = 0; i < n; i++) {
            Process obj;
            vec.emplace_back(obj);
        }

        sort(vec.begin(), vec.end(), compare_a);

        // Initialize vectors
        for (int i = 0; i < n; i++) {
            remainingBurstTimes.push_back(vec[i].get_burst());
            startTimes.push_back(-1);   // -1 indicates the process hasn't started yet
            finishTimes.push_back(0);
            hasStarted.push_back(false); // Initialize the started flag to false
        }

        execute();
    }
};

class RoundRobin {
private:
    int n;
    vector<Process> vec;
    vector<int> remainingBurstTimes;
    vector<int> startTimes;
    vector<int> finishTimes;
    vector<bool> inQueue; // To track if a process is already in the queue
    int quantum;

public:
    void execute() {
        int currentTime = 0;
        queue<int> processQueue;
        queue<int> preempted;

        cout << "\nProcess Execution Order:\n" << endl;
        cout << "Process ID\tStart Time\tEnd Time" << endl;
        cout << "------------------------------------------" << endl;

        while (true) {
            // Enqueue processes that have arrived by the current time and are not in the queue yet
            bool newProcessAdded = false;
            for (int i = 0; i < n; i++) {
                if (vec[i].get_arrival() <= currentTime && !inQueue[i] && remainingBurstTimes[i] > 0) {
                    processQueue.push(i);
                    inQueue[i] = true;
                    newProcessAdded = true;
                }
            }
            while(!preempted.empty()){
                processQueue.push(preempted.front());
                preempted.pop();
            }

            if (!newProcessAdded && processQueue.empty()) {
                break;  // All processes are completed
            }

            if (!processQueue.empty()) {
                int currentProcessIndex = processQueue.front();
                processQueue.pop();
                Process& currentProcess = vec[currentProcessIndex];

                // If this is the first time the process is being executed, set the start time
                if (startTimes[currentProcessIndex] == -1) {
                    startTimes[currentProcessIndex] = currentTime;
                }

                // Determine the actual time to execute the current process
                int execTime = min(quantum, remainingBurstTimes[currentProcessIndex]);

                // Print the start and end time of the current execution
                cout << "P" << currentProcess.get_pid() << "\t\t" << currentTime << "\t\t";
                currentTime += execTime;
                remainingBurstTimes[currentProcessIndex] -= execTime;
                cout << currentTime << endl;
                cout << "------------------------------------------" << endl;

                // If the process is finished, record its finish time
                if (remainingBurstTimes[currentProcessIndex] == 0) {
                    finishTimes[currentProcessIndex] = currentTime;
                    inQueue[currentProcessIndex]= false;
                } else {
                    // Re-enqueue the process if it has remaining burst time
                    preempted.push(currentProcessIndex);
                    inQueue[currentProcessIndex]= true;
                    
                }
            } else {
                // If no process is ready, increment time
                currentTime++;
            }
        }
    }

    RoundRobin(int q) : quantum(q) {
        quantum= q;
        cout << "\n\n------Round Robin Scheduling------\n\n";
        cout << "Enter the number of Processes: ";
        cin >> n;
        cout << "\nPID\tArrival Time\tBurst Time\n";

        for (int i = 0; i < n; i++) {
            Process obj;
            vec.emplace_back(obj);
        }

        sort(vec.begin(), vec.end(), compare_a);

        // Initialize vectors
        for (int i = 0; i < n; i++) {
            remainingBurstTimes.push_back(vec[i].get_burst());
            startTimes.push_back(-1);   // -1 indicates the process hasn't started yet
            finishTimes.push_back(0);
            inQueue.push_back(false);   // Initialize all processes as not in queue
        }

        execute();
    }
};

class Priority {
private:
    int n;
    vector<Process> vec;
    vector<int> remainingBurstTimes;
    vector<int> startTimes;
    vector<int> finishTimes;
    vector<bool> hasStarted; // To track whether a process has started execution

public:
    void execute() {
        int currentTime = 0;
        int completed = 0;
        int minRemainingTime;
        int shortestProcess = -1;
        bool foundProcess;
        int lastProcess = -1;

        cout << "\nProcess Execution Order:\n" << endl;
        cout << "Process ID\tStart Time\tEnd Time" << endl;
        cout << "------------------------------------------" << endl;

        while (completed < n) {
            minRemainingTime = INT_MAX;
            foundProcess = false;

            // Find the process with the highest priority (lowest number) among those that have arrived
            for (int i = 0; i < n; i++) {
                if (vec[i].get_arrival() <= currentTime && remainingBurstTimes[i] > 0 && vec[i].get_priority() < minRemainingTime) {
                    minRemainingTime = vec[i].get_priority();
                    shortestProcess = i;
                    foundProcess = true;
                }
            }

            // If no process is ready, increment time
            if (!foundProcess) {
                currentTime++;
                continue;
            }

            // Handle context switch: if a different process is selected, print the end time for the last process
            if (lastProcess != -1 && lastProcess != shortestProcess) {
                finishTimes[lastProcess] = currentTime;
                cout << "P" << vec[lastProcess].get_pid() << "\t\t"
                     << startTimes[lastProcess] << "\t\t"
                     << finishTimes[lastProcess] <<endl;
                cout << "------------------------------------------------" << endl;
            }

            // If this is the first time the process is executing, record its start time
            if (!hasStarted[shortestProcess]) {
                startTimes[shortestProcess] = currentTime;
                hasStarted[shortestProcess] = true;
            } else if (lastProcess != shortestProcess) {
                // Update the start time when the process resumes
                startTimes[shortestProcess] = currentTime;
            }

            // Execute the process for one unit of time
            remainingBurstTimes[shortestProcess]--;

            // If the process completes, print its final execution segment
            if (remainingBurstTimes[shortestProcess] == 0) {
                completed++;
                finishTimes[shortestProcess] = currentTime + 1;
                cout << "P" << vec[shortestProcess].get_pid() << "\t\t"
                     << startTimes[shortestProcess] << "\t\t"
                     << finishTimes[shortestProcess] <<endl;
                cout << "------------------------------------------------" << endl;
                lastProcess = -1; // No active process after this one completes
            } else {
                lastProcess = shortestProcess; // Mark this as the last executed process
            }

            currentTime++;
        }

        // Print the final state of the last process if needed
        if (lastProcess != -1 && remainingBurstTimes[lastProcess] > 0) {
            finishTimes[lastProcess] = currentTime;
            cout << "P" << vec[lastProcess].get_pid() << "\t\t"
                 << startTimes[lastProcess] << "\t\t"
                 << finishTimes[lastProcess] << "\t\t"
                 << vec[lastProcess].get_priority() << endl;
            cout << "------------------------------------------------" << endl;
        }
    }

    Priority() {
        cout << "\n\n------Priority Scheduling------\n\n";
        cout<<"-> Preemptive Mode\n"<<"-> Smaller Number Represents Higher Priority\n\n";
        cout << "Enter the number of Processes: ";
        cin >> n;
        cout << "\nPID\tArrival Time\tBurst Time\tPriority\n";

        for (int i = 0; i < n; i++) {
            Process obj(2);
            vec.emplace_back(obj);
        }

        sort(vec.begin(), vec.end(), compare_p);

        // Initialize vectors
        for (int i = 0; i < n; i++) {
            remainingBurstTimes.push_back(vec[i].get_burst());
            startTimes.push_back(-1);   // -1 indicates the process hasn't started yet
            finishTimes.push_back(0);
            hasStarted.push_back(false); // Initialize the started flag to false
        }

        execute();
    }
};

int main() {
    cout << "\n\n------Welcome to Process Scheduling Calculator------\n\n";
    cout << "Enter the Scheduling Type:- \n";
    cout << "1. First Come First Serve (FCFS)\n";
    cout << "2. Shortest Job First (SJF)\n";
    cout << "3. Shortest Remaining Time (SRT)\n";
    cout << "4. Round Robin (RR)\n";
    cout << "5. Priority Scheduling (Preemptive)\n";

    int choice;
    cout << endl << "Enter Your Choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            FCFS objFCFS;
            break;
        }
        case 2: {
            SJF objSJF;
            break;
        }
        case 3: {
            SRT objSRT;
            break;
        }
        case 4: {
            int q;
            cout<<"\nEnter The Time Quantum: ";
            cin>>q;
            RoundRobin objRR(q);
            break;
        }
        case 5: {
            Priority objPriority;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}
