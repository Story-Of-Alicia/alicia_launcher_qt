#ifndef GameStartWidget_HPP
#define GameStartWidget_HPP

#include <QOpenGLWidget>
namespace ui
{
class GameStartWidget : public QOpenGLWidget
{
Q_OBJECT
public:
  GameStartWidget(QWidget *parent) : QOpenGLWidget(parent) {};
protected:
  void paintGL() override;
};
}

#endif // GameStartWidget_HPP