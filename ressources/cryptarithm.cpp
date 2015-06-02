#include <base/logging.h>
#include <constraint_solver/constraint_solver.h>

namespace operations_research {

void Cryptoarithmetics() {

  Solver solver("cryptarithm");

  // declaration des variables et de leur domaine
  IntVar* b = solver.MakeIntVar(1, 9, "B");
  IntVar* o = solver.MakeIntVar(1, 9, "O");
  IntVar* n = solver.MakeIntVar(1, 9, "N");
  IntVar* j = solver.MakeIntVar(0, 9, "J");
  IntVar* u = solver.MakeIntVar(0, 9, "U");
  IntVar* r = solver.MakeIntVar(0, 9, "R");

  std::vector<IntVar*> letters;
  letters.push_back(b);
  letters.push_back(o);
  letters.push_back(n);
  letters.push_back(j);
  letters.push_back(u);
  letters.push_back(r);

  // contrainte initiale
  solver.AddConstraint(
              solver.MakeEquality(
                  solver.MakeSum(
                      solver.MakeSum(
                          solver.MakeProd(b,10),
                          o
                          )->Var(),
                      solver.MakeSum(
                          solver.MakeProd(n,10),
                          j
                          )->Var()
                      )->Var(),
                  solver.MakeSum(
                      solver.MakeSum(
                          solver.MakeProd(o,100),
                          solver.MakeProd(u,10)
                          )->Var(),
                      r
                      )->Var()
                  )
              );

  // contrainte suplementaire
  solver.AddConstraint(solver.MakeAllDifferent(letters));

  // orientation de la recherche
  DecisionBuilder* const db = solver.MakePhase(
      letters, Solver::CHOOSE_FIRST_UNBOUND, Solver::ASSIGN_MIN_VALUE);
  solver.NewSearch(db);

  // parcours des solutions
  while (solver.NextSolution()) {
    LOG(INFO) << "B=" << b->Value();
    LOG(INFO) << "O=" << o->Value();
    LOG(INFO) << "N=" << n->Value();
    LOG(INFO) << "J=" << j->Value();
    LOG(INFO) << "O=" << o->Value();
    LOG(INFO) << "U=" << u->Value();
    LOG(INFO) << "R=" << r->Value();

    LOG(INFO) << "-----";
  }
  LOG(INFO) << "nb solutions = " << solver.solutions();
  solver.EndSearch();
}
}  // namespace operations_research

int main(int argc, char** argv) {
  operations_research::Cryptoarithmetics();
  return 0;
}


