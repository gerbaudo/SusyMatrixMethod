#include "SusyMatrixMethod/DiLeptonMatrixMethod.h"
#include "SusyMatrixMethod/MatrixLepton.h"

#include "TArrayD.h"

#include <iostream>
#include <iterator>
#include <string>
#include <cassert>
#include <cmath>
#include <vector>

/*
  Test the matrix method with the recommended, most up-to-date matrix.
  
  davide.gerbaudo@gmail.com
  April 2014
*/

using namespace std;
namespace smm = SusyMatrixMethod;
namespace sf = susy::fake;

//----------------------------------------------------------
vector<double>  bin_edges2bin_centers(const TArrayD* binEdges)
{
    vector<double> binCenters;
    if(binEdges){
        for(int i=0; i<binEdges->GetSize()-1; ++i)
            binCenters.push_back(0.5*(binEdges->At(i) + binEdges->At(i+1)));        
    }
    return binCenters;
}
//----------------------------------------------------------
void printSystematics(smm::DiLeptonMatrixMethod & matrix, bool isEl, bool isMu)
{
    if(isEl==isMu) cout<<"pick either el or mu"<<endl;
    assert(isEl!=isMu);
 
    vector<double> ptBins (bin_edges2bin_centers(matrix.getPtBins()));
    vector<double> etaBins(bin_edges2bin_centers(matrix.getEtaBins()));        
    cout<<"pt bin centers: ";
    copy(ptBins.begin(), ptBins.end(), ostream_iterator<double>(cout, ", "));
    cout<<endl;
    cout<<"eta bin centers: ";
    copy(etaBins.begin(), etaBins.end(), ostream_iterator<double>(cout, ", "));
    cout<<endl;
    bool isTight(false), isElectron(true);
    for(size_t i=0; i<ptBins.size(); ++i)
        for(size_t j=0; j<etaBins.size(); ++j){
            float pt(ptBins[i]), eta(etaBins[j]);
            smm::MatrixLepton l(isTight, isElectron, pt, eta);
            smm::DiLeptonMatrixMethod::RATE_TYPE rt = smm::DiLeptonMatrixMethod::FAKE;
            susy::fake::Region reg = susy::fake::CR_SSInc1j;
            matrix.printRateSystematics(l, rt, reg);
        }
/*   
        float gev2mev(1.0e3);
        bool l0IsSig(true), l0IsEle(false);
        bool l1IsSig(false), l1IsEle(true);
        float l0Pt(30.0), l0Eta(+0.5);
        float l1Pt(25.0), l1Eta(-0.5);
        float dummyMetRel(20.0);
        sf::Region region = sf::CR_SSInc1j;
        smm::SYSTEMATIC sys = smm::SYS_NOM;
        float weight = matrix.getTotalFake(l0IsSig, l0IsEle, l0Pt*gev2mev, l0Eta,
                                           l1IsSig, l1IsEle, l1Pt*gev2mev, l1Eta,
                                           region, metRel*gev2mev, sys);
        cout<<"weight for"
            <<" "<<sf::region2str(region)<<", "
            <<" "<<smm::systematic_names[sys]
            <<" : "<<weight
            <<endl;
        success = true;
*/
}
//----------------------------------------------------------
int main(int argc, char **argv)
{

  string inputFilename="data/FinalFakeHist_Apr_10.root";
  
  bool isEl(false), isMu(false);

  const smm::RATE_PARAM rp = smm::PT_ETA;
  smm::DiLeptonMatrixMethod matrix;
  if(matrix.configure(inputFilename, rp, rp, rp, rp)) {
      cout<<endl<<" --- Fake systematic uncertainties --- "<<endl;
      
      cout<<endl<<" --- Fake electron  --- "<<endl;
      isEl = true; isMu = false;
      printSystematics(matrix, isEl, isMu);

      isEl = false; isMu = true;
      cout<<endl<<" --- Fake muon      --- "<<endl;
      printSystematics(matrix, isEl, isMu);
      cout<<endl;
  }
  return 0;
}