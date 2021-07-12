#include <iostream>
#include <queue>
#include <cstring>
using namespace std;


int my_arr[201][201];
int parent[201];
bool visited[201];

// Based off pseudocode provided by textbook and slide information
bool search(int t) {
    // Initialize values of all list elements to zero for visited array
    memset(visited, false, sizeof(visited));

    // Initialize the queue
    queue <int> my_q;
    my_q.push(1);
    visited[1] = true;
    parent[1] = -1;

    // Main search loop
    while (!my_q.empty()){
        // Retrieve first (oldest) member of the queue, then remove it from the queue
        int val = my_q.front();
        my_q.pop();

        // Search my_arr to check if the values in the row have been visited, append to the queue if they haven't
        for (int i = 1; i <= t; i++) {
            if (my_arr[val][i] > 0 && visited[i] == false) {
                visited[i] = true;
                parent[i] = val;
                my_q.push(i);
            }
        }
    }

    // Return true if visited, false if not
    if (visited[t] == true)
        return true;
    else
        return false;
}

// Based off of the pseudocode provided by textbook and slide information
int ford_fulk(int t) {
    parent[1] = -1;
    int max_flow = 0; // Return value

    while (search(t)) {
        // set path flow to large int to be overwritten
        int flow = 1000;
        for (int i = t; i != 1; i = parent[i]) {
            int tmp = parent[i];
            flow = min(flow, my_arr[tmp][i]); 
        }

        for (int i = t; i != 1; i = parent[i]) {
            int tmp = parent[i];
            my_arr[tmp][i] -= flow;
            my_arr[i][tmp] += flow;
        }
        max_flow += flow;
    }

    return max_flow;
}


// Collaborated with Jonathan L. on solution concepts (high level, problem understanding)
int main() {
    int temp_list[201][201];

    int num_cases;
    scanf("%d", &num_cases);

    while (num_cases--) {
        // Initialize the values of each array to 0
        //  Reference 1: https://stackoverflow.com/questions/15520880/initializing-entire-2d-array-with-one-value
        //  Reference 2: http://www.cplusplus.com/reference/cstring/memset/
        memset(parent, 0, sizeof(parent));
        memset(temp_list, 0, sizeof(temp_list));
        memset(my_arr, 0, sizeof(my_arr));

        // Retrieve the number of chambers from input
        int num_chambers;
        scanf("%d", &num_chambers);
        for (int i = 1; i <= num_chambers - 1; i++) {
            // Retrieve the number of exits from input
            int num_exits;
            scanf("%d", &num_exits);
            for (int j = 1; j <= num_exits; j++) {
                // For each of the exits, store the exit destination
                int val;
                scanf("%d", &val);
                if (i == 1 || val == num_chambers) {
                    temp_list[i][val] = 1;
                    my_arr[i][val] = 1;
                }
                else {
                    temp_list[i][val] = 1000;
                    my_arr[i][val] = 1000;
                }
                my_arr[val][i] = 0;
            }
        }
        // Run algorithm
        cout << ford_fulk(num_chambers) << endl;
    }
}