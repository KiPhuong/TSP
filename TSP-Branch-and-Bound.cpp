#include <iostream>
#include <algorithm>

using namespace std;

int n, city[100][100], X[100]; 
int visited[100];
int cost = INT_MAX, cmin = INT_MAX;
int d;

void Input() {
	cout<<"Input number: ";
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> city[i][j];
		}
	}
}
//Tìm X[i]: thu tu thanh pho nguoi du lich di qua
void Try(int i) {
	for (int j = 1; j <= n; j++) {
		if (visited[j] == 0) {
			visited[j] = 1;
			X[i] = j; //Tim duoc thanh pho thu i
			d += city[X[i - 1]][X[i]]; //cap nhat khoang cach 
			if (i == n) { //di het thanh pho
				cost = min(cost, d + city[X[n]][X[1]]); //so sanh voi cost -> be hon thi cap nhat lai
			}
			//danh gia can
			else if (d + (n - i + 1) * cmin < cost) {
				Try(i + 1);
			}
			//quay lui lai
			visited[j] = 0;
			d -= city[X[i - 1]][X[i]];
		}
	}
}

int main() {
	cout<<"Using Branch and Bound"<<endl;
	Input();
	X[1] = 1; //bat dau tu thanh pho thu 1
	visited[1] = 1; //danh dau thanh pho thu 1 da di qua
	Try(2); //bat dau tim thanh pho ke tiep
	cout << "Shortest path: ";
	for (int i = 1; i <= n + 1; i++) {
		if (i <= n) cout << X[i] << " ";
		else cout << "1 \n";
	}
	cout <<"Min cost: " << cost << endl;
}