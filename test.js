var AminoAcids = require('scripts/amino-acids')

var formula = "VVV"
var aa = AminoAcids.AminoAcids.combine(formula)
writeXyzFile(aa, formula+".xyz")
