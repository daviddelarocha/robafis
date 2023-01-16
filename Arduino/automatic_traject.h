// automatic_traject.h

//------------------------------------------------------------PACKAGES-------------------------------------------------------------------------

#include "graph.h"
#include "airport_graph.h"
#include "LinkedList.h"

//------------------------------------------------------------GlOBAL_VAR-----------------------------------------------------------------------

//------------------------------------------------------------FUNCTIONS------------------------------------------------------------------------

LinkedList<Action> add_auto_path(Node start_node, Node end_node, Graph AIRPORT_GRAPH, LinkedList<Action> ACTION_PILE)
{
  LinkedList<Node> nodes = map_nodes(start_node, end_node);
  start_node = nodes.getCurrent();
  nodes.next();
  end_node = nodes.getCurrent();
  LinkedList<Arc> path_arcs = AIRPORT_GRAPH.get_path(start_node, end_node);
  Serial.print("Path length : ");
  Serial.print(path_arcs.getLength());
  Serial.println("Path : ");

  for(int i = 0; i < path_arcs.getLength(); i++)
  {
    path_arcs.moveToStart();
    Arc a = path_arcs.getCurrent();
    a.print();
    LinkedList<Action> cost = a.getCost();
    if(cost.getLength() > 0)
    {
      do
      {
        //cost.getCurrent().print();
        ACTION_PILE.Append(cost.getCurrent());
      } while (cost.next());
    }
    path_arcs.next();
  }

  return ACTION_PILE;

}

LinkedList<Action> exec_auto(LinkedList<Action> ACTION_PILE)
{
  if(ACTION_PILE.getLength() > 0)
  {
    if(ACTION_PILE.getCurrent().execAction())
    {
      // ACTION_PILE.getCurrent().print();
      ACTION_PILE.DeleteCurrent();
      // STOP_R();
    }
  }

  return ACTION_PILE;
}