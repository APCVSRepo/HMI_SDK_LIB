#ifndef DATETIMEPICKER_H
#define DATETIMEPICKER_H

#include <QWidget>
#include <HMIWidgets/Picker.h>
#include <QDate>
#include <QColor>
#include <QScrollBar>

class DateTimePicker : public QWidget
{
    Q_OBJECT
public:
    enum ePickerType
    {
        eYearPicker = 0,
        eMonthPicker,
        eDayPicker,
        eHourPicker,
        eMinutePicker,
        eAMPMPicker,
        eAllPikcer
    };
    enum eMonthPickerType
    {
        eChineseText,
        eEngLishText,
        eEngLishAbbrText,
        eEngLishWithComma
    };
    enum eFontStyle
    {
        eKnownFontStyle,
        eYearMonthStyle,
        eYearYearMonthDayStyle,
        eMonthDayHourMinStyle,
    };
    explicit DateTimePicker(QWidget *parent = 0);
    ~DateTimePicker();

    void SetCurrentDate( QDate date,bool isreturn=false);
    void SetCurrentHour(int hour,bool isreturn=false);
    void SetCurrentMinute(int minute,bool isreturn=false);
    void SetCurrentAMPM(bool bAMOrPm,bool isreturn=false);
    QDate GetCurrentDate();
    int   GetCurrentHour();
    int   GetCurrentMinute();
    bool  IsAMOrPM(); //true is AM; false is PM

    void SetItemCountPerPage(int count);
    void SetCurrentFontSize(int fontSize);
    void SetYearFontStyle(Picker::eFontStyle type);
    void SetMonthFontStyle(Picker::eFontStyle type);
    void SetDayFontStyle(Picker::eFontStyle type);
    void SetHourFontStyle(Picker::eFontStyle type);
    void SetMinFontStyle(Picker::eFontStyle type);
    void SetAMAndFMFontStyle(Picker::eFontStyle type);
    void CreateYearPicker(int minYear, int maxYear, const QSize& itemSize,bool isUpdateYear = false);
    void CreateMonthPicker(const QSize& itemSize, eMonthPickerType type);
    void CreateMonthPicker(const QSize& itemSize, QStringList qsMonth);
    void CreateDayPicker(int days, const QSize& itemSize);
    void CreateHourPicker(const QSize& itemSize, bool b12HourSystem = true);
    void CreateMinutePicker(const QSize& itemSize);
    void CreateAMPMPicker(const QSize& itemSize,int nPage=3,bool isSliderByTime = false);
    void YearPickerHide();
    void SetYearPickerGeometry(int x, int y, int w, int h);
    void SetMonthPickerGeometry(int x, int y, int w, int h);
    void SetDayPickerGeometry(int x, int y, int w, int h);
    void SetHourPickerGeometry(int x, int y, int w, int h);
    void SetMinutePickerGeometry(int x, int y, int w, int h);
    void SetAMPMPickerGeometry(int x, int y, int w, int h);

    void SetPickerGeometry(int x, int y, int w, int h, ePickerType type);
    void SetPickerFontSize(int fontSize, ePickerType type);
    void SetPickerEnabled(bool enabled, ePickerType type = eAllPikcer);
    bool GetIs12HourSystem();

    void SetCurColor(QColor color);
    void setAlPha(qreal al);
    void SetUpAndDownColor(QColor color);
    void UpdateMonthPickerText(QStringList qsMonth);
    void UpdateMonthPickerText(eMonthPickerType type);
    void UpdateAMAndMMPickerText(bool isChanese);
    void UpdateAMAndMMPickerText(QString StrAM,QString StrPM);
    bool getIsUpdateAmOrFm();
    void setPaintPickEnd(bool);
    void initPicker();
    void PickerPosition(double xmove,double ymove,double Xzoom,double YZoom,int nrow,ePickerType type = eYearPicker);
protected:
    bool eventFilter(QObject *object, QEvent *event);
    int UpdateDayPickerByYear(int year,bool isAnimation=false);
    int UpdateDayPickerByMonth(int month,bool isAnimation=false);
    bool MouseEvent(QObject *object, QEvent *event);

signals:
    void currentDateTimeChanged();
    void UpdateYear(int);
public slots:
    void onYearChanged(int year);
    void onMonthChanged(int month);
    void onUpdateYearChanged(int step,int month);
    void onDayChanged(int day);
    void onHourChanged(int hour);
    void onMinuteChanged(int minute);
    void onAMPMChanged(int ampm);
    void onAMPMChanged(int UpOrDown,int hour);
    void onPaintFinish(QString name);
    void onPickFinish(int type);
private:
    Picker*     m_pYearPicker;
    Picker*     m_pMonthPicker;
    Picker*     m_pDayPicker;
    Picker*     m_pHourPicker;
    Picker*     m_pMinutePicker;
    Picker*     m_pAMPMPicker;
    int            m_nMinYear;
    int            m_nMaxYear;
    QDate          m_dateCurrent;
    int            m_recordMonth;
    int            m_recordHour;
    int            m_recordDirection;
    int            m_recordAMAndPMDirection;
    int            m_nItemCountPerPage;
    int            m_nItemAMAndFMCountPerPage;
    int            m_nCurrentHour;
    int            m_nCurrentMinute;
    bool           m_bAMOrPM;
    int            m_nCurrentFontSize;
    QSize          m_sizeDayPickerItem;
    QMap<ePickerType, int>    m_mapFontSize;
    bool           m_isUpdateYear;
    bool           m_b12HourSystem;
    eFontStyle     m_FontStyle;
    bool           m_isUpdateAMrOFM;
    bool           m_isPickSlide;
    bool           m_isPaintPickEnd;
    bool           m_isAllPickEnable;
    bool           m_IsSliderByTime;
    bool           m_pDayPickerAnimation;
    int            m_needUpdateMon;
    int            m_needUpdateYear;
    int            m_IsneedUpdateMon;
    int            m_IsneedUpdateYear;
};

#endif // DATETIMEPICKER_H
