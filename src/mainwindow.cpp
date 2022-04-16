//
// Created by felipe on 15/04/2021.
//
#include "mainwindow.h"

MainWindow::~MainWindow() = default;

MainWindow::MainWindow()
    : m_VBox(Gtk::Orientation::VERTICAL, 6),
      m_button_Fechar("_Fechar", true),
      m_button_Limpar("_Limpar", true)
{
  set_layout();
  set_slots();
}
void MainWindow::set_layout()
{
  set_title("Analisador Léxico");
  set_default_size(1000, 600);

  m_VBox.set_margin(6);
  set_child(m_VBox);

  // infoBar
  m_infoBar.add_child(m_label_Mensagem);
  // Adicionar o botão para a barra de info quando aparente:
  m_infoBar.add_button("_OK", 0);
  m_VBox.append(m_infoBar);

  // Cria o buffer e atribui ao TextView
  m_refTextBuffer = Gtk::TextBuffer::create();
  m_textView.set_buffer(m_refTextBuffer);

  // scrolledWindow
  m_scrolledWindow.set_child(m_textView);
  m_scrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_scrolledWindow.set_expand();
  m_VBox.append(m_scrolledWindow);

  // buttonBox
  m_VBox.append(m_buttonBox);
  m_buttonBox.append(m_button_Limpar);
  m_buttonBox.append(m_button_Fechar);

  m_buttonBox.set_spacing(6);
  m_button_Limpar.set_hexpand(true);
  m_button_Limpar.set_halign(Gtk::Align::END);

  m_infoBar.hide();
  m_button_Limpar.set_sensitive(false);
}

void MainWindow::set_slots()
{
  m_button_Limpar.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_click_m_button_limpar));
  m_infoBar.signal_response().connect(sigc::mem_fun(*this, &MainWindow::on_response_m_infobar));
  m_refTextBuffer->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_changed_m_reftextbuffer));
}

void MainWindow::on_changed_m_reftextbuffer()
{
  // Só fica habilitado quando há algo em buffer.
  m_button_Limpar.set_sensitive(m_refTextBuffer->size() > 0);
}

void MainWindow::on_response_m_infobar(int)
{
  m_label_Mensagem.set_text("");
  m_infoBar.hide();
}

void MainWindow::on_click_m_button_limpar()
{
  m_refTextBuffer->set_text("");

  m_label_Mensagem.set_text("Texto limpo");
  m_infoBar.set_message_type(Gtk::MessageType::INFO);
  m_infoBar.show();
}