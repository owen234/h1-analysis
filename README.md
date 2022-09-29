# h1-analysis

## Bin center corrections
The H1 legacy papers use Bin Center Corrections (BCCs).  We probably won't use those in the future, but we need them in order to do direct comparisons to the H1 measurements.  The binning is defined in [utils.c](utils.c) and the bin centers, where the cross sections are evaluated, are set in [fill_h1_rxsec_th2.c](fill_h1_rxsec_th2.c).  The file [h1-binning.pdf](h1-binning.pdf) shows the global bin index (gbi) and the bin center values inside the TH2Poly histograms.  The BCCs are calculated by [calc_bincentercf_poly.C](calc_bincentercf_poly.C), which must be compiled within the H1OO framework at DESY.  The output of this is in the root file [cbc-poly-output-h1-bin-centers.root](cbc-poly-output-h1-bin-centers.root).  A useful text-format table is created by [dump_bc_table.c](dump_bc_table.c), which creates [bin-center-corrections-table.txt](bin-center-corrections-table.txt).  To read in the table within python, you might want to do something like this
```
import pandas as pd
df = pd.read_fwf("bin-center-corrections-table.txt")
```
If we do a new measurement, which will be an average cross section within the bin (i.e. something proportional to Ncounts / (Lumi * bin_area)) to compare with the H1 bin-centered points, you will need the BCC_area column of the table, which is defined as the ratio of the cross section at the center divided by the average cross section within the bin.  Divide the H1 measurement by BCC_area to undo the BCC in the H1 measurement. 
