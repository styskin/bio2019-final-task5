//
//  main.cpp
//  Final5
//
//  Created by Andrey Styskin on 23.02.2019.
//  Copyright © 2019 Andrey Styskin. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <bitset>
#include <unordered_map>
#include <stdlib.h>
#include <math.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

typedef pair<int, int> pii;
typedef vector<pii> vii;

int dist(const vi& male, const vi& female) {
    int d = 0;
    for (int i = 0; i < male.size(); ++i) {
        d += male[i] ^ female[i];
    }
    return d;
}

int main(int argc, const char * argv[]) {
    
    for (int T = 2; T <= 7; ++T) {
    
        string path("/Users/styskin/bio2019/Final5/tests/");
        ifstream in;
        in.open(path + to_string(T) + ".in");
        ofstream out;
        out.open(path + to_string(T) + ".out");
        
        int K, P, N;
        in >> K >> P;
        
        
        vii polymorphic;
        for (int i = 0; i < P; ++i) {
            int c, p;
            in >> c >> p;
            polymorphic.push_back(pii(c, p));
        }
        in >> N;
        
        vector<vvi> M(2, vvi(N));
        
        for (int sex = 0; sex < 2; ++sex) {
            string s;
            for (int i = 0; i < N; ++i) {
                getline(in, s);
                for (int j = 0; j < P; ++j) {
                    getline(in, s);
                    if (s == "0/0") {
                        M[sex][i].push_back(0);
                    } else if (s == "0/1") {
                        M[sex][i].push_back(1);
                    } else if (s == "1/0") {
                        M[sex][i].push_back(2);
                    } else if (s == "1/1") {
                        M[sex][i].push_back(3);
                    }
                }
    //            getline(in, s);
            }
        }
        
        for (int sex = 0; sex < 2; ++sex) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M[sex][i].size(); ++j) {
                    if (j > 0) {
                        cout << " ";
                    }
                    cout << M[sex][i][j];
                }
                cout << endl;
            }
        }
        
        
        vvi DD(N, vi(N));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                DD[i][j] = dist(M[0][i], M[1][j]);
                if (j > 0)
                    cout << " ";
                cout << DD[i][j];
            }
            cout << endl;
        }
        bitset<100> mask;
        
        for (int i = 0; i < N; ++i) {
            // find max in DD
            int mx = 0;
            int d  = 0;
            for (int j = 0; j < N; ++j) {
                if (mask[j] == 0 && DD[i][j] > d) {
                    d = DD[i][j];
                    mx = j;
                }
            }
            out << (mx + 1) << endl;
            mask[mx] = 1;
        }
        in.close();
        out.close();
    }
    return 0;
}
