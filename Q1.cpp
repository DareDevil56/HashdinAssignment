#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

// Struct to store each URL and its timestamp
struct HistoryEntry {
    string url;
    time_t timestamp; // time of visit
};

class BrowserHistory {
private:
    list<HistoryEntry> historyList; // Most recent at front
    unordered_map<string, list<HistoryEntry>::iterator> urlMap;
    int maxSize;

public:
    BrowserHistory(int size = 10) {
        maxSize = size;
    }

    // Visit a URL, make it most recent
    void visitPage(const string& url) {
        time_t now = time(nullptr);

        // If URL exists, remove it from list
        if (urlMap.find(url) != urlMap.end()) {
            historyList.erase(urlMap[url]);
        } else if (historyList.size() >= maxSize) {
            // Remove least recent
            auto last = historyList.back();
            urlMap.erase(last.url);
            historyList.pop_back();
        }

        // Insert at front
        historyList.push_front({url, now});
        urlMap[url] = historyList.begin();
    }

    // Display N most recent URLs
    void getMostRecentHistory(int N) {
        int count = 0;
        cout << "\n--- Most Recent History ---\n";
        for (auto& entry : historyList) {
            if (count >= N) break;
            cout << entry.url << " (Visited at: " << put_time(localtime(&entry.timestamp), "%H:%M:%S") << ")\n";
            count++;
        }
        if (count == 0) cout << "No history available.\n";
    }

    // Clear all history
    void clearHistory() {
        historyList.clear();
        urlMap.clear();
        cout << "History cleared successfully.\n";
    }

    // Change max size
    void changeHistoryLength(int newSize) {
        maxSize = newSize;
        while (historyList.size() > maxSize
