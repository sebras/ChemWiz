
#include "molecule.h"
#include "Exception.h"

#include <boost/format.hpp>

#include <iostream>
#include <string>

#include <dsrpdb/PDB.h>
#include <dsrpdb/Model.h>
#include <dsrpdb/Protein.h>

/// Molecule

std::vector<Molecule*> Molecule::readPdbFile(const std::string &newFname) {
  std::vector<Molecule*> res;
  // read into dsrpdb::PDB
  std::ifstream file;
  file.open(newFname);
  dsrpdb::PDB pdb(file, true/*print_errors*/);

  if (pdb.number_of_models() == 0)
    throw Exception(str(boost::format("The PDB file '%1%' doesn't have any molecules in it") % newFname));

  auto dsrpdbAtomTypeToOurs = [](auto type) {
    switch (type) {
    case dsrpdb::Atom::C: return C;
    case dsrpdb::Atom::N: return N;
    case dsrpdb::Atom::H: return H;
    case dsrpdb::Atom::O: return O;
    case dsrpdb::Atom::S: return S;
    default: throw Exception("Unknown atom type in the PDB file");
    }
  };

  for (unsigned m = 0; m < pdb.number_of_models(); m++) {
    auto &model = pdb.model(m);
    auto molecule = new Molecule("");
    for (unsigned c = 0; c < model.number_of_chains(); c++) {
      auto &chain = model.chain(c);
      //std::cout << "chain#" << c << ": number_of_residues=" << chain.number_of_residues() << std::endl;
      //residueCount += chain.number_of_residues();
      for (auto a = chain.atoms_begin(), ae = chain.atoms_end(); a != ae; ++a) {
        auto &atom = *a;
        molecule->add(Atom(dsrpdbAtomTypeToOurs(atom.second.type()), Vec3(atom.second.cartesian_coords()[0], atom.second.cartesian_coords()[1], atom.second.cartesian_coords()[2])));
      }
    }
    molecule->detectBonds();
    molecule->setId(str(boost::format("%1%#%2%") % newFname % (m+1)));
    res.push_back(molecule);
  }
  return res;
}

