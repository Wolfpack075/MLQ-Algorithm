/*
    
    Bismillahir Rahmanir Rahim. 
    Every praise goes to ALLAH for our wellbeing.
    She is who she is and all of my codes are dedicated to HER Majesty.
    Code : Kazi Fahim Tahmid
    Judge: Codeforces
    Date : 2023-10-18 05:31
 
    
*/

#include <bits/stdc++.h>

using namespace std;

#define int            long long int
#define F              first
#define S              second
#define pb             push_back
#define si             set <int>
#define vi             vector <int>
#define pii            pair <int, int>
#define vpi            vector <pii>
#define vpp            vector <pair<int, pii>>
#define mii            map <int, int>
#define mpi            map <pii, int>
#define spi            set <pii>
#define endl           "\n"
#define sz(x)          ((int) x.size())
#define all(p)         p.begin(), p.end()
#define double         long double
#define que_max        priority_queue <int>
#define que_min        priority_queue <int, vi, greater<int>>
#define bug(...)       __f (#__VA_ARGS__, __VA_ARGS__)
#define print(a)       for(auto x : a) cout << x << " "; cout << endl
#define print1(a)      for(auto x : a) cout << x.F << " " << x.S << endl
#define print2(a,x,y)  for(int i = x; i < y; i++) cout<< a[i]<< " "; cout << endl

void flush(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
}

void file(){
	#ifndef ONLINE_JUDGE
		freopen("input.txt",  "r",  stdin);
		freopen("output.txt", "w", stdout);
	#endif
}

inline int power(int a, int b)
{
	int x = 1;
	while (b)
	{
		if (b & 1) x *= a;
		a *= a;
		b >>= 1;
	}
	return x;
}

template <typename Arg1>
void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f (const char* names, Arg1&& arg1, Args&&... args)
{
	const char* comma = strchr (names + 1, ',');
	cout.write (names, comma - names) << " : " << arg1 << " | "; __f (comma + 1, args...);
}

const int N = 200005;


class Process {
public:
    // ProcessID , BurstTime , ArrivalTime , QueueAllocation , StartingTIme , TurnAroundTime , WaitingTime , ResponseTIme
    int p , bt , at , q , st , tat , wt , rt; 
    Process(int p, int bt, int at, int q) {
        this->p = p;	this->bt = bt;		this->at = at;		this->q = q;
        st = 0;		tat = -1;	rt = -1;
    }
};

vector<Process> P;
vector<vector<Process>> processQueue;
vi queuePriority = {0, 1};
vi output;

void solve() {
	
	int processNum , T , tq;
	cin >> processNum >> T >> tq;
	output.assign(T, -1);
    processQueue.resize(queuePriority.size());
    
    for( int i=0;i<processNum;i++) {
    	int p, bt, at, q;
        cin >> p >> bt >> at >> q;
        Process process(--p, bt, at, --q);
        P.push_back(process);
    }

    int currentPosInQueue = 0, st = 0;
    for (int t = 0; t < T; ++t) {
        for (auto p : P) {
            if (p.at == t) {
                processQueue[p.q].push_back(p);
            }
        }
        for (auto prioLevel : queuePriority) {
            if (prioLevel == 0 && !processQueue[prioLevel].empty()) {
                output[t] = processQueue[prioLevel][currentPosInQueue].p;
                processQueue[prioLevel][currentPosInQueue].st++; st++;
                if(processQueue[prioLevel][currentPosInQueue].st == processQueue[prioLevel][currentPosInQueue].bt) {
                    processQueue[prioLevel].erase(processQueue[prioLevel].begin() + currentPosInQueue);
                    currentPosInQueue = max((int)0, --currentPosInQueue);
                }
                if (st == tq) {
                    st = 0;
                    currentPosInQueue++;
                    if (processQueue[prioLevel].size() != 0) currentPosInQueue %= (int)processQueue[prioLevel].size();
                    else currentPosInQueue = 0;
                }
                break;
            } else if (prioLevel == 1 && !processQueue[prioLevel].empty()) {
                output[t] = processQueue[prioLevel][0].p;
                processQueue[prioLevel][0].st++;
                if(processQueue[prioLevel][currentPosInQueue].st == processQueue[prioLevel][currentPosInQueue].bt) {
                    processQueue[prioLevel].erase(processQueue[prioLevel].begin() + currentPosInQueue);
                }
                break;
            }

        }
    }
    for (int t = 0; t < T; ++t) {
        cout << t << " " << output[t] + 1 << endl;
    }
    for (int t = T-1; t >= 0; --t) {
        if (P[output[t]].tat == -1) {
            P[output[t]].tat = (t+1) - P[output[t]].at;
            P[output[t]].wt = P[output[t]].tat - P[output[t]].bt;
        }
    }
    for (int t = 0; t < T; ++t) {
        if (P[output[t]].rt == -1) {
            P[output[t]].rt = t - P[output[t]].at;
        }
    }
    cout  << "\n\n\n" << "Process" << "\t" << "TurnAroundTIme" << "\t" << "WaitingTime" << "\t" << "ResponseTime" << endl;
    for (int i = 0; i < P.size(); ++i) {
        cout << i+1 << "\t\t" << P[i].tat << "\t\t\t\t" << P[i].wt << "\t\t\t" << P[i].rt << endl;
    }

	// int n, m;
	// cin >> n >> m;
	// bug(n, m);
}

int32_t main()
{
	
	flush();
	file();

	
	clock_t z = clock();

	int t = 1;
	// cin >> t;
	while (t--) solve();

	cerr << "Run Time : " << ((double)(clock() - z) / CLOCKS_PER_SEC);

	return 0;
}