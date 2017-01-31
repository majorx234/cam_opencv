#ifndef QT_DISPLAY_PARAMETERS_WINDOW_H
#define QT_DISPLAY_PARAMETERS_WINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QImage>
#include <QTimer>
#include <mutex>
#include <condition_variable>

class QtDisplayParametersWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit QtDisplayParametersWindow(QWidget *parent = Q_NULLPTR);
  ~QtDisplayParametersWindow();    
  double getParameter();
  void setBild(QImage bild);
  void close();

private:
  QPushButton *closeButton;
  QPushButton *newFrameButton;
  QDoubleSpinBox *parameterBox;
  QPushButton *newParameter;
  QGraphicsScene* scene;
  QGraphicsView* scene_view;
  QTimer*screenRefreshTimer;
  double parameter;
  
  QImage bild;
  std::mutex bildMutex;
  std::condition_variable bildCV;

  bool closed;
  bool bildReadingRequest;
  std::mutex bildReadingRequestMutex; 
  std::condition_variable bildReadingRequestCV;

private slots:
  void on_closebutton_clicked();   
  void pullNewFrame();
  void on_new_parameter_clicked();

 

};





#endif //QT_DISPLAY_PARAMETERS_WINDOW_H