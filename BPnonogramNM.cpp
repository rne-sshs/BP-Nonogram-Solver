#include <bits/stdc++.h>
const int N = 5;
const int M = 5;
using namespace std;

double R[N+M][N*M][2], Q[N+M][N*M][2], QQ[N*M][2];
vector<int> X[N+M];
vector<int> NC[N+M], NS[N*M];
double P[N*M][2] = {0,};
int E[N*M] = {0,};
void initN() {
    for(int i = 0; i<N; i++) {
		for(int j = 0; j<M; j++) {
			NC[i].push_back(M*i+j);
		}
	}
	for(int i = 0; i<M; i++) {
		for(int j = 0; j<N; j++) {
			NC[N+i].push_back(i+M*j);
		}
	}
	
	for(int i = 0; i<N; i++) {
		for(int j = 0; j<M; j++) {
			NS[M*i+j].push_back(i);
			NS[M*i+j].push_back(N+j);
		}
	}
}

void initP() {
	for(int i = 0; i<N; i++) {
		for(int j = 0; j<M; j++) {
			P[M*i+j][0] = 1;
			P[M*i+j][1] = 1;
		}
	}
	for(int i = 0; i<N+M; i++) {
		for(int j = 0; j<N*M; j++) {
		    Q[i][j][0] = 1;
		    Q[i][j][1] = 1;
		}
	}
}
vector<int> arrangeV;
void next_arrangement(int m, bool horizontal) {
	int cnt = arrangeV.size()-1;
	int consum = X[m][cnt];
	while(cnt>=0) {
		arrangeV[cnt]++;
		if(horizontal)
			if(arrangeV[cnt]+consum-1>=M) {
				cnt--;
				consum += X[m][cnt]+1;
			}
			else{
				for(int i = cnt+1; i<arrangeV.size(); i++) {
					arrangeV[i] = arrangeV[i-1]+X[m][i-1]+1;
				}
				return;
			}
		else
			if(arrangeV[cnt]+consum-1>=N) {
				cnt--;
				consum += X[m][cnt]+1;
			}
			else{
				for(int i = cnt+1; i<arrangeV.size(); i++) {
					arrangeV[i] = arrangeV[i-1]+X[m][i-1]+1;
				}
				return;
			}
	}
	if(cnt<0) {
		arrangeV.clear();
		arrangeV.push_back(-1);
	}
}

vector<int> genArr(int m, bool horizontal) {
	vector<int> res;
	int cnt = 0;
	if(horizontal)
		for(int i = 0; i<M; i++) {
			if(cnt>=arrangeV.size()) {
				res.push_back(0);
				continue;
			}
			if(i<arrangeV[cnt]+X[m][cnt]) {
				if(arrangeV[cnt]<=i) res.push_back(1);
				else res.push_back(0);
			}
			else {
				res.push_back(0);
				cnt++;
			}
		}
	else
		for(int i = 0; i<N; i++) {
			if(cnt>=arrangeV.size()) {
				res.push_back(0);
				continue;
			}
			if(i<arrangeV[cnt]+X[m][cnt]) {
				if(arrangeV[cnt]<=i) res.push_back(1);
				else res.push_back(0);
			}
			else {
				res.push_back(0);
				cnt++;
			}
		}
	return res;
}

void printVec(vector<int> vec) {
	for(auto it: vec) {
		printf("%d ", it);
	}
	printf("\n");
	return;
}
vector<string> split(string str, char delimiter) {
    vector<string> ans;
    stringstream ss(str);
    string temp;
    while(getline(ss,temp,delimiter)) {
    	ans.push_back(temp);
    }
    return ans;
}
int main() {
    for(int i = 0; i < N+M; i++) {
        string s;
        getline(cin, s);
        vector<string> VS = split(s, ' ');
        for(int j=0;j<VS.size();j++) {
            X[i].push_back(stoi(VS[j]));
        }
    }
    
    int sum1 = 0, sum2 = 0;
    for(int i=0;i<N;i++) {
        for(int m : X[i]) sum1 += m;
    }
    for(int i=N;i<N+M;i++) {
        for(int m : X[i]) sum2 += m;
    }
    if(sum1!=sum2) {
    	cout << sum1 << '\n' << sum2 << '\n';
        cout << "Wrong Input\n";
        return 0;
    }
    
    clock_t st = clock();
	initN();
	initP();
	
	int iternum = 0;
	int prevchange = -1, lastchanged = 0, changedcnt = 0;
//   vector<int> V = next_arrangement({1, 1, 1, 1, 1}, {0, 3, 5, 7, 9});
//   for(auto vec: V) {
//      printf("%d ", vec);
//   }
	int left = N*M;
    while(left>0) {
		for(int m = 0; m<N; m++) {
			for(int r = 0; r<M; r++) {
			   R[m][NC[m][r]][0] = 0;
			   R[m][NC[m][r]][1] = 0;
			}
            arrangeV.clear();
            arrangeV.push_back(0);
            for(int l = 1; l<X[m].size(); l++) {
				arrangeV.push_back(arrangeV[l-1]+X[m][l-1]+1);
			}
			double res = 0;
			while(1) {
				int cnt = 0;
				vector<int> row = genArr(m, true);
				double val = 1;
				for(int l = 0; l<M; l++) {
					val *= Q[m][NC[m][l]][row[l]];
				}
				if(!val==0) {
					for(int r = 0; r<M; r++) {
						R[m][NC[m][r]][row[r]] += val / Q[m][NC[m][r]][row[r]];
					}
	            }
                next_arrangement(m, true);
				if(arrangeV[0]==-1) break;
            }
            for(int n: NC[m]) {
				double sumR = R[m][n][0] + R[m][n][1];
				if(sumR != 0) {
					R[m][n][0] /= sumR;
					R[m][n][1] /= sumR;
	            }
//            cout << "m:" << m << " n:" << n << " " << R[m][n][0] << ' ' << R[m][n][1] << '\n';
			}
		}
		for(int m = N; m<M+N; m++) {
			for(int r = 0; r<N; r++) {
			   R[m][NC[m][r]][0] = 0;
			   R[m][NC[m][r]][1] = 0;
			}
            arrangeV.clear();
            arrangeV.push_back(0);
            for(int l = 1; l<X[m].size(); l++) {
				arrangeV.push_back(arrangeV[l-1]+X[m][l-1]+1);
			}
			double res = 0;
			while(1) {
				int cnt = 0;
				vector<int> row = genArr(m, false);
				double val = 1;
				for(int l = 0; l<N; l++) {
					val *= Q[m][NC[m][l]][row[l]];
				}
				if(!val==0) {
					for(int r = 0; r<N; r++) {
						R[m][NC[m][r]][row[r]] += val / Q[m][NC[m][r]][row[r]];
					}
	            }
                next_arrangement(m, false);
				if(arrangeV[0]==-1) break;
            }
            for(int n: NC[m]) {
				double sumR = R[m][n][0] + R[m][n][1];
				if(sumR != 0) {
					R[m][n][0] /= sumR;
					R[m][n][1] /= sumR;
	            }
//            cout << "m:" << m << " n:" << n << " " << R[m][n][0] << ' ' << R[m][n][1] << '\n';
			}
		}
		
		for(int n = 0; n<N*M; n++) {
			for(int m: NS[n]) {
				double sumQ = 0;
				for(int k = 0; k<2; k++) {
					double res = 1;
					if(m==NS[n][0]) {
						res = R[NS[n][1]][n][k];
					}
					else {
						res = R[NS[n][0]][n][k];
					}
					res *= P[n][k];
					Q[m][n][k] = res;
					sumQ += res;
				}
//               cout << "m:" << m << " n:" << n << " " << Q[m][n][0] << ' ' << Q[m][n][1] << '\n';
				if(sumQ!=0) {
					Q[m][n][0] /= sumQ;
					Q[m][n][1] /= sumQ;
				}
			}
		}
		bool fl = false;
		for(int n = 0; n<N*M; n++) {
			double a = R[NS[n][0]][n][0] * R[NS[n][1]][n][0] * P[n][0];
			double b = R[NS[n][0]][n][1] * R[NS[n][1]][n][1] * P[n][1];
			if((0.999<a && a<=1) || (0.999<b && b<=1)) {
				if(E[n]!=1) {
					E[n] = 1;
					left--;
					fl = true;
				}
			}
		}
		printf("%d %d\n", left, fl);
		iternum++;
		if(!fl) changedcnt++;
		else changedcnt = 0;
		if(changedcnt>=10 && iternum!=1) {
			for(int n = 0; n<N*M; n++) {
				if(E[n]==1) continue;
				double a = R[NS[n][0]][n][0] * R[NS[n][1]][n][0] * P[n][0];
				double b = R[NS[n][0]][n][1] * R[NS[n][1]][n][1] * P[n][1];
				if(E[n]==0) {
					if(a>b) P[n][1] = 0;
					else P[n][0] = 0;
					break;
				}
			}
			changedcnt = 0;
		}
//      for(int n = 0; n<N*N; n++) {
//       for(int k = 0; k<2; k++) {
//            double res = 1;
//            res *= R[NS[n][0]][n][k];
//            res *= R[NS[n][1]][n][k];
//            res *= P[n][k];
//            QQ[n][k] = res;
//       }
//       double sumQQ = QQ[n][0] + QQ[n][1];
//       if(sumQQ!=0) {
//            QQ[n][0] /= sumQQ;
//            QQ[n][1] /= sumQQ;
//      }
//      }
//
//      for(int i = 0; i<N; i++) {
//         for(int j = 0; j<N; j++) {
//            //string ma= "бр";
//            string ma = "бр";
//          if(QQ[i*N+j][0]-QQ[i*N+j][1] < 0.5 && QQ[i*N+j][1]-QQ[i*N+j][0] < 0.5) ma = "бу";
//            else if(QQ[i*N+j][0]<QQ[i*N+j][1]) ma = "бс";//ma = "бс";
//            cout << ma;
//         }
//         cout << '\n';
//      }
//      if(iternum>200) break;
	}
	for(int n = 0; n<N*M; n++) {
		for(int k = 0; k<2; k++) {
			double res = 1;
			res *= R[NS[n][0]][n][k];
			res *= R[NS[n][1]][n][k];
			res *= P[n][k];
			QQ[n][k] = res;
		}
		double sumQQ = QQ[n][0] + QQ[n][1];
		if(sumQQ!=0) {
			QQ[n][0] /= sumQQ;
			QQ[n][1] /= sumQQ;
		}
	}
	
	for(int i = 0; i<N; i++) {
		for(int j = 0; j<M; j++) {
			// string ma= "бр";
			string ma = "бр";
			if(QQ[i*M+j][0]-QQ[i*M+j][1] < 0.5 && QQ[i*M+j][1]-QQ[i*M+j][0] < 0.5) ma = "бу";
			else if(QQ[i*M+j][0]<QQ[i*M+j][1]) ma = "бс";//ma = "бс";
			cout << ma;
		}
		cout << '\n';
	}
	cout << clock() - st << "ms";
}

