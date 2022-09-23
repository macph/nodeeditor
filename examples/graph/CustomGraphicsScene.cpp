#include "CustomGraphicsScene.hpp"

#include <QtGui/QAction>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMenu>
#include <QtNodes/ConnectionIdUtils>

CustomGraphicsScene::
CustomGraphicsScene(QtNodes::AbstractGraphModel &graphModel, QObject *parent)
  : QtNodes::BasicGraphicsScene(graphModel, parent)
{}

void
CustomGraphicsScene::
handleDroppedDraftConnection(QPointF const & scenePos,
                             QtNodes::ConnectionId const & draftConnectionId)
{
  auto v = views();

  if (v.isEmpty()) {
    resetDraftConnection();
    return;
  }

  auto view = v.first();

  auto menu = new QMenu(view);
  menu->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);

  connect(menu, &QMenu::destroyed, [&]() { resetDraftConnection(); });

  auto action = menu->addAction("Add node here");

  connect(action, &QAction::triggered,
          [&, scenePos, draftConnectionId]()
          {
            auto nodeId = graphModel().addNode(QString());

            graphModel().setNodeData(nodeId, QtNodes::NodeRole::Position, scenePos);

            graphModel().addConnection(
              makeCompleteConnectionId(draftConnectionId, nodeId, 0));
          });

  auto pos = view->mapToGlobal(view->mapFromScene(scenePos));

  menu->popup(pos);
}
