/*#include <QtGui>
#include <QtWidgets>


class MainWindow : public QMainWindow {

public:

  MainWindow();


private:

  void create_actions_();
  void create_menus_();
  void create_toolbar_();

  void about_();

  QMenuBar* menu_bar_;
  QMenu* file_menu_;
  QMenu* help_menu_;

  QToolBar* file_toolbar_;

  QAction* action_about_;

};



MainWindow::MainWindow() {
  resize(800, 600);

  create_actions_();
}


void MainWindow::create_actions_() {
  action_about_ = new QAction(tr("About"), this);
  connect(action_about_, &QAction::triggered, this, &MainWindow::about_);
}


void MainWindow::create_menus_() {

  menu_bar_ = new QMenuBar(this);

  file_menu_ = menu_bar_->addMenu(tr("&File"));

  help_menu_ = menu_bar_->addMenu(tr("&Help"));
  help_menu_->addAction(action_about_);

  menu_bar_->setNativeMenuBar(true);
}


void MainWindow::create_toolbar_() {

  file_toolbar_ = addToolBar(tr("File"));
  file_toolbar_->addAction(action_about_);

  file_toolbar_->setIconSize(QSize(16, 16));

}


void MainWindow::about_() {
  QMessageBox::about(this, tr("About"), tr("FooBar"));
}


int main(int argc, char **argv) {

  QApplication app(argc, argv);

  MainWindow main_window;
  main_window.show();

  const int exit_code = app.exec();
  return exit_code;
}*/
