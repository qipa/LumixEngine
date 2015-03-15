#pragma once


#include <cstdint>
#include <qdockwidget.h>
#include <qundostack.h>


namespace Lumix
{
	struct Component;
	class WorldEditor;
}


class AnimationEditor;
class AnimationNode;
class AnimatorNodeContent;
class Animator;
class AnimatorNode;
class PropertyView;
class ScriptCompiler;


class AnimationGraphView : public QWidget
{
	Q_OBJECT
	public:
		enum class MouseMode
		{
			NONE,
			DRAGGING,
			EDGE
		};

	public:
		AnimationGraphView(AnimationEditor& editor);

		void setNode(AnimatorNode* node) { m_node = node; }

	private:
		virtual void paintEvent(QPaintEvent*) override;
		virtual void mousePressEvent(QMouseEvent*) override;
		virtual void mouseMoveEvent(QMouseEvent*) override;
		virtual void mouseReleaseEvent(QMouseEvent*) override;
		void drawGrid(QPainter& painter);
		void drawNodes(QPainter& painter);
		void drawNewEdge(QPainter& painter);
		void selectNode(AnimatorNode* node);

	private slots:
		void showContextMenu(const QPoint& pos);

	private:
		AnimatorNode* m_node;
		AnimatorNode* m_mouse_node;
		MouseMode m_mouse_mode;
		QPoint m_last_mouse_position;
		AnimationEditor& m_editor;
};



class AnimationEditor : public QDockWidget
{
	Q_OBJECT
	public:
		AnimationEditor(PropertyView& property_view, ScriptCompiler& compiler);

		void setWorldEditor(Lumix::WorldEditor& editor);
		void setComponent(const Lumix::Component& component);
		void update(float time_delta);
		Animator* getAnimator() { return m_animator; }
		void executeCommand(QUndoCommand* command);
		PropertyView& getPropertyView() { return m_property_view; }
		AnimatorNodeContent* createContent(AnimatorNode& node, uint32_t content_type);

	private slots:
		void onCompileAction();
		void onRunAction();
		void onSaveAction();
		void onSaveAsAction();
		void onLoadAction();

	private:
		QUndoStack m_undo_stack;
		Animator* m_animator;
		AnimationGraphView* m_animation_graph_view;
		PropertyView& m_property_view;
		Lumix::WorldEditor* m_editor;
		ScriptCompiler& m_compiler;
};