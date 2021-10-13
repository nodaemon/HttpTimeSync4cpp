/*
 * Copyright: 2021-2021 noerror.net
 * 基于Http协议的时间同步类
 */

#include <ctime>
#include <functional>
#include <string>
#include <vector>
#include <map>

class HttpTimeSync final {
public:
    HttpTimeSync();
    virtual ~HttpTimeSync() = default;
    HttpTimeSync(const HttpTimeSync&) = delete;
    HttpTimeSync& operator=(const HttpTimeSync&) = delete;

    // (local time - remote time) in microsecond, 1/1000000 s.
    int getTimeDifference();

    void setUrl(const std::string &url) { m_url = url; }

    void runTimeDetect();

    void setDetectTimes(int detectTimes) { m_detectTimes = detectTimes; }

private:
    const int defaultDetectTimes = 1000;
    const int maxDetectTimes = 1000000;
    const int minDetectTimes = 1;
    int m_detectTimes;
    std::string m_url;
    std::map<int, clock_t> m_timeDiffs;

    void httpRequest(int startTimeIndex);
    clock_t getGMTimeByString(const std::string time);
    clock_t getLocalGMTime();
    int getCurrentMillisecond();
};