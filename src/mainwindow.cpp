//
// Created by felipe on 15/04/2021.
//
#include "mainwindow.h"

MainWindow::~MainWindow() = default;

MainWindow::MainWindow()
    : m_VBox(Gtk::Orientation::VERTICAL)
{
  set_layout();
  set_slots();
}
void MainWindow::set_layout()
{
  set_title("Analisador Léxico");
  set_default_size(1000, 600);

  m_VBox.set_margin(5);
  set_child(m_VBox);


  //m_VBox.append(m_buttonBox);
  //m_scrolledWindow.set_child(m_treeView);
  // Mostra scrollbar somente quando é necessario
  m_scrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_scrolledWindow.set_expand();
  m_VBox.append(m_scrolledWindow);
}

void MainWindow::set_slots()
{
  //m_button_Decompress.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_click_m_Button_Decompress));
}

/*
void MainWindow::on_click_m_Button_Compress()
{
}*/