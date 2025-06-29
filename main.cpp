#include <bits/stdc++.h>
using namespace std;
static const long long INF = LLONG_MAX;

// Edge list: each tuple is (from, to, weight)
vector<tuple<int, int, int>> edges;

// Add a single directed edge; we'll mirror when building adjacency
void connect(int x, int y)
{
	edges.push_back({x, y, 1});
	edges.push_back({y, x, 1});
}

// Connect all consecutive stations in [start..end] by hops of 1
void connect_range(int start, int end)
{
	for (int i = start; i <= end; ++i)
	{
		connect(i, i + 1);
	}
}

// Runs Dijkstra from src, fills dist[] and prev[]
void dijkstra(int N,
			  int src,
			  const vector<vector<pair<int, int>>> &adj,
			  vector<long long> &dist,
			  vector<int> &prev)
{
	dist.assign(N, INF);
	prev.assign(N, -1);
	dist[src] = 0;

	// min‑heap of (distance, node)
	priority_queue<pair<long long, int>,
				   vector<pair<long long, int>>,
				   greater<pair<long long, int>>>
		pq;
	pq.push({0, src});

	while (!pq.empty())
	{
		auto [d, u] = pq.top();
		pq.pop();
		if (d > dist[u])
			continue;
		for (auto [v, w] : adj[u])
		{
			if (dist[u] + w < dist[v])
			{
				dist[v] = dist[u] + w;
				prev[v] = u;
				pq.push({dist[v], v});
			}
		}
	}
}

// Reconstructs path from src→dst using prev[]
vector<int> build_path(int src, int dst, const vector<int> &prev)
{
	vector<int> path;
	for (int at = dst; at != -1; at = prev[at])
	{
		path.push_back(at);
	}
	reverse(path.begin(), path.end());
	if (!path.empty() && path.front() == src)
		return path;
	return {}; // no path
}

int main()
{
	// 1) Station list, 1‑based indexing
	vector<string> stations = {
		"",
		"Miyapur", "JNTU College", "KPHB Colony", "Kukatpally",
		"Dr. B.R. Ambedkar Balanagar", "Moosapet", "Bharat Nagar",
		"Erragadda", "ESI Hospital", "S.R. Nagar", "Ameerpet",
		"Punjagutta", "Irrum Manzil", "Khairatabad", "Lakdi-ka-pul",
		"Assembly", "Nampally", "Gandhi Bhavan", "Osmania Medical College",
		"M.G. Bus Station", "Malakpet", "New Market", "Musarambagh",
		"Dilsukhnagar", "Chaitanyapuri", "Victoria Memorial", "L.B. Nagar",
		"Raidurg", "HITEC City", "Durgam Cheruvu", "Madhapur",
		"Peddamma Gudi", "Jubilee Hills Check Post", "Road No.5 Jubilee Hills",
		"Yusufguda", "Madhura Nagar", "Begumpet", "Prakash Nagar",
		"Rasoolpura", "Paradise", "Parade Ground", "Secunderabad East",
		"Mettuguda", "Tarnaka", "Habsiguda", "NGRI", "Stadium", "Uppal",
		"Nagole", "JBS Parade Ground", "Secunderabad West", "Gandhi Hospital",
		"Musheerabad", "RTC X Roads", "Chikkadpally", "Narayanaguda",
		"Sultan Bazaar"};
	int N = stations.size(); // includes dummy at index 0

	// 2) Build name→index map
	unordered_map<string, int> idx;
	for (int i = 1; i < N; ++i)
	{
		idx[stations[i]] = i;
	}

	// 3) Define metro connections
	connect_range(1, 26);  // Miyapur → Victoria Memorial
	connect_range(28, 35); // Raidurg → Jubilee Hills Check Post
	connect(11, 36);	   // Ameerpet ↔ Begumpet interchange
	connect(11, 37);	   // Ameerpet ↔ Prakash Nagar interchange
	connect_range(37, 48); // Prakash Nagar → Stadium
	connect(50, 41);	   // Nagole ↔ Secunderabad East (example interchange)
	connect(51, 41);	   // JBS Parade Ground ↔ Secunderabad East
	connect_range(51, 56); // JBS Parade Ground → Sultan Bazaar
	connect(57, 20);	   // Sultan Bazaar ↔ M.G. Bus Station (example)

	// 4) Build adjacency list (undirected)
	vector<vector<pair<int, int>>> adj(N);
	for (auto &[u, v, w] : edges)
	{
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	// 5) List stations
	cout << "Stations:\n";
	for (int i = 1; i < N; ++i)
	{
		cout << setw(3) << i << ": " << stations[i] << "\n";
	}

	// 6) Read source & destination names
	cout << "\nEnter source station name (exactly as shown): ";
	string srcName, dstName;
	getline(cin, srcName);
	cout << "Enter destination station name: ";
	getline(cin, dstName);

	if (!idx.count(srcName) || !idx.count(dstName))
	{
		cerr << "Error: Invalid station name entered.\n";
		return 1;
	}
	int src = idx[srcName];
	int dst = idx[dstName];

	// 7) Run Dijkstra
	vector<long long> dist;
	vector<int> prev;
	dijkstra(N, src, adj, dist, prev);

	// 8) Output result
	if (dist[dst] == INF)
	{
		cout << "No path exists between \"" << srcName
			 << "\" and \"" << dstName << "\".\n";
	}
	else
	{
		cout << "\nShortest hops from \"" << srcName
			 << "\" to \"" << dstName << "\": " << dist[dst] << "\n\n";
		auto path = build_path(src, dst, prev);
		cout << "Route:\n";
		for (int node : path)
		{
			cout << "  - " << stations[node] << "\n";
		}
	}

	return 0;
}
