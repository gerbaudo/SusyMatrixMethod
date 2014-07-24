// -*- c++ -*-
#ifndef SUSY_FAKE_DILEPTONMATRIXMETHOD_H
#define SUSY_FAKE_DILEPTONMATRIXMETHOD_H

/**
 * @author Brett Jackson <Brett.David.Jackson@cern.ch>
 * @data July 2012
 *
 * Class to perform the matrix method fake estimate
 */

#include <iostream>
#include <map>
#include <math.h>
#include <string>

#include "DileptonMatrixMethod/MatrixLepton.h"
#include "DileptonMatrixMethod/FakeRegions.h"
#include "DileptonMatrixMethod/Parametrization.h"
#include "DileptonMatrixMethod/Systematic.h"

class TFile;
class TH1;
class TH1F;
class TArrayD;
class TAxis;

namespace susy{
namespace fake{
class DiLeptonMatrixMethod
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      /**
       * constructor/destructor
       */
      DiLeptonMatrixMethod();
      ~DiLeptonMatrixMethod();

      /**
       * congigure the tool with a histogram file
       */
      bool configure( std::string file_name
                    , susy::fake::Parametrization::Value rate_param_real_el
                    , susy::fake::Parametrization::Value rate_param_fake_el
                    , susy::fake::Parametrization::Value rate_param_real_mu
                    , susy::fake::Parametrization::Value rate_param_fake_mu
                    );

      /**
       * set the units for the rates file
       */
      // void setMeV();
      // void setGeV();

      /**
       * Get the total fake contribution for this event -- called by the user
       */
      float getTotalFake( bool isTight1, bool isElectron1, float pt1, float eta1
                        , bool isTight2, bool isElectron2, float pt2, float eta2
                        , susy::fake::Region region
                        , float MetRel
                        , susy::fake::Systematic::Value syst = susy::fake::Systematic::SYS_NOM
                        ) const;

      /**
       * Get the RR contribution for this event -- called by the user
       */
      float getRR( bool isTight1, bool isElectron1, float pt1, float eta1
                 , bool isTight2, bool isElectron2, float pt2, float eta2
                 , susy::fake::Region region
                 , float MetRel
                 , susy::fake::Systematic::Value syst = susy::fake::Systematic::SYS_NOM
                 ) const;

      /**
       * Get the RF contribution for this event -- called by the user
       */
      float getRF( bool isTight1, bool isElectron1, float pt1, float eta1
                 , bool isTight2, bool isElectron2, float pt2, float eta2
                 , susy::fake::Region region
                 , float MetRel
                        , susy::fake::Systematic::Value syst = susy::fake::Systematic::SYS_NOM
                 ) const;

      /**
       * Get the FR contribution for this event -- called by the user
       */
      float getFR( bool isTight1, bool isElectron1, float pt1, float eta1
                 , bool isTight2, bool isElectron2, float pt2, float eta2
                 , susy::fake::Region region
                 , float MetRel
                        , susy::fake::Systematic::Value syst = susy::fake::Systematic::SYS_NOM
                 ) const;

      /**
       * Get the FF contribution for this event -- called by the user
       */
      float getFF( bool isTight1, bool isElectron1, float pt1, float eta1
                 , bool isTight2, bool isElectron2, float pt2, float eta2
                 , susy::fake::Region region
                 , float MetRel
                        , susy::fake::Systematic::Value syst = susy::fake::Systematic::SYS_NOM
                 ) const;
      //! given a region, determine the internal index used to store its histograms; abort if invalid
      static int getIndexRegion(susy::fake::Region region);
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      enum RATE_TYPE { REAL
                     , FAKE
                     };

      // Get the rate for this lepton -- real/fake for electron or muon
      // Specific rate depends on type of lepton supplied and the
      // RATE_TYPE parameter
      float getRate( bool isTight
                   , bool isElectron
                   , float pt
                   , float eta
                   , RATE_TYPE rate_type
                   , susy::fake::Region region
                   , float MetRel
                        , susy::fake::Systematic::Value syst = susy::fake::Systematic::SYS_NOM
                   ) const;

      const TArrayD* getPtBins() const;
      const TArrayD* getEtaBins() const;
      void printRateSystematics(const MatrixLepton &l, RATE_TYPE &rt, susy::fake::Region &r) const;
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  protected:
      // Get the rate for this lepton -- real/fake for electron or muon
      // Specific rate depends on type of lepton supplied and the
      // RATE_TYPE parameter
      // for internal use
      float getRate( const MatrixLepton&
                   , RATE_TYPE
                   , susy::fake::Region region
                   , float MetRel
                        , susy::fake::Systematic::Value syst = susy::fake::Systematic::SYS_NOM
                   ) const;
      float getRateSyst( const MatrixLepton&
                       , RATE_TYPE
           , susy::fake::Region region
                       , float MetRel
                        , susy::fake::Systematic::Value syst = susy::fake::Systematic::SYS_NOM
                       ) const;

      int getRateBin( const MatrixLepton& lep,
                      TH1* h_rate,
                      susy::fake::Parametrization::Value rate_param
			) const;

      // Get the fake/real contribution for this event -- for internal use
      float getTotalFake( const MatrixLepton& lep1
                        , const MatrixLepton& lep2
                        , susy::fake::Region region
                        , float MetRel
                        , susy::fake::Systematic::Value syst = susy::fake::Systematic::SYS_NOM
                        ) const;
      float getRR( const MatrixLepton& lep1
                 , const MatrixLepton& lep2
                 , susy::fake::Region region
                 , float MetRel
                        , susy::fake::Systematic::Value syst = susy::fake::Systematic::SYS_NOM
                 ) const;
      float getRF( const MatrixLepton& lep1
                 , const MatrixLepton& lep2
                 , susy::fake::Region region
                 , float MetRel
                        , susy::fake::Systematic::Value syst = susy::fake::Systematic::SYS_NOM
                 ) const;
      float getFR( const MatrixLepton& lep1
                 , const MatrixLepton& lep2
                 , susy::fake::Region region
                 , float MetRel
                        , susy::fake::Systematic::Value syst = susy::fake::Systematic::SYS_NOM
                 ) const;
      float getFF( const MatrixLepton& lep1
                 , const MatrixLepton& lep2
                 , susy::fake::Region region
                 , float MetRel
                        , susy::fake::Systematic::Value syst = susy::fake::Systematic::SYS_NOM
                 ) const;

      // Additional methods needed for systematics
      float getStatError(const MatrixLepton&, RATE_TYPE, susy::fake::Region) const;
      float getRelStatError(const MatrixLepton&, RATE_TYPE, susy::fake::Region) const;

      // Determine if the event is TT/TL/LT/LL -- for internal use
      int getTT(const MatrixLepton& lep1, const MatrixLepton& lep2) const;
      int getTL(const MatrixLepton& lep1, const MatrixLepton& lep2) const;
      int getLT(const MatrixLepton& lep1, const MatrixLepton& lep2) const;
      int getLL(const MatrixLepton& lep1, const MatrixLepton& lep2) const;

      // Verbose output
      void printInfo( const MatrixLepton& lep1
                    , const MatrixLepton& lep2
                    , susy::fake::Region region
                    , float MetRel
                        , susy::fake::Systematic::Value syst = susy::fake::Systematic::SYS_NOM
                    ) const;

      // Get systematic value from file -- for internal use
      void loadSysFromFile();

      const TH1* getFirstPtEtaHisto() const; /// get the first available pt_eta histo
      const TAxis* getPtAxis() const;  /// only consider pt_eta histos; assume all histos have the same binning
      const TAxis* getEtaAxis() const; /// only consider pt_eta histos; assume all histos have the same binning
      bool getHistoAndParametrization(const MatrixLepton &lep,
                                      const susy::fake::Region reg,
                                      const RATE_TYPE &rt,
                                      TH1* &h,
                                      susy::fake::Parametrization::Value &rp) const;
      float getFracRelativeError(const MatrixLepton &lep, RATE_TYPE rt, susy::fake::Region region, 
                                 susy::fake::Systematic::Value syst) const;

      // Histograms which hold the real efficiency and fake rates for leptons
      TFile* m_hist_file;
      TH1* m_el_real_eff [susy::fake::NumberOfSignalRegions];
      TH1* m_el_fake_rate[susy::fake::NumberOfSignalRegions];
      TH1* m_mu_real_eff [susy::fake::NumberOfSignalRegions];
      TH1* m_mu_fake_rate[susy::fake::NumberOfSignalRegions];
      TH1* m_el_frac_up;
      TH1* m_el_frac_do;
      TH1* m_mu_frac_up;
      TH1* m_mu_frac_do;

      // Systematic uncertainties grabbed from the config file
      // Real errors
      double m_el_real_up;
      double m_el_real_down;
      double m_mu_real_up;
      double m_mu_real_down;
      // Fake errors
      double m_el_datamc;
      double m_mu_datamc;
      double m_el_region;
      double m_mu_region;
      TH1F* m_el_metrel;
      TH1F* m_mu_metrel;
      TH1F* m_el_eta;
      TH1F* m_mu_eta;
      double m_el_HFLFerr;

      // rate parameterization that describes how the rates are binned
      //Parametrization::Value m_rate_param;
      Parametrization::Value m_rate_param_real_el;
      Parametrization::Value m_rate_param_fake_el;
      Parametrization::Value m_rate_param_real_mu;
      Parametrization::Value m_rate_param_fake_mu;
  };
} // fake
} // susy

#endif
