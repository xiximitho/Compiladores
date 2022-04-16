//
// Created by felipe on 15/04/2021.
//

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_
#include "gtkmm-4.0/gtkmm.h"
#include "sigc++/sigc++.h"
#include <utility>
#include <iostream>

class MainWindow : public Gtk::Window
{
public:
  MainWindow();
  ~MainWindow() override;

protected:
  // Sinais
  void on_click_m_Button_Quit();

private:
  void set_layout();
  void set_slots();

  // Componentes
  Gtk::Box m_VBox;
  Gtk::ScrolledWindow m_scrolledWindow;
};

#endif //_MAINWINDOW_H_
