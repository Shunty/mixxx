/***************************************************************************
                          dlgprefvinyl.h  -  description
                             -------------------
    begin                : Thu Oct 23 2006
    copyright            : (C) 2006 by Stefan Langhammer
    email                : stefan.langhammer@9elements.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef DLGPREFVINYL_H
#define DLGPREFVINYL_H

#include <QWidget>

#include "ui_dlgprefvinyldlg.h"
#include "configobject.h"
#include "vinylcontrol/vinylcontrolsignalwidget.h"
#include "preferences/dlgpreferencepage.h"

class ControlObjectSlave;
class VinylControlManager;

class DlgPrefVinyl : public DlgPreferencePage, Ui::DlgPrefVinylDlg  {
    Q_OBJECT
  public:
    DlgPrefVinyl(QWidget* pParent, VinylControlManager* m_pVCMan, ConfigObject<ConfigValue>* _config);
    virtual ~DlgPrefVinyl();

  public slots:
    void slotUpdate();
    void slotApply();
    void slotHide();
    void slotShow();
    void VinylTypeSlotApply();
    void VinylGainSlotApply();

  private slots:
    void slotNumDecksChanged(double);

  private:
    void setDeckWidgetsVisible(int deck, bool visible);
    void setDeck1WidgetsVisible(bool visible);
    void setDeck2WidgetsVisible(bool visible);
    void setDeck3WidgetsVisible(bool visible);
    void setDeck4WidgetsVisible(bool visible);

    QList<VinylControlSignalWidget*> m_signalWidgets;

    VinylControlManager* m_pVCManager;
    ConfigObject<ConfigValue>* config;
    QList<ControlObjectSlave*> m_COSpeeds;
    ControlObjectSlave* m_pNumDecks;
    int m_iConfiguredDecks;
};

#endif
