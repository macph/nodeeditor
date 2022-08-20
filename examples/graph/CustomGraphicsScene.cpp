#include "CustomGraphicsScene.hpp"

#include <QtGui/QCursor>
#include <QtWidgets/QMenu>
#include <QtNodes/internal/ConnectionGraphicsObject.hpp>
#include <QtNodes/ConnectionIdUtils>

CustomGraphicsScene::CustomGraphicsScene(QtNodes::AbstractGraphModel &graphModel,
                                         QObject *parent)
  : QtNodes::BasicGraphicsScene(graphModel, parent)
{}

void CustomGraphicsScene::handleDroppedDraftConnection(QPointF scenePos)
{
  auto menu = QMenu();
  auto action = menu.addAction("Add node here");
  auto result = menu.exec(QCursor::pos());

  if (result != action) {
    return;
  }

  auto draft = draftConnection();

  if (!draft) {
    return;
  }

  auto nodeId = graphModel().addNode(QString());
  graphModel().setNodeData(nodeId, QtNodes::NodeRole::Position, scenePos);

  auto connectionId = QtNodes::makeCompleteConnectionId(draft->connectionId(), nodeId, 0);

  graphModel().addConnection(connectionId);
}
