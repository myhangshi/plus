#include <iostream>
#include <vector>
 
using namespace std;
 

string addBinary(string a, string b) {
    int la, lb; 
    int ai, bi, val; 
    int carry = 0; 
    string result; 
        
    for (la = a.size() - 1, lb = b.size() - 1; la >= 0 || lb >= 0;) { 
        ai = (la >= 0) ? a[la--] - '0': 0; 
        bi = (lb >= 0) ? b[lb--] - '0': 0; 
        val = ai + bi + carry; 
        carry = val / 2; 
        cout << carry << "value of carry " << val <<endl; 

        result.insert(result.begin(), (val % 2) + '0');    
    }
        
    if (carry == 1) { 
        result.insert(result.begin(), '1');    
    }
    return result; 
}

int main() { 
    string a = "1"; 
    string b = "1"; 
 
    string c = addBinary(a, b); 
    cout << c << "\n"; 
    return 0; 
} 


int main1()
{
    vector <int> g1;
    vector <int> :: iterator i;
    vector <int> :: reverse_iterator ir;
 
    for (int i = 1; i <= 5; i++)
        g1.push_back(i);
 
    cout << "Output of begin and end\t:\t";
    for (i = g1.begin(); i != g1.end(); ++i)
        cout << *i << '\t';
 
    cout << endl << endl;
    cout << "Output of rbegin and rend\t:\t";
    for (ir = g1.rbegin(); ir != g1.rend(); ++ir)
        cout << '\t' << *ir;
 
    return 0;
 
}


