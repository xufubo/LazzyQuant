#ifndef BOLLINGER_BAND_H
#define BOLLINGER_BAND_H

#include "mql5_indicator.h"

class BollingerBand : public MQL5IndicatorOnSingleDataBuffer
{
    Q_OBJECT
    Q_CLASSINFO("parameter_number", "4")
    Q_PROPERTY(int ExtBandsPeriod READ getBBPeriod CONSTANT)
    Q_PROPERTY(int ExtBandsShift READ getBBShift CONSTANT)
    Q_PROPERTY(double ExtBandsDeviations READ getBBDeviations CONSTANT)

public:
    Q_INVOKABLE explicit BollingerBand(int InpBandsPeriod, int InpBandsShift, double InpBandsDeviations, ENUM_APPLIED_PRICE applyTo, QObject *parent = 0);

    void OnInit() override;

    int getBBPeriod() const { return ExtBandsPeriod; }
    int getBBShift() const { return ExtBandsShift; }
    double getBBDeviations() const { return ExtBandsDeviations; }

protected:
    int ExtBandsPeriod;
    int ExtBandsShift;
    double ExtBandsDeviations;
    int ExtPlotBegin=0;

    IndicatorBuffer<double> ExtMLBuffer;
    IndicatorBuffer<double> ExtTLBuffer;
    IndicatorBuffer<double> ExtBLBuffer;
    IndicatorBuffer<double> ExtStdDevBuffer;

    int OnCalculate (const int rates_total,                     // size of the price[] array
                     const int prev_calculated,                 // bars handled on a previous call
                     const int begin,                           // where the significant data start from
                     const _TimeSeries<double>& price           // array to calculate
                     ) override;
};

template<class T>
double SimpleMA(const int position,const int period,const T &price);

template<class T, class U>
double StdDev_Func(int position, const T &price, const U &MAprice, int period);

#endif // BOLLINGER_BAND_H