#include <bits/stdc++.h>
using namespace std;

/* ================= SEGMENT TREE ================= */
class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(vector<int>& arr) {
        n = (int)arr.size();
        tree.assign(4 * max(1, n), 0);
        if (n) build(arr, 1, 0, n - 1);
    }

    void build(vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
        } else {
            int mid = (l + r) / 2;
            build(arr, 2 * node, l, mid);
            build(arr, 2 * node + 1, mid + 1, r);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (ql > qr || l > r || qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return query(2 * node, l, mid, ql, qr) +
               query(2 * node + 1, mid + 1, r, ql, qr);
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
        } else {
            int mid = (l + r) / 2;
            if (idx <= mid) update(2 * node, l, mid, idx, val);
            else update(2 * node + 1, mid + 1, r, idx, val);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
};

void segmentTreeMenu() {
    int n;
    cout << "\nEnter size of array: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter array elements:\n";
    for (int i = 0; i < n; i++) cin >> arr[i];

    SegmentTree st(arr);
    while (true) {
        cout << "\n--- Segment Tree Menu ---\n";
        cout << "1. Range Query\n";
        cout << "2. Update Value\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        int c; cin >> c;
        if (c == 0) break;
        if (c == 1) {
            int l, r; cout << "Enter L R: "; cin >> l >> r;
            l = max(l, 0); r = min(r, n - 1);
            if (l > r) { cout << "Invalid range.\n"; continue; }
            cout << "Sum = " << st.query(1, 0, n - 1, l, r) << "\n";
        } else if (c == 2) {
            int idx, val; cout << "Enter idx and new value: "; cin >> idx >> val;
            if (idx < 0 || idx >= n) { cout << "Invalid index.\n"; continue; }
            st.update(1, 0, n - 1, idx, val);
            cout << "Value updated.\n";
        } else {
            cout << "Invalid choice!\n";
        }
    }
}

/* ================= TRIE ================= */
struct TrieNode {
    bool isEnd;
    unordered_map<char, TrieNode*> children;
    TrieNode() : isEnd(false) {}
};

class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }
    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c)) node->children[c] = new TrieNode();
            node = node->children[c];
        }
        node->isEnd = true;
    }
    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c)) return false;
            node = node->children[c];
        }
        return node->isEnd;
    }
};

void trieMenu() {
    Trie trie;
    while (true) {
        cout << "\n--- Trie Menu ---\n";
        cout << "1. Insert Word\n";
        cout << "2. Search Word\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        int c; cin >> c;
        if (c == 0) break;
        if (c == 1) {
            string w; cout << "Enter word: "; cin >> w;
            trie.insert(w);
            cout << "Inserted!\n";
        } else if (c == 2) {
            string w; cout << "Enter word: "; cin >> w;
            cout << (trie.search(w) ? "Found!" : "Not Found!") << "\n";
        } else {
            cout << "Invalid choice!\n";
        }
    }
}

/* ================= GRAPH ================= */
class Graph {
    int V;
    vector<vector<int>> adj;
public:
    Graph(int V) : V(V), adj(V) {}
    void addEdge(int u, int v) {
        if (u < 0 || v < 0 || u >= V || v >= V) return;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void BFS(int start) {
        if (start < 0 || start >= V) { cout << "Invalid start.\n"; return; }
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        cout << "BFS: ";
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << u << " ";
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << "\n";
    }
    void DFSUtil(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << u << " ";
        for (int v : adj[u]) {
            if (!visited[v]) DFSUtil(v, visited);
        }
    }
    void DFS(int start) {
        if (start < 0 || start >= V) { cout << "Invalid start.\n"; return; }
        vector<bool> visited(V, false);
        cout << "DFS: ";
        DFSUtil(start, visited);
        cout << "\n";
    }
};

void graphMenu() {
    int V, E;
    cout << "\nEnter number of vertices & edges: ";
    cin >> V >> E;
    Graph g(V);
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v; cin >> u >> v;
        g.addEdge(u, v);
    }
    int start; cout << "Enter start node: "; cin >> start;
    g.BFS(start);
    g.DFS(start);
}

/* ================= MAIN ================= */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int choice;
    while (true) {
        cout << "\n===== AlgoMarket DSA Visualizer (C++) =====\n";
        cout << "1. Segment Tree\n";
        cout << "2. Trie\n";
        cout << "3. Graph (BFS/DFS)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) break;

        switch (choice) {
            case 1: segmentTreeMenu(); break;
            case 2: trieMenu(); break; // fixed name
            case 3: graphMenu(); break;
            case 0: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
    return 0;
}
