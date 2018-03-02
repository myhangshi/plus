/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
            vector<Interval>::iterator i = intervals.begin();
        
            while (i != intervals.end()) {
                if (newInterval.end < i->start) {
                    intervals.insert(i, newInterval); 
                    return intervals; 
                } else if (newInterval.start > i->end) { 
                    i++; 
                    continue; 
                } else { 
                    newInterval.start = min(newInterval.start, i->start);
                    newInterval.end = max(newInterval.end, i->end);
                    i = intervals.erase(i);                
                } 
            }
            intervals.insert(intervals.end(), newInterval); 
            return intervals; 

    }
    
};

