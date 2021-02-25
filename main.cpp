#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

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


  // int counter = 0; // Tracks number of intersections being scheduled
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

    // sort based on number of starts
    sort(incoming_streets.begin(), incoming_streets.end(), [&starting](const street* a, const street* b) {
      return starting[b->name] - starting[a->name];
      });

    for (const auto& street : incoming_streets) {
      int time_interval = 1;
      sched_individual.push_back(street->name + " " + to_string(time_interval));
    }

    schedule.push_back(sched_individual);

    // if (incoming_streets.size() == 1) { // If there is only a single street coming into the intersection
    //   sched_individual.push_back("1");
    //   sched_individual.push_back(((incoming_streets[0])->name) + " 1");
    // }
    // else {
    //   //   vector<street*> streets = s->in;
    // }
  }


  // Output
  cout << schedule.size() << endl;
  for (const vector<string>& sched_individual : schedule) {
    for (const string& line : sched_individual) cout << line << endl;
  }

  cout << "some random crap" << endl;

  // for (int i = 0; i < schedule.size(); i++) {
  //   vector<string> sched_indvidual = schedule[i];
  //   for (int j = 0; j < sched_individual.size(); j++) {
  //     cout << sched_indvidual[j] << endl;
  //   }
  // }
}