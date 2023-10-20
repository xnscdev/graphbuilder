#ifndef BUILDCONTEXT_H
#define BUILDCONTEXT_H

#include <QPainter>

class BuildContextException : public std::exception {
public:
  explicit BuildContextException(QString msg) : msg(std::move(msg)) {}
  [[nodiscard]] QString getMessage() const { return msg; }

private:
  QString msg;
};

class BuildContext {
public:
  explicit BuildContext(QPainter &painter, int width, int height)
      : painter(painter), width(width), height(height) {}
  void setupGraph();
  static int axisIncrement(int min, int max);

  int transposeX(int x) { return graphTransform.x() + x; }

  int transformX(double x) {
    return static_cast<int>(graphTransform.x() + graphTransform.width() * x);
  }

  int transposeY(int y) { return graphTransform.bottom() - y; }

  int transformY(double y) {
    return static_cast<int>(graphTransform.bottom() -
                            graphTransform.height() * y);
  }

  QRect getRectTransformedY(int x, double y, int w, double h) {
    int top = transformY(y + h);
    return {transposeX(x), top, w, transformY(y) - top};
  }

  QPoint getPointTransformedY(int x, double y) {
    return {transposeX(x), transformY(y)};
  }

  QPainter &painter;
  int currHeight = padding;
  int currBlockId = 0;

private:
  static const int padding = 20;
  int width;
  int height;
  bool graphSetupDone = false;
  QRect graphTransform;
};

struct GraphTickInfo {
  QRect rect;
  QString label;
  double y;
};

#endif
