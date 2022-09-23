#pragma once

#include <QtNodes/BasicGraphicsScene>
#include <QtCore/QPointF>

class CustomGraphicsScene : public QtNodes::BasicGraphicsScene
{
  Q_OBJECT

public:
  CustomGraphicsScene(QtNodes::AbstractGraphModel &graphModel, QObject *parent = nullptr);

  void
  handleDroppedDraftConnection(
    QPointF const & scenePos,
    QtNodes::ConnectionId const & draftConnectionId) override;
};
