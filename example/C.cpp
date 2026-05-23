#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define endl '\n' 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    string p = "execute";
    while (T--)
    {
        string s;
        cin >> s;
        vector<int> pos;
        for (size_t  i = 0; i + 7 <=s.size(); i++)
        {
            if (s.compare(i, 7, p) == 0)
            {
                pos.push_back(i);
            }
        }
        int n = pos.size();
        for (int l = 0; l < n; )
        {
            int r = l;
            while (r + 1 < n && pos[r + 1] - pos[r] == 6)
            {
                r++;
            }
            int len = r - l + 1;
            if (len % 2 == 1)
            {
                for (int i = 0; i < len; i += 2)
                {
                    s[pos[l + i]] = '1';
                }
            }
            else
            {
                for (int i = 1; i < len; i += 2)
                {
                    s[pos[l + i]] = '1';
                }
            }

            l = r + 1;
        }
        cout << s << endl; 
    }

    return 0;
}