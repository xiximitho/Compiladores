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
  // Eventos para connect
  void on_click_m_button_limpar();
  void on_response_m_infobar(int response);
  void on_changed_m_reftextbuffer();

  // Widgets.
  Gtk::Box m_VBox;
  Gtk::ScrolledWindow m_scrolledWindow;
  Gtk::TextView m_textView;
  Gtk::InfoBar m_infoBar;
  Gtk::Label m_label_Mensagem;
  Gtk::Box m_buttonBox;
  Gtk::Button m_button_Fechar, m_button_Limpar;

  // Para acessar o buffer de texto.
  Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

private:
  void set_layout();
  void set_slots();
};

#endif //_MAINWINDOW_H_
