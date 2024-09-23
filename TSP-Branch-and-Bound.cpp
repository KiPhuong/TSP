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
			X[i] = j;
			d += city[X[i - 1]][X[i]];
			if (i == n) {
				cost = min(cost, d + city[X[n]][X[1]]);
			}
			//Danh gia can
			/*else {
				Try(i + 1);
			}*/
			else if (d + (n - i + 1) * cmin < cost) {
				Try(i + 1);
			}
			//backtrack
			visited[j] = 0;
			d -= city[X[i - 1]][X[i]];
		}
	}
}

int main() {
	cout<<"Using Branch and Bound"<<endl;
	Input();
	X[1] = 1;
	visited[1] = 1;
	Try(2);
	cout << "Shortest path: ";
	for (int i = 1; i <= n + 1; i++) {
		if (i <= n) cout << X[i] << " ";
		else cout << "1 \n";
	}
	cout <<"Min cost: " << cost << endl;
}