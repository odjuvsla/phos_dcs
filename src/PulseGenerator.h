#ifndef PULSEGENERATOR_H
#define PULSEGENERATOR_H
/* Copyright(c) 2007, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                          */

/* $Id: PulseGenerator.h 19760 2007-07-18 16:24:28Z policheh $ */

// The class which simulates the pulse shape from the PHOS FEE shaper,
// make sampled amplitudes, digitize them.
// The shape is described by the function RawResponseFunction
// The input parameters for the shape function (time and aplitude) are passed
// to the class via constructor.
// Other parameters related to the shaper are hard-coded in this class


//#include <Rtypes.h>

class PulseGenerator : public TObject
{
public:
  PulseGenerator(double a=0, double t0=0);
  PulseGenerator(const PulseGenerator & pulse);
  virtual  ~PulseGenerator();

  void      AddBaseline(double baselineLevel);
  void      AddNoise   (double sigma);
  void      AddNoise   (double *sigma, double cutoff);
  void      AddPretriggerSamples(int nPresamples);
  void      GetSamples(int *adcHG, int *adcLG) const;
  bool    MakeSamples();
  void      Digitize();
  bool    GetDigitize() {return fDigitize;}
  void      SetDigitise (bool flag) {fDigitize  = flag;}
  void      SetAmplitude(double  a) {fAmplitude = a   ; Reset();}
  void      SetTZero    (double t0) {fTZero     = t0  ; Reset();}
  void      Reset();

  // Raw Read Out
  double        GetRawFormatCapa()        const { return fgCapa ; }
  static double GetRawFormatHighCharge()        { return fgHighCharge ; }
  static double GetRawFormatHighGain()          { return fgHighGain ; }
  static double GetRawFormatHighLowGainFactor() { return fgHighLowGainFactor ; }
  static double GetRawFormatLowCharge()         { return ( fgHighCharge *  fgHighLowGainFactor ) ; }
  static double GetRawFormatLowGain()           { return ( fgHighGain / fgHighLowGainFactor ) ; }
  int           GetRawFormatOrder()       const { return fgOrder ; }
  static int    GetRawFormatTimeBins()          { return fkTimeBins ; }
  static double GetRawFormatTimeMax()           { return fgTimeTrigger*fkTimeBins ; }
  double        GetRawFormatTimePeak()    const { return fgTimePeak ; }
  double        GetRawFormatTimeTrigger() const { return fgTimeTrigger ; }
  static double RawResponseFunctionMax(double charge, double gain) ;
  static double RawResponseFunction   (double *x, double *par) ;
  static double GeV2ADC();

  virtual void Print(Option_t*) const;
  virtual void Draw (Option_t*);

  PulseGenerator& operator = (const PulseGenerator &) {
    Fatal("operator =", "not implemented") ;
    return *this;
  }

private:
  static double fgCapa ;              // capacitor of the preamplifier
  static double fgHighCharge ;        // high charge (to convert energy to charge)
  static double fgHighGain ;          // high gain
  static double fgHighLowGainFactor ; // high to low gain factor
  static int    fgOrder ;             // order of the gamma function

  //  static const int fkTimeBins = 64 ;  // number of sampling bins
  static const int fkTimeBins = 1008 ;  // number of sampling bins

  static double fgTimeMax ;           // maximum sampled time
  static double fgTimePeak ;          // peaking time
  static double fgTimeTrigger ;       // time of the trigger for the RO signal 
  
private:
  double  fAmplitude;    // signal amplitude in GeV
  double  fTZero;        // signal start time in ns
  double *fDataHG;       // samples array for high gain
  double *fDataLG;       // samples array for low  gain
  bool    fDigitize;     // true is samples should be rounded to integers
  
  //  ClassDef(PulseGenerator,1)

};

#endif

