// #define USE_EVERYWHERE

void solveTest() {
    bool improved;
    do {
        improved = false;
        fori(clients) {
            set<int> current = pizza;
            for (auto x : like[i]) {
                pizza.insert(x);
            }
            if (writeCurrentSolution()) {
                improved = true;
            } else {
                pizza = current;
            }
        }
    } while (improved);
}
