// requires amino-acids-and-codons.js

var AcidsCodons = require('scripts/amino-acids-and-codons')

exports.AminoAcids = {
  xyzPath: "molecules/Amino_Acids/",
  codeToName: function(code) {
    return AcidsCodons.AMINO_ACIDS[code].name
  },
  codeToFile: function(code) {
    return exports.AminoAcids.xyzPath+"L-"+exports.AminoAcids.codeToName(code)+".xyz"
  },
  decodePeptide: function(peptide, f) {
    for (var i = 0; i < peptide.length; i++) {
      f(i, peptide.charAt(i))
    }
  },
  combine: function(peptide) {
    var peptideChain;
    exports.AminoAcids.decodePeptide(peptide, function(i,code) {
      var aaMolecule = readXyzFile(exports.AminoAcids.codeToFile(code))
      if (i == 0) {
        peptideChain = aaMolecule
      } else {
        peptideChain.appendAminoAcid(aaMolecule)
      }
    })
    return peptideChain
  }
}

