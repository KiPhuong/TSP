#include <iostream>
#include <vector>
#include <map>
using namespace std;

int num;
int sum;
vector<vector<int> > tsp;
void findMinRoute(vector<vector<int> > tsp)
{
    int counter = 0;
    int j = 0, i = 0;
    int min = INT_MAX;
    map<int, int> visitedRouteList;
    visitedRouteList[0] = 1; //bat dau tu thanh pho dau tien
    int route[tsp.size()];
    while (i < tsp.size() && j < tsp[i].size())
    {
 
        // Corner of the Matrix
        if (counter >= tsp[i].size() - 1)
        {
            break;
        }
        //kiem tra nhung thanh pho chua den va co chi phi nho hon -> update cost
        if (j != i && (visitedRouteList[j] == 0))
        {
            if (tsp[i][j] < min)
            {
                min = tsp[i][j];
                route[counter] = j + 1;
            }
        }
        j++;

        //da di het thanh pho tu i -> update sum
        if (j == tsp[i].size())
        {
            sum += min;
            min = INT_MAX;
            visitedRouteList[route[counter] - 1] = 1;
            j = 0;
            i = route[counter] - 1;
            cout<<route[counter]<<" ";
            counter++;
        }
    }
    i = route[counter - 1] - 1;
    min = tsp[i][0]; //tro ve thanh pho dau tien
    sum += min;
    cout<<"1";
}
 
void Input(){
    cout << "Input number: ";
    cin >> num;
    for (int i = 0; i < num; i++) { 
        vector<int> v1; //vector tam
        for (int j = 0; j < num; j++) { 
            int temp;
            cin >> temp;
            v1.push_back(temp); 
        } 
        tsp.push_back(v1); 
    }
}
int main()
{
    cout<<"Using Greedy Approach\n";
    Input();
    cout<<"Shortes path: 1 ";
    findMinRoute(tsp);
    cout << ("\nMinimum Cost is : ");
    cout << (sum);
}