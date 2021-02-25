#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

struct street {
  string name;
  int L;
  int start;
  int end;

  street(const string& s, int L, int start, int end) : name(s), L(L), start(start), end(end) {}
};

struct intersection {
  int id;
  vector<street*> in;
  vector<street*> out;

  intersection(int id) : id(id) {
    in = vector<street*>(0);
    out = vector<street*>(0);
  }
};

int get_interval(int total_street_cars, int total_intersection_cars, int street_length, int simulation_time);

int main() {
  int D, I, S, V, F;

  cin >> D >> I >> S >> V >> F;

  // street and intersection descriptions
  int B, E, L;
  string street_name;
  vector<intersection*> intersections(I, nullptr);
  vector<street*> streets; streets.reserve(S);
  unordered_map<string, int> cars; // Tracks how many cars pass through a given street
  unordered_map<string, int> starting; // Tracks how many cars are starting at a given street

  for (int i = 0; i < S; i++) {
    cin >> B >> E >> street_name >> L;

    street* S = new street(street_name, L, B, E);
    streets.push_back(S);
    // intersection at the start of the street -> leaving intersection
    if (intersections[B] == nullptr) intersections[B] = new intersection(B);
    intersections[B]->out.push_back(S);

    if (intersections[E] == nullptr) intersections[E] = new intersection(E);
    intersections[E]->in.push_back(S);
  }

  // car descriptions
  int P;
  for (int i = 0; i < V; i++) {
    cin >> P;
    for (int j = 0; j < P - 1; j++) {
      cin >> street_name;
      cars[street_name]++;
      if (j == 0) {
        starting[street_name]++;
      }
    }
  }


  vector<vector<string>> schedule;

  // Processing
  /* Heuristics
  ORDER:
    -> the number of cars that start at the end of the street
  TIMING:
    -> the length of each street
    -> the number of cars that pass through the street
  */
  for (size_t i = 0; i < intersections.size(); i++) {
    auto& incoming_streets = intersections[i]->in;
    vector<string> sched_individual;

    sched_individual.push_back(to_string(i)); // intersection id
    sched_individual.push_back(to_string(incoming_streets.size()));

    // sort based on number of cars that start
    sort(incoming_streets.begin(), incoming_streets.end(), [&starting](const street* a, const street* b) {
      return starting[a->name] - starting[b->name];
      });

    int total_intersection_cars = 0;
    for (const auto& street : incoming_streets) {
      cerr << street->name << " " << cars[street->name] << endl;
      total_intersection_cars += cars[street->name];
    }
    for (const auto& street : incoming_streets) {
      int time_interval = get_interval(cars[street->name], total_intersection_cars, street->L, D);
      sched_individual.push_back(street->name + " " + to_string(time_interval));
    }

    schedule.push_back(sched_individual);
  }


  // Output
  cout << schedule.size() << endl;
  for (const vector<string>& sched_individual : schedule) {
    for (const string& line : sched_individual) cout << line << endl;
  }

}

int get_interval(int total_street_cars, int total_intersection_cars, int street_length, int simulation_time) {

  // cerr << total_street_cars << " " << total_intersection_cars << endl;

  if (total_street_cars == total_intersection_cars) return 1;
  if (total_street_cars == 0) return 0;

  float intersection_ratio = (float)total_street_cars / (float)total_intersection_cars;

  int interval = (int)intersection_ratio / (float)street_length;

  // cerr << interval << endl;

  assert(interval <= simulation_time);
  assert(interval >= 0);

  return interval;
}