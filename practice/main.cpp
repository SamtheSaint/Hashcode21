#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

/*
1 < I < 10,000 number of ingredients
0 < T_n < 50,000 number of n-number teams
*/

/*
Data structure to store pizzas
->
->
*/

struct Pizza {
  int n;
  unordered_set<string> ingredients;
  bool allocated;

  Pizza() : allocated(false) {}
};

// returns {num_unique, num_repeated} pizza ingredients
// n(p1) <= n(p2) required
pair<int,int> num_unique_repeated_ingredients(const Pizza& p1, const Pizza& p2) {
  assert(p1.n <= p2.n && "p1 > p2");
  int num_union = p1.n + p2.n;
  int num_intersect = 0;
  for(const auto& item : p1.ingredients) {
    if (p2.ingredients.contains(item)) num_intersect++;
  }
  return {num_union - num_intersect, num_intersect};
}

int main() {

  int M; // number of pizza  
  int T_2, T_3, T_4; // number of 2,3 and 4 teams

  vector<Pizza> pizzas;

  vector<vector<int>> allocated_pizzas;

  cin >> M >> T_2 >> T_3 >> T_4;
  for (int i = 0; i < M; i++) {
    Pizza pizza;
    int n; // number of ingredients
    cin >> n;
    pizza.n = n;

    for (int j = 0; j < n; j++) {
      string ing;
      cin >> ing;
      pizza.ingredients.insert(ing);
    }

    pizzas.push_back(pizza);
  }

  // TODO: processing
  /* Algorithm Logic
  if(T_3 > 0){
    
  }
  */

  cout << allocated_pizzas.size() << endl;
  for(auto pizza_indexes : allocated_pizzas) {
    cout << pizza_indexes.size();
    for (int i : pizza_indexes) cout << " " << i;
    cout << endl;
  }
}