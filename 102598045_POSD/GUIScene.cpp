#include "GUIScene.h"
#include "GraphicalUI.h"
#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include "GraphicalPresentation.h"
#include "WidgetFactory.h"

GUIScene::GUIScene(QRectF sceneRect,GraphicalUI* graphicalUI,QGraphicsView* view) : QGraphicsScene(sceneRect,graphicalUI),graphicalUI(graphicalUI),view(view){
    this->graphicalPresentation = this->graphicalUI->getGraphicalPresentation();
    this->graphicalPresentation->registerObserver(this);
    this->connect(this,SIGNAL(notifyEvent()),this,SLOT(executeNotify()));
}

GUIScene::~GUIScene(){
    this->graphicalUI->getGraphicalPresentation()->unregisterObserver(this);
}

void GUIScene::notify(ISubject* subject){
    this->notifyEvent();
}

void GUIScene::displayDiagram(){
    this->clearAll();
    WidgetFactory widgetFactory;
    //display preview
    if(this->graphicalPresentation->getPreviewState()){
        BaseWidget* widget = widgetFactory.createPreviewWidget(this->graphicalPresentation);
        this->addWidget(widget);
    }
    //display all
    HashMap<string,Component*>& componentMap = this->graphicalPresentation->getAllComponents();
    for each(Component* component in componentMap){
        BaseWidget* componentWidget = widgetFactory.createComponentWidget(component,this->graphicalPresentation);
        this->addWidget(componentWidget);
    }
}

void GUIScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF qPosition = mouseEvent->scenePos();
    ComponentWidget* widget = static_cast<ComponentWidget*>(this->itemAt(qPosition));
    Component* component = NULL;
    Point position = Point(qPosition.x(),qPosition.y());
    if(widget){
        component = widget->getComponent();
        this->view->ensureVisible(widget);
    }
    this->graphicalPresentation->mousePressEvent(position,component);
    this->updateAll();
}

void GUIScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF qPosition = mouseEvent->scenePos();
    ComponentWidget* widget = static_cast<ComponentWidget*>(this->itemAt(qPosition));
    Component* component = NULL;
    Point position = Point(qPosition.x(),qPosition.y());
    if(widget){
        component = widget->getComponent();
        this->view->ensureVisible(widget);
    }
    this->graphicalPresentation->mouseMoveEvent(position,component);
    this->updateAll();
}

void GUIScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF qPosition = mouseEvent->scenePos();
    ComponentWidget* widget = static_cast<ComponentWidget*>(this->itemAt(qPosition));
    Component* component = NULL;
    Point position = Point(qPosition.x(),qPosition.y());
    if(widget){
        component = widget->getComponent();
        this->view->ensureVisible(widget);
    }
    this->graphicalPresentation->mouseReleaseEvent(position,component);
    this->updateAll();
}

void GUIScene::executeNotify(){
    this->displayDiagram();
}

void GUIScene::addWidget(BaseWidget* widget){
    this->addItem(widget);
    this->widgetList.push_back(widget);
    widget->updateWidget();
    this->view->ensureVisible(widget);
}

void GUIScene::updateAll(){
    for each(BaseWidget* widget in this->widgetList){
        widget->updateWidget();
    }
    this->update();
}

void GUIScene::clearAll(){
    this->clear();
    //qt's scene will auto delete widget item,so the work we have to do just clear it.
    this->widgetList.clear();
}