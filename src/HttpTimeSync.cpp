#include "HttpTimeSync.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "HTTPRequest.hpp"

using namespace std;

HttpTimeSync::HttpTimeSync()
    : m_detectTimes(defaultDetectTimes), m_timeDiffs() {}

int HttpTimeSync::getTimeDifference() {}

void HttpTimeSync::runTimeDetect() {
  int detectCount = 0;
  while (detectCount < m_detectTimes) {
    int millse = getCurrentMillisecond();
    if (m_timeDiffs.find(millse) == m_timeDiffs.end()) {
      httpRequest(millse);
      detectCount++;
      cout << millse << " " << detectCount << endl;
    }
  }

  std::map<int, int> countMap;
  for (auto &index : m_timeDiffs) {
    cout << "key:" << index.first << " value:" << index.second << endl;
    countMap[index.second]++;
  }
  for (auto &index : countMap) {
    cout << "key:" << index.first << " count:" << index.second << endl;
  }
}

void HttpTimeSync::httpRequest(int startTimeIndex) {

  try {
    http::Request request{m_url};
    const auto response = request.send("GET");
    auto headers = response.headers;
    for (auto &index : headers) {
      const string dateTag = "Date:";
      if (index.find(dateTag) == 0) {
        const string dateString = index.substr(dateTag.length() + 1);
        cout << dateString << endl;
        clock_t remoteTime = getGMTimeByString(dateString);
        clock_t localTime = getLocalGMTime();
        m_timeDiffs[startTimeIndex] = (localTime - remoteTime);
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Request failed, error: " << e.what() << '\n';
  }
}

clock_t HttpTimeSync::getGMTimeByString(const std::string time) {
  std::tm tm = {};
  strptime(time.c_str(), "%a, %d %b %Y %H:%M:%S GMT", &tm);
  return mktime(&tm);
}

clock_t HttpTimeSync::getLocalGMTime() {
  time_t localTime;
  time(&localTime);
  return mktime(gmtime(&localTime));
}

int HttpTimeSync::getCurrentMillisecond() {
  chrono::microseconds millse = chrono::duration_cast<chrono::microseconds>(
      chrono::steady_clock::now().time_since_epoch());
  return millse.count() % maxDetectTimes * m_detectTimes / maxDetectTimes;
}
