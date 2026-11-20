// SPDX-FileCopyrightText: 2019-2022 Connor McLaughlin <stenzek@gmail.com>
// SPDX-License-Identifier: (GPL-3.0 OR CC-BY-NC-ND-4.0)

#pragma once

#include "core/controller.h"
#include "core/settings.h"
#include <QtWidgets/QWidget>
#include <functional>
#include <vector>

#include "ui_controllerbindingwidget.h"
#include "ui_controllerbindingwidget_analog_controller.h"
#include "ui_controllerbindingwidget_analog_joystick.h"
#include "ui_controllerbindingwidget_digital_controller.h"
#include "ui_controllerbindingwidget_guncon.h"
#include "ui_controllerbindingwidget_mouse.h"
#include "ui_controllerbindingwidget_negcon.h"

class QVBoxLayout;

class InputBindingWidget;
class ControllerSettingsDialog;
class ControllerCustomSettingsWidget;
class ControllerBindingWidget_Base;

//////////////////////////////////////////////////////////////////////////

class ControllerBindingWidget final : public QWidget
{
  Q_OBJECT

public:
  ControllerBindingWidget(QWidget* parent, ControllerSettingsDialog* dialog, u32 port);
  ~ControllerBindingWidget();

  QIcon getIcon() const;

  ALWAYS_INLINE ControllerSettingsDialog* getDialog() const { return m_dialog; }
  ALWAYS_INLINE const std::string& getConfigSection() const { return m_config_section; }
  ALWAYS_INLINE ControllerType getControllerType() const { return m_controller_type; }
  ALWAYS_INLINE u32 getPortNumber() const { return m_port_number; }

private Q_SLOTS:
  void onTypeChanged();
  void onAutomaticBindingClicked();
  void onClearBindingsClicked();
  void onBindingsClicked();
  void onSettingsClicked();

private:
  void populateControllerTypes();
  void populateWidgets();
  void updateHeaderToolButtons();
  void doDeviceAutomaticBinding(const QString& device);
  void saveAndRefresh();

  Ui::ControllerBindingWidget m_ui;

  ControllerSettingsDialog* m_dialog;

  std::string m_config_section;
  ControllerType m_controller_type;
  u32 m_port_number;

  ControllerBindingWidget_Base* m_bindings_widget = nullptr;
  ControllerCustomSettingsWidget* m_settings_widget = nullptr;
};

//////////////////////////////////////////////////////////////////////////

class ControllerCustomSettingsWidget : public QWidget
{
  Q_OBJECT

public:
  ControllerCustomSettingsWidget(ControllerBindingWidget* parent);
  ~ControllerCustomSettingsWidget();

  void createSettingWidgets(ControllerBindingWidget* parent, QWidget* parent_widget, QGridLayout* layout,
                            const Controller::ControllerInfo* cinfo);

private Q_SLOTS:
  void restoreDefaults();

private:
  ControllerBindingWidget* m_parent;
};

//////////////////////////////////////////////////////////////////////////

class ControllerBindingWidget_Base : public QWidget
{
  Q_OBJECT

public:
  ControllerBindingWidget_Base(ControllerBindingWidget* parent);
  virtual ~ControllerBindingWidget_Base();

  ALWAYS_INLINE ControllerSettingsDialog* getDialog() const
  {
    return static_cast<ControllerBindingWidget*>(parent())->getDialog();
  }
  ALWAYS_INLINE const std::string& getConfigSection() const
  {
    return static_cast<ControllerBindingWidget*>(parent())->getConfigSection();
  }
  ALWAYS_INLINE ControllerType getControllerType() const
  {
    return static_cast<ControllerBindingWidget*>(parent())->getControllerType();
  }
  ALWAYS_INLINE u32 getPortNumber() const { return static_cast<ControllerBindingWidget*>(parent())->getPortNumber(); }

  virtual QIcon getIcon() const;

protected:
  void initBindingWidgets();
};

//////////////////////////////////////////////////////////////////////////

class ControllerBindingWidget_DigitalController final : public ControllerBindingWidget_Base
{
  Q_OBJECT

public:
  ControllerBindingWidget_DigitalController(ControllerBindingWidget* parent);
  ~ControllerBindingWidget_DigitalController();

  QIcon getIcon() const override;

  static ControllerBindingWidget_Base* createInstance(ControllerBindingWidget* parent);

private:
  Ui::ControllerBindingWidget_DigitalController m_ui;
};

//////////////////////////////////////////////////////////////////////////

class ControllerBindingWidget_AnalogController final : public ControllerBindingWidget_Base
{
  Q_OBJECT

public:
  ControllerBindingWidget_AnalogController(ControllerBindingWidget* parent);
  ~ControllerBindingWidget_AnalogController();

  QIcon getIcon() const override;

  static ControllerBindingWidget_Base* createInstance(ControllerBindingWidget* parent);

private:
  Ui::ControllerBindingWidget_AnalogController m_ui;
};

//////////////////////////////////////////////////////////////////////////

class ControllerBindingWidget_AnalogJoystick final : public ControllerBindingWidget_Base
{
  Q_OBJECT

public:
  ControllerBindingWidget_AnalogJoystick(ControllerBindingWidget* parent);
  ~ControllerBindingWidget_AnalogJoystick();

  QIcon getIcon() const override;

  static ControllerBindingWidget_Base* createInstance(ControllerBindingWidget* parent);

private:
  Ui::ControllerBindingWidget_AnalogJoystick m_ui;
};

//////////////////////////////////////////////////////////////////////////

class ControllerBindingWidget_NeGcon final : public ControllerBindingWidget_Base
{
  Q_OBJECT

public:
  ControllerBindingWidget_NeGcon(ControllerBindingWidget* parent);
  ~ControllerBindingWidget_NeGcon();

  QIcon getIcon() const override;

  static ControllerBindingWidget_Base* createInstance(ControllerBindingWidget* parent);

private:
  Ui::ControllerBindingWidget_NeGcon m_ui;
};

//////////////////////////////////////////////////////////////////////////

class ControllerBindingWidget_GunCon final : public ControllerBindingWidget_Base
{
  Q_OBJECT

public:
  ControllerBindingWidget_GunCon(ControllerBindingWidget* parent);
  ~ControllerBindingWidget_GunCon();

  QIcon getIcon() const override;

  static ControllerBindingWidget_Base* createInstance(ControllerBindingWidget* parent);

private:
  Ui::ControllerBindingWidget_GunCon m_ui;
};

//////////////////////////////////////////////////////////////////////////

class ControllerBindingWidget_Mouse final : public ControllerBindingWidget_Base
{
  Q_OBJECT

public:
  ControllerBindingWidget_Mouse(ControllerBindingWidget* parent);
  ~ControllerBindingWidget_Mouse();

  QIcon getIcon() const override;

  static ControllerBindingWidget_Base* createInstance(ControllerBindingWidget* parent);

private:
  Ui::ControllerBindingWidget_Mouse m_ui;
};

//////////////////////////////////////////////////////////////////////////
