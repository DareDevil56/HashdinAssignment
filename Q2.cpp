#include <iostream>
#include <list>
#include <unordered_map>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;

// Struct to store each history entry
struct HistoryEntry {
    string url;
    time_t timestamp; // UNIX timestamp of visit
};

class BrowserHistory {
private:
    list<HistoryEntry> historyList; // Doubly linked list for recent history
    unordered_map<string, list<HistoryEntry>::iterator> urlMap; // Map for quick lookup
    int maxSize; // Maximum number of entries to store

public:
    // Constructor to set history size
    BrowserHistory(int size = 5) {
        maxSize = size;
    }

    // Visit a URL
    void visitPage(const string& url) {
        time_t now = time(nullptr); // Get current time

        // If URL already visited, remove old entry
        if (urlMap.find(url) != urlMap.end()) {
            historyList.erase(urlMap[url]);
        }
        // If size exceeds limit, remove least recent
        else if (historyList.size() >= maxSize) {
            HistoryEntry last = historyList.back();
            urlMap.erase(last.url);
            historyList.pop_back();
        }

        // Insert new entry at front
        historyList.push_front({url, now});
        urlMap[url] = historyList.begin();
    }

    // Display the most recent N visited URLs
    void getMostRecentHistory(int N) {
        int count = 0;
        cout << "\n--- Most Recent History ---\n";

        for (const auto& entry : historyList) {
            if (count >= N) break;

            cout << "URL: " << entry.url << "\n";
            cout << "Visited at: "
                 << put_time(localtime(&entry.timestamp), "%d-%m-%Y %H:%M:%S")
                 << "\n\n";
            count++;
        }

        if (count == 0) {
            cout << "No history available.\n";
        }
    }

    // Clear all history
    void clearHistory() {
        historyList.clear();
        urlMap.clear();
        cout << "Browser history cleared.\n";
    }

    // Change the maximum number of entries allowed
    void changeMaxSize(int size) {
        maxSize = size;
        // Trim history if it's too long
        while (historyList.size() > maxSize) {
            HistoryEntry last = historyList.back();
            urlMap.erase(last.url);
            historyList.pop_back();
        }
    }
};

int main() {
    BrowserHistory browser(5); // Default size is 5

    // Sample simulation
    browser.visitPage("google.com");
    browser.visitPage("leetcode.com");
    browser.visitPage("github.com");
    browser.visitPage("stackoverflow.com");
    browser.visitPage("geeksforgeeks.org");

    // Revisit google.com (should move to front)
    browser.visitPage("google.com");

    // Display top 5 most recent
    browser.getMostRecentHistory(5);

    // Clear and show result
    browser.clearHistory();
    browser.getMostRecentHistory(3);

    return 0;
}
