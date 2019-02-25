#include <iostream>

using namespace std;

const int MAX_V = 300;

int dist[MAX_V][MAX_V];

void warshall_floyd(int v) {
  for (int k = 0; k < v; k++) {
    for (int i = 0; i < v; i++) {
      for (int j = 0; j < v; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
}

int main() {
  warshall_floyd(MAX_V);

  return 0;
}